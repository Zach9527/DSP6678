
/* includes */ 
#include <c6x.h>
#include "datatype.h"
#include "delay.h"
#include "dsp667x.h"
  
/* defines */ 
	

/* typedefs */  

/* globals */ 

/* locals */

/* local function declarations */

/*global function define*/ 
void dsp667x_bootCfgLock(void)
{
	CSL_BootCfgLockKicker();
}

void dsp667x_bootCfgUnLock(void)
{

	CSL_BootCfgUnlockKicker();
	/* Wait for Stabilization time (min 100 us)                                *
     * The below loop is good enough for the Gel file to get minDrvLib.cfgimum of        *
     * 100 micro seconds, this should be appropriately modified for port       *
     * to a C function                                                         *
     * Minimum delay in GEL can be 1 milli seconds, so program to 1ms=1000us,  *
     * more than required, but should be Okay                                  */    
	delay(140056/5);	
}


/*local function define*/


