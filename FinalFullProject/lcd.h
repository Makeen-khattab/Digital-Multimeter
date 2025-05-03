/***************************************************************
 * File: lcd.h
 * Author: Makeen Khattab
 * Date: February 10, 2024
 * Description: Contains all general purpose register prototype
 ***************************************************************
 ***************************************************************/
/*---------------------------INCLUDES----------------------------*/
#ifndef LCD_H_
#define LCD_H_
#include "Std_Types.h"

/*-------------Pre-processor Constants and configuration----------*/
#define LCD_4BITSMODE			   1
#define LCD_8BITSMODE              0


/*Selecting the mode and the number of lines we want to display in-------------------*/
#define 	   LCD_EIGHTBIT_ONELINE		    				 0x30
#define 	   LCD_EIGHTBIT_TWOLINE 	     	   			 0x38
#define 	   LCD_FOURBIT_ONELINE 		     				 0x20
#define 	   LCD_FOURBIT_TWOLINE 		     				 0x28
/*-----------------------------------------------------------------------------------*/
/* In the 4 bit mode LCD must be initialized by sending the  two consecutive commands*/
#define		   LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   		 0x33
#define 	   LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   		 0x32
/*-----------------------------------------------------------------------------------*/
#define 	   LCD_ENTRYMODE				                 0x06
#define 	   LCD_DISPLAYOFF_CURSOROFF		 				 0x08
#define 	   LCD_DISPLAYON_CURSOROFF		     			 0x0C
#define 	   LCD_DISPLAYON_CURSORON		                 0x0E
#define 	   LCD_DISPLAYON_CURSORBLINK	                 0x0F
#define 	   LCD_SHIFT_DISPLAYLEFT			             0x18
#define 	   LCD_SHIFT_DISPLAYRIGHT			             0x1C
#define 	   LCD_MOVE_CURSORLEFT				             0x10
#define 	   LCD_MOVE_CURSORRIGHT			                 0x14
#define 	   LCD_CLEAR_DISPLAY				             0x01
#define 	   LCD_SET_CURSOR_LOCATION             			 0x80

#define LCD_DATA_PORTID										PORTD_ID
#define LCD_RS_PORTID										PORTD_ID
#define LCD_SELECT_COMMAND_REGISTER							LOGIC_LOW
#define LCD_SELECT_DATA_REGISTER							LOGIC_HIGH
#define LCD_RS_PINID										PIN0_ID
#define LCD_EN_PORTID										PORTD_ID
#define LCD_EN_PINID										PIN1_ID

#if(LCD_8BITSMODE==1)


#elif(LCD_4BITSMODE ==1 )
#define LCD_PIN0ID											PIN4_ID
#define LCD_PIN1ID											PIN5_ID
#define LCD_PIN2ID											PIN6_ID
#define LCD_PIN3ID											PIN7_ID
#endif

#define MAXROWPOS											  2
#define MINROWPOS											  1
#define FIRSTROWADD											 0x00
#define SECROWADD											 0x40
#define MAXCOLPOS											  16
#define MINCOLPOS											  1
#define ZEROASCII											 0x30
#define MAXDIGITS											  15
#define ACCURACY											  4
#define MAXFLOATDIG											  10
#define DOT													  '.'
#define INTEGERNUM											  'i'
#define FLOATNUM											  'F'

/*Initialize the module to be Capable to send commands to LCD*/
void LCD_init(void);
void LCD_sendCommand(uint8 LCD_commands);
void LCD_displayCharachter(uint8 a_char);
void LCD_displayString(uint8*const a_char);
void LCD_moveCursor(uint8 a_row,uint8 a_column) ;
void LCD_displayStringRowColumn(uint8 a_row,uint8 a_column,uint8*const a_char);
void LCD_clearScreen();
void LCD_intgerToString(uint32 a_num);
void LCD_floatToString (float32 a_num);




#endif /* LCD_H_ */



