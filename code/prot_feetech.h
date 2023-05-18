#ifndef __PROT_FEETECH_H__
#define __PROT_FEETECH_H__

#define FEETECH_MAGIC_HEAD1 0xFF
#define FEETECH_MAGIC_HEAD2 0xFF

#define FEETECH_PARAS_POS 5

/** @brief Enumerated for command. */
typedef enum {
    FEETECH_CMD_PING = 0x01,
    FEETECH_CMD_READ_DATA = 0x02,
    FEETECH_CMD_WRITE_DATA = 0x03,
    FEETECH_CMD_RWRITE_DATA = 0x04,
    FEETECH_CMD_ACTION = 0x05,
    FEETECH_CMD_SYNC_READ_DATA = 0x82,
    FEETECH_CMD_SYNC_WRITE_DATA = 0x83,
    FEETECH_CMD_RECOVERY = 0x06,
    FEETECH_CMD_RESET = 0x0A,
}feetech_cmd_code_t;

// /** @brief Enumerated for command. */
// typedef enum {
//     FEETECH_MEM_MAIN_FW_VERSION = 0x00,
//     FEETECH_MEM_MIN_FW_VERSION = 0x01,
//     FEETECH_MEM_END = 0x02,
//     FEETECH_MEM_MAIN_SERVO_VERSION = 0x03,
//     FEETECH_MEM_MIN_SERVO_VERSION = 0x04,
//     FEETECH_MEM_ID = 0x05,
//     FEETECH_MEM_BAUD = 0x06,
//     FEETECH_MEM_RETURN_DELAY = 0x07,
//     FEETECH_MEM_PHASE2 = 0x08,
//     FEETECH_MEM_MIN_ANGLE_LIM = 0x09,
//     FEETECH_MEM_MAX_ANGLE_LIM = 0x0B,
//     FEETECH_MEM_MAX_TEMP_LIM = 0x0D,
//     FEETECH_MEM_MAX_IN_VOL = 0x0E,
//     FEETECH_MEM_MIN_IN_VOL = 0x0F,
//     FEETECH_MEM_MAX_TORQUE = 0x10,
//     FEETECH_MEM_PHASE = 0x12,
// }feetech_mem_addr_code_t;

void feetech_send_ping_cmd(uint8_t id);

void feetech_write_data_cmd(uint8_t id, uint8_t addr, uint8_t *data, uint8_t data_len);

void feetech_write_action_cmd(uint8_t id, uint16_t pos);

#endif // !__PROT_FEETECH_H__



