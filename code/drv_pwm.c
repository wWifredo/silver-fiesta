#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include "drv_pwm.h"
#include "ctrl_pwm.h"
#include <string.h>

#include <stm32f407xx.h>

#include "../../../../../common/com_error/com_error.h"
#include "../../../../../common/com_algorithm/motor/stepper/com_smd.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim9;

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *timHandle);

/* TIM1 init function */
void MX_TIM1_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 167;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 65535;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
    {
        printk("HAL_TIM1_Base_Init failed\n");
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
    {
        printk("HAL_TIM1_ConfigClockSource failed\n");
    }
    if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
    {
        printk("HAL_TIM1_OC_Init failed\n");
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
    {
        printk("HAL_TIM1Ex_MasterConfigSynchronization failed\n");
    }
    sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        printk("HAL_TIM1_OC_ConfigChannel1 failed\n");
    }
    if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        printk("HAL_TIM1_OC_ConfigChannel2 failed\n");
    }
    if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        printk("HAL_TIM1_OC_ConfigChannel3 failed\n");
    }
    if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        printk("HAL_TIM1_OC_ConfigChannel4 failed\n");
    }
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
    {
        printk("HAL_TIM1Ex_ConfigBreakDeadTime failed\n");
    }

    HAL_TIM_MspPostInit(&htim1);

}

/* TIM8 init function */
void MX_TIM8_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    htim8.Instance = TIM8;
    htim8.Init.Prescaler = 167;
    htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim8.Init.Period = 2499;
    htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim8.Init.RepetitionCounter = 0;
    htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
    {
        printk("HAL_TIM8_Base_Init failed\n");
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
    {
        printk("HAL_TIM8_ConfigClockSource failed\n");
    }
    if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
    {
        printk("HAL_TIM8_PWM_Init failed\n");
    }
    if (HAL_TIM_OC_Init(&htim8) != HAL_OK)
    {
        printk("HAL_TIM8_OC_Init failed\n");
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
    {
        printk("HAL_TIM8Ex_MasterConfigSynchronization failed\n");
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM2;
    sConfigOC.Pulse = 500;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        printk("HAL_TIM8_PWM_ConfigChannel1 failed\n");
    }
    if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        printk("HAL_TIM8_PWM_ConfigChannel2 failed\n");
    }
    if (HAL_TIM_OC_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        printk("HAL_TIM8_OC_ConfigChannel failed\n");
    }
    if (HAL_TIM_OC_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        printk("HAL_TIM8_OC_ConfigChannel failed\n");
    }
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
    {
        printk("HAL_TIM8Ex_ConfigBreakDeadTime failed\n");
    }

    HAL_TIM_MspPostInit(&htim8);
}
/* TIM9 init function */
void MX_TIM9_Init(void)
{
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim9.Instance = TIM9;
    htim9.Init.Prescaler = 167;
    htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim9.Init.Period = 65535;
    htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&htim9) != HAL_OK)
    {
        printk("HAL_TIM9_PWM_Init failed\n");
    }
    sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        printk("HAL_TIM9_PWM_ConfigChannel1 failed\n");
    }
    if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        printk("HAL_TIM9_PWM_ConfigChannel2 failed\n");
    }

    HAL_TIM_MspPostInit(&htim9);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(tim_baseHandle->Instance==TIM1)
    {
        /* TIM1 clock enable */
        __HAL_RCC_TIM1_CLK_ENABLE();

        __HAL_RCC_GPIOE_CLK_ENABLE();
        /**TIM1 GPIO Configuration
        PE15     ------> TIM1_BKIN
        */
        GPIO_InitStruct.Pin = GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

        /* TIM1 interrupt Init */
        HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
        HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
        HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
        HAL_NVIC_SetPriority(TIM1_CC_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
    }
    else if(tim_baseHandle->Instance==TIM8)
    {
        /* TIM8 clock enable */
        __HAL_RCC_TIM8_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**TIM8 GPIO Configuration
        PA6     ------> TIM8_BKIN
        */
        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* TIM8 interrupt Init */
        HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
        HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
        HAL_NVIC_SetPriority(TIM8_TRG_COM_TIM14_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);
        HAL_NVIC_SetPriority(TIM8_CC_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM8_CC_IRQn);
    }
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle)
{
    if(tim_pwmHandle->Instance==TIM9)
    {
        /* TIM9 clock enable */
        __HAL_RCC_TIM9_CLK_ENABLE();

        /* TIM9 interrupt Init */
        HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
    }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(timHandle->Instance==TIM1)
    {
        __HAL_RCC_GPIOE_CLK_ENABLE();
        /**TIM1 GPIO Configuration
        PE9     ------> TIM1_CH1
        PE11     ------> TIM1_CH2
        PE13     ------> TIM1_CH3
        PE14     ------> TIM1_CH4
        */
        GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_14;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    }
    else if(timHandle->Instance==TIM8)
    {
        __HAL_RCC_GPIOC_CLK_ENABLE();
        /**TIM8 GPIO Configuration
        PC6     ------> TIM8_CH1
        PC7     ------> TIM8_CH2
        PC8     ------> TIM8_CH3
        PC9     ------> TIM8_CH4
        */
        GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    }
    else if(timHandle->Instance==TIM9)
    {
        __HAL_RCC_GPIOE_CLK_ENABLE();
        /**TIM9 GPIO Configuration
        PE5     ------> TIM9_CH1
        PE6     ------> TIM9_CH2
        */
        GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF3_TIM9;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{
    if(tim_baseHandle->Instance==TIM1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_TIM1_CLK_DISABLE();

        /**TIM1 GPIO Configuration
        PE9     ------> TIM1_CH1
        PE11     ------> TIM1_CH2
        PE13     ------> TIM1_CH3
        PE14     ------> TIM1_CH4
        PE15     ------> TIM1_BKIN
        */
        HAL_GPIO_DeInit(GPIOE, GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

        /* TIM1 interrupt Deinit */
        /* USER CODE BEGIN TIM1:TIM1_BRK_TIM9_IRQn disable */
        /**
        * Uncomment the line below to disable the "TIM1_BRK_TIM9_IRQn" interrupt
        * Be aware, disabling shared interrupt may affect other IPs
        */
        /* HAL_NVIC_DisableIRQ(TIM1_BRK_TIM9_IRQn); */
        /* USER CODE END TIM1:TIM1_BRK_TIM9_IRQn disable */

        HAL_NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
        HAL_NVIC_DisableIRQ(TIM1_TRG_COM_TIM11_IRQn);
        HAL_NVIC_DisableIRQ(TIM1_CC_IRQn);
    }
    else if(tim_baseHandle->Instance==TIM8)
    {
        /* Peripheral clock disable */
        __HAL_RCC_TIM8_CLK_DISABLE();

        /**TIM8 GPIO Configuration
        PA6     ------> TIM8_BKIN
        PC6     ------> TIM8_CH1
        PC7     ------> TIM8_CH2
        PC8     ------> TIM8_CH3
        PC9     ------> TIM8_CH4
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6);

        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);

        /* TIM8 interrupt Deinit */
        HAL_NVIC_DisableIRQ(TIM8_BRK_TIM12_IRQn);
        HAL_NVIC_DisableIRQ(TIM8_UP_TIM13_IRQn);
        HAL_NVIC_DisableIRQ(TIM8_TRG_COM_TIM14_IRQn);
        HAL_NVIC_DisableIRQ(TIM8_CC_IRQn);
    }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_pwmHandle)
{
    if(tim_pwmHandle->Instance==TIM9)
    {
        /* Peripheral clock disable */
        __HAL_RCC_TIM9_CLK_DISABLE();

        /* TIM9 interrupt Deinit */
        /* USER CODE BEGIN TIM9:TIM1_BRK_TIM9_IRQn disable */
        /**
        * Uncomment the line below to disable the "TIM1_BRK_TIM9_IRQn" interrupt
        * Be aware, disabling shared interrupt may affect other IPs
        */
        /* HAL_NVIC_DisableIRQ(TIM1_BRK_TIM9_IRQn); */
        /* USER CODE END TIM9:TIM1_BRK_TIM9_IRQn disable */
    }
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    //printk("TIM1_BRK_TIM9_IRQHandler\n");
    HAL_TIM_IRQHandler(&htim1);
}

void TIM1_UP_TIM10_IRQHandler(void)
{
    printk("TIM1_UP_TIM10_IRQHandler\n");
    HAL_TIM_IRQHandler(&htim1);
}

void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
    printk("TIM1_TRG_COM_TIM11_IRQHandler\n");
    HAL_TIM_IRQHandler(&htim1);
}

void TIM1_CC_IRQHandler(void)
{
    //printk("TIM1_CC_IRQHandler\n");
    HAL_TIM_IRQHandler(&htim1);
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
    printk("TIM8_BRK_TIM12_IRQHandler\n");
    HAL_TIM_IRQHandler(&htim8);
}

/**
  * @brief This function handles TIM8 update interrupt and TIM13 global interrupt.
  */
void TIM8_UP_TIM13_IRQHandler(void)
{
    printk("TIM8_UP_TIM13_IRQHandler\n");
    HAL_TIM_IRQHandler(&htim8);
}

/**
  * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
    printk("TIM8_TRG_COM_TIM14_IRQHandler\n");
    HAL_TIM_IRQHandler(&htim8);
}

/**
  * @brief This function handles TIM8 capture compare interrupt.
  */
void TIM8_CC_IRQHandler(void)
{
    //printk("TIM8_CC_IRQHandler\n");
    HAL_TIM_IRQHandler(&htim8);
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    //printk("HAL_TIM_OC_DelayElapsedCallback\n");
    uint32_t g_count_val = 0;
    if(htim == &htim1){
        g_count_val = __HAL_TIM_GET_COUNTER(&htim1);
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (g_count_val + high_ctrl_motor.ccr) % 0xFFFF); // 
            com_smd_count_add_quick(&high_ctrl_motor);
        }
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (g_count_val + length_ctrl_motor.ccr) % 0xFFFF); // 
            com_smd_count_add_quick(&length_ctrl_motor);
        }
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (g_count_val + angle_ctrl_motor.ccr) % 0xFFFF); // 
            com_smd_count_add_quick(&angle_ctrl_motor);
        }
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4){
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, (g_count_val + turntable_ctrl_motor.ccr) % 0xFFFF); // 
            com_smd_count_add_quick(&turntable_ctrl_motor);
        }
    } else if(htim == &htim8){

    } else if(htim == &htim9){
        g_count_val = __HAL_TIM_GET_COUNTER(&htim9);
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
            __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, (g_count_val + timer9_ch1.ccr) % 0xFFFF); // 
            com_smd_count_add_quick(&timer9_ch1);
        }
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
            __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, (g_count_val + timer9_ch2.ccr) % 0xFFFF); // 
            com_smd_count_add_quick(&timer9_ch2);
        }
    }
}

void drv_pwm_init(void)
{
    printk("start init pwm\n");
    //crtl_pwm_init();

    //__HAL_RCC_GPIOE_CLK_ENABLE();
    MX_TIM1_Init();
    MX_TIM8_Init();
    MX_TIM9_Init();

    IRQ_CONNECT(TIM1_BRK_TIM9_IRQn, 0, TIM1_BRK_TIM9_IRQHandler, 0, 0);
    //irq_enable(TIM1_BRK_TIM9_IRQn);
    IRQ_CONNECT(TIM1_UP_TIM10_IRQn, 0, TIM1_UP_TIM10_IRQHandler, 0, 0);
    irq_enable(TIM1_UP_TIM10_IRQn);
    IRQ_CONNECT(TIM1_TRG_COM_TIM11_IRQn, 0, TIM1_TRG_COM_TIM11_IRQHandler, 0, 0);
    irq_enable(TIM1_TRG_COM_TIM11_IRQn);
    IRQ_CONNECT(TIM1_CC_IRQn, 0, TIM1_CC_IRQHandler, 0, 0);
    irq_enable(TIM1_CC_IRQn);

    IRQ_CONNECT(TIM8_BRK_TIM12_IRQn, 0, TIM8_BRK_TIM12_IRQHandler, 0, 0);
    irq_enable(TIM8_BRK_TIM12_IRQn);
    IRQ_CONNECT(TIM8_UP_TIM13_IRQn, 0, TIM8_UP_TIM13_IRQHandler, 0, 0);
    irq_enable(TIM8_UP_TIM13_IRQn);
    IRQ_CONNECT(TIM8_TRG_COM_TIM14_IRQn, 0, TIM8_TRG_COM_TIM14_IRQHandler, 0, 0);
    irq_enable(TIM8_TRG_COM_TIM14_IRQn);
    IRQ_CONNECT(TIM8_CC_IRQn, 0, TIM8_CC_IRQHandler, 0, 0);
    irq_enable(TIM8_CC_IRQn);

    //HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, high_ctrl_motor.ccr);
    //HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, length_ctrl_motor.ccr);
    //HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, angle_ctrl_motor.ccr);
    //HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, turntable_ctrl_motor.ccr);

    printk("finish init pwm\n");
}