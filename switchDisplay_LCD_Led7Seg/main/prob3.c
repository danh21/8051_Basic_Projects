#include <reg51.h>
#include "LCD_16x2_4bit.h"
#include "7Seg8Dig_Anode.h"



char toggle = 1;					// init LCD on, 7seg off

uchar scanState = led7seg_off;		// init 7seg off

uchar id[8] = {1, 9, 1, 1, 9, 1, 6, 0}; 



void configTimer()
{
	TMOD = 0x05; 					// select counter mode for 16-bit timer0
	TR0 = 1; 						// start operation of timer0
	TH0 = 0xff;						// high byte of timer0															
	TL0 = 0xff;				    	// low byte of timer0	
}



void configInt()
{
	IE = 0x82; 						// enable global interrupt and timer0 interrupt	
}



void ISR_T0() interrupt 1  			// timer0 interrupt
{
	toggle = ~toggle;

	if (toggle == 1) {			
		lcd_onScreen();
		scanState = led7seg_off;		   	// Led7Seg off
		delay_ms(1);	
	}
	else {		   				
		lcd_offScreen(); 		   
		scanState = led7seg_dig8;		   	// Led7Seg can scan digits
		delay_ms(1);
	}
   	
	TH0 = 0xFF;																				
	TL0 = 0xFF;				    
}



void main(void)
{
	int i, j;
	
	configTimer();
	configInt();
				
	lcd_init();
	lcd_movCur(1, 1);
	lcd_sendStr("PHAN CONG DANH");
	lcd_movCur(2, 1);
	lcd_sendStr("19119160");
	
	while(1) {											// scan 8 leds 7seg	
		for (j = 400; j > 0; j--) {
			Led7Seg_scan = scanState;  				
			for (i = led7seg_numOfDigs - 1; i >= 0; i--) {
				Led7Seg_data = dig[id[i]];
				delayScan(100);
				Led7Seg_scan = Led7Seg_scan << 1;
			}
		}	
	}
}