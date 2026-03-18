#ifndef BSP_UART_H
#define BSP_UART_H

#include <stdint.h>

typedef void (*bsp_uart_rx_cb_t)(uint8_t byte);

void bsp_uart_init(void);
void bsp_uart_set_rx_callback(bsp_uart_rx_cb_t cb);
void bsp_uart_send_byte(uint8_t byte);
void bsp_uart_send(const uint8_t *data, uint16_t length);
void bsp_uart_irq_handler(void);

#endif /* BSP_UART_H */
