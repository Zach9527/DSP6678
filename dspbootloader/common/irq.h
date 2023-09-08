/*
 �ļ����ƣ�irq.h
ժҪ��
*/

#ifndef __IRQ_H__
#define __IRQ_H__

#ifdef __cplusplus
extern "C" {
#endif

/*include*/
#include "common.h"

/*defines*/
#define IRQ_NUM		16

/*typedef*/
typedef void (*ISRPFUNC)(UINT32 arg);
typedef struct irq_vector
{
	#ifdef DSP_BIOS
	#ifdef DSP_BIOS_6
	Hwi_Params hwiParams;
	#else
	HWI_Attrs hwiAttrs;		/*�ж�����*/
	#endif
	#endif
	ISRPFUNC pRegisterIsr;	/*�û�ע����жϺ���ָ��*/	
	INT32 isrArg;			/*�û������жϺ�������*/
}IRQ_VECTOR;

typedef struct __intContex
{
	UINT8 conectType;
	UINT8 irqNum;
	UINT8 eventId;
	//UINT8 eventGoupId;		/*���ID*/
	UINT8 cicEventId;
	//UINT8 cicNum;			/*cic NUM*/
	ISRPFUNC pIsr;
	INT32 isrArg;
	BOOL enableInt; 
}INTCONTEXT;


/*global declarations*/
IMPORT IRQ_VECTOR g_irqVectorsTable[IRQ_NUM];



/* function declaration */
IMPORT STATUS intInit(void);
IMPORT  void intGlobalEnable(void);
IMPORT  UINT32  intGlobalDisable(void);
IMPORT void intGlobalRestore(UINT32 unRestoreValue);
IMPORT void intNmiEnable(void);
IMPORT void intNmiDisable(void);
IMPORT STATUS intEnable(UINT32 unIntNum);
IMPORT STATUS intDisable(UINT32 unIntNum);
IMPORT INLINE STATUS intClear(UINT32 unIntNum);
IMPORT INLINE STATUS intMap(UINT32 unEvnetId, UINT32 unIntNum);
IMPORT INLINE void intSetVecs(void* pVectors);
IMPORT INLINE void intxIsr(INT32 irqNum);
IMPORT void intIsrInstal(void);
IMPORT INT32 intIsrRegister(UINT8 irqNum, ISRPFUNC pIsr, INT32 isrArg, BOOL enableInt);
IMPORT INT32 intConnect(INTCONTEXT* pIntContext);
IMPORT INT32 extIntConnect(UINT8 conectType, UINT8 eventId, UINT8 irqNum, UINT8 pinId, UINT8 intType, ISRPFUNC pIsr, INT32 isrArg, BOOL enableInt);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__IRQ_H__*/

