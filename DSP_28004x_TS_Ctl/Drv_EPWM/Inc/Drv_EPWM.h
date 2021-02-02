/*
 * Drv_EPWM.h
 *
 *  Created on: 15 janv. 2021
 *      Author: STuser
 */

#ifndef DRV_EPWM_INC_DRV_EPWM_H_
#define DRV_EPWM_INC_DRV_EPWM_H_

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/
//
// Defines
//
#define EPWM1_TIMER_TBPRD  2000U
#define EPWM1_MAX_CMPA     1950U
#define EPWM1_MIN_CMPA       50U
#define EPWM1_MAX_CMPB     1950U
#define EPWM1_MIN_CMPB       50U

#define EPWM2_TIMER_TBPRD  2000U
#define EPWM2_MAX_CMPA     1950U
#define EPWM2_MIN_CMPA       50U
#define EPWM2_MAX_CMPB     1950U
#define EPWM2_MIN_CMPB       50U

#define EPWM3_TIMER_TBPRD  2000U
#define EPWM3_MAX_CMPA      950U
#define EPWM3_MIN_CMPA       50U
#define EPWM3_MAX_CMPB     1950U
#define EPWM3_MIN_CMPB     1050U

#define EPWM_CMP_UP           1U
#define EPWM_CMP_DOWN         0U
/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/
void initEPWM1 (void);
void initEPWM2 (void);
void initEPWM3 (void);
void vDrvepwm_InitEpwm1  (void);
__interrupt void vDrvepwm_Epwm1ISR(void);
__interrupt void epwm2ISR(void);
__interrupt void epwm3ISR(void);
/**AutomaticEnd***************************************************************/



#endif /* DRV_EPWM_INC_DRV_EPWM_H_ */
