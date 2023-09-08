#include"datatype.h"
#include"c6x.h"



/***********************************************************************
 * ��������GetCurSysTime_D
 * ���ܣ���ȡ��ǰ��ϵͳʱ�� ��λΪns
 * �����������
 * �����������
 * ����ֵ����
 * ˵��    ��
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
