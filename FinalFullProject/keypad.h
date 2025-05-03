#ifndef KEYPAD_H_
#define KEYPAD_H_
#include"Std_Types.h"

#define KEYPAD_4x4					1

#define	KEYPAD_4x3					0

#define PULLUP						1

#define	PULLDOWN					0

#define PORT_COLUMNID 			    PORTB_ID
#define PIN1_COLUMNID				PIN0_ID
#define PIN2_COLUMNID				PIN1_ID
#define PIN3_COLUMNID				PIN2_ID
#if(KEYPAD_4x4)
#define PIN4_COLUMNID				PIN3_ID
#endif
#define PORT_ROWID 					PORTA_ID
#define PIN1_ROWID					PIN0_ID
#define PIN2_ROWID					PIN1_ID
#define PIN3_ROWID					PIN2_ID
#define PIN4_ROWID					PIN3_ID

#if(PULLUP ==1)
#define COMPVALUE					0
#define WRITEVALUE					0


#elif(PULLDOWN ==1)
#define COMPVALUE					1
#define WRITEVALUE					1
#endif


#define BUTTON_POSITION		 ((a_row*COLNUM)+a_col+1)


#if(KEYPAD_4x4==1)

#define ROWNUM 		4
#define COLNUM 		4

#elif(KEYPAD_4x3==1)
#define ROWNUM 		4
#define COLNUM 		3
#endif

void KEYPAD_init(void);
uint8 KEYPAD_getPressedKey(void);
#endif /* KEYPAD_H_ */
