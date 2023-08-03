# Description
    Basic projects related to 8051 microcontroller.

# Software
    - Keil C IDE
    - Proteus
    
# Source: 
    - Led_effect: 
        + Version 1: uses switches to turn on/off leds.
        + Version 2: creates some effects of leds as blinking, interleave, run led from left to right...
        + Version 3: uses timer to create exact delay.

    - RTOS: use RTOS to handle different tasks at the same time (blinking, light up fade out effect).

    - ctrlMotor: use 3 button (forward, backward, stop) to control direction of motor.

    - display_led7seg: 
        + Version 1: uses 4 leds 7-segment and 4 transistors, scans through them and display 0-F sequentially, then repeat.
        + Version 2: user presses key, then one of characters in range of 0-F is displayed on led 7-segment.
        + Version 3: uses buttons (as keypad) to create interrupt, then handles data and displays on led 7-segment.

    - PWM: use timer and PWM principle to control led light up fade out.

    - counter_display_led7seg:
        + Version 1: uses BCD-to-7-Segment decoder to decode, displays on led 7-segment from 0 to 9 and repeats.
        + Version 2: counts up and counts down, displays on led 7-segment and turns on leds by dozens value.
        + Version 3: displays on led 7-segment from 0000 to 9999 and repeats.
        + Version 4: displays on led 7-segment from 00000000 to 99999999 and repeats.
        + Version 5: uses button (to create an interrupt) to count up, displays value on led 7-segment.
        + Version 6: uses timer to create exact frequency as requirement, uses button (to create an interrupt) to switch between counting up and counting down, then displays value on led 7-segment.
    
    - Traffic_Lights: simulates traffic lights at intersections.

    - switchDisplay_LCD_Led7Seg: uses switch button to toggle display. If LCD is on/off, 7-segment is off/on.

# Code:
    - Modify pin connection of devices in libraries if necessary:
        + LCD_16x2_4bit.h 
        + LCD_16x2_8bit.h  
        + Keypad_4x3.h
        + Keypad_4x4.h
        + 7Seg2Dig_Anode.h
        + 7Seg4Dig_Anode.h
        + 7Seg8Dig_Anode.h
        + ADC0808.h

    - Modify keys by requirement:
        + Keypad_4x3.h
        + Keypad_4x4.h