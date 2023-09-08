
/*******************************************************************************
*    Copyright Description:   Copyright (C),2022,ORC electronic co.Ltd
*    File Name:               DDR_NormalTest.c
*    Author:                  handsome Yang
*    Version:                 V1。00
*    Date:                    2022-12-27
*    Description:
*    Other:
*    Function List:
*    History:
*******************************************************************************/


#ifndef DDR_NORMALTEST_H_
#define DDR_NORMALTEST_H_

#include "dataType.h"

#define DDR_WRITE8(addr,value) 		*((volatile UINT8 *) (addr)) = value
#define DDR_READ8(addr)				(*(volatile UINT8 *) (addr))
#define DDR_WRITE16(addr,value) 	*((volatile UINT16 *)(addr)) = value
#define DDR_READ16(addr)			(*(volatile UINT16 *)(addr))
#define DDR_WRITE32(addr,value) 	*((volatile UINT32 *)(addr)) = value
#define DDR_READ32(addr)			(*(volatile UINT32 *)(addr))
#define DDR_WRITE64(addr,value) 	*((volatile UINT64 *)(addr)) = value
#define DDR_READ64(addr)			(*(volatile UINT64 *)(addr))

static INT32 ddrDataNormalTest(UINT32 dataBit, UINT32 offAddr, UINT32 testLen);
static INT32 ddrAddrNormalTest(UINT32 offAddr, UINT32 testLen);
static INT32 ddrStorageNormalTest(UINT32 offAddr, UINT32 testLen);

extern INT32 ddrTest(UINT32 ddrDataBit, UINT32	ddrOffAddr, UINT32 ddrTestLen);

#endif /* DDR_NORMALTEST_H_ */

