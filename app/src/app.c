#include "app.h"
#include "bsp_uart.h"

void app_main(void)
{
    bsp_uart_init();

    while (1)
    {
        if (bsp_uart_rx_available())
        {
            uint8_t byte = bsp_uart_rx_read_byte();
            bsp_uart_send_byte(byte); /* echo */
        }
    }
}
