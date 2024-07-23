#include "app.h"

#include "mcc_generated_files/delay.h"

void RELAY_setOnTest() {
    PWM_Disable();
    PWM_DutyCycleSet(4, 0xF0); // Duty cycle = 100% LOW
    PWM_Enable();
    DELAY_milliseconds(500);
    PWM_DutyCycleSet(4, 0x90);
    //RY_SetLow();
    DebugAndRfid_Printf("ON_RELAY\r\n");
}

void RELAY_setOffTest() {
    PWM_Disable();
    PWM_DutyCycleSet(4, 0x00); // Duty cycle = 0% HIGH 
    PWM_Enable();
//    RY_SetHigh();
    DebugAndRfid_Printf("OFF_RELAY\r\n");
}

void RELAY_setOn() {
    PWM_DutyCycleSet(4, 0xF0);
    DELAY_milliseconds(500);
    PWM_DutyCycleSet(4, 0x90);
}

void RELAY_setOff() {
    PWM_DutyCycleSet(4, 0x00);
}