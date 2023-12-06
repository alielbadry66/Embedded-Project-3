#include <avr/io.h>
#include <stdint.h>
#include "temp.h"

// Define constants
#define TEMPERATURE_SENSOR_PIN 0   // Analog pin A0 on Arduino Uno

// Function to initialize the ADC
void initADC() {
    // Set reference voltage to AVCC and left-adjust result
    ADMUX = (1 << REFS0) | (1 << ADLAR);

    // Enable ADC, enable ADC interrupt, and set prescaler to 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// Function to read the temperature
uint16_t readADC() {
    // Select the ADC channel
    ADMUX = (ADMUX & 0xF8) | (TEMPERATURE_SENSOR_PIN & 0x07);
    
    // Start the conversion
    ADCSRA |= (1 << ADSC);
    
    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC));
    
    // Return the ADC result
    return ADC;
}

// Function to initialize the temperature sensor
void initTemperatureSensor() {
    // Initialize the ADC
    initADC();
}

// Function to read the temperature from the LM35 sensor
float readTemperature() {
    // Read the temperature from the LM35
    uint16_t adcValue = readADC();
    
    // Convert ADC value to temperature in Celsius
    float temperatureC = (adcValue * 0.48876) - 50.0;  // LM35 provides 10mV per degree Celsius
    
    return temperatureC;
}
