/* 
 * File:   ecu_init.h
 * Author: omar fathy
 *
 * Created on 24 June 2024, 00:08
 */

#ifndef ECU_INIT_H
#define	ECU_INIT_H

/* INCLUDES */
#include "Button/ecu_button.h"
#include "LCD/ecu_lcd.h"

/* MACRO DECLARATIONS */


/* MACRO FUNCTIONS DECLARATIONS */


/* DATA TYPES DECLARATIONS */


/* OBJECTS DECLARATIONS */
lcd_4bit_t lcd;
button_t btn1;
button_t btn2;
button_t btn3;
button_t btn4;
button_t btn5;
button_t btn6;

/* FUNCTIONS DECLARATIONS */
void ecu_initialize(void);

#endif	/* ECU_INIT_H */

