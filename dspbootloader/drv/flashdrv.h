/*
 * flashdrv.h
 *
 *  Created on: 2023-1-5
 *      Author: ORC-C001
 */

#ifndef FLASHDRV_H_
#define FLASHDRV_H_

Uint32 SectorErase(Uint32 sectorNum);
void Program16Data(Uint32 addr, Uint16 data);
void OpenFastMode(void);
void ProgramFastMode(Uint32 addr, Uint16 data);
void CloseFastMode(void);
Uint32 program_boot_to_flash(void);
void s29glWrite16bit(Uint16 offset , Uint16 data);
void mt28ew256Reset();
void mt28ew256ChipErase();


#endif /* FLASHDRV_H_ */
