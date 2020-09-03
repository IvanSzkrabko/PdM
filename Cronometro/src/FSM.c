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
#include "parser.h"
#include "FSM.h"

// FSM DECLARATIONS
static gpioMap_t leds[] = {LED1, LED2, LED3};//amarillo rojo verde
static delay_t contador;
static tick_t tickdiff, saveduration, newduration;

// FSM Error Handler Function
void fsmError( void )
{
	 fsmState = ResetCron;
}

// FSM Initialize Function
void fsmInit( void )
{
   fsmState = ResetCron;   // Set initial state
}

fsmState_t fsmReadState(void){
	return fsmState;
}


// FSM Update Sate Function
void fsmUpdate( fsmState_t updateState, tick_t time, bool_t checkonly )
{
	if(checkonly){
		if( fsmState == SetCron && delayRead( &contador )){
			updateState=ResetCron;
			checkonly=FALSE;
		}
	}

	if(!checkonly){

		switch(updateState){

		case SetCron://AMARILLO
			fsmState=SetCron;
			gpioWrite( leds[0], TRUE);
			gpioWrite( leds[1], FALSE);
			gpioWrite( leds[2], FALSE);

			if(contador.running==FALSE){
				if(time>0 && contador.duration==0){ //incio conteo
					delayInit( &contador, time*1000); //Para pasar time a segundos
					delayRead( &contador);
					saveduration=FALSE;
					uartWriteString(UART_USB,"(>)");
				}else{
					if(time==0 && saveduration)//reactivo conteo
						delayInit( &contador, newduration);
					    delayRead( &contador);
						saveduration=FALSE;
					}
			}
			break;

		case ResetCron://ROJO
			fsmState=ResetCron;
			contador.startTime=0;
			contador.running=0;
			contador.duration=0;
			saveduration=FALSE;
			gpioWrite( leds[0], FALSE);
			gpioWrite( leds[1], TRUE);
			gpioWrite( leds[2], FALSE);
			break;


		case StopCron://VERDE
				if(!saveduration && fsmState==SetCron){
					tickdiff=tickRead() - contador.startTime;
					newduration=contador.duration-tickdiff;
					contador.startTime=0;
					contador.running=0;
					contador.duration=0;
					saveduration=TRUE;
				}
				fsmState=StopCron;
				gpioWrite( leds[0], FALSE);
				gpioWrite( leds[1], FALSE);
				gpioWrite( leds[2], TRUE);
			break;

		default:
			fsmError();
			break;
		}
	}
}
