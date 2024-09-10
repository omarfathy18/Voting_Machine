/* 
 * File:   mcal_external_interrupt.h
 * Author: omar fathy
 *
 * Created on 29 June 2024, 20:46
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* INCLUDES */
#include "mcal_interrupt_cfg.h"

/* MACRO DECLARATIONS */


/* MACRO FUNCTIONS DECLARATIONS */
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable INT0 */
#define EXT_INT0_Interrupt_Enable()        (INTCONbits.INT0IE = 1)
#define EXT_INT0_Interrupt_Disable()       (INTCONbits.INT0IE = 0)
/* Clear INT0 flag */
#define EXT_INT0_Interrupt_FlagClear()     (INTCONbits.INT0IF = 0)
/* Set INT0 edge detect (rising edge / falling edge) */
#define EXT_INT0_RisingEdge()              (INTCON2bits.INTEDG0 = 1)
#define EXT_INT0_FallingEdge()             (INTCON2bits.INTEDG0 = 0)

/* Enable and disable INT1 */
#define EXT_INT1_Interrupt_Enable()        (INTCON3bits.INT1IE = 1)
#define EXT_INT1_Interrupt_Disable()       (INTCON3bits.INT1IE = 0)
/* Clear INT1 flag */
#define EXT_INT1_Interrupt_FlagClear()     (INTCON3bits.INT1IF = 0)
/* Set INT1 edge detect (rising edge / falling edge) */
#define EXT_INT1_RisingEdge()              (INTCON2bits.INTEDG1 = 1)
#define EXT_INT1_FallingEdge()             (INTCON2bits.INTEDG1 = 0)

/* Enable and disable INT2 */
#define EXT_INT2_Interrupt_Enable()        (INTCON3bits.INT2IE = 1)
#define EXT_INT2_Interrupt_Disable()       (INTCON3bits.INT2IE = 0)
/* Clear INT2 flag */
#define EXT_INT2_Interrupt_FlagClear()     (INTCON3bits.INT2IF = 0)
/* Set INT2 edge detect (rising edge / falling edge) */
#define EXT_INT2_RisingEdge()              (INTCON2bits.INTEDG2 = 1)
#define EXT_INT2_FallingEdge()             (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set INT1 to be high or low priority */
#define EXT_INT1_SetHighPriority()        (INTCON3bits.INT1IF = 1)
#define EXT_INT1_SetlowPriority()         (INTCON3bits.INT1IF = 0)
/* Set INT2 to be high or low priority */
#define EXT_INT2_SetHighPriority()        (INTCON3bits.INT2IF = 1)
#define EXT_INT2_SetlowPriority()         (INTCON3bits.INT2IF = 0)
#endif
#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Enable and disable RBx */
#define EXT_RBx_Interrupt_Enable()        (INTCONbits.RBIE = 1)
#define EXT_RBx_Interrupt_Disable()       (INTCONbits.RBIE = 0)
/* Clear RBx flag */
#define EXT_RBx_Interrupt_FlagClear()     (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Set RBx to be high or low priority */
#define EXT_RBx_SetHighPriority()        (INTCON2bits.RBIP = 1)
#define EXT_RBx_SetlowPriority()         (INTCON2bits.RBIP = 0)
#endif
#endif

/* DATA TYPES DECLARATIONS */
typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edge_t;

typedef enum{
    INTERRUPT_INT0 = 0,
    INTERRUPT_INT1,
    INTERRUPT_INT2
}interrupt_INTx_src_t;

typedef struct{
    void (* InterruptHandler)(void);
    pin_config_t int_pin;
    interrupt_INTx_edge_t edge;
    interrupt_INTx_src_t source;
    interrupt_priority_t priority;
}interrupt_INTx_t;

typedef struct{
    void (* InterruptHandler_HIGH)(void);
    void (* InterruptHandler_LOW)(void);
    pin_config_t int_pin;
    interrupt_priority_t priority;
}interrupt_RBx_t;

/* FUNCTIONS DECLARATIONS */
Std_ReturnType interrupt_INTx_initialize(const interrupt_INTx_t *int_obj);
Std_ReturnType interrupt_INTx_deinitialize(const interrupt_INTx_t *int_obj);
Std_ReturnType interrupt_RBx_initialize(const interrupt_RBx_t *int_obj);
Std_ReturnType interrupt_RBx_deinitialize(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

