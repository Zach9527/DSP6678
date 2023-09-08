#include"datatype.h"
#include"c6x.h"



/***********************************************************************
 * 函数名：GetCurSysTime_D
 * 功能：读取当前的系统时间 单位为ns
 * 输入参数：无
 * 输出参数：无
 * 返回值：无
 * 说明    ：
 * **********************************************************************/
unsigned long long GetCurSysTime_D(void)
{
	unsigned long long timel=0;
	unsigned long long timeh=0;
	unsigned long long cursystime=0;

	timel=TSCL;
	timeh=TSCH;
	cursystime=(timeh<<32)+timel;
	return cursystime;
}




INLINE void delayOneUs(void)
{
	asm("	   nop	5");
}

INLINE void delayOnems(void)
{
	long long  time0,time1;
	UINT32     cost_time=0;
	time0=GetCurSysTime_D();

    while(1)
    {
    	time1=GetCurSysTime_D();
    	cost_time=time1-time0;
    	if((cost_time > 1000000 ) || (cost_time == 1000000))
    	{
    		break;
    	}

    }
    return ;

}


void delay(UINT32 unDelayCnt)
{
	while (unDelayCnt -- > 0 )
	{
		delayOneUs();
	}
}

void delay_ms(UINT32 ms_Cnt)
{
	while (ms_Cnt -- > 0 )
	{
		delayOnems();
	}
}
