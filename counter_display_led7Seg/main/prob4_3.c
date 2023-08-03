#include <reg51.h>
#include "7Seg2Dig_Anode.h"



#define LEDs P2



void main() {
	int units, dozens, i;	
	LEDs = 0xFF;									// off

	while(1) {
		/* COUNT UP */					   
		for (dozens = 0; dozens < 10; dozens++) {
			for (units = 0; units < 10; units++) {
				if (dozens == 9 && units == 1)  	// 91 -> count down
					break;
						
				for (i = 100; i > 0; i--) {
					Led7Seg_scan = led7seg_dig2;  			
					Led7Seg_data = dig[units];			
					delayScan(200);
		
					Led7Seg_scan = led7seg_dig1;		
					Led7Seg_data = dig[dozens];
					delayScan(200);
				}			
			}

			LEDs <<= 1;								// turn on led gradually
		}

		/* COUNT DOWN */		
		for (dozens = 8; dozens >= 0; dozens--) {						
			if (dozens == 7)					  	// turn off led gradually
				LEDs = 0x80;						
			else if (dozens < 7)
				LEDs |= (LEDs >> 1);				
			
			for (units = 9; units >= 0; units--) {				
				for (i = 100; i > 0; i--) {
					Led7Seg_scan = led7seg_dig2;  		
					Led7Seg_data = dig[units];			
					delayScan(200);
		
					Led7Seg_scan = led7seg_dig1;			
					Led7Seg_data = dig[dozens];
					delayScan(200);
				}

				if (dozens == 0 && units == 0)		// 00 -> count up 
					break;	
			}
		}
	}
}