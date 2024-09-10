/* 
 * File:   ecu_init.c
 * Author: omar fathy
 *
 * Created on 24 June 2024, 00:08
 */

#include "ecu_init.h"

lcd_4bit_t lcd = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
};

button_t btn1 = {
    .button_pin.port = PORTB_INDEX,
    .button_pin.pin  = GPIO_PIN0,
    .button_pin.direction = GPIO_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn2 = {
    .button_pin.port = PORTB_INDEX,
    .button_pin.pin  = GPIO_PIN1,
    .button_pin.direction = GPIO_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn3 = {
    .button_pin.port = PORTB_INDEX,
    .button_pin.pin  = GPIO_PIN2,
    .button_pin.direction = GPIO_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn4 = {
    .button_pin.port = PORTB_INDEX,
    .button_pin.pin  = GPIO_PIN4,
    .button_pin.direction = GPIO_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn5 = {
    .button_pin.port = PORTB_INDEX,
    .button_pin.pin  = GPIO_PIN5,
    .button_pin.direction = GPIO_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn6 = {
    .button_pin.port = PORTB_INDEX,
    .button_pin.pin  = GPIO_PIN6,
    .button_pin.direction = GPIO_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

void ecu_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_initialize(&lcd);
    ret &= button_initialize(&btn1);
    ret &= button_initialize(&btn2);
    ret &= button_initialize(&btn3);
    ret &= button_initialize(&btn4);
    ret &= button_initialize(&btn5);
    ret &= button_initialize(&btn6);
}