/* 
 * File:   ecu_button.h
 * Author: omar fathy
 *
 * Created on 15 June 2024, 20:51
 */

#include "ecu_button.h"

/**
 * @brief Initialize the assigned pin to be INPUT
 * @param btn (Pointer to the button configuration)
 * @return Status of the function
 */
Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType ret = E_NOT_OK;
    
    if (btn == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(&(btn->button_pin));
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Read the button state
 * @param btn (Pointer to the button configuration)
 * @param btn_state (Pointer to store the button state)
 * @return Status of the function
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    Std_ReturnType ret = E_NOT_OK;
    logic_t pin_logic = GPIO_LOW;
    
    if ((btn == NULL) || (btn_state == NULL)){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_read_logic(&(btn->button_pin), &pin_logic);
        if(btn->button_connection == BUTTON_ACTIVE_HIGH){
            if(pin_logic == GPIO_HIGH){
                *btn_state = BUTTON_PRESSED;
            }
            else if(pin_logic == GPIO_LOW){
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(btn->button_connection == BUTTON_ACTIVE_LOW){
            if(pin_logic == GPIO_HIGH){
                *btn_state = BUTTON_RELEASED;
            }
            else if(pin_logic == GPIO_LOW){
                *btn_state = BUTTON_PRESSED;
            }
        }
        ret = E_OK;
    }

    return ret;
}
 