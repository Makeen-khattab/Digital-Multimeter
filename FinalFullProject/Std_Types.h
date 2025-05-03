/*****************************************************
 * File: Std_Types
 * Author: Makeen Khattab
 * Date: January 1, 2024
 * Description: Contains all standard declaration
 *
 ****************************************************/
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Boolean Expression*/
#ifndef FALSE
#define FALSE		0u
#endif

#ifndef TRUE
#define TRUE		1u
#endif

#ifndef LOGIC_HIGH
#define LOGIC_HIGH		1u
#endif

#ifndef LOGIC_LOW
#define LOGIC_LOW		0u
#endif


#ifndef NULL
#define NULL		((void*)0)
#endif

typedef unsigned char		  uint8 ; 		  /*   0 to 255*/
typedef signed   char		  sint8 ;		  /* -128 to 127*/
typedef unsigned short		  uint16 ; 		  /*   0 to 65535*/
typedef signed   short		  sint16 ;		  /* -32768 to 32767*/
typedef unsigned long		  uint32 ; 		  /*   0 to 4294967296*/
typedef signed   long		  sint32 ;		  /* -2147483648 to 2147483647*/
typedef unsigned long long	  uint64 ; 		  /*   0 to 18446744073709551615*/
typedef signed   long long	  sint64 ;		  /* -9223372036854775808 .. 9223372036854775807*/
typedef float		  		  float32 ;		  /* 1 sign bit, 8 exponent bits,23 mantissa */
typedef double		  		  float64 ;		  /* 1 sign bit, 11 exponent bits,52 mantissa */


#endif
