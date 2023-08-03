#include <at89x51.h>



#define keyboard P1
#define Led7Seg P2



void configInt()
{
	EA = 1;				// enable global interrupt
	EX1 = 1;			// enable external 1 interrupt	
}



void keyinterrupt() interrupt 2	
{	
	keyboard = 0xEF;					// 11101111 -> row 1
					
	while ((keyboard & 0x0F) == 0x0F)	
		keyboard = (keyboard<<1) | 1; 	// scan row	

	Led7Seg = ~keyboard;				// display led7seg

	while (1) 						   	// wait until the key is released	
		if (INT1) 						
			break;		
}



void main(void)
{					
	configInt();
	while(1)
		keyboard = 0x0F;				// init keyboard
}	