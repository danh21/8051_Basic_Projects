#include <regx51.h>



#define UP 1
#define DOWN 0

sbit PWM_PIN = P2^0;

int duty = 65;

unsigned int T, Ton, Toff, dir = UP;
unsigned char Ton_TH, Ton_TL, Toff_TH, Toff_TL;



void delay(int interval)
{
	int i, j;
	for (i = 0; i < 255; i++)
		for (j = 0; j < interval; j++);
}



void PWM_Init(unsigned int cycle) {			// us unit
	PWM_PIN = 0;
	TMOD = 0x01;							// timer 16bit
   	ET0 = 1;								// enable timer 0 interrupt 
	EA = 1;									// enable global interrupt											
	T = cycle;								
}



void PWM_SetDuty(unsigned int duty) {
	if (duty == 0) {
		PWM_PIN = 0;
		ET0 = 0;
	}
	else if (duty == 100) {
	 	PWM_PIN = 1;
		ET0 = 0;
	}
	else {
	  	Ton = ((unsigned long)T) * duty / 100;	// calculate Ton and Toff
		Toff = T - Ton;
	
		Ton_TH = (65536 - Ton) >> 8;		   	// get init value for TH0 and TL0
		Ton_TL = (65536 - Ton) & 0x00FF; 
		Toff_TH = (65536 - Toff) >> 8;
		Toff_TL = (65536 - Toff) & 0x00FF;
		
		ET0 = 1;
		TR0 = 1; 								// start timer0 
	}										
}



void IntTimer0() interrupt 1 {					// create PWM		
	PWM_PIN = ~PWM_PIN;

	if (PWM_PIN) {
		TH0 = Ton_TH;
		TL0 = Ton_TL;	
	}
	else {
		TH0 = Toff_TH;
		TL0 = Toff_TL;
	}
}




int main() {
	PWM_Init(1000);				// T = 1000us
		
	while(1) {				 
		PWM_SetDuty(duty);		// set duty cycle

		if (dir == UP) {	   	// light up
			duty += 2;
			if (duty > 100) {
				dir = DOWN;
				duty = 100;
			}			
		}
		else {				 	// fade out
			duty -= 2;
			if (duty < 0) {
				dir = UP;
				duty = 0;
			}						
		}

		delay(50);			
	}		
}