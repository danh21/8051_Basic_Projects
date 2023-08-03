#include <REGX51.H>



#define leds P2

#define uint unsigned int
#define uchar unsigned char



void delay_ms(uint ms) 
{
	uint i, j;
	for (i = 0; i < ms; i++)
		for (j = 0; j < 123; j++);
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
		blink(3);
		runR2L(1);
		runL2R(1);		
		interleave(3);
		run2directs(1);
	}
}