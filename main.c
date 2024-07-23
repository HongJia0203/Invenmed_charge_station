#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"

int main(void) {
    SYSTEM_Initialize();
    WATCHDOG_TimerSoftwareEnable();
    DELAY_milliseconds(50); 
    PWM_Enable(); 
    
    LED_setSystemOpenLight(); 
    
    DebugAndRfid_Printf("\n\r\n\rVersion_Date:%d\n\r",VERSION_DATA);
	DebugAndRfid_Printf("Version_Number:%d\n\r",VERSION_NUMBER);
    
    while (1) {
        APP_taskUartFlow();
        APP_taskMainFlow();
        
        WATCHDOG_TimerClear();
    }
    return 1;
}
