/*
 �ļ����ƣ�irq.c
ժҪ����Ҫʵ����ƽ̨�޹ص��жϹ���
*/
/* �޸���ʷ:
2016.3..13,�����ļ�
*/

/* includes */

#include"datatype.h"
#include"delay.h"
#include"c6x.h"
//#include"oshead.h"
#include"irq.h"
#include "cic_dsp667x.h"
#include "irq_dsp667x.h"
/* defines */ 

/*typedef*/

/* globals */                                 

/* locals */                                  

                                              
/*global function define*/

/******************************************************************************
 * ��   ��  ��:  intGlobalEnable                        
 *                                            
 * ����˵��: ʹ��ȫ���ж�
 * �������: ��
 * �������:	��                              
 * ��  ��   ֵ:	��
 *                                            
 *��ע��                                      
******************************************************************************/
void intGlobalEnable(void)
{
    _enable_interrupts();
}

/******************************************************************************
 * ��   ��  ��:  intGlobalEnable                        
 *                                            
 * ����˵��: ʹ��ȫ���ж�
 * �������: ��
 * �������:	��                              
 * ��  ��   ֵ:	�����ж�״̬
 *                                            
 *��ע��                                      
******************************************************************************/
UINT32  intGlobalDisable(void)
{
    return (UINT32)(_disable_interrupts());
}

/******************************************************************************
 * ��   ��  ��:  intGlobalEnable                        
 *                                            
 * ����˵��: ʹ��ȫ���ж�
 * �������: ��
 * �������:	��                              
 * ��  ��   ֵ:	�����ж�״̬
 *                                            
 *��ע��                                      
******************************************************************************/
void intGlobalRestore(UINT32 unRestoreValue)
{
    _restore_interrupts(unRestoreValue);
}

/******************************************************************************
 * ��   ��  ��:  intNmiEnable                        
 *                                            
 * ����˵��: ʹ�ܷ������ж�
 * �������: ��
 * �������:	��                              
 * ��  ��   ֵ:	��
 *                                            
 *��ע��                                      
******************************************************************************/
void intNmiEnable(void)
{
	IER |= 0x2;
}

/******************************************************************************
 * ��   ��  ��:  intNmiDisable                        
 *                                            
 * ����˵��: ��ֹ�������ж�
 * �������: ��
 * �������:	��                              
 * ��  ��   ֵ:	��
 *                                            
 *��ע��                                      
******************************************************************************/
void intNmiDisable(void)
{
	IER &= ~0x2;
}


/******************************************************************************
 * ��   ��  ��:  intEnable                        
 *                                            
 * ����˵��: ʹ���ж�
 * �������: unIntNum dsp�ж�������ţ��ò���Ϊ4~15
 * �������:	��                              
 * ��  ��   ֵ:	�����ж�״̬
 *                                            
 *��ע��                                      
******************************************************************************/
STATUS intEnable(UINT32 unIntNum)
{
	UINT32 restoreVal;
	
	if((unIntNum<4) || (unIntNum>15))
	{
		return DSP_ERROR;
	}
    /* Disable interrupts */
    restoreVal = intGlobalDisable();

    /* Enable CPU maskable interrupt */
    IER |= (1 << unIntNum);

    /* Restore interrupts */
    intGlobalRestore(restoreVal);

	return DSP_OK;	
}

/******************************************************************************
 * ��   ��  ��:  intEnable                        
 *                                            
 * ����˵��: ʹ���ж�
 * �������: unIntNum dsp�ж�������ţ��ò���Ϊ4~15
 * �������:	��                              
 * ��  ��   ֵ:	�����ж�״̬
 *                                            
 *��ע��                                      
******************************************************************************/
STATUS intDisable(UINT32 unIntNum)
{
	UINT32 restoreVal;	
	
	if((unIntNum<4) || (unIntNum>15))
	{
		return DSP_ERROR;
	}
    /* Disable interrupts */
    restoreVal = intGlobalDisable();

    /* Enable CPU maskable interrupt */
    IER &= ~(1 << unIntNum);

    /* Restore interrupts */
    intGlobalRestore(restoreVal);

	return DSP_OK;	
}

/******************************************************************************
 * ��   ��  ��:  intEnable                        
 *                                            
 * ����˵��: ʹ���ж�
 * �������: unIntNum dsp�ж�������ţ��ò���Ϊ4~15&0xFF(ȫ��)
 * �������:	��                              
 * ��  ��   ֵ:	�ɹ�����DSP_OK, ʧ�ܷ���DSP_ERROR
 *                                            
 *��ע��                                      
******************************************************************************/
INLINE STATUS intClear(UINT32 unIntNum)
{
	if (unIntNum == 0xFF)
	{
		ICR = 0xFFFF;
		return DSP_OK;
	}
	
	if ((unIntNum<4) || (unIntNum>15))
	{
		return DSP_ERROR;
	}
	
    ICR = 1<<unIntNum;

	return DSP_OK;	
}


/******************************************************************************
 * ��   ��  ��:  intMap                        
 *                                            
 * ����˵��: �¼������жϺŽ���ӳ��
 * �������: unEvnetId�¼�ID�ţ��ò�����0~127
 *                         unIntNum �ж�ID�ţ��ò�����4~15
 * �������:	��                              
 * ��  ��   ֵ:	DSP_ERROR/ʧ��   DSP_OK/�ɹ�      
 *                                            
 *��ע��                                      
******************************************************************************/
INLINE STATUS intMap(UINT32 unEvnetId, UINT32 unIntNum)
{
	eventMap(unEvnetId, unIntNum);
	return 0;
}
                                              






 
