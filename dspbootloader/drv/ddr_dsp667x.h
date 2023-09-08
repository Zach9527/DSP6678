/*

 文件名称：ddr_dsp6678.h
摘要：
*/
/* 修改历史:

2016.3.19,chengqb创建文件
*/

#ifndef __DDR_DSP6678__
#define __DDR_DSP6678__

#ifdef __cplusplus
extern "C" {
#endif

/*include*/
#include"datatype.h"
/*typedef*/

typedef struct _ddr_tim1_6678
{
	UINT32 t_wtr:3;
	UINT32 t_rrd:3;
	UINT32 t_rc:6;
	UINT32 t_ras:5;
	UINT32 t_wr:4;
	UINT32 t_rcd:4;
	UINT32 t_rp:4;
	UINT32 res0:3;
}DDR_TIM1_6678;
typedef union _ddr_tim1_xx
{
	UINT32 ddrTim1;
	DDR_TIM1_6678 ddrTim16678;
}DDR_TIM1_XX;
typedef struct _ddr_tim2_6678
{
	UINT32 t_cke:3;
	UINT32 t_rtp:3;
	UINT32 t_xsrd:10;
	UINT32 t_xsnr:9;
	UINT32 res0:3;
	UINT32 t_xp:3;
	UINT32 res1:1;
}DDR_TIM2_6678;
typedef union _ddr_tim2_xx
{
	UINT32 ddrTim2;
	DDR_TIM2_6678 ddrTim26678;
}DDR_TIM2_XX;

typedef struct _ddr_tim3_6678
{
	UINT32 t_ras_max:4;
	UINT32 t_rfc:9;
	UINT32 res0:2;
	UINT32 zq_zqcs:6;
	UINT32 t_ckesr:3;
	UINT32 t_csta:4;
	UINT32 t_pdll_ul:4;
}DDR_TIM3_6678;
typedef union _ddr_tim3_xx
{
	UINT32 ddrTim3;
	DDR_TIM3_6678 ddrTim36678;
}DDR_TIM3_XX;

//该结构体用于将分散的参数集中化
typedef struct __ddr_others_6678
{
	UINT32 pageSize:2;
	UINT32 bankNum:2;
	UINT32 rowNum:3;
	UINT32 busSize:2;
	UINT32 res0:13;
}DDR_OTHERS_6678;

typedef union __ddr_others
{
	DDR_OTHERS_6678 others6678;
}DDR_OTHERS;
typedef struct _ddr_parameter
{
	UINT32 ddrParamtertFlag;	//DDR参数状态标志，用以区分默认还是新设置
	UINT32 ddrTotalSize;		//DDR内存容量
	UINT16 ddrBusSize;			//DDR总线宽度
	UINT16 ddrPageSize;			//DDR页大小
	UINT16 ddrBankNum;			//DDR的bank数量
	UINT16 ddrRowNum;			//DDR的ROW数量
	DDR_TIM1_XX ddrTim1;		//DDR的时序参数1
	DDR_TIM2_XX ddrTim2;		//DDR的时序参数2
	DDR_TIM3_XX ddrTim3;		//DDR的时序参数2(6678only)
	DDR_OTHERS ddrOthers;		//参数集中化
}DDR_PARAMETER;

/*global declarations*/

/*defines*/

/* function declaration */
IMPORT INT32 dsp667x_ddrInit(void* pCfg);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__DDR_DSP6746__*/

