#include <reg51.h>
#include "LCD_16x2_4bit.h"
#include "Keypad_4x3.h"



void main()
{ 	
    uint numOfChars = 0, col, row, i;
	uchar buffer[LCD_numOfCols] = "";
	
	lcd_init();
	lcd_sendStr("Enter character:");
	lcd_blinkCur();
	
    while(1)
    {   		
		col = keypad_scanColumn();

		if (col != -1) 								// when key is pressed
		{								
			if (numOfChars == LCD_numOfCols-1) {	// handle full line
				buffer[0] = 0x7F;					// symbol '<-'
				for (i = 1; i < LCD_numOfCols-2; i++)
					buffer[i] = buffer[i+1];			
				--numOfChars;
			}

		 	row = keypad_scanRow();  					
			buffer[numOfChars++] = keys[row][col];
			
			lcd_movCur(2, 1);						// display
			lcd_sendStr(buffer);
		}

		lcd_movCur(2, numOfChars+1);
		
		delay_ms(100);
    }
}