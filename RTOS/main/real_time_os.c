#include <REGX51.H>
#include <RTX51TNY.H>



#define led_blink_1s P1_0
#define led_blink_3s P1_1
#define led_blink_5s P1_2
#define leds_lightUp_fadeOut P2



void blink_1s(void) _task_ 1		
{
	while(1)
	{
		led_blink_1s = 1;
		os_wait2(K_IVL, 50);	// K_IVL: Wait for the interval specified by ticks
		led_blink_1s = 0;
		os_wait2(K_IVL, 50);	// 1 tick = 0.01s
	}
}



void blink_3s(void) _task_ 2	
{
	while(1)
	{
		led_blink_3s = 1;
		os_wait2(K_IVL, 150);
		led_blink_3s = 0;
		os_wait2(K_IVL, 150);
	}
}



void blink_5s(void) _task_ 3	
{
	while(1)
	{
		led_blink_5s = 1;
		os_wait2(K_IVL, 250);
		led_blink_5s = 0;
		os_wait2(K_IVL, 250);
	}
}



void lightUp_fadeOut(void) _task_ 4		
{
	unsigned int i;

	leds_lightUp_fadeOut = 0;											// init
	os_wait2(K_IVL, 50);

	while(1)
	{
		for (i = 0; i < 8; i++) {									   	// light up
			leds_lightUp_fadeOut = (leds_lightUp_fadeOut << 1) | 0x01;
			os_wait2(K_IVL, 50);
		}
		 
		for (i = 0; i < 8; i++) {								   		// fade out
			leds_lightUp_fadeOut = leds_lightUp_fadeOut << 1;
			os_wait2(K_IVL, 50);
		}
	}
}



void main_task(void) _task_ 0
{
	os_create_task (1);		// init 
	os_create_task (2); 
	os_create_task (3); 
	os_create_task (4); 

	os_delete_task (0);		// terminate 
}