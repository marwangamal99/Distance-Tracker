/*--------------------------------------------------------------------------
 * [FILE NAME]:		<ultrasonic.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<14/10/2021>
 *
 * [DESCRIPTION]:	<A header file for Ultra-Sonic sensor driver>
 ---------------------------------------------------------------------------*/

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------DEFINITIONS AND CONFIGURATIONS----------------------*/

#define	TRIGGER_PORT_ID		PORTC_ID
#define TRIGGER_PIN_ID		PIN0_ID

/*----------------------------------EXTERNS-----------------------------------*/

extern uint8 g_edgeCount;
extern uint16 g_highTime;

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/
void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H */
