/* 
 * File:   timer_api.h
 * Author: Hugo
 *
 * Created on July 16, 2024, 4:44 PM
 */

#ifndef TIMER_API_H
#define	TIMER_API_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define EMERGENCY_STOP_FLOW_TIME 500
#define GET_CHARGEING_CP_TIME 50
#define GET_CHARGEING_CP_COUNT 50
#define GET_CHARGEING_PMU_TIME 300
#define GET_CHARGEING_PMU_GET_DATA_COUNT 3
#define DESPLAY_CHARGEING_PANEL_INFO_TIME 100
#define DESPLAY_CHARGEING_PANEL_INFO_COUNT 3
#define CHARGEING_FINISH_FLOW_TIME 0

typedef enum
{
    ePGD_Voltage=0x00,
    ePGD_Current,
    ePGD_Power,
}enumPMU_Get_Data;

typedef enum
{
//    ePDD_Voltage=0x00,
//    ePDD_Current,
    ePDD_Power=0x00,
    ePDD_Hour,
    ePDD_Minute,
}enumPanel_Display_Data;

typedef struct
{
    uint16_t u16Emergency_Stop_Flow_Timer;
    uint16_t u16Chargeing_CP_Timer;
    uint16_t u16Chargeing_PMU_Timer;
    uint16_t u16Desplay_Charging_Panel_Info_Timer;
    uint16_t u16Charging_Finish_Flow_Timer;
}STRUCT_TIMER_TYPE;

typedef struct
{
    uint8_t u8PMU_Get_Data_Index;
    uint8_t u8ADC2_Get_Data_Index;
    uint8_t u8ADC2_Get_Data_Count;
    uint8_t u8Panel_Display_Chargeing_Info_Index;
}STRUCT_TIMER_GET_DATA_TYPE;

extern STRUCT_TIMER_TYPE stTimerInfo;
extern STRUCT_TIMER_GET_DATA_TYPE stTimerGetInfo;

void tickTimer1ms(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_API_H */

