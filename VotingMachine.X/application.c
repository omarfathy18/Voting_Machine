/*
 * @File:     application.c
 *
 * @Author:
 * @Name:     Omar Fathy
 * @Email:    omarttt50@gmail.com
 * @LinkedIn: linkedin.com/in/omar-fathyy
 *
 * @Date_Created:  1 September 2024, 02:52
 * @Last_Modified: 10 September 2024, 18:30
 *
 * @Version:  1.0
 * 
 * @Name: Voting Machine
 * 
 * @Features: 
 *      Normal Mode: Voting for 4 candidates / Reset
 *      Winner Mode: Display winner / Reset
 *      If the power is cut out the votes are still stored in the EEPROM and can be recovered
 * 
 * @Drivers: GPIO / Interrupt / EEPROM / LCD
 * 
 * @Components: Microcontroller(PIC18f4620) / LCD(LM016L) / Push Buttons / Resistors
 */

#include "application.h"

Std_ReturnType ret = E_NOT_OK;

uint8 can_A = ZERO_INIT, can_B = ZERO_INIT, can_C = ZERO_INIT, can_D = ZERO_INIT, operation_mode = NORMAL_MODE;
uint8 can_A_str[6], can_B_str[6], can_C_str[6], can_D_str[6];

int main(){
    /* Initialize LCD pins and push buttons */
    ecu_initialize();
    /* Initialize interrupts */
    mcal_initialize();
    /* Display a welcome message */
    welcome_message();
    /* Loading */
    loading_screen();
    while(1){
        /* Winner Mode */
        if(operation_mode){
            winner();
        }
        /* Normal Mode */
        else{
            display();
        }
    }
    
    return (EXIT_SUCCESS);
}

void INT0_APP_ISR(void){
    if(operation_mode == NORMAL_MODE){
        can_A++;
        store_eeprom();
    }
}

void INT1_APP_ISR(void){
    if(operation_mode == NORMAL_MODE){
        can_B++;
        store_eeprom();
    }
}

void INT2_APP_ISR(void){
    if(operation_mode == NORMAL_MODE){
        can_C++;
        store_eeprom();
    }
}

void RB4_HIGH_APP_ISR(){
    if(operation_mode == NORMAL_MODE){
        can_D++;
        store_eeprom();
    }
}

void RB5_LOW_APP_ISR(){
    operation_mode = NORMAL_MODE;
    lcd_4bit_send_command(&lcd, LCD_CLEAR);
    can_A = ZERO_INIT;
    can_B = ZERO_INIT;
    can_C = ZERO_INIT;
    can_D = ZERO_INIT;
    clear_eeprom();
    display();
}

void RB6_HIGH_APP_ISR(){
    if(operation_mode == NORMAL_MODE){
        operation_mode = WINNER_MODE;
        lcd_4bit_send_command(&lcd, LCD_CLEAR);
        winner();
    }
}

void welcome_message(void){
    ret = lcd_4bit_send_string_pos(&lcd, (uint8 *)"Welcome", 1, 5);
    __delay_ms(500);
    ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
    __delay_ms(100);
}

void loading_screen(void){
    uint8 counter1 = ZERO_INIT, counter2 = ZERO_INIT;
    ret = lcd_4bit_send_string_pos(&lcd, (uint8 *)"Loading", 1, 1);
    __delay_ms(200);
    for(counter2 = 0; counter2 < 3; counter2++){
        for(counter1 = 8; counter1 < 11; counter1++){
            ret = lcd_4bit_send_char_data_pos(&lcd, '.', 1, counter1);
            __delay_ms(250);
        }
        ret = lcd_4bit_send_string_pos(&lcd, (uint8 *)"   ", 1, 8);
        __delay_ms(250);
    }
    ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
    __delay_ms(100);
    ret = lcd_4bit_send_string_pos(&lcd, (uint8 *)"Voting is ready", 1, 1);
    __delay_ms(750);
    ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
}

void display(void){
    read_eeprom();
    
    ret = convert_uint16_to_string(can_A, can_A_str);
    ret = convert_uint16_to_string(can_B, can_B_str);
    ret = convert_uint16_to_string(can_C, can_C_str);
    ret = convert_uint16_to_string(can_D, can_D_str);
    
    ret = lcd_4bit_send_string_pos(&lcd, (uint8 *)"A:", 1, 1);
    ret = lcd_4bit_send_string_pos(&lcd, can_A_str, 1, 3);
    ret = lcd_4bit_send_string_pos(&lcd, (uint8 *)"B:", 1, 12);
    ret = lcd_4bit_send_string_pos(&lcd, can_B_str, 1, 14);
    ret = lcd_4bit_send_string_pos(&lcd, (uint8 *)"C:", 2, 1);
    ret = lcd_4bit_send_string_pos(&lcd, can_C_str, 2, 3);
    ret = lcd_4bit_send_string_pos(&lcd, (uint8 *)"D:", 2, 12);
    ret = lcd_4bit_send_string_pos(&lcd, can_D_str, 2, 14);
    if(operation_mode){
        ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
    }
}

void clear_eeprom(void){
    Data_EEPROM_WriteByte(0x0000, 0x00);
    Data_EEPROM_WriteByte(0x0008, 0x00);
    Data_EEPROM_WriteByte(0x0010, 0x00);
    Data_EEPROM_WriteByte(0x0018, 0x00);
}

void store_eeprom(void){
    Data_EEPROM_WriteByte(0x0000, can_A);
    Data_EEPROM_WriteByte(0x0008, can_B);
    Data_EEPROM_WriteByte(0x0010, can_C);
    Data_EEPROM_WriteByte(0x0018, can_D);
}

void read_eeprom(void){
    Data_EEPROM_ReadByte(0x0000, &can_A);
    Data_EEPROM_ReadByte(0x0008, &can_B);
    Data_EEPROM_ReadByte(0x0010, &can_C);
    Data_EEPROM_ReadByte(0x0018, &can_D);
}

void winner(void){
	if((can_A > can_B) && (can_A > can_C) && (can_A > can_D)){
        /* Display that A is the winner */
        lcd_4bit_send_string_pos(&lcd, (uint8 *)"A is the winner", 1, 1);
    }
    else if((can_B > can_A) && (can_B > can_C) && (can_B > can_D)){
        /* Display that B is the winner */
        lcd_4bit_send_string_pos(&lcd, (uint8 *)"B is the winner", 1, 1);
    }
    else if((can_C > can_A) && (can_C > can_B) && (can_C > can_D)){
        /* Display that C is the winner */
        lcd_4bit_send_string_pos(&lcd, (uint8 *)"C is the winner", 1, 1);
    }
    else{
        /* Display that D is the winner */
        lcd_4bit_send_string_pos(&lcd, (uint8 *)"D is the winner", 1, 1);
    }
    if(operation_mode == NORMAL_MODE){
        ret = lcd_4bit_send_command(&lcd, LCD_CLEAR);
    }
}