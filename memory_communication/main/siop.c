#include <AT89X51.H>



void SetupSerial(char baud);
void TxChar(unsigned char ch);
unsigned char RxChar(void);
void TxStr(char *str);
void TxHex(unsigned char ch);
void TxCrLf(void);



void SetupSerial(char baud)
{
	SCON = 0x50;				// UART 8bit, receive enable
	TMOD = 0x20;				// timer 1, auto reload 8 bit 
	TH1 = baud;
	TR1 = 1;  					// start timer1
}



void TxChar(unsigned char ch)
{
	SBUF = ch;
	while(!TI);
	TI = 0;
}



unsigned char RxChar(void)
{
	RI = 0;			
	return SBUF;
}



void TxStr(char *str)
{
	while (*str) 	
		TxChar(*str++);
}



void TxNible(unsigned char ch)	// convert hex to ascii and transmit 
{
	if (ch < 10) 				// digit
		ch += 48;
	else 		  				// alpha
		ch += 55;				

	TxChar(ch);
}



void TxHex(unsigned char ch) 	// transmit HEX value
{	
	TxNible((ch & 0xF0) >> 4);
	TxNible(ch & 0x0F);

	TxChar(0x20);  				// space
}



void TxCrLf(void)
{
	TxChar(13);					// \r
	TxChar(10);					// \n
}