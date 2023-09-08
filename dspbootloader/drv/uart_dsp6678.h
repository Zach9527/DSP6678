/*
 �ļ����ƣ�uart_dsp6678.h
ժҪ��
*/
/* �޸���ʷ:

2016.3.19 chengqb�����ļ�
*/

#ifndef __UART_DSP6678__
#define __UART_DSP6678__

#ifdef __cplusplus
extern "C" {
#endif

/*include*/

/*typedef*/

/*global declarations*/

/*defines*/
#define DSPUART_SET_BUARD_CMD			    (0)		/*���ò�����*/
#define DSPUART_QUERY_SEND_CMD			  (1)		/*��ѯ�Ƿ���Է�������*/
#define DSPUART_QUERY_RECE_CMD			  (2)		/*��ѯ�Ƿ���Խ�������*/
#define DSPUART_ENABLE_RECEINT_CMD		(3)		/*ʹ�ܽ����ж�*/
#define DSPUART_DISABLE_RECEINT_CMD		(4)		/*�رս����ж�*/
#define DSPUART_ENABLE_SENDINT_CMD		(5)		/*ʹ�ܷ����ж�*/
#define DSPUART_DISABLE_SENDINT_CMD		(6)		/*�رշ����ж�*/
#define PRINT  uartprintf


/* function declaration */
IMPORT INT32 dspUartOpen(UINT8 channel);
IMPORT INT32 dspUartSend(UINT8 channel, UINT8* pByte, UINT32 len);
IMPORT INT32 dspUartRece(UINT8 channel, UINT8* pByte, UINT32* pLen);
IMPORT INT32 dspUartClose(UINT8 channel);
extern void dspUartIsr(UINT32 ucUartIndex);
extern INT32 fifoOpen(void);
extern INT32 fifoWrite(INT8* pBuf, UINT32 wLen);
extern INT32 fifoRead(INT8* pBuf, UINT32* pRLen8);
extern INT32 fifoCheck(void);
extern void uartprintf(const char *fmt, ... );

typedef struct _fifo8
{
	UINT32 fifoSize;
	INT8*  pFifoBuf;
	INT8*  pFifoIn;
	INT8*  pFifoOut;
}FIFO8;

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__UART_DSP6678__*/



