#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include "drv_uart.h"

#include <string.h>

// UART1
#define CAM_UART_DEVICE_NODE DT_ALIAS(camuart0)
static const struct device *cam_uart_dev = DEVICE_DT_GET(CAM_UART_DEVICE_NODE);

// UART2
#define UART2_DEVICE_NODE DT_ALIAS(usart2)
static const struct device *uart2_dev = DEVICE_DT_GET(UART2_DEVICE_NODE);

// UART3
#define CTRL_UART_DEVICE_NODE DT_ALIAS(ctrluart3)
static const struct device *ctrl_uart_dev = DEVICE_DT_GET(CTRL_UART_DEVICE_NODE);

// UART1
void cam_uart_cb(const struct device *dev, void *user_data)
{
	uint8_t c = 0;

	if (!uart_irq_update(cam_uart_dev)) {
		return;
	}

	while (uart_irq_rx_ready(cam_uart_dev)) {

		uart_fifo_read(cam_uart_dev, &c, 1);
		printk("%x ",c);
	}
}

void cam_uart_print(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(cam_uart_dev, buf[i]);
	}
}

void cam_uart_transmit(uint8_t *buf, uint16_t len)
{
	//printk("uart_transmit len = %d!\n",len);
	// for(int i=0;i<len;i++){
	// 	printk("%x ", buf[i]);
	// }
	// printk("\n");
	for(int i=0; i< len; i++){
		uart_poll_out(cam_uart_dev, buf[i]);
	}
}

void cam_uart_init( void )
{
	if (!device_is_ready(cam_uart_dev)) {
		printk("cam_uart_dev not found!");
		return;
	}
	
	uart_irq_callback_user_data_set(cam_uart_dev, cam_uart_cb, NULL);
	uart_irq_rx_enable(cam_uart_dev);

	//print_uart("uart inited\n");
}

// UART2
void uart2_cb(const struct device *dev, void *user_data)
{
	uint8_t c = 0;

	if (!uart_irq_update(uart2_dev)) {
		return;
	}

	while (uart_irq_rx_ready(uart2_dev)) {

		uart_fifo_read(uart2_dev, &c, 1);
		printk("%x ",c);
	}
}

void uart2_print(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(uart2_dev, buf[i]);
	}
}

void uart2_transmit(uint8_t *buf, uint16_t len)
{
	//printk("uart_transmit len = %d!\n",len);
	// for(int i=0;i<len;i++){
	// 	printk("%x ", buf[i]);
	// }
	// printk("\n");
	for(int i=0; i< len; i++){
		uart_poll_out(uart2_dev, buf[i]);
	}
}

void uart2_init( void )
{
	if (!device_is_ready(uart2_dev)) {
		printk("uart2_dev not found!");
		return;
	}
	
	uart_irq_callback_user_data_set(uart2_dev, uart2_cb, NULL);
	uart_irq_rx_enable(uart2_dev);

	//print_uart("uart inited\n");
}

// UART3
void ctrl_uart_cb(const struct device *dev, void *user_data)
{
	uint8_t c = 0;

	if (!uart_irq_update(ctrl_uart_dev)) {
		return;
	}

	while (uart_irq_rx_ready(ctrl_uart_dev)) {

		uart_fifo_read(ctrl_uart_dev, &c, 1);
		printk("%x ",c);
	}
}

void ctrl_uart_print(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(ctrl_uart_dev, buf[i]);
	}
}

void ctrl_uart_transmit(uint8_t *buf, uint16_t len)
{
	printk("uart_transmit len = %d!\n",len);
	for(int i=0;i<len;i++){
		printk("%x ", buf[i]);
	}
	printk("\n");
	for(int i=0; i< len; i++){
		uart_poll_out(ctrl_uart_dev, buf[i]);
	}
}

void ctrl_uart_init( void )
{
	if (!device_is_ready(ctrl_uart_dev)) {
		printk("ctrl_uart_dev not found!");
		return;
	}
	
	uart_irq_callback_user_data_set(ctrl_uart_dev, ctrl_uart_cb, NULL);
	uart_irq_rx_enable(ctrl_uart_dev);

	//print_uart("uart inited\n");
}