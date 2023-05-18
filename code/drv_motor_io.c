#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include <string.h>

#include "drv_motor_io.h"

// st1
#define ST1EN0_NODE DT_ALIAS(st1en0)
static const struct gpio_dt_spec st1en0 = GPIO_DT_SPEC_GET(ST1EN0_NODE, gpios);
#define ST1DIR0_NODE DT_ALIAS(st1dir0)
static const struct gpio_dt_spec st1dir0 = GPIO_DT_SPEC_GET(ST1DIR0_NODE, gpios);
// st2
#define ST2EN0_NODE DT_ALIAS(st2en0)
static const struct gpio_dt_spec st2en0 = GPIO_DT_SPEC_GET(ST2EN0_NODE, gpios);
#define ST2DIR0_NODE DT_ALIAS(st2dir0)
static const struct gpio_dt_spec st2dir0 = GPIO_DT_SPEC_GET(ST2DIR0_NODE, gpios);
// st3
#define ST3EN0_NODE DT_ALIAS(st3en0)
static const struct gpio_dt_spec st3en0 = GPIO_DT_SPEC_GET(ST3EN0_NODE, gpios);
#define ST3DIR0_NODE DT_ALIAS(st3dir0)
static const struct gpio_dt_spec st3dir0 = GPIO_DT_SPEC_GET(ST3DIR0_NODE, gpios);
// st4
#define ST4EN0_NODE DT_ALIAS(st4en0)
static const struct gpio_dt_spec st4en0 = GPIO_DT_SPEC_GET(ST4EN0_NODE, gpios);
#define ST4DIR0_NODE DT_ALIAS(st4dir0)
static const struct gpio_dt_spec st4dir0 = GPIO_DT_SPEC_GET(ST4DIR0_NODE, gpios);

// st5
#define ST5EN0_NODE DT_ALIAS(st5en0)
static const struct gpio_dt_spec st5en0 = GPIO_DT_SPEC_GET(ST5EN0_NODE, gpios);
#define ST5DIR0_NODE DT_ALIAS(st5dir0)
static const struct gpio_dt_spec st5dir0 = GPIO_DT_SPEC_GET(ST5DIR0_NODE, gpios);
// st6
#define ST6EN0_NODE DT_ALIAS(st6en0)
static const struct gpio_dt_spec st6en0 = GPIO_DT_SPEC_GET(ST6EN0_NODE, gpios);
#define ST6DIR0_NODE DT_ALIAS(st6dir0)
static const struct gpio_dt_spec st6dir0 = GPIO_DT_SPEC_GET(ST6DIR0_NODE, gpios);

void drv_motor_io_init(void)
{
    int ret;

	// st1
	if (!device_is_ready(st1en0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st1en0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	if (!device_is_ready(st1dir0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st1dir0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	// st2
	if (!device_is_ready(st2en0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st2en0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	if (!device_is_ready(st2dir0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st2dir0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	// st3
	if (!device_is_ready(st3en0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st3en0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	if (!device_is_ready(st3dir0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st3dir0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	// st4
	if (!device_is_ready(st4en0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st4en0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	if (!device_is_ready(st4dir0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st4dir0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

    // st5
	if (!device_is_ready(st5en0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st5en0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	if (!device_is_ready(st5dir0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st5dir0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

    // st6
	if (!device_is_ready(st6en0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st6en0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}

	if (!device_is_ready(st6dir0.port)) {
		return;
	}
	ret = gpio_pin_configure_dt(&st6dir0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return;
	}
}

// st1
void drv_set_motor_st1_en(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st1en0, val);
	if (ret < 0) {
		printk("set st1en0 value fail\n");
	}
}

void drv_set_motor_st1_dir(uint8_t val)
{
	int ret;
	printk("set st1dir0 value = %d\n",val);
	ret = gpio_pin_set_dt(&st1dir0, val);
	if (ret < 0) {
		printk("set st1dir0 value fail\n");
	}
}

// st2
void drv_set_motor_st2_en(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st2en0, val);
	if (ret < 0) {
		printk("set st2en0 value fail\n");
	}
}

void drv_set_motor_st2_dir(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st2dir0, val);
	if (ret < 0) {
		printk("set st2dir0 value fail\n");
	}
}

// st3
void drv_set_motor_st3_en(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st3en0, val);
	if (ret < 0) {
		printk("set st3en0 value fail\n");
	}
}

void drv_set_motor_st3_dir(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st3dir0, val);
	if (ret < 0) {
		printk("set st3dir0 value fail\n");
	}
}

// st4
void drv_set_motor_st4_en(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st4en0, val);
	if (ret < 0) {
		printk("set st4en0 value fail\n");
	}
}

void drv_set_motor_st4_dir(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st4dir0, val);
	if (ret < 0) {
		printk("set st4dir0 value fail\n");
	}
}

// st5
void drv_set_motor_st5_en(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st5en0, val);
	if (ret < 0) {
		printk("set st5en0 value fail\n");
	}
}

void drv_set_motor_st5_dir(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st5dir0, val);
	if (ret < 0) {
		printk("set st5dir0 value fail\n");
	}
}

// st6
void drv_set_motor_st6_en(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st6en0, val);
	if (ret < 0) {
		printk("set st6en0 value fail\n");
	}
}

void drv_set_motor_st6_dir(uint8_t val)
{
	int ret;
	ret = gpio_pin_set_dt(&st6dir0, val);
	if (ret < 0) {
		printk("set st6dir0 value fail\n");
	}
}