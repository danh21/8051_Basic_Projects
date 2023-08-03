#include <reg51.h>
#include "ADC0808.h"
#include "7Seg4Dig_Anode.h"



void main()
{
	uchar channel, temp, hundreds, dozens, units, i;
	
	for (channel = 0; channel < 8; channel++)	// 8 LM35 sensors
	{ 
		for (i = 0; i < 30; i++)				// scan led 7-seg
		{		
			Led7Seg_scan = led7seg_dig1; 		// channel
			Led7Seg_data = dig[channel+1];
			on_DP;
			delay_scanDig(500);

			temp = ADC0808_read(channel);  		// read temperature from channel

			hundreds = temp / 100;				// handle value
			dozens = temp / 10 % 10;
			units = temp % 10;

			Led7Seg_scan = led7seg_dig2;		// display hundreds number
			Led7Seg_data = dig[hundreds];
			off_DP;
			delay_scanDig(500);

			Led7Seg_scan = led7seg_dig3;		// display dozens number
			Led7Seg_data = dig[dozens];
			off_DP;
			delay_scanDig(500);

			Led7Seg_scan = led7seg_dig4;		// display units number
			Led7Seg_data = dig[units];
			off_DP;
			delay_scanDig(500);	
		}
	}
}