

/**
 * main.c
 */
/** Infinite State machine external header files **/
#include "appctrlExt.h"
#include "modeWaitExt.h"
#include "modeOpenLoopExt.h"
#include "modeCloseLoopExt.h"
#include "modeComExt.h"

/** functions Drivers external files **/
#include "Drv_epmw_ext.h"
#include "Drv_adc_Ext.h"

#include "main.h"

SYSTEM_STATE_ENUM (* appCtrl_ptrInit) (void);
SYSTEM_STATE_ENUM (* appCtrl_ptrWait) (void);
SYSTEM_STATE_ENUM (* appCtrl_ptrCloseLoop) (void);
SYSTEM_STATE_ENUM (* appCtrl_ptrOpenLoop) (void);
SYSTEM_STATE_ENUM (* appCtrl_ptrCom) (void);


bool_t WaitInit;
bool_t OpenLoopInit;
bool_t CloseLoopInit;
bool_t ComInit;

void
main(void)
{

    /* System init PLL clock and pinout GPIO and ADC ... */
    vAppCtrl_Init();

    SYSTEM_STATE_ENUM NextState = APP_CTRL_MODE_WAIT_STATE;
    SYSTEM_EVENT_ENUM NewEvent  = APP_CTRL_MODE_WAIT_EVENT;

    /* Pointer to function submodules */
    appCtrl_ptrWait         = &eModeWait_Mng;
    appCtrl_ptrOpenLoop     = &eModeOpenLoop_Mng;
    appCtrl_ptrCloseLoop    = &eModeCloseLoop_Mng;
    appCtrl_ptrCom          = &eModeCom_Mng;

    WaitInit        = true;
    OpenLoopInit    = true;
    CloseLoopInit   = true;
    ComInit         = true;

    /* Start the while loop for motor control */

    while (1)
    {
        while (true == EpwmInterruptFlag)
        {
            /* Execute the while loop every epwm tick */
            EpwmInterruptFlag = false;

            /* Toggle the pin for pwm checking */
            GPIO_togglePin(0);

            /* Switch case for interrupt */
            switch (NextState)
            {
                /* Wait state */
                case APP_CTRL_MODE_WAIT_STATE:
                {
                    if (APP_CTRL_MODE_WAIT_EVENT == NewEvent)
                    {
                        NextState = (*appCtrl_ptrWait)();
                    }
                }
                break;

                /* Close loop State */
                case APP_CTRL_MODE_CLOSE_LOOP_STATE:
                {
                    if (APP_CTRL_MODE_CLOSE_LOOP_EVENT == NewEvent)
                    {
                        NextState = (*appCtrl_ptrCloseLoop)();
                    }
                }
                break;

                /* Open loop state */
                case APP_CTRL_MODE_OPEN_LOOP_STATE:
                {
                    if (APP_CTRL_MODE_OPEN_LOOP_EVENT == NewEvent)
                    {
                        NextState = (*appCtrl_ptrOpenLoop)();
                    }
                }
                break;

                /* Com state */
                case APP_CTRL_MODE_COM_STATE:
                {
                    if (APP_CTRL_MODE_COM_EVENT == NewEvent)
                    {
                        NextState = (*appCtrl_ptrCom)();
                    }
                }
                break;

                default:
                break;

            }
            // read event
            NewEvent = mode;
        }


    }
}

void
vAppCtrl_Init (void)
{


    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Assign the interrupt service routines to ePWM interrupts
    //
    Interrupt_register(INT_EPWM1, &vDrvepwm_Epwm1ISR);

    //
    // Configure GPIO0/1 , GPIO2/3 and GPIO4/5 as ePWM1A/1B, ePWM2A/2B and
    // ePWM3A/3B pins respectively
    //
    //GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    //GPIO_setPinConfig(GPIO_0_GPIO0);

    GPIO_setPadConfig(0, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO8
    GPIO_setPinConfig(GPIO_0_GPIO0);                // GPIO8 = GPIO8
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_OUT);    // GPIO8 = output

    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_EPWM1B);

    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_2_EPWM2A);
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_3_EPWM2B);

    GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_4_EPWM3A);
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_5_EPWM3B);

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    /* EPWM initialization and interrupt for SOC */
    vDrvepwm_InitEpwm1();

    /* ADC initialization, SOC and offset calibration */
    vDrvadc_InitAllAdc();
    vDrvadc_AdcSocCnfg();
    vDrvadc_SetupPPBOffset(60,60,60);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable ePWM interrupts
    //
    Interrupt_enable(INT_EPWM1);


    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;
}
void
vAppCtrl_Reset (void)
{

}
