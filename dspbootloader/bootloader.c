/*
 * bootloader.c
 *
 *  Created on: 2016-3-23
 *      Author: YF
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#include <ti/csl/csl_chip.h>
#include <ti/csl/csl_chipAux.h>
#include <ti/csl/csl_ipcAux.h>
#include <ti/csl/csl_cacheAux.h>

#include "datatype.h"
#include "emif_dsp667x.h"
#include "pll_dsp667x.h"
#include "ddr_dsp667x.h"
#include "uart_dsp6678.h"
#include "bootCfg_dsp667x.h"
#include "bootloader.h"
#include "DDR_NormalTest.h"
#include "EMIF16_NormalTest.h"
#include "flashdrv.h"

#define FLASH_BASE_ADDR         0x70000000

#define DSP_FLASH_DELAY_CNT         		0x5u         /* flashоƬָ��֮�����ʱ */
#define DSP_FLASH_READ16(addr)				(*(volatile UINT16 *)(FLASH_BASE_ADDR + (2*(addr))))
#define BOOT_NOR_FLASH_READ(Offset)     *(volatile UINT16 *)(FLASH_BASE_ADDR + (Offset))
#define APPRUN_LEN				(0x3E0000-0x400)	 //APP���򳤶�=0x400000-0x20000-0x400
#define PART_LEN				(0x04000000) //������С
#define APPDATA_BASEADDR		(0x80000000+0x20000)
#define APPRUN_BASEADDR			(0x82000000+0x20000)


#define  CORE0_BASE_ADDR                0x70020000	//flash�ĵ�0����0x70000000~0x70020000��ŵ��Ƕ���bootloader  ֮�������0x70020000֮����core0Ӧ�ó���
#define  CORE1_BASE_ADDR                0x70a00000
#define  CORE2_BASE_ADDR                0x71400000
#define BOOT_ADDR_BASE			0x2620040
#define BOOT_ADDR(x)			(BOOT_ADDR_BASE + (x*4))
#define BOOT_COMPLETE_ADDR		0x262013C

extern void delay_ms(UINT32 ms_Cnt);
void bootLoaderJump2(UINT32 downAddr);
void read_nor_data(UINT32 spiAddr,UINT32 dstAddr);
void appExtSet(void);






void bootLoaderInit(void)
{
        CSL_chipWriteTSCL(0x0);
        dsp667x_pllInit(NULL);
        dsp667x_emifInit(NULL);
        delay_ms(100);
        dsp667x_ddrInit(NULL);
        dspUartOpen(0);
        //SPI_MAX_FREQ,SPI_MODULE_CLK�������궼Ҫ�޸ģ������Լ���Ƶ�����޸�Ŀǰ����ֲ������
        //spi_claim(SPI_CS0,SPI_MAX_FREQ);

}
/******************************************************************************
 * �� �� ��:bootLoaderJump
 *
 * ����˵��:bootloader��ת��ָ����ַAPP
 * ����˵��:��
 * �������:downAddr �����ַ
 * �������:��
 * �� �� ֵ:�̶�����0
******************************************************************************/

void bootLoaderJump(UINT32 downAddr)
{
	UINT16 *tmpAddr;
	UINT32 tmpLen;
	UINT16* dstAddr;
	UINT32 jumpAddr;
	JUMPFUNC jump;

	tmpAddr = (UINT16*)downAddr;
	jumpAddr = MAKE32(tmpAddr[0],tmpAddr[1]);
	if(jumpAddr==0xffffffff)
	{
		while(1);
	}

	tmpAddr += 2;
	while(1)
	{
		tmpLen = MAKE32(tmpAddr[0],tmpAddr[1]);
		if(tmpLen == 0)
		{
			break;
		}
		if(tmpLen > 0x400000)	//�β�����4M
		{
			while(1);
		}

		tmpAddr += 2;
		dstAddr = (UINT16*)MAKE32(tmpAddr[0],tmpAddr[1]);
		tmpAddr += 2;
		if(tmpLen&0x3)//�еĶ��䳤�Ȳ���4�ı���
        {
			tmpLen += (0x4-tmpLen&0x3);	/*����4�ı���*/
		}
		while(tmpLen)
		{
			*dstAddr++ = *tmpAddr++;
			tmpLen -= 2;
		}
	
	jump = (JUMPFUNC)jumpAddr;
	jump();

	return;
    }
}

UINT32 short2word(UINT32 Addr)
{
	UINT32 temp1,temp2;

	temp1=BOOT_NOR_FLASH_READ(Addr);
	temp2=BOOT_NOR_FLASH_READ(Addr+2);

	temp1=temp1+(temp2<<16);
	return temp1;

}
INLINE void bootInterrupt(UINT8 coreId, UINT32 flag)
{
	dsp667x_bootCfgUnLock();
	CSL_IPC_genGEMInterrupt(coreId,0);//start cores..
	dsp667x_bootCfgLock();
}

INT32 bootCore(UINT8 coreId, UINT32 jumpAddr)
{
	UINT32 bootMagicAddr;
	JUMPFUNC jump;
    volatile UINT32 *reg;

	dsp667x_bootCfgUnLock();
    reg = (UINT32 *)BOOT_ADDR(coreId);
    *reg = jumpAddr;
    if(coreId == 1)
    {
        reg = (UINT32 *)BOOT_COMPLETE_ADDR;
        *reg = (1 << coreId);
    }
	if(coreId > 0)
	{
		bootMagicAddr = COREX_BOOT_MAGIC_ADDR(coreId);
		*(VOLATILE UINT32*)bootMagicAddr = jumpAddr;

		bootInterrupt(coreId, 0x0);//start cores..
		return 0x0;
	}
	jump = (JUMPFUNC)jumpAddr;
	jump();

	return 0;
}

void bootLoaderJump2(UINT32 downAddr)
{
	UINT32 tmpAddr;
	UINT32 tmpLen;
	UINT32* dstAddr;
	UINT32 jumpAddr;
	UINT16 coreid=0;
	UINT32 dspjumpAddr[8]={0};
    INT32 i,j;
	tmpAddr =downAddr;
	coreid=0;


	jumpAddr = short2word(tmpAddr);//*tmpAddr++;
	tmpAddr+=4;
	/*�жϼ���Ӧ�ü����ļ��Ƿ����*/
    if(jumpAddr==0xFFFFFFFF)
    {
       return ;    //���ؾ��񲻴���  ֱ�ӷ���
    }
	while(1)
	{
		tmpLen = short2word(tmpAddr);
	    tmpAddr+=4;
		if(tmpLen == 0)
		{
			dspjumpAddr[coreid]=BOOT_GLOBAL_ADDR(jumpAddr,coreid);
			jumpAddr = short2word(tmpAddr);
	    	tmpAddr+=4;
			tmpLen = short2word(tmpAddr);
	    	tmpAddr+=4;
			coreid++;
			if(jumpAddr==0xffffffff)
			{
						break;
			}
		}
		dstAddr = (UINT32*)(short2word(tmpAddr));
	    tmpAddr+=4;
		dstAddr = (UINT32*)BOOT_GLOBAL_ADDR(dstAddr,coreid);
		//�еĶ��䳤�Ȳ���4�ı���
		if(tmpLen&0x3)
		{
			tmpLen += (0x4-tmpLen&0x3);	/*����4�ı���*/
		}
		while(tmpLen)
		{
			*dstAddr++ =short2word(tmpAddr);
	   		tmpAddr+=4;
			tmpLen -= 4;
		}
	}

	for(i=7;i>=0;i--)
	{
		for(j=0;j<0xfffff;j++);
		bootCore(i, dspjumpAddr[i]);
	}

}

#define BASE_ADDR	(0x80000000)
#define TOTAL_SIZE	(1024*1024*1024/2)
#define RANDSIZE     (1024*1024*32/4)

#define WRITE_DATA_55	0x55555555
#define WRITE_DATA_AA	0xAAAAAAAA
#define BUS_WIDTH		UINT32

void test_ddr(void)
{
	UINT32 i,error;
    UINT32 high,low,compare,val;
	VOLATILE BUS_WIDTH* addr;
	error=0;
    srand(1);
    
	addr = (VOLATILE BUS_WIDTH*)(BASE_ADDR);
	for(i=0x0; i<TOTAL_SIZE; i++)
	{
	    high = rand();
        low = rand();
		*addr++ = (high << 16) | low;
	}
    srand(1);
	addr = (VOLATILE BUS_WIDTH*)(BASE_ADDR);
    for(i = 0x0; i < RANDSIZE;i++)
    {
        high = rand();
        low = rand();
        compare = (high << 16) | low;
        val = *addr++;
        if(compare != val)
        {
            error++;
        }
    }
	if(error)
	{
		printf("ddr test fail!error=%d\r\n",error);
	}
	else
	{
		printf("ddr test ok\r\n");

	}
}

UINT8 pbuf[20] = {0};

void main(void)
{
	if(DNUM == 0)
	{
    	bootLoaderInit();
    //	delay_ms(5000);
   	    PRINT("bootloader up!\r\nV1.0 Build Time:%s,%s\r\n",__DATE__,__TIME__);
        //ddrTest(32,DDR_TESTADDR,DDR_TESTLENTH);
       // test_ddr();
        bootLoaderJump2(APPRUN_PROGRAM_ADDR);
    	//while(1);
    }
}




/******************************************************************************
 * ��  ��  ��:flashDelay
 *
 * ����˵��:flashָ��֮�����ʱ
 * ����˵��:��
 * �������:unDelayCnt ��ʱֵ
 * �������:��
 * ��  ��  ֵ:��
******************************************************************************/

static void flashDelay(UINT32 unDelayCnt)
{
    while (unDelayCnt -- > 0 )
    {
        asm("	   NOP	5");
    }
}

/******************************************************************************
 * ��  ��  ��:flashReadOneWord
 *
 * ����˵��:ָ����ַ��ȡһ��������
 * ����˵��:��
 * �������:addr ��ַ
 * �������:*rData ����ȡ������
 * ��  ��  ֵ:�ɹ�����0��ʧ�ܷ���С��0
******************************************************************************/


static INT32 dspflashReadOneWord(UINT32 addr, UINT16 *rData)
{
	if(rData == NULL)
	{
		return -1;
	}

	flashDelay(DSP_FLASH_DELAY_CNT);

	*rData = DSP_FLASH_READ16(addr);

	return 0;
}

/******************************************************************************
 * ��  ��  ��:dspFlashReadNWords
 *
 * ����˵��:ָ��λ�ö�ȡָ�����ֵ�����
 * ����˵��:��
 * �������:flashOffsetAddr flash�ռ��ַ
 *			*pData ��ȡ��������
 *			lenthWords ���ȣ���λ����
 * �������:��
 * ��  ��  ֵ:�ɹ�����0��ʧ�ܷ���С��0
******************************************************************************/

static INT32 dspFlashReadNWords(UINT32 flashOffsetAddr, UINT16 *pData, UINT32 lenthWords)
{
	UINT16 tempData = 0;
	UINT32 i = 0;
	INT32 status = 0;

	for(i = 0; i < lenthWords; i++)
	{
		status = dspflashReadOneWord(flashOffsetAddr+i, &tempData);
		if(status != 0)
		{
			return -1;
		}

		pData[i] = tempData;
	}

	return 0;
}

/******************************************************************************
 * �� �� ��:dspFlashReadBoot
 *
 * ����˵��:��DSP FLASH�ӿ�
 * ����˵��:��
 * �������:addr FLASH��ַ
 			*pBuf ��ȡ����ָ��
 			bufLen ���ȣ���λ���ֽ�
 * �������:��
 * �� �� ֵ:�ɹ�����0��ʧ�ܷ���С��0
******************************************************************************/

INT32 dspFlashReadBoot(UINT32 addr,UINT8 *pBuf,UINT32 bufLen)
{
	UINT16* tempP = NULL;
	INT32  status = 0;

	if(pBuf == NULL)
	{
		return -1;
	}
	addr = addr/2;
	bufLen = bufLen/2;

	tempP = (UINT16 *)pBuf;
	status = dspFlashReadNWords(addr, tempP, bufLen);

	return status;
}



