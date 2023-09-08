/******************************************************************************
 * filename:  flash.c
 *
 * describe:	flash type => S29GL512N
 *
 * author:
 *
 * �޸���ʷ��2014 - 06 - 12
 * 		��������1�����flash����ģʽ��bypassģʽ��
 * 			��2���Ľ�д�����Ƿ���ɵ��жϷ�ʽ
 * 			��3����ӽ�������ʾ
 * 			��4��CORE0��д��ַ��flash��ַ�ĸĶ�
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
#define flash_base_addr			0x70000000  //flash ������DSP��CS0�ռ�
#define CORE0_FLASH_BASE_ADDR	0x70020000  //core0����640k - 64K��flash�ռ�
#define CORE1_FLASH_BASE_ADDR   0x70a00000  //640K
#define CORE2_FLASH_BASE_ADDR   0x71400000

#define SOURCE_FILE_OFFSET 5//����ת�����ߺ����ɵ�*.dat�ļ�ǰ��5��32bit�����ڴ��е�����


/******************************************************************************
*
* ��������       s29glWrite16bit
*
* �������ܣ� ��FLASH��ƫ�Ƶ�ַдһ��16λ����
*
* ��ڲ�����ƫ�Ƶ�ַoffset�� д�����ݣ�data
*
* ����ֵ��    ��
*
*/
void s29glWrite16bit(Uint16 offset , Uint16 data)
{
	*(Uint16 *)(flash_base_addr+(offset<<1)) = data;
}
/******************************************************************************
*
* ��������       sm29glRead16bit
*
* �������ܣ� ��FLASH��ƫ�Ƶ�ַ��һ��16λ����
*
* ��ڲ�����ƫ�Ƶ�ַoffset
*
* ����ֵ��    ��������data
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
 *������:	SectorErase
 *
 *��������:	����һ������
 *
 *��ڲ���:	sectorNum
 *
 *���ز���: SUCCESS or FAIL
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

	/*********************��������ǰ��ָ��***********************/
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
	/**********************��������ָ��************************/
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
 *������:	Program16Data
 *
 *��������:	��flashд16bit������
 *
 *��ڲ���:	addr����ַ		data��д�������
 *
 *���ز���: void
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
 *������:	OpenFastMode
 *
 *��������:	���ÿ���programģʽ=��Bypassģʽ
 *
 *��ڲ���:	void
 *
 *���ز���: void
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
 *������:	ProgramFastMode
 *
 *��������:	���ÿ���programģʽ=��Bypassģʽ
 *
 *��ڲ���:	void
 *
 *���ز���: void
 *
 *********************************************/
void ProgramFastMode(Uint32 addr, Uint16 data)
{
	s29glWrite16bit(0x0, 0xA0);
	*(Uint16 *)(addr) =data;
}

/*********************************************
 *
 *������:	CloseFastMode
 *
 *��������:	���ÿ���programģʽ=��Bypassģʽ
 *
 *��ڲ���:	void
 *
 *���ز���: void
 *
 *********************************************/
void CloseFastMode(void)
{
	s29glWrite16bit(0x0, 0x90);
	s29glWrite16bit(0x0, 0x00);
}


/*********************************************
 *
 *������:	program_code_to_flash
 *
 *��������:	��Ӧ�ó�����д��flash��
 *
 *��ڲ���:	unsigned char code_type:��ʾ��д��������ͣ���0����7����ʾcore0��core7��Ӧ�ó���
 *                                          	   8��ʾ��дbootloader����
 *
 *���ز���: SUCCESS or FAIL
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
			block_begin_num = 1;//��0�������ڴ�Ŷ���bootloader,CORE0��Ӧ�ó���ӵ�һ������ʼ���
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

	/********������д�Ĵ�����Ҫռ�õ���������***********/
	write_block=(length)/SECTOR_SIZE;
	if((length)%SECTOR_SIZE)
	{
		write_block=write_block+1;
	}
	/********������д������Ҫռ�õ�����***********/
    for(i=block_begin_num;i<write_block+block_begin_num;i++)
    {
    	SectorErase(i);
    }
    /***************��д����*******************/
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
