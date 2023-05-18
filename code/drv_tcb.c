#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include <string.h>

#include "drv_tcb.h"

// tcbctrl0
#define TCB0_NODE DT_ALIAS(tcbctrl0)
static const struct gpio_dt_spec tcbctrl0 = GPIO_DT_SPEC_GET(TCB0_NODE, gpios);

void drv_tcb_init(void)
{
    int ret;

	// tcbctrl0
	if (!device_is_ready(tcbctrl0.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&tcbctrl0, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}
}

void drv_tcb_run(void)
{
	int ret;
	ret = gpio_pin_set_dt(&tcbctrl0, 0);
	if (ret < 0) {
		printk("set tcbctrl0 value fail\n");
	}
}

void drv_tcb_stop(void)
{
	int ret;
	ret = gpio_pin_set_dt(&tcbctrl0, 1);
	if (ret < 0) {
		printk("set tcbctrl0 value fail\n");
	}
}
