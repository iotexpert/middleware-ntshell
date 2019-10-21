
#include "ntshell.h"
#include "ntlibc.h"
#include "psoc6_ntshell_port.h"

ntshell_t ntshell;

void startShell()
{

    printf("Started ntshell\n");
    setvbuf(stdin, NULL, _IONBF, 0);
    ntshell_init(
        &ntshell,
        ntshell_read,
        ntshell_write,
        ntshell_callback,
        (void *)&ntshell);
    ntshell_set_prompt(&ntshell, "BlueTank>");
    vtsend_erase_display(&ntshell.vtsend);
    ntshell_execute(&ntshell);
}

