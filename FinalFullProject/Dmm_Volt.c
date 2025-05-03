#include "dmm_voltmeter.h"
#include "gpio.h"
#include "util/delay.h"
#include "lcd.h"
#include "adc.h"


extern volatile  uint8 g_reset;
/* Indication that we entered the voltmeter circuit*/
 volatile uint8 g_voltMeterEnter = 0;

void VOLTMETER_init(void)
{
	/**************Relay Pin on ATMEGA32******************/
	GPIO_setupPinDirection(PORTA_ID,PIN7_ID,PIN_OUTPUT);
	/**************Relay Pin Of AC to DC******************/
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_OUTPUT);

	/**************Led pin output*************************/
	GPIO_setupPinDirection(PORTC_ID, PIN1_ID, PIN_OUTPUT);

}

void VOLTMETER_firstRange(void)
{ float32 a_VoltValue;

/*Assuring that you pushed the reset button while you are at Voltmeter section*/
	g_voltMeterEnter = 1;
/******** Relay selection line for first range 0 1 ***************/
	GPIO_writePin(PORTA_ID,PIN7_ID,LOGIC_LOW);
	GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_HIGH);

	while(1)
	{

/**************The volt value read on the ADC Hardware*******************/
	a_VoltValue= MAX1*((4.5*ADC_readChannel(ADC6))/DIGITALMAX);

	/*********************************************
	 * Checking that you pushed the reset button
     * by a an indication variable changed in ISR
     * ********************************************/
	 if(g_reset == 1)
		 {
		 	g_reset =0;
		 	GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_LOW);
		 	LCD_clearScreen();
		 	break;
		 }


	LCD_floatToString(a_VoltValue);
	LCD_displayString(" V");
	_delay_ms(500);

	LCD_clearScreen();
/*********************************************
* Checking that you pushed the reset button
* by a an indication variable changed in ISR
* ********************************************/
	 if(g_reset == 1)
	 {
	 	g_reset =0;
	 	GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_LOW);
	 	LCD_clearScreen();
	 	break;

	 }
	}


}
void VOLTMETER_secondRange(void)
{ float32 a_VoltValue;

/*Assuring that you pushed the reset button while you are at Voltmeter section*/
	g_voltMeterEnter = 1;
/******** Relay selection line for first range 1 1 ***************/
	GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_HIGH);
	GPIO_writePin(PORTA_ID,PIN7_ID,LOGIC_HIGH);

	while(1)
	{
	/**************The volt value read on the ADC Hardware*******************/
	a_VoltValue=MAX2*((4.5*ADC_readChannel(ADC6))/DIGITALMAX);

	/*********************************************
	* Checking that you pushed the reset button
    * by a an indication variable changed in ISR
	* ********************************************/
	 if(g_reset == 1)
		 {
		 	g_reset =0;
		 	GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_LOW);
		 	LCD_clearScreen();
		 	break;

		 }

	LCD_floatToString(a_VoltValue);
	LCD_displayString(" V");
	_delay_ms(500);
	LCD_clearScreen();


/*********************************************
 * Checking that you pushed the reset button
* by a an indication variable changed in ISR
* ********************************************/
	 if(g_reset == 1)
	 {
	 	g_reset =0;
	 	GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_LOW);
	 	LCD_clearScreen();
	 	break;

	 }
	}



}
