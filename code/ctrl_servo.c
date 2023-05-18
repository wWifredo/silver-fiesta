#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <string.h>

#include "ctrl_servo.h"

#include "../../../../common/com_error/com_error.h"

#include <stm32f407xx.h>
extern TIM_HandleTypeDef htim8;

static dev_servo_type_t dev1;
static dev_servo_type_t dev2;
static dev_servo_type_t dev3;
static dev_servo_type_t dev4;

int servo1_set_angle(float angle)
{
    int res;
    uint32_t val;

    res = dev_servo_angle_2_timer(&dev1,angle,&val);
    if(res == COM_SUCCESS){
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,val);
    }

    return COM_SUCCESS;
}

int servo2_set_angle(float angle)
{
    int res;
    uint32_t val;

    res = dev_servo_angle_2_timer(&dev2,angle,&val);
    if(res == COM_SUCCESS){
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,val);
    }

    return COM_SUCCESS;
}

int servo3_set_angle(float angle)
{
    int res;
    uint32_t val;

    res = dev_servo_angle_2_timer(&dev3,angle,&val);
    if(res == COM_SUCCESS){
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,val);
    }

    return COM_SUCCESS;
}

int servo4_set_angle(float angle)
{
    int res;
    uint32_t val;

    res = dev_servo_angle_2_timer(&dev4,angle,&val);
    if(res == COM_SUCCESS){
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,val);
    }

    return COM_SUCCESS;
}
void ctrl_servo_init(void)
{
    printk("ctrl_servo_init\n");
    COM_ERROR_CHECK(dev_servo_init(&dev1,500,2000,0.0f,270.0f));
    COM_ERROR_CHECK(dev_servo_init(&dev2,500,2000,0.0f,270.0f));
    COM_ERROR_CHECK(dev_servo_init(&dev3,500,2000,0.0f,270.0f));
    COM_ERROR_CHECK(dev_servo_init(&dev4,500,2000,0.0f,270.0f));

    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);

    servo1_set_angle(0);
    servo2_set_angle(0);
    servo3_set_angle(0);
    servo4_set_angle(0);
}