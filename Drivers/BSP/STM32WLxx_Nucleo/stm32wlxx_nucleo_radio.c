/**
  ******************************************************************************
  * @file    stm32wlxx_nucleo_radio.c
  * @author  MCD Application Team
  * @brief   This file provides set of firmware functions to manage:
  *          - RF circuitry available on STM32WLXX-Nucleo
  *            Kit from STMicroelectronics
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  * ---JoEmbedded--
  * Ca. Z.24: #include "device.h"
  * Ca. Z.50/103/138 BSP_RADIO_(De)Init/switch(): PINS einbauen RAK
  * Ca. Z.211 RAK-Version
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "device.h"
#include "stm32wlxx_nucleo_radio.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32WLXX_NUCLEO
  * @{
  */

/** @addtogroup STM32WLXX_NUCLEO_RADIO_LOW_LEVEL
  * @brief This file provides set of firmware functions to Radio switch 
  *        available on STM32WLXX-Nucleo Kit from STMicroelectronics.
  * @{
  */

/** @addtogroup STM32WLXX_NUCLEO_RADIO_LOW_LEVEL_Exported_Functions
  * @{
  */
  
/**
  * @brief  Init Radio Switch 
  * @retval BSP status
  */
int32_t BSP_RADIO_Init(void)
{
  GPIO_InitTypeDef  gpio_init_structure = {0};

#if defined(RAK3172LP_SIP) || defined(RAK3172_SIP)
 HAL_GPIO_DeInit(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN);
  HAL_GPIO_DeInit(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN);
  /* Enable the Radio Switch Clock */
  RF_SW_CTRL1_GPIO_CLK_ENABLE();
  RF_SW_CTRL2_GPIO_CLK_ENABLE();
  /* Configure the Radio Switch pin */
  gpio_init_structure.Pin   = RF_SW_CTRL1_PIN;
  gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull  = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(RF_SW_CTRL1_GPIO_PORT, &gpio_init_structure);
  gpio_init_structure.Pin = RF_SW_CTRL2_PIN;
  HAL_GPIO_Init(RF_SW_CTRL2_GPIO_PORT, &gpio_init_structure);
  HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET);
#else
  // Std. Nucleo
  /* Enable the Radio Switch Clock */
  RF_SW_CTRL3_GPIO_CLK_ENABLE();
  
  /* Configure the Radio Switch pin */
  gpio_init_structure.Pin   = RF_SW_CTRL1_PIN;
  gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull  = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  
  HAL_GPIO_Init(RF_SW_CTRL1_GPIO_PORT, &gpio_init_structure);
  
  gpio_init_structure.Pin = RF_SW_CTRL2_PIN;
  HAL_GPIO_Init(RF_SW_CTRL2_GPIO_PORT, &gpio_init_structure);
  
  gpio_init_structure.Pin = RF_SW_CTRL3_PIN;
  HAL_GPIO_Init(RF_SW_CTRL3_GPIO_PORT, &gpio_init_structure);

  HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_RESET); 
#endif
  return BSP_ERROR_NONE;
}

/**
  * @brief  DeInit Radio Switch
  * @retval BSP status
  */
int32_t BSP_RADIO_DeInit(void)
{
#if defined(RAK3172LP_SIP) || defined(RAK3172_SIP)
  RF_SW_CTRL1_GPIO_CLK_ENABLE();
  RF_SW_CTRL2_GPIO_CLK_ENABLE();
  /* Turn off switch */
  HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET);
  /* DeInit the Radio Switch pin */
  HAL_GPIO_DeInit(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN);
  HAL_GPIO_DeInit(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN);
#else
	RF_SW_CTRL3_GPIO_CLK_ENABLE();

  /* Turn off switch */
  HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_RESET); 
  
  /* DeInit the Radio Switch pin */
  HAL_GPIO_DeInit(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN);
  HAL_GPIO_DeInit(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN);
  HAL_GPIO_DeInit(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN);
#endif
  return BSP_ERROR_NONE;
}

/**
  * @brief  Configure Radio Switch.
  * @param  Config: Specifies the Radio RF switch path to be set. 
  *         This parameter can be one of following parameters:
  *           @arg RADIO_SWITCH_OFF
  *           @arg RADIO_SWITCH_RX
  *           @arg RADIO_SWITCH_RFO_LP
  *           @arg RADIO_SWITCH_RFO_HP
  * @retval BSP status
  */
int32_t BSP_RADIO_ConfigRFSwitch(BSP_RADIO_Switch_TypeDef Config)
{
  switch (Config)
  {
    case RADIO_SWITCH_OFF:
    {
#if defined(RAK3172LP_SIP) || defined(RAK3172_SIP)
        /* Turn off switch */
        HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET);
      #else
        /* Turn off switch */
        HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET);
      #endif
      break;      
    }
    case RADIO_SWITCH_RX:
    {
#if defined(RAK3172LP_SIP) || defined(RAK3172_SIP)
        /*Turns On in Rx Mode the RF Switch */
        HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET);
      #else
        /*Turns On in Rx Mode the RF Switch */
        HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET);
      #endif
      break;
    }
    case RADIO_SWITCH_RFO_LP:
    {
#if defined(RAK3172LP_SIP) || defined(RAK3172_SIP)
        /*Turns On in Tx Low Power the RF Switch */
        HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_SET);
      #else
        /*Turns On in Tx Low Power the RF Switch */
        HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_SET);
      #endif
      break;
    }
    case RADIO_SWITCH_RFO_HP:
    {
#if defined(RAK3172LP_SIP) || defined(RAK3172_SIP)
        /*Turns On in Tx High Power the RF Switch */
        HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_SET);
      #else
        /*Turns On in Tx High Power the RF Switch */
        HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_SET);
      #endif
      break;
    }
    default:
      break;    
  }  

  return BSP_ERROR_NONE;
}
/**
  * @brief  Return Board Configuration
  * @retval 
  *  RADIO_CONF_RFO_LP_HP
  *  RADIO_CONF_RFO_LP
  *  RADIO_CONF_RFO_HP
  */
int32_t BSP_RADIO_GetTxConfig(void)
{
#if defined(RAK3172_SIP)
	return RADIO_CONF_RFO_HP;
#elif defined(RAK3172LP_SIP)
	return RADIO_CONF_RFO_LP;
#else
	return RADIO_CONF_RFO_LP_HP;
#endif
}

/**
  * @brief  Get If TCXO is to be present on board
  * @note   never remove called by MW,
  * @retval
  *  RADIO_CONF_TCXO_NOT_SUPPORTED
  *  RADIO_CONF_TCXO_SUPPORTED
  */
int32_t BSP_RADIO_IsTCXO(void)
{
  return RADIO_CONF_TCXO_SUPPORTED;
}

/**
  * @brief  Get If DCDC is to be present on board
  * @note   never remove called by MW,
  * @retval
  *  RADIO_CONF_DCDC_NOT_SUPPORTED
  *  RADIO_CONF_DCDC_SUPPORTED  
  */
int32_t BSP_RADIO_IsDCDC(void)
{
  return RADIO_CONF_DCDC_SUPPORTED;
}

/**
  * @brief  Return RF Output Max Power Configuration
  * @retval
  *    RADIO_CONF_RFO_LP_MAX_15_dBm for LP mode
  *    RADIO_CONF_RFO_HP_MAX_22_dBm for HP mode
  */
int32_t BSP_RADIO_GetRFOMaxPowerConfig(BSP_RADIO_RFOMaxPowerConfig_TypeDef Config)
{
  int32_t ret;

  if(Config == RADIO_RFO_LP_MAXPOWER)
  {
    ret = RADIO_CONF_RFO_LP_MAX_15_dBm;
  }
  else
  {
    ret = RADIO_CONF_RFO_HP_MAX_22_dBm;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
