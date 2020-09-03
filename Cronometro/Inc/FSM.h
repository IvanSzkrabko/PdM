/*=============================================================================
 * Copyright (c) 2020, IvanSzkrabko <ivanleonelszk@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/08/15
 *
 *El cronometro cuenta de 0 a 9 segundos
 *
 *   Secuencias Permitidas por UART:
	 step0 step1 step2 step3
	   A	I	  1/9	Z	:Cuenta
	   A	I	   0	Z	:Continua cuenta
	   A	D	   Z		:Detiene
	   A	R	   Z		:Reinicia
 *

 *===========================================================================*/

#include "sapi.h"

#ifndef MISPROGRAMAS_CRONOMETRO_SRC_FSM_H_
#define MISPROGRAMAS_CRONOMETRO_SRC_FSM_H_

// FSM state names
typedef enum{
   SetCron,
   ResetCron,
   StopCron,
} fsmState_t;

fsmState_t fsmState;

// FSM functions
void fsmError( void );
void fsmInit( void );
void fsmUpdate(fsmState_t, tick_t time, bool_t);
fsmState_t fsmReadState(void);



#endif /* MISPROGRAMAS_CRONOMETRO_SRC_FSM_H_ */
