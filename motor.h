#ifndef MOTOR_H_
#define MOTOR_H_

void DC_Init();
void DC_Start_CW(unsigned char MotorID, unsigned char Speed);
void DC_Start_CCW(unsigned char MotorID, unsigned char Speed);
void DC_Stop(unsigned char MotorID);

#endif
