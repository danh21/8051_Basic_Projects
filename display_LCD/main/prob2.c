#include <reg51.h>					
#include "LCD_16x2_4bit.h"



uint count = 0;	 

// code - constant
uchar code string[]	= "COMPUTER ENGINEERING TECHNOLOGY - HCMC UNIVERSITY OF TECHNOLOGY AND EDUCATION. ";	



void configTimer()
{
	TMOD = 0x05; 				// select counter mode for 16-bit timer0 
	TR0 = 1; 					// start timer0
	TH0 = 0xFF;					// higher byte 															
	TL0 = 0xFF;				    // lower byte	
}

void configInt()
{
	IE = 0x82;					// enable global and timer0 interrupt	
}

void ISR_Timer0() interrupt 1 	// ISR for counter
{
	count++;	
	TH0 = 0xFF;																	
	TL0 = 0xFF;			
}



void main (void)
{
	uchar i, traversal = 0, start = 0;
	
	configTimer();
	configInt();

	lcd_init();

	while (1) 					
	{
		lcd_movCur(2, 1);
		lcd_sendInt(count);

		lcd_movCur(1, 1);
		traversal = start;
		for (i = 0; i < LCD_numOfCols; i++) {
			lcd_sendData(string[traversal++]);
			if (traversal == sizeof(string)/sizeof(uchar) - 1) 	// NULL
				traversal = 0;							
		}
		if (start++ == sizeof(string)/sizeof(uchar) - 1)		// NULL
				start = 0;

		delay_ms(100);
	}
}