#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"

// 定義數據接收陣列
uint8_t Panel_Start_Data[10]; 
size_t Panel_Start_Data_arraySize = 0; 

int main(void) {
    SYSTEM_Initialize();
    WATCHDOG_TimerSoftwareEnable();
    DELAY_milliseconds(50); 
    PWM_Enable(); 
    
    LED_setSystemOpenLight(); 

    while (1) {
        APP_taskUartFlow();
        APP_taskMainFlow();
        
        WATCHDOG_TimerClear();
    }
    return 1;
}
