#include "bsp_uart.h"
#include "main.h"

extern UART_HandleTypeDef huart5;

#define RX_BUFFER_SIZE 64U

static uint8_t rx_buffer[RX_BUFFER_SIZE];

static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0;

void bsp_uart_init(void)
{
    __HAL_UART_ENABLE_IT(&huart5, UART_IT_RXNE);
    HAL_NVIC_SetPriority(UART5_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(UART5_IRQn);
}

void bsp_uart_send_byte(uint8_t byte)
{
    HAL_UART_Transmit(&huart5, &byte, 1, HAL_MAX_DELAY);
}

void bsp_uart_send(const uint8_t *data, uint16_t length)
{
    HAL_UART_Transmit(&huart5, (uint8_t *)data, length, HAL_MAX_DELAY);
}

bool bsp_uart_rx_available(void)
{
    return rx_head != rx_tail;
}

uint8_t bsp_uart_rx_read_byte(void)
{
    uint8_t byte = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1U) % RX_BUFFER_SIZE;
    return byte;
}

void bsp_uart_irq_handler(void)
{
    if (__HAL_UART_GET_FLAG(&huart5, UART_FLAG_RXNE))
    {
        uint8_t byte = (uint8_t)(huart5.Instance->DR & 0xFFU);
        uint16_t next_head = (rx_head + 1U) % RX_BUFFER_SIZE;
        if (next_head != rx_tail)
        {
            rx_buffer[rx_head] = byte;
            rx_head = next_head;
        }
    }
}
