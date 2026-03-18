#include "app.h"
#include "bsp_uart.h"
#include "cli.h"
#include "commands.h"
#include "cmsis_compiler.h"

static void uart_write(const char *data, uint16_t len)
{
    bsp_uart_send((const uint8_t *)data, len);
}

void app_main(void)
{
    bsp_uart_init();
    bsp_uart_set_rx_callback(cli_process_byte);
    cli_init(uart_write);
    commands_init();

    while (1)
    {
        __WFI();
    }
}
