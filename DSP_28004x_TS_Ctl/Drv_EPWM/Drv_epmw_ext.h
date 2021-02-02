/*
 * Drv_EPWM_X.h
 *
 *  Created on: 9 janv. 2021
 *      Author: STuser
 */

#ifndef DRV_EPWM_DRV_EPMW_EXT_H_
#define DRV_EPWM_DRV_EPMW_EXT_H_


extern bool EpwmInterruptFlag;

extern void vDrvepwm_InitEpwm1 (void);
extern __interrupt void vDrvepwm_Epwm1ISR(void);

#endif /* DRV_EPWM_DRV_EPMW_EXT_H_ */
