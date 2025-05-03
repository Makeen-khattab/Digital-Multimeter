#include "dmmAmmeter.h"
#include "gpio.h"
#include "adc.h"
#include <util/delay.h>
#include "lcd.h"


extern volatile  uint8 g_reset;
/* Indication that we entered the ammeter circuit*/
 volatile uint8 g_ammMeterEnter = 0;
void AMMETER_init(void)
{
GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT);

/********************Led pin *************************/
GPIO_setupPinDirection(PORTC_ID, PIN6_ID, PIN_OUTPUT);
}
void AMMETER_firstRange(void)
{
	g_ammMeterEnter = 1;
	GPIO_writePin(PORTB_ID,PIN7_ID, LOGIC_HIGH);
	GPIO_writePin(PORTC_ID, PIN6_ID, LOGIC_HIGH);
	uint16 a_valueReadByAdc;
	float32 a_currentValue;
	while(1)
	{

	a_valueReadByAdc=ADC_readChannel(ADC5);

	if(g_reset == 1)
	{
		g_reset =0;
		GPIO_writePin(PORTC_ID, PIN6_ID, LOGIC_LOW);
		LCD_clearScreen();
		break;

	}


	a_currentValue = ((( a_valueReadByAdc - 94 )*5)/47) + 10 ;

	if((a_valueReadByAdc > 94 ) && (a_valueReadByAdc < 940 ))
	{
	LCD_clearScreen();
	LCD_moveCursor(1,1);
	LCD_floatToString(a_currentValue);
	LCD_displayString(" mA");
	_delay_ms(500);
	}

	if(g_reset == 1)
	{
		g_reset =0;
		GPIO_writePin(PORTC_ID, PIN6_ID, LOGIC_LOW);
		LCD_clearScreen();
		break;
	}

	}

}
void AMMMETER_secondRange(void)
{
	g_ammMeterEnter = 1;
	uint16 a_valueReadByAdc;
	float32 a_currentValue;
	GPIO_writePin(PORTC_ID, PIN6_ID, LOGIC_HIGH);
	GPIO_writePin(PORTB_ID,PIN7_ID, LOGIC_LOW);

	while(1)
	{

	a_valueReadByAdc=ADC_readChannel(ADC5);

	a_currentValue = (((( a_valueReadByAdc - 96.1 )*9)/8650) + 0.1) ;

	if(g_reset == 1)
	{
		g_reset =0;
		GPIO_writePin(PORTC_ID, PIN6_ID, LOGIC_LOW);
		LCD_clearScreen();
		break;

	}



	if((a_valueReadByAdc > 94 ) && (a_valueReadByAdc < 940 ))
	{
		a_currentValue = a_currentValue*1000;
	LCD_clearScreen();
	LCD_moveCursor(1,1);
	LCD_floatToString(a_currentValue);
	LCD_displayString(" mA");
	_delay_ms(500);
	}
	else if(a_valueReadByAdc > 960)
	{
		LCD_clearScreen();
		LCD_moveCursor(1,1);
		LCD_floatToString(a_currentValue);
		LCD_displayString(" A");
		_delay_ms(500);
	}

	if(g_reset == 1)
	{
		g_reset =0;
		GPIO_writePin(PORTC_ID, PIN6_ID, LOGIC_LOW);
		break;
	}

	}

}
