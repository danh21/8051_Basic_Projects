/* ---------------------------------------------------------- LIBRARY ---------------------------------------------------------- */
#include <reg51.h>



/* ------------------------------------------------------ PIN CONNECTION ------------------------------------------------------- */
sbit KEYPAD_C4 = P1^3;		// columns of keypad ...
sbit KEYPAD_C3 = P1^2;
sbit KEYPAD_C2 = P1^1;
sbit KEYPAD_C1 = P1^0;
sbit KEYPAD_R4 = P1^7;		// rows of keypad ...
sbit KEYPAD_R3 = P1^6;
sbit KEYPAD_R2 = P1^5;
sbit KEYPAD_R1 = P1^4;



/* ---------------------------------------------------------- MACRO ------------------------------------------------------------ */
#define uchar unsigned char
#define uint unsigned int

#define keypad_numOfRows 4							// number of rows
#define keypad_numOfCols 4							// number of columns

char keys[keypad_numOfRows][keypad_numOfCols] = {	// keys of keypad
	0xC0, 0xF9, 0xA4, 0xB0,
	0x99, 0x92, 0x82, 0xF8,
	0x80, 0x90, 0x08, 0x03,
	0x46, 0x21, 0x06, 0x8E
};



/* ---------------------------------------------------------- PROTOTYPE ---------------------------------------------------------- */
// scan keypad to identify column of pressed key
uint keypad_scanColumn(void); 

// scan keypad to identify row of pressed key
uint keypad_scanRow(void); 					



/* ---------------------------------------------------------- FUNCTION ---------------------------------------------------------- */
uint keypad_scanColumn() 
{
	uint col = -1;
	
	KEYPAD_R1 = KEYPAD_R2 = KEYPAD_R3 = KEYPAD_R4 = 0;	
    KEYPAD_C1 = KEYPAD_C2 = KEYPAD_C3 = KEYPAD_C4 = 1;
    
    if (KEYPAD_C1 == 0)					  		
    	col = 0;
    else if (KEYPAD_C2 == 0)
    	col = 1;
    else if (KEYPAD_C3 == 0)
    	col = 2;
	else if (KEYPAD_C4 == 0)
    	col = 3;
		
	return col;	
}



uint keypad_scanRow() 					
{
	uint row;

	KEYPAD_R1 = KEYPAD_R2 = KEYPAD_R3 = KEYPAD_R4 = 1;
	KEYPAD_C1 = KEYPAD_C2 = KEYPAD_C3 = KEYPAD_C4 = 0;

	if (KEYPAD_R1 == 0)
		row = 0;
	else if (KEYPAD_R2 == 0)
		row = 1;
	else if (KEYPAD_R3 == 0)
		row = 2;
	else if(KEYPAD_R4 == 0)
		row = 3;

	return row;
}