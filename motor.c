#include "motor.h"
#include <avr/io.h>
#include "pwm.h"

#define PWM_PIN 0 // Define PWM PIN 
#define DIR_PIN 1 // Define DIR PIN

// Define MotorArray 
unsigned char MyMotorArray[1][2];

void DC_Init() {
    MyMotorArray[0][0] = PWM_PIN;
    MyMotorArray[0][1] = DIR_PIN;

    // Set the motor pins as outputs
    DDRD |=  (1 << MyMotorArray[0][PWM_PIN]);
    DDRD |=  (1 << MyMotorArray[0][DIR_PIN]);
    // Initialize the PWM module
    PWM_init();
}

void DC_Start_CW(unsigned char MotorID, unsigned char Speed) {
    // Set the direction pin for clockwise movement
    PORTD |= (1 << MyMotorArray[MotorID][DIR_PIN]);
    
    // Start the motor by applying PWM and define speed
    Set_DutyCycle(Speed);
}

void DC_Start_CCW(unsigned char MotorID, unsigned char Speed) {
    // Set the direction pin for anti-clockwise movement
    PORTD &= ~(1 << MyMotorArray[MotorID][DIR_PIN]);
    
    // Start the motor by applying PWM and define speed
    Set_DutyCycle(Speed);
}

void DC_Stop(unsigned char MotorID) {
    // Stopping the motor by turning off the PWM and direction pins
    Set_DutyCycle(0);
    PORTD &= ~(1 << MyMotorArray[MotorID][DIR_PIN]);
}
