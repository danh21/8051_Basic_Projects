#include <reg51.h>
#include "ADC0808.h"



unsigned char rxData;

sbit led = P0^0;

#define ADC_EXTRACTED_DATA P2



void setup_UART()
{
	TMOD = 0x20;	// enable timer1, mode 2 (auto reload)
	TH1 = 0xFD;	 	// 9600	Baud rate	
	SCON = 0x50; 	// 8 bit uart, 1 stop bit, REN enabled
	TR1 = 1;		// start timer1
	IE = 0x90;		// enable global, serial port interrupt													
}



void delay(int interval)
{
	int i, j;
	for (i = 0; i < 255; i++)
		for (j = 0; j < interval; j++);
}



void serial_int(void) interrupt	4	 			// turn on/off led
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
	unsigned char channel, dozens, units, temp;

	setup_UART();

	while(1)
	{
		for (channel = 0; channel < 8; channel++)
		{ 	
			temp = ADC0808_read(channel);		 	// read data

			dozens = (temp / 10) << 4;				// extract data
			units = temp % 10;
			ADC_EXTRACTED_DATA = dozens | units;

			SBUF = ADC_EXTRACTED_DATA;				// transmit data
			while (TI == 0);
			TI = 0;

			delay(200);
		}		
	}
}