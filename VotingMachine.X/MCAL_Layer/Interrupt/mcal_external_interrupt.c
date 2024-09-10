/* 
 * File:   mcal_external_interrupt.c
 * Author: omar fathy
 *
 * Created on 29 June 2024, 20:46
 */

#include "mcal_external_interrupt.h"

static void (* INT0_InterruptHandler)(void) = NULL;
static void (* INT1_InterruptHandler)(void) = NULL;
static void (* INT2_InterruptHandler)(void) = NULL;

static void (* RB4_InterruptHandler_HIGH)(void) = NULL;
static void (* RB4_InterruptHandler_LOW)(void) = NULL;
static void (* RB5_InterruptHandler_HIGH)(void) = NULL;
static void (* RB5_InterruptHandler_LOW)(void) = NULL;
static void (* RB6_InterruptHandler_HIGH)(void) = NULL;
static void (* RB6_InterruptHandler_LOW)(void) = NULL;
static void (* RB7_InterruptHandler_HIGH)(void) = NULL;
static void (* RB7_InterruptHandler_LOW)(void) = NULL;

static Std_ReturnType interrupt_INTx_enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_priority_init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_edge_init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_pin_init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_clear_flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (* InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (* InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (* InterruptHandler)(void));
static Std_ReturnType interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static Std_ReturnType interrupt_RBx_enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_priority_init(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_pin_init(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_clear_flag(const interrupt_RBx_t *int_obj);

void INT0_ISR(void){
    EXT_INT0_Interrupt_FlagClear();
    
    if(INT0_InterruptHandler){
        INT0_InterruptHandler();
    }
}

void INT1_ISR(void){
    EXT_INT1_Interrupt_FlagClear();
    
    if(INT1_InterruptHandler){
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void){
    EXT_INT2_Interrupt_FlagClear();
    
    if(INT2_InterruptHandler){
        INT2_InterruptHandler();
    }
}

void RB4_ISR(uint8 RB4_source){
    EXT_RBx_Interrupt_FlagClear();
    if(RB4_source == 0){
        if(RB4_InterruptHandler_HIGH){
        RB4_InterruptHandler_HIGH();
        }
    }
    else if(RB4_source == 1){
       if(RB4_InterruptHandler_LOW){
        RB4_InterruptHandler_LOW();
        } 
    }
}

void RB5_ISR(uint8 RB5_source){
    EXT_RBx_Interrupt_FlagClear();
    if(RB5_source == 0){
        if(RB5_InterruptHandler_HIGH){
        RB5_InterruptHandler_HIGH();
        }
    }
    else if(RB5_source == 1){
       if(RB5_InterruptHandler_LOW){
        RB5_InterruptHandler_LOW();
        } 
    }
}

void RB6_ISR(uint8 RB6_source){
    EXT_RBx_Interrupt_FlagClear();
    if(RB6_source == 0){
        if(RB6_InterruptHandler_HIGH){
        RB6_InterruptHandler_HIGH();
        }
    }
    else if(RB6_source == 1){
       if(RB6_InterruptHandler_LOW){
        RB6_InterruptHandler_LOW();
        } 
    }
}

void RB7_ISR(uint8 RB7_source){
    EXT_RBx_Interrupt_FlagClear();
    if(RB7_source == 0){
        if(RB7_InterruptHandler_HIGH){
        RB7_InterruptHandler_HIGH();
        }
    }
    else if(RB7_source == 1){
       if(RB7_InterruptHandler_LOW){
        RB7_InterruptHandler_LOW();
        } 
    }
}

/**
 * @brief Initialize INTx interrupt
 * @param int_obj (pointer to interrupt configuration)
 * @return Status of the function
 */
Std_ReturnType interrupt_INTx_initialize(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = interrupt_INTx_disable(int_obj);
        ret = interrupt_INTx_clear_flag(int_obj);
        ret = interrupt_INTx_edge_init(int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret = interrupt_INTx_priority_init(int_obj);
#endif
        ret = interrupt_INTx_pin_init(int_obj);
        ret = interrupt_INTx_SetInterruptHandler(int_obj);
        ret = interrupt_INTx_enable(int_obj);
    }

    return ret;
}

/**
 * @brief Deinitialize INTx interrupt
 * @param int_obj (pointer to interrupt configuration)
 * @return Status of the function
 */
Std_ReturnType interrupt_INTx_deinitialize(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = interrupt_INTx_disable(int_obj);
    }

    return ret;
}

/**
 * @brief Initialize RBx interrupt
 * @param int_obj (pointer to interrupt configuration)
 * @return Status of the function
 */
Std_ReturnType interrupt_RBx_initialize(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        EXT_RBx_Interrupt_Disable();
        EXT_RBx_Interrupt_FlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(int_obj->priority == INTERRUPT_PRIORITY_HIGH){
            INTERRUPT_GlobalInterruptEnableHigh();
            EXT_RBx_SetHighPriority();
        }
        else if(int_obj->priority == INTERRUPT_PRIORITY_LOW){
            INTERRUPT_GlobalInterruptEnableLow();
            EXT_RBx_SetlowPriority();
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        ret = gpio_pin_direction_initialize(&(int_obj->int_pin));
        switch(int_obj->int_pin.pin){
            case GPIO_PIN4:
                RB4_InterruptHandler_HIGH = int_obj->InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->InterruptHandler_LOW;
                ret = E_OK;
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler_HIGH = int_obj->InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->InterruptHandler_LOW;
                ret = E_OK;
                break;
            case GPIO_PIN6:
                RB6_InterruptHandler_HIGH = int_obj->InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->InterruptHandler_LOW;
                ret = E_OK;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler_HIGH = int_obj->InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->InterruptHandler_LOW;
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
        EXT_RBx_Interrupt_Enable();
    }

    return ret;
}

/**
 * @brief Deinitialize RBx interrupt
 * @param int_obj (pointer to interrupt configuration)
 * @return Status of the function
 */
Std_ReturnType interrupt_RBx_deinitialize(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        EXT_RBx_Interrupt_Disable();
        EXT_RBx_Interrupt_FlagClear();
//        ret = interrupt_RBx_disable(int_obj);
//        ret = interrupt_RBx_clear_flag(int_obj);
    }

    return ret;
}

static Std_ReturnType interrupt_INTx_enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_INT0:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                INTERRUPT_GlobalInterruptEnableHigh();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_Interrupt_Enable();
                ret = E_OK;
                break;
            case INTERRUPT_INT1:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(int_obj->priority == INTERRUPT_PRIORITY_HIGH){
                    INTERRUPT_GlobalInterruptEnableHigh();
                }
                else if(int_obj->priority == INTERRUPT_PRIORITY_LOW){
                    INTERRUPT_GlobalInterruptEnableLow();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_Interrupt_Enable();
                ret = E_OK;
                break;
            case INTERRUPT_INT2:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(int_obj->priority == INTERRUPT_PRIORITY_HIGH){
                    INTERRUPT_GlobalInterruptEnableHigh();
                }
                else if(int_obj->priority == INTERRUPT_PRIORITY_LOW){
                    INTERRUPT_GlobalInterruptEnableLow();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_Interrupt_Enable();
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;
        }
    }

    return ret;
}

static Std_ReturnType interrupt_INTx_disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_INT0:
                EXT_INT0_Interrupt_Disable();
                ret = E_OK;
                break;
            case INTERRUPT_INT1:
                EXT_INT1_Interrupt_Disable();
                ret = E_OK;
                break;
            case INTERRUPT_INT2:
                EXT_INT2_Interrupt_Disable();
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;
        }
    }

    return ret;
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_INTx_priority_init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_INT1:
                if(int_obj->priority == INTERRUPT_PRIORITY_HIGH){
                    EXT_INT1_SetHighPriority();
                }
                else if(int_obj->priority == INTERRUPT_PRIORITY_LOW){
                    EXT_INT1_SetlowPriority();
                }
                ret = E_OK;
                break;
            case INTERRUPT_INT2:
                if(int_obj->priority == INTERRUPT_PRIORITY_HIGH){
                    EXT_INT2_SetHighPriority();
                }
                else if(int_obj->priority == INTERRUPT_PRIORITY_LOW){
                    EXT_INT2_SetlowPriority();
                }
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;
        }
    }

    return ret;
}
#endif

static Std_ReturnType interrupt_INTx_edge_init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_INT0:
                if(int_obj->edge == INTERRUPT_FALLING_EDGE){
                    EXT_INT0_FallingEdge();
                }
                else if(int_obj->edge == INTERRUPT_RISING_EDGE){
                    EXT_INT0_RisingEdge();
                }
                ret = E_OK;
                break;
            case INTERRUPT_INT1:
                if(int_obj->edge == INTERRUPT_FALLING_EDGE){
                    EXT_INT1_FallingEdge();
                }
                else if(int_obj->edge == INTERRUPT_RISING_EDGE){
                    EXT_INT1_RisingEdge();
                }
                ret = E_OK;
                break;
            case INTERRUPT_INT2:
                if(int_obj->edge == INTERRUPT_FALLING_EDGE){
                    EXT_INT2_FallingEdge();
                }
                else if(int_obj->edge == INTERRUPT_RISING_EDGE){
                    EXT_INT2_RisingEdge();
                }
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;
        }
    }

    return ret;
}

static Std_ReturnType interrupt_INTx_pin_init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(int_obj->int_pin));
    }

    return ret;
}

static Std_ReturnType interrupt_INTx_clear_flag(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_INT0:
                EXT_INT0_Interrupt_FlagClear();
                ret = E_OK;
                break;
            case INTERRUPT_INT1:
               EXT_INT1_Interrupt_FlagClear();
                ret = E_OK;
                break;
            case INTERRUPT_INT2:
                EXT_INT2_Interrupt_FlagClear();
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;
        }
    }

    return ret;
}

static Std_ReturnType INT0_SetInterruptHandler(void (* InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    
    if (InterruptHandler == NULL){
        ret = E_NOT_OK;
    }
    else{
        INT0_InterruptHandler = InterruptHandler;
        
        ret = E_NOT_OK;
    }

    return ret;
}

static Std_ReturnType INT1_SetInterruptHandler(void (* InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    
    if (InterruptHandler == NULL){
        ret = E_NOT_OK;
    }
    else{
        INT1_InterruptHandler = InterruptHandler;
        
        ret = E_NOT_OK;
    }

    return ret;
}

static Std_ReturnType INT2_SetInterruptHandler(void (* InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    
    if (InterruptHandler == NULL){
        ret = E_NOT_OK;
    }
    else{
        INT2_InterruptHandler = InterruptHandler;
        
        ret = E_NOT_OK;
    }

    return ret;
}

static Std_ReturnType interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj == NULL){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_INT0:
                ret = INT0_SetInterruptHandler(int_obj->InterruptHandler);
                break;
            case INTERRUPT_INT1:
                ret = INT1_SetInterruptHandler(int_obj->InterruptHandler);
                break;
            case INTERRUPT_INT2:
                ret = INT2_SetInterruptHandler(int_obj->InterruptHandler);
                break;
            default:
                ret = E_NOT_OK;
        }
    }

    return ret;
}
