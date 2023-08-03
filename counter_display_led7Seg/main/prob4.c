#include <reg51.h>
#include "7Seg4Dig_Anode.h"



void main()
{
	int thousands, hundreds, dozens, units, i;
		
	while(1) {
		for (thousands = 0; thousands < 10; thousands++)
		for (hundreds = 0; hundreds < 10; hundreds++)
		for (dozens = 0; dozens < 10; dozens++)
		for (units = 0; units < 10; units++)
		for (i = 100; i > 0; i--) {
			Led7Seg_scan = led7seg_dig4;  		
			Led7Seg_data = dig[units];			
			delayScan(200);

			Led7Seg_scan = led7seg_dig3;			
			Led7Seg_data = dig[dozens];
			delayScan(200);

			Led7Seg_scan = led7seg_dig2;		
			Led7Seg_data = dig[hundreds];
			delayScan(200);

			Led7Seg_scan = led7seg_dig1;		
			Led7Seg_data = dig[thousands];
			delayScan(200);
		}
	}
}