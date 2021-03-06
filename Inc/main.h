/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_iwdg.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_gpio.h"

#include "stm32f4xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI1_CS_Pin GPIO_PIN_15
#define SPI1_CS_GPIO_Port GPIOF
#define RELE5_Pin GPIO_PIN_9
#define RELE5_GPIO_Port GPIOE
#define RELE4_Pin GPIO_PIN_11
#define RELE4_GPIO_Port GPIOE
#define RELE3_Pin GPIO_PIN_13
#define RELE3_GPIO_Port GPIOE
#define RELE6_Pin GPIO_PIN_14
#define RELE6_GPIO_Port GPIOE
#define RS485_DIR1_Pin GPIO_PIN_10
#define RS485_DIR1_GPIO_Port GPIOD
#define RS485_DIR2_Pin GPIO_PIN_2
#define RS485_DIR2_GPIO_Port GPIOG
#define RELE1_Pin GPIO_PIN_6
#define RELE1_GPIO_Port GPIOC
#define RELE2_Pin GPIO_PIN_7
#define RELE2_GPIO_Port GPIOC
#define LED_R_Pin GPIO_PIN_6
#define LED_R_GPIO_Port GPIOI
#define LED_G_Pin GPIO_PIN_7
#define LED_G_GPIO_Port GPIOI
/* USER CODE BEGIN Private defines */

#define LWIP_NETIF_LINK_CALLBACK        1

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
