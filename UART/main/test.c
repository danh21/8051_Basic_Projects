#include <at89x51.h>



unsigned char rxData;

#define led P2_7



void delay_ms(int ms) 
{
	int i, j;
	for (i = 0; i < ms; i++)
		for (j = 0; j < 123; j++);
}



void setupUART()
{
	EA = 1;		  		// enable global interrupt
	ES = 1;				// enable serial port interrupt	
	SCON = 0x50; 		// 8 bit uart, receive enable
	TMOD = 0x20;		// enable timer1, mode 2 (auto reload)	
	TH1 = TL1 = 0xFD;	// 9600	Baud rate
	TR1 = 1;			// start timer1										
}



void serial_int(void) interrupt	4 	// turn on/off led
{		
	if (RI)	   						// flag is set when a character is received completely
	{				
		RI = 0;	
		
		rxData = SBUF;
							
		switch (rxData) {
			case('0'):				
				led = 0; 	
				break;
			case('1'):				
				led = 1; 	
				break;		
		}				
	}
}



void transmit_char(char Data)
{
	SBUF = Data;
	while (TI == 0);				// flag is set when a character is transmitted completely
	TI = 0;
}



void transmit_str(char *Data)
{
	int i = 0;
	for (i = 0; Data[i] != '\0'; i++)
		transmit_char(Data[i]);
}



void main()
{
	setupUART();

	while (1)
	{		
		transmit_str("danh");
		delay_ms(1000);
	}
}