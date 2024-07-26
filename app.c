#include "app.h"

STRUCT_SYSTEM_TYPE stSystemInfo;

char buffer[];
char hour_buffer[];
char minute_buffer[];
char cost_buffer[];

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
    if(stSystemInfo.stInterruptInfo.u8Emergency_Stop_Event){
        stSystemInfo.stInterruptInfo.u8Emergency_Stop_Event = false;
        stSystemInfo.u8System_Flow = eSF_Emergency;
        stSystemInfo.stInterruptInfo.u8Emergency_Stop_Flow = eESF_enterEmergency_Step;
        RELAY_setOff();
    }
    switch(stSystemInfo.stInterruptInfo.u8Emergency_Stop_Flow)
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
            stSystemInfo.stInterruptInfo.u8Emergency_Stop_Flow = eESF_Finish;
        }break;
        case eESF_Finish:{
            if(stTimerInfo.u16Emergency_Stop_Flow_Timer == 0){
                sendStringtoPenal("page Start");
                LED_setSystemOpenLight();                
                stSystemInfo.u8System_Flow = eSF_Idel;
                stSystemInfo.stInterruptInfo.u8Emergency_Stop_Flow = eESF_Idel;
            }  
        }break;
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
            switch(stSystemInfo.stChrage_Flow.u8Chrageing_Flow)
            {
                case eCF_Idel:{
                }break;
                case eCF_ConfirmVerification:{
                    stSystemInfo.stChrage_Flow.u8Chrageing_Flow = eCF_selsectPowerLevel;
                }break;
                case eCF_selsectPowerLevel:{
                    if(stSystemInfo.stChargeInfo.u8Power_Level == eCPL_7KW){
                        PWM_DutyCycleSet(PWM_GENERATOR_5, PWM_DUTYCYCLE_7KW);
                    }
                    else if(stSystemInfo.stChargeInfo.u8Power_Level == eCPL_9KW){
                        PWM_DutyCycleSet(PWM_GENERATOR_5, PWM_DUTYCYCLE_9KW);
                    }
                    else if(stSystemInfo.stChargeInfo.u8Power_Level == eCPL_12KW){
                        PWM_DutyCycleSet(PWM_GENERATOR_5, PWM_DUTYCYCLE_12KW);
                    }
                    else{
                        //exception
                    }
                    setStartChargringInit();
                    stSystemInfo.stChrage_Flow.u8Chrageing_Flow = eCF_startChargeing;
                }break;
                case eCF_startChargeing:{
                        getCPPinValue();
                        getPMUData();
                        setPanelDisplay();
                        switchCPpinState();
                        LED_setChargeStateDisplay();
                }break;
                case eCF_Checkouts:{
                    switch(stSystemInfo.stChrage_Flow.stSubFlow.u8Chargeing_Checkouts_Flow)
                    {
                        case eCCF_enterChargeing_Checkouts_step:{
                            RELAY_setOff();
                            TMR2_Stop();
                            sendStringtoPenal("page Total");
                            sendPowerMonitorUtilityData(ePSC_Read_Power);
                            //confirm if here need to add a delay for wait read power can edit by CHARGEING_FINISH_FLOW_TIME
                            stTimerInfo.u16Charging_Finish_Flow_Timer = CHARGEING_FINISH_FLOW_TIME;
                            stSystemInfo.stChrage_Flow.stSubFlow.u8Chargeing_Checkouts_Flow = eCCF_Finish;
                        }break;
                        case eCCF_Finish:{
                            if(stTimerInfo.u16Charging_Finish_Flow_Timer == 0){
                                DebugAndRfid_Printf("Total power: %.2f\r\n", (double)stSystemInfo.stChargeInfo.stPowerMeterInfo.fPower);
                                sprintf(buffer, "Total.t0.txt=\"%.2f\"", (double)stSystemInfo.stChargeInfo.stPowerMeterInfo.fPower);
                                sendStringtoPenal(buffer);
                                sprintf(hour_buffer, "Total.t1.txt=\"%d\"", stSystemInfo.stChargeInfo.u8Charge_Hour);
                                sendStringtoPenal(hour_buffer);
                                sprintf(minute_buffer, "Total.t2.txt=\"%d\"", stSystemInfo.stChargeInfo.u8Charge_Minute);
                                sendStringtoPenal(minute_buffer);
                                float cost = stSystemInfo.stChargeInfo.stPowerMeterInfo.fPower * 0.01;
                                sprintf(cost_buffer, "Total.t3.txt=\"%.2f\"", (double)cost);
                                sendStringtoPenal(cost_buffer);

                                sendPowerMonitorUtilityData(ePSC_Power_Disable);
                                 
                                stSystemInfo.stChrage_Flow.u8Chrageing_Flow = eCF_Idel;
                                stSystemInfo.stChrage_Flow.stSubFlow.u8Chargeing_Checkouts_Flow = eCCF_Idel;
                            }
                        }break;
                    }
                }break;
                case eCF_Finish:{
                    LED_setSystemOpenLight();
                    sendStringtoPenal("page End");
                    stSystemInfo.stChrage_Flow.u8Chrageing_Flow = eCF_Idel;
                }
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
    actionPowerMonitorUtility();
}

/*********************************************************************
 * Function:        void getCPPinValue(void)
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
void getCPPinValue(void) {
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
                if (CP_VEHICLE_CONNECTED(adc2_result)) stSystemInfo.stChargeInfo.CPs[1]++;
                else if (CP_READY(adc2_result)) stSystemInfo.stChargeInfo.CPs[2]++;
                else if (CP_READY_VENTILATION(adc2_result)) stSystemInfo.stChargeInfo.CPs[3]++;
                else if (CP_NO_VEHICLE(adc2_result)) stSystemInfo.stChargeInfo.CPs[0]++;
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
        if (stSystemInfo.stChargeInfo.CPs[i] > stSystemInfo.stChargeInfo.CPs[sort_max_CP_index]) {
            sort_max_CP_index = i;
            }
        }
        stSystemInfo.stChargeInfo.u8CP_Pin_Present = sort_max_CP_index;
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
                sendPowerMonitorUtilityData(ePSC_Read_Voltage);               
            }break;
            case ePGD_Current:{
                sendPowerMonitorUtilityData(ePSC_Read_Current);                
            }break;
            case ePGD_Power:{
                sendPowerMonitorUtilityData(ePSC_Read_Power);                
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
        switch(stSystemInfo.stChargeInfo.u8CP_Pin_Present){
            case eCCV_12V:{
            }break;
            case eCCV_9V:{
            }break;
            case eCCV_6V:{
                switch(stTimerGetInfo.u8Panel_Display_Chargeing_Info_Index)
                {
//                    case ePDD_Voltage:{
//                        //send voltage data to panel from stSystemInfo.stChargeInfo.stPowerMeterInfo.fVoltage
//                    }break;
//                    case ePDD_Current:{
//                        //send current data to panel from stSystemInfo.stChargeInfo.stPowerMeterInfo.fCurrent
//                    }break;
                    case ePDD_Power:{
                            DebugAndRfid_Printf("Power Meter power_result: %.2f\r\n", (double)stSystemInfo.stChargeInfo.stPowerMeterInfo.fPower);
                            sprintf(buffer, "Charging.t0.txt=\"%.2f\"", (double)stSystemInfo.stChargeInfo.stPowerMeterInfo.fPower);
                            sendStringtoPenal(buffer);
                        //send power data to panel from stSystemInfo.stChargeInfo.stPowerMeterInfo.fPower
                    }break;
                    case ePDD_Hour:{
                        
                        sprintf(hour_buffer, "Charging.t1.txt=\"%d\"", stSystemInfo.stChargeInfo.u8Charge_Hour);
                        sendStringtoPenal(hour_buffer);
                        //send power data to panel from stSystemInfo.stChargeInfo.u8Charge_Hour
                    }break;
                    case ePDD_Minute:{                      
                        sprintf(minute_buffer, "Charging.t2.txt=\"%d\"", stSystemInfo.stChargeInfo.u8Charge_Minute);
                        sendStringtoPenal(minute_buffer);
                        //send power data to panel from stSystemInfo.stChargeInfo.u8Charge_Minute
                    }break;
                    default:{
                        stTimerGetInfo.u8Panel_Display_Chargeing_Info_Index = 0;
                    }break;
                }
            }break;            
            case eCCV_3V:{
                DebugAndRfid_Printf(buffer, "Charging.t0.txt=\"%d\"", stSystemInfo.stChargeInfo.stPowerMeterInfo.fPower);
                sendStringtoPenal(buffer);
            }break;
        }
        stTimerInfo.u16Desplay_Charging_Panel_Info_Timer = DESPLAY_CHARGEING_PANEL_INFO_TIME;
    }  
}

/*********************************************************************
 * Function:        void switchCPpinState(void)
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
void switchCPpinState(void) {
    if(stSystemInfo.stChargeInfo.u8CP_Pin_Present != stSystemInfo.stChargeInfo.u8CP_Pin_Past){
        stSystemInfo.stChargeInfo.u8CP_Pin_Past = stSystemInfo.stChargeInfo.u8CP_Pin_Present;
        switch(stSystemInfo.stChargeInfo.u8CP_Pin_Present){
            case eCCV_12V:{
                sendStringtoPenal("page Input");
                DebugAndRfid_Printf("Ready, no Vehicle Detected\r\n");
                sendPowerMonitorUtilityData(ePSC_Power_Disable);
                RELAY_setOff();
            }break;
            case eCCV_9V:{
                sendStringtoPenal("page Wait");
                DebugAndRfid_Printf("Vehicle Detected\r\n");
                RELAY_setOff();
            }break;
            case eCCV_6V:{
                sendStringtoPenal("page Charging");
                setChargingTimeInit();
                DebugAndRfid_Printf("Vehicle Ready for Charging\r\n");
                sendStringtoPenal("Charging.t0.txt=\"0\"");
                sendStringtoPenal("Charging.t1.txt=\"0\"");
                sendStringtoPenal("Charging.t2.txt=\"0\"");
                sendPowerMonitorUtilityData(ePSC_Power_Enable);
                RELAY_setOn();
            }break;
            case eCCV_3V:{
                sendStringtoPenal("page Charging");
                DebugAndRfid_Printf("Vehicle Ready for Charging - Ventilation Required\r\n");
                RELAY_setOn();
            }break;
            default:
                break;
        }
    }
    else{
    }
}

/*********************************************************************
 * Function:        void setStartChargringInit(void)
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
void setStartChargringInit(void) {
    stTimerGetInfo.u8ADC2_Get_Data_Index = 0;
    stTimerGetInfo.u8ADC2_Get_Data_Count = 0;
    stTimerInfo.u16Chargeing_CP_Timer = 0;
    stTimerGetInfo.u8PMU_Get_Data_Index = 0;
    stTimerInfo.u16Chargeing_PMU_Timer = 0;
    stTimerGetInfo.u8Panel_Display_Chargeing_Info_Index = 0;
    stTimerInfo.u16Desplay_Charging_Panel_Info_Timer = 0;
    stSystemInfo.stChargeInfo.u8CP_Pin_Present = eCCV_12V;
    stSystemInfo.stChargeInfo.u8CP_Pin_Past = 0xFF;
    PWM_Enable();
}

/*********************************************************************
 * Function:        void setChargingTimeInit(void)
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
void setChargingTimeInit(void) {
    TMR2_Start();
    stSystemInfo.stChargeInfo.u32Charge_Time = 0;
    stSystemInfo.stChargeInfo.u8Charge_Hour = 0;
    stSystemInfo.stChargeInfo.u8Charge_Minute = 0;
}
