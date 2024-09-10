/* 
 * File:   hal_gpio.c
 * Author: omar fathy
 *
 * Created on 25 April 2024, 02:52
 */

#include "hal_gpio.h"

volatile uint8 *tric_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE}; /* Reference to the data direction control registers */
volatile uint8 *lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE}; /* Reference to the data latch registers (read or write) */
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE}; /* Reference to the port status registers */

/**
 * @brief Initialize the direction of a specific pin
 * @param pin_config pointer to the configurations
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config){
    Std_ReturnType ret = E_NOT_OK;

    if ((pin_config == NULL) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        switch (pin_config->direction){
            case GPIO_OUTPUT:
                CLR_BIT(*(tric_registers[pin_config->port]), pin_config->pin);
                ret = E_OK;
                break;
            case GPIO_INPUT:
                SET_BIT(*(tric_registers[pin_config->port]), pin_config->pin);
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }

    return ret;
}
#endif

/**
 * 
 * @param pin_config pointer to the configurations
 * @param direction_status
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config, direction_t *direction_status){
    Std_ReturnType ret = E_NOT_OK;

    if ((pin_config == NULL) || (direction_status == NULL) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        *direction_status = READ_BIT(*(tric_registers[pin_config->port]), pin_config->pin);
        ret = E_OK;
    }

    return ret;
}
#endif

/**
 * 
 * @param pin_config pointer to the configurations
 * @param logic
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic){
    Std_ReturnType ret = E_NOT_OK;

    if ((pin_config == NULL) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        switch (logic){
            case GPIO_LOW:
                CLR_BIT(*(lat_registers[pin_config->port]), pin_config->pin);
                ret = E_OK;
                break;
            case GPIO_HIGH:
                SET_BIT(*(lat_registers[pin_config->port]), pin_config->pin);
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }

    return ret;
}
#endif

/**
 * 
 * @param pin_config pointer to the configurations
 * @param logic
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t *logic){
    Std_ReturnType ret = E_NOT_OK;

    if ((pin_config == NULL) || (logic == NULL) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*(port_registers[pin_config->port]), pin_config->pin);
        ret = E_OK;
    }

    return ret;
}
#endif

/**
 * 
 * @param pin_config pointer to the configurations
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config){
    Std_ReturnType ret = E_NOT_OK;

    if ((pin_config == NULL) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*(lat_registers[pin_config->port]), pin_config->pin);
        ret = E_OK;
    }

    return ret;
}
#endif

/**
 * 
 * @param pin_config pointer to the configurations
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config){
    Std_ReturnType ret = E_NOT_OK;

    if ((pin_config == NULL) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(pin_config);
        ret = gpio_pin_write_logic(pin_config, pin_config->logic);
        ret = E_OK;
    }

    return ret;
}
#endif

/**
 * 
 * @param port_index
 * @param direction
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_initialize(port_index_t port_index, uint8 direction){
    Std_ReturnType ret = E_NOT_OK;

    if (port_index > PORT_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }
    else{
        *(tric_registers[port_index]) = direction;
        ret = E_OK;
    }

    return ret;
}
#endif

/**
 * 
 * @param port_index
 * @param direction_status
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_initialize(port_index_t port_index, uint8 *direction_status){
    Std_ReturnType ret = E_NOT_OK;

    if ((direction_status == NULL) || (port_index > PORT_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        *direction_status = *(tric_registers[port_index]);
        ret = E_OK;
    }

    return ret;
}
#endif

/**
 * 
 * @param port_index
 * @param logic
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port_index, uint8 logic){
    Std_ReturnType ret = E_NOT_OK;

    if (port_index > PORT_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }
    else{
        *(lat_registers[port_index]) = logic;
        ret = E_OK;
    }

    return ret;
}
#endif

/**
 * 
 * @param port_index
 * @param logic
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action 
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port_index, uint8 *logic){
    Std_ReturnType ret = E_NOT_OK;

    if ((logic == NULL) || (port_index > PORT_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        *logic = *(lat_registers[port_index]);
        ret = E_OK;
    }

    return ret;
}
#endif

/**
 * 
 * @param port_index
 * @return Status of the function
 *         (E_OK): the function run successfully
 *         (E_NOT_OK): the function has issue in performing this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port_index){
    Std_ReturnType ret = E_NOT_OK;

    if (port_index > PORT_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }
    else{
        *(lat_registers[port_index]) ^= PORTC_MASK;
        ret = E_OK;
    }

    return ret;
}
#endif