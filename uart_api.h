/* 
 * File:   uart_api.h
 * Author: Hugo
 *
 * Created on July 16, 2024, 4:52 PM
 */

#ifndef UART_API_H
#define	UART_API_H

#ifdef	__cplusplus
extern "C" {
#endif

#define DEF_BUF_SIZE 256
#define DEF_BUF_NUM   4
#define TX_BUFFER_LENGTH 128
    
#define PANEL_BUF_HEAD 0x55
#define POWER_METER_ACK 0x06
#define POWER_METER_NACK 0x15
#define POWER_METER_CSFAIL 0x51
    
#define PANEL_DEVELOP_MODE 0x45
#define PANEL_PAGESTART_MODE 0x48
#define PANEL_PAGEVERIFY_MODE 0x05
#define PANEL_INFORMATION_MODE 0x53
#define PANEL_PAGECASE_MODE 0x11

#define PANEL_DEFAULT_OPTION 0x00
#define PANEL_DEVELOP_MODE_TEST_LED_OPTION 0x4C
#define PANEL_DEVELOP_MODE_TEST_METER_OPTION 0x4D  
#define PANEL_DEVELOP_MODE_TEST_RELAY_OPTION 0x52
#define PANEL_DEVELOP_MODE_TEST_GFCI_OPTION 0x47    
#define PANEL_DEVELOP_MODE_TEST_RFID_OPTION 0x49
#define PANEL_DEVELOP_MODE_TEST_PARAMETER_OPTION 0x50    
#define PANEL_PAGECASE_MODE_7KW_OPTION 0x07
#define PANEL_PAGECASE_MODE_9KW_OPTION 0x09
#define PANEL_PAGECASE_MODE_12KW_OPTION 0x12
    
typedef struct 
{
    uint8_t u8WIBufIdx;
    uint8_t u8ROBufIdx;
    uint8_t u8TargetBufLen;
    uint8_t u8InBufLen;
    uint8_t u8UartBuf[DEF_BUF_NUM][DEF_BUF_SIZE];
}UART_DATA_TYPE;

typedef struct
{
	uint8_t u8Buf[TX_BUFFER_LENGTH];
	
	uint8_t u8Tx_Delay;
	uint8_t u8Status;
	uint8_t u8Length;
	uint8_t u8Count;
}UART_TX_TYPE;

extern UART_DATA_TYPE stUart3Data,stUart4Data;
extern UART_TX_TYPE stPowerMeterTX;

extern void checkUartDataBuf(void);
extern void getByteUart3(unsigned char B);
extern void checkParserUart3(void);
extern void decodeUart3Data(void);
extern void getByteUart4(unsigned char B);
extern void checkParserUart4(void);
extern void decodeUart4Data(void);
extern void UART_sendMonitorData(unsigned int writebufferLen, unsigned char *pD);
extern void UART_sendPowerMonitorUtilityData(unsigned int writebufferLen, unsigned char *pD);
extern void UART_sendMonitorStr(char *pS);
extern void UART_sendPowerMonitorUtilityStr(char *pS);
#ifdef	__cplusplus
}
#endif

#endif	/* UART_API_H */

