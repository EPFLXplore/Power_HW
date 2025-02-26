/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32g4xx_hal.h"

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
#define LED_CAT1_Pin GPIO_PIN_13
#define LED_CAT1_GPIO_Port GPIOC
#define LED_CAT2_Pin GPIO_PIN_14
#define LED_CAT2_GPIO_Port GPIOC
#define RUN1_B_Pin GPIO_PIN_15
#define RUN1_B_GPIO_Port GPIOC
#define IRQ_Pin GPIO_PIN_0
#define IRQ_GPIO_Port GPIOC
#define SYNC0_Pin GPIO_PIN_1
#define SYNC0_GPIO_Port GPIOC
#define SYNC1_Pin GPIO_PIN_2
#define SYNC1_GPIO_Port GPIOC
#define RUN0_B_Pin GPIO_PIN_3
#define RUN0_B_GPIO_Port GPIOC
#define FAULT1_B_Pin GPIO_PIN_0
#define FAULT1_B_GPIO_Port GPIOA
#define MB_SHDN_VA_Pin GPIO_PIN_1
#define MB_SHDN_VA_GPIO_Port GPIOA
#define ALERT_B_Pin GPIO_PIN_2
#define ALERT_B_GPIO_Port GPIOA
#define MB_SHDN_VB_Pin GPIO_PIN_3
#define MB_SHDN_VB_GPIO_Port GPIOA
#define FAULT0_B_Pin GPIO_PIN_4
#define FAULT0_B_GPIO_Port GPIOC
#define PRE_FLT_Pin GPIO_PIN_5
#define PRE_FLT_GPIO_Port GPIOC
#define PRE_EN_Pin GPIO_PIN_0
#define PRE_EN_GPIO_Port GPIOB
#define FAN_CTRL_Pin GPIO_PIN_1
#define FAN_CTRL_GPIO_Port GPIOB
#define MA_SHDN_VA_Pin GPIO_PIN_2
#define MA_SHDN_VA_GPIO_Port GPIOB
#define FAULT1_A_Pin GPIO_PIN_10
#define FAULT1_A_GPIO_Port GPIOB
#define TEMP_SENS_Pin GPIO_PIN_11
#define TEMP_SENS_GPIO_Port GPIOB
#define RUN0_A_Pin GPIO_PIN_6
#define RUN0_A_GPIO_Port GPIOC
#define INT_Pin GPIO_PIN_7
#define INT_GPIO_Port GPIOC
#define RUN1_A_Pin GPIO_PIN_10
#define RUN1_A_GPIO_Port GPIOA
#define ALERT_A_Pin GPIO_PIN_2
#define ALERT_A_GPIO_Port GPIOD
#define FAULT0_A_Pin GPIO_PIN_4
#define FAULT0_A_GPIO_Port GPIOB
#define FAULT1_AB7_Pin GPIO_PIN_7
#define FAULT1_AB7_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
