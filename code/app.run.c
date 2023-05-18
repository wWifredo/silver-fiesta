#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <string.h>

#include "app_run.h"
#include "../../../../common/com_error/com_error.h"

#include "data_sys.h"
#include "drv_key.h"
#include "ctrl_tcb.h"
#include "prot_feetech.h"
#include "ctrl_oled.h"
#include "ctrl_pwm.h"
#include "drv_motor_io.h"
#include "ctrl_servo.h"

#define STACKSIZE 512               ///< size of stack area used by each thread
#define PRIORITY CONFIG_NUM_PREEMPT_PRIORITIES  ///< scheduling priority used by each thread
static k_tid_t sys_k_tid = 0;       ///< thread ID
static int dev_index = 0;
#define TOTAL_MANUAL_CTRL_DEV 4     ///< 0-high; 1-length; 2-angle; 3-turntable
static int manual_adj_tick = 1;


 void set_st3_initial_position(void)
{
    const float initial_angle = 180.0f; // 设置初始角度为45度
    com_smd_set_step_angle(&length_ctrl_motor, initial_angle);
}
void button1_pressed_proc(void)
{
    if(data_sys_node.run_state != RUN_STATE_AUTO_RUN){
        change_run_state(RUN_STATE_AUTO_RUN);
        ctrl_tcb_run();
        set_st3_initial_position(); // 在自动控制开始之前设置ST2电机的初始位置
    } else {
        change_run_state(RUN_STATE_MANUAL_RUN);
        ctrl_tcb_stop();
        k_thread_suspend(sys_k_tid);
    }
}

void button2_pressed_proc(void)
{
    //printk("button2 pressed app!\n");
    switch(dev_index){
        // high
        case 0:
            drv_set_motor_st1_dir(0);
            com_smd_set_step_angle(&high_ctrl_motor,360.0f*manual_adj_tick);
        break;
        // length
        case 1:
            drv_set_motor_st2_dir(0);
            com_smd_set_step_angle(&length_ctrl_motor,360.0f*manual_adj_tick);
        break;
        case 2:
            drv_set_motor_st3_dir(0);
            com_smd_set_step_angle(&angle_ctrl_motor,1.0f*manual_adj_tick);
        break;
        case 4:
            drv_set_motor_st4_dir(0);
            com_smd_set_step_angle(&turntable_ctrl_motor,1.0f*manual_adj_tick);
        break;
        default:
        break;
    }
}

void button3_pressed_proc(void)
{
    //printk("button3 pressed app!\n");
    switch(dev_index){
        // high
        case 0:
            drv_set_motor_st1_dir(1);
            com_smd_set_step_angle(&high_ctrl_motor,360.0f*manual_adj_tick);
        break;
        // length
        case 1:
            drv_set_motor_st2_dir(1);
            com_smd_set_step_angle(&length_ctrl_motor,360.0f*manual_adj_tick);
        break;
        case 2:
            drv_set_motor_st3_dir(1);
            com_smd_set_step_angle(&angle_ctrl_motor,1.0f*manual_adj_tick);
        break;
        case 4:
            drv_set_motor_st4_dir(1);
            com_smd_set_step_angle(&turntable_ctrl_motor,1.0f*manual_adj_tick);
        break;
        default:
        break;
    }
}

void button4_pressed_proc(void)
{
    //printk("button4 pressed app!\n");
    switch(manual_adj_tick){
        case 1:
            manual_adj_tick = 5;
        break;
        case 5:
            manual_adj_tick = 10;
        break;
        case 10:
            manual_adj_tick = 1;
        break;
        default:
            manual_adj_tick = 1;
        break;
    }
    COM_ERROR_CHECK(com_spi_lcd_dev_show_string(&lcd_dev,72,4,"    ",FontSize_16,1));
    COM_ERROR_CHECK(com_spi_lcd_dev_show_uint32_num(&lcd_dev,72,4,manual_adj_tick, FontSize_16,1));
}

void start_key_pressed_proc(void)
{
    //printk("start_key pressed app!\n");
    if(data_sys_node.run_state != RUN_STATE_AUTO_RUN){
        change_run_state(RUN_STATE_AUTO_RUN);
        ctrl_tcb_run();
    } else {
        change_run_state(RUN_STATE_MANUAL_RUN);
        ctrl_tcb_stop();
        k_thread_suspend(sys_k_tid);
    }
}

void ptonc0_pressed_proc(void)
{
    printk("ptonc0 pressed app!\n");
    if(data_sys_node.part_seq_cfg == PART_SEQ_0){
        printk("ptono0_pressed_proc wrong seq_cfg\n");
        return;
    }

    if(data_sys_node.part_seq >= 3){
        printk("ptono0_pressed_proc wrong seq\n");
        return;
    }

    if(data_sys_node.run_state != RUN_STATE_AUTO_RUN){
        printk("ptono0_pressed_proc wrong state\n");
        return;
    }

    k_thread_resume(sys_k_tid);
}

void app_run_init(void)
{
    COM_ERROR_CHECK(com_spi_lcd_dev_show_string(&lcd_dev,0,0,"cfg_num:",FontSize_16,1));
    COM_ERROR_CHECK(com_spi_lcd_dev_show_char(&lcd_dev,64,0,0x30+data_sys_node.part_seq_cfg,FontSize_16,1));
    COM_ERROR_CHECK(com_spi_lcd_dev_show_string(&lcd_dev,0,2,"dev_num:",FontSize_16,1));
    COM_ERROR_CHECK(com_spi_lcd_dev_show_char(&lcd_dev,64,2,0x30 + dev_index, FontSize_16,1));
    COM_ERROR_CHECK(com_spi_lcd_dev_show_string(&lcd_dev,0,4,"tick_num:",FontSize_16,1));
    COM_ERROR_CHECK(com_spi_lcd_dev_show_uint32_num(&lcd_dev,72,4,manual_adj_tick, FontSize_16,1));
    feetech_write_action_cmd(0x01,2800);
    servo1_set_angle(0);
}

/**
* @brief app_run task
*/
void app_run_task( void )
{
    uint8_t pos_index = 0;
    uint8_t i;
    uint8_t part_seq_cfg;

    sys_k_tid = k_current_get();
    if(!sys_k_tid){
        printk("get sys app_run k_tid fail\n");
    } else {
        //printk("get sys wwdg k_tid = %d\n",(int)sys_k_tid);
    }
    k_thread_suspend(sys_k_tid);
    while (1) {
        part_seq_cfg = data_sys_node.part_seq_cfg - 1;
         com_smd_set_step_angle(&length_ctrl_motor, 90.0f);
        k_msleep(5);

        // find a place
        for(i = 0; i < 8; i++){
            if((rotary_tab_seq_table[i] == part_seq_table[part_seq_cfg][data_sys_node.part_seq]) && rotary_tab_fill_table[i] == 0){
                pos_index = i;
                break;
            }
        }
        printk("app pos = %d\n",i);
        // no position
        if(i >= 8){
            // discard part
            // TODO
            ctrl_tcb_run();
            k_thread_suspend(sys_k_tid);
        } else {
            // turntable rotate
            // TODO

            switch(part_seq_table[part_seq_cfg][data_sys_node.part_seq]){
                case PART_TYPE_CIRCLE:
                    k_msleep(30);
                    ctrl_tcb_stop();
                    feetech_write_action_cmd(0x01,0);
                    k_msleep(30);
                    // rotate
                    k_msleep(3000);
                    // place
                    feetech_write_action_cmd(0x01,2800);
                    k_msleep(1000);
                    // rotate
                    k_msleep(3000);
                break;
                case PART_TYPE_SQUARE:
                break;
                case PART_TYPE_TRIANGLE:
                break;
                default:
                break;
            }

            data_sys_node.part_seq++;
            if(data_sys_node.part_seq >= 3){
                data_sys_node.part_seq = 0;
            }
            ctrl_tcb_run();
            printk("app end\n");
            k_thread_suspend(sys_k_tid);
        }
        
        k_msleep(5);
    }
}

/**
* @brief app_run thread define.
*/
K_THREAD_DEFINE(app_run_task_id, STACKSIZE, app_run_task, NULL, NULL, NULL, PRIORITY, 0, 0);