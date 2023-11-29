#ifndef MOTOR_H_
#define MOTOR_H_

// Define the enumeration for motor direction
typedef enum {
    DIRECTION_CW,
    DIRECTION_CCW
} tenuDirection;

void DC_Init();
void DC_Start(unsigned char MotorID, tenuDirection Direction, unsigned char Speed);
void DC_Stop(unsigned char MotorID);

#endif
