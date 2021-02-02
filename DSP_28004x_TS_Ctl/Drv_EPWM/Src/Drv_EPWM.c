/**CFile***********************************************************************
  FileName    [ required ]
  PackageName [ required ]
  Synopsis    [ required ]
  Description [ optional ]
  SeeAlso     [ optional ]
  Author      [ optional ]
  Copyright   [ required ]
******************************************************************************/

#include "driverlib.h"
#include "device.h"
#include "Drv_EPWM.h"
#include "epwm.h"

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/
typedef struct
{
    uint32_t epwmModule;
    uint16_t epwmCompADirection;
    uint16_t epwmCompBDirection;
    uint16_t epwmTimerIntCount;
    uint16_t epwmMaxCompA;
    uint16_t epwmMinCompA;
    uint16_t epwmMaxCompB;
    uint16_t epwmMinCompB;
}epwmInformation;
//
// Defines
//
#define RESULTS_BUFFER_SIZE     256
bool EpwmInterruptFlag = false;
//
// Globals
//
uint16_t adcAResults[RESULTS_BUFFER_SIZE];   // Buffer for results
uint16_t index;                              // Index into result buffer
volatile uint16_t bufferFull;                // Flag to indicate buffer is full
//
// Globals to hold the ePWM information used in this example
//
epwmInformation epwm1Info;
uint32_t IsrTicker = 0;
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
// vDrvepwm_InitEpwm1 - Function to configure ePWM1 to generate the SOC.
//
void
vDrvepwm_InitEpwm1 (void)
{
    //
    // Enable SOCA
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    //
    // Configure the SOC to occur on the first up-count event
    //
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //
    // Set the compare A value to 2048 and the period to 4096
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 200);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 416);

    //
    // Counter up and down
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);

    //
    // Interrupt where we will change the Compare Values
    // Select INT on Time base counter zero event,
    // Enable INT, generate INT on 1rs event
    //
    EPWM_setInterruptSource(EPWM1_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(EPWM1_BASE);
    EPWM_setInterruptEventCount(EPWM1_BASE, 1U);
}
//
// vDrvepwm_Epwm1ISR - ePWM 1 ISR
//
__interrupt void
vDrvepwm_Epwm1ISR (void)
{

    /* Verifying the ISR */
    IsrTicker++;

    /* The signal period for while loop and states */
    EpwmInterruptFlag = true;

    /* Clear INT flag for this timer */
    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);

    /* Acknowledge interrupt group */
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}
