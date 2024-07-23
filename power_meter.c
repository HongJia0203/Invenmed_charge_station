#include "app.h"

STRUCT_POWERMETER_INFO_TYPE stPowerMeterInfo;

/*********************************************************************
 * Function:        void actionPowerMonitorUtility(void)
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
void actionPowerMonitorUtility(void) {  
    processPowerMeterCmd();
    
    if((stSystemInfo.stPowerMeterTX.u8Length > 0) && (stSystemInfo.stPowerMeterTX.u8Status == busy) && (!stSystemInfo.stPowerMeterTX.u8Tx_Delay) && (stSystemInfo.stPowerMeterTX.u8Count > 0)){
        UART_sendPowerMonitorUtilityData(stSystemInfo.stPowerMeterTX.u8Length,stSystemInfo.stPowerMeterTX.u8Buf);
        stSystemInfo.stPowerMeterTX.u8Count--;
    }
    else{
        if(stSystemInfo.stPowerMeterTX.u8Count == 0){
            stPowerMeterInfo.u8Cmd_Type = ePSC_End;
            memset(stSystemInfo.stPowerMeterTX.u8Buf,0,TX_BUFFER_LENGTH);
        }
        else if((stSystemInfo.stPowerMeterTX.u8Status == busy) && (!stSystemInfo.stPowerMeterTX.u8Tx_Delay)){
            stSystemInfo.stPowerMeterTX.u8Tx_Delay = POWER_METER_TX_RETRY_TIME;
        }       
    } 
}

/*********************************************************************
 * Function:        void requestPowerMonitorUtilityValue(uint8_t cmd)
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
void sendPowerMonitorUtilityData(uint8_t cmd) {
    switch(cmd)
    {
        case ePSC_Power_Enable:{
            stPowerMeterInfo.stPowerMeterCmd.u8Power_Enable = 1;
        }break;
        case ePSC_Power_Disable:{
            stPowerMeterInfo.stPowerMeterCmd.u8Power_Disable = 1;
        }break;
        case ePSC_Read_Voltage:{
            stPowerMeterInfo.stPowerMeterCmd.u8Read_Voltage = 1;
        }break;
        case ePSC_Read_Current:{
            stPowerMeterInfo.stPowerMeterCmd.u8Read_Current = 1;
        }break;
        case ePSC_Read_Power:{
            stPowerMeterInfo.stPowerMeterCmd.u8Read_Power = 1;
        }break;     
    }
}

/*********************************************************************
 * Function:        void processPowerMeterCmd(void)
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
void processPowerMeterCmd(void) {
    if(stPowerMeterInfo.stPowerMeterCmd.u8Power_Enable == 1){
        if(stSystemInfo.stPowerMeterTX.u8Status == idle){
            memset(stSystemInfo.stPowerMeterTX.u8Buf,0,TX_BUFFER_LENGTH);
            stPowerMeterInfo.u8Cmd_Type = ePSC_Power_Enable;
//            uint8_t power_enable[12] = {0xA5, 0x0C, 0x41, 0x00, 0x94, 0x4D, 0x04, 0x01, 0x80, 0x00, 0x03, 0x5B};
//            UART_sendPowerMonitorUtilityData(sizeof(power_enable),&power_enable);            
            stSystemInfo.stPowerMeterTX.u8Buf[0] = 0xA5;
            stSystemInfo.stPowerMeterTX.u8Buf[1] = 0x0C;
            stSystemInfo.stPowerMeterTX.u8Buf[2] = 0x41;
            stSystemInfo.stPowerMeterTX.u8Buf[3] = 0x00;
            stSystemInfo.stPowerMeterTX.u8Buf[4] = 0x94;
            stSystemInfo.stPowerMeterTX.u8Buf[5] = 0x4D;
            stSystemInfo.stPowerMeterTX.u8Buf[6] = 0x04;
            stSystemInfo.stPowerMeterTX.u8Buf[7] = 0x01;
            stSystemInfo.stPowerMeterTX.u8Buf[8] = 0x80;
            stSystemInfo.stPowerMeterTX.u8Buf[9] = 0x00;
            stSystemInfo.stPowerMeterTX.u8Buf[10] = 0x03;
            stSystemInfo.stPowerMeterTX.u8Buf[11] = calculateCheckSum(&stSystemInfo.stPowerMeterTX.u8Buf,11);
            
            stSystemInfo.stPowerMeterTX.u8Length = 12;
            
            stPowerMeterInfo.stPowerMeterCmd.u8Power_Enable = 0;
            stSystemInfo.stPowerMeterTX.u8Count = POWER_METER_TX_RETRY_COUNT;
            stSystemInfo.stPowerMeterTX.u8Status = busy;
        }
    }
    if(stPowerMeterInfo.stPowerMeterCmd.u8Power_Disable == 1){
        if(stSystemInfo.stPowerMeterTX.u8Status == idle){
            memset(stSystemInfo.stPowerMeterTX.u8Buf,0,TX_BUFFER_LENGTH);
            stPowerMeterInfo.u8Cmd_Type = ePSC_Power_Disable;
            uint8_t power_disable[12] = {0xA5, 0x0C, 0x41, 0x00, 0x94, 0x4D, 0x04, 0x00, 0x80, 0x00, 0x03, 0x5A};
//            UART_sendPowerMonitorUtilityData(sizeof(power_disable),&power_disable);
            
            memcpy(&stSystemInfo.stPowerMeterTX.u8Buf[0],power_disable,12);
            
            stPowerMeterInfo.stPowerMeterCmd.u8Power_Disable = 0;
            stSystemInfo.stPowerMeterTX.u8Count = POWER_METER_TX_RETRY_COUNT;
            stSystemInfo.stPowerMeterTX.u8Status = busy;
        }
    }
    if(stPowerMeterInfo.stPowerMeterCmd.u8Read_Voltage == 1){
        if(stSystemInfo.stPowerMeterTX.u8Status == idle){
            memset(stSystemInfo.stPowerMeterTX.u8Buf,0,TX_BUFFER_LENGTH);
            stPowerMeterInfo.u8Cmd_Type = ePSC_Read_Voltage;
            uint8_t voltage_read[8] = {0xA5, 0x08, 0x41, 0x00, 0x06, 0x4E, 0x02, 0x44};               
//            UART_sendPowerMonitorUtilityData(sizeof(voltage_read),&voltage_read);
            memcpy(&stSystemInfo.stPowerMeterTX.u8Buf[0],voltage_read,8);
            
            stPowerMeterInfo.stPowerMeterCmd.u8Read_Voltage = 0;
            stSystemInfo.stPowerMeterTX.u8Count = POWER_METER_TX_RETRY_COUNT;
            stSystemInfo.stPowerMeterTX.u8Status = busy;
        }
    }
    if(stPowerMeterInfo.stPowerMeterCmd.u8Read_Current == 1){
        if(stSystemInfo.stPowerMeterTX.u8Status == idle){
            memset(stSystemInfo.stPowerMeterTX.u8Buf,0,TX_BUFFER_LENGTH);
            stPowerMeterInfo.u8Cmd_Type = ePSC_Read_Current;
            uint8_t current_read[8] = {0xA5, 0x08, 0x41, 0x00, 0x0E, 0x4E, 0x04, 0x4E};
//            UART_sendPowerMonitorUtilityData(sizeof(current_read),&current_read);
            memcpy(&stSystemInfo.stPowerMeterTX.u8Buf[0],current_read,8);
            
            stPowerMeterInfo.stPowerMeterCmd.u8Read_Current = 0;
            stSystemInfo.stPowerMeterTX.u8Count = POWER_METER_TX_RETRY_COUNT;
            stSystemInfo.stPowerMeterTX.u8Status = busy;
        }
    }
    if(stPowerMeterInfo.stPowerMeterCmd.u8Read_Power == 1){
        if(stSystemInfo.stPowerMeterTX.u8Status == idle){
            memset(stSystemInfo.stPowerMeterTX.u8Buf,0,TX_BUFFER_LENGTH);
            stPowerMeterInfo.u8Cmd_Type = ePSC_Read_Power;
            uint8_t power_read[8] = {0xA5, 0x08, 0x41, 0x00, 0x1E, 0x4E, 0x08, 0x62};
//            UART_sendPowerMonitorUtilityData(sizeof(power_read),&power_read);
            memcpy(&stSystemInfo.stPowerMeterTX.u8Buf[0],power_read,8);
            
            stPowerMeterInfo.stPowerMeterCmd.u8Read_Power = 0;
            stSystemInfo.stPowerMeterTX.u8Count = POWER_METER_TX_RETRY_COUNT;
            stSystemInfo.stPowerMeterTX.u8Status = busy;
        }
    }
}
