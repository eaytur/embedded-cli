#include "bsp_uart.h"
#include "main.h"

extern UART_HandleTypeDef huart5;

static bsp_uart_rx_cb_t s_rx_cb = NULL;

void bsp_uart_init(void)
{
    __HAL_UART_ENABLE_IT(&huart5, UART_IT_RXNE);
    HAL_NVIC_SetPriority(UART5_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(UART5_IRQn);
}

void bsp_uart_set_rx_callback(bsp_uart_rx_cb_t cb)
{
    s_rx_cb = cb;
}

void bsp_uart_send_byte(uint8_t byte)
{
    HAL_UART_Transmit(&huart5, &byte, 1, HAL_MAX_DELAY);
}

void bsp_uart_send(const uint8_t *data, uint16_t length)
{
    HAL_UART_Transmit(&huart5, (uint8_t *)data, length, HAL_MAX_DELAY);
}

void bsp_uart_irq_handler(void)
{
    if (__HAL_UART_GET_FLAG(&huart5, UART_FLAG_RXNE))
    {
        uint8_t byte = (uint8_t)(huart5.Instance->DR & 0xFFU);
        if (s_rx_cb != NULL)
        {
            s_rx_cb(byte);
        }
    }
}
