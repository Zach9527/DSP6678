/******************************************************************************
 * filename:  flash.c
 *
 * describe:	flash type => S29GL512N
 *
 * author:
 *
 * 修改历史：2014 - 06 - 12
 * 		描述：（1）添加flash快速模式（bypass模式）
 * 			（2）改进写操作是否完成的判断方式
 * 			（3）添加进度条显示
 * 			（4）CORE0烧写地址和flash地址的改动
 * 		by YangJun
 */
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "progress_bar.h"
/*Macro define*/
#define	Uint32	unsigned int
#define	Uint16	unsigned short
#define	Uint8	unsigned char


#define SECTOR_SIZE				(0x20000)	/*64K*16bit   128K*8bit*/
#define	MAX_SECTOR_NUM			(511)

#define	S29GL_CHIP_SIZE		(0x4000000)	/* 64M */
#define flash_base_addr			0x70000000  //flash 挂载在DSP的CS0空间
#define CORE0_FLASH_BASE_ADDR	0x70020000  //core0分配640k - 64K的flash空间
#define CORE1_FLASH_BASE_ADDR   0x70a00000  //640K
#define CORE2_FLASH_BASE_ADDR   0x71400000

#define SOURCE_FILE_OFFSET 5//经过转换工具后生成的*.dat文件前面5个32bit不是内存中的数据


/******************************************************************************
*
* 函数名：       s29glWrite16bit
*
* 函数功能： 向FLASH的偏移地址写一个16位数据
*
* 入口参数：偏移地址offset； 写入数据：data
*
* 返回值：    无
*
*/
void s29glWrite16bit(Uint16 offset , Uint16 data)
{
	*(Uint16 *)(flash_base_addr+(offset<<1)) = data;
}
/******************************************************************************
*
* 函数名：       sm29glRead16bit
*
* 函数功能： 向FLASH的偏移地址读一个16位数据
*
* 入口参数：偏移地址offset
*
* 返回值：    读出数据data
*
*/
Uint16 sm29glRead16bit(Uint16 offset)
{
	Uint16 data;
	data = *(Uint16 *)(flash_base_addr+(offset<<1));
	return data;
}

/*********************************************
 *
 *函数名:	SectorErase
 *
 *函数功能:	擦除一个扇区
 *
 *入口参数:	sectorNum
 *
 *返回参数: SUCCESS or FAIL
 *
 *********************************************/

Uint32 SectorErase(Uint32 sectorNum)
{
	Uint16 rc;
	Uint32 SectorAddr;
	Uint16 i;

	if(sectorNum > MAX_SECTOR_NUM)
		{
		printf("Invalid Sector Number: %d.\n",sectorNum);
		return FAIL;
		}
	SectorAddr = flash_base_addr + sectorNum * SECTOR_SIZE;
	printf("Sector Address: 0x%x,Sector Num: %d\n",SectorAddr,sectorNum);

	/*********************扇区擦出前导指令***********************/
	s29glWrite16bit(0x555, 0xAA);
	for(i=0;i<100;i++);
	s29glWrite16bit(0x2AA, 0x55);
	for(i=0;i<100;i++);
	s29glWrite16bit(0x555, 0x80);
	for(i=0;i<100;i++);
	s29glWrite16bit(0x555, 0xAA);
	for(i=0;i<100;i++);
	s29glWrite16bit(0x2AA, 0x55);
	for(i=0;i<100;i++);
	/**********************扇区擦除指令************************/
	*(Uint16 *)SectorAddr = 0x30;

	for(i=0;i<0x0000ffff;i++);

	do
		{
		rc = *(Uint16 *)SectorAddr;
	}while( (rc & 0xffff) !=0xffff );

	printf("Sector %d Erase Done.\n",sectorNum);
	return SUCCESS;
}

/*********************************************
 *
 *函数名:	Program16Data
 *
 *函数功能:	向flash写16bit的数据
 *
 *入口参数:	addr：地址		data：写入的数据
 *
 *返回参数: void
 *
 *********************************************/
void Program16Data(Uint32 addr, Uint16 data)
{
	s29glWrite16bit(0x555, 0xAA);
	s29glWrite16bit(0x2AA, 0x55);
	s29glWrite16bit(0x555, 0xA0);
	*(Uint16 *)(addr) =data;
}

/*********************************************
 *
 *函数名:	OpenFastMode
 *
 *函数功能:	设置快速program模式=》Bypass模式
 *
 *入口参数:	void
 *
 *返回参数: void
 *
 *********************************************/
void OpenFastMode(void)
{
	s29glWrite16bit(0x555, 0xAA);
	s29glWrite16bit(0x2AA, 0x55);
	s29glWrite16bit(0x555, 0x20);
}

/*********************************************
 *
 *函数名:	ProgramFastMode
 *
 *函数功能:	设置快速program模式=》Bypass模式
 *
 *入口参数:	void
 *
 *返回参数: void
 *
 *********************************************/
void ProgramFastMode(Uint32 addr, Uint16 data)
{
	s29glWrite16bit(0x0, 0xA0);
	*(Uint16 *)(addr) =data;
}

/*********************************************
 *
 *函数名:	CloseFastMode
 *
 *函数功能:	设置快速program模式=》Bypass模式
 *
 *入口参数:	void
 *
 *返回参数: void
 *
 *********************************************/
void CloseFastMode(void)
{
	s29glWrite16bit(0x0, 0x90);
	s29glWrite16bit(0x0, 0x00);
}


/*********************************************
 *
 *函数名:	program_code_to_flash
 *
 *函数功能:	将应用程序烧写到flash中
 *
 *入口参数:	unsigned char code_type:表示烧写程序的类型：（0——7）表示core0到core7的应用程序；
 *                                          	   8表示烧写bootloader程序
 *
 *返回参数: SUCCESS or FAIL
 *
 *********************************************/
Uint32 program_code_to_flash(unsigned char code_type)
{
    unsigned int Data_Tmp,temp,temp1;
    unsigned int i,j,length,len;
    unsigned int block_begin_num=0;
    unsigned int flash_program_addr;
    Uint8        write_block;
    FILE * 			file;
    HANDLE_BAR *handle_bar;

    switch (code_type)
		{
		case 0:
		{
			file=fopen("AppPrj.bin","rb");
			flash_program_addr = CORE0_FLASH_BASE_ADDR;
			block_begin_num = 1;//第0扇区用于存放二级bootloader,CORE0的应用程序从第一扇区开始存放
			break;
		}
		case 1:
		{
			file=fopen("app_core\\APPcore1.dat","rb");
			flash_program_addr = CORE1_FLASH_BASE_ADDR;
			block_begin_num = 160;
			break;
		}
		case 2:
		{
			file=fopen("app_core\\APPcore2.dat","rb");
			flash_program_addr = CORE2_FLASH_BASE_ADDR;
			block_begin_num = 320;
			break;
		}
		default:
			printf("input parameter  error! please check it!!!\n");
			return FAIL;
		}

	if(file==0)
	{
	 	printf("Flash Program: Can't open file!\n");
	 	return FAIL;
	}
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

	/********计算烧写的代码需要占用的扇区个数***********/
	write_block=(length)/SECTOR_SIZE;
	if((length)%SECTOR_SIZE)
	{
		write_block=write_block+1;
	}
	/********擦除烧写代码需要占用的扇区***********/
    for(i=block_begin_num;i<write_block+block_begin_num;i++)
    {
    	SectorErase(i);
    }
    /***************烧写代码*******************/
    printf("Flash Program: Start!\n");

    handle_bar = creat_progress_bar();

    OpenFastMode();

    for(i=0; i<(length/4+1); i++)
    {
        len =  fread(&Data_Tmp, 1, sizeof(unsigned int), file);
        if(len == 0)
         {
             printf("file load over\r\n");
             break;
         }

		for(j=0; j<2; j++)
		{
			if(j==0)
				temp=Data_Tmp&0x0000ffff;
			else
				temp=Data_Tmp>>16;

			ProgramFastMode(flash_program_addr+(2*i+j)*2, (Uint16 )(temp));
			do
			{
				temp1 = *(volatile unsigned short *)( flash_program_addr+(2*i+j)*2 );
			}while(temp != temp1);
		}

		progress_bar(handle_bar, i, length);
    }
    stop_progress_bar(handle_bar);

    destory_progress_bar(handle_bar);

    CloseFastMode();

    fclose(file);

    printf("Flash Program is SUCCESS!Program  code %d byte to flash!!!\n",length);
    return SUCCESS;
 }
