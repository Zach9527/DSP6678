/*

 文件名称：clock_dsp6678.h
摘要：
*/
/* 修改历史:

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
	UINT32 pllParamtertFlag; //PLL参数状态标志，用以区分默认还是新设置
	UINT32 crystalFreq;		 //晶振频率
	UINT32 coreFreq;		 //core频率
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


