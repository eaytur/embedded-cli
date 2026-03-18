#ifndef CLI_H
#define CLI_H

#include <stdint.h>

typedef void (*cli_handler_t)(int argc, char *argv[]);

typedef struct
{
    const char     *name;
    const char     *help;
    cli_handler_t   handler;
} cli_cmd_t;

void cli_init(void);
void cli_register_cmd(const char *name, const char *help, cli_handler_t handler);
void cli_process_byte(uint8_t byte);
void cli_print(const char *str);
void cli_println(const char *str);

#endif /* CLI_H */
