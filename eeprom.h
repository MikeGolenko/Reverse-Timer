


#ifndef EEPROM_H_
#define EEPROM_H_

#include "main.h"

void EEPROM_write(uint8_t uiAddress, uint8_t ucData);

uint8_t EEPROM_read(uint8_t uiAddress);



#endif /* EEPROM_H_ */