#include "temp.h"
#include "eeprom.h"
#include "LCD.h"
#include "Keypad.h"
#include "motor.h"
#include "i2c.h"
#include <util/delay.h>
#include <avr/io.h>

// Define EEPROM addresses
#define EEPROM_ADDR_TEMP 0

int main() {
    // Initialize system components
    LCD_Init();      // Initialize LCD
    Keypad_Init();   // Initialize Keypad
    DC_Init();       // Initialize DC Motor Control
    i2cInit();       // Initialize I2C communication

    // Read last temperature from EEPROM
    float lastTemperature = eeprom_custom_read_byte(EEPROM_ADDR_TEMP);

    while (1) {

        // Read temperature and update the LCD
        float temperatureInput = readTemperature();
        updateLCD(temperatureInput, lastTemperature);

        // Save the current temperature to EEPROM
        eeprom_custom_write_byte(EEPROM_ADDR_TEMP, temperatureInput);

        // Control DC motor based on temperature
        if (temperatureInput > 30.0) {
            DC_Start(0, DIRECTION_CW, 50); // Motor ID 0, CW direction, Speed 50
        } else {
            DC_Stop(0); // Stop the motor
        }

        // Other application logic will be added by abdelrahman and omar...

    }

    return 0;
}
