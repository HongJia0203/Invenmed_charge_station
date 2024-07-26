#include "app.h"

STRUCT_ENGINEER_MODE_TYPE stEngineerModeInfo;

/*********************************************************************
 * Function:        void ENGINEERMODE_testLed(void)
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
void ENGINEERMODE_testLed(void) {
    LED_Test(); // 執行LED測試
    DebugAndRfid_Printf("LED OVER\r\n");
    LED_setSystemOpenLight(); // 開啟系統
}

/*********************************************************************
 * Function:        void ENGINEERMODE_testRelay(uint8_t u8state)
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
void ENGINEERMODE_testRelay(uint8_t u8switch) {
    if(u8switch){
        RELAY_setOnTest(); // 執行繼電器開啟測試
        DebugAndRfid_Printf("RelayOnTest OVER\r\n");
    }
    else{
        RELAY_setOffTest(); // 執行繼電器關閉測試
        DebugAndRfid_Printf("RelayoffTest OVER\r\n");
    }
}

/*********************************************************************
 * Function:        void ENGINEERMODE_testGFCI(uint8_t u8switch)
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
void ENGINEERMODE_testGFCI(uint8_t u8switch) {
    if(u8switch){
        GFCI_TEST_SetHigh(); // 開啟GFCI
        DebugAndRfid_Printf("GFCI On OVER\r\n");
    }
    else{
        GFCI_TEST_SetLow(); // 關閉GFCI
        DebugAndRfid_Printf("GFCI off Test OVER\r\n");
    }
}

/*********************************************************************
 * Function:        void ENGINEERMODE_testRFID(void)
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
void ENGINEERMODE_testRFID(void) {
    char rfid_number[9]; 
    memcpy(rfid_number,&stSystemInfo.cRFID_ID_Number,9);
    sendStringtoPenal(rfid_number);
}

/*********************************************************************
 * Function:        void ENGINEERMODE_testReturnVerify(void)
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
void ENGINEERMODE_testReturnVerify(void) {
    
}
