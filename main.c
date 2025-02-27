//--------------------------------------------------------------
// File     : main.c
// Date    	: 27.02.2025
// Autor    : Le Minh Huu - ICTU
// Web      : github: https://github.com/lmhuu02
// yt		: https://www.youtube.com/@LeHuu02
// CPU      : STM32F407
// IDE      : CooCox CoIDE 1.7.6
// GCC      : 8 2018-q4-major
// Module   : FreeRTOS
// Funktion : FreeRTOS (GCC-Version f�r ARM Cortex-M4/F)
//            Version 11.1.0 (vom 202406.1 LTS)
//            Quelle : www.freertos.org
//
// Doku und Beispiele : www.freertos.org
//
// FPU      : Hardware FPU muss in CoIDE aktiviert werden
//
// Heap     : nur EIN File vom "FreeRTOS\Source\portable\MemMang\" "heap_4.c")
//--------------------------------------------------------------

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

void GPIO_SETUP(void);

#define STACK_SIZE  ( ( unsigned short ) 128 ) // Kich thuoc stack danh cho 1 task
// Do uu tien cua tien trinh nam trong khoang 0->MAX_PRIORITY
#define PRIORITY ( ( unsigned portBASE_TYPE ) 2 )

/* Khai bao cac Task */
static void vLEDTask1( void *pvParameters );
static void vLEDTask2( void *pvParameters );
static void vLEDTask3( void *pvParameters );
static void vLEDTask4( void *pvParameters );

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

void delay(int ticks)
{
  while(ticks--);
}

void GPIO_SETUP(void)
{

  GPIO_InitTypeDef        GPIO_InitS;
  /* cap xung cho cong D vi cac LED nam tren cong D  */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  /* cau hinh PC9 and PC8 la dau ra, khong dung tro keo */
  GPIO_InitS.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14 | GPIO_Pin_15 ;

  GPIO_InitS.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitS.GPIO_OType = GPIO_OType_PP;
  GPIO_InitS.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitS.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitS);// Gan cao hinh GPIO_InitS vao cong D
}

int main(void)
{
	GPIO_SETUP();
	// Tao 4 Task
	xTaskCreate( vLEDTask1,  "LED_PD12", STACK_SIZE, NULL,PRIORITY, NULL);
	xTaskCreate( vLEDTask2,  "LED_PD13", STACK_SIZE, NULL,PRIORITY, NULL);
	xTaskCreate( vLEDTask3,  "LED_PD14", STACK_SIZE, NULL,PRIORITY, NULL);
	xTaskCreate( vLEDTask4,  "LED_PD15", STACK_SIZE, NULL,PRIORITY, NULL);

	 /* KHOI TAO BO LAP LICH  */
	vTaskStartScheduler();

	/* Will only get here if there was not enough heap space to create the idle task. */
	return 0;
}

// DINH NGHIA CHI TIET NOI DUNG TUNG TASK
static void vLEDTask1( void *pvParameters ){
	while(1){
		GPIOD->ODR |=(uint16_t) 0x1000; //PD12 =1
		vTaskDelay(100);
//		delay(1000000);
		GPIOD->ODR &=(uint16_t)~0x1000;
		vTaskDelay(100);
//		delay(1000000);
	  }
}
static void vLEDTask2( void *pvParameters ){

		while(1){
			GPIOD->ODR |=(uint16_t) 0x2000;  // PD13
			vTaskDelay(100);
//			delay(1000000);
			GPIOD->ODR &=(uint16_t)~0x2000;
			vTaskDelay(100);
//			delay(1000000);

		  }
	}
static void vLEDTask3( void *pvParameters ){

		while(1){
			GPIOD->ODR |=(uint16_t) 0x4000;  //PD14
			vTaskDelay(100);
			GPIOD->ODR &=(uint16_t)~0x4000;
			vTaskDelay(100);
		  }
	}
static void vLEDTask4( void *pvParameters ){

		while(1){
			GPIOD->ODR |=(uint16_t) 0x8000;  //PD15
			vTaskDelay(100);
			GPIOD->ODR &=(uint16_t)~0x8000;
			vTaskDelay(100);
		  }
	}



