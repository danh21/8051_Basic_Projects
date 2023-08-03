#include <reg51.h>
#include "Keypad_4x4.h"



#define Led7Seg P2



void main()
{
	uint col, row;
	
	while (1)
	{
		col = keypad_scanColumn();

		if (col != -1) {					 	// key is pressed
			row = keypad_scanRow();
			Led7Seg = keys[row][col];
			while (keypad_scanColumn() != -1);  // debounce
		}
	}
}