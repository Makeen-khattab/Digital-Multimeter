#ifndef DMM_VOLTMETER_H_
#define DMM_VOLTMETER_H_

#include "Std_Types.h"

/*----------------------------------------------------------------------------------------------------------*/
#define MAX1    0.4
#define MAX2    4


#define VOLTMETERFIRSTRANGE						1

#define VOLTMETERSECRANGE						2


#define ACVOLT									1
#define DCVOLT									2
/*----------------------------------------------------------------------------------------------------------*/
#define DIGITALMAX							((4.5*1023)/5)
/*-----------------------------------------------------------------------------------------------------------*/
void VOLTMETER_init(void);
void VOLTMETER_firstRange(void);
void VOLTMETER_secondRange(void);

/*--------------------------------------------------------------------------------------------------------------*/


#endif
