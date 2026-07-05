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
#include "stm32l4xx_hal.h"

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
    void init_SPI();

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Buck_EN_Pin GPIO_PIN_13
#define Buck_EN_GPIO_Port GPIOC
#define DWM_IRQ_Pin GPIO_PIN_0
#define DWM_IRQ_GPIO_Port GPIOA
#define DWM_IRQ_EXTI_IRQn EXTI0_IRQn
#define BMS_QONn_Pin GPIO_PIN_1
#define BMS_QONn_GPIO_Port GPIOA
#define BMS_INT_Pin GPIO_PIN_2
#define BMS_INT_GPIO_Port GPIOA
#define SPI1_NSS_Pin GPIO_PIN_4
#define SPI1_NSS_GPIO_Port GPIOA
#define EXTON_Pin GPIO_PIN_0
#define EXTON_GPIO_Port GPIOB
#define WAKEUP_Pin GPIO_PIN_1
#define WAKEUP_GPIO_Port GPIOB
#define DWM_nRST_Pin GPIO_PIN_2
#define DWM_nRST_GPIO_Port GPIOB
#define BMS_SCL_Pin GPIO_PIN_9
#define BMS_SCL_GPIO_Port GPIOA
#define BMS_SDA_Pin GPIO_PIN_10
#define BMS_SDA_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
extern SPI_HandleTypeDef hspi1;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
