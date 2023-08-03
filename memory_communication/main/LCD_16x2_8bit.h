/* ---------------------------------------------------------- LIBRARY ---------------------------------------------------------- */
#include <reg51.h>
#include <math.h>



/* ------------------------------------------------------ PIN CONNECTION ------------------------------------------------------- */
sbit LCD_RS = P1^4; 	// register select (0 - command, 1 - data)							
sbit LCD_RW = P1^5; 	// read/write select (0 - write, 1 - read)						
sbit LCD_EN = P1^3; 	// operation (read/write) enable						
#define LCD_DATA P0		// data



/* ---------------------------------------------------------- MACRO ------------------------------------------------------------ */
#define uchar unsigned char
#define uint unsigned int

#define LCD_numOfCols 16	// number of columns
#define LCD_numOfRows 2		// number of rows



/* ---------------------------------------------------------- PROTOTYPE ---------------------------------------------------------- */
// delay in ms
void delay_ms(uint ms);

// enable to read or write data
void lcd_enable(void);

// send 8-bit data
void lcd_sendData(uchar Data);

// send 8-bit command
void lcd_sendCmd(uchar command);

// clear screen
void lcd_clear(void);

// turn on screen, turn off cursor
void lcd_onScreen(void);

// turn off screen
void lcd_offScreen(void);

// initialize LCD
void lcd_init(void);

// move cursor to specific location by DDRAM address
void lcd_movCur(uchar row, uchar column);

// turn on blinking cursor
void lcd_blinkCur(void);

// turn off blinking cursor
void lcd_off_blinkCur(void);

// send string
void lcd_sendStr(uchar* string);

// send integer number
void lcd_sendInt(uint value);

// send decimal point number
void lcd_sendFloat(float value, uint precision);



/* ---------------------------------------------------------- FUNCTION ---------------------------------------------------------- */
void delay_ms(uint ms)													
{
	uint i, j;
	for (i = 0; i < ms; i++)
		for (j = 0; j < 123; j++); 					
}



void lcd_enable()									
{
	LCD_EN = 1;										// high to low transition
	delay_ms(1);
	LCD_EN = 0;	
	delay_ms(1);
}



void lcd_sendData(uchar Data)						
{
	LCD_RW = 0; 									// select write mode
	LCD_RS = 1; 									// select data register
	LCD_DATA = Data;	
	lcd_enable();									
}



void lcd_sendCmd(uchar cmd)							
{
	LCD_RW = 0; 									
	LCD_RS = 0; 									// select command register
	LCD_DATA = cmd;								
	lcd_enable();																		
}



void lcd_clear()									
{
	lcd_sendCmd(0x01);																
}



void lcd_onScreen()									
{
	lcd_sendCmd(0x0C);
}



void lcd_offScreen()								
{
	lcd_sendCmd(0x08);
}



void lcd_init()										
{
	LCD_RS = 0;										
	LCD_RW = 0;										
	delay_ms(20); 									// LCD Power ON Initialization time > 15ms
	lcd_sendCmd(0x38); 								// 8-bit mode, 2 lines, 5x8 pixel
	lcd_onScreen();
	lcd_sendCmd(0x06); 								// increase cursor
	lcd_clear();
}



void lcd_movCur(uchar row, uchar column)			
{
	switch (row)
	{
		case 1:
			lcd_sendCmd(0x80 | (column - 1));		// 0x00 | 0x80	 		
			break;
		case 2: 
			lcd_sendCmd(0xC0 | (column - 1));		// 0x40 | 0x80
			break;
		default: 
			break;
	}
}



void lcd_blinkCur()									
{
	lcd_sendCmd(0x0F);
}



void lcd_off_blinkCur()								
{
	lcd_sendCmd(0x0E);
}



void lcd_sendStr(uchar *string)						
{
	while (*string)									
		lcd_sendData(*string++);
}



void lcd_sendInt(uint value)						
{
	uchar buffer[LCD_numOfCols], i = 0;

	do {
		buffer[i++] = (value % 10) + '0'; 			// convert number to character
		value /= 10;							
	} while (value);
	
	while (i)										
		lcd_sendData(buffer[--i]);
}



void lcd_sendFloat(float value, uint precision)		
{
	uint integer, fractional;
										
	integer = (uint)value;						
	fractional = (value - integer) * pow(10, precision);		
	
	lcd_sendInt(integer);								
	lcd_sendData('.');									
	lcd_sendInt(fractional);								
}