/*

 �ļ����ƣ�ddr_dsp6678.h
ժҪ��
*/
/* �޸���ʷ:

2016.3.19,chengqb�����ļ�
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

//�ýṹ�����ڽ���ɢ�Ĳ������л�
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
	UINT32 ddrParamtertFlag;	//DDR����״̬��־����������Ĭ�ϻ���������
	UINT32 ddrTotalSize;		//DDR�ڴ�����
	UINT16 ddrBusSize;			//DDR���߿��
	UINT16 ddrPageSize;			//DDRҳ��С
	UINT16 ddrBankNum;			//DDR��bank����
	UINT16 ddrRowNum;			//DDR��ROW����
	DDR_TIM1_XX ddrTim1;		//DDR��ʱ�����1
	DDR_TIM2_XX ddrTim2;		//DDR��ʱ�����2
	DDR_TIM3_XX ddrTim3;		//DDR��ʱ�����2(6678only)
	DDR_OTHERS ddrOthers;		//�������л�
}DDR_PARAMETER;

/*global declarations*/

/*defines*/

/* function declaration */
IMPORT INT32 dsp667x_ddrInit(void* pCfg);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__DDR_DSP6746__*/

