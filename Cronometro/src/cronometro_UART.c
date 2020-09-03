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
#include "sapi.h"
#include "parser.h"

//#define debug_uart //para debugear

static uint8_t dato;
static char comand[5],time;
static uint8_t step;

void UART_initicmd(void){
	uartConfig( UART_USB, 115200 );
	dato=' ';
	step=0;
	strncpy(comand, "", sizeof(comand));
}

void UART_getCmd(){
	char caracter_A='A',caracter_R='R',caracter_D='D',caracter_Z='Z',caracter_I='I';

	if(uartReadByte( UART_USB, &dato )){

	 switch(dato){

	       case 'A':
	    	   if(step==0){
	    		   strncat(comand,&caracter_A,1);
					#if defined debug_uart
	    		    	uartWriteString(UART_USB,comand);
					#endif
	    		   step=1;
	    		   break;
	    	   }else


	       case 'I':
	    	   if(step==1){
	    		   strncat(comand,&caracter_I, 1);
				   #if defined debug_uart
	    		   	   uartWriteString(UART_USB,comand);
				   #endif
	    		   step=2;
	    		   break;
	    	   }else


	       case '0' ... '9':
		   	   if(step==2){
		   	      time=dato;
				  #if defined debug_uart
		   	      	  uartWriteString(UART_USB,comand);
				  #endif
		   	      step=3;
		   	   break;
		   	   }else


	       case 'R':
	    	   if(step==1){
	    		   strncat(comand,&caracter_R,1);
				   #if defined debug_uart
	    		     uartWriteString(UART_USB,comand);
				   #endif
	    		   step=3;
	    		   break;
	    	   }else



	       case 'D':
	    	   if(step==1){
	    		   strncat(comand,&caracter_D,1);
				   #if defined debug_uart
	    		     uartWriteString(UART_USB,comand);
				   #endif
	    		   step=3;
	    		   break;
	    	   }else



	       case 'Z':
	    	   if(step==3){
	    		   strncat(comand,&caracter_Z,1);
	    		   uartWriteByte(UART_USB,'_');
	    		   uartWriteString(UART_USB,comand);
	    		   uartWriteByte(UART_USB,'_');
	    		   goParse(comand,time);
	    		   step=0;
	    		   strncpy(comand, "", sizeof(comand));
	    		   dato=' ';
	    		   break;
	    	   }else

	       default:
	    	   dato=' ';
	    	   step=0;
	    	   strncpy(comand, "", sizeof(comand));
	    	   uartWriteString(UART_USB,"_RESET_");
	    	   goParse("ARZ",'0');
	       	   break;
	 }
	}
}


