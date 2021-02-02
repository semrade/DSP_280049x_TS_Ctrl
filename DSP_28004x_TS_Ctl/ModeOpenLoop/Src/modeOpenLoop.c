/*
 * csu_mode_open_loop.c
 *
 *  Created on: 8 janv. 2021
 *      Author: STuser
 */

#include "appctrlExt.h"

SYSTEM_STATE_ENUM
eModeOpenLoop_Mng(void)
{
    mode = APP_CTRL_MODE_OPEN_LOOP_EVENT;

    if (APP_CTRL_MODE_OPEN_LOOP_EVENT == mode)
    {
        return APP_CTRL_MODE_OPEN_LOOP_STATE;
    }
    else
    {
        return APP_CTRL_MODE_WAIT_STATE;
    }

}
