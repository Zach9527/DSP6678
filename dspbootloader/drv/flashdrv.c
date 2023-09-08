/******************************************************************************
 * filename:  flash.c
 *
 * describe:	flash type => MT28EW256
 *
 * author:
 */
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "progress_bar.h"
#include "uart_dsp6678.h"
/*Macro define*/
#define	Uint32	unsigned int
#define	Uint16	unsigned short
#define	Uint8	unsigned char

#define	SUCCESS					(0)
#define	FAIL 					(1)
#define SECTOR_SIZE				(0x10000)	/*64K*16bit*/

#define TOTAL_SECTOR_NUM		(512)      //扇区总数
#define	MAX_SECTOR_NUM			(511)
#define	S29GL_CHIP_SIZE		(0x4000000)	/* 64M */
#define flash_base_addr			0x70000000  //flash 挂载在DSP的CS0空间
#define CORE0_FLASH_BASE_ADDR	0x70020000  //core0分配10M的flash空间
#define CORE1_FLASH_BASE_ADDR   0x70a00000  //
#define CORE2_FLASH_BASE_ADDR   0x71400000

#define SOURCE_FILE_OFFSET 6//经过转换工具后生成的*.dat文件前面8个32bit不是内存中的数据


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

void mt28ew256Reset()
{
	Uint16 i = 0;
	s29glWrite16bit(0x555,0xAA);
	for(i=0;i<100;i++);
	s29glWrite16bit(0x2AA,0x55);
	for(i=0;i<100;i++);
	s29glWrite16bit(0x0,0xF0);
	for(i=0;i<100;i++);
}
void mt28ew256ChipErase()
{
    	Uint16 i = 0;
	s29glWrite16bit(0x555,0xAA);
	for(i=0;i<100;i++);
	s29glWrite16bit(0x2AA,0x55);
	for(i=0;i<100;i++);
	s29glWrite16bit(0x555,0x80);
	for(i=0;i<100;i++);
    s29glWrite16bit(0x555,0xAA);
	for(i=0;i<100;i++);
    s29glWrite16bit(0x2AA,0x55);
	for(i=0;i<100;i++);
    s29glWrite16bit(0x555,0x10);
	for(i=0;i<100;i++);
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
		PRINT("Invalid Sector Number: %d.\r\n",sectorNum);
		return FAIL;
		}
	SectorAddr = flash_base_addr + sectorNum * SECTOR_SIZE;
	PRINT("Sector Address: 0x%x,Sector Num: %d\r\n",SectorAddr,sectorNum);
//	s29glWrite16bit(0x555,0x98);
//	for(i=0;i<100;i++);
//	s29glWrite16bit(0x0,0xF0);
//	for(i=0;i<100;i++);
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

	PRINT("Sector %d Erase Done.\r\n",sectorNum);
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
Uint32 program_boot_to_flash(void)
{
    unsigned int DataHead[SOURCE_FILE_OFFSET],Data_Tmp,temp,temp1;
    unsigned int i,j, m,count,length,length2,offset_temp;
    unsigned int block_begin_num=0;
    unsigned int flash_program_addr;
    Uint8        write_block;
    FILE *file_boot, *file_boot2;
    HANDLE_BAR *handle_bar;

    file_boot=fopen("vector_boot.dat","rb");
    file_boot2=fopen("twice_boot.dat","rb");
    //初始化参数表
    flash_program_addr=CORE0_FLASH_BASE_ADDR;
    block_begin_num=0;

	if((file_boot==0) || (file_boot2==0))
	{
	 	printf("Flash Program: Can't open file!\n");
	 	return FAIL;
	}

	//for(j=0;j<5;j++)
	for(j=0;j<SOURCE_FILE_OFFSET;j++)
	{
	fscanf(file_boot,"%x",&DataHead[j]);       	    //以16进制格式读取一维数组
		//fread(&DataHead[j], 1, sizeof(unsigned int), file);
	}
	length = DataHead[4];                 			//数组最后一个元素为要烧写的文件的长度

	for(j=0;j<SOURCE_FILE_OFFSET;j++)
	{
	fscanf(file_boot2,"%x",&DataHead[j]);       	    //以16进制格式读取一维数组
		//fread(&DataHead[j], 1, sizeof(unsigned int), file);
	}
	length2 = DataHead[4];                 			//数组最后一个元素为要烧写的文件的长度


	/********计算烧写的代码需要占用的扇区个数***********/
	write_block=((length+length2)*4)/SECTOR_SIZE;
	if((length+length2)%SECTOR_SIZE)
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
    //烧写第一部分
    for(i=0;i<length;i++)
	{
		fscanf(file_boot,"%x",&Data_Tmp);

		//fread(&Data_Tmp, 1, sizeof(unsigned int), file);
		//printf("0x%08x\n", Data_Tmp);
		for(j=0;j<2;j++, count = 0)
		{
			if(j==0)
				temp=Data_Tmp&0x0000ffff;
			else
				temp=Data_Tmp>>16;

			ProgramFastMode(flash_program_addr+(2*i+j)*2, (Uint16 )(temp));
			//Program16Data(flash_program_addr+(2*i+j)*2, (Uint16 )(temp));
			do
			{
				temp1 = *(volatile unsigned short *)( flash_program_addr+(2*i+j)*2 );
				count += 1;
				if(count > 0xffffff)
				{
					//wrong_num = 1;
					//break;
				}
			}while(temp != temp1);
		}

		progress_bar(handle_bar, i, length);
	}

    stop_progress_bar(handle_bar);
    offset_temp = i;
    //烧写第二部分
    for(i = 0;i<length2;i++)
	{
		fscanf(file_boot2,"%x",&Data_Tmp);

		//fread(&Data_Tmp, 1, sizeof(unsigned int), file);
		//printf("0x%08x\n", Data_Tmp);
		for(j=0;j<2;j++)
		{
			if(j==0)
				temp=Data_Tmp&0x0000ffff;
			else
				temp=Data_Tmp>>16;

			ProgramFastMode(flash_program_addr+(2*(i+offset_temp)+j)*2, (Uint16 )(temp));
			do
			{
				temp1 = *(volatile unsigned short *)( flash_program_addr+(2*(i+offset_temp)+j)*2 );
				for(m = 0; m < 100; m++);
			}while(temp != temp1);
		}

		progress_bar(handle_bar, i, length2);
	}
    stop_progress_bar(handle_bar);
    CloseFastMode();

    destory_progress_bar(handle_bar);

    fclose(file_boot);
    fclose(file_boot2);

    printf("Flash Program is SUCCESS!Program  code %d byte to flash!!!\n",(length + length2)*4);
    return SUCCESS;
 }
/*
 * QRY
 */
void qryShow(void)
{
	unsigned char CfiFlag[4];
	int i;
	volatile unsigned short *pNOR =(unsigned short *)flash_base_addr;

	pNOR[0x55] = 0x0098;/*16bit write CFI entry command*/
	for(i=0;i<10*1000;i++);

	CfiFlag[0] = (char) pNOR[0x10];
	CfiFlag[1] = (char) pNOR[0x11];
	CfiFlag[2] = (char) pNOR[0x12];

	if((CfiFlag[0]!='Q')||(CfiFlag[1]!='R')||(CfiFlag[2]!='Y'))
	{
		printf("*****error CFI flsh%c%c%c*****\n",CfiFlag[0],CfiFlag[1],CfiFlag[2]);
		while(1);
	}
	else
	{
		printf("----Find CFI---\r\n");
	}
	pNOR[0x00] = 0x00f0;/* exit CFI entry command*/
	for(i=0;i<10*1000;i++);
}
