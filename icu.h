/*--------------------------------------------------------------------------
 * [FILE NAME]:		<icu.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<13/10/2021>
 *
 * [DESCRIPTION]:	<A header file for AVR ICU driver>
 ---------------------------------------------------------------------------*/

#ifndef ICU_H
#define ICU_H

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*-----------------------------TYPES DECLEARATION-----------------------------*/

typedef enum{
	FALLING,RISING
}ICU_EdgeSelect;

typedef enum{
	NO_CLOCK,NO_PRESCALING,CLK_8,CLK_64,CLK_256,CLK_1024,XCLK_FALLING,XCLK_RISING
}ICU_Prescalar;

typedef struct{
	ICU_EdgeSelect edge;
	ICU_Prescalar prescalar;
}ICU_ConfigType;

/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/

void ICU_init(const ICU_ConfigType *a_configPtr);
void ICU_setCallBack(void(*a_ptr)(void));
void ICU_setEdgeSelect(const ICU_EdgeSelect edge_type);
uint16 ICU_getInputCaptureValue(void);
void ICU_clearTimerValue(void);
void ICU_deInit(void);

#endif /* ICU_H */
