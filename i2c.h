#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define F_CPU 16000000UL // Adjust according to your clock frequency
#define I2C_BAUD_RATE 100000UL // Adjust this value based on your requirements (e.g., 100 kHz)
#define I2C_DEVICE_ADDRESS 0x50 // Replace with the actual device address
#define I2C_WRITE ((I2C_DEVICE_ADDRESS << 1) | 0)
#define I2C_READ  ((I2C_DEVICE_ADDRESS << 1) | 1)

void i2cInit();
void i2cStart();
void i2cStop();
void i2cWrite(uint8_t data);
uint8_t i2cReadACK();
uint8_t i2cReadNACK();

#endif // I2C_H
