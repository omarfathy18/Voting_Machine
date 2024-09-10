/* 
 * File:   mcal_interrupt_manager.h
 * Author: omar fathy
 *
 * Created on 29 June 2024, 20:47
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* INCLUDES */
#include "mcal_interrupt_cfg.h"

/* MACRO DECLARATIONS */


/* MACRO FUNCTIONS DECLARATIONS */


/* DATA TYPES DECLARATIONS */


/* FUNCTIONS DECLARATIONS */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_source);
void RB5_ISR(uint8 RB5_source);
void RB6_ISR(uint8 RB6_source);
void RB7_ISR(uint8 RB7_source);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

