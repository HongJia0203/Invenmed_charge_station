#include "app.h"

STRUCT_TIMER_TYPE stTimerInfo ={0};
STRUCT_TIMER_GET_DATA_TYPE stTimerGetInfo ={0};


void TMR2_CallBack() {
    stSystemInfo.stChargeInfo.u32Charge_Time++;
    stSystemInfo.stChargeInfo.u8Charge_Hour = stSystemInfo.stChargeInfo.u32Charge_Time / 60;
    stSystemInfo.stChargeInfo.u8Charge_Minute = stSystemInfo.stChargeInfo.u32Charge_Time % 60;
}
void TMR3_CallBack() {
    tickTimer1ms();
}
/*********************************************************************
 * Function:        void tickTimer1ms(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void tickTimer1ms(void) {
    if(stTimerInfo.u16Emergency_Stop_Flow_Timer){
        stTimerInfo.u16Emergency_Stop_Flow_Timer--;
    }
    if(stTimerInfo.u16Chargeing_CP_Timer){
        stTimerInfo.u16Chargeing_CP_Timer--;
    }
    if(stTimerInfo.u16Chargeing_PMU_Timer){
        stTimerInfo.u16Chargeing_PMU_Timer--;
    }
    if(stTimerInfo.u16Charging_Finish_Flow_Timer){
        stTimerInfo.u16Charging_Finish_Flow_Timer--;
    }
    if(stPowerMeterTX.u8Tx_Delay){
        stPowerMeterTX.u8Tx_Delay--;
    }
}
