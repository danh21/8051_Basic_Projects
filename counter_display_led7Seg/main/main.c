#include <reg51.h>
#include "7Seg4Dig_Anode.h"



#define uchar unsigned char

sbit countCLK = P1^0;
sbit countFlag = P1^1;

int count = 0;



void configInt()
{
	IE = 0x84; 				// enable global and external 1 interrupt	
	IT1 = 1; 				// interrupt by edge
}



void ISR_Ext1() interrupt 2
{		
	EA = 0; 				// clear interrupt

	countFlag = ~countFlag;

	if (countFlag == 1)		// init for count down 
		count = 9999;
	else				   	// init for count up
		count = 0;		  	

	EA = 1;
}



void delay_hardware_6ms()
{	
	TMOD = 0x01;			// 16-bit timer0
	ET0 = 0;				// no interrupt
	TH0 = 0xE8;				// 0xE890 ~ 59536 ---> 65535-59536+1 = 6000us = 6ms		
	TL0 = 0x90;					
	TF0 = 0; 				// clear overflow countFlag of timer0	
	TR0 = 1; 				// start timer0
	while (TF0 == 0);		// wait until overflow
	TR0 = 0; 				// stop timer0	
}



void display_number(int iNum)
{	
	uchar pos = led7seg_dig4, temp, i;
	
	for (i = 0; i < led7seg_numOfDigs; i++)  
	{
		temp = iNum % 10;
		iNum = iNum / 10; 

		Led7Seg_scan = pos; 
		Led7Seg_data = dig[temp]; 	

		delay_hardware_6ms();					 
		pos <<= 1;	
	}	
}



void main() 
{		 
	int i;
	countFlag = 0;

	configInt();
	
	while (1) 
	{
		for (i = 0; i < 20; i++)
			display_number(count);

		countCLK = ~countCLK;	// 6ms * 4 * 20 = 0.5s ---> period 1s ---> frequency 1Hz 				

		if (countFlag == 1)					// count down 						
			count--; 
		else 		 						// count up
	  		count++;
	} 
}