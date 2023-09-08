
/* includes */ 
#include <c6x.h>

#include "common.h"
#include "datatype.h"
#include "delay.h"
#include "dsp667x.h"
#include "uart_dsp6678.h"
#include "irq_dsp667x.h"
#include "cic_dsp667x.h"

/* defines */ 
#define DSP_UART0_REGS_BASE_ADDR				(0x02540000)
#define UART_BAUTE								(182291666)		/*182291666涓婚1.09375G*/

#define IRQRES_DSPUART_FIRST					IRQRES_RS232_UART0
#define MAX_WRITE_LEN  4096

#pragma DATA_SECTION(printfBuff, ".UART_DATA_BUF")
static INT8 printfBuff[MAX_WRITE_LEN];

#define UART_PWREMUMGMT_TXRST_ENABLE            ((UINT32)1<<14)
#define UART_PWREMUMGMT_RXRST_ENABLE            ((UINT32)1<<13)
#define UART_PWREMUMGMT_FREE_MODE               ((UINT32)1<<0)

#define UART_LCR_WLS_8BIT			((UINT32)3<<0)		/*word length 8bit*/
#define UART_LCR_STB_1BIT			((UINT32)0<<2)		/*stop bit 1bit*/
#define UART_LCR_PEN_ENABLE			((UINT32)1<<3)		/*parity enable*/
#define UART_LCR_EPS_ODD			((UINT32)0<<4)		/*odd parith*/
#define UART_LCR_EPS_EVEN			((UINT32)1<<4)		/*even parith*/
#define UART_LCR_SP_ENABLE			((UINT32)1<<5)		/*stick parith is enable*/
#define UART_LCR_BC_ENABLE			((UINT32)1<<5)		/*break contrl enable*/
#define UART_LCR_DLAB_EABLE			((UINT32)1<<7)		/*Allows access t*/

#define UART_FCR_FIFOEN         	((UINT32)1<<0)		/*FIFO enable*/
#define UART_FCR_RXCLR          	((UINT32)1<<1)		/*RX CLR*/
#define UART_FCR_TXCLR          	((UINT32)1<<2)		/*TX CLR*/
#define UART_FCR_RXFIFTL(level)     (((UINT32)(level)&0x3)<<6)
#define UART_FCR_DMAMODE1		((UINT32)1<<3)

#define UART_LSR_TEMT           ((UINT32)1<<6)
#define UART_LSR_THRE           ((UINT32)1<<5)
#define UART_LSR_DR             ((UINT32)1<<0)


#define UART_ENABLE_RECE_IRQ_CMD			0x0
#define UART_ENABLE_SEND_IRQ_CMD			0x1

/* typedefs */  
typedef struct __uart_dsp_reg                      
{                                             
	VOLATILE UINT32 rbr_thr; 		/*00h*/ 
	VOLATILE UINT32 ier; 			/*04h*/
	VOLATILE UINT32 iir_fcr; 		/*08h*/	 
	VOLATILE UINT32 lcr;        		/*0Ch*/
	VOLATILE UINT32 mcr;        		/*10h*/
	VOLATILE UINT32 lsr;          	/*14h*/
	VOLATILE UINT32 msr;          	/*18h*/
	VOLATILE UINT32 scr;          	/*1Ch*/
	VOLATILE UINT32 dll;          	/*20h*/
	VOLATILE UINT32 dlh;        	  	/*24h*/
	VOLATILE UINT32 revid1;     	  	/*28h*/
	VOLATILE UINT32 revid2;       	/*2Ch*/
	VOLATILE UINT32 pwremu_mgmt;   	/*30h*/
	VOLATILE UINT32 mdr;          	/*34h*/
}UART_DSP_REG;                                     
#pragma STRUCT_ALIGN(__uart_dsp_reg,4);            

/* globals */ 

/* locals */

/* local function declarations */ 
LOCAL void uartCfg(UINT8 ucUartIndex, UINT32 unUartClk, UINT32 unBaudrate);


#define MAX_WRITE_LEN  4096


static INT8 fifoBuffer[MAX_WRITE_LEN];
FIFO8 s_fifo8;

/******************************************************************************
 * 函 数 名:fifoOpen
 *
 * 函数说明:FIFO初始化
 * 参数说明:无
 * 输入参数:无
 * 输出参数:无
 * 返 回 值:固定返回0
******************************************************************************/

INT32 fifoOpen(void)
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

INT32 fifoWrite(INT8* pBuf, UINT32 wLen)
{
	UINT32 i;
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

INT32 fifoRead(INT8* pBuf, UINT32* pRLen8)
{
	FIFO8* pFifo8 = &s_fifo8;
	UINT32 len = *pRLen8;
	UINT32 total = 0x0;
	UINT32 i;	
	
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

INT32 fifoCheck(void)
{
	FIFO8* pFifo8 = &s_fifo8;

	if(pFifo8->pFifoIn != pFifo8->pFifoOut)
	{
		return 1;
	}

	return 0;
}


/*global function define*/
INT32 dspUartOpen(UINT8 channel)
{
	uartCfg(channel,UART_BAUTE,115200U);

	return 0x0;
}

INT32 dspUartSend(UINT8 channel, UINT8* pByte, UINT32 len)
{	
	UART_DSP_REG* pReg;
	UINT32 txEmpty;
	
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
	
	txEmpty = UART_LSR_TEMT | UART_LSR_THRE;	
	while(len)
	{
		while (txEmpty != (pReg->lsr & txEmpty));	
		delay(10);
		pReg->rbr_thr = *pByte++;	
		len --;
	}

	return 0;	
}

INT32 dspUartRece(UINT8 channel, UINT8* pByte, UINT32* pLen)
{
	UART_DSP_REG* pReg;
	UINT32 len;
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
		*pByte++ = (UINT8)(pReg->rbr_thr);
		len++;
		if(len >= *pLen)	
		{
			break;
		}
	}

	*pLen = len;
	return 0;
}


INT32 dspUartClose(UINT8 channel)
{

	return 0;		
}

/*local function define*/
LOCAL void uartCfg(UINT8 ucUartIndex, UINT32 unUartClk, UINT32 unBaudrate)
{
	UART_DSP_REG* pReg;
	UINT32 divisor;
	UINT32 intStatus;
	UINT8 byte;

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

	pReg->ier |= (UINT32)1<<0;

	intStatus = pReg->iir_fcr;
	if ((intStatus&0x1) == 0x1) /*no interrupts pending*/
	{
		return;
	}
	switch((intStatus>>0x1)&0x7)
	{
		case 1: 	/*Transmitter holding register empty (priority 3)*/
			pReg->rbr_thr = byte;	/*write thr clean this interrupt*/
			break;
		case 2: 	/*Receiver data available (priority 2)*/
			byte = (UINT8)(pReg->rbr_thr);	/*non fifo mode read rbr reg clean interrupt , fifo mode low trigger level clean interrupt*/
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


void dspUartIsr(UINT32 ucUartIndex)
{
	UART_DSP_REG* pReg;
	UINT32 intStatus;
	INT8 byte;
    /* Disable the CIC out for interrupt processing */
	pReg = (UART_DSP_REG*)DSP_UART0_REGS_BASE_ADDR;
	// Interrupt from UART0
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
			while(pReg->lsr&0x1)	//data is ready
			{
				byte = (INT8)(pReg->rbr_thr);	/*non fifo mode read rbr reg clean interrupt , fifo mode low trigger level clean interrupt*/
				//pReg->rbr_thr = byte;
				fifoWrite((INT8*)&byte, 1);			
			}
			break;
		
		case 0:		/*reserver*/
		case 4:
		case 5:
		case 7:
		default:
			break;
	    }	
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

INT32 uartWrite(UINT8 *data, UINT16 nbytes)
{
	dspUartSend(0,(UINT8 *)data, nbytes);
	
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

INT32 uartRead(UINT8 *data, UINT16 nbytes)
{
	UINT16 i = 0;
	UINT16 readCnt = 0;
	UINT32 status = 0;
	UINT32 readLen = 1;

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
	UINT32	length = 0;

    if (strlen(fmt) > MAX_WRITE_LEN)
    {
    	return;
    }

    memset(printfBuff,0,MAX_WRITE_LEN);

    va_start(arg_ptr, fmt);
    length = vsprintf((char *)printfBuff, fmt, arg_ptr);
    va_end(arg_ptr);

    uartWrite((UINT8 *)printfBuff,length);
}
