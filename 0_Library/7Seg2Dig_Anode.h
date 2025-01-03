/* ---------------------------------------------------------- LIBRARY ---------------------------------------------------------- */
#include <reg51.h>



/* ------------------------------------------------------ PIN CONNECTION ------------------------------------------------------- */
#define Led7Seg_data P0     // data port
#define Led7Seg_scan P1     // scan port



/* ---------------------------------------------------------- MACRO ------------------------------------------------------------ */
// number of digits of Led 7SEG
#define led7seg_numOfDigs 2

// select pin to scan led
#define led7seg_off 0x00
#define led7seg_dig2 0x01
#define led7seg_dig1 (led7seg_dig2 << 1)

// display digit 0-9
unsigned char const dig[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};   

// display alphabet A-F
unsigned char const alpha[6] = {0x08, 0x03, 0x46, 0x21, 0x06, 0x0e}; 

#define on_DP   (Led7Seg_data &= 0x7F)      // turn on decimal point
#define off_DP  (Led7Seg_data |= 0x80)		// turn off decimal point



/* ---------------------------------------------------------- PROTOTYPE ---------------------------------------------------------- */
// delay to scan
void delayScan(int times);



/* ---------------------------------------------------------- FUNCTION ---------------------------------------------------------- */
void delayScan(int times)
{
    int i;
	for (i = 0; i < times; i++);
}