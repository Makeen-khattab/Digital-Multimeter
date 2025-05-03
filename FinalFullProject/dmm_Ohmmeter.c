#include "dmm_Ohmmeter.h"
#include "gpio.h"
#include "avr/interrupt.h"
#include "adc.h"
#include "lcd.h"
#include "keypad.h"
#include "util/delay.h"

 extern volatile uint8 g_reset;
 /* Indication that we entered the Ohmmeter circuit*/
 volatile uint8 g_ohmMeterEnter = 0;


void OHMMETER_init(void)
{
	/*Setting the pins responsible for mux selection as an output pins*/
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_OUTPUT);
	/********************Led pin *************************/
	GPIO_setupPinDirection(PORTC_ID, PIN7_ID, PIN_OUTPUT);

}

void OHMMETER_firstRange(void)
{
	/*************Powering the Led of Ohmmeter****************/
	GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_HIGH);
	/*Assuring that you pushed the reset button while you are at Ohmmeter section*/
	g_ohmMeterEnter=1;
	float32 voltValue;
	float32 resistValue;
  /******** Mux selection line for first range 0 0 ***************/
	GPIO_writePin(PORTB_ID, PIN5_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID, PIN6_ID,LOGIC_LOW);


while(1)
{
LCD_moveCursor(1,1);

/**************The volt value read on the ADC Hardware*******************/
voltValue= (ADC_readChannel(ADC4) / 1023.0)*5 ;

_delay_ms(100);

/* Equation responsible for calculating the value of resistance based on the specific range*/
resistValue = voltValue * ( (OHMMETERMUXRES + OHMMETERRES1 ) /(5-voltValue));

/*********************************************
 * Checking that you pushed the reset button
 * by a an indication variable changed in ISR
 * ********************************************/
if(g_reset == 1)
{
	g_reset =0;
	GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_LOW);
	LCD_clearScreen();
	break;

}


if(resistValue > 1000)
{
	/**************Evaluating Resistance in Kohm**************/
	resistValue/=1000;
	LCD_clearScreen();
LCD_floatToString(resistValue);
LCD_displayString("kohm");
_delay_ms(500);
}
else
{
	/**************Evaluating Resistance in  ohm**************/
	LCD_clearScreen();
	LCD_floatToString(resistValue);
	LCD_displayString("ohm");
	_delay_ms(500);
}

/*********************************************
 * Checking that you pushed the reset button
 * by a an indication variable changed in ISR
 * ********************************************/
 if(g_reset == 1)
 {
 	g_reset =0;
 	GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_LOW);
 	LCD_clearScreen();
 	break;

 }



}

}
void OHMMETER_secondRange(void)
{
	/*************Powering the Led of Ohmmeter****************/
	GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_HIGH);
	/*Assuring that you pushed the reset button while you are at Ohmmeter section*/
	g_ohmMeterEnter=1;
	float32 voltValue;
	float32 resistValue;
	/******** Mux selection line for first range 0 1 ***************/
	GPIO_writePin(PORTB_ID, PIN5_ID,LOGIC_HIGH);
	GPIO_writePin(PORTB_ID, PIN6_ID,LOGIC_LOW);

	while(1)
	{
		/*********************************************
		 * Checking that you pushed the reset button
		 * by a an indication variable changed in ISR
		 * ********************************************/
		if(g_reset == 1)
		{
			g_reset =0;
			GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_LOW);
			LCD_clearScreen();
			break;

		}

		LCD_moveCursor(1,1);

	/**************The volt value read on the ADC Hardware*******************/
		voltValue= (ADC_readChannel(ADC4) / 1023.0)*5 ;

	/* Equation responsible for calculating the value of resistance based on the specific range*/
		resistValue = voltValue * ( (OHMMETERMUXRES + OHMMETERRES2 ) /(5-voltValue));



		if(resistValue > 1000)
		{
			/**************Evaluating Resistance in Kohm**************/
			resistValue/=1000;
			LCD_floatToString(resistValue);
			LCD_displayString("kohm");

		}

	/*********************************************
    * Checking that you pushed the reset button
	* by a an indication variable changed in ISR
	* ********************************************/

if(g_reset == 1)
{
	g_reset =0;
	GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_LOW);
	LCD_clearScreen();
	break;

}


	}


}
void OHMMETER_thirdRange(void)
{
	/*************Powering the Led of Ohmmeter****************/
	g_ohmMeterEnter=1;
	float32 voltValue;
	float32 resistValue;
	/*Assuring that you pushed the reset button while you are at Ohmmeter section*/
	GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_HIGH);

	/******** Mux selection line for first range 1 0 ***************/
	GPIO_writePin(PORTB_ID, PIN5_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID, PIN6_ID,LOGIC_HIGH);

	while(1)
	{

	LCD_moveCursor(1,1);

	/**************The volt value read on the ADC Hardware*******************/
	voltValue= (ADC_readChannel(ADC4) / 1023.0)*5 ;

	/* Equation responsible for calculating the value of resistance based on the specific range*/
	resistValue = voltValue * ( (OHMMETERMUXRES + OHMMETERRES3 ) /(5-voltValue));

	/*********************************************
    * Checking that you pushed the reset button
	* by a an indication variable changed in ISR
	* ********************************************/
	if(g_reset == 1)
	{
		g_reset =0;
		GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_LOW);
		LCD_clearScreen();
		break;

	}

	/**************Evaluating Resistance in Mohm**************/
	if(resistValue > 1000000)
	{

		resistValue/=1000000;
		LCD_floatToString(resistValue);
		LCD_displayString("Mohm");


	}
	/**************Evaluating Resistance in Kohm**************/
	else if (resistValue > 1000)
	{
		resistValue/=1000;
		LCD_floatToString(resistValue);
	     LCD_displayString("kohm");
	}

	/*********************************************
    * Checking that you pushed the reset button
	* by a an indication variable changed in ISR
	* ********************************************/

if(g_reset == 1)
{
	g_reset =0;
	GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_LOW);
	LCD_clearScreen();
	break;

}

	}

}









