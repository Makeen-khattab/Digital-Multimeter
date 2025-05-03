/*****************************************************
 * File: Std_Types
 * Author: Makeen Khattab
 * Date: February 6, 2024
 * Description: Contains all standard declaration
 ****************************************************/
#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_
/*Set a certain bit to 1 */
#define SET_BIT(REG,BIT_NUM)					(REG|=(1<<BIT_NUM))


/*Clear a certain bit to 0 */
#define CLEAR_BIT(REG,BIT_NUM)					(REG&=~(1<<BIT_NUM))


/*Change a value of certain bit from 0 to 1  or from 1 to 0 */
#define TOGGLE_BIT(REG,BIT_NUM)					(REG^=(1<<BIT_NUM))


/*Check the value of a certain bit is equal to 1 */
#define BIT_IS_SET(REG,BIT_NUM)					((1<<BIT_NUM)&(REG))

/*Check the value of a certain bit is equal to 0 */
#define BIT_IS_CLEAR(REG,BIT_NUM)				(!((1<<BIT_NUM)&(REG)))

/*Rotate Right the value in a Register*/
#define ROR(REG,BIT_NUM)						(REG=((REG>>BIT_NUM)|(REG<<(8-BIT_NUM))))

/*Rotate Left the value in a Register*/
#define ROL(REG,BIT_NUM)						(REG=((REG<<BIT_NUM)|(REG>>(8-BIT_NUM))))


/* Get that bit and shift it to be the first bit in the register to have a decimal value either 0 or 1 */
#define GET_BIT(REG,BIT_NUM) 					((REG & (1<<BIT_NUM))>> BIT_NUM)


#define CHANGE_ENDIANNESS(A)   ((((uint32)(A) & 0xff000000) >> 24)  \
                               | (((uint32)(A) & 0x00ff0000) >> 8)  \
                               | (((uint32)(A) & 0x0000ff00) << 8)  \
                               | (((uint32)(A) & 0x000000ff) << 24))

#define FLOOR(NUM)				((uint32)(NUM))

#endif /* COMMON_MACROS_H_ */
