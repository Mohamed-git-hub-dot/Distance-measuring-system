/*
 * main.c
 *
 *  Created on: Oct 12, 2022
 *      Author: dell
 */

#include "ultrasonic.h"
#include "lcd.h"
#include "avr/interrupt.h"


int main()
{
	uint16 dis = 0;

	// Enabling I-bit for ICU interrupt //
	sei();

	// Initialization The External devices and give a 10 micro second pulse to trigger pin //
	LCD_init();
	Ultrasonic_init();
	Ultrasonic_Trigger();

	LCD_displayString("Distance =   cm");

	while(1)
	{
		// reading distance from ultrasonic continously //
		dis = Ultrasonic_readDistance();

		if(dis < 100)
		{
			LCD_moveCursor(0, 10);
			LCD_intgerToString(dis);
			LCD_displayCharacter(' ');
		}
		else
		{
			LCD_moveCursor(0, 10);
			LCD_intgerToString(dis);
		}



	}

	return 0;
}
