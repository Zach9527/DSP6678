
/*******************************************************************************
*    Copyright Description:   Copyright (C),2022,ORC electronic co.Ltd
*    File Name:               EMIF16_NormalTest.c
*    Author:                  handsome Yang
*    Version:                 V1。00
*    Date:                    2022-12-27
*    Description:
*    Other:
*    Function List:
*    History:
*******************************************************************************/
#include <dataType.h>
#include <stdio.h>

#define EMIF_ADDR                            0x74000000
#define EMIF_DATA_BUS_TEST_ADDR              0x01
#define EMIF_TEST_WRITE16(addr,data)         (*(volatile UINT16 *)(EMIF_ADDR + (addr)*2)) = (data)
#define EMIF_TEST_READ16(addr)         		 (*(volatile UINT16 *)(EMIF_ADDR + (addr)*2))

/******************************************************************************
 * 函 数 名:test_emifDataBus
 *
 * 函数说明:EMIF数据线测试
 * 参数说明:无
 * 输入参数:无
 * 输出参数:无
 * 返 回 值:无
******************************************************************************/
static INT32 test_emifDataBus(void)
{
	UINT16 i = 0;
	UINT16 writeData = 0;
	UINT16 readData = 0;
	UINT16 unData[12] = {0x5555, 0xAAAA, 0x3333, 0xCCCC,
                         0x0F0F, 0xF0F0, 0x00FF, 0xFF00,
                         0x0000, 0xFFFF, 0x5a5a, 0xa5a5};

	/*数据线走1测试*/
	for(i = 0; i < 16; i++)
	{
		writeData = 1 << i;
		EMIF_TEST_WRITE16(EMIF_DATA_BUS_TEST_ADDR, writeData);
		readData = EMIF_TEST_READ16(EMIF_DATA_BUS_TEST_ADDR);

		if(writeData != readData)
		{
			printf("write data = 0x%x, read data = 0x%x\r\n", writeData, readData);
			return -1;
		}
	}

	/*数据线特殊值测试*/
	for(i = 0; i < 12; i++)
	{
		writeData = unData[i];
		EMIF_TEST_WRITE16(EMIF_DATA_BUS_TEST_ADDR, writeData);
		readData = EMIF_TEST_READ16(EMIF_DATA_BUS_TEST_ADDR);

		if(writeData != readData)
		{
			printf("write data = 0x%x, read data = 0x%x\r\n", writeData, readData);
			return -1;
		}
	}

	return 0;
}

/******************************************************************************
 * 函 数 名:test_emifAddrBus
 *
 * 函数说明:EMIF地址线测试
 * 参数说明:无
 * 输入参数:无
 * 输出参数:无
 * 返 回 值:无
******************************************************************************/
static INT32 test_emifAddrBus(void)
{
	UINT16 i = 0;
	UINT32 writeAddr = 0;
	UINT16 readData = 0;

	/*地址线走1测试*/
	for(i = 0; i < 24; i++)
	{
		writeAddr = 1 << i;
		EMIF_TEST_WRITE16(writeAddr, 0xCCDD);
	}

	for(i = 0; i < 24; i++)
	{
		writeAddr = 1 << i;
		readData = EMIF_TEST_READ16(writeAddr);

		if(readData != 0xCCDD)
		{
			printf("write data = 0xCCDD, read data = 0x%x\r\n", readData);
			return -1;
		}
	}

	return 0;
}

/******************************************************************************
 * 函 数 名:test_emif
 *
 * 函数说明:EMIF测试
 * 参数说明:无
 * 输入参数:无
 * 输出参数:无
 * 返 回 值:无
******************************************************************************/
void test_emif(void)
{
	INT32 temp = 0;

    temp = test_emifDataBus();
    if(temp == 0)
    {
        printf("EMIF数据总线测试是否通过(Y/N):Y\r\n");
    }
    else
    {
        printf("EMIF数据总线测试是否通过(Y/N):N\r\n");
    }

    temp = test_emifAddrBus();
    if (temp == 0)
    {
        printf("EMIF地址总线测试是否通过(Y/N):Y\r\n");
    }
    else
    {
        printf("EMIF地址总线测试是否通过(Y/N):N\r\n");
    }

	return;
}


