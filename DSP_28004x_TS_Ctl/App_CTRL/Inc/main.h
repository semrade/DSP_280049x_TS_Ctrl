/*
 * main.h
 *
 *  Created on: 7 janv. 2021
 *      Author: STuser
 */

#ifndef MAIN_H_
#define MAIN_H_
#include "F28x_Project.h"
#include "f28004x_device.h"
#include "appctrlExt.h"

void vAppCtrl_Init (void);
void vAppCtrl_Reset (void);


SYSTEM_EVENT_ENUM mode;

#endif /* MAIN_H_ */
