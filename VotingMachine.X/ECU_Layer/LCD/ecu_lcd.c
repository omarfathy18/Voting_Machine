/* 
 * File:   ecu_lcd.c
 * Author: omar fathy
 *
 * Created on 25 June 2024, 16:15
 */

#include "ecu_lcd.h"

static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd, uint8 data);
static Std_ReturnType lcd_4bit_enable_signal(const lcd_4bit_t *lcd);
static Std_ReturnType lcd_8bit_enable_signal(const lcd_8bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8 row, uint8 column);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 column);

/**
 * @brief Initialize the assigned pins
 * @param lcd (pointer to the LCD module configuration)
 * @return Status of the function
 */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        uint8 data_pins_counter = ZERO_INIT;
        for(data_pins_counter = ZERO_INIT; data_pins_counter < 4; data_pins_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        ret = lcd_4bit_send_command(lcd, LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd, LCD_CGRAM_START);
        ret = lcd_4bit_send_command(lcd, LCD_DDRAM_START);
        ret = lcd_4bit_send_command(lcd, LCD_4BIT_MODE_2LINE);
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a command to the LCD to do
 * @param lcd (pointer to the LCD module configuration)
 * @param command (command number to do)
 * @return Status of the function
 */
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_send_4bits(lcd, (command >> 4));
        ret = lcd_4bit_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, command);
        ret = lcd_4bit_enable_signal(lcd);
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a character data to the LCD to display
 * @param lcd (pointer to the LCD module configuration)
 * @param data (data to be displayed)
 * @return Status of the function
 */
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bits(lcd, (data >> 4));
        ret = lcd_4bit_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, data);
        ret = lcd_4bit_enable_signal(lcd);
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a character data to the LCD to display in a specific position
 * @param lcd (pointer to the LCD module configuration)
 * @param data (data of the character to be displayed)
 * @param row (the row to display the character on)
 * @param column (the column to display the character on)
 * @return Status of the function
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd, uint8 data, uint8 row, uint8 column){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a string data to the LCD to display
 * @param lcd (pointer to the LCD module configuration)
 * @param str (pointer to the string to be displayed)
 * @return Status of the function
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    
    if ((lcd == NULL) || (str == NULL)){
        ret = E_NOT_OK;
    }
    else{
        while(*str){
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a string data to the LCD to display in a specific position
 * @param lcd (pointer to the LCD module configuration)
 * @param str (pointer to the string to be displayed)
 * @param row (the start row to display the string on)
 * @param column (the start column to display the string on)
 * @return Status of the function
 */
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8 *str, uint8 row, uint8 column){
    Std_ReturnType ret = E_NOT_OK;
    
    if ((lcd == NULL) || (str == NULL)){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        while(*str){
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a custom character data to the LCD to display in a specific position
 * @param lcd (pointer to the LCD module configuration)
 * @param chr (array describing the custom character to be displayed)
 * @param row (the row to display the character on)
 * @param column (the column to display the character on)
 * @param mem_pos (memory position of the custom character)
 * @return Status of the function
 */
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, uint8 chr[], uint8 row, uint8 column, uint8 mem_pos){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        uint8 counter = ZERO_INIT;
        ret = lcd_4bit_send_command(lcd, (LCD_CGRAM_START + (mem_pos * 8)));
        for(counter = ZERO_INIT; counter < 8; counter++){
            ret = lcd_4bit_send_char_data(lcd, chr[counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, mem_pos, row, column);
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Initialize the assigned pins
 * @param lcd (pointer to the LCD module configuration)
 * @return Status of the function
 */
Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        uint8 data_pins_counter = ZERO_INIT;
        for(data_pins_counter = ZERO_INIT; data_pins_counter < 8; data_pins_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        ret = lcd_8bit_send_command(lcd, LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd, LCD_CGRAM_START);
        ret = lcd_8bit_send_command(lcd, LCD_DDRAM_START);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a command to the LCD to do
 * @param lcd (pointer to the LCD module configuration)
 * @param command (command number to do)
 * @return Status of the function
 */
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        uint8 bit_counter = ZERO_INIT;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        
        for(bit_counter = ZERO_INIT; bit_counter < 8; bit_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[bit_counter]), (command >> bit_counter) & (uint8)0x01);
        }
        ret = lcd_8bit_enable_signal(lcd);
        
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a character data to the LCD to display
 * @param lcd (pointer to the LCD module configuration)
 * @param data (data to be displayed)
 * @return Status of the function
 */
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        uint8 bit_counter = ZERO_INIT;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        
        for(bit_counter = ZERO_INIT; bit_counter < 8; bit_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[bit_counter]), (data >> bit_counter) & (uint8)0x01);
        }
        ret = lcd_8bit_enable_signal(lcd);
        
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a character data to the LCD to display in a specific position
 * @param lcd (pointer to the LCD module configuration)
 * @param data (data of the character to be displayed)
 * @param row (the row to display the character on)
 * @param column (the column to display the character on)
 * @return Status of the function
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd, uint8 data, uint8 row, uint8 column){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char_data(lcd, data);
        
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a string data to the LCD to display
 * @param lcd (pointer to the LCD module configuration)
 * @param str (pointer to the string to be displayed)
 * @return Status of the function
 */
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    
    if ((lcd == NULL) || (str == NULL)){
        ret = E_NOT_OK;
    }
    else{
        while(*str){
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a string data to the LCD to display in a specific position
 * @param lcd (pointer to the LCD module configuration)
 * @param str (pointer to the string to be displayed)
 * @param row (the start row to display the string on)
 * @param column (the start column to display the string on)
 * @return Status of the function
 */
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, uint8 *str, uint8 row, uint8 column){
    Std_ReturnType ret = E_NOT_OK;
    
    if ((lcd == NULL) || (str == NULL)){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_string(lcd, str);
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Send a custom character data to the LCD to display in a specific position
 * @param lcd (pointer to the LCD module configuration)
 * @param chr (array describing the custom character to be displayed)
 * @param row (the row to display the character on)
 * @param column (the column to display the character on)
 * @param mem_pos (memory position of the custom character)
 * @return Status of the function
 */
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, uint8 chr[], uint8 row, uint8 column, uint8 mem_pos){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        uint8 counter = ZERO_INIT;
        ret = lcd_8bit_send_command(lcd, (LCD_CGRAM_START + (mem_pos * 8)));
        for(counter = ZERO_INIT; counter < 8; counter++){
            ret = lcd_8bit_send_char_data(lcd, chr[counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, mem_pos, row, column);
        
        ret = E_OK;
    }

    return ret;
}

static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (data >> 0) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (data >> 1) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (data >> 2) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (data >> 3) & (uint8)0x01);
        ret = E_OK;
    }

    return ret;
}

static Std_ReturnType lcd_4bit_enable_signal(const lcd_4bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
        ret = E_OK;
    }

    return ret;
}

static Std_ReturnType lcd_8bit_enable_signal(const lcd_8bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
        ret = E_OK;
    }

    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        column--;
        switch(row){
            case ROW1: ret = lcd_4bit_send_command(lcd, (LCD_DDRAM_START + column)); break;
            case ROW2: ret = lcd_4bit_send_command(lcd, (0xC0 + column)); break;
            case ROW3: ret = lcd_4bit_send_command(lcd, (0x94 + column)); break;
            case ROW4: ret = lcd_4bit_send_command(lcd, (0xD4 + column)); break;
            default: ;
        }
        ret = E_OK;
    }

    return ret;
}

static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_NOT_OK;
    
    if (lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        column--;
        switch(row){
            case ROW1: ret = lcd_8bit_send_command(lcd, (LCD_DDRAM_START + column)); break;
            case ROW2: ret = lcd_8bit_send_command(lcd, (0xC0 + column)); break;
            case ROW3: ret = lcd_8bit_send_command(lcd, (0x94 + column)); break;
            case ROW4: ret = lcd_8bit_send_command(lcd, (0xD4 + column)); break;
            default: ;
        }
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Convert the byte to a string
 * @param value (the value to be converted)
 * @param str (pointer to store the converted string)
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    
    if (str == NULL){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', 4);
        sprintf((char *)str, "%i", value);
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Convert the short to a string
 * @param value (the value to be converted)
 * @param str (pointer to store the converted string)
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    
    if (str == NULL){
        ret = E_NOT_OK;
    }
    else{
        uint8 temp_str[6] = {0};
        uint8 data_counter = ZERO_INIT;
        
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)temp_str, "%i", value);
        while(temp_str[data_counter] != '\0'){
            str[data_counter] = temp_str[data_counter];
            data_counter++;
        }
        ret = E_OK;
    }

    return ret;
}

/**
 * @brief Convert the integer to a string
 * @param value (the value to be converted)
 * @param str (pointer to store the converted string)
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    
    if (str == NULL){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', 11);
        sprintf((char *)str, "%i", value);
        ret = E_OK;
    }

    return ret;
}

