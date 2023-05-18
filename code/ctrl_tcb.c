#include <zephyr/sys/printk.h>
#include <string.h>

#include "ctrl_tcb.h"
#include "drv_tcb.h"

#include "../../../../common/com_error/com_error.h"
#include "../../../../common/com_algorithm/motor/stepper/com_smd.h"

void ctrl_tcb_init(void)
{
    drv_tcb_init();//初始化
}

void ctrl_tcb_run(void)
{
    drv_tcb_run();//启动
}

void ctrl_tcb_stop(void)
{
    drv_tcb_stop();//停止
}
