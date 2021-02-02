/*
 * appctrlExt.h
 *
 *  Created on: 16 janv. 2021
 *      Author: STuser
 */

#ifndef APP_CTRL_APPCTRLEXT_H_
#define APP_CTRL_APPCTRLEXT_H_

#include "F28x_Project.h"
#include "device.h"

typedef enum
{
    APP_CTRL_MODE_INIT_STATE,
    APP_CTRL_MODE_WAIT_STATE,
    APP_CTRL_MODE_CLOSE_LOOP_STATE,
    APP_CTRL_MODE_OPEN_LOOP_STATE,
    APP_CTRL_MODE_COM_STATE

}SYSTEM_STATE_ENUM;

typedef enum
{
    APP_CTRL_MODE_INIT_EVENT,
    APP_CTRL_MODE_WAIT_EVENT,
    APP_CTRL_MODE_CLOSE_LOOP_EVENT,
    APP_CTRL_MODE_OPEN_LOOP_EVENT,
    APP_CTRL_MODE_COM_EVENT,
    APP_CTRL_MODE_NON_EVENT

}SYSTEM_EVENT_ENUM;

extern SYSTEM_EVENT_ENUM mode;

extern bool_t WaitInit;
extern bool_t OpenLoopInit;
extern bool_t CloseLoopInit;
extern bool_t ComInit;



#endif /* APP_CTRL_APPCTRLEXT_H_ */
