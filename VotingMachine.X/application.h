/* 
 * File:   application.h
 * Author: omar fathy
 *
 * Created on 25 April 2024, 03:00
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* INCLUDES */
#include "ECU_Layer/ecu_init.h"
#include "MCAL_Layer/mcal_init.h"

/* MACRO DECLARATIONS */
#define NORMAL_MODE     0
#define WINNER_MODE     1

/* MACRO FUNCTIONS DECLARATIONS */


/* DATA TYPES DECLARATIONS */


/* FUNCTIONS DECLARATIONS */
void welcome_message(void);
void loading_screen(void);
void display(void);
void clear_eeprom(void);
void store_eeprom(void);
void read_eeprom(void);
void winner(void);

#endif	/* APPLICATION_H */

