#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include <string.h>

#include "drv_oled_io.h"

// oleddc0
#define OLED_DC0_NODE DT_ALIAS(oleddc0)
static const struct gpio_dt_spec oleddc0 = GPIO_DT_SPEC_GET(OLED_DC0_NODE, gpios);
// oledres0
#define OLED_RES0_NODE DT_ALIAS(oledres0)
static const struct gpio_dt_spec oledres0 = GPIO_DT_SPEC_GET(OLED_RES0_NODE, gpios);

void drv_oled_io_init(void)
{
    int ret;

	// oleddc0
	if (!device_is_ready(oleddc0.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&oleddc0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	// oledres0
	if (!device_is_ready(oledres0.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&oledres0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}
}

void drv_oled_dc_set(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&oleddc0, !!val);
	if (ret < 0) {
		printk("set oleddc0 value fail\n");
	}
}

void drv_oled_res_set(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&oledres0, !!val);
	if (ret < 0) {
		printk("set oledres0 value fail\n");
	}
}
