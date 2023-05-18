#include <zephyr/sys/printk.h>
#include <zephyr/zephyr.h>
#include <string.h>

#include "ctrl_oled.h"
#include "drv_oled_io.h"
#include "drv_spi.h"

#include "../../../../common/com_error/com_error.h"

com_spi_lcd_dev_node_t lcd_dev;

int lcd_dev_write_cb(uint8_t *data,uint16_t len)
{
    drv_spi_write(data,len);
    return COM_SUCCESS;
}

int lcd_dev_delay_cb(uint16_t ms)
{
    k_msleep(ms);
    return COM_SUCCESS;
}

int lcd_dev_set_dc_cb(uint8_t val)
{
    drv_oled_dc_set(val);
    return COM_SUCCESS;
}

int lcd_dev_set_rst_cb(uint8_t val)
{
    drv_oled_res_set(val);
    return COM_SUCCESS;
}

int lcd_dev_set_cs_cb(uint8_t val)
{
    return COM_SUCCESS;
}


void ctrl_oled_init(void)
{
    drv_oled_io_init();
    drv_spi_init();

    COM_ERROR_CHECK(com_spi_lcd_dev_creat(&lcd_dev,128,64));
    COM_ERROR_CHECK(com_spi_lcd_dev_cfg_cb(&lcd_dev,lcd_dev_write_cb,NULL,lcd_dev_delay_cb,lcd_dev_set_dc_cb,lcd_dev_set_rst_cb,lcd_dev_set_cs_cb));
    COM_ERROR_CHECK(com_spi_lcd_dev_init(&lcd_dev));
    //COM_ERROR_CHECK(com_spi_lcd_dev_show_string(&lcd_dev,0,0,"Hello",FontSize_16,1));
}