#include "lcd.h"
#include "ultrasonic.h"

#define F_CPU 8000000UL

int main(void)
{
	uint16 distance = 0;

	LCD_init();
	Ultrasonic_init();

	LCD_displayStringRowColumn("Distance =    cm",0,0);
	while(1)
	{
		distance = Ultrasonic_readDistance();
		LCD_moveCursor(0,11);

		if(distance >= 100)
		{
			LCD_integerToString(distance);
		}
		else if((distance < 100) && (distance > 10))
		{
			LCD_integerToString(distance);
			LCD_displayCharacter(' ');
		}
		else
		{
			LCD_integerToString(distance);
			LCD_displayStringRowColumn("  ",0,12);
		}
	}
}
