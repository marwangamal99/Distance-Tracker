/*--------------------------------------------------------------------------------------
 * [FILE NAME]:		<icu.c>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<16/10/2021>
 *
 * [DESCRIPTION]:	<A source file for AVR ICU driver>
 --------------------------------------------------------------------------------------*/

/*----------------------------------------INCLUDES-------------------------------------*/
#include "icu.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*------------------------------------GLOBAL VARIABLES----------------------------------*/

static volatile void(*g_callBackPtr)(void) = NULL_PTR;

/*---------------------------------FUNCTIONS DEFINITIONS-------------------------------*/

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	ICU_init
 * [DESCRIPTION]:	This Function is used to initialize the Input Capture Unit
 * [ARGS]:	const ICU_ConfigType *a_configPtr : This Argument is a pointer to struct,
 * 			it will indicate the struct input for the function
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void ICU_init(const ICU_ConfigType *a_configPtr)
{
	/* Set PD6 as input pin */
	CLEAR_BIT(DDRB,PD6);

	/* We are using a non-PWM mode */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	/* Edge and clock prescaling dynamic configuration */
	TCCR1B = (TCCR1B & 0xBF) | ((a_configPtr->edge) << 6);
	TCCR1B = (TCCR1B & 0xF8) | (a_configPtr->prescalar);

	TCNT1 = 0;
	ICR1 = 0;

	/* Timer1 input capture interrupt enable */
	TIMSK |= (1<<TICIE1);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	ICU_setCallBack
 * [DESCRIPTION]:	This Function is used to assign the specific function used to the
 * 					global pointer to function to use it in the ISR
 * [ARGS]:	void(*a_ptr)(void) : This Argument is a pointer to function, indicating the
 * 								 function called in the call back function
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void ICU_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	ICU_setEdgeSelect
 * [DESCRIPTION]:	This Function is used to select the triggering edge
 * [ARGS]:	const ICU_EdgeSelect edge_type : This Argument shall indicate the edge type
 * 											 (Rising/Falling)
 *	[RETURNS]:	No Returns
 ----------------------------------------------------------------------------------------*/
void ICU_setEdgeSelect(const ICU_EdgeSelect edge_type)
{
	TCCR1B = (TCCR1B & 0xBF) | (edge_type << 6);
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	ICU_getInputCaptureValue
 * [DESCRIPTION]:	This Function is used to get the input capture unit value.
 * [ARGS]:	No Argument
 *	[RETURNS]:	return Input capture register value.
 ----------------------------------------------------------------------------------------*/
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	ICU_getInputCaptureValue
 * [DESCRIPTION]:	This Function is used to clear the input capture unit value.
 * [ARGS]:	No Argument
 *	[RETURNS]:	No Return
 ----------------------------------------------------------------------------------------*/
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*---------------------------------------------------------------------------------------
 * [FUNCTION NAME]:	ICU_getInputCaptureValue
 * [DESCRIPTION]:	This Function is used to de-initialize the ICU, used when finishing the
 * 					specific function
 * [ARGS]:	No Argument
 *	[RETURNS]:	No Return
 ----------------------------------------------------------------------------------------*/
void ICU_deInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	TIMSK &= ~(1<<TICIE1);
}
/*--------------------------------INTERRUPT SERVICE ROUTINES-----------------------------*/
/*---------------------------------------------------------------------------------------
 * [ISR NAME]:	TIMER1_CAPT_vect
 * [DESCRIPTION]:	This ISR will trigger the call back function
 * [ARGS]:	No Argument
 *	[RETURNS]:	No Return
 ----------------------------------------------------------------------------------------*/
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}
