/***************************************************************
 * File: gpio.h
 * Author: Makeen Khattab
 * Date: February 9, 2024
 * Description: Contains all general purpose register prototype
 ***************************************************************
 ***************************************************************/


#ifndef GPIO_H_
#define GPIO_H_
/*---------------------------INCLUDES----------------------------*/

#include<avr/io.h>
#include "common_macros.h"
#include "std_types.h"

/*-------------Pre-processor Constants and configuration----------*/

/*
 * Set a identification "0" for PORTA instead of using PORTA Address
 * mapped in RAM to enhance the code logic
 *
 * */
#define PORTA_ID 									0

/*
 *  Set a identification "1" for PORTB instead of using PORTB Address
 * mapped in RAM to enhance the code logic
 *
 * */
#define PORTB_ID 									1

/*
 * Set a identification "2" for PORTC instead of using PORTC Address
 * mapped in RAM to enhance the code logic
 *
 * */
#define PORTC_ID 									2

/*
 *  Set a identification "3" for PORTD instead of using PORTD Address
 * mapped in RAM to enhance the code logic
 *
 * */
#define PORTD_ID 									3

/* Max number of Ports in ATMEGA32 which is 4 Ports "PORTA" ,"PORTB","PORTC","PORTD"*/
#define GPIO_NUM_OF_PORTS							4

/* Max number of Pins in each port in ATMEGA32 which is 8 Pins*/
#define GPIO_NUM_OF_PINS							8

#define PIN0_ID										0
#define PIN1_ID										1
#define PIN2_ID										2
#define PIN3_ID										3
#define PIN4_ID										4
#define PIN5_ID										5
#define PIN6_ID										6
#define PIN7_ID										7


/* Default values written on each Pin in a Port to set it's direction Either Input or Output */
typedef enum
{
	/*When you write logic zero on a Pin on DDR register the pin is set as an Input pin*/
	PIN_INPUT,

	/*When you write logic one on a Pin DDR register the pin is set as an Output pin*/
	PIN_OUTPUT

}GPIO_PinDirectionType;

/* Default values written on each Port to set the whole port direction to be Either Input or Output */
typedef enum
{

	/*When you write logic zero on a DDR register the whole Port is set as an input Port */
	PORT_INPUT,

	/*When you write 1111 1111 on a DDR register the whole Port is set as an output Port */
	PORT_OUTPUT=0xFF

}GPIO_PortDirectionType;

/*---------------------------FUNCTION DECLARATION----------------------------*/

/* Setting the pin on each port to be either Input pin or Output pin */
void GPIO_setupPinDirection(uint8 a_portNum,uint8 a_pinNum,GPIO_PinDirectionType a_direction);

/* Writing a logic 0 or 1 on an Output pin */
void GPIO_writePin(uint8 a_portNum,uint8 a_pinNum,uint8 a_value);

/* Changing the value of Output pin from "0" to "1" or from "1" to "0"  */
void GPIO_togglePin(uint8 a_portNum,uint8 a_pinNum);

/* Reading the value on an Input pin and returning it's value */
uint8 GPIO_readPin(uint8 a_portNum,uint8 a_pinNum);

/* Setting the whole Port to be either Input or Output Port */
void GPIO_setupPortDirection(uint8 a_portNum,GPIO_PortDirectionType a_direction);

/* Writing any value ranged between (0000 0000 "0x00") to (1111 1111 "0xFF") on a Port */
void GPIO_writePort(uint8 a_portNum,uint8 a_value);

/* Reading any value ranged between (0000 0000 "0x00") to (1111 1111 "0xFF") on a Port */
uint8 GPIO_readPort(uint8 a_portNum);


#endif /* GPIO_H_ */
