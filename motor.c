#include "motor.h"
#include <avr/io.h>

#define PWM_PIN 0 // Define PWM PIN 
#define DIR_PIN 3 // Define DIR PIN

unsigned char MotorArray[][2] = {
    {PWM_PIN, DIR_PIN} // Motor 0: {PWM_pin, Direction_pin}
};

void DC_Init() {
    // Set the motor pins as outputs
    DDRD |= (1 << MotorArray[0][PWM_PIN]) | (1 << MotorArray[0][DIR_PIN]);

    // Initialize the PWM module
    PWM_init();
}

void DC_Start(unsigned char MotorID, tenuDirection Direction, unsigned char Speed) {
    // Set the direction pin
    if (Direction == DIRECTION_CW) {
        PORTD |= (1 << MotorArray[MotorID][DIR_PIN]);
    } else {
        PORTD &= ~(1 << MotorArray[MotorID][DIR_PIN]);
    }

    // Start the motor by applying PWM and define speed
    Set_DutyCycle(Speed);
}

void DC_Stop(unsigned char MotorID) {
    // Stopping the motor by turning off the PWM and direction pins
    Set_DutyCycle(0);
    PORTD &= ~(1 << MotorArray[MotorID][DIR_PIN]);
}
