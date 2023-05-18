#include <zephyr/sys/printk.h>
#include <string.h>

#include "prot_feetech.h"
#include "drv_uart.h"
#include "../../../../../common/com_error/com_error.h"

#define FEETECH_SEND_BUF_LEN 36
uint8_t feetech_send_buf[FEETECH_SEND_BUF_LEN];

static uint8_t calc_chk_sum(uint8_t *buf, uint16_t len)
{
    uint8_t sum = 0;
    for(int i = 2; i < len; i++){
        sum += buf[i];
    }
    return ~sum;
}

static int pkg_cmd(uint8_t id, uint8_t cmd, uint8_t paras_len, uint8_t *buf, uint16_t len)
{
    if(buf == NULL){
        return COM_ERROR_NULL;
    }
    if(len < paras_len + 6){
        return COM_ERROR_INVALID_LENGTH;
    }

    uint8_t sum;

    buf[0] = FEETECH_MAGIC_HEAD1;
    buf[1] = FEETECH_MAGIC_HEAD2;
    buf[2] = id;
    buf[3] = paras_len + 2;
    buf[4] = cmd;
    sum = calc_chk_sum(buf,paras_len + 5);
    buf[paras_len + 5] = sum;

    return COM_SUCCESS;
}

void feetech_send_ping_cmd(uint8_t id)
{
    pkg_cmd(id,FEETECH_CMD_PING,0,feetech_send_buf,sizeof(feetech_send_buf));
    // printk("uart send data\n");
    // for(int i = 0; i < 6; i++){
    //     printk("%x ",feetech_send_buf[i]);
    // }
    // printk("\n");
    ctrl_uart_transmit(feetech_send_buf,6);
}

void feetech_read_data_cmd(uint8_t id, uint8_t addr, uint8_t len)
{
    feetech_send_buf[FEETECH_PARAS_POS] = addr;
    feetech_send_buf[FEETECH_PARAS_POS + 1] = len;
    pkg_cmd(id,FEETECH_CMD_READ_DATA,2,feetech_send_buf,sizeof(feetech_send_buf));
    ctrl_uart_transmit(feetech_send_buf,8);
}

void feetech_write_data_cmd(uint8_t id, uint8_t addr, uint8_t *data, uint8_t data_len)
{
    feetech_send_buf[FEETECH_PARAS_POS] = addr;
    for(int i = 0; i < data_len; i++){
        feetech_send_buf[FEETECH_PARAS_POS + 1 +i] = data[i];
    }
    pkg_cmd(id,FEETECH_CMD_WRITE_DATA,data_len + 1,feetech_send_buf,sizeof(feetech_send_buf));
    // printk("uart send data\n");
    // for(int i = 0; i < 7 + data_len; i++){
    //     printk("%x ",feetech_send_buf[i]);
    // }
    // printk("\n");
    ctrl_uart_transmit(feetech_send_buf,7 + data_len);
}

void feetech_reg_write_data_cmd(uint8_t id, uint8_t addr, uint8_t *data, uint8_t data_len)
{
    feetech_send_buf[FEETECH_PARAS_POS] = addr;
    for(int i = 0; i < data_len; i++){
        feetech_send_buf[FEETECH_PARAS_POS + 1 +i] = data[i];
    }
    pkg_cmd(id,FEETECH_CMD_RWRITE_DATA,data_len + 1,feetech_send_buf,sizeof(feetech_send_buf));
    ctrl_uart_transmit(feetech_send_buf,7 + data_len);
}

void feetech_send_action_cmd(uint8_t id)
{
    pkg_cmd(id,FEETECH_CMD_ACTION,0,feetech_send_buf,sizeof(feetech_send_buf));
    ctrl_uart_transmit(feetech_send_buf,6);
}

void feetech_sync_write_data_cmd(uint8_t id, uint8_t addr, uint8_t *data, uint8_t data_len)
{
    feetech_send_buf[FEETECH_PARAS_POS] = addr;
    for(int i = 0; i < data_len; i++){
        feetech_send_buf[FEETECH_PARAS_POS + 1 +i] = data[i];
    }
    pkg_cmd(id,FEETECH_CMD_SYNC_READ_DATA,data_len + 1,feetech_send_buf,sizeof(feetech_send_buf));
    ctrl_uart_transmit(feetech_send_buf,7 + data_len);
}

// void feetech_sync_read_data_cmd(uint8_t id, uint8_t addr, uint8_t len)
// {
//     feetech_send_buf[FEETECH_PARAS_POS] = addr;
//     feetech_send_buf[FEETECH_PARAS_POS + 1] = len;
//     pkg_cmd(id,FEETECH_CMD_SYNC_WRITE_DATA,2,feetech_send_buf,sizeof(feetech_send_buf));
//     ctrl_uart_transmit(feetech_send_buf,8);
// }

void feetech_send_recovery_cmd(uint8_t id)
{
    pkg_cmd(id,FEETECH_CMD_RECOVERY,0,feetech_send_buf,sizeof(feetech_send_buf));
    ctrl_uart_transmit(feetech_send_buf,6);
}

void feetech_send_reset_cmd(uint8_t id)
{
    pkg_cmd(id,FEETECH_CMD_RESET,0,feetech_send_buf,sizeof(feetech_send_buf));
    ctrl_uart_transmit(feetech_send_buf,6);
}

void feetech_write_action_cmd(uint8_t id, uint16_t pos)
{
    uint8_t crc;

    feetech_send_buf[0] = FEETECH_MAGIC_HEAD1;
    feetech_send_buf[1] = FEETECH_MAGIC_HEAD2;
    feetech_send_buf[2] = id;
    feetech_send_buf[3] = 0x09;     // len
    feetech_send_buf[4] = 0x03;
    feetech_send_buf[5] = 0x2A;     // address
    feetech_send_buf[6] = pos % 0xFF;   // positon low byte
    feetech_send_buf[7] = (pos >> 8) % 0xFF;    // position high byte
    feetech_send_buf[8] = 0x00;     // time set value low
    feetech_send_buf[9] = 0x00;     // time set value high
    feetech_send_buf[10] = 0xE8;    // speed set value low
    feetech_send_buf[11] = 0x03;    // speed set value high
    crc = calc_chk_sum(feetech_send_buf,12);
    feetech_send_buf[12] = crc;
    ctrl_uart_transmit(feetech_send_buf,13);
}