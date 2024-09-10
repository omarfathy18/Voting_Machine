/* 
 * File:   hal_gpio.h
 * Author: omar fathy
 *
 * Created on 25 April 2024, 02:55
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* INCLUDES */
//#include "../proc/pic18f4620.h"
#include <xc.h>
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/* MACRO DECLARATIONS */
#define BIT_MASK             (uint8)1

#define PORT_PIN_MAX_NUMBER  8
#define PORT_MAX_NUMBER      5

#define PORTC_MASK           0xFF

/* MACRO FUNCTIONS DECLARATIONS */
#define HWREG8(_x) (*((volatile uint8 *)(_x)))

#define SET_BIT(REG, BIT_POSN)       (REG |= (BIT_MASK << BIT_POSN))
#define CLR_BIT(REG, BIT_POSN)       (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN)    (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG, BIT_POSN)      ((REG >> BIT_POSN) & BIT_MASK)

/* DATA TYPES DECLARATIONS */
typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH
} logic_t;

typedef enum {
    GPIO_OUTPUT = 0,
    GPIO_INPUT
} direction_t;

typedef enum {
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
} pin_index_t;

typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
} port_index_t;

typedef struct {
    // why not use the typedefs
    uint8 port : 3;      /* @ref port_index_t */
    uint8 pin : 3;       /* @ref pin_index_t */
    uint8 direction : 1; /* @ref direction_t */
    uint8 logic : 1;     /* @ref logic_t */
} pin_config_t;

/* FUNCTIONS DECLARATIONS */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config, direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config);

Std_ReturnType gpio_port_direction_initialize(port_index_t port_index, uint8 direction);
Std_ReturnType gpio_port_get_direction_initialize(port_index_t port_index, uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port_index, uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port_index, uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port_index);

#endif	/* HAL_GPIO_H */

