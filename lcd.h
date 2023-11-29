#ifndef LCD_H
#define LCD_H


void LCD_Init();
void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char data);
void LCD_String(char *str);
void LCD_Clear();
void updateLCD(float temperature, float upperLimit);

#endif // LCD_H
