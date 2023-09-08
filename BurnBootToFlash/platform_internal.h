/* ========================================================================== */
/**
 *  @file   platform_internal.h
 *
 *  @brief  Private definitions for the Platform Library.
 *
 *  ============================================================================
 */
/* --COPYRIGHT--,BSD
 * Copyright (c) 2011, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

#ifndef PLATFORM_INTERNAL_H_
#define PLATFORM_INTERNAL_H_

/********************************************************************************************
 * 					BUILD OPTIONS FOR THE LIBRARY											*
 *******************************************************************************************/

/***
 * @brief  The following flags are used for controlling the build of Platform Library
 */

/*  brief Platform Library version number */
#define PLATFORM_LIB_VERSION "2.00.00.10"

/* Turn on and off debug statements (may not be safe in certain contexts) */
#define	PLATFORM_DEBUG	0

/* These flags compile in and out functionality offered by the library allowing you to control
 * the size of the code that is included.
 */
#ifdef _PLATFORM_LITE_
	/*
	 * Build a version of Platform Library suitable for use in an EEPROM or other small application.
	 * (likely needs tailoring to the specific application if size matters)
	 */
	#define	PLATFORM_VERSTRING_IN		1
	#define	PLATFORM_INIT_IN			1
	#define	PLATFORM_GETINFO_IN			1
	#define PLATFORM_GETCOREID_IN		1
	#define PLATFORM_GETSWITCHSTATE_IN	0
	#define PLATFORM_GETMACADDR_IN		1
	#define PLATFORM_GETPHYADDR_IN		0
	#define PLATFORM_PHYLINKSTATUS_IN	0
	#define PLATFORM_DELAY_IN			1
	#define PLATFORM_LED_IN				1
	#define PLATFORM_WRITE_IN			0
	#define	PLATFORM_EXTMEMTEST_IN		1
	#define PLATFORM_INTMEMTEST_IN		0
	#define	PLATFORM_EEPROM_IN			1
	#define	PLATFORM_EEPROM_WRITE_IN	1
	#define	PLATFORM_UART_IN			1
	#define	PLATFORM_NOR_IN				1
	#define	PLATFORM_NOR_READ_IN		1
	#define	PLATFORM_NOR_WRITE_IN		0
	#define PLATFORM_NAND_IN			1
	#define PLATFORM_NAND_READ_IN		1
	#define PLATFORM_NAND_WRITE_IN		0
	#define PLATFORM_SEMLOCK_IN			0
	#define PLATFORM_CACHE_IN			0
#else
	/*
	 * Build the FULL version of Platform Library
	 */
	#define	PLATFORM_VERSTRING_IN		1
	#define	PLATFORM_INIT_IN			1
	#define	PLATFORM_GETINFO_IN			1
	#define PLATFORM_GETCOREID_IN		1
	#define PLATFORM_GETSWITCHSTATE_IN	1
	#define PLATFORM_GETMACADDR_IN		1
	#define PLATFORM_GETPHYADDR_IN		1
	#define PLATFORM_PHYLINKSTATUS_IN	1
	#define PLATFORM_DELAY_IN			1
	#define PLATFORM_LED_IN				1
	#define PLATFORM_WRITE_IN			1
	#define	PLATFORM_EXTMEMTEST_IN		1
	#define PLATFORM_INTMEMTEST_IN		1
	#define	PLATFORM_EEPROM_WRITE_IN	1
	#define	PLATFORM_EEPROM_IN			1
	#define	PLATFORM_UART_IN			1
	#define	PLATFORM_NOR_IN				1
	#define	PLATFORM_NOR_READ_IN		1
	#define	PLATFORM_NOR_WRITE_IN		1
	#define PLATFORM_NAND_IN			1
	#define PLATFORM_NAND_READ_IN		1
	#define PLATFORM_NAND_WRITE_IN		1
	#define PLATFORM_SEMLOCK_IN			1
	#define PLATFORM_CACHE_IN			1
#endif

#if (PLATFORM_DEBUG && !PLATFORM_WRITE_IN)
#error	You must enable PLATFORM_WRITE to turn on DEBUG
#endif

#if (PLATFORM_DEBUG)
#define IFPRINT(x)   (x)
#else
#define IFPRINT(x)
#endif

/********************************************************************************************
 * 					Includes for the Library Routines										*
 *******************************************************************************************/

#include "types.h"
#include "ti/csl/csl_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ti/csl/csl_chip.h"
#include "ti/csl/csl_chipAux.h"
//#include "cslr_device.h"
//#include "cslr_psc.h"
//#include "csl_psc.h"


#include "ti/csl/csl_pscAux.h"
#include "ti/csl/csl_bootcfg.h"
#include "ti/csl/csl_bootcfgAux.h"

#include "ti/csl/csl_pllcAux.h"
#include "ti/csl/csl_xmcAux.h"
#include "evmc66x_pllc.h"

/********************************************************************************************
 * 					Platform Specific Declarations											*
 *******************************************************************************************/

/* Clock rate */
//#define PLATFORM_BASE_CLK_RATE_MHZ (100)

/* PREDIV */
#define PLATFORM_PLL_PREDIV_val (1)

/* POSTDIV */
#define PLATFORM_PLL_POSTDIV_val (2)

/* Default PLL PLLM value (100/1*(20/2)) = 1.0GHz) */
#define  PLATFORM_PLL1_PLLM_val (20)

/* Default PLL PLLD value for 1.0GHz) */
#define  PLATFORM_PLL1_PLLD_val (1)


/* 1/x-rate clock for CorePac (emulation) and the ADTF module */
#define  PLATFORM_PLLDIV2_val  (3)
/* 1/y-rate clock for system trace module only */
#define  PLATFORM_PLLDIV5_val (5)
/* 1/z-rate clock is used as slow_sysclck in the system */
#define  PLATFORM_PLLDIV8_val (64)

/* Number of cores on the platform */
#define PLATFORM_CORE_COUNT 8

#endif
