#include "app.h"

STRUCT_SYSTEM_TYPE stSystemInfo;

int CPs[NUM_CP] = {0};

/*********************************************************************
 * Function:        void APP_interruptOccurredAtEX1(void)
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
void APP_interruptOccurredAtEX1(void) {
    if(stSystemInfo.stPanelInfo.u8Emergency_Stop_Event){
        stSystemInfo.u8System_Flow = eSF_Emergency;
        stSystemInfo.stPanelInfo.u8Emergency_Stop_Flow = eESF_enterEmergency_Step;
        RELAY_setOff();
        switch(stSystemInfo.stPanelInfo.u8Emergency_Stop_Flow)
        {
            case eESF_enterEmergency_Step:{
                sendStringtoPenal("page Interrupt");
                int sg;
                for (sg = 0; sg < 24; sg++) {
                    if (sg < 13) {
                        LED_setRed();
                    } 
                    else if (sg >= 13 && sg < 16) {
                        LED_setWhite();
                    } 
                    else if (sg >= 16 && sg <= 18) {
                        LED_setSpace();
                    } 
                    else {
                        LED_setWhite();
                    }
                }
                stTimerInfo.u16Emergency_Stop_Flow_Timer = EMERGENCY_STOP_FLOW_TIME;
                stSystemInfo.stPanelInfo.u8Emergency_Stop_Flow = eESF_Finish;
            }break;
            case eESF_Finish:{
                if(stTimerInfo.u16Emergency_Stop_Flow_Timer == 0){
                    sendStringtoPenal("page Start");
                    LED_setSystemOpenLight();
                    stSystemInfo.stPanelInfo.u8Emergency_Stop_Event = false;
                    stSystemInfo.u8System_Flow = eSF_Idel;
                    stSystemInfo.stPanelInfo.u8Emergency_Stop_Flow = eESF_Idel;
                }  
            }break;
        }
    }
}

/*********************************************************************
 * Function:        void APP_runPanelFlow(void)
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
void APP_runPanelFlow(void) {
    switch(stSystemInfo.u8System_Flow)
    {
        case eSF_Idel:{
        }break;
        case eSF_Charge:{
            switch(stSystemInfo.u8Chrageing_Flow)
            {
                case eCF_ConfirmVerification:{
                    stSystemInfo.u8Chrageing_Flow = eCF_selsectPowerLevel;
                }break;
                case eCF_selsectPowerLevel:{
                    if(stSystemInfo.stChargeInfo.u8Power_Level = eCPL_7KW){
                        PWM_DutyCycleSet(PWM_GENERATOR_5, PWM_DUTYCYCLE_7KW);
                    }
                    else if(stSystemInfo.stChargeInfo.u8Power_Level = eCPL_9KW){
                        PWM_DutyCycleSet(PWM_GENERATOR_5, PWM_DUTYCYCLE_9KW);
                    }
                    else if(stSystemInfo.stChargeInfo.u8Power_Level = eCPL_12KW){
                        PWM_DutyCycleSet(PWM_GENERATOR_5, PWM_DUTYCYCLE_12KW);
                    }
                    else{
                        //exception
                    }
                    PWM_Enable();
                    stTimerGetInfo.u8ADC2_Get_Data_Index = 0;
                    stSystemInfo.u8Chrageing_Flow = eCF_startChargeing;
                }break;
                case eCF_startChargeing:{
                    startChargeingFlow();
                }break;
                case eCF_Finish:{
                    
                }break;
            }
        }
        case eSF_EnginnerMode:{
            switch(stEngineerModeInfo.u8Engineer_Mode_Flow)
            {
                case eEMF_Idel:{
                }break;
                case eEMF_testLed:{
                    ENGINEERMODE_testLed();
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_Idel;
                }break;
                case eEMF_testRelayOn:{
                    ENGINEERMODE_testRelay(1);
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_Idel;
                }break;
                case eEMF_testRelayOff:{
                    ENGINEERMODE_testRelay(0);
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_Idel;
                }break;
                case eEMF_testGFCIOn:{
                    ENGINEERMODE_testGFCI(1);
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_Idel;
                }break;
                case eEMF_testGFCIOff:{
                    ENGINEERMODE_testGFCI(0);
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_Idel;
                }break;
                case eEMF_testRFID:{
                    ENGINEERMODE_testRFID();
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_Idel;
                }break;
                case eEMF_testReturn_verify:{
                    ENGINEERMODE_testReturnVerify();
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_Idel;
                }break;
                case eEMF_testMeterValue:{
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_Idel;
                }break;
                case eEMF_testParameter:{
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_Idel;
                }
                default:
                    break;
            }
        }
        case eSF_FactoryMode:{
            
        }
    }    
}

/*********************************************************************
 * Function:        void APP_taskMainFlow(void)
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
void APP_taskMainFlow(void) {
    APP_interruptOccurredAtEX1();
    APP_runPanelFlow();
}

/*********************************************************************
 * Function:        void APP_taskUartFlow(void)
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
void APP_taskUartFlow(void) {
    checkUartDataBuf();
}

/*********************************************************************
 * Function:        void startChargeingFlow(void)
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
void startChargeingFlow(void) {
    getCPPinData();
    getPMUData();
    setPanelDisplay();
    
    LED_setChargeStateDisplay();
    //here can do something
}

/*********************************************************************
 * Function:        void getCPPinData(void)
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
void getCPPinData(void) {
    switch(stTimerGetInfo.u8ADC2_Get_Data_Index)      
    {
        case 0:{
            ADC2_Enable();
            ADC2_SoftwareTriggerEnable();
            stTimerInfo.u16Chargeing_CP_Timer = GET_CHARGEING_CP_TIME;
            stTimerGetInfo.u8ADC2_Get_Data_Index = 1;
        }break;
        case 1:{
            if(stTimerInfo.u16Chargeing_CP_Timer == 0)
            {
                ADC2_SoftwareTriggerDisable();
                uint16_t adc2_result;
                adc2_result = ADC2BUF2;
                printf("HERE is 12V ADC is %d\r\n", adc2_result);

                // 根據測量結果判斷狀態
                if (CP_VEHICLE_CONNECTED(adc2_result)) CPs[1]++;
                else if (CP_READY(adc2_result)) CPs[2]++;
                else if (CP_READY_VENTILATION(adc2_result)) CPs[3]++;
                else if (CP_NO_VEHICLE(adc2_result)) CPs[0]++;
                ADC2_Disable();
                stTimerGetInfo.u8ADC2_Get_Data_Index = 0;
                stTimerGetInfo.u8ADC2_Get_Data_Count++;
            }
        }break;
    }
    
    if(stTimerGetInfo.u8ADC2_Get_Data_Count == GET_CHARGEING_CP_COUNT)
    {
        int sort_max_CP_index = 0;
        int i;
        for (i = 0; i < NUM_CP; i++) {
        if (CPs[i] > CPs[sort_max_CP_index]) {
            sort_max_CP_index = i;
            }
        }
        stSystemInfo.stChargeInfo.iCP_Pin = sort_max_CP_index;
        stTimerGetInfo.u8ADC2_Get_Data_Count = 0;
    }
}

/*********************************************************************
 * Function:        void getPMUData(void)
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
void getPMUData(void) {
    if(stTimerInfo.u16Chargeing_PMU_Timer == 0){
        switch(stTimerGetInfo.u8PMU_Get_Data_Index)
        {
            case ePGD_Voltage:{
                uint8_t voltage_read[8] = {0xA5, 0x08, 0x41, 0x00, 0x06, 0x4E, 0x02, 0x44};               
                UART_sendPowerMonitorUtilityData(sizeof(voltage_read),&voltage_read);
            }break;
            case ePGD_Current:{
                uint8_t current_read[8] = {0xA5, 0x08, 0x41, 0x00, 0x0E, 0x4E, 0x04, 0x4E};
                UART_sendPowerMonitorUtilityData(sizeof(current_read),&current_read);
            }break;
            case ePGD_Power:{
                uint8_t power_read[8] = {0xA5, 0x08, 0x41, 0x00, 0x1E, 0x4E, 0x08, 0x62};
                UART_sendPowerMonitorUtilityData(sizeof(power_read),&power_read);
            }break;
            default:{
                stTimerGetInfo.u8PMU_Get_Data_Index = 0;
            }break;
        }
        stTimerGetInfo.u8PMU_Get_Data_Index = (stTimerGetInfo.u8PMU_Get_Data_Index + 1) % GET_CHARGEING_PMU_GET_DATA_COUNT;
        stTimerInfo.u16Chargeing_PMU_Timer = GET_CHARGEING_PMU_TIME;
    }
}

/*********************************************************************
 * Function:        void setPanelDisplay(void)
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
void setPanelDisplay(void) {
    if(stTimerInfo.u16Desplay_Charging_Panel_Info_Timer == 0){
        switch(stTimerGetInfo.u8Panel_Display_Chargeing_Info_Index)
        {
            case ePDD_Voltage:{
                
                //send voltage data to panel from stSystemInfo.stChargeInfo.stPowerMeterInfo.fVoltage
            }break;
            case ePDD_Current:{
                //send current data to panel from stSystemInfo.stChargeInfo.stPowerMeterInfo.fCurrent
            }break;
            case ePDD_Power:{
                //send power data to panel from stSystemInfo.stChargeInfo.stPowerMeterInfo.fPower
            }break;
            default:{
                stTimerGetInfo.u8Panel_Display_Chargeing_Info_Index = 0;
            }break;
        }
        stTimerInfo.u16Desplay_Charging_Panel_Info_Timer = DESPLAY_CHARGEING_PANEL_INFO_TIME;
    }
}
