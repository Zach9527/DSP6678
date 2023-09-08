
/*******************************************************************************
*    Copyright Description:   Copyright (C),2022,ORC electronic co.Ltd
*    File Name:               DDR_NormalTest.c
*    Author:                  handsome Yang
*    Version:                 V1。00
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
 * 函 数 名:ddrDataNormalTest
 *
 * 函数说明:DDR数据线测试
 * 输入参数:dataBit:DDR数据位宽
 *			offAddr:DDR测试偏移地址
 *			testLen:DDR测试长度
 * 输出参数:无
 * 返 回 值:0:数据线测试成功;
 *			-1:参数错误;
 *			-2:数据线走1错误；
 *			-3:数据线走0错误。
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

	/*1.数据线走1 :对测试地址offAddr进行读写校验*/

	if(dataBit == 16)
	{
		for(i = 0; i < dataBit; i++)
		{
			wtData16 = (1 << i) & 0xFFFFu;

			/*1.向测试地址写数*/
			DDR_WRITE16(offAddr, wtData16);

			/*2.地址读数*/
			rdData16 = DDR_READ16(offAddr);

			/*3.数据比较*/
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

			/*1.向测试地址写数*/
			DDR_WRITE32(offAddr, wtData32);

			/*2.地址读数*/
			rdData32 = DDR_READ32(offAddr);

			/*3.数据比较*/
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

			/*1.向测试地址写数*/
			DDR_WRITE64(offAddr, wtData64);

			/*2.地址读数*/
			rdData64 = DDR_READ64(offAddr);

			/*3.数据比较*/
			if(rdData64 != wtData64)
			{
				errCnt++;
			}
		}
	}

	/*打印错误数据线*/
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

			/*1.向测试地址写数*/
			DDR_WRITE16(offAddr, wtData16);

			/*2.地址读数*/
			rdData16 = DDR_READ16(offAddr);

			/*3.数据比较*/
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

			/*1.向测试地址写数*/
			DDR_WRITE32(offAddr, wtData32);

			/*2.地址读数*/
			rdData32 = DDR_READ32(offAddr);

			/*3.数据比较*/
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

			/*1.向测试地址写数*/
			DDR_WRITE64(offAddr, wtData64);

			/*2.地址读数*/
			rdData64 = DDR_READ64(offAddr);

			/*3.数据比较*/
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
 * 函 数 名:ddrAddrNormalTest
 *
 * 函数说明:DDR地址线测试
 * 输入参数:offAddr:DDR 偏移地址
 *			testLen:DDR 测试偏移地址
 * 输出参数:无
 * 返 回 值:0 :地址线测试成功;
 *			-1:地址线走1错误；
 *			-2:地址线走0错误。
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

	/*获得地址线数量:地址线不足会补齐*/
	while(temp < testLen)
	{
		temp = 1 << addrCnt;
		if(temp >= testLen)
		{
			break;
		}
		addrCnt++;
	}

	tempnum = (1 << addrCnt) - 1;		//测试地址数

	/*1.地址线走1:测试使用递增数(写完再读)*/
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


	/*2.地址线走0:测试使用递增数(写完再读)*/
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
 * 函 数 名:ddrStorageNormalTest
 *
 * 函数说明:DDR存储空间测试
 * 输入参数:offAddr:DDR 偏移地址
 *			testLen:DDR 空间测试长度
 * 输出参数:无
 * 返 回 值:0 :DDR存储空间测试成功;
 *			-1:DDR存储空间测试成功；
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

	/*1.将存储空间划分为相同的两部分，即part1以及part2，进行数据测试*/
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
 * 函 数 名:ddrTest
 *
 * 函数说明:DDR测试
 * 输入参数:ddrDataBit:数据位宽
 *			ddrOffAddr:DDR测试偏移地址
 *			ddrTestLen:DDR测试长度
 * 输出参数:无
 * 返 回 值:0 :DDR 测试成功;
 *			-1:DDR 参数错误;
 *			-2:DDR 数据线测试异常;
 *			-3:DDR 地址线测试异常；
 *			-4:DDR 存储空间测试异常。
******************************************************************************/
INT32 ddrTest(UINT32 ddrDataBit, UINT32	ddrOffAddr, UINT32 ddrTestLen)
{
	INT32 testStatus = 0;

	if((ddrDataBit != 16) && (ddrDataBit != 32) && (ddrDataBit != 64))
	{
		return -1;
	}

	/*1.对DDR数据线进行测试*/
	testStatus = ddrDataNormalTest(ddrDataBit, ddrOffAddr, ddrTestLen);
	if(testStatus != 0)
	{
		return -2;
	}

	/*2.对地址线进行测试*/
	testStatus = ddrAddrNormalTest(ddrOffAddr, ddrTestLen);
	if(testStatus != 0)
	{
		return -3;
	}

	/*3.对DDR待测试存储空间进行测试*/
	testStatus = ddrStorageNormalTest(ddrOffAddr, ddrTestLen);
	if(testStatus != 0)
	{
		return -4;
	}

	return 0;
}






