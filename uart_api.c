#include "app.h"

UART_DATA_TYPE stUart3Data,stUart4Data ={0};

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
                    uint8_t parameter;
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
                    uint8_t parameter;
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
                    stSystemInfo.u8Chrageing_Flow = eCF_selsectPowerLevel;
                    stSystemInfo.stChargeInfo.u8Power_Level = eCPL_7KW;
                    
                }
                case PANEL_PAGECASE_MODE_9KW_OPTION:{
                    stSystemInfo.u8System_Flow = eSF_Charge;
                    stSystemInfo.u8Chrageing_Flow = eCF_selsectPowerLevel;
                    stSystemInfo.stChargeInfo.u8Power_Level = eCPL_9KW;
                }
                case PANEL_PAGECASE_MODE_12KW_OPTION:{
                    stSystemInfo.u8System_Flow = eSF_Charge;
                    stSystemInfo.u8Chrageing_Flow = eCF_selsectPowerLevel;
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