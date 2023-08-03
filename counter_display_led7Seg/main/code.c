#include <at89x51.h>



void delay(unsigned long time) {
	unsigned long i;
	for (i = 0; i < time; i++);
}



void main(void) {
	int value = 0;
	while (value < 10) {
		P2 = value++;
		delay(10000);
	}  
}