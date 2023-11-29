#include "I2C.h"
#include <stdint.h>
#include <avr/io.h>


void i2cInit() {
    TWSR = 0; // Set prescaler to 1
    TWBR = ((F_CPU / I2C_BAUD_RATE) - 16) / 2;
}

void i2cStart() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void i2cStop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2cWrite(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

uint8_t i2cReadACK() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

uint8_t i2cReadNACK() {
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}
