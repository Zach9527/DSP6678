/*
 文件名称：irq.c
摘要：主要实现与平台无关的中断管理
*/
/* 修改历史:
2016.3..13,创建文件
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
 * 函   数  名:  intGlobalEnable                        
 *                                            
 * 函数说明: 使能全局中断
 * 输入参数: 无
 * 输出参数:	无                              
 * 返  回   值:	无
 *                                            
 *备注：                                      
******************************************************************************/
void intGlobalEnable(void)
{
    _enable_interrupts();
}

/******************************************************************************
 * 函   数  名:  intGlobalEnable                        
 *                                            
 * 函数说明: 使能全局中断
 * 输入参数: 无
 * 输出参数:	无                              
 * 返  回   值:	返回中断状态
 *                                            
 *备注：                                      
******************************************************************************/
UINT32  intGlobalDisable(void)
{
    return (UINT32)(_disable_interrupts());
}

/******************************************************************************
 * 函   数  名:  intGlobalEnable                        
 *                                            
 * 函数说明: 使能全局中断
 * 输入参数: 无
 * 输出参数:	无                              
 * 返  回   值:	返回中断状态
 *                                            
 *备注：                                      
******************************************************************************/
void intGlobalRestore(UINT32 unRestoreValue)
{
    _restore_interrupts(unRestoreValue);
}

/******************************************************************************
 * 函   数  名:  intNmiEnable                        
 *                                            
 * 函数说明: 使能非屏蔽中断
 * 输入参数: 无
 * 输出参数:	无                              
 * 返  回   值:	无
 *                                            
 *备注：                                      
******************************************************************************/
void intNmiEnable(void)
{
	IER |= 0x2;
}

/******************************************************************************
 * 函   数  名:  intNmiDisable                        
 *                                            
 * 函数说明: 禁止非屏蔽中断
 * 输入参数: 无
 * 输出参数:	无                              
 * 返  回   值:	无
 *                                            
 *备注：                                      
******************************************************************************/
void intNmiDisable(void)
{
	IER &= ~0x2;
}


/******************************************************************************
 * 函   数  名:  intEnable                        
 *                                            
 * 函数说明: 使能中断
 * 输入参数: unIntNum dsp中断向量编号，该参数为4~15
 * 输出参数:	无                              
 * 返  回   值:	返回中断状态
 *                                            
 *备注：                                      
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
 * 函   数  名:  intEnable                        
 *                                            
 * 函数说明: 使能中断
 * 输入参数: unIntNum dsp中断向量编号，该参数为4~15
 * 输出参数:	无                              
 * 返  回   值:	返回中断状态
 *                                            
 *备注：                                      
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
 * 函   数  名:  intEnable                        
 *                                            
 * 函数说明: 使能中断
 * 输入参数: unIntNum dsp中断向量编号，该参数为4~15&0xFF(全清)
 * 输出参数:	无                              
 * 返  回   值:	成功返回DSP_OK, 失败返回DSP_ERROR
 *                                            
 *备注：                                      
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
 * 函   数  名:  intMap                        
 *                                            
 * 函数说明: 事件号与中断号进行映射
 * 输入参数: unEvnetId事件ID号，该参数从0~127
 *                         unIntNum 中断ID号，该参数从4~15
 * 输出参数:	无                              
 * 返  回   值:	DSP_ERROR/失败   DSP_OK/成功      
 *                                            
 *备注：                                      
******************************************************************************/
INLINE STATUS intMap(UINT32 unEvnetId, UINT32 unIntNum)
{
	eventMap(unEvnetId, unIntNum);
	return 0;
}
                                              






 
