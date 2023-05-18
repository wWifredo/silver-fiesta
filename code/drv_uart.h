#ifndef __DRV_UART_H__
#define __DRV_UART_H__

void cam_uart_init( void );
void cam_uart_print(char *buf);
void cam_uart_transmit(uint8_t *buf, uint16_t len);

void uart2_init( void );
void uart2_print(char *buf);
void uart2_transmit(uint8_t *buf, uint16_t len);

void ctrl_uart_init( void );
void ctrl_uart_print(char *buf);
void ctrl_uart_transmit(uint8_t *buf, uint16_t len);


#endif // !__DRV_UART_H__



