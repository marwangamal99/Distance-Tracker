/*--------------------------------------------------------------------------
 * [FILE NAME]:		<lcd.h>
 *
 * [AUTHOR]:		<Marwan Gamal>
 *
 * [DATE CREATED]:	<4/10/2021>
 *
 * [DESCRIPTION]:	<A header file for AVR LCD>
 ---------------------------------------------------------------------------*/

#ifndef LCD_H
#define LCD_H

/*-----------------------------------INCLUDES---------------------------------*/

#include "std_types.h"

/*------------------------DEFINITIONS AND CONFIGURATIONS----------------------*/

#define NUM_OF_COLS		16
#define NUM_OF_ROWS		4

#define LCD_RS_PORT		PORTB_ID
#define LCD_RS_PIN		PIN0_ID

#define	LCD_RW_PORT		PORTB_ID
#define	LCD_RW_PIN		PIN1_ID

#define LCD_E_PORT		PORTB_ID
#define LCD_E_PIN		PIN2_ID

#define LCD_DB_PORT		PORTA_ID

#define LCD_2LINES_8BITS_MODE	0x38
#define	LCD_CURSOR_OFF			0x0C
#define LCD_CLEAR_SCREEN		0x01
#define LCD_SET_CURSOR_AT_BEGIN	0x80

/*-----------------------------TYPES DECLEARATION-----------------------------*/


/*-----------------------------FUNCTIONS PROTOTYPES---------------------------*/

void LCD_sendCommand(uint8 command);

void LCD_displayCharacter(uint8 character);

void LCD_init(void);

void LCD_displayString(const char *str);

void LCD_moveCursor(uint8 row, uint8 column);

void LCD_displayStringRowColumn(const char *str, uint8 row, uint8 column);

void LCD_clearScreen(void);

void LCD_integerToString(uint32 integer);

#endif /* LCD_H */
