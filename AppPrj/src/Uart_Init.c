/*******************************************************************************
*    Copyright Description:   Copyright (C),2022,ORC electronic co.Ltd
*    File Name:               uart_dsp66xx.c
*    Author:                  handsome Yang
*    Version:                 V1.00
*    Date:                    2022.12.29
*    Description:             UART驱动
*    Other:
*    Function List:
*    History:
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <csl_bootcfgAux.h>
#include <csl_cpintc.h>
#include <cslr_uart.h>
#include "Uart_Init.h"
#include "srio_drv.h"
#define MAX_WRITE_LEN  1024
#define UART_BAUTE								(182291666)		/*182291666涓婚1.09375G*/
Uint32 uiCIC_out_num; //first CIC output for UART
#pragma DATA_SECTION(printfBuff, ".UART_DATA_BUF")
static Int8 printfBuff[MAX_WRITE_LEN];
CSL_CPINTCRegs* CIC_Regs;
static Int8 fifoBuffer[MAX_WRITE_LEN];
FIFO8 s_fifo8;
static UART_CMD_FUN_TAB_TYPE cmdFunTab[] = {
//	{"1     :	test DDR3", ddr_test},
//	{"2     :	test emif", emif_test},
	{"3     :   test srio", test_srioDio},
//	{"4     :   get fpga version", get_fpga_version},
//	{"5     :   rs422 test ", rs422_test},
//	{"6     :   spi test", spi_test},
//	{"7     :   clock state get", get_clk_sta},
	{NULL, NULL},
};


/******************************************************************************
 * 函 数 名:fifoOpen
 *
 * 函数说明:FIFO初始化
 * 参数说明:无
 * 输入参数:无
 * 输出参数:无
 * 返 回 值:固定返回0
******************************************************************************/
Int32 fifoOpen(void)
{
	FIFO8* pFifo8 = &s_fifo8;

	pFifo8->fifoSize = 4096;
	pFifo8->pFifoBuf = fifoBuffer;
	pFifo8->pFifoIn  = fifoBuffer;
	pFifo8->pFifoOut = fifoBuffer;

	return 0;
}

/******************************************************************************
 * 函 数 名:fifoWrite
 *
 * 函数说明:往FIFO中丢数，若FIFO满了则覆盖最后一个数
 * 参数说明:无
 * 输入参数:pBuf 待写入数据
 *			wLen 待写入数据长度
 * 输出参数:无
 * 返 回 值:成功返回0，失败返回小于0
******************************************************************************/
Int32 fifoWrite(Int8* pBuf, Uint32 wLen)
{
	Uint32 i;
	FIFO8* pFifo8 = &s_fifo8;

	if(pBuf==NULL)
	{
		return -1;
	}

	for(i = 0; i < wLen; i++)
	{
		pFifo8->pFifoIn[0] = pBuf[i];
		if(((pFifo8->pFifoIn-pFifo8->pFifoBuf+1)%pFifo8->fifoSize) != pFifo8->pFifoOut-pFifo8->pFifoBuf)
		{
			pFifo8->pFifoIn++;
			if(pFifo8->pFifoIn == pFifo8->pFifoBuf+pFifo8->fifoSize)
			{
				pFifo8->pFifoIn = pFifo8->pFifoBuf;
			}
		}
	}

	return 0;
}

/******************************************************************************
 * 函 数 名:fifoRead
 *
 * 函数说明:从FIFO中读取数据
 * 参数说明:无
 * 输入参数:pBuf 读取数据接受区
 *			pRLen8 待读取数据长度
 * 输出参数:pRLen8 实际读取到的数据长度
 * 返 回 值:成功返回0，失败返回小于0
******************************************************************************/
Int32 fifoRead(Int8* pBuf, Uint32* pRLen8)
{
	FIFO8* pFifo8 = &s_fifo8;
	Uint32 len = *pRLen8;
	Uint32 total = 0x0;
	Uint32 i;

	if((pBuf==NULL) || (pRLen8==NULL))
	{
		return -1;
	}

	for(i=0; i<len; i++)
	{
		if(pFifo8->pFifoIn != pFifo8->pFifoOut)
		{
			pBuf[i] = pFifo8->pFifoOut[0];
			pFifo8->pFifoOut++;
			if(pFifo8->pFifoOut == pFifo8->pFifoBuf+pFifo8->fifoSize)
			{
				pFifo8->pFifoOut = pFifo8->pFifoBuf;
			}
			total++;
		}
	}

	*pRLen8 = total;

	return 0;
}

/******************************************************************************
 * 函 数 名:fifoCheck
 *
 * 函数说明:查询FIFO中是否有数据
 * 参数说明:无
 * 输入参数:无
 * 输出参数:无
 * 返 回 值:无数据返回0，有数据返回1
******************************************************************************/
Int32 fifoCheck(void)
{
	FIFO8* pFifo8 = &s_fifo8;

	if(pFifo8->pFifoIn != pFifo8->pFifoOut)
	{
		return 1;
	}

	return 0;
}
Int32 uartCfg(Uint8 ucUartIndex, Uint32 unUartClk, Uint32 unBaudrate)
{
	UART_DSP_REG* pReg;
	Uint32 divisor;
	Uint32 intStatus;
	Uint8 byte;

	/*1. Perform the necessary device pin multiplexing setup (see your device-specific data manual).*/
	switch (ucUartIndex)
	{
		case 0:
			pReg = (UART_DSP_REG*)DSP_UART0_REGS_BASE_ADDR;
			break;
		case 1:
		case 2:
		default:
			break;

	}

	/*2. Set the desired baud rate by writing the appropriate clock divisor values to the divisor latch registers (DLL and DLH).*/
	/*2. Set the desired baud rate by writing the appropriate clock divisor values to the divisor latch registers (DLL and DLH).*/
	pReg->mdr = 0x1;
	divisor = unUartClk/(unBaudrate * 13) + 1;
	pReg->lcr = UART_LCR_DLAB_EABLE;	/*enable access dll and dlh*/
	//divisor = 0x601;
	pReg->dll = divisor&0xFF;
	pReg->dlh = (divisor&0xFF00)>>8;
	pReg->lcr &= ~UART_LCR_DLAB_EABLE;	/*disable access dll and dlh*/


	/*3. If the FIFOs will be used, select the desired trigger level and enable the FIFOs by writing the
		appropriate values to the FIFO control register (FCR). The FIFOEN bit in FCR must be set first,
		before the other bits in FCR are configured.*/
	pReg->iir_fcr = 0x1;//UART_FCR_FIFOEN /*| UART_FCR_RXFIFTL(0) */; 	/*fifoen must be 1 first*/
	while((pReg->iir_fcr&0xc0) != 0xc0)
	{
	}
	pReg->iir_fcr = UART_FCR_RXCLR | UART_FCR_TXCLR |UART_FCR_RXFIFTL(3) |UART_FCR_DMAMODE1;

	//pReg->iir_fcr &= ~UART_FCR_FIFOEN;	/*disable fifo*/
    

	/*4. Choose the desired protocol settings by writing the appropriate values to the line control register (LCR).*/
	pReg->lcr |= UART_LCR_STB_1BIT
			   |UART_LCR_WLS_8BIT
			   |UART_LCR_EPS_ODD
			   |UART_LCR_SP_ENABLE
			   |UART_LCR_BC_ENABLE;
	/*5. If autoflow control is desired, write appropriate values to the modem control register (MCR). Note that
		all UARTs do not support autoflow control, see your device-specific data manual for supported features.*/

	/*6. Choose the desired response to emulation suspend events by configuring the FREE bit and enable the
		UART by setting the UTRST and URRST bits in the power and emulation management register (PWREMU_MGMT).*/
	pReg->pwremu_mgmt = UART_PWREMUMGMT_TXRST_ENABLE | UART_PWREMUMGMT_RXRST_ENABLE | UART_PWREMUMGMT_FREE_MODE;

	/*读空缓冲区中的数据*/
    while ((pReg->lsr & UART_LSR_DR) != 0)
	{
		byte = pReg->rbr_thr;
	}
	/*使能接收中断*/

	pReg->ier |= (Uint32)1<<0;

	intStatus = pReg->iir_fcr;
	if ((intStatus&0x1) == 0x1) /*no interrupts pending*/
	{
		return 0;
	}
	switch((intStatus>>0x1)&0x7)
	{
		case 1: 	/*Transmitter holding register empty (priority 3)*/
			pReg->rbr_thr = byte;	/*write thr clean this interrupt*/
			break;
		case 2: 	/*Receiver data available (priority 2)*/
			byte = (Uint8)(pReg->rbr_thr);	/*non fifo mode read rbr reg clean interrupt , fifo mode low trigger level clean interrupt*/
			break;
		case 3: 	/*Receiver line status (priority 1, highest)*/
			byte = pReg->lsr; /*read it clean thi interrupt*/
			break;
		case 6: 	/*Character timeout indication (priority 2)*/
			byte = pReg->rbr_thr;
			break;

		case 0: 	/*reserver*/
		case 4:
		case 5:
		case 7:
		default:
			break;
	}
}
/**********************************************以下是UART驱动部分************************************************/
/******************************************************************************
 * 函 数 名:dspUartInit
 *
 * 函数说明:UART底层初始化
 * 参数说明:无
 * 输入参数:bps 波特率9600~3000000
 * 输出参数:无
 * 返 回 值:成功返回0，失败返回小于0
******************************************************************************/
Int32 dspUartInit(Uint32 bps)
{
	Uint32 divisor;
	float  divisorF = 0.0;
	Uint32 intStatus;
	Uint8 byte;
	UART_DSP_REG* pReg;

	pReg = (UART_DSP_REG*)DSP_UART0_REGS_BASE_ADDR;

	/*Set the desired baud rate by writing the appropriate clock divisor values to the divisor latch registers (DLL and DLH)*/
	pReg->mdr = 0x0;	//x16

	divisorF = (float)(UART_BAUTE/(bps * 16.0));
	divisor = UART_BAUTE/(bps * 16);
	divisorF = divisorF * 1.0 - divisor;
	if(divisorF > 0.5)
	{
		divisor = divisor + 1;
	}

	pReg->lcr = UART_LCR_DLAB_EABLE;/*enable access dll and dlh*/
	pReg->dll = divisor&0xFF;
	pReg->dlh = (divisor&0xFF00)>>8;
	pReg->lcr &= ~UART_LCR_DLAB_EABLE;/*disable access dll and dlh*/

	/*If the FIFOs will be used, select the desired trigger level and enable the FIFOs by writing the
	  appropriate values to the FIFO control register (FCR). The FIFOEN bit in FCR must be set first,
	  before the other bits in FCR are configured.*/
	pReg->iir_fcr = UART_FCR_FIFOEN;
	while((pReg->iir_fcr&0xc0) != 0xc0)
	{
	}
	pReg->iir_fcr = UART_FCR_RXCLR|UART_FCR_TXCLR|UART_FCR_RXFIFTL(3)|UART_FCR_DMAMODE1;

	//pReg->mcr |= 0x10;	//内部自环使能
	/*Choose the desired protocol settings by writing the appropriate values to the line control register (LCR).*/
	pReg->lcr |= UART_LCR_STB_1BIT
			   	|UART_LCR_WLS_8BIT
			   	|UART_LCR_EPS_ODD
			   	|UART_LCR_SP_ENABLE
			   	|UART_LCR_BC_ENABLE;
	pReg->pwremu_mgmt = UART_PWREMUMGMT_TXRST_ENABLE|UART_PWREMUMGMT_RXRST_ENABLE|UART_PWREMUMGMT_FREE_MODE;

	/*读空缓冲区中的数据*/
    while((pReg->lsr & UART_LSR_DR) != 0)
	{
		byte = pReg->rbr_thr;
	}

	/*使能接收中断*/
	pReg->ier |= (Uint32)1<<0;

	/*清中断*/
	intStatus = pReg->iir_fcr;
	if((intStatus&0x1) == 0x1) /*no interrupts pending*/
	{
		return 1;
	}
	switch((intStatus>>0x1)&0x7)
	{
		case 1: 	/*Transmitter holding register empty (priority 3)*/
			pReg->rbr_thr = byte;	/*write thr clean this interrupt*/
			break;
		case 2: 	/*Receiver data available (priority 2)*/
			byte = (Uint8)(pReg->rbr_thr);	/*non fifo mode read rbr reg clean interrupt , fifo mode low trigger level clean interrupt*/
			break;
		case 3: 	/*Receiver line status (priority 1, highest)*/
			byte = pReg->lsr; /*read it clean thi interrupt*/
			break;
		case 6: 	/*Character timeout indication (priority 2)*/
			byte = pReg->rbr_thr;
			break;

		case 0: 	/*reserver*/
		case 4:
		case 5:
		case 7:
		default:
			break;
	}

	return 0x0;
}

/******************************************************************************
 * 函 数 名:dspUartSend
 *
 * 函数说明:UART查询发送
 * 参数说明:无
 * 输入参数:pByte 待发送数据
 *			len 待发送数据长度
 * 输出参数:无
 * 返 回 值:成功返回0，失败返回小于0
******************************************************************************/
Int32 dspUartSend(Int8* pByte, Uint32 len)
{
	UART_DSP_REG* pReg = (UART_DSP_REG*)DSP_UART0_REGS_BASE_ADDR;;
	Uint32 txEmpty;

	txEmpty = UART_LSR_TEMT | UART_LSR_THRE;
	while(len)
	{
		while(txEmpty != (pReg->lsr & txEmpty));
		pReg->rbr_thr = *pByte++;
		len--;
	}

	return 0;
}

/******************************************************************************
 * 函 数 名:dspUartRece
 *
 * 函数说明:UART查询接收
 * 参数说明:无
 * 输入参数:pByte 数据接收缓存
 *			pLen 待接收数据
 * 输出参数:pLen 实际接收数据长度
 * 返 回 值:成功返回0，失败返回小于0
******************************************************************************/
Int32 dspUartRece(Uint8 channel, Uint8* pByte, Uint32* pLen)
{
	UART_DSP_REG* pReg;
	Uint32 len;
	switch (channel)
	{
		case 0:
			pReg = (UART_DSP_REG*)DSP_UART0_REGS_BASE_ADDR;
			break;
		case 1:
		case 2:
		default:
			return -1;
	}

	len = 0x0;

	while(1)
	{

		while ((pReg->lsr & UART_LSR_DR) == 0);
		*pByte++ = (Uint8)(pReg->rbr_thr);
		len++;
		if(len >= *pLen)
		{
			break;
		}
	}

	*pLen = len;
	return 0;
}

/******************************************************************************
 * 函 数 名:dspUartIsr
 *
 * 函数说明:UART接收中断
 * 参数说明:无
 * 输入参数:pByte 数据接收缓存
 *			pLen 待接收数据
 * 输出参数:pLen 实际接收数据长度
 * 返 回 值:成功返回0，失败返回小于0
******************************************************************************/
interrupt void dspUartIsr()
{
	UART_DSP_REG* pReg;
	Uint32 intStatus;
	Int8 byte;
	Uint32 eventFlag;
    CSL_CPINTCRegs* CIC_Regs = gpCIC0_regs;
    CIC_Regs->HINT_ENABLE_CLR_INDEX_REG = 32;
    if(CIC_Regs->RAW_STATUS_REG[CSL_INTC0_UARTINT>>5])

	{
	    pReg = (UART_DSP_REG*)DSP_UART0_REGS_BASE_ADDR;

    	intStatus = pReg->iir_fcr;
    	if((intStatus&0x1) == 0x1)	/*no interrupts pending*/
    	{
    		return;
    	}

    	switch((intStatus>>0x1)&0x7)
    	{
    		case 1:		/*Transmitter holding register empty (priority 3)*/
    			/*发送中断*/
    			pReg->rbr_thr = 0;	/*write thr clean this interrupt*/
    			break;

    		case 3: 	/*Receiver line status (priority 1, highest)  read it clean thi interrupt*/
    		case 6: 	/*Character timeout indication (priority 2)*/
    		case 2:		/*Receiver data available (priority 2)*/
    			/*接收中断*/
    			//while(pReg->lsr&0x1)	//data is ready
    			{
    				byte = (Int8)(pReg->rbr_thr);	/*non fifo mode read rbr reg clean interrupt , fifo mode low trigger level clean interrupt*/
    				//pReg->rbr_thr = byte;
    				fifoWrite((Int8*)&byte, 1);
                    
    			}
    			break;

    		case 0:		/*reserver*/
    		case 4:
    		case 5:
    		case 7:
    		default:
    			break;
	    }

        CIC_Regs->STATUS_CLR_INDEX_REG = CSL_INTC0_UARTINT; //no os need clr stutas
        CIC_Regs->HINT_ENABLE_SET_INDEX_REG = 32;
    }
}

/******************************************************************************
 * 函 数 名:uartInit
 *
 * 函数说明:6678 UART初始化
 * 参数说明:无
 * 输入参数:bps 波特率
 * 输出参数:无
 * 返 回 值:固定返回0
******************************************************************************/
Int32 uartInit(Uint32 bps)
{

	fifoOpen();
	//uartCfg(0,UART_BAUTE,115200);
     //中断注册
//    cicChannelIsrRegisterC(EVENT_CIC0_OUT32_0_11_N_CIC1_OUT32_0_11_N_4,148, (EVENT_ISR_FUNC)dspUartIsr, 0,1);
//    /*  USART  INT10*/
//    eventMap(EVENT_CIC0_OUT32_0_11_N_CIC1_OUT32_0_11_N_4,10);
	KeyStone_UART_Interrupts_Init();
	return 0;
}

/******************************************************************************
 * 函 数 名:uartWrite
 *
 * 函数说明:UART发送数据
 * 参数说明:无
 * 输入参数:data 待发送数据
 			nbytes 待发送数据长度
 * 输出参数:无
 * 返 回 值:大于0时表示发送的实际长度，等于0表示无数据可发送，-1表示发送错误
******************************************************************************/
Int32 uartWrite(Uint8 *data, Uint16 nbytes)
{
	dspUartSend((void *)data, nbytes);

	return nbytes;
}

/******************************************************************************
 * 函 数 名:uartRead
 *
 * 函数说明:UART接收数据
 * 参数说明:无
 * 输入参数:data 接收数据缓存
 			nbytes 期望接收的数据长度
 * 输出参数:无
 * 返 回 值:大于0时表示接收的实际长度，等于0表示无数据可接收，-1表示接收错误
******************************************************************************/
Int32 uartRead(Uint8 *data, Uint16 nbytes)
{
	Uint16 i = 0;
	Uint16 readCnt = 0;
	Uint32 status = 0;
	Uint32 readLen = 1;

	for(i = 0; i < nbytes; i++)
	{
		status = fifoCheck();
		if(status)
		{
			fifoRead((void *)&(data[i]), &readLen);
			readCnt++;
		}
	}

	return readCnt;
}

/******************************************************************************
 * 函 数 名:Uartprintf
 *
 * 函数说明:UART打印函数
 * 参数说明:无
 * 输入参数:fmt 打印字符
 * 输出参数:无
 * 返 回 值:wu
******************************************************************************/
void uartprintf(const char *fmt, ... )
{
    va_list arg_ptr;
	Uint32	length = 0;

    if (strlen(fmt) > MAX_WRITE_LEN)
    {
    	return;
    }

    memset(printfBuff,0,MAX_WRITE_LEN);

    va_start(arg_ptr, fmt);
    length = vsprintf((char *)printfBuff, fmt, arg_ptr);
    va_end(arg_ptr);

    uartWrite((void *)printfBuff,length);
}

void KeyStone_UART_Interrupts_Init(void)
{

    CSL_CPINTCRegs* CIC_Regs;


	if(DNUM<4) //for core 0, 1, 2, 3
		CIC_Regs= gpCIC0_regs;

	/* Disable Global host interrupts. */
	CIC_Regs->GLOBAL_ENABLE_HINT_REG= 0;

	/* Configure no nesting support in the CPINTC Module. */
	CIC_Regs->CONTROL_REG= ((CIC_Regs->CONTROL_REG&
		~CSL_CPINTC_CONTROL_REG_NEST_MODE_MASK)|
		(CPINTC_NO_NESTING<<CSL_CPINTC_CONTROL_REG_NEST_MODE_SHIFT));

	/*map UART ERR INT, RX EVT, and EDMA CC2 GINT to CIC out*/
	KeyStone_CIC_event_map(CIC_Regs, CSL_INTC0_UARTINT, 32);
	/* Enable Global host interrupts. */
	CIC_Regs->GLOBAL_ENABLE_HINT_REG= 1;

	gpCGEM_regs->INTMUX2 =
		(CSL_GEM_INTC0_OUT_32_PLUS_11_MUL_N_OR_INTC0_OUT_32_PLUS_11_MUL_N_MINUS_4<<CSL_CGEM_INTMUX2_INTSEL10_SHIFT);

	/* enable INT10 */
	CPU_interrupt_enable(1<<10);
}
#define UART_RX_BUF_SIZE      64
typedef struct UART_RX_BUF_TYPE_t{
	Uint8 buf[UART_RX_BUF_SIZE];  //接收数据
	Uint8 rx_cnt;                 //接收数据的个数
}UART_RX_BUF_TYPE;


void DebugSerialDatIdle(void)
{
	Uint8 i, len;
	Uint8 dat;
	Uint8 cmdIdleFlag;
	Uint8 *inBuf;
	static UART_RX_BUF_TYPE DEBUG_RX_Buff = {{0},0};

	if(uartRead(&dat, 1) == 1)
	{
		cmdIdleFlag = 0;
		DEBUG_RX_Buff.buf[DEBUG_RX_Buff.rx_cnt] = dat;
		DEBUG_RX_Buff.rx_cnt++;

		if(dat == '\n' || dat == '\r')
		{
			for(i = 0; NULL != cmdFunTab[i].cmd; i++)
			{
				    len = strlen(cmdFunTab[i].cmd);
					if(0 == strncmp(cmdFunTab[i].cmd, (char *)DEBUG_RX_Buff.buf, len))
					{
						    inBuf = DEBUG_RX_Buff.buf+len;
							if(NULL != cmdFunTab[i].fun)
							{
									//cmdFunTab[i].fun();
									cmdIdleFlag = 1;
							}
					}
			}
			if(0 == cmdIdleFlag)
			{
				printf("cmd err\r\n");
			}
			memset(DEBUG_RX_Buff.buf, 0, DEBUG_RX_Buff.rx_cnt);
			DEBUG_RX_Buff.rx_cnt = 0;
		}
	}
}
