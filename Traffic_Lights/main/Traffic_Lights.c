#include <reg51.H>
#include "7Seg4Dig_Anode.h"



sbit red1 	 = P0^0;			
sbit yellow1 = P0^1;
sbit green1  = P0^2;
sbit red2 	 = P0^3;
sbit yellow2 = P0^4;
sbit green2  = P0^5;

unsigned char timer1, timer2, 
			  timerGreen = 15, timerYellow = 5, timerRed = 20;  
		   
			

void displayCount()			
{
	unsigned char dozens1, units1, dozens2, units2, i;

	dozens1 = timer1 / 10;	
	units1 	= timer1 % 10;				 
	dozens2 = timer2 / 10;
	units2 	= timer2 % 10;

	for (i = 0; i <= 100; i++) 
	{
		Led7Seg_scan = led7seg_dig4;
		Led7Seg_data = dig[units1];		
		delayScan(200);

		Led7Seg_scan = led7seg_dig3;
		Led7Seg_data = dig[dozens1];	
		delayScan(200);

		Led7Seg_scan = led7seg_dig2;
		Led7Seg_data = dig[units2];		
		delayScan(200);

		Led7Seg_scan = led7seg_dig1;
		Led7Seg_data = dig[dozens2];		
		delayScan(200);
	} 

	timer1--;  				
	timer2--;
}



void main()
{
	red1 = yellow1 = green1 = red2 = yellow2 = green2 = 0;

	while (1) 
	{
		timer1 = timerGreen;		// 2 green light, 2 red light
		green1 = 1;
		timer2 = timerRed;		
		red2 = 1;
		do {
			displayCount();			
		} while (timer1 != 0);
		green1 = 0;		
						 	
		timer1 = timerYellow;  		// 2 yellow light, 2 red light
		yellow1 = 1;
		do {							
			displayCount();
		} while (timer1 != 0);
		yellow1 = 0;			 	
		red2 = 0;		
		
		timer1 = timerRed;			// 2 red light, 2 green light
		red1 = 1;				
		timer2 = timerGreen;		
		green2 = 1;
		do {
			displayCount();
		} while (timer2 != 0);		
		green2 = 0;

		timer2 = timerYellow;		// 2 red light, 2 yellow light
		yellow2 = 1;
		do {
			displayCount();
		} while (timer2 != 0);	
		red1 = 0;
		yellow2 = 0;
	}
}