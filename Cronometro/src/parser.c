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

#include <string.h>
#include "FSM.h"

 void goParse(char comand[5],char time){

	       if(strcmp(comand, "ARZ")==0)
	    	   fsmUpdate(ResetCron,0,FALSE);

	       if(strcmp(comand, "ADZ")==0)
	    	   fsmUpdate(StopCron,0,FALSE);

	       if(strcmp(comand, "AIZ")==0)
	    	   if(time>='0' && time<='9'){
	    	   fsmUpdate(SetCron,((int)(time)-48),FALSE);
	    	   }

 }


