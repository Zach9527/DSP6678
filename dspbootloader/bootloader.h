/*
 * bootloader.h
 *
 *  Created on: 2016-3-31
 *      Author: YF
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#define MAKE32(H16,L16) (((UINT32)(L16)<<16)|((UINT32)(H16)))
/*多核启动时，需要考虑如下宏*/
/*The BOOT_MAGIC ADDRESS for each core is the last four words in the respective local L2*/
#define CORE0_BOOT_MAGIC_ADDR				(0x10800000+512*1024 -4)
#define COREX_BOOT_MAGIC_ADDR(coreId) 		(CORE0_BOOT_MAGIC_ADDR+0x1000000*(coreId))

#define DSP_CORE_NUM						(1)
#define DSP_CORE_BOOT_MASK				    (0x1)


#define BOOTLOADER_PROGRAM_ADDR		(0x0)							/*BootLoader 程序在FLASH中的起始地址*/
#define BOOTLOADER_PROGRAM_SIZE		(128*1024)						/*BootLoader 程序所占FLASH空间*/

#define APPRUN_PROGRAM_ADDR			(BOOTLOADER_PROGRAM_ADDR+BOOTLOADER_PROGRAM_SIZE)
#define APPRUN_PROGRAM_SIZE			(4*1024*1024)

#define BOOT_GLOBAL_ADDR(addr,corid) ((Uint32)addr<0x1000000?\
						(Uint32)addr+(0x10000000+corid*0x1000000):\
						(Uint32)addr)

/*typedef*/
typedef void (*BJUMPFUNC)(void);

#endif /* BOOTLOADER_H_ */
