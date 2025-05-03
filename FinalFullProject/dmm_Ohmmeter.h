#ifndef DMM_OHMMETER_H_
#define DMM_OHMMETER_H_




/* 0 ohm to 1.3kohm*/
#define OHMMETERFIRSTRANGE						1
/* 1.3kohm to 10Kohm*/
#define OHMMETERSECRANGE						2
/* 10kohm to 1Megaohm*/
#define OHMMETERTHIRDRANGE						3

/**************First range limiting resistance***********************/
#define OHMMETERRES1							1.5
/**************Second range limiting resistance**********************/
#define OHMMETERRES2							940
/**************Third range limiting resistance***********************/
#define OHMMETERRES3						    100000

/*********************Mux input resistance***************************/
#define OHMMETERMUXRES							143

/**********Function responsible for ohmmeter initialization***************/
void OHMMETER_init(void);
/**********Function responsible for ohmmeter first range of Calculation***************/
void OHMMETER_firstRange(void);
/**********Function responsible for ohmmeter Second range of Calculation***************/
void OHMMETER_secondRange(void);
/**********Function responsible for ohmmeter Third range of Calculation***************/
void OHMMETER_thirdRange(void);

#endif /* DMM_OHMMETER_H_ */
