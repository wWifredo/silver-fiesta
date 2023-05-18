/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include <string.h>
#include "../../../../common/com_error/com_error.h"

#include "drv_beep.h"
#include "drv_pwm.h"
#include "drv_key.h"
#include "drv_uart.h"

#include "ctrl_servo.h"
#include "ctrl_pwm.h"
#include "ctrl_tcb.h"
#include "data_sys.h"
#include "ctrl_oled.h"
#include "ctrl_cfg.h"

#include "app_run.h"

#include "prot_feetech.h"

#define SLEEP_TIME_MS   200
//static uint8_t tmp_data[8];

void main(void)
{
    // power up
	printk("power up\n");
    data_sys_init();
    change_run_state(RUN_STATE_POWER_UP);

    // init
    printk("init start\n");
    change_run_state(RUN_STATE_INIT);
    cam_uart_init();
    uart2_init();
    ctrl_uart_init();
    ctrl_tcb_init();
    drv_beep_init();
    crtl_pwm_init();
    drv_pwm_init();
    ctrl_servo_init();
    drv_key_init();
    
	//cam_uart_print("cam_uart_print");
    //uart2_print("uart2_print");
    //ctrl_uart_print("ctrl_uart_init");
	
    ctrl_oled_init();
    k_msleep(20);
    ctrl_cfg_init();
    printk("p1 init done\n");

    app_run_init();
    printk("p2 init done\n");

    // proc for init done
    change_run_state(RUN_STATE_MANUAL_RUN);
    // tmp_data[0] = 0xFF;
    // tmp_data[1] = 0xFF;
    // tmp_data[2] = 0x01;
    // tmp_data[3] = 0x04;
    // tmp_data[4] = 0x02;
    // tmp_data[5] = 0x00;
    // tmp_data[6] = 0x09;
    // tmp_data[7] = 0xEF;

    //tmp_data[0] = 0x0A;
    //tmp_data[1] = 0xE0;
    //ctrl_uart_transmit(tmp_data,8);
    //feetech_write_data_cmd(1,0x2A,tmp_data,2);
    // feetech_send_ping_cmd(01);
    // k_msleep(SLEEP_TIME_MS);
    // feetech_send_ping_cmd(01);
    // k_msleep(SLEEP_TIME_MS);
    // feetech_send_ping_cmd(01);

    //feetech_write_action_cmd(0x01,2800);

	while (1) {
		k_msleep(SLEEP_TIME_MS);
	}
}

void com_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
	printk("error: err_code = %d, file = %s, line = %d \n", error_code, p_file_name, line_num);
}

// void key1_pressed_proc(void)
// {
//     printk("key1 pressed main\n");
// }