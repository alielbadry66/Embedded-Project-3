#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>
#include "IntegerToString.h"


#define LCD_Dir DDRD
#define LCD_Port PORTD
#define RS_EN_Dir DDRB
#define RS_EN_Port PORTB
#define RS PB0
#define EN PB1

void LCD_Command(unsigned char cmnd) {
    LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0);
    RS_EN_Port &= ~(1 << RS);
    RS_EN_Port |= (1 << EN);
    _delay_us(1);
    RS_EN_Port &= ~(1 << EN);
    _delay_us(200);
    LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);
    RS_EN_Port |= (1 << EN);
    _delay_us(1);
    RS_EN_Port &= ~(1 << EN);
    _delay_ms(2);
}

void LCD_Char(unsigned char data) {
    LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0);
    RS_EN_Port |= (1 << RS);
    RS_EN_Port |= (1 << EN);
    _delay_us(1);
    RS_EN_Port &= ~(1 << EN);
    _delay_us(200);
    LCD_Port = (LCD_Port & 0x0F) | (data << 4);
    RS_EN_Port |= (1 << EN);
    _delay_us(1);
    RS_EN_Port &= ~(1 << EN);
    _delay_ms(2);
}

void LCD_Init(void) {
    LCD_Dir = 0xFF;
    RS_EN_Dir |= (1 << EN) | (1 << RS);
    _delay_ms(20);
    LCD_Command(0x02);
    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Command(0x01);
    _delay_ms(2);
}

void LCD_String(char *str) {
    int i;
    for (i = 0; str[i] != 0; i++) {
        LCD_Char(str[i]);
    }
}

void LCD_Clear() {
    LCD_Command(0x01);
    _delay_ms(2);
    LCD_Command(0x80);
}

void updateLCD(float temperature, float upperLimit) {
    LCD_Clear();
    LCD_String("Temp: ");
    char tempStr[16];
    int temperatureInt = (int)temperature;
    integerToString(temperatureInt, tempStr);
    LCD_String(tempStr);

    LCD_Command(0xC0);
    LCD_String("Upper: ");
    
    char upperLimitStr[16];
    int upperLimitInt = (int)upperLimit;
    integerToString(upperLimitInt, upperLimitStr);
    LCD_String(upperLimitStr);
}
