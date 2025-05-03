#include "lcd.h"
#include "gpio.h"
#include "Common_Macros.h"
#include <util/delay.h>


static void LCD_modifyString(uint8 *string_Ptr,uint32 a_num,uint8 a_numOfdigits,uint8 a_type);
static void LCD_modifyFloat(uint8 * string_Ptr,float32 a_num);
static void LCD_rearrange(uint8 * string_Ptr);
static void LCD_decToString(uint8*string_Ptr ,float32 a_decimalValue );
static void LCD_concatWith(uint8* a_mainStr,uint8 * string_Ptr,uint8 * string_Ptr2,uint8 a_symb);
void LCD_init(void)
{
	GPIO_setupPinDirection(LCD_RS_PORTID, LCD_RS_PINID, PIN_OUTPUT);
GPIO_setupPinDirection(LCD_EN_PORTID, LCD_EN_PINID, PIN_OUTPUT);
#if(LCD_8BITSMODE==1)
GPIO_setupPortDirection(LCD_DATA_PORTID, PORT_OUTPUT);


#elif(LCD_4BITSMODE ==1 )
GPIO_setupPinDirection(LCD_DATA_PORTID, LCD_PIN0ID, PIN_OUTPUT);
GPIO_setupPinDirection(LCD_DATA_PORTID, LCD_PIN1ID, PIN_OUTPUT);
GPIO_setupPinDirection(LCD_DATA_PORTID, LCD_PIN2ID, PIN_OUTPUT);
GPIO_setupPinDirection(LCD_DATA_PORTID, LCD_PIN3ID, PIN_OUTPUT);
#endif
/* as the LCD takes 15 millisecond to start up	*/
	_delay_ms(20);
#if(LCD_8BITSMODE==1)
LCD_sendCommand(LCD_EIGHTBIT_TWOLINE);
#elif(LCD_4BITSMODE ==1 )
LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1 );
LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2 );
LCD_sendCommand(LCD_FOURBIT_TWOLINE);
#endif

	LCD_sendCommand(LCD_DISPLAYON_CURSOROFF	);
	LCD_sendCommand(LCD_CLEAR_DISPLAY);
}

void LCD_sendCommand(uint8 a_LCD_commands)
{
	/* RS bit is responsible for register select for each of data and
	 *  commands to adjust settings*/
	GPIO_writePin(LCD_RS_PORTID,LCD_RS_PINID, LCD_SELECT_COMMAND_REGISTER);
		_delay_ms(1);
	/* EN bit is used to turn on the screen*/
	GPIO_writePin(LCD_EN_PORTID,LCD_EN_PINID,LOGIC_HIGH);
		_delay_ms(1);
#if(LCD_8BITSMODE==1)
		GPIO_writePort(LCD_DATA_PORTID,a_LCD_commands);
#elif(LCD_4BITSMODE ==1 )
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN0ID,GET_BIT(a_LCD_commands,4));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN1ID,GET_BIT(a_LCD_commands,5));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN2ID,GET_BIT(a_LCD_commands,6));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN3ID,GET_BIT(a_LCD_commands,7));
		_delay_ms(1);
		GPIO_writePin(LCD_EN_PORTID,LCD_EN_PINID,LOGIC_LOW);
		_delay_ms(1);
		GPIO_writePin(LCD_EN_PORTID,LCD_EN_PINID,LOGIC_HIGH);

		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN0ID,GET_BIT(a_LCD_commands,0));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN1ID,GET_BIT(a_LCD_commands,1));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN2ID,GET_BIT(a_LCD_commands,2));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN3ID,GET_BIT(a_LCD_commands,3));
#endif
		_delay_ms(1);
		GPIO_writePin(LCD_EN_PORTID,LCD_EN_PINID,LOGIC_LOW);
		_delay_ms(1);
}

void LCD_displayCharachter(uint8 a_char)
{
	/* RS bit is responsible for register select for each of data and
		 *  commands to adjust settings*/
		GPIO_writePin(LCD_RS_PORTID,LCD_RS_PINID,LCD_SELECT_DATA_REGISTER);
			_delay_ms(1);
		/* EN bit is used to turn on the screen*/

		GPIO_writePin(LCD_EN_PORTID,LCD_EN_PINID,LOGIC_HIGH);
			_delay_ms(1);
#if(LCD_8BITSMODE==1)
		GPIO_writePort(LCD_DATA_PORTID,a_char);
#elif(LCD_4BITSMODE ==1 )
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN0ID,GET_BIT(a_char,4));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN1ID,GET_BIT(a_char,5));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN2ID,GET_BIT(a_char,6));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN3ID,GET_BIT(a_char,7));
		_delay_ms(1);
		GPIO_writePin(LCD_EN_PORTID,LCD_EN_PINID,LOGIC_LOW);
		_delay_ms(1);
		GPIO_writePin(LCD_EN_PORTID,LCD_EN_PINID,LOGIC_HIGH);

		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN0ID,GET_BIT(a_char,0));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN1ID,GET_BIT(a_char,1));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN2ID,GET_BIT(a_char,2));
		GPIO_writePin(LCD_DATA_PORTID,LCD_PIN3ID,GET_BIT(a_char,3));
#endif
			_delay_ms(1);
			GPIO_writePin(LCD_EN_PORTID,LCD_EN_PINID,LOGIC_LOW);
			_delay_ms(1);
}

void LCD_displayString(uint8 * a_char)
{
	uint8*a_charPTR=a_char;

		while( *(a_charPTR)!= '\0')
		{

			LCD_displayCharachter(*a_charPTR);
			a_charPTR++;
		}
}

void LCD_moveCursor(uint8 a_row,uint8 a_col)
{
	uint8 a_command=0;
if((a_row>MAXROWPOS)|(a_row<MINROWPOS) | (a_col>MAXCOLPOS)|(a_col<MINCOLPOS) )
{
	/* Do nothing*/
}
else
{
		switch (a_row)
		{
		case 1 :
			a_command=FIRSTROWADD;
			break;
		case 2 :
			a_command=SECROWADD;
			break;
		}

LCD_sendCommand((a_command | (a_col-1)|(LCD_SET_CURSOR_LOCATION)));

}
}

void LCD_displayStringRowColumn(uint8 a_row,uint8 a_column,uint8  * a_char)
{
	LCD_moveCursor(a_row,a_column);
	LCD_displayString(a_char);
}
void LCD_clearScreen()
{

	LCD_sendCommand(LCD_CLEAR_DISPLAY);

}

void LCD_intgerToString(uint32 a_num)
{
	uint8 buff[16];
	LCD_modifyString(buff,a_num,MAXDIGITS,INTEGERNUM);
	LCD_displayString(buff);

}

static void LCD_modifyString(uint8 * string_Ptr,uint32 a_num,uint8 a_numOfdigits,uint8 a_type)
{ uint8 i=0;

if(a_type == INTEGERNUM)
{
if(a_num==0)
{
	*(string_Ptr)= ZEROASCII;
	*(string_Ptr+1)= '\0';
}
else
{
	while(a_num !=0 && i<a_numOfdigits)
	{
		*(string_Ptr +i)=  (((0x0F) & (a_num%10)) | ZEROASCII);

		a_num/=10;
		i++;
	}
	*(string_Ptr +i)='\0';
}
}
else if (a_type == FLOATNUM)
{
	if(a_num==0)
	{
		*(string_Ptr)= ZEROASCII;
		*(string_Ptr+1)= '\0';
	}
	else
	{
		while(i<a_numOfdigits)
		{
			*(string_Ptr +i)=  (((0x0F) & (a_num%10)) | ZEROASCII);

			a_num/=10;
			i++;
		}
		*(string_Ptr +i)='\0';
	}

}
	LCD_rearrange(string_Ptr);



}

void LCD_floatToString (float32 a_num)
{
	uint8 buff[16];
	LCD_modifyFloat(buff,a_num);
	LCD_displayString(buff);
}


static void LCD_modifyFloat(uint8 * string_Ptr,float32 a_num)
{
	uint8 LCD_dectoInt[ACCURACY+1];
	uint8 LCD_intToStr[MAXFLOATDIG+1];
	float64 a_decimalValue;

	uint32 a_numWithoutDec;

	a_decimalValue = a_num -FLOOR(a_num);

	a_numWithoutDec =FLOOR(a_num) ;


	LCD_decToString(LCD_dectoInt,a_decimalValue);
	LCD_modifyString(LCD_intToStr, a_numWithoutDec, MAXFLOATDIG,INTEGERNUM);
	LCD_concatWith(string_Ptr, LCD_intToStr, LCD_dectoInt,DOT);

}
static void LCD_rearrange(uint8 * string_Ptr)
{
	uint8 temp;
	uint8*Ptr_endString =string_Ptr ;

	while(*(Ptr_endString) != '\0')
	{
		Ptr_endString++;
	}

	Ptr_endString--;

	while(Ptr_endString - string_Ptr > 0)
	{
		temp= *Ptr_endString ;
		*Ptr_endString =*(string_Ptr);
		*(string_Ptr)=temp;
		Ptr_endString --;
		  string_Ptr++;
	}

}
static void LCD_decToString(uint8*string_Ptr ,float32 a_decimalValue )
{ uint8 a_numOfDigits=0 ;
	uint16 a_decimalTointeger ;

	 while( a_numOfDigits<ACCURACY )
		 {
			 a_decimalValue*=10;
			 a_numOfDigits++;
		 }

	 a_decimalTointeger =a_decimalValue;

	 LCD_modifyString( string_Ptr, a_decimalTointeger ,ACCURACY,FLOATNUM);

}
static void LCD_concatWith(uint8* a_mainStr,uint8 * string_Ptr,uint8 * string_Ptr2,uint8 a_symb)
{
	uint8 i=0;
	while(*string_Ptr !='\0')
	{
		*(a_mainStr+i) = *(string_Ptr);
		i++;
		string_Ptr++;
	}

	*(a_mainStr+i)=a_symb;
	i++;
	while(*string_Ptr2 !='\0')
		{
			*(a_mainStr+i) = *(string_Ptr2);
			string_Ptr2++;
			i++;
		}
	*(a_mainStr+i)='\0';


}



