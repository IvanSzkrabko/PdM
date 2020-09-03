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

#ifndef MISPROGRAMAS_CRONOMETRO_SRC_CRONOMETRO_UART_H_
#define MISPROGRAMAS_CRONOMETRO_SRC_CRONOMETRO_UART_H_

void UART_getCmd(void);
void UART_initicmd(void);


#endif /* MISPROGRAMAS_CRONOMETRO_SRC_CRONOMETRO_UART_H_ */
