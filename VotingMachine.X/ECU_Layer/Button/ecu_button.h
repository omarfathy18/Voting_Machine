/* 
 * File:   ecu_button.h
 * Author: omar fathy
 *
 * Created on 15 June 2024, 20:51
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* INCLUDES */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"

/* MACRO DECLARATIONS */


/* MACRO FUNCTIONS DECLARATIONS */


/* DATA TYPES DECLARATIONS */
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;

/* FUNCTIONS DECLARATIONS */

/**
 * @brief Initialize the assigned pin to be INPUT
 * @param btn (Pointer to the button configuration)
 * @retur Status of the function
 */
Std_ReturnType button_initialize(const button_t *btn);

/**
 * @brief Read the button state
 * @param btn (Pointer to the button configuration)
 * @param btn_state (Pointer to store the button state)
 * @return Status of the function
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

