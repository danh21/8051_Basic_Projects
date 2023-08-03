/* ---------------------------------------------------------- LIBRARY ---------------------------------------------------------- */
#include <reg51.h>



/* ------------------------------------------------------ PIN CONNECTION ------------------------------------------------------- */
sbit KEYPAD_C3 = P1^1;	// columns of keypad
sbit KEYPAD_C2 = P1^2;
sbit KEYPAD_C1 = P1^3;
sbit KEYPAD_R4 = P1^4;	// rows of keypad
sbit KEYPAD_R3 = P1^5;
sbit KEYPAD_R2 = P1^6;
sbit KEYPAD_R1 = P1^7;



/* ---------------------------------------------------------- MACRO ------------------------------------------------------------ */
#define KEYPAD_numOfRows 4							// number of rows
#define KEYPAD_numOfCols 3							// number of columns
    		
char keys[KEYPAD_numOfRows][KEYPAD_numOfCols] = {	// keys of keypad
	'1', '2', '3',
	'4', '5', '6',
	'7', '8', '9',
	'*', '0', '#'
};



/* ---------------------------------------------------------- PROTOTYPE ---------------------------------------------------------- */
// scan keypad to identify column of pressed key
unsigned int keypad_scanColumn(void);

// scan keypad to identify row of pressed key
unsigned int keypad_scanRow(void); 



/* ---------------------------------------------------------- FUNCTION ---------------------------------------------------------- */
unsigned int keypad_scanColumn()
{
	unsigned int col = -1;
	
	KEYPAD_R1 = KEYPAD_R2 = KEYPAD_R3 = KEYPAD_R4 = 0;	
    KEYPAD_C1 = KEYPAD_C2 = KEYPAD_C3 = 1;
    
    if (KEYPAD_C1 == 0)					  		
    	col = 0;
    else if (KEYPAD_C2 == 0)
    	col = 1;
    else if (KEYPAD_C3 == 0)
    	col = 2;
		
	return col;	
}



unsigned int keypad_scanRow() 					
{
	unsigned int row;

	KEYPAD_R1 = KEYPAD_R2 = KEYPAD_R3 = KEYPAD_R4 = 1;
	KEYPAD_C1 = KEYPAD_C2 = KEYPAD_C3 = 0;

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