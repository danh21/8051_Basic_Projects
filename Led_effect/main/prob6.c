#include <at89x51.h>



#define leds P1

#define uint unsigned int
#define uchar unsigned char



void delay_hardware_50ms()
{	
	TMOD = 0x01;						// 16-bit timer0 (0 - 65535)
	ET0 = 0;							// no interrupt
	TH0 = 0x3C;							// 0x3CB0 ~ 15536 -> 65535-15536+1 = 50000us = 50ms	
	TL0 = 0xB0;							
	TF0 = 0; 							// clear overflow flag	
	TR0 = 1; 							// start timer0
	while (TF0 == 0);					// wait until overflow
	TR0 = 0; 							// stop timer0	
}



void delay_ms(int ms)
{
	int i;
	for (i = 0; i < ms/50; i++)	   	
		delay_hardware_50ms();
}



void blink(uchar times)		    
{
	uchar i;
	for (i = 0; i < times; i++)
	{
		leds = 0xFF;	
		delay_ms(500);
		leds = 0; 		
		delay_ms(500);
	}
}



void interleave(uchar times)
{
	uchar i;						  
	for (i = 0; i < times; i++)
	{
		leds = 0x55; 
		delay_ms(500);	  		  	//01010101
		leds = 0xAA; 
		delay_ms(500);	          	//10101010
	}
}



void runR2L(uchar times)			// right to left
{
	uchar i, j;
	for (i = 0; i < times; i++)
	{
		for (j = 0; j < 8; j++) {
			leds = (1 << j);
			delay_ms(500);
		}
	}
}



void runL2R(uchar times)			// left to right			 
{
	uchar i, j;
	for (i = 0; i < times; i++)
	{
		for (j = 0; j < 8; j++) {
			leds = (0x80 >> j);
			delay_ms(500);
		}
	}
}



void run2directs(uchar times)
{
	uchar i, j;
	for (i = 0; i < times; i++)
	{
		for (j = 0; j < 4; j++) {
			leds = (0x80 >> j) | (1 << j);
			delay_ms(500);
		}
		for (j = 1; j < 4; j++) {
			leds = (0x08 >> j) | (0x10 << j);
			delay_ms(500);
		}
	}
}



void main()								  
{ 
	while (1)
	{ 
		blink(5);
		runR2L(1);
		runL2R(1);		
		interleave(3);
		run2directs(1);
	}
}