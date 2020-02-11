/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

#include "ld_prog.h"
#include "os_conf.h"
#include "rs485.h"
#include "iwdg.h"
#include "crc.h"
#include "din.h"
#include "dout.h"
#include "ain.h"
#include "udp_server.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

extern unsigned short sys_tmr;
unsigned short work_time = 1;
extern unsigned short plc_cycle;
extern short ain[AI_CNT];
extern short ain_raw[AI_CNT];

uint16_t ai_type = 0xFFFF;

uint8_t adc_spi_tx[32];
uint8_t adc_spi_rx[32];
uint32_t adc_sum[14];

extern short ireg[IREG_CNT];

extern SPI_HandleTypeDef hspi1;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId progTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

extern void tcp_server_init(void);
extern void calculate_adc();
void update_ethip_intern_regs();
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void ProgTask(void const * argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of progTask */
  osThreadDef(progTask, ProgTask, osPriorityBelowNormal, 0, 512);
  progTaskHandle = osThreadCreate(osThread(progTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  tcp_server_init();
  udp_server_init();
  static uint16_t led_tmr = 0;
  static uint16_t adc_spi_tmr = 0;
  static uint16_t crc = 0;
  static uint16_t i=0;
  static uint16_t value=0;
  static uint16_t filter_cnt = 0;
  init_din();
  for(;;)
  {
	  led_tmr++;
	  if(led_tmr>=1000) {led_tmr=0;}
	  if(led_tmr==0) HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_SET);
	  else if(led_tmr==10) HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_RESET);

	  adc_spi_tmr++;
	  if(adc_spi_tmr==2) {
		  HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_RESET);
	  }else if(adc_spi_tmr==4) {
		  adc_spi_tx[0]=0x31;
		  adc_spi_tx[1]=0x31;
		  adc_spi_tx[2]=ai_type>>8;
		  adc_spi_tx[3]=ai_type&0xFF;
		  crc = GetCRC16(adc_spi_tx,30);
		  adc_spi_tx[30] = crc >> 8;
		  adc_spi_tx[31] = crc & 0xFF;
		  HAL_SPI_TransmitReceive_DMA(&hspi1, adc_spi_tx, adc_spi_rx, 32);
	  }else if(adc_spi_tmr==6) {
		  HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);
		  crc = GetCRC16(adc_spi_rx,32);
		  if(crc==0) {

			  for(i=0;i<AI_CNT;i++) {

				  value = (uint16_t)adc_spi_rx[2+i*2]<<8;
				  value|=adc_spi_rx[3+i*2];
				  adc_sum[i]+=value;
			  }
			  filter_cnt++;
			  if(filter_cnt==10) {
				  for(i=0;i<AI_CNT;i++) {
					  if(ai_type & ((uint16_t)1<<i)) {value = adc_sum[i]*50/62;}	// mA
					  else { value = adc_sum[i]/10; }	// mV
					  adc_sum[i] = 0;
					  //ireg[4+i] = value;
					  ain_raw[i]=value;
				  }
				  filter_cnt = 0;
				  calculate_adc();
				  update_ethip_ain();
			  }
		  }
	  }else if(adc_spi_tmr==10) {
		  adc_spi_tmr=0;
		  update_ethip_intern_regs();
	  }


	  update_din();

	  uart1_scan();
	  uart2_scan();
	  osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_ProgTask */
/**
* @brief Function implementing the progTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ProgTask */
void ProgTask(void const * argument)
{
  /* USER CODE BEGIN ProgTask */
  /* Infinite loop */

  static unsigned short work_tmr = 0;
  MX_IWDG_Init();
  for(;;)
  {
	  work_tmr = sys_tmr;
	  ld_process();
	  if(sys_tmr>=work_tmr) work_time = sys_tmr-work_tmr+1;
	  else work_time = 0xFFFF-work_tmr+sys_tmr;
	  inc_timers();
	  update_dout();
	  if(plc_cycle) osDelay(plc_cycle);
	  LL_IWDG_ReloadCounter(IWDG);
  }
  /* USER CODE END ProgTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
