#include "cli.h"
#include "bsp_uart.h"
#include <string.h>

#define CLI_LINE_BUF_SIZE   128U
#define CLI_MAX_CMDS        16U
#define CLI_MAX_ARGS        8U

static cli_cmd_t s_cmds[CLI_MAX_CMDS];
static uint8_t   s_cmd_count = 0;

static char      s_line_buf[CLI_LINE_BUF_SIZE];
static uint8_t   s_line_len = 0;

static const char *PROMPT   = "\r\n> ";
static const char *CRLF     = "\r\n";

/* -------------------------------------------------------------------------- */

void cli_print(const char *str)
{
    bsp_uart_send((const uint8_t *)str, (uint16_t)strlen(str));
}

void cli_println(const char *str)
{
    cli_print(str);
    cli_print(CRLF);
}

/* -------------------------------------------------------------------------- */

static void cmd_help(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    cli_println("Available commands:");
    for (uint8_t i = 0; i < s_cmd_count; i++)
    {
        cli_print("  ");
        cli_print(s_cmds[i].name);
        cli_print("\t- ");
        cli_println(s_cmds[i].help);
    }
}

/* -------------------------------------------------------------------------- */

void cli_init(void)
{
    s_cmd_count = 0;
    s_line_len  = 0;
    cli_register_cmd("help", "List all available commands", cmd_help);
    cli_print(PROMPT);
}

void cli_register_cmd(const char *name, const char *help, cli_handler_t handler)
{
    if (s_cmd_count >= CLI_MAX_CMDS)
    {
        return;
    }
    s_cmds[s_cmd_count].name    = name;
    s_cmds[s_cmd_count].help    = help;
    s_cmds[s_cmd_count].handler = handler;
    s_cmd_count++;
}

/* -------------------------------------------------------------------------- */

static void dispatch(void)
{
    if (s_line_len == 0)
    {
        return;
    }

    /* tokenize */
    char  *argv[CLI_MAX_ARGS];
    int    argc = 0;
    char  *token = strtok(s_line_buf, " ");

    while (token != NULL && argc < CLI_MAX_ARGS)
    {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc == 0)
    {
        return;
    }

    for (uint8_t i = 0; i < s_cmd_count; i++)
    {
        if (strcmp(argv[0], s_cmds[i].name) == 0)
        {
            cli_print(CRLF);
            s_cmds[i].handler(argc, argv);
            return;
        }
    }

    cli_print(CRLF);
    cli_print("Unknown command: ");
    cli_println(argv[0]);
    cli_println("Type 'help' to see available commands.");
}

void cli_process_byte(uint8_t byte)
{
    switch (byte)
    {
        case '\r':
        case '\n':
            s_line_buf[s_line_len] = '\0';
            dispatch();
            s_line_len = 0;
            cli_print(PROMPT);
            break;

        case 0x7F: /* backspace (DEL) */
        case '\b':
            if (s_line_len > 0)
            {
                s_line_len--;
                cli_print("\b \b");
            }
            break;

        default:
            if (s_line_len < CLI_LINE_BUF_SIZE - 1U)
            {
                s_line_buf[s_line_len++] = (char)byte;
                bsp_uart_send_byte(byte); /* local echo */
            }
            break;
    }
}
