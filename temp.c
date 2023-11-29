#include "temp.h"
#include "LCD.h"
#include "Keypad.h"
#include "motor.h"
#include "i2c.h"


#define I2C_TEMPERATURE_REGISTER 0x00 // Omar Replace this with the actual register address for temperature

float readTemperature() {
    // Start I2C communication
    i2cStart();

    // Select the I2C device and write the register address
    i2cWrite((I2C_DEVICE_ADDRESS << 1) | I2C_WRITE);
    i2cWrite(I2C_TEMPERATURE_REGISTER);

    // Select the I2C device and read the temperature
    i2cWrite((I2C_DEVICE_ADDRESS << 1) | I2C_READ);
    
    // Read temperature MSB (Most Significant Byte)
    uint8_t msb = i2cReadACK();

    // Read temperature LSB (Least Significant Byte)
    uint8_t lsb = i2cReadNACK();

    // Stop I2C communication
    i2cStop();

    // Combine MSB and LSB to get the temperature value
    int16_t temperatureRaw = (msb << 8) | lsb;

    // Convert the raw temperature value to a floating-point value (abdelrahman adjust this according to the sensor's data format from the data sheet)
    float temperature = temperatureRaw / 256.0;

    return temperature;
}


float getTemperatureInput() {
    char key;
    do {
        key = Keypad_ReadKey(); // Keep reading until a valid key is pressed
    } while (key == '\0');

    return key - '0'; // Convert char to int (assuming single-digit input)
}

void displayParameters(float temperature) {
    updateLCD(temperature, 0.0); // Assuming the upper limit is not used here until we decide the final application
}
