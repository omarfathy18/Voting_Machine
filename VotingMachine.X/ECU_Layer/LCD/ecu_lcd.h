/* 
 * File:   ecu_lcd.h
 * Author: omar fathy
 *
 * Created on 25 June 2024, 16:15
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/* INCLUDES */
#include "ecu_lcd_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* MACRO DECLARATIONS */
#define LCD_CLEAR                      0x01
#define LCD_RETURN_HOME                0x02
#define LCD_ENTRY_MODE                 0x06
#define LCD_CURSOR_OFF_DISPLAY_ON      0x0C
#define LCD_CURSOR_OFF_DISPLAY_OFF     0x08
#define LCD_CURSOR_ON_BLINK_ON         0x0F
#define LCD_CURSOR_ON_BLINK_OFF        0x0E
#define LCD_DISPLAY_SHIFT_RIGHT        0x1C
#define LCD_DISPLAY_SHIFT_LEFT         0x18  
#define LCD_4BIT_MODE_2LINE            0x28
#define LCD_8BIT_MODE_2LINE            0x38
#define LCD_CGRAM_START                0x40
#define LCD_DDRAM_START                0x80

#define ROW1    1
#define ROW2    2
#define ROW3    3
#define ROW4    4

/* MACRO FUNCTIONS DECLARATIONS */


/* DATA TYPES DECLARATIONS */
typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}lcd_4bit_t;

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}lcd_8bit_t;

/* FUNCTIONS DECLARATIONS */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd, uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd, uint8 data, uint8 row, uint8 column);
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8 *str, uint8 row, uint8 column);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, uint8 chr[], uint8 row, uint8 column, uint8 mem_pos);

Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd, uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd, uint8 data, uint8 row, uint8 column);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, uint8 *str, uint8 row, uint8 column);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, uint8 chr[], uint8 row, uint8 column, uint8 mem_pos);

Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str);
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str);
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str);

#endif	/* ECU_LCD_H */

