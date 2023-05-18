#include <zephyr/sys/printk.h>
#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include "drv_key.h"
#include "ctrl_pwm.h"
#include "drv_motor_io.h"
#include "ctrl_servo.h"
#include "prot_feetech.h"

// key1
#define KEY1	DT_ALIAS(key1)
#if !DT_NODE_HAS_STATUS(KEY1, okay)
#error "Unsupported board: key1 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec key1 = GPIO_DT_SPEC_GET_OR(KEY1, gpios,{0});

// key2
#define KEY2	DT_ALIAS(key2)
#if !DT_NODE_HAS_STATUS(KEY2, okay)
#error "Unsupported board: key2 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec key2 = GPIO_DT_SPEC_GET_OR(KEY2, gpios,{0});

// key3
#define KEY3	DT_ALIAS(key3)
#if !DT_NODE_HAS_STATUS(KEY3, okay)
#error "Unsupported board: key3 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec key3 = GPIO_DT_SPEC_GET_OR(KEY3, gpios,{0});

// key4
#define KEY4	DT_ALIAS(key4)
#if !DT_NODE_HAS_STATUS(KEY4, okay)
#error "Unsupported board: key4 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec key4 = GPIO_DT_SPEC_GET_OR(KEY4, gpios,{0});

// button1
#define BUTTON1	DT_ALIAS(button1)
#if !DT_NODE_HAS_STATUS(BUTTON1, okay)
#error "Unsupported board: button1 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET_OR(BUTTON1, gpios,{0});

// button2
#define BUTTON2	DT_ALIAS(button2)
#if !DT_NODE_HAS_STATUS(BUTTON2, okay)
#error "Unsupported board: button2 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET_OR(BUTTON2, gpios,{0});

// button3
#define BUTTON3	DT_ALIAS(button3)
#if !DT_NODE_HAS_STATUS(BUTTON3, okay)
#error "Unsupported board: button3 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET_OR(BUTTON3, gpios,{0});

// button4
#define BUTTON4	DT_ALIAS(button4)
#if !DT_NODE_HAS_STATUS(BUTTON4, okay)
#error "Unsupported board: button4 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec button4 = GPIO_DT_SPEC_GET_OR(BUTTON4, gpios,{0});

// cfg1
#define CFG1	DT_ALIAS(cfg1)
#if !DT_NODE_HAS_STATUS(CFG1, okay)
#error "Unsupported board: cfg1 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec cfg1 = GPIO_DT_SPEC_GET_OR(CFG1, gpios,{0});

// cfg2
#define CFG2	DT_ALIAS(cfg2)
#if !DT_NODE_HAS_STATUS(CFG2, okay)
#error "Unsupported board: cfg2 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec cfg2 = GPIO_DT_SPEC_GET_OR(CFG2, gpios,{0});

// cfg3
#define CFG3	DT_ALIAS(cfg3)
#if !DT_NODE_HAS_STATUS(CFG3, okay)
#error "Unsupported board: cfg3 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec cfg3 = GPIO_DT_SPEC_GET_OR(CFG3, gpios,{0});

// cfg4
#define CFG4	DT_ALIAS(cfg4)
#if !DT_NODE_HAS_STATUS(CFG4, okay)
#error "Unsupported board: cfg4 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec cfg4 = GPIO_DT_SPEC_GET_OR(CFG4, gpios,{0});

// start_key
#define START_KEY	DT_ALIAS(start0)
#if !DT_NODE_HAS_STATUS(START_KEY, okay)
#error "Unsupported board: start_key devicetree alias is not defined"
#endif
static const struct gpio_dt_spec start_key = GPIO_DT_SPEC_GET_OR(START_KEY, gpios,{0});

// ptonc0
#define PTO_NC0	DT_ALIAS(ptonc0)
#if !DT_NODE_HAS_STATUS(PTO_NC0, okay)
#error "Unsupported board: ptonc0 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec ptonc0 = GPIO_DT_SPEC_GET_OR(PTO_NC0, gpios,{0});

// ptono0
#define PTO_NO0	DT_ALIAS(ptono0)
#if !DT_NODE_HAS_STATUS(PTO_NO0, okay)
#error "Unsupported board: ptono0 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec ptono0 = GPIO_DT_SPEC_GET_OR(PTO_NO0, gpios,{0});

static struct gpio_callback button_cb[16];
// timer
struct k_timer key1_timer;
struct k_timer key2_timer;
struct k_timer key3_timer;
struct k_timer key4_timer;

struct k_timer button1_timer;
struct k_timer button2_timer;
struct k_timer button3_timer;
struct k_timer button4_timer;

struct k_timer start_key_timer;
struct k_timer ptonc0_timer;
struct k_timer ptono0_timer;

void __attribute__((weak)) key1_pressed_proc(void)
{
    static int index = 1;
    printk("key1 pressed!\n");
    drv_set_motor_st1_dir(index % 2);
    drv_set_motor_st2_dir(index % 2);
    drv_set_motor_st3_dir(index % 2);
    drv_set_motor_st4_dir(index % 2);
    drv_set_motor_st5_dir(index % 2);
    drv_set_motor_st6_dir(index++ % 2);
}

void key1_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&key1);
	
    if(val == 1){
        key1_pressed_proc();
    }
    k_timer_stop(&key1_timer);
}

void key1_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    k_timer_start(&key1_timer, K_MSEC(30), K_MSEC(30));
}

void __attribute__((weak)) key2_pressed_proc(void)
{
    printk("key2 pressed!\n");
    com_smd_set_step_angle(&high_ctrl_motor,360.0f);
    //printk("high_ctrl_motor target_count = %d!\n",high_ctrl_motor.target_count);
    com_smd_set_step_angle(&length_ctrl_motor,360.0f);
    com_smd_set_step_angle(&angle_ctrl_motor,360.0f);
    com_smd_set_step_angle(&turntable_ctrl_motor,360.0f);
    com_smd_set_step_angle(&timer9_ch1,360.0f);
    com_smd_set_step_angle(&timer9_ch2,360.0f);
}

void key2_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&key2);
	
    if(val == 1){
        key2_pressed_proc();
    }
    k_timer_stop(&key2_timer);
}

void key2_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    k_timer_start(&key2_timer, K_MSEC(30), K_MSEC(30));
}

void __attribute__((weak)) key3_pressed_proc(void)
{
    static int index = 0;
    printk("key3 pressed!\n");
    servo1_set_angle(45.0f * index++);
    //servo2_set_angle(45.0f * index);
    //servo3_set_angle(45.0f * index);
    //servo4_set_angle(45.0f * index++);
    if(index >= 7){
        index = 0;
    }
}

void key3_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&key3);
	
    if(val == 1){
        key3_pressed_proc();
    }

    k_timer_stop(&key3_timer);
}

void key3_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    k_timer_start(&key3_timer, K_MSEC(30), K_MSEC(30));
}

void __attribute__((weak)) key4_pressed_proc(void)
{
    static int index = 0;
    printk("key4 pressed!\n");
    if(index++ % 2){
        feetech_write_action_cmd(0x01,2800);
    } else {
        feetech_write_action_cmd(0x01,0);
    }
}

void key4_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&key4);
	
    if(val == 1){
        key4_pressed_proc();
    }

    k_timer_stop(&key4_timer);
}

void key4_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    k_timer_start(&key4_timer, K_MSEC(30), K_MSEC(30));
}

void __attribute__((weak)) button1_pressed_proc(void)
{
    printk("button1 pressed!\n");
}

void button1_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&button1);
    static int index = 0;
	
    if(val == 1){
        index++;
        if(index == 2){
            button1_pressed_proc();
        }
    } else {
        index = 0;
    }
    //k_timer_stop(&button1_timer);
}

void __attribute__((weak)) button2_pressed_proc(void)
{
    printk("button2 pressed!\n");
}

void button2_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&button2);
    static int index = 0;
	
    if(val == 1){
        index++;
        if(index == 2){
            button2_pressed_proc();
        }
    } else {
        index = 0;
    }
    //k_timer_stop(&button2_timer);
}

void __attribute__((weak)) button3_pressed_proc(void)
{
    printk("button3 pressed!\n");
}

void button3_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&button3);
    static int index = 0;
	
    if(val == 1){
        index++;
        if(index == 2){
            button3_pressed_proc();
        }
    } else {
        index = 0;
    }
    //k_timer_stop(&button3_timer);
}

void __attribute__((weak)) button4_pressed_proc(void)
{
    printk("button4 pressed!\n");
}

void button4_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&button4);
	
    if(val == 1){
        button4_pressed_proc();
    }
    k_timer_stop(&button4_timer);
}

void button4_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    k_timer_start(&button4_timer, K_MSEC(30), K_MSEC(30));
}

//cfg
int drv_read_cfg_value(void)
{
    int val, sum;
    val = gpio_pin_get_dt(&cfg1);
    sum = !val;
    val = gpio_pin_get_dt(&cfg2);
    sum = (sum << 1) | !val;
    val = gpio_pin_get_dt(&cfg3);
    sum = (sum << 1) | !val;
    val = gpio_pin_get_dt(&cfg4);
    sum = (sum << 1) | !val;
    printk("cfg value = %d\n",sum);
    return sum;
}

// start_key
void __attribute__((weak)) start_key_pressed_proc(void)
{
    printk("start_key pressed!\n");
}

void start_key_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&start_key);
	
    if(val == 1){
        start_key_pressed_proc();
    }
    k_timer_stop(&start_key_timer);
}

void start_key_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    k_timer_start(&start_key_timer, K_MSEC(30), K_MSEC(30));
}

// ptonc0
void __attribute__((weak)) ptonc0_pressed_proc(void)
{
    printk("ptonc0 pressed!\n");
}

void ptonc0_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&ptonc0);
	
    if(val == 1){
        ptonc0_pressed_proc();
    }
    k_timer_stop(&ptonc0_timer);
}

void ptonc0_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    k_timer_start(&ptonc0_timer, K_MSEC(30), K_MSEC(30));
}

// ptono0
void __attribute__((weak)) ptono0_pressed_proc(void)
{
    printk("ptono0 pressed!\n");
}

void ptono0_timer_out(struct k_timer *timer_id)
{
	int val = gpio_pin_get_dt(&ptono0);
	
    if(val == 1){
        ptono0_pressed_proc();
    }
    k_timer_stop(&ptono0_timer);
}

void ptono0_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    k_timer_start(&ptono0_timer, K_MSEC(30), K_MSEC(30));
}

void drv_key_init(void)
{
    int ret;

    // key1
	if (!device_is_ready(key1.port)) {
		printk("Error: key1 device %s is not ready\n", key1.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&key1, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, key1.port->name, key1.pin);
		return;
	}
	ret = gpio_pin_interrupt_configure_dt(&key1, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, key1.port->name, key1.pin);
		return;
	}
	gpio_init_callback(&button_cb[0], key1_pressed, BIT(key1.pin));
	gpio_add_callback(key1.port, &button_cb[0]);
	printk("Set up key1 at %s pin %d\n", key1.port->name, key1.pin);

    // key2
	if (!device_is_ready(key2.port)) {
		printk("Error: key2 device %s is not ready\n", key2.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&key2, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, key2.port->name, key2.pin);
		return;
	}
	ret = gpio_pin_interrupt_configure_dt(&key2, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, key2.port->name, key2.pin);
		return;
	}
	gpio_init_callback(&button_cb[1], key2_pressed, BIT(key2.pin));
	gpio_add_callback(key2.port, &button_cb[1]);
	printk("Set up key2 at %s pin %d\n", key2.port->name, key2.pin);

    // key3
	if (!device_is_ready(key3.port)) {
		printk("Error: key3 device %s is not ready\n", key3.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&key3, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, key3.port->name, key3.pin);
		return;
	}
	ret = gpio_pin_interrupt_configure_dt(&key3, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, key3.port->name, key3.pin);
		return;
	}
	gpio_init_callback(&button_cb[2], key3_pressed, BIT(key3.pin));
	gpio_add_callback(key3.port, &button_cb[2]);
	printk("Set up key3 at %s pin %d\n", key3.port->name, key3.pin);

    // key4
	if (!device_is_ready(key4.port)) {
		printk("Error: key4 device %s is not ready\n", key4.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&key4, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, key4.port->name, key4.pin);
		return;
	}
	ret = gpio_pin_interrupt_configure_dt(&key4, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, key4.port->name, key4.pin);
		return;
	}
	gpio_init_callback(&button_cb[3], key4_pressed, BIT(key4.pin));
	gpio_add_callback(key4.port, &button_cb[3]);
	printk("Set up key4 at %s pin %d\n", key4.port->name, key4.pin);

    // button1
	if (!device_is_ready(button1.port)) {
		printk("Error: button1 device %s is not ready\n", button1.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&button1, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, button1.port->name, button1.pin);
		return;
	}
	// ret = gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE);
	// if (ret != 0) {
	// 	printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, button1.port->name, button1.pin);
	// 	return;
	// }
	// gpio_init_callback(&button_cb[4], button1_pressed, BIT(button1.pin));
	// gpio_add_callback(button1.port, &button_cb[4]);
	// printk("Set up button1 at %s pin %d\n", button1.port->name, button1.pin);

    // button2
	if (!device_is_ready(button2.port)) {
		printk("Error: button2 device %s is not ready\n", button2.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&button2, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, button2.port->name, button2.pin);
		return;
	}
	// ret = gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_TO_ACTIVE);
	// if (ret != 0) {
	// 	printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, button2.port->name, button2.pin);
	// 	return;
	// }
	// gpio_init_callback(&button_cb[5], button2_pressed, BIT(button2.pin));
	// gpio_add_callback(button2.port, &button_cb[5]);
	// printk("Set up button2 at %s pin %d\n", button2.port->name, button2.pin);

    // button3
	if (!device_is_ready(button3.port)) {
		printk("Error: button3 device %s is not ready\n", button3.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&button3, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, button3.port->name, button3.pin);
		return;
	}
	// ret = gpio_pin_interrupt_configure_dt(&button3, GPIO_INT_EDGE_TO_ACTIVE);
	// if (ret != 0) {
	// 	printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, button3.port->name, button3.pin);
	// 	return;
	// }
	// gpio_init_callback(&button_cb[6], button3_pressed, BIT(button3.pin));
	// gpio_add_callback(button3.port, &button_cb[6]);
	// printk("Set up button3 at %s pin %d\n", button3.port->name, button3.pin);

    // button4
	if (!device_is_ready(button4.port)) {
		printk("Error: button4 device %s is not ready\n", button4.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&button4, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, button4.port->name, button4.pin);
		return;
	}
	ret = gpio_pin_interrupt_configure_dt(&button4, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, button4.port->name, button4.pin);
		return;
	}
	gpio_init_callback(&button_cb[7], button4_pressed, BIT(button4.pin));
	gpio_add_callback(button4.port, &button_cb[7]);
	printk("Set up button4 at %s pin %d\n", button4.port->name, button4.pin);

	// cfg1
	if (!device_is_ready(cfg1.port)) {
		printk("Error: cfg1 device %s is not ready\n", cfg1.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&cfg1, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, cfg1.port->name, cfg1.pin);
		return;
	}

	// cfg2
	if (!device_is_ready(cfg2.port)) {
		printk("Error: cfg2 device %s is not ready\n", cfg2.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&cfg2, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, cfg2.port->name, cfg2.pin);
		return;
	}

	// cfg3
	if (!device_is_ready(cfg3.port)) {
		printk("Error: cfg3 device %s is not ready\n", cfg3.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&cfg3, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, cfg3.port->name, cfg3.pin);
		return;
	}

	// cfg4
	if (!device_is_ready(cfg4.port)) {
		printk("Error: cfg4 device %s is not ready\n", cfg4.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&cfg4, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, cfg4.port->name, cfg4.pin);
		return;
	}

    // start_key
	if (!device_is_ready(start_key.port)) {
		printk("Error: start_key device %s is not ready\n", start_key.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&start_key, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, start_key.port->name, start_key.pin);
		return;
	}
	ret = gpio_pin_interrupt_configure_dt(&start_key, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, start_key.port->name, start_key.pin);
		return;
	}
	gpio_init_callback(&button_cb[8], start_key_pressed, BIT(start_key.pin));
	gpio_add_callback(start_key.port, &button_cb[8]);
	printk("Set up start_key at %s pin %d\n", start_key.port->name, start_key.pin);

    // ptonc0
	if (!device_is_ready(ptonc0.port)) {
		printk("Error: ptonc0 device %s is not ready\n", ptonc0.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&ptonc0, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, ptonc0.port->name, ptonc0.pin);
		return;
	}
	ret = gpio_pin_interrupt_configure_dt(&ptonc0, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, ptonc0.port->name, ptonc0.pin);
		return;
	}
	gpio_init_callback(&button_cb[9], ptonc0_pressed, BIT(ptonc0.pin));
	gpio_add_callback(ptonc0.port, &button_cb[9]);
	printk("Set up ptonc0 at %s pin %d\n", ptonc0.port->name, ptonc0.pin);

    // ptono0
	if (!device_is_ready(ptono0.port)) {
		printk("Error: ptono0 device %s is not ready\n", ptono0.port->name);
		return;
	}
	ret = gpio_pin_configure_dt(&ptono0, GPIO_INPUT | GPIO_PULL_UP);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",	ret, ptono0.port->name, ptono0.pin);
		return;
	}
	ret = gpio_pin_interrupt_configure_dt(&ptono0, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, ptono0.port->name, ptono0.pin);
		return;
	}
	gpio_init_callback(&button_cb[10], ptono0_pressed, BIT(ptono0.pin));
	gpio_add_callback(ptono0.port, &button_cb[10]);
	printk("Set up ptono0 at %s pin %d\n", ptono0.port->name, ptono0.pin);

    // timer 
    k_timer_init(&key1_timer, key1_timer_out, NULL);
	k_timer_init(&key2_timer, key2_timer_out, NULL);
	k_timer_init(&key3_timer, key3_timer_out, NULL);
	k_timer_init(&key4_timer, key4_timer_out, NULL);

	k_timer_init(&button1_timer, button1_timer_out, NULL);
	k_timer_init(&button2_timer, button2_timer_out, NULL);
	k_timer_init(&button3_timer, button3_timer_out, NULL);
	k_timer_init(&button4_timer, button4_timer_out, NULL);

    k_timer_init(&start_key_timer, start_key_timer_out, NULL);
    k_timer_init(&ptonc0_timer, ptonc0_timer_out, NULL);
    k_timer_init(&ptono0_timer, ptono0_timer_out, NULL);

    k_timer_start(&button1_timer, K_MSEC(51), K_MSEC(51));
    k_timer_start(&button2_timer, K_MSEC(51), K_MSEC(51));
    k_timer_start(&button3_timer, K_MSEC(51), K_MSEC(51));
}