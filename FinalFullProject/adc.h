#ifndef ADC_H_
#define ADC_H_

#include "Std_Types.h"

#define ADC_POLLINGMODE			   1
#define ADC_INTERRUPTMODE		   0

#if(ADC_INTERRUPTMODE==1)
#include "avr/interrupt.h"

extern volatile uint16 g_ADC_value;

#endif

#define ADC_MAXCOUNT		 1023
#define VREF				 5

typedef enum{
ADC_AREF,
ADC_AVCC,
ADC_RESERVED,
ADC_INTERNAL_2560mv

}ADC_ReferenceVolatge;


typedef enum{

	ADC_F_CPUOVER2,
	ADC_F_CPUOVER_2,
	ADC_F_CPUOVER_4,
	ADC_F_CPUOVER_8,
	ADC_F_CPUOVER_16,
	ADC_F_CPUOVER_32,
	ADC_F_CPUOVER_64,
	ADC_F_CPUOVER_128,
}ADC_Prescaler;
typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
}ADC_chNum;


typedef struct{
 ADC_ReferenceVolatge ref_volt;
 ADC_Prescaler prescaler;
}ADC_ConfigType;


void ADC_init(const ADC_ConfigType * Config_Ptr);
#if(ADC_POLLINGMODE==1)
uint16 ADC_readChannel(ADC_chNum a_chNum);
#elif(ADC_INTERRUPTMODE==1)
void ADC_readChannel(ADC_chNum a_chNum);
void ADC_setCallBack(void(*Ptr2Func)(void));
#endif
void ADC_disable(void);

#endif /* ADC_H_ */
