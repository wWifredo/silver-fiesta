#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include "ctrl_pwm.h"
#include <string.h>
#include "drv_motor_io.h"
#include <stm32f407xx.h>

#include "../../../../../common/com_error/com_error.h"

com_smd_dev_t high_ctrl_motor;			// timer1_ch1
com_smd_dev_t length_ctrl_motor;		// timer1_ch2
com_smd_dev_t angle_ctrl_motor;			// timer1_ch3
com_smd_dev_t turntable_ctrl_motor;		// timer1_ch4旋转台控制电机

com_smd_dev_t timer9_ch1;
com_smd_dev_t timer9_ch2;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim9;

// timer1 ch1
static int high_ctrl_motor_dir_cb(uint8_t dir)
{
    drv_set_motor_st1_dir(dir);
    return COM_SUCCESS;
}

static int high_ctrl_motor_en_cb(uint8_t enable)
{
    drv_set_motor_st1_en(!enable);
    return COM_SUCCESS;
}

static int high_ctrl_motor_set_speed_cb(uint32_t ccr)
{
    // do nothing
    return COM_SUCCESS;
}

static int high_ctrl_motor_set_pos_cb(uint32_t edge_count)
{
    // do nothing
    return COM_SUCCESS;
}

static int high_ctrl_motor_set_state_cb(com_smd_state_code_t state)
{
    switch(state){
        case COM_SMD_STATE_START:
            HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_1);
        break;
        case COM_SMD_STATE_STOP:
            HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_1);
        break;
        default:
            HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_1);
        break;
    }
    return COM_SUCCESS;
}

// timer1 ch2
static int length_ctrl_motor_dir_cb(uint8_t dir)
{
    drv_set_motor_st2_dir(dir);
    return COM_SUCCESS;
}

static int length_ctrl_motor_en_cb(uint8_t enable)
{
    drv_set_motor_st2_en(!enable);
    return COM_SUCCESS;
}

static int length_ctrl_motor_set_speed_cb(uint32_t ccr)
{
    // do nothing
    return COM_SUCCESS;
}

static int length_ctrl_motor_set_pos_cb(uint32_t edge_count)
{
    // do nothing
    return COM_SUCCESS;
}

static int length_ctrl_motor_set_state_cb(com_smd_state_code_t state)
{
    switch(state){
        case COM_SMD_STATE_START:
            printk("tim1_ch2 start!\n");
            HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_2);
        break;
        case COM_SMD_STATE_STOP:
            printk("tim1_ch2 stop!\n");
            HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_2);
        break;
        default:
            HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_2);
        break;
    }
    return COM_SUCCESS;
}

// timer1 ch3
static int angle_ctrl_motor_dir_cb(uint8_t dir)
{
    drv_set_motor_st3_dir(dir);
    return COM_SUCCESS;
}

static int angle_ctrl_motor_en_cb(uint8_t enable)
{
    drv_set_motor_st3_en(!enable);
    return COM_SUCCESS;
}

static int angle_ctrl_motor_set_speed_cb(uint32_t ccr)
{
    // do nothing
    return COM_SUCCESS;
}

static int angle_ctrl_motor_set_pos_cb(uint32_t edge_count)
{
    // do nothing
    return COM_SUCCESS;
}

static int angle_ctrl_motor_set_state_cb(com_smd_state_code_t state)
{
    switch(state){
        case COM_SMD_STATE_START:
            //printk("tim1_ch3 start!\n");
            HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_3);
        break;
        case COM_SMD_STATE_STOP:
            //printk("tim1_ch3 stop!\n");
            HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_3);
        break;
        default:
            HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_3);
        break;
    }
    return COM_SUCCESS;
}

// timer1 ch4
static int turntable_ctrl_motor_dir_cb(uint8_t dir)
{
    drv_set_motor_st4_dir(dir);
    return COM_SUCCESS;
}

static int turntable_ctrl_motor_en_cb(uint8_t enable)
{
    drv_set_motor_st4_en(!enable);
    return COM_SUCCESS;
}

static int turntable_ctrl_motor_set_speed_cb(uint32_t ccr)
{
    // do nothing
    return COM_SUCCESS;
}

static int turntable_ctrl_motor_set_pos_cb(uint32_t edge_count)
{
    // do nothing
    return COM_SUCCESS;
}

static int turntable_ctrl_motor_set_state_cb(com_smd_state_code_t state)
{
    switch(state){
        case COM_SMD_STATE_START:
            HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_4);
        break;
        case COM_SMD_STATE_STOP:
            HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_4);
        break;
        default:
            HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_4);
        break;
    }
    return COM_SUCCESS;
}

// timer9 ch1
static int timer9_ch1_dir_cb(uint8_t dir)
{
    drv_set_motor_st5_dir(dir);
    return COM_SUCCESS;
}

static int timer9_ch1_en_cb(uint8_t enable)
{
    drv_set_motor_st5_en(!enable);
    return COM_SUCCESS;
}

static int timer9_ch1_set_speed_cb(uint32_t ccr)
{
    // do nothing
    return COM_SUCCESS;
}

static int timer9_ch1_set_pos_cb(uint32_t edge_count)
{
    // do nothing
    return COM_SUCCESS;
}

static int timer9_ch1_set_state_cb(com_smd_state_code_t state)
{
    switch(state){
        case COM_SMD_STATE_START:
            HAL_TIM_OC_Start_IT(&htim9, TIM_CHANNEL_1);
        break;
        case COM_SMD_STATE_STOP:
            HAL_TIM_OC_Stop_IT(&htim9, TIM_CHANNEL_1);
        break;
        default:
            HAL_TIM_OC_Stop_IT(&htim9, TIM_CHANNEL_1);
        break;
    }
    return COM_SUCCESS;
}

// timer9 ch2
static int timer9_ch2_dir_cb(uint8_t dir)
{
    drv_set_motor_st6_dir(dir);
    return COM_SUCCESS;
}

static int timer9_ch2_en_cb(uint8_t enable)
{
    drv_set_motor_st6_en(!enable);
    return COM_SUCCESS;
}

static int timer9_ch2_set_speed_cb(uint32_t ccr)
{
    // do nothing
    return COM_SUCCESS;
}

static int timer9_ch2_set_pos_cb(uint32_t edge_count)
{
    // do nothing
    return COM_SUCCESS;
}

static int timer9_ch2_set_state_cb(com_smd_state_code_t state)
{
    switch(state){
        case COM_SMD_STATE_START:
            HAL_TIM_OC_Start_IT(&htim9, TIM_CHANNEL_2);
        break;
        case COM_SMD_STATE_STOP:
            HAL_TIM_OC_Stop_IT(&htim9, TIM_CHANNEL_2);
        break;
        default:
            HAL_TIM_OC_Stop_IT(&htim9, TIM_CHANNEL_2);
        break;
    }
    return COM_SUCCESS;
}

void crtl_pwm_init(void)
{
    drv_motor_io_init();

    COM_ERROR_CHECK(com_smd_init(&high_ctrl_motor,4,1.8f,1000000));
    COM_ERROR_CHECK(com_smd_cfg_cb(&high_ctrl_motor,high_ctrl_motor_dir_cb,high_ctrl_motor_en_cb,high_ctrl_motor_set_speed_cb,high_ctrl_motor_set_pos_cb,high_ctrl_motor_set_state_cb));

    COM_ERROR_CHECK(com_smd_init(&length_ctrl_motor,4,1.8f,1000000));
    COM_ERROR_CHECK(com_smd_cfg_cb(&length_ctrl_motor,length_ctrl_motor_dir_cb,length_ctrl_motor_en_cb,length_ctrl_motor_set_speed_cb,length_ctrl_motor_set_pos_cb,length_ctrl_motor_set_state_cb));

    COM_ERROR_CHECK(com_smd_init(&angle_ctrl_motor,4,1.8f,1000000));
    COM_ERROR_CHECK(com_smd_cfg_cb(&angle_ctrl_motor,angle_ctrl_motor_dir_cb,angle_ctrl_motor_en_cb,angle_ctrl_motor_set_speed_cb,angle_ctrl_motor_set_pos_cb,angle_ctrl_motor_set_state_cb));

    COM_ERROR_CHECK(com_smd_init(&turntable_ctrl_motor,4,1.8f,1000000));
    COM_ERROR_CHECK(com_smd_cfg_cb(&turntable_ctrl_motor,turntable_ctrl_motor_dir_cb,turntable_ctrl_motor_en_cb,turntable_ctrl_motor_set_speed_cb,turntable_ctrl_motor_set_pos_cb,turntable_ctrl_motor_set_state_cb));

    COM_ERROR_CHECK(com_smd_init(&timer9_ch1,4,1.8f,1000000));
    COM_ERROR_CHECK(com_smd_cfg_cb(&timer9_ch1,timer9_ch1_dir_cb,timer9_ch1_en_cb,timer9_ch1_set_speed_cb,timer9_ch1_set_pos_cb,timer9_ch1_set_state_cb));

    COM_ERROR_CHECK(com_smd_init(&timer9_ch2,4,1.8f,1000000));
    COM_ERROR_CHECK(com_smd_cfg_cb(&timer9_ch2,timer9_ch2_dir_cb,timer9_ch2_en_cb,timer9_ch2_set_speed_cb,timer9_ch2_set_pos_cb,timer9_ch2_set_state_cb));

    COM_ERROR_CHECK(com_smd_set_en(&high_ctrl_motor,1));//控制电机运行  
    COM_ERROR_CHECK(com_smd_set_dir(&high_ctrl_motor,0));//控制电机方向
    COM_ERROR_CHECK(com_smd_set_en(&length_ctrl_motor,1));
    COM_ERROR_CHECK(com_smd_set_dir(&length_ctrl_motor,0));
    COM_ERROR_CHECK(com_smd_set_en(&angle_ctrl_motor,1));
    COM_ERROR_CHECK(com_smd_set_dir(&angle_ctrl_motor,0));
    COM_ERROR_CHECK(com_smd_set_en(&turntable_ctrl_motor,1));
    COM_ERROR_CHECK(com_smd_set_dir(&turntable_ctrl_motor,0));
    COM_ERROR_CHECK(com_smd_set_en(&timer9_ch1,1));
    COM_ERROR_CHECK(com_smd_set_dir(&timer9_ch1,0));
    COM_ERROR_CHECK(com_smd_set_en(&timer9_ch2,1));
    COM_ERROR_CHECK(com_smd_set_dir(&timer9_ch2,0));

    COM_ERROR_CHECK(com_smd_set_speed_rpm(&high_ctrl_motor,120));
    COM_ERROR_CHECK(com_smd_set_speed_rpm(&length_ctrl_motor,120));
    COM_ERROR_CHECK(com_smd_set_speed_rpm(&angle_ctrl_motor,240));
    COM_ERROR_CHECK(com_smd_set_speed_rpm(&turntable_ctrl_motor,360));
    COM_ERROR_CHECK(com_smd_set_speed_rpm(&timer9_ch1,120));
    COM_ERROR_CHECK(com_smd_set_speed_rpm(&timer9_ch2,120));

    // printk("ch1 ccr = %d\n",high_ctrl_motor.ccr);
    // printk("ch2 ccr = %d\n",length_ctrl_motor.ccr);
    // printk("ch3 ccr = %d\n",angle_ctrl_motor.ccr);
    // printk("ch4 ccr = %d\n",turntable_ctrl_motor.ccr);
}
