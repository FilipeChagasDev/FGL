/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32h7xx_hal.h"

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
void jumpToCPP();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TFT_RST_Pin GPIO_PIN_4
#define TFT_RST_GPIO_Port GPIOA
#define TFT_A0_Pin GPIO_PIN_6
#define TFT_A0_GPIO_Port GPIOA
#define TFT_CS_Pin GPIO_PIN_4
#define TFT_CS_GPIO_Port GPIOC
#define GPIO_EXTI1_ENC_A_Pin GPIO_PIN_1
#define GPIO_EXTI1_ENC_A_GPIO_Port GPIOD
#define GPIO_EXTI1_ENC_A_EXTI_IRQn EXTI1_IRQn
#define GPIO_EXT2_ENC_B_Pin GPIO_PIN_2
#define GPIO_EXT2_ENC_B_GPIO_Port GPIOD
#define GPIO_EXT2_ENC_B_EXTI_IRQn EXTI2_IRQn
#define GPIO_EXTI3_ENC_SW_Pin GPIO_PIN_3
#define GPIO_EXTI3_ENC_SW_GPIO_Port GPIOD
#define GPIO_EXTI3_ENC_SW_EXTI_IRQn EXTI3_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
