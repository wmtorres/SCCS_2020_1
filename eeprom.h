#ifndef __EEPROM_H
#define ___EEPROM_H

#include "Config.h"


void Init_EEPROM(void);
unsigned char EEPROM_ReadByte (unsigned char MemoryAddress);
void EEPROM_WriteByte (unsigned char WriteMemoryAddress, unsigned char WriteData);


#endif	/* EEPROM_H */

