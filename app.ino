#include <avr/io.h>
#include "uart.h"
#include "uart.c"
#include "temp.h"
#include "temp.c"
#include "eeprom.h"
#include "eeprom.c"
#include "LCD.h"
#include "LCD.c"
#include "Keypad.h"
#include "Keypad.c"
#include "motor.h"
#include "motor.c"
#include "pwm.h"
#include "pwm.c"
#include "IntegerToString.h"
#include "IntegerToString.c"
#include <util/delay.h>

// Define EEPROM addresses
#define EEPROM_ADDR_TEMP 0
#define EEPROM_ADDR_TARGET_TEMP 1

int main() {
    // Initialize system components
    LCD_Init();      // Initialize LCD
    Keypad_Init();   // Initialize Keypad
    DC_Init();       // Initialize DC Motor Control
    uart_init(9600); // Initialize UART with baud rate 9600
    
    // Read last temperature and target temperature from EEPROM
    float lastTemperature = eeprom_custom_read_byte(EEPROM_ADDR_TEMP);
    float targetTemperature = 20.0; 

    // Initialize the temperature sensor
    initTemperatureSensor();

    while (1) {
        // Read current temperature
        float temperatureInput = readTemperature();

        // Update LCD with current and target temperatures
        updateLCD(temperatureInput, targetTemperature);

        // Check for Keypad input to adjust target temperature
        char keypadInput = Keypad_ReadKey();
        if (keypadInput == '2') {
            targetTemperature += 1.0;  // Increase target temperature
            // Save the new target temperature to EEPROM
            eeprom_custom_write_byte(EEPROM_ADDR_TARGET_TEMP, targetTemperature);
        } else if (keypadInput == '1') {
            targetTemperature -= 1.0;  // Decrease target temperature
            // Save the new target temperature to EEPROM
            eeprom_custom_write_byte(EEPROM_ADDR_TARGET_TEMP, targetTemperature);
        }

        // Control DC motor based on UART input for motor direction
        if (uart_receive_ready()) {
            char uartInput = uart_receive_char();
            if (uartInput == 'H') {
                DC_Start_CCW(0, 100); // Anti-clockwise direction at full speed
                uart_send_string("Heating Mode On\n");
            } else if (uartInput == 'C') {
                DC_Start_CW(0, 100); // Clockwise direction at full speed
                uart_send_string("Cooling Mode On\n");
            } else {
                DC_Stop(0); // Stop the motor for any other input
            }
        } else {
            // Calculate the speed based on the temperature difference
            float tempDifference = targetTemperature - temperatureInput;
            unsigned char speed = (unsigned char)(tempDifference * 2.0);

            // Adjust the speed to be within the valid range (0 to 100)
            if (speed > 100) {
                speed = 100;
            } else if (speed < 0) {
                speed = 0;
            }

            // Start or stop the motor based on the temperature difference
            if (tempDifference > 0.0) {
                DC_Start_CCW(0, speed); // Anti-clockwise direction
            } else if (tempDifference < 0.0) {
                DC_Start_CW(0, speed); // Clockwise direction
            } else {
                DC_Stop(0);
            }
        }

        _delay_ms(1000);  // Delay for a second to make the temperature adjustment smoother
    }

    return 0;
}
