/* 
 * File:   engineer_mode.h
 * Author: Hugo
 *
 * Created on July 17, 2024, 3:31 PM
 */

#ifndef ENGINEER_MODE_H
#define	ENGINEER_MODE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum
{
    eEMF_Idel=0x00,
    eEMF_testLed,
    eEMF_testRelayOn,
    eEMF_testRelayOff,
    eEMF_testGFCIOn,
    eEMF_testGFCIOff,
    eEMF_testRFID,
    eEMF_testReturn_verify,
    eEMF_testMeterValue,
    eEMF_testParameter,        
}enumEngineer_Mode_Flow;

typedef struct
{
    uint8_t u8Engineer_Mode_Flow;
    uint8_t u8Rev;
}STRUCT_ENGINEER_MODE_TYPE;

extern STRUCT_ENGINEER_MODE_TYPE stEngineerModeInfo;

extern void ENGINEERMODE_testLed(void);
extern void ENGINEERMODE_testRelay(uint8_t u8switch);
extern void ENGINEERMODE_testGFCI(uint8_t u8switch);
extern void ENGINEERMODE_testRFID(void);
extern void ENGINEERMODE_testReturnVerify(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ENGINEER_MODE_H */

