#include "app.h"
#include "bsp_uart.h"
#include "cli.h"

void app_main(void)
{
    bsp_uart_init();
    cli_init();

    while (1)
    {
        if (bsp_uart_rx_available())
        {
            cli_process_byte(bsp_uart_rx_read_byte());
        }
    }
}
