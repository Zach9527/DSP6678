/*
 * Uart_Init.h
 *
 *  Created on: 2022-12-28
 *      Author: ORC-C001
 */

#ifndef UART_INIT_H_
#define UART_INIT_H_


#include "KeyStone_common.h"


#define PRINT  uartprintf
#define DSP_UART0_REGS_BASE_ADDR	(0x02540000)
#define UART_BAUTE					(182291666)		/*166666666为主频1G*/
#define UART_PWREMUMGMT_TXRST_ENABLE ((Uint32)1<<14)
#define UART_PWREMUMGMT_RXRST_ENABLE ((Uint32)1<<13)
#define UART_PWREMUMGMT_FREE_MODE    ((Uint32)1<<0)

#define UART_LCR_WLS_8BIT			((Uint32)3<<0)	/*word length 8bit*/
#define UART_LCR_STB_1BIT			((Uint32)0<<2)	/*stop bit 1bit*/
#define UART_LCR_PEN_ENABLE			((Uint32)1<<3)	/*parity enable*/
#define UART_LCR_EPS_ODD			((Uint32)0<<4)	/*odd parith*/
#define UART_LCR_EPS_EVEN			((Uint32)1<<4)	/*even parith*/
#define UART_LCR_SP_ENABLE			((Uint32)1<<5)	/*stick parith is enable*/
#define UART_LCR_BC_ENABLE			((Uint32)1<<5)	/*break contrl enable*/
#define UART_LCR_DLAB_EABLE			((Uint32)1<<7)	/*Allows access t*/

#define UART_FCR_FIFOEN         	((Uint8)1<<0)	/*FIFO enable*/
#define UART_FCR_RXCLR          	((Uint8)1<<1)	/*RX CLR*/
#define UART_FCR_TXCLR          	((Uint8)1<<2)	/*TX CLR*/
#define UART_FCR_RXFIFTL(level)     (((Uint8)(level)&0x3)<<6)
#define UART_FCR_DMAMODE1			((Uint8)1<<3)

#define UART_LSR_TEMT           	((Uint8)1<<6)
#define UART_LSR_THRE           	((Uint8)1<<5)
#define UART_LSR_DR             	((Uint8)1<<0)
typedef struct _fifo8
{
	Uint32 fifoSize;
	Int8*  pFifoBuf;
	Int8*  pFifoIn;
	Int8*  pFifoOut;
}FIFO8;
typedef struct __uart_dsp_reg                      
{                                             
	volatile Uint32 rbr_thr; 		/*00h*/ 
	volatile Uint32 ier; 			/*04h*/
	volatile Uint32 iir_fcr; 		/*08h*/	 
	volatile Uint32 lcr;        	/*0Ch*/
	volatile Uint32 mcr;        	/*10h*/
	volatile Uint32 lsr;          	/*14h*/
	volatile Uint32 msr;          	/*18h*/
	volatile Uint32 scr;          	/*1Ch*/
	volatile Uint32 dll;          	/*20h*/
	volatile Uint32 dlh;        	/*24h*/
	volatile Uint32 revid1;     	/*28h*/
	volatile Uint32 revid2;       	/*2Ch*/
	volatile Uint32 pwremu_mgmt;   	/*30h*/
	volatile Uint32 mdr;          	/*34h*/
}UART_DSP_REG;
typedef void SERIAL_IDLE_FUNC(Int32 num);
typedef struct UART_CMD_FUN_TAB_t{
	char *cmd;                //命令
	SERIAL_IDLE_FUNC *fun;    //串口命令处理函数
}UART_CMD_FUN_TAB_TYPE;




Int32 uartInit(Uint32 bps);
void uartprintf(const char *fmt, ... );
Int32 dspUartRece(Uint8 channel, Uint8* pByte, Uint32* pLen);
void KeyStone_UART_Interrupts_Init(void);
Int32 uartRead(Uint8 *data, Uint16 nbytes);
#endif /* UART_INIT_H_ */
