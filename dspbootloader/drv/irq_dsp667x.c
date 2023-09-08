/*
 文件名称：irq_dsp667x.c
摘要：主要实现dsp667x的irq模块的驱动接口
*/
/* 修改历史:
2016.3.13,chengqb创建文件
*/

/* includes */
#include "common.h"
#include "datatype.h"
#include "delay.h"
#include "dsp667x.h"
#include "cic_dsp667x.h"
#include "irq_dsp667x.h"


/* defines */ 
                                              
#define IRQ_REGS_BASE_ADDR            					(0x01800000)	/*基地址*/
                                              
/* typedefs */                                
typedef struct __irq_reg                      
{                                             
	VOLATILE UINT32 evtflag0; 			/*01800000h*/ 
	VOLATILE UINT32 evtflag1; 			/*01800004h*/
	VOLATILE UINT32 evtflag2; 			/*01800008h*/	 
	VOLATILE UINT32 evtflag3; 			/*0180000Ch*/
	VOLATILE UINT32 res0[4]; 			
	VOLATILE UINT32 evtset0; 			  /*01800020h*/
	VOLATILE UINT32 evtset1;    	  /*01800024h*/
	VOLATILE UINT32 evtset2;    	  /*01800028h*/
	VOLATILE UINT32 evtset3;    	  /*0180002Ch*/
	VOLATILE UINT32 res1[4]; 			
	VOLATILE UINT32 evtclr0;    	  /*01800040h*/
	VOLATILE UINT32 evtclr1;  	  	/*01800044h*/
	VOLATILE UINT32 evtclr2;  	  	/*01800048h*/
	VOLATILE UINT32 evtclr3;    	  /*0180004Ch*/
	VOLATILE UINT32 res2[12]; 			
	VOLATILE UINT32 evtmask0;    	  /*01800080h*/
	VOLATILE UINT32 evtmask1;    	  /*01800084h*/
	VOLATILE UINT32 evtmask2;    	  /*01800088h*/
	VOLATILE UINT32 evtmask3;  	  	  /*0180008Ch*/
	VOLATILE UINT32 res3[4]; 			
	VOLATILE UINT32 mevtflag0;   	  /*018000A0h*/
	VOLATILE UINT32 mevtflag1;   	  /*018000A4h*/
	VOLATILE UINT32 mevtflag2;   	  /*018000A8h*/
	VOLATILE UINT32 mevtflag3;   	  /*018000ACh*/
	VOLATILE UINT32 res4[4]; 			
	VOLATILE UINT32 expmask0;   	  /*018000C0h*/
	VOLATILE UINT32 expmask1;   	  /*018000C4h*/
	VOLATILE UINT32 expmask2;   	  /*018000C8h*/
	VOLATILE UINT32 expmask3;   	  /*018000CCh*/
	VOLATILE UINT32 res5[4]; 			
	VOLATILE UINT32 mexpflag0;   	  /*018000E0h*/
	VOLATILE UINT32 mexpflag1;   		/*018000E4h*/
	VOLATILE UINT32	mexpflag2;   	  /*018000E8h*/
	VOLATILE UINT32	mexpflag3;      /*018000ECh*/
	VOLATILE UINT32 res6[5];			
	VOLATILE UINT32	intmux1;   	  	/*01800104h*/
	VOLATILE UINT32	intmux2; 		  	/*01800108h*/
	VOLATILE UINT32	intmux3;		  	/*0180010Ch*/
	VOLATILE UINT32	res7[12];
	VOLATILE UINT32  aegmux0;			/*01810140*/
	VOLATILE UINT32  aegmux1;			/*01810144*/
	VOLATILE UINT32	res8[10];
	VOLATILE UINT32	intxstat;		  	/*01800180h*/
	VOLATILE UINT32	intxclr;		  	/*01800184h*/
	VOLATILE UINT32	intdmask;		  	/*01800188h*/
	//VOLATILE UINT32	res8[13];		  	
	//VOLATILE UINT32	evtasrt;		  	/*018001C0h*/
}IRQ_REG;                                     
#pragma STRUCT_ALIGN(__irq_reg,4);            
                                              
                                              
/* globals */                                 
                                              
/* locals */                                  

IMPORT EVNET_C_VECTOR g_eventIsrTableC[EVENT_TOTAL_NUM] = {{NULL,0}};
                                              
/* local function declarations */
                                              
/*global function define*/


/******************************************************************************
 * 函   数  名:  eventMap                        
 *                                            
 * 函数说明: 事件号与中断号进行映射
 * 输入参数: unEvnetId事件ID号，该参数从0~127
 *                         unIntNum 中断ID号，该参数从4~15
 * 输出参数:	无                              
 * 返  回   值:	DSP_ERROR/失败   DSP_OK/成功      
 *                                            
 *备注：                                      
******************************************************************************/
 STATUS eventMap(UINT32 unEvnetId, UINT32 unIntNum)
{
#define DSPINTC_INTMUX_INTSEL_SHIFT(n)	(((n) & 0x3) * 8)
#define DSPINTC_INTMUX_INTSEL(n)		(0x7F << DSPINTC_INTMUX_INTSEL_SHIFT(n))

	VOLATILE IRQ_REG* pReg = (VOLATILE IRQ_REG*)IRQ_REGS_BASE_ADDR;	
	
	UINT32 unIntNumGroupId = unIntNum>>2;	/*/4*/
	UINT32 unRestoreValue;

	/* Check the system event number */
	if((unEvnetId<4) || (unEvnetId>127))
	{
		return DSP_ERROR;
	}
	if((unIntNum<4) || (unIntNum>15))
	{
		return DSP_ERROR;
	}
	
    unRestoreValue = intGlobalDisable();/* Disable interrupts */
	switch(unIntNumGroupId)
	{
		case 1:
			pReg->intmux1 = (pReg->intmux1 & (~ DSPINTC_INTMUX_INTSEL(unIntNum))) 
							|(unEvnetId << DSPINTC_INTMUX_INTSEL_SHIFT(unIntNum));
			break;
		case 2:			
			pReg->intmux2 = (pReg->intmux2 & (~ DSPINTC_INTMUX_INTSEL(unIntNum))) 
							|(unEvnetId << DSPINTC_INTMUX_INTSEL_SHIFT(unIntNum));
			break;
		case 3:			
			pReg->intmux3 = (pReg->intmux3 & (~ DSPINTC_INTMUX_INTSEL(unIntNum))) 
							|(unEvnetId << DSPINTC_INTMUX_INTSEL_SHIFT(unIntNum));
			break;
		default:
			break;
	}
    /* Clear any residual interrupt */
    ICR = (1 << unIntNum);
	
    intGlobalRestore(unRestoreValue);    /* Enable interrupts */

	return DSP_OK;
}




/******************************************************************************
 * 函   数  名:  eventAddC                        
 *                                            
 * 函数说明: 将事件加入到事件组合器中(共用中断号)
 * 输入参数: 无                               
 * 输出参数:	无                              
 * 返  回   值:	DSP_ERROR/失败   DSP_OK/成功      
 *                                            
 *备注：                                      
******************************************************************************/
STATUS eventAddC(UINT32 unEvnetId)
{
	VOLATILE IRQ_REG* pReg = (VOLATILE IRQ_REG*)IRQ_REGS_BASE_ADDR;	
	
	UINT32 unEvnetGroupId = unEvnetId>>5;	/*/32*/
	UINT32 unRestoreValue;
	UINT32 unMaskValue;

	/* Check the system event number */
	#if 0
	if((unEvnetId<4) || (unEvnetId>127))
	{
		return DSP_ERROR;
	}
	#endif
    
	unMaskValue = (UINT32)1<<(unEvnetId&31);
	
    	unRestoreValue = intGlobalDisable();/* Disable interrupts */
	switch(unEvnetGroupId)
	{
		case 0:
			pReg->evtmask0 &= ~unMaskValue;
			break;
		case 1:
			pReg->evtmask1 &= ~unMaskValue;
			break;
		case 2:			
			pReg->evtmask2 &= ~unMaskValue;
			break;
		case 3:			
			pReg->evtmask3 &= ~unMaskValue;
			break;
		default:
			break;
	}	
    intGlobalRestore(unRestoreValue);    /* Enable interrupts */

	return DSP_OK;
}


/******************************************************************************
 * 函   数  名:  eventRemoveC                        
 *                                            
 * 函数说明: 将事件清除事件组合器(共用中断号)
 * 输入参数: unEvnetId 事件ID号，该参数为4~127                               
 * 输出参数:	无                              
 * 返  回   值:	DSP_ERROR/失败   DSP_OK/成功      
 *                                            
 *备注：                                      
******************************************************************************/
STATUS eventRemoveC(UINT32 unEvnetId)
{
	VOLATILE IRQ_REG* pReg = (VOLATILE IRQ_REG*)IRQ_REGS_BASE_ADDR;	
	
	UINT32 unEvnetGroupId = unEvnetId>>5;	/*/32*/
	UINT32 unRestoreValue;
	UINT32 unMaskValue;

	/* Check the system event number */
	#if 0
	if((unEvnetId<4) || (unEvnetId>127))
	{
		return DSP_ERROR;
	}
	#endif
    
	unMaskValue = (UINT32)1<<(unEvnetId&31);
	
    	unRestoreValue = intGlobalDisable();/* Disable interrupts */
	switch(unEvnetGroupId)
	{
		case 0:
			pReg->evtmask0 |= unMaskValue;
			break;
		case 1:
			pReg->evtmask1 |= unMaskValue;
			break;
		case 2:			
			pReg->evtmask2 |= unMaskValue;
			break;
		case 3:			
			pReg->evtmask3 |= unMaskValue;
			break;
		default:
			break;
	}	
    intGlobalRestore(unRestoreValue);    /* Enable interrupts */

	return DSP_OK;
}

/******************************************************************************
 * 函   数  名:  eventAddE                        
 *                                            
 * 函数说明: 将事件加入到异常事件组合器中(共用中断号)
 * 输入参数: 无                               
 * 输出参数:	无                              
 * 返  回   值:	DSP_ERROR/失败   DSP_OK/成功      
 *                                            
 *备注：                                      
******************************************************************************/
STATUS eventAddE(UINT32 unEvnetId)
{
	VOLATILE IRQ_REG* pReg = (VOLATILE IRQ_REG*)IRQ_REGS_BASE_ADDR;	
	
	UINT32 unEvnetGroupId = unEvnetId>>5;	/*/32*/
	UINT32 unRestoreValue;
	UINT32 unMaskValue;

	/* Check the system event number */
	if((unEvnetId<4) || (unEvnetId>127))
	{
		return DSP_ERROR;
	}
    
	unMaskValue = (UINT32)1<<(unEvnetId&31);
	
    unRestoreValue = intGlobalDisable();/* Disable interrupts */
	switch(unEvnetGroupId)
	{
		case 0:
			pReg->expmask0 &= ~unMaskValue;
			break;
		case 1:
			pReg->expmask0 &= ~unMaskValue;
			break;
		case 2:			
			pReg->expmask0 &= ~unMaskValue;
			break;
		case 3:			
			pReg->expmask0 &= ~unMaskValue;
			break;
		default:
			break;
	}	
    intGlobalRestore(unRestoreValue);    /* Enable interrupts */

	return DSP_OK;
}

/******************************************************************************
 * 函   数  名:  eventAddC                        
 *                                            
 * 函数说明: 将事件清除异常事件组合器(共用中断号)
 * 输入参数: unEvnetId 事件ID号，该参数为4~127                               
 * 输出参数:	无                              
 * 返  回   值:	DSP_ERROR/失败   DSP_OK/成功      
 *                                            
 *备注：                                      
******************************************************************************/
STATUS eventRemoveE(UINT32 unEvnetId)
{
	VOLATILE IRQ_REG* pReg = (VOLATILE IRQ_REG*)IRQ_REGS_BASE_ADDR;	
	
	UINT32 unEvnetGroupId = unEvnetId>>5;	/*/32*/
	UINT32 unRestoreValue;
	UINT32 unMaskValue;

	/* Check the system event number */
	if((unEvnetId<4) || (unEvnetId>127))
	{
		return DSP_ERROR;
	}
    
	unMaskValue = (UINT32)1<<(unEvnetId&31);
	
    unRestoreValue = intGlobalDisable();/* Disable interrupts */
	switch(unEvnetGroupId)
	{
		case 0:
			pReg->expmask0 |= unMaskValue;
			break;
		case 1:
			pReg->expmask0 |= unMaskValue;
			break;
		case 2:			
			pReg->expmask0 |= unMaskValue;
			break;
		case 3:			
			pReg->expmask0 |= unMaskValue;
			break;
		default:
			break;
	}	
    intGlobalRestore(unRestoreValue);    /* Enable interrupts */

	return DSP_OK;
}



/******************************************************************************
 * 函   数  名:  eventSet                        
 *                                            
 * 函数说明: 手动方式产生中断
 * 输入参数: unEvnetId事件ID号，该参数从0~127
 * 输出参数:	无                              
 * 返  回   值:	DSP_ERROR/失败   DSP_OK/成功      
 *                                            
 *备注：                                      
******************************************************************************/
STATUS eventSet(UINT32 unEvnetId)
{
	VOLATILE IRQ_REG* pReg = (VOLATILE IRQ_REG*)IRQ_REGS_BASE_ADDR;	
	
	UINT32 unEvnetGroupId = unEvnetId>>5;	/*/32*/
	UINT32 unMaskValue;

	/* Check the system event number */
	if((unEvnetId<4) || (unEvnetId>127))
	{
		return DSP_ERROR;
	}
	
	unMaskValue = (UINT32)1<<(unEvnetId&31);
	
	switch(unEvnetGroupId)
	{
		case 0:
			pReg->evtset0 = unMaskValue;
			break;
		case 1:
			pReg->evtset1 = unMaskValue;
			break;
		case 2:			
			pReg->evtset1 = unMaskValue;
			break;
		case 3:			
			pReg->evtset1 = unMaskValue;
			break;
		default:
			break;
	}	

	return DSP_OK;
}

/******************************************************************************
 * 函   数  名:  eventClear                        
 *                                            
 * 函数说明: 清除中断状态标志
 * 输入参数: unEvnetId事件ID号，该参数从0~127
 * 输出参数:	无                              
 * 返  回   值:	DSP_ERROR/失败   DSP_OK/成功      
 *                                            
 *备注：                                      
******************************************************************************/
STATUS eventClear(UINT32 unEvnetId)
{
	VOLATILE IRQ_REG* pReg = (VOLATILE IRQ_REG*)IRQ_REGS_BASE_ADDR;	
	
	UINT32 unEvnetGroupId = unEvnetId>>5;	/*/32*/
	UINT32 unMaskValue;

	/* Check the system event number */
	if((unEvnetId<4) || (unEvnetId>127))
	{
		return DSP_ERROR;
	}
	
	unMaskValue = (UINT32)1<<(unEvnetId&31);
	
	switch(unEvnetGroupId)
	{
		case 0:
			pReg->evtclr0 = unMaskValue;
			break;
		case 1:
			pReg->evtclr0 = unMaskValue;
			break;
		case 2:			
			pReg->evtclr0 = unMaskValue;
			break;
		case 3:			
			pReg->evtclr0 = unMaskValue;
			break;
		default:
			break;
	}	

	return DSP_OK;
}

/******************************************************************************
 * 函   数  名:  eventIsrDispatchC                        
 *                                            
 * 函数说明: 查询执行对应事件的ISR
 * 输入参数:unEvnetGroupId 时间组ID，该参数值为0~3                               
 * 输出参数:	无                              
 * 返  回   值:	DSP_ERROR/失败   DSP_OK/成功      
 *                                            
 *备注：                                      
******************************************************************************/
void eventIsrDispatchC(UINT32 unEvnetGroupId)
{
	VOLATILE IRQ_REG* pReg = (VOLATILE IRQ_REG*)IRQ_REGS_BASE_ADDR;
	
	VOLATILE UINT32* pMeventFlagReg;
	VOLATILE UINT32* pEventClrReg;

	UINT32 unMeventFlagReg;
	UINT32 unOffset;
	UINT32 unEvtIndex;
	
	/* Check the system event number */
	switch(unEvnetGroupId)
	{
		case 0:
			pMeventFlagReg = (VOLATILE UINT32*)&pReg->mevtflag0;
			pEventClrReg = (VOLATILE UINT32*)&pReg->evtclr0;
			break;
		case 1:
			pMeventFlagReg = (VOLATILE UINT32*)&pReg->mevtflag1;
			pEventClrReg = (VOLATILE UINT32*)&pReg->evtclr1;
			break;
		case 2:			
			pMeventFlagReg = (VOLATILE UINT32*)&pReg->mevtflag2;
			pEventClrReg = (VOLATILE UINT32*)&pReg->evtclr2;
			break;
		case 3:			
			pMeventFlagReg = (VOLATILE UINT32*)&pReg->mevtflag3;
			pEventClrReg = (VOLATILE UINT32*)&pReg->evtclr3;
			break;
		default:
			break;
	}

	unOffset = 32*unEvnetGroupId;
	unMeventFlagReg =*pMeventFlagReg;	/*获取可屏蔽中断的状态*/
	while(unMeventFlagReg)
	{
        /* Clear system events */
		*pEventClrReg = unMeventFlagReg;
		
        /* Service system events */
		do
		{
            unEvtIndex = 31 - _lmbd(1, unMeventFlagReg);			
            unMeventFlagReg &= ~(1 << unEvtIndex);		
			if(g_eventIsrTableC[unEvtIndex+unOffset].eventIsrFunc != NULL)
			{
				g_eventIsrTableC[unEvtIndex+unOffset].eventIsrFunc(g_eventIsrTableC[unEvtIndex+unOffset].nArg);
			}			
		}while(unMeventFlagReg);		
		
		/* Check for new system events */
		unMeventFlagReg = *pMeventFlagReg;
	}	
}

/******************************************************************************
 * 函   数  名:  eventIsrRegisterC                        
 *                                            
 * 函数说明: 注册事件的ISR  到事件组合器(共用中断号)
 * 输入参数: 无                               
 * 输出参数:	无                              
 * 返  回   值:	DSP_ERROR/失败   DSP_OK/成功      
 *                                            
 *备注：                                      
******************************************************************************/
INT32 eventIsrRegisterC(UINT32 unEvnetId, EVENT_ISR_FUNC eventIsrFunc, INT32 nArg,BOOL enableInt)
{
	/* Check the system event number */
	#if 0
	if ((unEvnetId<4) || (unEvnetId>127))
	{
		return -1;
	}
	#endif
	g_eventIsrTableC[unEvnetId].eventIsrFunc = eventIsrFunc;
	g_eventIsrTableC[unEvnetId].nArg = nArg;
	if (enableInt)
	{
		eventAddC(unEvnetId);
		return 0;
	}
	eventRemoveC(unEvnetId);
	return 0;
}


void eventIstInstalC(void)
{
	VOLATILE IRQ_REG* pReg = (VOLATILE IRQ_REG*)IRQ_REGS_BASE_ADDR;	
	UINT8 i;

	/*初始化事件向量表*/
	for(i=0; i<EVENT_TOTAL_NUM; i++)
	{
		g_eventIsrTableC[i].eventIsrFunc = NULL;
	}

	/*安装事件服务函数:本处不需要安装，
	  通过注册方式实现对每个事件服务函数的安装*/

	/*关闭所有事件产生中断*/
	pReg->evtmask0 = 0xFFFFFFFF;
	pReg->evtmask0 = 0xFFFFFFFF;
	pReg->evtmask0 = 0xFFFFFFFF;
	pReg->evtmask0 = 0xFFFFFFFF;	
}

/*local function define*/                     

