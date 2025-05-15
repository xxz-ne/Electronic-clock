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
#include "stm32f1xx_hal.h"

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
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOA
#define SELECT_Pin GPIO_PIN_11
#define SELECT_GPIO_Port GPIOB
#define SELECT_EXTI_IRQn EXTI15_10_IRQn
#define INC1_Pin GPIO_PIN_12
#define INC1_GPIO_Port GPIOB
#define INC1_EXTI_IRQn EXTI15_10_IRQn
#define DEC1_Pin GPIO_PIN_13
#define DEC1_GPIO_Port GPIOB
#define DEC1_EXTI_IRQn EXTI15_10_IRQn
#define IN_CLEAR_Pin GPIO_PIN_14
#define IN_CLEAR_GPIO_Port GPIOB
#define STOP_Pin GPIO_PIN_15
#define STOP_GPIO_Port GPIOB
#define STOP_EXTI_IRQn EXTI15_10_IRQn
#define MODE_Pin GPIO_PIN_7
#define MODE_GPIO_Port GPIOB
#define MODE_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
