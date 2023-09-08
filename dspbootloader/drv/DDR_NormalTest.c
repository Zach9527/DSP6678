
/*******************************************************************************
*    Copyright Description:   Copyright (C),2022,ORC electronic co.Ltd
*    File Name:               DDR_NormalTest.c
*    Author:                  handsome Yang
*    Version:                 V1��00
*    Date:                    2022-12-27
*    Description:
*    Other:
*    Function List:
*    History:
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "DDR_NormalTest.h"
#include "dataType.h"

/******************************************************************************
 * �� �� ��:ddrDataNormalTest
 *
 * ����˵��:DDR�����߲���
 * �������:dataBit:DDR����λ��
 *			offAddr:DDR����ƫ�Ƶ�ַ
 *			testLen:DDR���Գ���
 * �������:��
 * �� �� ֵ:0:�����߲��Գɹ�;
 *			-1:��������;
 *			-2:��������1����
 *			-3:��������0����
******************************************************************************/
static INT32 ddrDataNormalTest(UINT32 dataBit, UINT32	offAddr, UINT32 testLen)
{
	UINT16	errCnt = 0;
	UINT32	i = 0;
	UINT16	wtData16 = 0;
	UINT16	rdData16 = 0;
	UINT32	wtData32 = 0;
	UINT32	rdData32 = 0;
	UINT64	wtData64 = 0;
	UINT64	rdData64 = 0;

	/*1.��������1 :�Բ��Ե�ַoffAddr���ж�дУ��*/

	if(dataBit == 16)
	{
		for(i = 0; i < dataBit; i++)
		{
			wtData16 = (1 << i) & 0xFFFFu;

			/*1.����Ե�ַд��*/
			DDR_WRITE16(offAddr, wtData16);

			/*2.��ַ����*/
			rdData16 = DDR_READ16(offAddr);

			/*3.���ݱȽ�*/
			if(rdData16 != wtData16)
			{
				errCnt++;
			}
		}
	}
	else if(dataBit == 32)
	{
		for(i = 0; i < dataBit; i++)
		{
			wtData32 = (1 << i) & 0xFFFFFFFFu;

			/*1.����Ե�ַд��*/
			DDR_WRITE32(offAddr, wtData32);

			/*2.��ַ����*/
			rdData32 = DDR_READ32(offAddr);

			/*3.���ݱȽ�*/
			if(rdData32 != wtData32)
			{
				errCnt++;
			}
		}
	}
	else	//databit == 64
	{
		for(i = 0; i < dataBit; i++)
		{
			wtData64 = (1 << i) & 0xFFFFFFFFFFFFFFFFu;

			/*1.����Ե�ַд��*/
			DDR_WRITE64(offAddr, wtData64);

			/*2.��ַ����*/
			rdData64 = DDR_READ64(offAddr);

			/*3.���ݱȽ�*/
			if(rdData64 != wtData64)
			{
				errCnt++;
			}
		}
	}

	/*��ӡ����������*/
	if(errCnt != 0)
	{
	
        printf("ddr data line err:%d\r\n",errCnt);
		return -2;
	}


	if(dataBit == 16)
	{
		for(i = 0; i < dataBit; i++)
		{
			wtData16 = (~(1 << i)) & 0xFFFFu;

			/*1.����Ե�ַд��*/
			DDR_WRITE16(offAddr, wtData16);

			/*2.��ַ����*/
			rdData16 = DDR_READ16(offAddr);

			/*3.���ݱȽ�*/
			if(rdData16 != wtData16)
			{
				errCnt++;
			}
		}
	}
	else if(dataBit == 32)
	{
		for(i = 0; i < dataBit; i++)
		{
			wtData32 = (~(1 << i)) & 0xFFFFFFFFu;

			/*1.����Ե�ַд��*/
			DDR_WRITE32(offAddr, wtData32);

			/*2.��ַ����*/
			rdData32 = DDR_READ32(offAddr);

			/*3.���ݱȽ�*/
			if(rdData32 != wtData32)
			{
				errCnt++;
			}
		}
	}
	else	//databit == 64
	{
		for(i = 0; i < dataBit; i++)
		{
			wtData64 = (~(1 << i)) & 0xFFFFFFFFFFFFFFFFu;

			/*1.����Ե�ַд��*/
			DDR_WRITE64(offAddr, wtData64);

			/*2.��ַ����*/
			rdData64 = DDR_READ64(offAddr);

			/*3.���ݱȽ�*/
			if(rdData64 != wtData64)
			{
				errCnt++;
			}
		}
	}

	if(errCnt != 0)
	{
	
        printf("ddr data line err:%d\r\n",errCnt);
		return -3;
	}

	return 0;
}

/******************************************************************************
 * �� �� ��:ddrAddrNormalTest
 *
 * ����˵��:DDR��ַ�߲���
 * �������:offAddr:DDR ƫ�Ƶ�ַ
 *			testLen:DDR ����ƫ�Ƶ�ַ
 * �������:��
 * �� �� ֵ:0 :��ַ�߲��Գɹ�;
 *			-1:��ַ����1����
 *			-2:��ַ����0����
******************************************************************************/
static INT32 ddrAddrNormalTest(UINT32 offAddr, UINT32 testLen)
{
	UINT8	i = 0;
	UINT8	rdaddr8 = 0;
	UINT8	errCnt = 0;
	UINT32	tempnum = 0;
	UINT32 	wtaddr32 = 0;
	UINT32	addrCnt = 0;
	UINT32	temp = 0;

	/*��õ�ַ������:��ַ�߲���Ჹ��*/
	while(temp < testLen)
	{
		temp = 1 << addrCnt;
		if(temp >= testLen)
		{
			break;
		}
		addrCnt++;
	}

	tempnum = (1 << addrCnt) - 1;		//���Ե�ַ��

	/*1.��ַ����1:����ʹ�õ�����(д���ٶ�)*/
	for(i = 0; i < addrCnt; i++)
	{
		wtaddr32 = offAddr + (1 << i);
		DDR_WRITE8(wtaddr32, i);
	}

	for(i = 0; i < addrCnt; i++)
	{
		wtaddr32 = offAddr + (1 << i);
		rdaddr8= DDR_READ8(wtaddr32);

		if( rdaddr8 != i )
		{
			errCnt++;
		}
	}

	if(errCnt != 0)
	{
		return -1;
	}


	/*2.��ַ����0:����ʹ�õ�����(д���ٶ�)*/
	for(i = 0; i < addrCnt; i++)
	{
		wtaddr32 = offAddr + ((~(1 << i)) & tempnum);
		DDR_WRITE8(wtaddr32, i);
	}

	for(i = 0; i < addrCnt; i++)
	{
		wtaddr32 = offAddr + ((~(1 << i)) & tempnum);
		rdaddr8 = DDR_READ8(wtaddr32);

		if( rdaddr8 != i )
		{
			errCnt++;
		}
	}

	if(errCnt != 0)
	{
		return -2;
	}

	return 0;
}

/******************************************************************************
 * �� �� ��:ddrStorageNormalTest
 *
 * ����˵��:DDR�洢�ռ����
 * �������:offAddr:DDR ƫ�Ƶ�ַ
 *			testLen:DDR �ռ���Գ���
 * �������:��
 * �� �� ֵ:0 :DDR�洢�ռ���Գɹ�;
 *			-1:DDR�洢�ռ���Գɹ���
******************************************************************************/
static INT32 ddrStorageNormalTest(UINT32 offAddr, UINT32 testLen)
{
	UINT8 	wrtData8 = 0;
	UINT8	errCnt = 0;
	UINT8	part1Data = 0;
	UINT8	part2Data = 0;
	UINT32 	part1Addr = 0;
	UINT32 	part2Addr = 0;
	UINT32  i = 0;

	part1Addr = offAddr;
	part2Addr = part1Addr + (testLen / 2);

	/*1.���洢�ռ仮��Ϊ��ͬ�������֣���part1�Լ�part2���������ݲ���*/
	for(i = 0; i < testLen / 2; i++)
	{
		wrtData8 = 0xFF & rand();
		DDR_WRITE8(part1Addr + i, wrtData8);
		DDR_WRITE8(part2Addr + i, wrtData8);
	}

	for(i = 0; i < testLen / 2; i++)
	{
		part1Data = DDR_READ8(part1Addr + i);
		part2Data = DDR_READ8(part2Addr + i);
		if(part1Data != part2Data)
		{
			errCnt++;
		}
	}

	if(errCnt != 0)
	{
		return -1;
	}

	return 0;
}

/******************************************************************************
 * �� �� ��:ddrTest
 *
 * ����˵��:DDR����
 * �������:ddrDataBit:����λ��
 *			ddrOffAddr:DDR����ƫ�Ƶ�ַ
 *			ddrTestLen:DDR���Գ���
 * �������:��
 * �� �� ֵ:0 :DDR ���Գɹ�;
 *			-1:DDR ��������;
 *			-2:DDR �����߲����쳣;
 *			-3:DDR ��ַ�߲����쳣��
 *			-4:DDR �洢�ռ�����쳣��
******************************************************************************/
INT32 ddrTest(UINT32 ddrDataBit, UINT32	ddrOffAddr, UINT32 ddrTestLen)
{
	INT32 testStatus = 0;

	if((ddrDataBit != 16) && (ddrDataBit != 32) && (ddrDataBit != 64))
	{
		return -1;
	}

	/*1.��DDR�����߽��в���*/
	testStatus = ddrDataNormalTest(ddrDataBit, ddrOffAddr, ddrTestLen);
	if(testStatus != 0)
	{
		return -2;
	}

	/*2.�Ե�ַ�߽��в���*/
	testStatus = ddrAddrNormalTest(ddrOffAddr, ddrTestLen);
	if(testStatus != 0)
	{
		return -3;
	}

	/*3.��DDR�����Դ洢�ռ���в���*/
	testStatus = ddrStorageNormalTest(ddrOffAddr, ddrTestLen);
	if(testStatus != 0)
	{
		return -4;
	}

	return 0;
}






