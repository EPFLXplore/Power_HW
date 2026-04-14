/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#define INPUT_ALERT_Pin GPIO_PIN_15
#define INPUT_ALERT_GPIO_Port GPIOC
#define PG_5V_Pin GPIO_PIN_2
#define PG_5V_GPIO_Port GPIOC
#define PG_12V_Pin GPIO_PIN_3
#define PG_12V_GPIO_Port GPIOC
#define ALERT_24V_Pin GPIO_PIN_0
#define ALERT_24V_GPIO_Port GPIOA
#define ALERT_15V_Pin GPIO_PIN_1
#define ALERT_15V_GPIO_Port GPIOA
#define ALERT_12V_Pin GPIO_PIN_2
#define ALERT_12V_GPIO_Port GPIOA
#define SHDN_5V_Pin GPIO_PIN_3
#define SHDN_5V_GPIO_Port GPIOA
#define PG_15V_Pin GPIO_PIN_4
#define PG_15V_GPIO_Port GPIOC
#define PG_24V_Pin GPIO_PIN_5
#define PG_24V_GPIO_Port GPIOC
#define PG_BATT_Pin GPIO_PIN_6
#define PG_BATT_GPIO_Port GPIOC
#define SCREEN_INT_Pin GPIO_PIN_7
#define SCREEN_INT_GPIO_Port GPIOC
#define SPI_CS0_Pin GPIO_PIN_8
#define SPI_CS0_GPIO_Port GPIOC
#define SPI_CS1_Pin GPIO_PIN_9
#define SPI_CS1_GPIO_Port GPIOC
#define SHDN_12V_Pin GPIO_PIN_10
#define SHDN_12V_GPIO_Port GPIOA
#define ALERT_5V_Pin GPIO_PIN_15
#define ALERT_5V_GPIO_Port GPIOA
#define SPI_CS2_Pin GPIO_PIN_10
#define SPI_CS2_GPIO_Port GPIOC
#define SPI_CS3_Pin GPIO_PIN_11
#define SPI_CS3_GPIO_Port GPIOC
#define SPI_CS4_Pin GPIO_PIN_12
#define SPI_CS4_GPIO_Port GPIOC
#define SHDN_15V_Pin GPIO_PIN_4
#define SHDN_15V_GPIO_Port GPIOB
#define SHDN_24V_Pin GPIO_PIN_7
#define SHDN_24V_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
