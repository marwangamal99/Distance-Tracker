/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<ultrasonic.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<13/10/2021>
 *
 * [DESCRIPTION]:	<A source file for Ultra-Sonic sensor driver>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <avr/io.h>
#include <util/delay.h>

/*------------------------------------GLOBAL VARIABLES----------------------------------*/

uint8 g_edgeCount = 0;
uint16 g_highTime = 0;

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	Ultrasonic_init
 * [DESCRIPTION]:	This Function is used to initialize the Ultrasonic sensor.
 * [ARGS]:	No Arguments
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void Ultrasonic_init(void)
{
	/* The ICU configuration structure (Edge, Prescalar) */
	ICU_ConfigType ICU_config = {RISING,CLK_8};

	/* Initializing the ICU driver */
	ICU_init(&ICU_config);

	/* Set the I-bit to 1 then waiting for an interrupt (Finding a rising edge) */
	SREG |= (1<<7);

	/* The call back function is what will calculate the distance */
	ICU_setCallBack(Ultrasonic_edgeProcessing);

	/* Set the Trigger Pin as an OUTPUT pin */
	GPIO_setPinDirection(TRIGGER_PORT_ID,TRIGGER_PIN_ID,PIN_OUTPUT);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	Ultrasonic_Trigger
 * [DESCRIPTION]:	This Function is used to initiate the Ultrasonic sensor Trigger.
 * [ARGS]:	No Arguments
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void Ultrasonic_Trigger(void)
{
	/* The trigger pin should have a pulse of width 10usec at least so
	 * At first, set the trigger pin to high */
	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_HIGH);
	/* Delay for 1ms */
	_delay_us(10);
	/* Clear the trigger bit, the pulse will be sent */
	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_LOW);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	Ultrasonic_readDistance
 * [DESCRIPTION]:	This Function is used to read the distance by taking the high time of
 * 					the sensor then by equation, calculating the distance
 * [ARGS]:	No Arguments
 *	[RETURNS]:	The return indicate the distance of the object from the sensor
 ----------------------------------------------------------------------------------------*/
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();

	/* EQUATION: Distance = (Speed "340*10^3 cm/sec" *Time) / 2
	 * 						17,000 * Time "TimerValue / Frequency"
	 * We are using F_cpu/8 = 8MHz/8 = 1MHz
	 * 						Distance = TimerValue / 58.8 */
	if(g_edgeCount == 2)
	{
		g_edgeCount = 0;
	}
	return g_highTime/58.8;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	Ultrasonic_edgeProcessing
 * [DESCRIPTION]:	This Function is used to detect the edges for operate the calculations,
 * 					at first when it will detect a rising edge it will start the ICU timer,
 * 					then when detecting a falling edge "which is the time of the pulse from
 * 					the sensor to the object and return" it will return the high time of the
 * 					pulse
 * [ARGS]:		No Arguments
 * [RETURNS]:	The return indicate the distance of the object from the sensor
 ----------------------------------------------------------------------------------------*/
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		ICU_clearTimerValue();
		ICU_setEdgeSelect(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		g_highTime = ICU_getInputCaptureValue();
		ICU_setEdgeSelect(RISING);
	}
}
