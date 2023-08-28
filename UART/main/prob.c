#include <reg51.h>



sbit led = P0^7;

#define ADC_DATA P1
#define ADC_EXTRACTED_DATA P2

unsigned char rxData;



void setup_UART()
{
	TMOD = 0x20;	// enable timer1, mode 2 (auto reload)
	TH1 = -3;	 	// 9600	Baud rate	
	SCON = 0x50; 	// 8 bit uart, REN enabled, timer1	
	TR1 = 1;		// start timer1
	IE = 0x90;		// enable global and serial port interrupt													
}



void serial_int(void) interrupt	4	  		// turn on/off led
{	
	if (RI)
	{		
		RI = 0;	

		rxData = SBUF;	
			
		switch(rxData)
		{
			case('0'):	{led = 0; 	break;}
			case('1'):	{led = 1; 	break;}	
		}			
	}	
}



void main()
{
	unsigned char txData, dozens, units, value;

	setup_UART();

	while(1)
	{	
		value = ADC_DATA;
		
		dozens = (value / 10) << 4;
		units = value % 10;	 

		ADC_EXTRACTED_DATA = dozens | units;

		txData = ADC_EXTRACTED_DATA;
		SBUF = txData;
		while(TI == 0);
		TI = 0;
	}
}