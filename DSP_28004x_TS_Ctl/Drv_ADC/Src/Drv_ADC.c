/**CFile***********************************************************************
  FileName    [ required ]
  PackageName [ required ]
  Synopsis    [ required ]
  Description [ optional ]
  SeeAlso     [ optional ]
  Author      [ optional ]
  Copyright   [ required ]
******************************************************************************/

//https://ptolemy.berkeley.edu/projects/embedded/research/vis/doc/VisEngineering/vis_eng/node3.html
//https://ptolemy.berkeley.edu/projects/embedded/research/vis/doc/VisEngineering/vis_eng/node1.html

#include "driverlib.h"
#include "device.h"
#include "F28x_Project.h"
#include "Drv_ADC.h"
#include "adc.h"
/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/**AutomaticStart*************************************************************/

/**AutomaticEnd***************************************************************/

/*---------------------------------------------------------------------------*/
/* Definition of exported functions                                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Definition of internal functions                                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/


//
// vDrvadc_InitAllAdc - Function to configure and power up ADCA.
//
void
vDrvadc_InitAllAdc (void)
{

    /* Setup VREF as internal */
    ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
    ADC_setVREF(ADCB_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
    ADC_setVREF(ADCC_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);

    /* Set ADCCLK divider to /4 */
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);
    ADC_setPrescaler(ADCB_BASE, ADC_CLK_DIV_4_0);
    ADC_setPrescaler(ADCC_BASE, ADC_CLK_DIV_4_0);


    /* Set pulse positions to late */
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);
    ADC_setInterruptPulseMode(ADCB_BASE, ADC_PULSE_END_OF_CONV);
    ADC_setInterruptPulseMode(ADCC_BASE, ADC_PULSE_END_OF_CONV);

    /* Power up the ADC and then delay for 1 ms */
    ADC_enableConverter(ADCA_BASE);
    ADC_enableConverter(ADCB_BASE);
    ADC_enableConverter(ADCC_BASE);

    /* Wait 1ms */
    DEVICE_DELAY_US(1000);
}


//
// vDrvadc_AdcSocCnfg - Function to configure ADCA's SOC0 to be triggered by ePWM1.
//
void
vDrvadc_AdcSocCnfg (void)
{
    //
    // Configure SOC0 of ADCA, B and C to convert pin A5, B0 and C2 with a sample window of 10
    // SYSCLK cycles. The EPWM1SOCA signal will be the trigger.
    //
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN5, 10);
    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN0, 10);
    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN2, 10);

    //
    // Set SOC0 to set the interrupt 1 flag. Enable the interrupt and make
    // sure its flag is cleared.
    //
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCB_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCC_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);

    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCB_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCC_BASE, ADC_INT_NUMBER1);

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER1);
}

void
vDrvadc_FirstAquisitionEnding (void)
{
    /* Wait for first measurements */
    while(!ADC_getInterruptStatus (ADCA_BASE, ADC_INT_NUMBER1));

    /* Clear interruption flag */
    ADC_clearInterruptOverflowStatus (ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus (ADCA_BASE, ADC_INT_NUMBER1);


}

void
vDrvadc_SecondAquisitionEnding (void)
{
    /* Wait for secondary measurements */
    while(1);
}
//
// SetupPPBOffset - Configure PPB for SOC
//
void
vDrvadc_SetupPPBOffset(int16 aOffset, int16 bOffset, int16 cOffset)
{

    /*
     * PPB1 is associated with SOC1
     * PPB1 will subtract OFFCAL value
     * to associated SOC
     * */
    ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setPPBCalibrationOffset(ADCA_BASE,ADC_PPB_NUMBER1 , aOffset);

    /*PPB1 is associated with SOC1
     *PPB1 will subtract OFFCAL value
     *to associated SOC
     * */
    ADC_setupPPB(ADCB_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setPPBCalibrationOffset(ADCB_BASE,ADC_PPB_NUMBER1 , bOffset);

    /*PPB1 is associated with SOC1
     *PPB1 will subtract OFFCAL value
     *to associated SOC
     * */
    ADC_setupPPB(ADCC_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setPPBCalibrationOffset(ADCC_BASE,ADC_PPB_NUMBER1 , cOffset);

}
