#include <reg51.h>
#include "7Seg4Dig_Anode.h"



#define DELAYTIME 500000000



void main() {
	int i;
	unsigned char pos = led7seg_dig4;

	while(1) {	
		for (i = 0; i <= 9; i++) {
			if (pos > led7seg_dig1)
				pos = led7seg_dig4;

			Led7Seg_scan = pos;
			Led7Seg_data = dig[i];
			delayScan(DELAYTIME);
			pos <<= 1;
		}

		for (i = 0; i <= 5; i++) {
			if (pos > led7seg_dig1)
				pos = led7seg_dig4;

			Led7Seg_scan = pos;
			Led7Seg_data = alpha[i];
			delayScan(DELAYTIME);
			pos <<= 1;
		}
	}
}
