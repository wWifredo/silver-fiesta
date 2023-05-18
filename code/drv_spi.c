#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include <string.h>
#include "../../../../common/com_error/com_error.h"
#include "drv_spi.h"

#define SPI3_NODE	DT_NODELABEL(oled_spi)
const struct device *oled_spi_dev = DEVICE_DT_GET(SPI3_NODE);

struct spi_config spi_cfg;

uint8_t spi_rx_buf[16];
uint8_t spi_tx_buf[16];

struct spi_buf rx_buf[] = {
    {
        .buf = spi_rx_buf,
        .len = 16
    },
};

struct spi_buf_set rx = {
    .buffers =  rx_buf,
    .count = 1
};

struct spi_buf tx_buf[] = {
    {
        .buf = spi_tx_buf,
        .len = 16
    },
};

struct spi_buf_set tx = {
    .buffers =  tx_buf,
    .count = 1
};

int drv_spi_write(uint8_t *tx_data_p, uint16_t size)
{
    int res = 0;
    if(size <= 16){
        memcpy(tx_buf->buf,tx_data_p,size);
        tx_buf->len = size;
        res = spi_write(oled_spi_dev, &spi_cfg, &tx);
        if(res < 0){
            printk("spi write error!, res = %d\n",res);
        }
        //printk("spi_write data!, data1 = %x, data1 = %x, size = %d\n",tx_data_p[0],tx_data_p[1],size);
    }
    //printk("spi_write!\n");
    return COM_SUCCESS;
}

void drv_spi_init(void)
{
    printk("drv spi init start!\n");
    spi_cfg.frequency = 1000000U;
    spi_cfg.operation = SPI_WORD_SET(8) | SPI_TRANSFER_MSB | SPI_OP_MODE_MASTER | SPI_MODE_CPOL; //  | SPI_MODE_CPHA  | SPI_MODE_CPOL

    printk("spi init done!\n");
}
