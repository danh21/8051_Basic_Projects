#include <reg51.H>
#include "LCD_16x2_4bit.h"
#include "ADC0808.h"



void configTimer()
{
	TMOD = 0x02;							// timer0 auto reload 8-bit
	TH0 = TL0 = 236;						// 20us -> overflow
	TR0 = 1;								// start operation of timer0
}



void configInt()
{
	EA = 1;									// enable global interrupt
	ET0 = 1;								// enable timer0 interrupt	
}



void ISR_Timer0() interrupt 1 {
	ADC0808_CLK = ~ADC0808_CLK;				// create clk for ADC0808 
}



void displayTemp(uchar temp, uchar channel) {
	lcd_sendStr("T = ");
	lcd_sendData(temp / 100 + '0');			// hundreds
	lcd_sendData(temp % 100 / 10 + '0');	// dozens
	lcd_sendData(temp % 10 + '0');			// units
	lcd_sendData(223);						// degrees
	lcd_sendData('C');
}



void main() {
	uchar temp;

	configTimer();
	configInt();

	lcd_init();							
	delay_ms(200);
	lcd_sendStr("MEASURING ...");
	delay_ms(1000);
	lcd_clear();
		
	while(1)
	{
		lcd_movCur(1, 3);
		temp = ADC0808_Read(0);	 			// channel 0 
		displayTemp(temp);
		delay_ms(500);
	}
}