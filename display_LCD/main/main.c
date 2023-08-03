#include <reg51.h>
#include "LCD_16x2_4bit.h"



void main()											
{
	uint count;
	float number = 21.12;

	lcd_init();	
	
	while (1) {
	  	lcd_movCur(1, 2);							
		lcd_sendStr("PHAN CONG DANH");
	
		lcd_movCur(2, 2);								
		lcd_sendStr("19119160 SPKT");
	
		delay_ms(1000);
		lcd_clear();
										
		lcd_movCur(2, 2);								
		lcd_sendStr("A FLOAT: ");
		lcd_movCur(2, 11);					
		lcd_sendFloat(number, 2);
	
		lcd_movCur(1, 2);								
		lcd_sendStr("COUNT = ");
		for (count = 0; count < 22; count++) 
		{
			lcd_movCur(1, 10);						
			lcd_sendInt(count);														
			delay_ms(100);		
		}

		delay_ms(1000);
		lcd_clear();
	}									
}