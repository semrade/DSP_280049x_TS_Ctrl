/*
 * Drv_ADC_X.h
 *
 *  Created on: 9 janv. 2021
 *      Author: STuser
 */

#ifndef DRV_ADC_DRV_ADC_EXT_H_
#define DRV_ADC_DRV_ADC_EXT_H_
#include "F28x_Project.h"

extern void vDrvadc_InitAllAdc (void);
extern void vDrvadc_AdcSocCnfg (void);

extern void vDrvadc_FirstAquisitionEnding(void);
extern void vDrvadc_SecondAquisitionEnding(void);
extern void vDrvadc_SetupPPBOffset(int16 aOffset, int16 bOffset, int16 cOffset);

#endif /* DRV_ADC_DRV_ADC_EXT_H_ */
