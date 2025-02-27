//--------------------------------------------------------------
// File     : stm32_ub_freertos.c
// Datum    : 11.01.2014
// Version  : 1.0
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.4
// GCC      : 4.7 2012q4
// Module   : FreeRTOS
// Funktion : FreeRTOS (GCC-Version f�r ARM Cortex-M4/F)
//            Version 7.6.0 (vom 18.11.2013)
//            Quelle : www.freertos.org
//
// Doku und Beispiele : www.freertos.org
//
// FPU      : Hardware FPU muss in CoIDE aktiviert werden
//
// Heap     : nur EIN File vom "FreeRTOS\Source\portable\MemMang\"
//            Ordner in das Projekt einbinden !! (z.B. "heap_2.c")
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
// #include "stm32_ub_freertos.h"
#include "edit_stm32_freertos.h"

//--------------------------------------------------------------
// IDLE
//--------------------------------------------------------------
void vApplicationIdleHook( void ){}
//--------------------------------------------------------------
// TICK
//--------------------------------------------------------------
void vApplicationTickHook( void ){}
//--------------------------------------------------------------
// STACK OVERFLOW
//--------------------------------------------------------------
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) xTask;
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
//--------------------------------------------------------------
// MALLOC FAILED
//--------------------------------------------------------------
void vApplicationMallocFailedHook( void )
{
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
