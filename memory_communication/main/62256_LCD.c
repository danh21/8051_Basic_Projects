#include <reg51.h>
#include "LCD_16x2_8bit.h"



uchar xdata *pp;						// data of external RAM

void write_ram(uint add, uchar dat)		// address, data 
{
	pp = 0x0000 + add;
	*pp = dat;
}

uchar read_ram(uint add)
{
	uchar dat;
	pp = 0x0000 + add;
	dat = *pp;
	return dat;
}



void main(void)
{
	uint i;
	uchar dat;
	uchar address[LCD_numOfCols] = "address:        ";
	uchar Data[LCD_numOfCols] 	 = "data:           ";

	for (i = 0; i < 32768; i++) 		// write data into external RAM 
		write_ram(i, i%256);
	
	lcd_init();
	lcd_movCur(1, 1);
	lcd_sendStr(address);
	lcd_movCur(2, 1);
	lcd_sendStr(Data);
	
	while(1) {
		for(i = 0; i < 32768; i++) { 	// read data from external RAM and display on LCD					
			dat = read_ram(i);
						
			lcd_movCur(1, 1);
			lcd_sendStr(address);
			lcd_movCur(1, 9);
			lcd_sendInt(i);	
			
			lcd_movCur(2, 1);
			lcd_sendStr(Data);
			lcd_movCur(2, 6);
			lcd_sendInt((uint)dat);
			
			delay_ms(1000);					
		}
	}
}