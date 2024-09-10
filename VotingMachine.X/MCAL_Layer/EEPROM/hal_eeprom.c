/* 
 * File:   hal_eeprom.c
 * Author: omar fathy
 *
 * Created on July 3, 2024, 5:40 PM
 */

#include "hal_eeprom.h"

/**
 * @brief Write byte in EEPROM
 * @param add (the address to write the data in)
 * @param data (the data to be written)
 * @return State of the function
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 adr, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
     /* Read the state of the interrupt */
    uint8 Global_Interrupt_status = INTCONbits.GIE;
    
    /* Update the address register */
    EEADRH = (uint8)((adr >> 8) & 0x03);
    EEADR = (uint8)(adr & 0xFF);
    
    /* Update the data register */
    EEDATA = data;
    
    /* Select access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    
    /* Allow write cycles to data EEPROM memory */
    EECON1bits.WREN = ALLOW_WRITE_FLASH_EEPROM;
    
    /* Disable all interrupts "General Interrupt" */
    INTERRUPT_GlobalInterruptDisable();
    
    /* Imp sequence */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    /* Initialize data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATE_EEPROM_ERASE_WRITE;
    
    /* Wait for writing to be complete */
    while(EECON1bits.WR);
    
    /* Inhibit write cycles to data EEPROM memory */
    EECON1bits.WREN = INHIBIT_WRITE_FLASH_EEPROM;
    
    /* Restore the Interrupt status */
    INTCONbits.GIE = Global_Interrupt_status;
    
    return ret;
}

/**
 * @brief Read byte from EEPROM
 * @param add (the address to read the data from)
 * @param data (the read data)
 * @return State of the function
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 adr, uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    
    if(data == NULL){
        ret = E_NOT_OK;
    }
    else{
        /* Update the address register */
        EEADRH = (uint8)((adr >> 8) & 0x03);
        EEADR = (uint8)(adr & 0xFF);

        /* Select access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        
        /* Initiate data EEPROM read cycle */
        EECON1bits.RD = INITIATE_EEPROM_READ;
        /* It is preferred to do "No Operation" for high frequency crystals */
        NOP();
        NOP();
        
        /* Return data */
        *data = EEDATA;
        
        ret = E_OK;
    }
    return ret;
}
