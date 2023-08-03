#include <at89x51.h>



#define SWs P2
#define LEDs P1



void main()
{	 
	while (1)
		LEDs = SWs;
}