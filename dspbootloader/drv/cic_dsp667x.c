/*

 文件名称：cic_dsp667x.c
摘要：主要实现dsp667x的cic初始化控制
*/
/* 修改历史:
2016.3.3,chengqb创建文件
*/

/* includes */ 
#include "common.h"
#include "datatype.h"
#include "delay.h"
#include "dsp667x.h"
#include "cic_dsp667x.h"
#include "irq_dsp667x.h"
/* defines */ 

/* typedefs */  

/* globals */ 
CIC_ISR_VECTOR g_cicIsrTable[CIC_MAX_NUM];

/* locals */

/* local function declarations */

/*global function define*/ 
INT32 cicSystemEventMapToChannel(UINT8 cicNum, UINT8 cicEventId, UINT8 channelId, UINT8 hostId)
{
	CIC_REG* pReg;

	switch(cicNum)
	{
		case 0:
			pReg = (CIC_REG*)CSL_CP_INTC_0_REGS;
			break;
		case 1:
			pReg = (CIC_REG*)CSL_CP_INTC_0_REGS;
			break;
		case 2:
			pReg = (CIC_REG*)CSL_CP_INTC_0_REGS;
			break;
		case 3:
			pReg = (CIC_REG*)CSL_CP_INTC_0_REGS;
			break;
		default :
			return -1;
	}

	/* disable all host interrupts. */
	pReg->global_enable_hint_reg = 0x0;
	
	/* configure no nesting support in the CPINTC Module. */
	pReg->control_reg = 0x10;
	/*clear system_event(index) */
	pReg->status_clr_index_reg = cicEventId;
	/* enable it (index)*/
	pReg->enable_set_index_reg = cicEventId;

	/*map event to channel*/
	pReg->ch_map[cicEventId] = channelId;	
	
	pReg->hint_enable_set_index_reg = hostId;	
	/* enable all host interrupts. */	
	pReg->global_enable_hint_reg = 0x1;

	return 0;
}


INT32 cicChannelIsrRegisterC(UINT8 eventId, UINT32 cicEventId, CHANNEL_ISR_FUNC pChannelIsrFunc, INT32 nArg,BOOL enableInt)
{
	CIC_ISR_VECTOR* pVector;
	UINT8 cicNum;
	UINT8 channelId;
	UINT8 hostId;
	UINT32 coreId = CSL_chipReadDNUM();

	/*根据event id号计算映射通道*/
	switch(eventId)
	{
		case EVENT_CIC0_OUT32_0_11_N_CIC1_OUT32_0_11_N_4:	/*32+0+11*n*/
			hostId = channelId = 32+0+11*coreId;
			break;

		default:
			return -1;
	}

	cicNum = cicEventId>>8;
	cicEventId = cicEventId%256;
	pVector = & g_cicIsrTable[cicNum];

	#if 0
	/*cic全部事件都映射到同一个envent 事件通道(21)*/
	pVector->channelIsrTable/*[coreId]*/[0x0][cicEventId].channelIsrFunc= pChannelIsrFunc;
	pVector->channelIsrTable/*[coreId]*/[0x0][cicEventId].nArg = nArg;
	#else
	pVector->channelIsrTable/*[coreId]*/[0x0][0].channelIsrFunc= pChannelIsrFunc;
	pVector->channelIsrTable/*[coreId]*/[0x0][0].nArg = nArg;
	#endif


	return cicSystemEventMapToChannel(cicNum, cicEventId,  channelId, hostId);
}

void cicChannelIsrDispatchC(UINT8 cicNum)
{
	CIC_ISR_VECTOR* pVector;
	CIC_REG* pReg;
	UINT32 intPend;
	UINT32 intStatus;
	UINT32 intEnableMask;
	UINT32 i,j;
	UINT32 coreId = CSL_chipReadDNUM();

	switch(cicNum)
	{
		case 0:
			pReg = (CIC_REG*)CSL_CP_INTC_0_REGS;
			break;
		case 1:
			pReg = (CIC_REG*)CSL_CP_INTC_0_REGS;
			break;
		case 2:
			pReg = (CIC_REG*)CSL_CP_INTC_0_REGS;
			break;
		case 3:
			pReg = (CIC_REG*)CSL_CP_INTC_0_REGS;
			break;
		default :
			return;
	}

	pVector = &g_cicIsrTable[cicNum];
	for(i=4/*0*/; i<5; i++)	/*此处按照160个事件设置，理论可以支持1024个cic事件*/
	{
		intStatus = pReg->raw_status_reg[i];
		intEnableMask = pReg->enable_reg[i];
		for(j=0x14/*0*/; j<0x15/*32*/; j++)
		{
			if(intEnableMask&((UINT32)1<<j)&intStatus)
			{
				//该事件产生了中断
				#if 0
				if(pVector->channelIsrTable/*[coreId]*/[0][i*32+j].channelIsrFunc != NULL)
				{
					pVector->channelIsrTable/*[coreId]*/[0][i*32+j].channelIsrFunc(pVector->channelIsrTable/*[coreId]*/[0][i*32+j].nArg);
				}
				#else
				if(pVector->channelIsrTable/*[coreId]*/[0][0].channelIsrFunc != NULL)
				{
					pVector->channelIsrTable/*[coreId]*/[0][0].channelIsrFunc(pVector->channelIsrTable/*[coreId]*/[0][0].nArg);
				}
				#endif
			}
		}
		/*清中断*/
		pReg->ena_status_reg[i] = intStatus;
	}
}

/*local function define*/
