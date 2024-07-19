/**
  ADC2 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    adc2.h

  @Summary
    This is the generated header file for the ADC2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for ADC2.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  dsPIC33EP128GM604
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _ADC2_H
#define _ADC2_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Data Types
*/

/** Scan Selected Macro Definition
 
 @Summary 
   Defines the scan option selection done for the shared channels.
 
 @Description
   This macro defines the scan option selection done for the shared channels.
 
 Remarks:
   None
 */
#define ADC2_SCAN_MODE_SELECTED true

/** ADC2 Channel Definition
 
 @Summary 
   Defines the channels selected.
 
 @Description
   This routine defines the channels that are available for the module to use.
 
 Remarks:
   None
 */
typedef enum 
{
    CP_ADC2,//Channel Name:AN1   Assigned to:Shared Channel
    PP_ADC,//Channel Name:AN2   Assigned to:Shared Channel
    CP_ADC,//Channel Name:AN3   Assigned to:Shared Channel
} ADC2_CHANNEL;

/**
  Section: Interface Routines
*/

/**
  @Summary
    Initializes ADC2 module.

  @Description
    This routine initializes ADC2 module, using the given initialization data. 
    This routine must be called before any other ADC routine is called. 

  @Preconditions
    None.

  @Param
    None.

  @Returns
    None

  @Example
    <code>
        int conversion,i=0;
        ADC2_Initialize();

        ADC2_Enable();
        ADC2_ChannelSelect(channel);
        ADC2_SoftwareTriggerEnable();
        //Provide Delay
        for(i=0;i <1000;i++)
        {
        }
        ADC2_SoftwareTriggerDisable();
        while(!ADC2_IsConversionComplete(channel));
        conversion = ADC2_ConversionResultGet(channel);
        ADC2_Disable(); 
    </code>
*/
void ADC2_Initialize (void);

/**
  @Summary
    Enables the ADC2 module.

  @Description
    This routine is used to enable the ADC2 module.
 
  @Preconditions
    ADC2_Initialize function should have been called 
    before calling this function.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
        int conversion,i=0;
        ADC2_Initialize();

        ADC2_Enable();
        ADC2_ChannelSelect(channel);
        ADC2_SoftwareTriggerEnable();
        //Provide Delay
        for(i=0;i <1000;i++)
        {
        }
        ADC2_SoftwareTriggerDisable();
        while(!ADC2_IsConversionComplete(channel));
        conversion = ADC2_ConversionResultGet(channel);
        ADC2_Disable(); 
    </code>
*/
inline static void ADC2_Enable(void)
{
   AD2CON1bits.ADON = 1;
}

/**
  @Summary
    Disables the ADC2 module.

  @Description
    This routine is used to disable the ADC2 module.
 
  @Preconditions
    ADC2_Initialize function should have been called 
    before calling this function.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
        int conversion,i=0;
        ADC2_Initialize();

        ADC2_Enable();
        ADC2_ChannelSelect(channel);
        ADC2_SoftwareTriggerEnable();
        //Provide Delay
        for(i=0;i <1000;i++)
        {
        }
        ADC2_SoftwareTriggerDisable();
        while(!ADC2_IsConversionComplete(channel));
        conversion = ADC2_ConversionResultGet(channel);
        ADC2_Disable(); 
    </code>
*/
inline static void ADC2_Disable(void)
{
   AD2CON1bits.ADON = 0;
}

/**
  @Summary
    Starts sampling manually.

  @Description
    This routine is used to start sampling manually.
 
  @Preconditions
    ADC2_Initialize function should have been called 
    before calling this function.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
        int conversion,i=0;
        ADC2_Initialize();

        ADC2_Enable();
        ADC2_ChannelSelect(channel);
        ADC2_SoftwareTriggerEnable();
        //Provide Delay
        for(i=0;i <1000;i++)
        {
        }
        ADC2_SoftwareTriggerDisable();
        while(!ADC2_IsConversionComplete(channel));
        conversion = ADC2_ConversionResultGet(channel);
        ADC2_Disable(); 
    </code>
*/
inline static void ADC2_SoftwareTriggerEnable(void)
{
   AD2CON1bits.SAMP = 1;
}

/**
  @Summary
    Stops sampling manually.

  @Description
    This routine is used to stop the sampling manually.
 
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
        int conversion,i=0;
        ADC2_Initialize();

        ADC2_Enable();
        ADC2_ChannelSelect(channel);
        ADC2_SoftwareTriggerEnable();
        //Provide Delay
        for(i=0;i <1000;i++)
        {
        }
        ADC2_SoftwareTriggerDisable();
        while(!ADC2_IsConversionComplete(channel));
        conversion = ADC2_ConversionResultGet(channel);
        ADC2_Disable(); 
    </code>
*/
inline static void ADC2_SoftwareTriggerDisable(void)
{
   AD2CON1bits.SAMP = 0;
}

/**
  @Summary
    Allows selection of a channel for conversion.

  @Description
    This routine is used to select desired channel for conversion.
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.

  @Param
    channel - Channel for conversion

  @Returns
    None
  
  @Example
    <code>
        int conversion,i=0;
        ADC2_Initialize();

        ADC2_Enable();
        ADC2_ChannelSelect(channel);
        ADC2_SoftwareTriggerEnable();
        //Provide Delay
        for(i=0;i <1000;i++)
        {
        }
        ADC2_SoftwareTriggerDisable();
        while(!ADC2_IsConversionComplete(channel));
        conversion = ADC2_ConversionResultGet(channel);
        ADC2_Disable(); 
    </code>
*/
inline static void ADC2_ChannelSelect( ADC2_CHANNEL channel )
{
    /*This routine does not have any implementation since 
            *Shared channels are put to scan.
            *Dedicated channels are selected from UI.
     */
}

/**
  @Summary
    Returns the conversion value for the channel selected.

  @Description
    This routine is used to get the analog to digital converted value for a 
    specific channel.
 
  @Preconditions
    This routine returns the conversion value only after the conversion is complete. 
    Conversion completion status can be checked using ADC2_IsConversionComplete(channel)
    routine.

  @Param
    channel - Selected channel
   
  @Returns
   Returns the analog to digital converted value
  
  @Example
    <code>
        int conversion,i=0;
        ADC2_Initialize();

        ADC2_Enable();
        ADC2_ChannelSelect(channel);
        ADC2_SoftwareTriggerEnable();
        //Provide Delay
        for(i=0;i <1000;i++)
        {
        }
        ADC2_SoftwareTriggerDisable();
        while(!ADC2_IsConversionComplete(channel));
        conversion = ADC2_ConversionResultGet(channel);
        ADC2_Disable(); 
    </code>
 */
inline static uint16_t ADC2_ConversionResultGet( ADC2_CHANNEL channel )
{
    uint16_t result;

    switch(channel)
    {
        case CP_ADC2:
                result = ADC2BUF0;
                break;
        case PP_ADC:
                result = ADC2BUF1;
                break;
        case CP_ADC:
                result = ADC2BUF2;
                break;
        default:
                break;
    }

    return result;
}

/**
  @Summary
    Returns the status of conversion.

  @Description
    This routine is used to determine if conversion is completed. When conversion
    is complete the routine returns true otherwise false.
 
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.

  @Param
    channel - Selected channel
 
  @Returns
    true - Conversion is complete.
    false - Conversion is not complete.
  
  @Example
    <code>
        int conversion,i=0;
        ADC2_Initialize();

        ADC2_Enable();
        ADC2_ChannelSelect(channel);
        ADC2_SoftwareTriggerEnable();
        //Provide Delay
        for(i=0;i <1000;i++)
        {
        }
        ADC2_SoftwareTriggerDisable();
        while(!ADC2_IsConversionComplete(channel));
        conversion = ADC2_ConversionResultGet(channel);
        ADC2_Disable(); 
    </code>
 */
inline static bool ADC2_IsConversionComplete(ADC2_CHANNEL channel)
{
    bool status;

    status = AD2CON1bits.DONE;

    return status;
}

/**
  @Summary
    Enables interrupts.

  @Description
    This routine is used to enable the ADC2 interrupt.
 
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
        ADC2_InterruptEnable(); 
    </code>
*/
inline static void ADC2_InterruptEnable(void)
{
    IEC1bits.AD2IE = 1;
}

/**
  @Summary
    Disables interrupts.

  @Description
    This routine is used to disable the ADC2 interrupt.
 
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
        ADC2_InterruptDisable(); 
    </code>
*/
inline static void ADC2_InterruptDisable(void)
{
    IEC1bits.AD2IE = 0;
}

/**
  @Summary
    Clears interrupt flag

  @Description
    This routine is used to clear the interrupt flag manually.
 
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
        ADC2_InterruptFlagClear(); 
    </code>
*/
inline static void ADC2_InterruptFlagClear(void)
{
    IFS1bits.AD2IF = 0;
}

/**
  @Summary
    Allows selection of priority for interrupt.

  @Description
    This routine is used to select desired priority for interrupt.
  
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
        uint16_t priorityValue;
        priorityValue = 0x002;
 
        ADC2_InterruptPrioritySet(priorityValue); 
    </code>
*/
inline static void ADC2_InterruptPrioritySet( uint16_t priorityValue )
{
    IPC5bits.AD2IP = 0x7 & priorityValue;
}

/**
  @Summary
    Callback for ADC2.

  @Description
    This routine is callback for ADC2
  
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>    
        ADC2_CallBack();
    </code>
*/
void ADC2_CallBack(void);

/**
  @Summary
    Assigns a function pointer with a callback address.

  @Description
    This routine assigns a function pointer with a callback address.
  
  @Preconditions
    None.

  @Param
    Address of the callback routine.

  @Returns
    None
 
  @Example 
    <code>
        ADC2_SetInterruptHandler(&ADC2_CallBack);
    </code>
*/
void ADC2_SetInterruptHandler(void* handler);


/*******************************************************************************

  !!! Deprecated Definitions and APIs !!!
  !!! These functions will not be supported in future releases !!!

*******************************************************************************/
/** ADC Positive 123 Channels Definition
 
 @Summary 
   Defines the positive 123 channels available for conversion
 
 @Description
   This routine defines the positive 123 channels that are available for the 
   module to use.
 
 Remarks:
   None
 */
typedef enum 
{
    ADC2_POS_123_CHANNEL_0 = 0x0,
    ADC2_POS_123_CHANNEL_1 = 0x1,   
    ADC2_POS_123_CHANNEL_2 = 0x8,
    ADC2_POS_123_CHANNEL_3 = 0x9,
    ADC2_POS_123_CHANNEL_4 = 0x10
} ADC2_POS_123_CHANNEL;

/** ADC Negative 123 Channels Definition
 
 @Summary 
   Defines the negative 123 channels available for conversion
 
 @Description
   This routine defines the negative 123 channels that are available for the 
   module to use.
 
 Remarks:
   None
 */
typedef enum 
{
   ADC2_NEG_123_CHANNEL_0 = 0x0,
   ADC2_NEG_123_CHANNEL_1 = 0x2,
   ADC2_NEG_123_CHANNEL_2 = 0x3
} ADC2_NEG_123_CHANNEL;

/** ADC Data Format Type Definition
 
 @Summary 
   Defines the data format types available
 
 @Description
   This routine defines the data format types that are available for the module 
   to use.
 
 Remarks:
   None
 */
typedef enum 
{
    ADC2_FORM_UNSIGNED_INT   = 0, /* Unsigned Integer */
    ADC2_FORM_SIGNED_INT     = 1, /* Signed Integer */
    ADC2_FORM_UNSIGNED_FRACT = 2, /* Unsigned Fraction */
    ADC2_FORM_SIGNED_FRACT   = 3  /* Signed Integer */
} ADC2_FORM_TYPE;

/** ADC Resolution Type Definition
 
 @Summary 
   Defines the resolution types available
 
 @Description
   This routine defines the resolution types that are available for the module 
   to use.
 
 Remarks:
   None
 */
typedef enum 
{
    ADC2_RESOLUTION_10_BIT   = 0, /* 10-bit, 4-channel ADC operation */
    ADC2_RESOLUTION_12_BIT   = 1  /* 12-bit, 1-channel ADC operation */
} ADC2_RESOLUTION_TYPE;

/** ADC Sampling Source Definition
 
 @Summary 
   Defines the sampling sources available
 
 @Description
   This routine defines the sampling sources that are available for the module 
   to use.
 
 Remarks:
   None
 */
typedef enum 
{
    ADC2_SAMPLING_SOURCE_MANUAL  =  0x0,
    ADC2_SAMPLING_SOURCE_PWM2  =  0x1,
    ADC2_SAMPLING_SOURCE_PWM_PRIMARY  =  0x3,
    ADC2_SAMPLING_SOURCE_INT0  =  0x1,
    ADC2_SAMPLING_SOURCE_AUTO  =  0x7,
    ADC2_SAMPLING_SOURCE_PWM1  =  0x0,
    ADC2_SAMPLING_SOURCE_PTGO12  =  0x3,
    ADC2_SAMPLING_SOURCE_PTGO14  =  0x5,
    ADC2_SAMPLING_SOURCE_TMR3  =  0x2,
    ADC2_SAMPLING_SOURCE_PWM3  =  0x2,
    ADC2_SAMPLING_SOURCE_PTGO13  =  0x4,
    ADC2_SAMPLING_SOURCE_PTGO15  =  0x6,
    ADC2_SAMPLING_SOURCE_CTMU  =  0x6,
    ADC2_SAMPLING_SOURCE_TMR5  =  0x4,
} ADC2_SAMPLING_SOURCE;

/** ADC Conversion Channel Type Definition
 
 @Summary 
   Defines the conversion channel types available
 
 @Description
   This routine defines the conversion channels types that are available for the 
   module to use.
 
 Remarks:
   None
 */
typedef enum 
{
    ADC2_CONVERSION_CHANNELS_CH0    = 0, /* Converts only CH0 */
    ADC2_CONVERSION_CHANNELS_CH01   = 1, /* Converts CH0 and CH1 */
    ADC2_CONVERSION_CHANNELS_CH0123 = 2  /* Converts CH0, CH1, CH2 and CH3 */
} ADC2_CONVERSION_CHANNELS_TYPE;

/**
  @Summary
    Starts sampling manually.

  @Description
    This routine is used to start the sampling manually.
 
  @Preconditions
    ADC2_Initialize() function should have been called 
    before calling this function.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
        int conversion;
        ADC2__Initialize();
        ADC2_ChannelSelect(AN1_Channel);
        ADC2_SamplingStart();
        //Provide Delay
        for(int i=0;i <1000;i++)
        {
        }
        ADC2_SamplingStop();
        while(!ADC2_IsConversionComplete())
        {
            ADC2_Tasks();   
        }
        conversion = ADC2_ConversionResultGet();
    </code>

*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse ADC2_SoftwareTriggerEnable instead."))) ADC2_SamplingStart(void)
{
   AD2CON1bits.SAMP = 1;
}

/**
  @Summary
    Stops sampling manually.

  @Description
    This routine is used to stop the sampling manually before conversion
    is triggered.
 
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
        int conversion;
        ADC2__Initialize();
        ADC2_ChannelSelect(AN1_Channel);
        ADC2_SamplingStart();
        //Provide Delay
        for(int i=0;i <1000;i++)
        {
        }
        ADC2_SamplingStop();
        while(!ADC2_IsConversionComplete())
        {
            ADC2_Tasks();   
        }
        conversion = ADC2_ConversionResultGet();
    </code>
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse ADC2_SoftwareTriggerDisable instead."))) ADC2_SamplingStop(void)
{
   AD2CON1bits.SAMP = 0;
}

/**
  @Summary
    Gets the buffer loaded with conversion results.

  @Description
    This routine is used to get the analog to digital converted values in a
    buffer. This routine gets converted values from multiple channels.
 
  @Preconditions
    This routine returns the buffer containing the conversion values only after 
    the conversion is complete. Completion status conversion can be checked using 
    ADC2_IsConversionComplete() routine.
 
  @Param
    None.

  @Returns
    Returns the count of the buffer containing the conversion values.

  @Example
    <code>
        int count;
        //Initialize for channel scanning
        ADC2_Initialize();
        ADC2_SamplingStart();
        //Provide Delay
        for(int i=0;i <1000;i++)
        {
        }
        ADC2_SamplingStop();
        while(!ADC2_IsConversionComplete())
        {
            count = ADC2_ConversionResultBufferGet();
        }
    </code>
*/
uint16_t __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_ConversionResultBufferGet(uint16_t *buffer);

/**
  @Summary
    Returns the ADC2 conversion value for Channel 0.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.
 
  @Preconditions
    The channel required must be selected before calling this routine using
    ADC2_ChannelSelect(channel). This routine returns the 
    conversion value only after the conversion is complete. Completion status 
    conversion can be checked using ADC2_IsConversionComplete()
    routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC2_Initialize(); for an example
 */
inline static uint16_t __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_Channel0ConversionResultGet(void) 
{
    return ADC2BUF0;
}

/**
  @Summary
    Returns the ADC2 conversion value from Channel 1.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.
 
  @Preconditions
    The channel required must be selected before calling this routine using
    ADC2_ChannelSelect(channel). This routine returns the 
    conversion value only after the conversion is complete. Completion status 
    conversion can be checked using ADC2_IsConversionComplete()
    routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC2_Initialize(); for an example
 */
inline static uint16_t __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_Channel1ConversionResultGet(void) 
{
    return ADC2BUF1;
}

/**
  @Summary
    Returns the ADC2 conversion value from Channel 2.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.
 
  @Preconditions
    The channel required must be selected before calling this routine using
    ADC2_ChannelSelect(channel). This routine returns the 
    conversion value only after the conversion is complete. Completion status 
    conversion can be checked using ADC2_IsConversionComplete()
    routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC2_Initialize(); for an example
 */
inline static uint16_t __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_Channel2ConversionResultGet(void) 
{
    return ADC2BUF2;
}

/**
  @Summary
    Returns the ADC2 conversion value from Channel 3.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.
 
  @Preconditions
    The channel required must be selected before calling this routine using
    ADC2_ChannelSelect(channel). This routine returns the 
    conversion value only after the conversion is complete. Completion status 
    conversion can be checked using ADC2_IsConversionComplete()
    routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC2_Initialize(); for an example
 */
inline static uint16_t __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_Channel3ConversionResultGet(void) 
{
    return ADC2BUF3;
}

/**
  @Summary
    Allows selection of a channel for conversion

  @Description
    This routine is used to select desired channel for conversion.
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required channel from the ADC2_CHANNEL list
  
  @Example
    Refer to ADC2_Initialize(); for an example
 
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_ChannelSelectSet( ADC2_CHANNEL channel )
{
    AD2CHS0bits.CH0SA = channel;
}

/**
  @Summary
    Returns the channel selected for conversion

  @Description
    This routine is used to return the channel selected for conversion.
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    The value of the Channel Conversion register

  @Param
    None
  
  @Example
    Refer to ADC2_Initialize(); for an example
 
*/
inline static uint16_t __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_ChannelSelectGet( void )
{
    return AD2CHS0bits.CH0SA ;
}

/**
  @Summary
    Allows selection of a data format type for conversion

  @Description
    This routine is used to select desired data format for conversion.
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required data format type from the ADC2_FORM_TYPE list
  
  @Example
    Refer to ADC2_Initialize(); for an example
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_FormatDataSet( ADC2_FORM_TYPE form )
{
    AD2CON1bits.FORM = form;
}

/**
  @Summary
    Allows selection of a resolution mode for conversion

  @Description
    This routine is used to select desired resolution mode for conversion.
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required resolution mode from the ADC2_RESOLUTION_TYPE list
  
  @Example
    Refer to ADC2_Initialize(); for an example
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_ResolutionModeSet( ADC2_RESOLUTION_TYPE resolution )
{
    AD2CON1bits.AD12B = resolution;
}

/**
  @Summary
    Allows simultaneous sampling to be enabled manually

  @Description
    This routine is used to enable simultaneous sampling of channels manually
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None.
  
  @Example
    Refer to ADC2_Initialize(); for an example

*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_SimultaneousSamplingEnable(void)
{
    AD2CON1bits.SIMSAM = 1;
}

/**
  @Summary
    Allows simultaneous sampling to be disabled manually

  @Description
    This routine is used to disable simultaneous sampling of channels manually
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None.
  
  @Example
    Refer to ADC2_Initialize(); for an example
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_SimultaneousSamplingDisble(void)
{
    AD2CON1bits.SIMSAM = 0;
}

/**
@Summary
    Allows sutomatic sampling to be enabled manually

  @Description
    This routine is used to enable automatic sampling of channels manually
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None.
  
  @Example
    Refer to ADC2_Initialize(); for an example
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_AutomaticSamplingEnable(void)
{
    AD2CON1bits.ASAM = 1;
}

/**
  @Summary
    Allows automatic sampling to be disabled manually

  @Description
    This routine is used to disable automatic sampling of channels manually
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None.
  
  @Example
    Refer to ADC2_Initialize(); for an example
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_AutomaticSamplingDisable(void)
{
    AD2CON1bits.ASAM = 0;
}

/**
  @Summary
    Allows conversion clock prescaler value to be set

  @Description
    This routine is used to allow conversion clock prescaler value to be set manually
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required prescaler integer value
  
  @Example
    Refer to ADC2_Initialize(); for an example
 
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_ConversionClockPrescalerSet(uint8_t prescaler)
{
    AD2CON3bits.ADCS = prescaler - 1;
}

/**
  @Summary
    Allows selection of a positive 123 channel for conversion

  @Description
    This routine is used to select desired positive 123 channel for conversion.
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required channel from the ADC2_POS_123_CHANNEL list
  
  @Example
    Refer to ADC2_Initialize(); for an example
 
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_Positive123ChannelSelect( ADC2_POS_123_CHANNEL channel )
{
    AD2CHS123 = (AD2CHS123 & 0xFF06) | channel;
}

/**
  @Summary
    Allows selection of a negative 123 channel for conversion

  @Description
    This routine is used to select desired negative 123 channel for conversion.
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required channel from the ADC2_NEG_123_CHANNEL list
  
  @Example
    Refer to ADC2_Initialize(); for an example
 
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_Negative123ChannelSelect( ADC2_NEG_123_CHANNEL channel )
{
    AD2CHS123bits.CH123NA = channel;
}

/**
  @Summary
    Allows selection of conversion channels

  @Description
    This routine is used to select conversion channel for conversion.
  
  @Preconditions
    ADC2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required channel from the ADC2_CONVERSION_CHANNELS_TYPE list
  
  @Example
    Refer to ADC2_Initialize(); for an example
 
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases."))) ADC2_ConversionChannelsSet( ADC2_CONVERSION_CHANNELS_TYPE channel )
{
    AD2CON2bits.CHPS = channel;
}

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_ADC2_H
    
/**
 End of File
*/
