#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

// MEF com 7 estados 
// Seleção por evento

typedef enum {seq0,seq1,seq2,seq3,seq4,seq5,seq6,seq7} state_t;

volatile uint8_t Evento = 0;

void SysTick_Handler(void){
  Evento = 1;
} // SysTick_Handler

void main(void){
  static state_t Estado = seq0; // estado inicial da MEF
  
  LEDInit(LED1); // Led 1
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();
  
  LEDInit(LED2); // Led 2
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();
  
  LEDInit(LED3); // Led 3
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while(1){
    if(Evento){
      Evento = 0;
      switch(Estado){
        case seq0: // Sequência 000
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado = seq1;
          break;
        case seq1: // Sequência 001
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOn(LED3);
          Estado = seq2;
          break;
       case seq2: // Sequência 011
          LEDOff(LED1);
          LEDOn(LED2);
          LEDOn(LED3);
          Estado = seq3;
          break; 
      case seq3: // Sequência 010
          LEDOff(LED1);
          LEDOn(LED2);
          LEDOff(LED3);
          Estado = seq4;
          break;
      case seq4: // Sequência 110
          LEDOn(LED1);
          LEDOn(LED2);
          LEDOff(LED3);
          Estado = seq5;
          break;  
      case seq5: // Sequência 111
          LEDOn(LED1);
          LEDOn(LED2);
          LEDOn(LED3);
          Estado = seq6;
          break;
      case seq6: // Sequência 101
          LEDOn(LED1);
          LEDOff(LED2);
          LEDOn(LED3);
          Estado = seq7;
          break;
      case seq7: // Sequência 100
          LEDOn(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado = seq0; // Retorna para a seq0 (Sequência 000)
          break;
      } // switch
    } // if
  } // while
} // main
