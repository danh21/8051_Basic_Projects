#include <reg51.h>

// https://punchlistzero.com/motor-rotation/#:~:text=By%20design%2C%20an%20electric%20motor,coincides%20with%20the%20load%20location.



#define motor P3

sbit Btn_Up   = P1^0;
sbit Btn_Down = P1^1;
sbit Btn_Stop = P1^2;



void main()
{	
	while(1) {	
		if (Btn_Up == 0) 	
			motor = 1;	
		else if (Btn_Down == 0) 	
			motor = 2;	
		else if (Btn_Stop == 0) 	
			motor = 0;
	}	
}	