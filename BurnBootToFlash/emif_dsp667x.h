/*

 文件名称：emif_dsp6678.h
摘要：
*/
/* 修改历史:

2016.3.19,chengqb创建文件
*/

#ifndef __EMIF_DSP6678__
#define __EMIF_DSP6678__

#ifdef __cplusplus
extern "C" {
#endif

/*include*/
#include"datatype.h"
/*typedef*/
typedef struct __emif_tim_6678
{
	UINT32 wsetup:4;
	UINT32 wstrobe:6;
	UINT32 whold:3;
	UINT32 rsetup:4;
	UINT32 rstrobe:6;
	UINT32 rhold:3;
	UINT32 ta:3;
	UINT32 asize:1;
	UINT32 res0:2;
}EMIF_TIM_6678;
typedef union __emif_tim_xx
{
	UINT32 emifTim;
	EMIF_TIM_6678 emifTim6678;
}EMIF_TIM_XX;
typedef struct _emif_parameter
{
	UINT32 emifParamtertFlag;	//EMIF参数状态标志，用以区分默认还是新设置
	UINT32 emifBaseAddr;		//EMIF基地址
	UINT32 emifBusSize;			//EMIF总线宽度
	EMIF_TIM_XX emifTim;		//EMIF的时序参数
}EMIF_PARAMETER;

/*global declarations*/

/*defines*/

/* function declaration */

IMPORT INT32 dsp667x_emifInit(void* pCfg);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__EMIF_DSP6678__*/

