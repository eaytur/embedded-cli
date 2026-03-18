#ifndef BSP_UART_H
#define BSP_UART_H

#include <stdint.h>
#include <stdbool.h>

void bsp_uart_init(void);
void bsp_uart_send_byte(uint8_t byte);
void bsp_uart_send(const uint8_t *data, uint16_t length);
bool bsp_uart_rx_available(void);
uint8_t bsp_uart_rx_read_byte(void);
void bsp_uart_irq_handler(void);

#endif /*BSP_UART_H*/