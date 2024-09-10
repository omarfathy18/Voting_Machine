/* 
 * File:   mcal_interrupt_cfg.h
 * Author: omar fathy
 *
 * Created on 29 June 2024, 20:47
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H

/* INCLUDES */
#include <xc.h>
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"

/* MACRO DECLARATIONS */
#define INTERRUPT_ENABLE           1
#define INTERRUPT_DISABLE          0
#define INTERRUPT_OCCUR            1
#define INTERRUPT_NOT_OCCUR        0
#define INTERRUPT_PRIORITY_ENABLE  1
#define INTERRUPT_PRIORITY_DISABLE 0

/* MACRO FUNCTIONS DECLARATIONS */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable priority levels in interrupts */
#define INTERRUPT_PriorityLevelsEnable()       (RCONbits.IPEN = 1)
#define INTERRUPT_PriorityLevelsDisable()      (RCONbits.IPEN = 0)
/* Enable and disable high priority global interrupts */
#define INTERRUPT_GlobalInterruptEnableHigh()  (INTCONbits.GIEH = 1)
#define INTERRUPT_GlobalInterruptDisableHigh() (INTCONbits.GIEH = 0)
/* Enable and disable low priority global interrupts */
#define INTERRUPT_GlobalInterruptEnableLow()   (INTCONbits.GIEL = 1)
#define INTERRUPT_GlobalInterruptDisableLow()  (INTCONbits.GIEL = 0)
#else
/* Enable and disable global interrupts */
#define INTERRUPT_GlobalInterruptEnable()      (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalInterruptDisable()     (INTCONbits.GIE = 0)
/* Enable and disable peripheral interrupts */
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)
#endif

/* DATA TYPES DECLARATIONS */
typedef enum{
    INTERRUPT_PRIORITY_LOW,
    INTERRUPT_PRIORITY_HIGH
}interrupt_priority_t;

/* FUNCTIONS DECLARATIONS */


#endif	/* MCAL_INTERRUPT_CFG_H */

