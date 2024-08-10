/*
 * ultrasonic.c
 *
 *  Created on: Oct 12, 2022
 *      Author: dell
 */

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include "util/delay.h"

uint8 g_edge_count = 0;
uint16 g_Time = 0;

/* Call back function that that will be executed every time the interrupt handler of ICU
 * will be executed (Detecting EDGE on ICP pin)
 */
void Ultrasonic_edgeProcessing(void)
{
	g_edge_count++;

	if(g_edge_count == 1)
	{
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edge_count == 2)
	{
		g_Time = Icu_getInputCaptureValue();
		Icu_setEdgeDetectionType(RISING);
		Icu_clearTimerValue();
		g_edge_count = 0;
	}
}

// Initializing ultrasonic at Rising edge at first and clock frequency = F_CPU / 8
void Ultrasonic_init(void)
{
	Icu_ConfigType icu_obj = {F_CPU_8,RISING};
	Icu_init(&icu_obj);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIGGER_PORT_ID, TRIGGER_PIN_ID, PIN_OUTPUT);
}

// generating a pulse of time greater than or equal 10 micro second //
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_LOW);
}

/* Read the distance continously from the ultrasonic using ICU to calculate the time of Ton
 * on ECHO pin (ICP1)
 */
uint16 Ultrasonic_readDistance(void)
{
	uint16 distance = 0;
	Ultrasonic_Trigger();
	distance = (float) ( (g_Time) * (0.0173) );
	return distance;
}
