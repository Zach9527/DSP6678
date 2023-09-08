/*

 �ļ����ƣ�emif_dsp6678.h
ժҪ��
*/
/* �޸���ʷ:

2016.3.19,chengqb�����ļ�
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
	UINT32 emifParamtertFlag;	//EMIF����״̬��־����������Ĭ�ϻ���������
	UINT32 emifBaseAddr;		//EMIF����ַ
	UINT32 emifBusSize;			//EMIF���߿��
	EMIF_TIM_XX emifTim;		//EMIF��ʱ�����
}EMIF_PARAMETER;

/*global declarations*/

/*defines*/

/* function declaration */

IMPORT INT32 dsp667x_emifInit(void* pCfg);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__EMIF_DSP6678__*/

