#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include <string.h>

#include "drv_led.h"

/* size of stack area used by each thread */
#define STACKSIZE 512

/* scheduling priority used by each thread */
#define PRIORITY 8

// LED
#define SYSLED_NODE DT_ALIAS(sysled)
static const struct gpio_dt_spec sysled = GPIO_DT_SPEC_GET(SYSLED_NODE, gpios);

#define LED1_NODE DT_ALIAS(led1)
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

#define LED2_NODE DT_ALIAS(led2)
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

#define LED3_NODE DT_ALIAS(led3)
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

#define LED4_NODE DT_ALIAS(led4)
static const struct gpio_dt_spec led4 = GPIO_DT_SPEC_GET(LED4_NODE, gpios);

void drv_led_init(void)
{
    int ret;

	// sysled
	if (!device_is_ready(sysled.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&sysled, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	// led1
	if (!device_is_ready(led1.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	// led2
	if (!device_is_ready(led2.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	// led3
	if (!device_is_ready(led3.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led3, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	// led4
	if (!device_is_ready(led4.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led4, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}
}

void sys_led_task( void )
{
	int ret;
	printk("LED init\n");
	drv_led_init();
	
    while (1) {
        ret = gpio_pin_toggle_dt(&sysled);
		if (ret < 0) {
			return;
		}
        k_msleep(400);
    }
}


K_THREAD_DEFINE(led_task_id, STACKSIZE, sys_led_task, NULL, NULL, NULL, PRIORITY, 0, 0);