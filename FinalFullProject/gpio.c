/***************************************************************
 * File: gpio.c
 * Author: Makeen Khattab
 * Date: February 10, 2024
 * Description: Contains all general purpose register implementation
 ***************************************************************
 ***************************************************************/


/*---------------------------INCLUDES--------------------------*/
#include"gpio.h"

/*-----------------------FUNCTION Definitions------------------*/


/* Setting the pin on each port to be either Input pin or Output pin */
void GPIO_setupPinDirection( uint8 a_portNum,uint8 a_pinNum,GPIO_PinDirectionType a_direction )
{

	/* Checking the number given by the user is valid  for Port number and Pin number */
	if( a_portNum>=GPIO_NUM_OF_PORTS || a_pinNum>=GPIO_NUM_OF_PINS )
		{

		/*------- If the number is not within the range--------*/
		/*-------------------Do nothing------------------------*/

		}
	/*------- If the number is within the range--------*/
	else
	{

		/*------- Selecting the Port you will set the Pin Direction in --------*/
		switch ( a_portNum )
		{

				case PORTA_ID :

		/*------- Selecting the Mode you will set the Pin Direction to --------*/
					if( a_direction == PIN_INPUT)
					{

						/* Common Macro function to clear a bit*/
						CLEAR_BIT( DDRA,a_pinNum );

					}
					else if ( a_direction == PIN_OUTPUT )
					{

						/* Common Macro function to Set a bit to 1*/
						SET_BIT( DDRA,a_pinNum );

					}
					else
						;

					break;

				case PORTB_ID :

				/*------- Selecting the Mode you will set the Pin Direction to --------*/
					if( a_direction == PIN_INPUT )
					{

						/* Common Macro function to clear a bit*/
						 CLEAR_BIT( DDRB,a_pinNum );

					}

					else if ( a_direction == PIN_OUTPUT )
					{

						/* Common Macro function to Set a bit to 1*/
						SET_BIT( DDRB,a_pinNum );

					}

					else
						;


					break;

				case PORTC_ID :

					/*------- Selecting the Mode you will set the Pin Direction to --------*/
					if( a_direction == PIN_INPUT )
					{
					/* Common Macro function to clear a bit*/
						 CLEAR_BIT( DDRC,a_pinNum );

					}

					else if ( a_direction == PIN_OUTPUT )
					{

						/* Common Macro function to Set a bit to 1*/
	   					 SET_BIT( DDRC,a_pinNum );

					}

					else
						;


					break;

				case PORTD_ID :

					/*------- Selecting the Mode you will set the Pin Direction to --------*/
					if( a_direction == PIN_INPUT )
					{

						/* Common Macro function to clear a bit*/
						CLEAR_BIT( DDRD,a_pinNum );

					}

					else if ( a_direction == PIN_OUTPUT )
					{
						/* Common Macro function to Set a bit to 1*/
						SET_BIT( DDRD,a_pinNum );

					}

					else
						;

					break;


				default:
					;

				}


	}



}


/* Writing a logic 0 or 1 on an Output pin */
void GPIO_writePin(uint8 a_portNum,uint8 a_pinNum,uint8 a_value)
{

	/* Checking the number given by the user is valid  for Port number and Pin number */

	if( a_portNum>=GPIO_NUM_OF_PORTS || a_pinNum>=GPIO_NUM_OF_PINS )
			{

			/*------- If the number is not within the range--------*/
			/*-------------------Do nothing------------------------*/

			}
	/*------- If the number is within the range--------*/
		else
		{

		/*------- Selecting the Port you will write on a Pin in --------*/
			switch ( a_portNum )
			{
					case PORTA_ID :

		/*------- Selecting the value you will write on a Pin in --------*/
						if( a_value == LOGIC_LOW )
						{

							/* Common Macro function to clear a bit*/
							CLEAR_BIT( PORTA,a_pinNum );

						}
						else if ( a_value == LOGIC_HIGH )
						{

							/* Common Macro function to Set a bit to 1*/
							SET_BIT( PORTA,a_pinNum );

						}
						else
							;

						break;

					case PORTB_ID :

					/*------- Selecting the value you will write on a Pin in --------*/
						if( a_value == LOGIC_LOW )
						{

							/* Common Macro function to clear a bit*/
							 CLEAR_BIT( PORTB,a_pinNum );

						}

						else if ( a_value == LOGIC_HIGH )
						{

							/* Common Macro function to Set a bit to 1*/
							SET_BIT( PORTB,a_pinNum );

						}

						else
							;


						break;

					case PORTC_ID :

						/*------- Selecting the value you will write on a Pin in --------*/
						if( a_value == LOGIC_LOW )
						{

							/* Common Macro function to clear a bit*/
							 CLEAR_BIT( PORTC,a_pinNum );

						}

						else if ( a_value == LOGIC_HIGH )
						{

							/* Common Macro function to Set a bit to 1*/
		   					 SET_BIT( PORTC,a_pinNum );

						}

						else
							;


						break;

					case PORTD_ID :

						/*------- Selecting the value you will write on a Pin in --------*/
						if( a_value == LOGIC_LOW )
						{

							/* Common Macro function to clear a bit*/
							CLEAR_BIT( PORTD,a_pinNum );

						}

						else if ( a_value == LOGIC_HIGH )
						{

							/* Common Macro function to Set a bit to 1*/
							SET_BIT( PORTD,a_pinNum );

						}

						else
							;

						break;


					default:
						;

					}


		}




}



void GPIO_togglePin(uint8 a_portNum,uint8 a_pinNum)
{
	/* Checking the number given by the user is valid  for Port number and Pin number */

	if( a_portNum>=GPIO_NUM_OF_PORTS || a_pinNum>=GPIO_NUM_OF_PINS )
			{

			/*------- If the number is not within the range--------*/
			/*-------------------Do nothing------------------------*/

			}
	/*------- If the number is within the range--------*/
		else
		{

		/*------- Selecting the Port you will toggle a Pin in --------*/
			switch ( a_portNum )
			{
					case PORTA_ID :

				/* Common Macro function to Toggle a bit*/
					TOGGLE_BIT(PORTA,a_pinNum);


						break;

					case PORTB_ID :

				/* Common Macro function to Toggle a bit*/
						TOGGLE_BIT(PORTB,a_pinNum);

						break;

					case PORTC_ID :

				/* Common Macro function to Toggle a bit*/
						TOGGLE_BIT(PORTC,a_pinNum);

						break;

					case PORTD_ID :

				/* Common Macro function to Toggle a bit*/
						TOGGLE_BIT(PORTD,a_pinNum);

						break;


					default:
						;

					}


		}


}



/* Reading the value on an Input pin and returning it's value */
uint8 GPIO_readPin( uint8 a_portNum,uint8 a_pinNum )
{
	uint8 a_pinValue = LOGIC_LOW;

	/* Checking the number given by the user is valid  for Port number and Pin number */
	if( a_portNum>=GPIO_NUM_OF_PORTS || a_pinNum>=GPIO_NUM_OF_PINS )
	{

		/*------- If the number is not within the range--------*/

						return a_pinValue;

	}

	/*------- If the number is within the range--------*/
	else
	{
		/*------- Selecting the Port you will read a Pin from --------*/
		switch ( a_portNum )
		{
		case PORTA_ID :
		/*------- Checking the Pin value by a Common macro function--------*/
			if( BIT_IS_SET(PINA,a_pinNum) )
			{
				a_pinValue=LOGIC_HIGH;

			}
			else
				a_pinValue=LOGIC_LOW;


			break;

		case PORTB_ID :
			/*------- Checking the Pin value by a Common macro function--------*/
			if( BIT_IS_SET(PINB,a_pinNum) )
			{
				a_pinValue=LOGIC_HIGH;

			}
			else
				a_pinValue=LOGIC_LOW;


					break;

		case PORTC_ID :
			/*------- Checking the Pin value by a Common macro function--------*/
			if( BIT_IS_SET(PINC,a_pinNum) )
			{
				a_pinValue=LOGIC_HIGH;

			}
			else
				a_pinValue=LOGIC_LOW;


					break;

		case PORTD_ID :
			/*------- Checking the Pin value by a Common macro function--------*/

			if( BIT_IS_SET(PIND,a_pinNum) )
			{
				a_pinValue=LOGIC_HIGH;

			}
			else
				a_pinValue=LOGIC_LOW;


					break;

		default:
			;

		}


	}

	return a_pinValue;
}


/* Setting the whole Port to be either Input or Output Port
 * */
void GPIO_setupPortDirection( uint8 a_portNum,GPIO_PortDirectionType a_direction )
{

	/* Checking the number given by the user is valid  for Port number and Pin number
	 *
	 *
	 *  Direction of Port must be either PORT_INPUT or PORT_OUTPUT
	 *  */
	if( a_portNum>=GPIO_NUM_OF_PORTS || ((a_direction !=PORT_INPUT ) && (a_direction !=PORT_OUTPUT )) )
		{

		/*------- If the number is not within the range--------*/
		/*-------------------Do nothing------------------------*/

		}

		/*------- If the number is within the range--------*/
	else
	{
		/*------- Selecting the Port you will set the it's Direction --------*/
		switch ( a_portNum )
		{
				case PORTA_ID :

				DDRA=a_direction;

					break;

				case PORTB_ID :

				DDRB=a_direction;

					break;

				case PORTC_ID :

				DDRC=a_direction;

					break;

				case PORTD_ID :

				DDRD=a_direction;

					break;

				default:
					;

				}


	}





}



/* Writing any value ranged between (0000 0000 "0x00") to (1111 1111 "0xFF") on a Port */
void GPIO_writePort( uint8 a_portNum,uint8 a_value )
{

	/* Checking the number given by the user is valid  for Port number and Pin number
	 *
	 */
	if( a_portNum>=GPIO_NUM_OF_PORTS )
			{

			/*------- If the number is not within the range--------*/
			/*-------------------Do nothing------------------------*/

			}

			/*------- If the number is within the range--------*/
	else
	{

	/*------- Selecting the Port you will write a value on --------*/
	switch (a_portNum)
			{
			case PORTA_ID :
				PORTA=a_value;
				break;

			case PORTB_ID :
				PORTB=a_value;
						break;

			case PORTC_ID :
				PORTC=a_value;
						break;

			case PORTD_ID :
				PORTD=a_value;
						break;

			}
	}

}


/* Reading any value ranged between (0000 0000 "0x00") to (1111 1111 "0xFF") on a Port */
uint8 GPIO_readPort(uint8 a_portNum)
{
	uint8 a_portValue = LOGIC_LOW;
	/* Checking the number given by the user is valid  for Port number and Pin number */
	if( a_portNum>=GPIO_NUM_OF_PORTS )
				{

				/*------- If the number is not within the range----------*/
				/*------------------- Do nothing ------------------------*/

				}

				/*------- If the number is within the range--------*/
		else
		{

			/*------- Selecting the Port you will read a value from --------*/
		switch (a_portNum)
				{
				case PORTA_ID :

					a_portValue=PINA;

					break;

				case PORTB_ID :

					a_portValue=PINB;

					break;

				case PORTC_ID :

					a_portValue=PINC;

					break;

				case PORTD_ID :

					a_portValue=PIND;

							break;
				default:
					;
				}

		}

	return a_portValue;

}

