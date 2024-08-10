/*
 * ultrasonic.h
 *
 *  Created on: Oct 12, 2022
 *      Author: dell
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

#define ECHO_PORT_ID          PORTD_ID
#define ECHO_PIN_ID           PIN6_ID

#define TRIGGER_PORT_ID       PORTB_ID
#define TRIGGER_PIN_ID        PIN5_ID

void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
