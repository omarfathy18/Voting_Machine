/* 
 * File:   mcal_init.c
 * Author: omar fathy
 *
 * Created on 21 August 2024, 16:45
 */

#include "mcal_init.h"

interrupt_INTx_t int0_obj = {
    .InterruptHandler = INT0_APP_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .source = INTERRUPT_INT0,
    .int_pin.port = PORTB_INDEX,
    .int_pin.pin = GPIO_PIN0,
    .int_pin.direction = GPIO_INPUT
};

interrupt_INTx_t int1_obj = {
    .InterruptHandler = INT1_APP_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .source = INTERRUPT_INT1,
    .int_pin.port = PORTB_INDEX,
    .int_pin.pin = GPIO_PIN1,
    .int_pin.direction = GPIO_INPUT
};

interrupt_INTx_t int2_obj = {
    .InterruptHandler = INT2_APP_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .source = INTERRUPT_INT2,
    .int_pin.port = PORTB_INDEX,
    .int_pin.pin = GPIO_PIN2,
    .int_pin.direction = GPIO_INPUT
};

interrupt_RBx_t rb4_obj = {
    .InterruptHandler_HIGH = RB4_HIGH_APP_ISR,
    .InterruptHandler_LOW = NULL,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .int_pin.port = PORTB_INDEX,
    .int_pin.pin = GPIO_PIN4,
    .int_pin.direction = GPIO_INPUT
};

interrupt_RBx_t rb5_obj = {
    .InterruptHandler_HIGH = NULL,
    .InterruptHandler_LOW = RB5_LOW_APP_ISR,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .int_pin.port = PORTB_INDEX,
    .int_pin.pin = GPIO_PIN5,
    .int_pin.direction = GPIO_INPUT
};

interrupt_RBx_t rb6_obj = {
    .InterruptHandler_HIGH = RB6_HIGH_APP_ISR,
    .InterruptHandler_LOW = NULL,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .int_pin.port = PORTB_INDEX,
    .int_pin.pin = GPIO_PIN6,
    .int_pin.direction = GPIO_INPUT
};

void mcal_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = interrupt_INTx_initialize(&int0_obj);
    ret &= interrupt_INTx_initialize(&int1_obj);
    ret &= interrupt_INTx_initialize(&int2_obj);
    ret &= interrupt_RBx_initialize(&rb4_obj);
    ret &= interrupt_RBx_initialize(&rb5_obj);
    ret &= interrupt_RBx_initialize(&rb6_obj);
}