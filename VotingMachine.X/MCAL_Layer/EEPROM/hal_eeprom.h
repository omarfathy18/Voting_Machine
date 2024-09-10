/* 
 * File:   hal_eeprom.h
 * Author: omar fathy
 *
 * Created on July 3, 2024, 5:40 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* INCLUDES */
#include <xc.h>
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* MACRO DECLARATIONS */
#define ACCESS_FLASH_MEMORY          1
#define ACCESS_EEPROM_MEMORY         0

#define ACCESS_CONFIG_REFGISTERS     1
#define ACCESS_FLASH_EEPROM_MEMORY   0

#define ALLOW_WRITE_FLASH_EEPROM     1
#define INHIBIT_WRITE_FLASH_EEPROM   0

#define INITIATE_EEPROM_ERASE_WRITE  1
#define EEPROM_ERASE_WRITE_COMPLETED 0

#define INITIATE_EEPROM_READ         1

/* MACRO FUNCTIONS DECLARATIONS */


/* DATA TYPES DECLARATIONS */


/* FUNCTIONS DECLARATIONS */
Std_ReturnType Data_EEPROM_WriteByte(uint16 adr, uint8 data);
Std_ReturnType Data_EEPROM_ReadByte(uint16 adr, uint8 *data);

#endif	/* HAL_EEPROM_H */

