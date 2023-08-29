#include <AT89X51.H>



#define B9600 -3	// baud 9600 11.059MHz (clock frequency of 8051)
#define B4800 -6	// baud 4800 11.059MHz
#define B2400 -12	// baud 2400 11.059MHz
#define B1200 -24	// baud 1200 11.059MHz

/* Define pins */
#define DBLED P3_2
#define LED_UP P3_3
#define LED_DOWN P3_4
unsigned char xdata *pp;

void SetupSerial(char baud);
void TxChar(unsigned char ch);
void TxStr(char *str);
void TxCrLf(void);
unsigned char RxChar(void);
void ResetXRam(void);
void write_ram(unsigned int add, unsigned char dat);
unsigned char read_ram(unsigned int add);



void main(void) 
{
	unsigned char rxData, txData;

	SetupSerial(B9600);

	DBLED = 1;
	LED_UP = 1;
	LED_DOWN = 1;

	TxStr("Test External RAM 62C256");
	TxCrLf();

	ResetXRam();

	while(1) 
	{
		if(RI) 
		{					
			rxData = RxChar();			  	// receive data 
			DBLED = 0;											
				
			switch(rxData) {
				case 'u':					// uppercase
					LED_UP = 0;		
					LED_DOWN = 1;
					TxChar(rxData - 32);	
					TxCrLf();
					break;
				case 'L':					// lowercase
					LED_DOWN = 0;		
					LED_UP = 1;
					TxChar(rxData + 32);	
					TxCrLf();
					break;
				default:
					LED_UP = 1;		   	
					LED_DOWN = 1;
					break;
			}

			txData = read_ram(rxData);	  	// transmit data from RAM
			TxChar(txData);	
			TxCrLf();
 		}
	}
}



void SetupSerial(char baud)
{
	SCON = 0x50;	// receive enable; UART8bit
	TMOD = 0x20;	// timer 1, auto reload 
	TH1 = baud;
	TF1 = 0;
	TR1 = 1;
}



//***************Transmit************************
void TxChar(unsigned char ch)
{
	SBUF = ch;
	while(TI == 0);	
	TI = 0;
}



void TxStr(char *str)
{
	while(*str != '\0') 	
		TxChar(*str++);
}




void TxCrLf(void)	// new line
{
	TxChar(13);		// \r
	TxChar(10);		// \n
}



//***************Receive************************
unsigned char RxChar(void)
{
	RI = 0;
	return SBUF;
}



//***********************************************
void ResetXRam(void)
{
	unsigned int j;

	TxStr("Reset Xram ...");
	TxCrLf();

	for (j = 0; j < 257; j++)
		write_ram(j, j%256);

	TxStr("Reset RAM completely");
	TxCrLf();
}



void write_ram(unsigned int add, unsigned char dat)
{
	pp = 0x0000 + add;
	*pp = dat;
}



unsigned char read_ram(unsigned int add)
{
	pp = 0x0000 + add;
	return *pp;
}