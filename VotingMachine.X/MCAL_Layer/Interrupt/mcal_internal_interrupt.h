/* 
 * File:   mcal_internal_interrupt.h
 * Author: omar fathy
 *
 * Created on 29 June 2024, 20:46
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* INCLUDES */
#include "mcal_interrupt_cfg.h"

/* MACRO DECLARATIONS */


/* MACRO FUNCTIONS DECLARATIONS */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable the ADC module */
#define ADC_Interrupt_Enable()        (PIE1bits.ADIE = 1)
#define ADC_Interrupt_Disable()       (PIE1bits.ADIE = 0)
/* Clear the ADC module interrupt flag */
#define ADC_Interrupt_FlagClear()     (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set ADC module interrupt priority to be high or low */
#define ADC_SetHighPriority()         (IPR1bits.ADIP = 1)
#define ADC_SetlowPriority()          (IPR1bits.ADIP = 0)
#endif
#endif

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable the Timer0 module */
#define Timer0_Interrupt_Enable()        (INTCONbits.TMR0IE = 1)
#define Timer0_Interrupt_Disable()       (INTCONbits.TMR0IE = 0)
/* Clear the Timer0 module interrupt flag */
#define Timer0_Interrupt_FlagClear()     (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set Timer0 module interrupt priority to be high or low */
#define Timer0_SetHighPriority()         (INTCON2bits.TMR0IP = 1)
#define Timer0_SetlowPriority()          (INTCON2bits.TMR0IP = 0)
#endif
#endif

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable the Timer1 module */
#define Timer1_Interrupt_Enable()        (PIE1bits.TMR1IE = 1)
#define Timer1_Interrupt_Disable()       (PIE1bits.TMR1IE = 0)
/* Clear the Timer1 module interrupt flag */
#define Timer1_Interrupt_FlagClear()     (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set Timer1 module interrupt priority to be high or low */
#define Timer1_SetHighPriority()         (IPR1bits.TMR1IP = 1)
#define Timer1_SetlowPriority()          (IPR1bits.TMR1IP = 0)
#endif
#endif

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable the Timer2 module */
#define Timer2_Interrupt_Enable()        (PIE1bits.TMR2IE = 1)
#define Timer2_Interrupt_Disable()       (PIE1bits.TMR2IE = 0)
/* Clear the Timer2 module interrupt flag */
#define Timer2_Interrupt_FlagClear()     (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set Timer2 module interrupt priority to be high or low */
#define Timer2_SetHighPriority()         (IPR1bits.TMR2IP = 1)
#define Timer2_SetlowPriority()          (IPR1bits.TMR2IP = 0)
#endif
#endif

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable the Timer3 module */
#define Timer3_Interrupt_Enable()        (PIE2bits.TMR3IE = 1)
#define Timer3_Interrupt_Disable()       (PIE2bits.TMR3IE = 0)
/* Clear the Timer3 module interrupt flag */
#define Timer3_Interrupt_FlagClear()     (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set Timer3 module interrupt priority to be high or low */
#define Timer3_SetHighPriority()         (IPR2bits.TMR3IP = 1)
#define Timer3_SetlowPriority()          (IPR2bits.TMR3IP = 0)
#endif
#endif

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable the CCP1 module */
#define CCP1_Interrupt_Enable()        (PIE1bits.CCP1IE = 1)
#define CCP1_Interrupt_Disable()       (PIE1bits.CCP1IE = 0)
/* Clear the CCP1 module interrupt flag */
#define CCP1_Interrupt_FlagClear()     (PIR1bits.CCP1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set CCP1 module interrupt priority to be high or low */
#define CCP1_SetHighPriority()         (IPR1bits.CCP1IP = 1)
#define CCP1_SetlowPriority()          (IPR1bits.CCP1IP = 0)
#endif
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable the CCP2 module */
#define CCP2_Interrupt_Enable()        (PIE2bits.CCP2IE = 1)
#define CCP2_Interrupt_Disable()       (PIE2bits.CCP2IE = 0)
/* Clear the CCP2 module interrupt flag */
#define CCP2_Interrupt_FlagClear()     (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set CCP2 module interrupt priority to be high or low */
#define CCP2_SetHighPriority()         (IPR2bits.CCP2IP = 1)
#define CCP2_SetlowPriority()          (IPR2bits.CCP2IP = 0)
#endif
#endif

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable the EUSART Tx interrupt */
#define EUSART_Tx_Interrupt_Enable()        (PIE1bits.TXIE = 1)
#define EUSART_Tx_Interrupt_Disable()       (PIE1bits.TXIE = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set EUSART Tx interrupt priority to be high or low */
#define EUSART_Tx_SetHighPriority()         (IPR1bits.TXIP = 1)
#define EUSART_Tx_SetlowPriority()          (IPR1bits.TXIP = 0)
#endif
#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable the EUSART Rx interrupt */
#define EUSART_Rx_Interrupt_Enable()        (PIE1bits.RCIE = 1)
#define EUSART_Rx_Interrupt_Disable()       (PIE1bits.RCIE = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set EUSART Rx interrupt priority to be high or low */
#define EUSART_Rx_SetHighPriority()         (IPR1bits.RCIP = 1)
#define EUSART_Rx_SetlowPriority()          (IPR1bits.RCIP = 0)
#endif
#endif

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable the MSSP I2C interrupt */
#define MSSP_I2C_Interrupt_Enable()             (PIE1bits.SSPIE = 1)
#define MSSP_I2C_BUS_COL_Interrupt_Enable()     (PIE2bits.BCLIE = 1)
#define MSSP_I2C_Interrupt_Disable()            (PIE1bits.SSPIE = 0)
#define MSSP_I2C_BUS_COL_Interrupt_Disable()    (PIE2bits.BCLIE = 0)
/* Clear the MSSP I2C module interrupt flag */
#define MSSP_I2C_Interrupt_FlagClear()          (PIR1bits.SSPIF = 0)
#define MSSP_I2C_BUS_COL_Interrupt_FlagClear()  (PIR2bits.BCLIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set MSSP I2C interrupt priority to be high or low */
#define MSSP_I2C_SetHighPriority()         (IPR1bits.SSPIP = 1)
#define MSSP_I2C_BUS_COL_SetHighPriority() (IPR2bits.BCLIP = 1)
#define MSSP_I2C_SetlowPriority()          (IPR1bits.SSPIP = 0)
#define MSSP_I2C_BUS_COL_SetlowPriority()  (IPR2bits.BCLIP = 0)
#endif
#endif

/* DATA TYPES DECLARATIONS */


/* FUNCTIONS DECLARATIONS */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

