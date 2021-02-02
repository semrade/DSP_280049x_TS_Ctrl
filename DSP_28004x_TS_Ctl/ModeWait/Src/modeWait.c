/*
 * csu_mode_wait.c
 *
 *  Created on: 8 janv. 2021
 *      Author: STuser
 */


#include "appctrlExt.h"
#include "modeWaitInt.h"

#include "Drv_adc_Ext.h"

SYSTEM_STATE_ENUM state;


SYSTEM_STATE_ENUM eModeWait_Mng (void)
{
    if (true == WaitInit)
    {
        vModewait_Reset();

        WaitInit = false;
    }


    /* Wait the 3 currents acquisition */
    vDrvadc_FirstAquisitionEnding();

    mode = APP_CTRL_MODE_WAIT_EVENT;
    state = APP_CTRL_MODE_WAIT_STATE;

    return state;
}


void vModewait_Reset (void)
{

}
