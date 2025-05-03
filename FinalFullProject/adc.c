#include"adc.h"
#include"gpio.h"
#include <avr/io.h>
#include "Common_Macros.h"


#if (ADC_INTERRUPTMODE ==1)
 static volatile void (*g_ADC_callBackPtr2Func)(void);
#endif

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	SET_BIT(ADCSRA,ADEN);
	ADMUX = (ADMUX&0x3F) | (((Config_Ptr->ref_volt)<<6) & 0xC0);
	CLEAR_BIT(ADMUX,ADLAR);
#if (ADC_POLLINGMODE ==1)
	CLEAR_BIT(ADCSRA,ADIE);
#elif (ADC_INTERRUPTMODE ==1)
	SET_BIT(ADCSRA,ADIE);

#endif

	ADCSRA=  (ADCSRA&(0xF8)) | ((Config_Ptr->prescaler)&(0x07));


}

#if(ADC_POLLINGMODE ==1)
uint16 ADC_readChannel(ADC_chNum a_chNum)
{
	ADMUX= ((ADMUX & 0xE0) | a_chNum);
	SET_BIT(ADCSRA,ADSC);
	while(!(BIT_IS_SET(ADCSRA,ADIF)));

		SET_BIT(ADCSRA,ADIF);
		return (uint16)(ADC);
}
#elif(ADC_INTERRUPTMODE ==1)
void ADC_readChannel(ADC_chNum a_chNum)
{
	ADMUX= ((ADMUX & 0xE0) | a_chNum);
	SET_BIT(ADCSRA,ADSC);


}

#endif

void ADC_disable(void)
{
	CLEAR_BIT(ADCSRA,ADEN);

}

#if (ADC_INTERRUPTMODE ==1)

void ADC_setCallBack(void(*Ptr2Func)(void))
{
	g_ADC_callBackPtr2Func=Ptr2Func;
}

ISR(ADC_vect)
{
	(*g_ADC_callBackPtr2Func)();

}

#endif
