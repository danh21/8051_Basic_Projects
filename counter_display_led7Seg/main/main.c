#include <reg51.h>
#include "7Seg8Dig_Anode.h"



void main() {
	int tensOfMillions, millions, hundredsOfThousands, tensOfThousands, thousands, hundreds, dozens, units, i;

	while(1) {
		for (tensOfMillions = 0; tensOfMillions < 10; tensOfMillions++)
		for (millions = 0; millions < 10; millions++)
		for (tensOfThousands = 0; tensOfThousands < 10; tensOfThousands++)
		for (hundredsOfThousands = 0; hundredsOfThousands < 10; hundredsOfThousands++)
		for (thousands = 0; thousands < 10; thousands++)
		for (hundreds = 0; hundreds < 10; hundreds++)
		for (dozens = 0; dozens < 10; dozens++)
		for (units = 0; units < 10; units++)
		for (i = 50; i > 0; i--) {
			Led7Seg_scan = led7seg_dig8;  		
			Led7Seg_data = dig[units];			
			delayScan(50);

			Led7Seg_scan = led7seg_dig7;			
			Led7Seg_data = dig[dozens];
			delayScan(50);

			Led7Seg_scan = led7seg_dig6;			
			Led7Seg_data = dig[hundreds];
			delayScan(50);

			Led7Seg_scan = led7seg_dig5;			
			Led7Seg_data = dig[thousands];
			delayScan(50);

			Led7Seg_scan = led7seg_dig4;  		
			Led7Seg_data = dig[hundredsOfThousands];			
			delayScan(50);

			Led7Seg_scan = led7seg_dig3;		
			Led7Seg_data = dig[tensOfThousands];
			delayScan(50);

			Led7Seg_scan = led7seg_dig2;			
			Led7Seg_data = dig[millions];
			delayScan(50);

			Led7Seg_scan = led7seg_dig1;		
			Led7Seg_data = dig[tensOfMillions];
			delayScan(50);
		}
	}
}