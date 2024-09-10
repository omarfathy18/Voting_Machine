/* 
 * File:   mcal_interrupt_manager.h
 * Author: omar fathy
 *
 * Created on 29 June 2024, 20:47
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_flag = 1, RB5_flag = 1, RB6_flag = 1, RB7_flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptManagerHigh(void){
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR)){
        INT0_ISR();
    }
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR)){
        INT2_ISR();
    }
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR)){
         INT1_ISR();
    }
}
#else
void __interrupt() InterruptManager(void){
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR)){
        INT0_ISR();
    }
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR)){
         INT1_ISR();
    }
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR)){
        INT2_ISR();
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
        && (PORTBbits.RB4 == GPIO_HIGH) && (RB4_flag == 1)){
        RB4_flag = 0;
        RB4_ISR(0);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
        && (PORTBbits.RB4 == GPIO_LOW) && (RB4_flag == 0)){
        RB4_flag = 1;
        RB4_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
        && (PORTBbits.RB5 == GPIO_HIGH) && (RB5_flag == 1)){
        RB5_flag = 0;
        RB5_ISR(0);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
        && (PORTBbits.RB5 == GPIO_LOW) && (RB5_flag == 0)){
        RB5_flag = 1;
        RB5_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
        && (PORTBbits.RB6 == GPIO_HIGH) && (RB6_flag == 1)){
        RB6_flag = 0;
        RB6_ISR(0);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
        && (PORTBbits.RB6 == GPIO_LOW) && (RB6_flag == 0)){
        RB6_flag = 1;
        RB6_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
        && (PORTBbits.RB7 == GPIO_HIGH) && (RB7_flag == 1)){
        RB7_flag = 0;
        RB7_ISR(0);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
        && (PORTBbits.RB7 == GPIO_LOW) && (RB7_flag == 0)){
        RB7_flag = 1;
        RB7_ISR(1);
    }
}
#endif