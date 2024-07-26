#include "app.h"

UART_DATA_TYPE stUart3Data,stUart4Data ={0};
UART_TX_TYPE stPowerMeterTX ={0};

void checkUartDataBuf(void) {
    while (UART3_IsRxReady())
    {
        getByteUart3(UART3_Read());
    }
    checkParserUart3();
    while (UART4_IsRxReady())
    {
        getByteUart4(UART4_Read());
    }
    checkParserUart4();
}

void getByteUart3(unsigned char B) {
    //stUart3Data.u8UartBuf[stUart3Data.u8WIBufIdx][stUart3Data.u8InBufLen++] = B;
    switch (stUart3Data.u8InBufLen)
    {
        case 0:
        {
            if (B == PANEL_BUF_HEAD)
            {
                stUart3Data.u8UartBuf[stUart3Data.u8WIBufIdx][stUart3Data.u8InBufLen++] = B;
            }
            else
            {
                stUart3Data.u8TargetBufLen = 0;
                stUart3Data.u8InBufLen = 0;
            }
        }break;
        case 1:
        {
            stUart3Data.u8UartBuf[stUart3Data.u8WIBufIdx][stUart3Data.u8InBufLen++] = B;
            stUart3Data.u8TargetBufLen = B;
        }break;
        default:
        {
            stUart3Data.u8UartBuf[stUart3Data.u8WIBufIdx][stUart3Data.u8InBufLen++] = B;
            if (stUart3Data.u8InBufLen == stUart3Data.u8TargetBufLen + 2)
            {
                if (calculateCRC16(&stUart3Data.u8UartBuf[stUart3Data.u8WIBufIdx],stUart3Data.u8InBufLen) == 0)
                {
                    stUart3Data.u8WIBufIdx = (stUart3Data.u8WIBufIdx + 1) % DEF_BUF_NUM;
                    stUart3Data.u8TargetBufLen = 0;
                    stUart3Data.u8InBufLen = 0;
                    return;
                }
                else
                {
                    stUart3Data.u8TargetBufLen = 0;
                    stUart3Data.u8InBufLen = 0;
                }
            }
        }break;
    }
}
void checkParserUart3(void) {
    while (stUart3Data.u8WIBufIdx != stUart3Data.u8ROBufIdx)
    {
        decodeUart3Data();
    }
}
void decodeUart3Data(void) {
    //here can do something
    uint8_t mode = stUart3Data.u8UartBuf[stUart3Data.u8ROBufIdx][2];
    uint8_t option = stUart3Data.u8UartBuf[stUart3Data.u8ROBufIdx][3];
    switch(mode){
        case PANEL_DEVELOP_MODE:{
            switch(option)
            {
                case PANEL_DEVELOP_MODE_TEST_LED_OPTION:{
                    stSystemInfo.u8System_Flow = eSF_EnginnerMode;
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_testLed;
                }break;
                case PANEL_DEVELOP_MODE_TEST_METER_OPTION:{
                    stSystemInfo.u8System_Flow = eSF_EnginnerMode;
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_testMeterValue;
                }break;
                case PANEL_DEVELOP_MODE_TEST_RELAY_OPTION:{
                    uint8_t parameter = stUart3Data.u8UartBuf[stUart3Data.u8ROBufIdx][4];
                    if(parameter == 0x4F){
                        stSystemInfo.u8System_Flow = eSF_EnginnerMode;
                        stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_testRelayOn;
                    }
                    else if(parameter == 0x43){
                        stSystemInfo.u8System_Flow = eSF_EnginnerMode;
                        stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_testRelayOff;
                    }
                    else{
                    }
                }break;
                case PANEL_DEVELOP_MODE_TEST_GFCI_OPTION:{
                    uint8_t parameter = stUart3Data.u8UartBuf[stUart3Data.u8ROBufIdx][4];
                    if(parameter == 0x4F){
                        stSystemInfo.u8System_Flow = eSF_EnginnerMode;
                        stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_testGFCIOn;
                    }
                    else if(parameter == 0x43){
                        stSystemInfo.u8System_Flow = eSF_EnginnerMode;
                        stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_testGFCIOff;
                    }
                    else{
                    }
                }break;
                case PANEL_DEVELOP_MODE_TEST_RFID_OPTION:{
                    stSystemInfo.u8System_Flow = eSF_EnginnerMode;
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_testRFID;
                }break;
                case PANEL_DEVELOP_MODE_TEST_PARAMETER_OPTION:{
                    stSystemInfo.u8System_Flow = eSF_EnginnerMode;
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_testParameter;
                }break;
                case PANEL_DEFAULT_OPTION:{
                    stSystemInfo.u8System_Flow = eSF_EnginnerMode;
                    stEngineerModeInfo.u8Engineer_Mode_Flow = eEMF_testReturn_verify;
                }break;
                default:{
                }break;
            }
        }break;
        case PANEL_PAGESTART_MODE:{
        }break;
        case PANEL_PAGEVERIFY_MODE:{
        }break;
        case PANEL_INFORMATION_MODE:{
        }break;
        case PANEL_PAGECASE_MODE:{
            switch(option){
                case PANEL_PAGECASE_MODE_7KW_OPTION:{                    
                    stSystemInfo.u8System_Flow = eSF_Charge;
                    stSystemInfo.stChrage_Flow.u8Chrageing_Flow = eCF_selsectPowerLevel;
                    stSystemInfo.stChargeInfo.u8Power_Level = eCPL_7KW;
                    
                }
                case PANEL_PAGECASE_MODE_9KW_OPTION:{
                    stSystemInfo.u8System_Flow = eSF_Charge;
                    stSystemInfo.stChrage_Flow.u8Chrageing_Flow = eCF_selsectPowerLevel;
                    stSystemInfo.stChargeInfo.u8Power_Level = eCPL_9KW;
                }
                case PANEL_PAGECASE_MODE_12KW_OPTION:{
                    stSystemInfo.u8System_Flow = eSF_Charge;
                    stSystemInfo.stChrage_Flow.u8Chrageing_Flow = eCF_selsectPowerLevel;
                    stSystemInfo.stChargeInfo.u8Power_Level = eCPL_12KW;
                }
                default:{
                }break;
            }
        }break;
        default:{
        }break;
    }
            
    stUart3Data.u8ROBufIdx = (stUart3Data.u8ROBufIdx + 1) % DEF_BUF_NUM; 
}

void getByteUart4(unsigned char B){
    switch (stUart4Data.u8InBufLen)
    {
        case 0:{
            if(B == POWER_METER_ACK){
                stUart4Data.u8UartBuf[stUart4Data.u8WIBufIdx][stUart4Data.u8InBufLen++] = B;
            }
            else if(B == POWER_METER_NACK){
                stPowerMeterTX.u8Tx_Delay = 0;
            }
            else if(B == POWER_METER_CSFAIL){
                memset(stPowerMeterTX.u8Buf,0,TX_BUFFER_LENGTH);
                stPowerMeterTX.u8Status = idle;
            }
            else{
                stUart4Data.u8TargetBufLen = 0;
                stUart4Data.u8InBufLen = 0;
            }
        }break;
        case 1:{
            stUart4Data.u8UartBuf[stUart4Data.u8WIBufIdx][stUart4Data.u8InBufLen++] = B;
            stUart4Data.u8TargetBufLen = B;
        }break;
        default:{
            stUart4Data.u8UartBuf[stUart4Data.u8WIBufIdx][stUart4Data.u8InBufLen++] = B;
            if (stUart4Data.u8InBufLen == stUart4Data.u8TargetBufLen)
            {
                if (stUart4Data.u8UartBuf[stUart4Data.u8WIBufIdx][stUart4Data.u8InBufLen] == calculateCheckSum(&stUart3Data.u8UartBuf[stUart4Data.u8WIBufIdx],stUart4Data.u8InBufLen -1))
                {
                    stUart4Data.u8WIBufIdx = (stUart4Data.u8WIBufIdx + 1) % DEF_BUF_NUM;
                    stUart4Data.u8TargetBufLen = 0;
                    stUart4Data.u8InBufLen = 0;
                    return;
                }
                else
                {
                    stUart4Data.u8TargetBufLen = 0;
                    stUart4Data.u8InBufLen = 0;
                }
            }
        }break;
    }
}
void checkParserUart4(void){
    while (stUart4Data.u8WIBufIdx != stUart4Data.u8ROBufIdx)
    {
        decodeUart4Data();
    }
}
void decodeUart4Data(void){
    //here can do something
//    uint8_t response_state = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][0];
//    uint8_t length = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][1];
    switch(stPowerMeterInfo.u8Cmd_Type)
    {
        case ePSC_Power_Enable:{
            //here do nothing>///<
        }break;
        case ePSC_Power_Disable:{
            //here do nothing>///<
        }break;
        case ePSC_Read_Voltage:{
            uint8_t L_byte = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][2];
            uint8_t H_byte = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][3];
            stSystemInfo.stChargeInfo.stPowerMeterInfo.fVoltage = ((float) H_byte * 256 + (float) L_byte) / 10.0f;
        }break;
        case ePSC_Read_Current:{
            uint8_t L_byte = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][2];
            uint8_t ML_byte = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][3];
            uint8_t MH_byte = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][4];
            uint8_t H_byte = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][5];
            stSystemInfo.stChargeInfo.stPowerMeterInfo.fCurrent = ((float) H_byte * 16777216 + (float) MH_byte * 65536 + (float) ML_byte * 256 + (float) L_byte) / 10000.0f*1.8;
        }break;
        case ePSC_Read_Power:{
            uint8_t L_byte = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][2];
            uint8_t ML_byte = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][3];
            uint8_t MH_byte = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][4];
            uint8_t H_byte = stUart4Data.u8UartBuf[stUart4Data.u8ROBufIdx][5];

            stSystemInfo.stChargeInfo.stPowerMeterInfo.fPower = ((float) H_byte * 16777.216 + (float) MH_byte * 65.536 + (float) ML_byte * 0.256 + (float) L_byte*0.001)*1.8;
        }break;
        default:{
            //unknown instruction response
        }break;
    }
    stPowerMeterTX.u8Status = idle;
    stPowerMeterInfo.u8Cmd_Type = ePSC_Null;
    stUart4Data.u8ROBufIdx = (stUart4Data.u8ROBufIdx + 1) % DEF_BUF_NUM;
}

void UART_sendMonitorData(unsigned int writebufferLen, unsigned char *pD)
{
    unsigned int numBytes = 0;
    while (numBytes < writebufferLen)
    {
        if (UART3_IsTxReady())
        {
            UART3_Write(*(pD + numBytes));
            numBytes++;
        }
    }
}
void UART_sendPowerMonitorUtilityData(unsigned int writebufferLen, unsigned char *pD)
{
    unsigned int numBytes = 0;
    while (numBytes < writebufferLen)
    {
        if (UART4_IsTxReady())
        {
            UART4_Write(*(pD + numBytes));
            numBytes++;
        }
    }
}

void UART_sendMonitorStr(char *pS)
{
    unsigned int writebufferLen = strlen((char *) pS);
    UART_sendMonitorData(writebufferLen, (unsigned char *) pS);
}
void UART_sendPowerMonitorUtilityStr(char *pS)
{
    unsigned int writebufferLen = strlen((char *) pS);
    UART_sendPowerMonitorUtilityData(writebufferLen, (unsigned char *) pS);
}
