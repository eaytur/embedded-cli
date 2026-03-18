#include "commands.h"
#include "cli.h"

/* ---- handlers ------------------------------------------------------------ */

static void cmd_version(int argc, char *argv[])
{
    (void)argc; (void)argv;

    cli_println("Firmware info:");
    cli_print  ("  Version : "); cli_println(GIT_TAG);
    cli_print  ("  Commit  : "); cli_println(GIT_HASH);
    cli_print  ("  Build   : "); cli_println(BUILD_TYPE);
}

static void cmd_foo(int argc, char *argv[])
{
    (void)argc; (void)argv;
    cli_println("Dummy command output");
}

static const cli_cmd_t s_commands[] = {
    { "version", "Show firmware version and build info", cmd_version },
    { "foo", "Dummy registration test command", cmd_foo }
};

/* ---- registration -------------------------------------------------------- */

void commands_init(void)
{
    cli_register_table(s_commands, sizeof(s_commands) / sizeof(s_commands[0]));
}
