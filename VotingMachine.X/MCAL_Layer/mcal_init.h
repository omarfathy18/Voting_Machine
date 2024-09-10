/* 
 * File:   mcal_init.h
 * Author: omar fathy
 *
 * Created on 21 August 2024, 16:45
 */

#ifndef MCAL_INIT_H
#define	MCAL_INIT_H

/* INCLUDES */
#include "Interrupt/mcal_external_interrupt.h"
#include "EEPROM/hal_eeprom.h"

/* MACRO DECLARATIONS */


/* MACRO FUNCTIONS DECLARATIONS */


/* DATA TYPES DECLARATIONS */


/* OBJECTS DECLARATIONS */
interrupt_INTx_t int0_obj;
interrupt_INTx_t int1_obj;
interrupt_INTx_t int2_obj;
interrupt_RBx_t rb4_obj;
interrupt_RBx_t rb5_obj;
interrupt_RBx_t rb6_obj;

/* FUNCTIONS DECLARATIONS */
void INT0_APP_ISR(void);
void INT1_APP_ISR(void);
void INT2_APP_ISR(void);
void RB4_HIGH_APP_ISR();
void RB5_LOW_APP_ISR();
void RB6_HIGH_APP_ISR();
void mcal_initialize(void);

#endif	/* MCAL_INIT_H */

