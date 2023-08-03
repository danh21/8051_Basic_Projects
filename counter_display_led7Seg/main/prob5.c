#include <reg51.h>
#include "7Seg4Dig_Anode.h"



int count = 0;



void configInt() 
{
	IE = 0x81;  	// enable global and external 0 interruot	
	IT0 = 1; 		// active by edge
} 



void ISR_Ext0() interrupt 0 
{
	count++;
}



void display_number(int iNum)
{	
	int i;
	unsigned char pos = led7seg_dig4, temp;	
	for (i = 0; i < led7seg_numOfDigs; i++)  		
	{
		temp = iNum % 10; 			
		iNum /= 10; 
					
		Led7Seg_scan = pos;  	 				
		Led7Seg_data = dig[temp];

		delayScan(500);	 
		pos <<= 1;					
	}
}



void main() 
{
	configInt();

	while (1) 
		display_number(count);
}