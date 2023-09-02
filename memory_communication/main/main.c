#include <AT89X51.H>



#define B9600 -3	// baud 9600 11.059MHz(clock frequency of 8051)
#define B4800 -6	// baud 4800 11.059MHz
#define B2400 -12	// baud 2400 11.059MHz
#define B1200 -24	// baud 1200 11.059MHz

#define DBLED P3_2
#define LAT P3_5
#define OE P3_6 
#define CE P3_7		



// siop.c
extern void SetupSerial(char baud);
extern void TxChar(unsigned char ch);
extern unsigned char RxChar(void);
extern void TxStr(char *str);
extern void TxHex(unsigned char ch);
extern void TxCrLf(void);

void ReadXRom(void);
unsigned char ReadByte(unsigned int Addr);



void main (void)
{
	unsigned char ch;

	SP = 0x62;	// stack pointer (chua dia chi cua data hien tai dang o dinh cua stack)

	SetupSerial(B9600);
   	
	TxStr("-----------------------------------");
	TxCrLf();
	TxStr("External rom");
	TxCrLf();

	while(1) 
	{
		if (RI) 					  	// receive char completely
		{ 						
			DBLED = 0;					// LED on

			ch = RxChar();			   	// receive char

			TxChar(ch);					// transmit char
			TxCrLf();

			switch(ch) {
				case 'R':				
					ReadXRom();
					break;
				default:
					break;
			}
		}
	}
}



void ReadXRom(void)
{
	unsigned char ch;
	unsigned int addr;

	for (addr = 0; addr < 10; addr++) {
		ch = ReadByte(addr);
		TxHex(ch);
	}

	TxCrLf();
}



unsigned char ReadByte(unsigned int Addr)	
{
	unsigned char RetVal, highAddr, lowAddr;

	lowAddr = (unsigned char) Addr;			
	highAddr = (unsigned char) (Addr >> 8);
		
	P0 = lowAddr; 								
	LAT = 1;
	LAT = 0;
	highAddr &= 0x7f;	// 7-bit high address
	P2 = highAddr;							

	CE = 0;
	OE = 0;

	RetVal = P0;
								
	CE = 1;
	OE = 1;

	return RetVal;							
}