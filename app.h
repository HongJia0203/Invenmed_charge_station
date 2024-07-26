/* 
 * File:   app.h
 * Author: Hugo
 *
 * Created on July 16, 2024, 3:22 PM
 */
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include <stdio.h>

#include "xc.h"
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/uart3.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/adc2.h"
#include "mcc_generated_files/tmr3.h"
#include "mcc_generated_files/watchdog.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/pwm.h"

#include "uart_api.h"
#include "timer_api.h"
#include "led_control.h"
#include "relay_control.h"
#include "engineer_mode.h"
#include "power_meter.h"
#include "function_api.h"

#ifndef APP_H
#define	APP_H

#ifdef	__cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------  version management information (only number)  -----------------------------------------------------------------------------------------------------------//    
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define VERSION_DATA 240723
#define VERSION_NUMBER 1
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------//    
    
#define RFID_ID_LENGTH 8 // 定義RFID ID的長度，8byte

#define PWM_DUTYCYCLE_7KW 0x5D9A
#define PWM_DUTYCYCLE_9KW 0x3BE8
#define PWM_DUTYCYCLE_12KW 0x1AF5

// 定義不同車輛連接狀態的ADC轉換電壓
#define CP_NO_VEHICLE(n)            (n >= 4020)
#define CP_VEHICLE_CONNECTED(n)    ((n >= 3703) && (n <= 3950))  //((n >= 3413) && (n <= 3755))
#define CP_READY(n)                ((n >= 3082) && (n <= 3496))  //((n >= 2901) && (n <= 3243))
#define CP_READY_VENTILATION(n)    ((n >= 2462) && (n <= 2875))
#define CP_DIODE_CHECK(n)           (n >= 171)
#define NUM_CP 4    
    
#define DEBUG_PRINTF_EN 1

    
#if(DEBUG_PRINTF_EN  == 1)
    #define   DebugAndRfid_Printf printf
#else
    #define   DebugAndRfid_Printf(...)
#endif
typedef enum
{
    eSF_Idel=0x00,
    eSF_Charge,
    eSF_EnginnerMode,
    eSF_Emergency,
    eSF_FactoryMode,     
}enumSystem_Flow;

typedef enum
{
    eESF_Idel=0x00,
    eESF_enterEmergency_Step,
    eESF_Finish,
}enumEmergency_Stop_Flow;

typedef enum
{
    eCCF_Idel=0x00,
    eCCF_enterChargeing_Checkouts_step,
    eCCF_Finish,
}enumChargeing_Checkouts_Flow;

typedef enum
{
    eCF_Idel=0x00,
    eCF_ConfirmVerification,
    eCF_selsectPowerLevel,
    eCF_startChargeing,
    eCF_Checkouts,
    eCF_Finish,
}enumChargeing_Flow;

typedef enum
{
    eCPL_7KW=0x00,
    eCPL_9KW,
    eCPL_12KW,
}enmCharge_Power_Level;

typedef enum
{
    eCCV_12V=0x00,
    eCCV_9V,
    eCCV_6V,
    eCCV_3V,
}enmCharge_CP_Value;

typedef struct
{
    uint8_t u8Chargeing_Checkouts_Flow;
    uint8_t u8Rev;
}STRUCT_SUB_FLOW;

typedef struct
{
    uint8_t u8Chrageing_Flow;
    uint8_t u8Rev;
    STRUCT_SUB_FLOW stSubFlow;
}STRUCT_CHARGEING_FLOW;

typedef struct
{
    uint8_t u8Emergency_Stop_Event;
    uint8_t u8Emergency_Stop_Flow;
}STRUCT_INTERRUPT_INFO_FLOW;

typedef struct
{
    float fVoltage;
    float fCurrent;
    float fPower;
    float fRev;
}STRUCT_POWER_METER_TYPE;
    
typedef struct
{
    uint8_t u8Power_Level;
    uint8_t u8CP_Pin_Present;
    uint8_t u8CP_Pin_Past;
    uint8_t Rev;
    int CPs[NUM_CP];
    uint32_t u32Charge_Time;
    uint8_t u8Charge_Minute;
    uint8_t u8Charge_Hour;
    STRUCT_POWER_METER_TYPE stPowerMeterInfo;
}STRUCT_CHARGE_TYPE;

typedef struct
{
    STRUCT_INTERRUPT_INFO_FLOW stInterruptInfo;
    STRUCT_CHARGEING_FLOW stChrage_Flow;
    STRUCT_CHARGE_TYPE stChargeInfo;
    uint8_t u8System_Flow;
    uint8_t u8Relay_state;
    char cRFID_ID_Number[RFID_ID_LENGTH + 1]; // 用於存儲RFID ID的陣列多一位用於終止'\0'
    uint8_t u8Rev;
}STRUCT_SYSTEM_TYPE;

extern STRUCT_SYSTEM_TYPE stSystemInfo;


extern void APP_interruptOccurredAtEX1(void);
extern void APP_runChargeFlow(void);
extern void APP_taskMainFlow(void);
extern void APP_taskUartFlow(void);
extern void APP_runPanelFlow(void);

extern void getCPPinValue(void);
extern void getPMUData(void);
extern void setPanelDisplay(void);
extern void switchCPpinState(void);
extern void setStartChargringInit(void);
extern void setChargingTimeInit(void);
#ifdef	__cplusplus
}
#endif

#endif	/* APP_H */

