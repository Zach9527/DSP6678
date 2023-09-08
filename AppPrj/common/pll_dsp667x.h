/*

 �ļ����ƣ�clock_dsp6678.h
ժҪ��
*/
/* �޸���ʷ:

*/

#ifndef __CLOCK_DSP6678__
#define __CLOCK_DSP6678__

#ifdef __cplusplus
extern "C" {
#endif

/*include*/
#include "datatype.h"
/*typedef*/
typedef struct _pll_parameter
{
	UINT32 pllParamtertFlag; //PLL����״̬��־����������Ĭ�ϻ���������
	UINT32 crystalFreq;		 //����Ƶ��
	UINT32 coreFreq;		 //coreƵ��
}PLL_PARAMETER;

/*global declarations*/

/*defines*/

/* function declaration */
extern INT32 dsp667x_pllInit(void* pCfg);
extern unsigned int getcore_clk ();

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__CLOCK_DSP6678__*/


