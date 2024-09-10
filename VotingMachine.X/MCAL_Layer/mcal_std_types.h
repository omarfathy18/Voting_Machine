/* 
 * File:   mcal_std_types.h
 * Author: omar fathy
 *
 * Created on 25 April 2024, 02:56
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* INCLUDES */
#include "std_libraries.h"
#include "compiler.h"

/* MACRO DECLARATIONS */
#define STD_HIGH       0x01
#define STD_LOW        0x00

#define CONFIG_ENABLE  0X01
#define CONFIG_DISABLE 0X00

#define STD_ON         0x01
#define STD_OFF        0x00

#define STD_ACTIVE     0x01
#define STD_IDLE       0x00

#define E_OK           (Std_ReturnType)0x01
#define E_NOT_OK       (Std_ReturnType)0x00

#define ZERO_INIT      0

#define CPU_TYPE_8     8
#define CPU_TYPE_16    16
#define CPU_TYPE_32    32
#define CPU_TYPE_64    64
/****************************/
#define CPU_TYPE (CPU_TYPE_64)
/****************************/

/* MACRO FUNCTIONS DECLARATIONS */


/* DATA TYPES DECLARATIONS */
#if (CPU_TYPE == CPU_TYPE_64)
typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef signed long long sint64;
typedef float float32;
typedef double float64;

#elif (CPU_TYPE == CPU_TYPE_32)
typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef signed long long sint64;
typedef float float32;
typedef double float64;

#elif (CPU_TYPE == CPU_TYPE_16)
typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef signed long long sint64;
typedef float float32;
typedef double float64;

#elif (CPU_TYPE == CPU_TYPE_8)
typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef float float32;

#endif

typedef uint8 Std_ReturnType;

/* FUNCTIONS DECLARATIONS */


#endif	/* MCAL_STD_TYPES_H */

