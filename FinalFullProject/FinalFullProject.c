
/**********************************************************************
 * Author: Makeen Khattab		                                      *
 * Date:   7/5/2024		                                              *
 * Description: Dmm Project											  *
 *                                                                    *
 *                                                                    *
 **********************************************************************/


/***************************** INCLUDES *******************************/
#include "util/delay.h"
#include "dmmAmmeter.h"
#include "dmm_Ohmmeter.h"
#include "dmm_voltmeter.h"
#include "gpio.h"
#include "lcd.h"
#include "keypad.h"
#include "adc.h"
#include <avr/interrupt.h>
/***************************** Global Variables ******************************/

volatile uint8 g_reset =0;
extern volatile uint8 g_ohmMeterEnter ;
extern volatile uint8 g_ammMeterEnter;
extern volatile uint8 g_voltMeterEnter;

/***************************** Macros ****************************************/
#define VOLTMETER_CIRCUIT												1
#define AMMETER_CIRCUIT													2
#define OHMMETER_CIRCUIT												3


/***************************** Function Prototypes ******************************/

void return_init(void);

/***************************** File.main ******************************/

int main(void)
{
	/* Variable used by Keypad*/
	uint8 keyPressed,firstEnteryMenu=1,firstEnteryVoltmeter=1,firstEnteryAmmeter=1,firstEnteryOhmmeter=1;
	/*Configuration of ADC*/
	ADC_ConfigType attributes = {ADC_AVCC,ADC_F_CPUOVER_4};
	/* Enabling the Global Variable enable to trigger an interrupt by Button*/
	SREG|=1<<7;
	/*Setting the Power pin as an output pin*/
	GPIO_setupPinDirection(PORTC_ID, PIN0_ID, PIN_OUTPUT);

/******************Initialization*************************/
	LCD_init();
	KEYPAD_init();
	return_init();
	ADC_init(&attributes);
	AMMETER_init();
	VOLTMETER_init();
	OHMMETER_init();

	/**********************************************************************
	 *                     Entery to the System		                      *
	 **********************************************************************/
			GPIO_writePin(PORTC_ID, PIN0_ID,LOGIC_HIGH);
			LCD_moveCursor(1, 1);
			LCD_displayString("Welcome to Dmm");
			_delay_ms(500);
			LCD_clearScreen();
while(1)
{

	 /**********************************************************************
	 *                  Choosing the Circuit	                           *
	 **********************************************************************/
	   LCD_moveCursor(1, 1);
	   LCD_displayString("Please sel a ");
	   LCD_moveCursor(2, 1);
	   LCD_displayString("value to meas.");
	   _delay_ms(500);
	   LCD_clearScreen();

	do
	{

	 /**********************************************************************
	 *             	    Case if user entered a wrong number                *
	 **********************************************************************/
	if(!firstEnteryMenu)
	 {
	   LCD_clearScreen();
	   LCD_moveCursor(1, 1);
	   LCD_displayString("Please Press on");
	   LCD_moveCursor(2, 1);
	   LCD_displayString("One of Av Circ.");
	   _delay_ms(500);
	   LCD_clearScreen();
		}

	 /**********************************************************************
	 *             	    Menu for the user to choose circuit from           *
	 **********************************************************************/
		LCD_moveCursor(1,1);
		LCD_displayString("1)Volt");
		LCD_moveCursor(2,1);
		LCD_displayString("2)Current");
		LCD_displayString(" 3)Res");

		keyPressed=KEYPAD_getPressedKey();
		firstEnteryMenu=0;
		}
		while((keyPressed!= VOLTMETER_CIRCUIT) && (keyPressed!=  AMMETER_CIRCUIT) && (keyPressed!=  OHMMETER_CIRCUIT));

	/* Returning the flag to it's default value for the upcoming Enteries*/
	LCD_clearScreen();
	firstEnteryMenu=1;


	switch (keyPressed)
	{

	case VOLTMETER_CIRCUIT :

		do
		{

			 /**********************************************************************
			 *             	    Case if user entered a wrong number                *
			 **********************************************************************/
			if(!firstEnteryVoltmeter)
			 {
			   LCD_clearScreen();
			   LCD_moveCursor(1, 1);
			   LCD_displayString("Please Press on");
			   LCD_moveCursor(2, 1);
			   LCD_displayString("One of Modes.");
			   _delay_ms(500);
			   LCD_clearScreen();
				}

			 /**********************************************************************
			 *        Menu for the user to choose Mode of Voltmeter from           *
			 **********************************************************************/
			   LCD_moveCursor(1, 1);
			   LCD_displayString("Please Select");
			   LCD_moveCursor(2, 1);
			   LCD_displayString("AC or DC");
			   _delay_ms(1000);
			   LCD_clearScreen();
			   LCD_moveCursor(1, 1);
			   LCD_displayString(" 1) AC");
			   LCD_moveCursor(2, 1);
			   LCD_displayString(" 2) DC");
			   _delay_ms(150);
			   keyPressed=KEYPAD_getPressedKey();
			    firstEnteryVoltmeter=0;
				}
				while((keyPressed!= ACVOLT) && (keyPressed!=DCVOLT));

		/* Returning the flag to it's default value for the upcoming Enteries*/
			firstEnteryVoltmeter=1;


	    /**********************************************************************
		 * Selecting the type of volt we are going to measure either AC or DC *
		 **********************************************************************/


		switch (keyPressed)
		{
			case ACVOLT:

		/* Selecting the relayv that switch the output of the Voltmeter circuit on AC to DC circuit */
			GPIO_writePin(PORTB_ID,PIN4_ID, LOGIC_LOW);

		 /**********************************************************************
		  *             Showing the user that he selected Ac mode              *
		  **********************************************************************/
				LCD_clearScreen();
				LCD_displayString("AC");
				_delay_ms(300);
				LCD_clearScreen();
		  /**********************************************************************
		   *          Requesting the range of voltage the user wish to measure  *
		   **********************************************************************/
				LCD_moveCursor(1, 1);
				LCD_displayString("Please sel req");
				LCD_moveCursor(2, 1);
				LCD_displayString("Range");
				_delay_ms(500);
				LCD_clearScreen();
			do
			  {

			 /**********************************************************************
			  *             	    Case if user entered a wrong number            *
			  **********************************************************************/
				if(!firstEnteryVoltmeter)
				{
				 LCD_clearScreen();
				 LCD_moveCursor(1, 1);
				 LCD_displayString("Please Press on");
				 LCD_moveCursor(2, 1);
				 LCD_displayString("One of Av Keys");
				 _delay_ms(500);
				 LCD_clearScreen();
				}

			 /**********************************************************************
			  *        Menu for the user to choose range of Voltmeter from         *
			  **********************************************************************/
				 LCD_moveCursor(1, 1);
				 LCD_displayString("1) 0.3V to 2V");
				 LCD_moveCursor(2,1);
				 LCD_displayString("2) 2V to 20v");
				 keyPressed=KEYPAD_getPressedKey();
				 firstEnteryVoltmeter=0;
				}
				while( (keyPressed!= VOLTMETERFIRSTRANGE) && (keyPressed!=VOLTMETERSECRANGE));

			/* Returning the flag to it's default value for the upcoming Enteries*/
				firstEnteryVoltmeter=1;

			 /**********************************************************************
			  *        Menu for the user to choose Range of Voltmeter from         *
			  **********************************************************************/
				switch (keyPressed)
				{
					case VOLTMETERFIRSTRANGE:

					LCD_clearScreen();
					LCD_displayString("First Range");
					 _delay_ms(500);
					LCD_clearScreen();

					VOLTMETER_firstRange();
						break;

					case VOLTMETERSECRANGE:

					LCD_clearScreen();
					LCD_displayString("Sec Range");
					 _delay_ms(500);
					LCD_clearScreen();

					VOLTMETER_secondRange();
					break;

				}

				break;

			case DCVOLT:

			/* Selecting the relayv that switch the output of the Voltmeter circuit on AC to DC circuit */
			GPIO_writePin(PORTB_ID,PIN4_ID, LOGIC_HIGH);

			/**********************************************************************
			 *        Showing the user that he selected Ac mode                   *
		     **********************************************************************/
			 LCD_clearScreen();
			 LCD_displayString("DC");
			 _delay_ms(300);
			 LCD_clearScreen();
			 /**********************************************************************
			  *          Requesting the range of voltage the user wish to measure  *
			  **********************************************************************/
			  LCD_moveCursor(1, 1);
			  LCD_displayString("Please sel req");
			  LCD_moveCursor(2, 1);
			  LCD_displayString("Range");
			  _delay_ms(500);
			  LCD_clearScreen();
		do
		  {

		  /**********************************************************************
		   *             	    Case if user entered a wrong number            *
		   **********************************************************************/
		  if(!firstEnteryVoltmeter)
			{
			  LCD_clearScreen();
			  LCD_moveCursor(1, 1);
			 LCD_displayString("Please Press on");
			 LCD_moveCursor(2, 1);
			 LCD_displayString("One of Av Keys");
			 _delay_ms(500);
			 LCD_clearScreen();
			}

			 /**********************************************************************
			  *        Menu for the user to choose range of Voltmeter from         *
			  **********************************************************************/
			 LCD_moveCursor(1, 1);
			 LCD_displayString("1) 0.3V to 2V");
			 LCD_moveCursor(2,1);
			 LCD_displayString("2) 2V to 20v");
			 keyPressed=KEYPAD_getPressedKey();
			 firstEnteryVoltmeter=0;
			}
			while( (keyPressed!= VOLTMETERFIRSTRANGE) && (keyPressed!=VOLTMETERSECRANGE));

			/* Returning the flag to it's default value for the upcoming Enteries*/
				firstEnteryVoltmeter=1;

		 /**********************************************************************
		  *        Menu for the user to choose Range of Voltmeter from         *
		  **********************************************************************/
			switch (keyPressed)
			{
				case VOLTMETERFIRSTRANGE:

		 /**********************************************************************
		  *  Select First range of voltmeter 0v to 2v         				   *
		  **********************************************************************/

				LCD_clearScreen();
				LCD_displayString("First Range");
				 _delay_ms(500);
				LCD_clearScreen();
		/* 					Entering the first range						   */
				VOLTMETER_firstRange();
					break;

				case VOLTMETERSECRANGE:

		/**********************************************************************
		 *  Select sec range of voltmeter 2v to 20v         				  *
		 **********************************************************************/
				LCD_clearScreen();
				LCD_displayString("Sec Range");
				 _delay_ms(500);
				LCD_clearScreen();
		/* 					Entering the sec range						   */
				VOLTMETER_secondRange();
				break;

			}


		break;

		default:
			;
		}

		break;


		case AMMETER_CIRCUIT:

	    /**********************************************************************
		 *          Requesting the range of Current the user wish to measure  *
		 **********************************************************************/
		LCD_moveCursor(1, 1);
		LCD_displayString("Please sel req");
		LCD_moveCursor(2, 1);
		LCD_displayString("Range");
		_delay_ms(500);
		LCD_clearScreen();
		do
		  {

		 /**********************************************************************
		  *             	    Case if user entered a wrong number            *
		  **********************************************************************/
			if(!firstEnteryAmmeter)
			{
			 LCD_clearScreen();
			 LCD_moveCursor(1, 1);
			 LCD_displayString("Please Press on");
			 LCD_moveCursor(2, 1);
			 LCD_displayString("One of Av Keys");
			 _delay_ms(500);
			 LCD_clearScreen();
			}

		 /**********************************************************************
		  *        Menu for the user to choose range of Ammeter from         *
		  **********************************************************************/
			 LCD_moveCursor(1, 1);
			 LCD_displayString("1) 10mA to 100mA");
			 LCD_moveCursor(2,1);
			 LCD_displayString("2) 100mA to 1A");
			 keyPressed=KEYPAD_getPressedKey();
			 firstEnteryAmmeter=0;
			}
			while( (keyPressed!= AMMETERFIRSTRANGE) && (keyPressed!=AMMMETERSECRANGE));

		/* Returning the flag to it's default value for the upcoming Enteries*/
			firstEnteryAmmeter=1;

		 /**********************************************************************
		  *        Menu for the user to choose Range of Ammeter from         *
		  **********************************************************************/
			switch (keyPressed)
			{
				case AMMETERFIRSTRANGE:

				LCD_clearScreen();


		 /**********************************************************************
		  *  Select First range of voltmeter 10mA to 100mA         			   *
		  **********************************************************************/

				LCD_displayString("First Range");
				 _delay_ms(500);
				LCD_clearScreen();

				AMMETER_firstRange();
					break;

				case AMMMETERSECRANGE:

				LCD_clearScreen();

		 /**********************************************************************
		  *  Select First range of voltmeter 100mA to 1A         			   *
		  **********************************************************************/
				LCD_displayString("Sec Range");
				 _delay_ms(500);
				LCD_clearScreen();

				AMMMETER_secondRange();
				break;

			}

			break;


			case OHMMETER_CIRCUIT :


		  /**********************************************************************
		   *       Requesting the range of resistance the user wish to measure  *
		   **********************************************************************/
				LCD_moveCursor(1, 1);
				LCD_displayString("Please sel req");
				LCD_moveCursor(2, 1);
				LCD_displayString("Range");
				_delay_ms(500);
				LCD_clearScreen();
				do
				  {

				 /**********************************************************************
				  *             	    Case if user entered a wrong number            *
				  **********************************************************************/
					if(!firstEnteryOhmmeter)
					{
					 LCD_clearScreen();
					 LCD_moveCursor(1, 1);
					 LCD_displayString("Please Press on");
					 LCD_moveCursor(2, 1);
					 LCD_displayString("One of Av Keys");
					 _delay_ms(500);
					 LCD_clearScreen();
					}

				 /**********************************************************************
				  *        Menu for the user to choose range of Ohmmeter from          *
				  **********************************************************************/
					 LCD_moveCursor(1, 1);
					 LCD_displayString("1)1.3kOHM");
					 LCD_moveCursor(2,1);
					 LCD_displayString("2)10kOhm");
					 LCD_displayString(" 3)1MOhm");
					 keyPressed=KEYPAD_getPressedKey();
					 firstEnteryOhmmeter=0;
					}
					while( (keyPressed!= OHMMETERFIRSTRANGE) && (keyPressed!=OHMMETERSECRANGE)&& (keyPressed!=OHMMETERTHIRDRANGE));

				/* Returning the flag to it's default value for the upcoming Enteries*/
					firstEnteryOhmmeter=1;

				 /**********************************************************************
				  *        Menu for the user to choose Range of Ohmeter from 	       *
				  **********************************************************************/
					switch (keyPressed)
					{
						case OHMMETERFIRSTRANGE:

						LCD_clearScreen();
				 /**********************************************************************
				  *  Select First range of voltmeter 0 Ω to 1.3kΩ        			   *
				  **********************************************************************/
						LCD_displayString("First Range");
						 _delay_ms(500);
						LCD_clearScreen();

						OHMMETER_firstRange();
							break;

						case OHMMETERSECRANGE:

						LCD_clearScreen();
				 /**********************************************************************
				  *  Select First range of voltmeter 1.3kΩ to 10kΩ        		       *
				  **********************************************************************/
						LCD_displayString("Sec Range");
						 _delay_ms(500);
						LCD_clearScreen();

						OHMMETER_secondRange();
						break;

						case OHMMETERTHIRDRANGE:
						LCD_clearScreen();
				 /**********************************************************************
				  *  Select First range of voltmeter 10kΩ to 1MΩ 					   *
				  **********************************************************************/

						LCD_displayString("Third Range");
						 _delay_ms(500);
						LCD_clearScreen();

						OHMMETER_thirdRange();
						break;

					}

					break;

	}

}

}

void return_init(void)
{
	GPIO_setupPinDirection(PORTD_ID,PIN2_ID,PIN_INPUT);
	/* Connecting it with an internal Pull up resistor */
	GPIO_writePin(PORTD_ID, PIN2_ID, LOGIC_HIGH);
	/*Interrupt with Any Falling Edge*/
    MCUCR = ((MCUCR & 0xFC) | (0x02)); // Interrupt with Falling Edge
	GICR =   ((GICR & 0xBF) | (1<<6));

}

ISR(INT0_vect)
{
	if(g_ammMeterEnter == 1)
	{
	g_reset=1;
	g_ammMeterEnter = 0;
	}
	else if (g_voltMeterEnter == 1)
	{
		g_reset=1;
		g_voltMeterEnter = 0;

	}
	else if(g_ohmMeterEnter == 1)
	{
		g_reset =1;
		g_ohmMeterEnter=0;

	}
	else
		g_reset=0;

}
