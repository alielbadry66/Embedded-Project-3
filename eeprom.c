#include "eeprom.h"

void eeprom_custom_write_byte(uint16_t addr, uint8_t data) {
    eeprom_write_byte((uint8_t*)addr, data);
}

uint8_t eeprom_custom_read_byte(uint16_t addr) {
    return eeprom_read_byte((uint8_t*)addr);
}
