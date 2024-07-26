/* 
 * File:   power_meter.h
 * Author: Hugo
 *
 * Created on July 23, 2024, 9:59 AM
 */

#ifndef POWER_METER_H
#define	POWER_METER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define POWER_METER_TX_RETRY_TIME 50
#define POWER_METER_TX_RETRY_COUNT 3
    
typedef enum
{
	powerOFF=0,
	powerON,
	enable=10,
	disenable,
	put=20,
	push,
	keep_push,
	idle=30,
	busy,
}enumStatusType;
    
typedef enum
{
    ePSC_Power_Enable=0x00,
    ePSC_Power_Disable,
    ePSC_Read_Voltage,
    ePSC_Read_Current,
    ePSC_Read_Power,            
    ePSC_Null=0xFF,
}enumPUMSendCmd;

typedef struct 
{
    uint8_t u8Power_Enable;
    uint8_t u8Power_Disable;
    uint8_t u8Read_Voltage;
    uint8_t u8Read_Current;
    uint8_t u8Read_Power;
}STRUCT_POWERMETER_CMD_TYPE;

typedef struct 
{
    STRUCT_POWERMETER_CMD_TYPE stPowerMeterCmd;
    uint8_t u8Cmd_Type;
    uint8_t u8Rev;
}STRUCT_POWERMETER_INFO_TYPE;

extern STRUCT_POWERMETER_INFO_TYPE stPowerMeterInfo;

extern void sendPowerMonitorUtilityData(uint8_t cmd);
extern void actionPowerMonitorUtility(void);
extern void processPowerMeterCmd(void);

#ifdef	__cplusplus
}
#endif

#endif	/* POWER_METER_H */

