#include "app.h"
#include "bsp_uart.h"
#include "cli.h"
#include "commands.h"
#include "cmsis_compiler.h"

void app_main(void)
{
    bsp_uart_init();
    bsp_uart_set_rx_callback(cli_process_byte);
    cli_init();
    commands_init();

    while (1)
    {
        __WFI();
    }
}
