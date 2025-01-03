/* ---------------------------------------------------------- LIBRARY ---------------------------------------------------------- */
#include <reg51.h>



/* ------------------------------------------------------ PIN CONNECTION ------------------------------------------------------- */
#define ADC0808_DATA P3		// output
sbit ADC0808_A = P1^3;		// address A
sbit ADC0808_B = P1^2;		// address B
sbit ADC0808_C = P1^1;		// address C
sbit ADC0808_ALE = P1^0;	// address latch enable 
sbit ADC0808_START = P1^6;	// start conversion (1)
sbit ADC0808_EOC = P1^5;	// end of conversion (1)
//sbit ADC0808_OE = P1^4;	// output enable
//sbit ADC0808_CLK = P1^7;	// clock



/* ---------------------------------------------------------- MACRO ------------------------------------------------------------ */
#define uchar unsigned char



/* ---------------------------------------------------------- PROTOTYPE ---------------------------------------------------------- */
// read ADC
uchar ADC0808_read(uchar channel);



/* ---------------------------------------------------------- FUNCTION ---------------------------------------------------------- */
uchar ADC0808_read(uchar channel) {	
	ADC0808_A = channel & 0x01;		// select channel		
	ADC0808_B = channel & 0x02;
	ADC0808_C = channel & 0x04;

	ADC0808_ALE = 0;				// low-to-high transition of ALE signal to latch address 		
	ADC0808_ALE = 1;

	ADC0808_START = 1;				// start conversion ADC	
	ADC0808_START = 0;

	//ADC0808_OE = 1;					// output data
	return ADC0808_DATA;
}