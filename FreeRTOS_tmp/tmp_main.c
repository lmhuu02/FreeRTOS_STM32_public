//--------------------------------------------------------------
// File     : main.c
// Datum    : 11.01.2013
// Version  : 1.0
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.4
// GCC      : 4.7 2012q4
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Funktion : Demo der FreeRTOS-Library
// Hinweis  : Diese zwei Files muessen auf 8MHz stehen
//              "cmsis_boot/stm32f4xx.h"
//              "cmsis_boot/system_stm32f4xx.c"
//--------------------------------------------------------------


#include "stm32f4xx.h"


/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "stm32f4xx_rcc.h"

#include "stm32f4xx_gpio.h"

#define STACK_SIZE  ( ( unsigned short ) 100 ) // Kich thuoc stack danh cho 1 task

// Do uu tien cua tien trinh nam trong khoang 0->MAX_PRIORITY
#define PRIORITY ( ( unsigned portBASE_TYPE ) 0U )

/* Khai bao cac Task */
static void vLEDTask1( void *pvParameters );
static void vLEDTask2( void *pvParameters );
static void vLEDTask3( void *pvParameters );
static void vLEDTask4( void *pvParameters );


//#define queueSIZE	6


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


	  //Include main header for MCU

	int main(void)
	{
		GPIO_SETUP();

		// Tao 4 Task
		xTaskCreate( vLEDTask1, ( signed portCHAR * ) "LED_PD12", STACK_SIZE, NULL,PRIORITY, NULL);
		xTaskCreate( vLEDTask2, ( signed portCHAR * ) "LED_PD13", STACK_SIZE, NULL,PRIORITY, NULL);
		xTaskCreate( vLEDTask3, ( signed portCHAR * ) "LED_PD14", STACK_SIZE, NULL,PRIORITY, NULL);
		xTaskCreate( vLEDTask4, ( signed portCHAR * ) "LED_PD15", STACK_SIZE, NULL,PRIORITY, NULL);


		/* KHOI TAO BO LAP LICH  */
		vTaskStartScheduler();

		/* Will only get here if there was not enough heap space to create the idle task. */
		return 0;
	}

	// DINH NGHIA CHI TIET NOI DUNG TUNG TASK
	static void vLEDTask1( void *pvParameters ){

		while(1){
			GPIOD->ODR |=(uint16_t) 0x1000; //PD12 =1
			delay(100000);
			GPIOD->ODR &=(uint16_t)~0x1000;
			delay(100000);
		  }
	}
	static void vLEDTask2( void *pvParameters ){

			while(1){
				GPIOD->ODR |=(uint16_t) 0x2000;  // PD13
				delay(100000);
				GPIOD->ODR &=(uint16_t)~0x2000;
				delay(100000);
			  }
		}
	static void vLEDTask3( void *pvParameters ){

			while(1){
				GPIOD->ODR |=(uint16_t) 0x4000;  //PD14
				delay(100000);
				GPIOD->ODR &=(uint16_t)~0x4000;
				delay(100000);
			  }
		}
	static void vLEDTask4( void *pvParameters ){

			while(1){
				GPIOD->ODR |=(uint16_t) 0x8000;  //PD15
				delay(100000);
				GPIOD->ODR &=(uint16_t)~0x8000;
				delay(100000);
			  }
		}
