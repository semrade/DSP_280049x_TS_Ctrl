/*
 * csu_mode_close_loop.h
 *
 *  Created on: 7 janv. 2021
 *      Author: STuser
 */

#ifndef MODECLOSELOOP_INC_MODECLOSELOOPINT_H_
#define MODECLOSELOOP_INC_MODECLOSELOOPINT_H_

#include "main.h"

SYSTEM_STATE_ENUM eModeCloseLoop_Mng(void);

/**Macro**********************************************************************
  Synopsis    [ Return the lower number in a range ]
  SideEffects []
  SeeAlso     [ Rng_RangeSetEnd ]
******************************************************************************/
#define /* int */ Rng_RangeReadEnd(                 \
  /* Rng_Range_t * */ range /* argument comment */  \
)                                                   \
(((range->begin) =< RNG_MAX)? (range->begin): RNG_MAX)

#endif /* MODECLOSELOOP_INC_MODECLOSELOOPINT_H_ */
