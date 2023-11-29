#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#define EEPROM_ADDR_TEMP 0 // Omar Change this address to the specific EEPROM address for temperature as well

void eeprom_custom_write_byte(uint16_t addr, uint8_t data);
uint8_t eeprom_custom_read_byte(uint16_t addr);

#endif
