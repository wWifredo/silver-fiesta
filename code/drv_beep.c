#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include <string.h>

#include "drv_beep.h"

/* size of stack area used by each thread */
#define STACKSIZE 512

/* scheduling priority used by each thread */
#define PRIORITY 8

// LED
#define BEEP0_NODE DT_ALIAS(beep0)
static const struct gpio_dt_spec beep0 = GPIO_DT_SPEC_GET(BEEP0_NODE, gpios);

void drv_beep_init(void)
{
    int ret;

	// beep0
	if (!device_is_ready(beep0.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&beep0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	drv_beep_flick(200);
}

void drv_beep_turn_on(void)
{
	int ret;
	ret = gpio_pin_set_dt(&beep0, 1);
	if (ret < 0) {
		printk("set beep value fail\n");
	}
}

void drv_beep_turn_off(void)
{
	int ret;
	ret = gpio_pin_set_dt(&beep0, 0);
	if (ret < 0) {
		printk("set beep value fail\n");
	}
}

void drv_beep_flick(int ms)
{
	int ret;
	ret = gpio_pin_set_dt(&beep0, 1);
	if (ret < 0) {
		printk("set beep value fail\n");
	}

	k_msleep(ms);

	ret = gpio_pin_set_dt(&beep0, 0);
	if (ret < 0) {
		printk("set beep value fail\n");
	}
}
