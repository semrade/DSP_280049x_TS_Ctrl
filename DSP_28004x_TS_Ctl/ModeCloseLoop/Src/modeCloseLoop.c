/*
 * csu_mode_close_loop.c
 *
 *  Created on: 7 janv. 2021
 *      Author: STuser
 */

#include "appctrlExt.h"
#include "math.h"




SYSTEM_STATE_ENUM
eModeCloseLoop_Mng (void)
{
    mode = APP_CTRL_MODE_CLOSE_LOOP_EVENT;
    //Level 1
#ifdef LEVEL_1
#endif

    //Level 2
#ifdef LEVEL_2
#endif

    //Level 3
#ifdef LEVEL_3
#endif

    //Level 4
#ifdef LEVEL_4
#endif

    //Level 5
#ifdef LEVEL_5
#endif

    // write event and return
    if (APP_CTRL_MODE_CLOSE_LOOP_EVENT == mode)
    {
        return APP_CTRL_MODE_CLOSE_LOOP_STATE;
    }
    else
    {
        return APP_CTRL_MODE_WAIT_STATE;
    }

}

