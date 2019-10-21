#include "ntshell.h"
#include "ntlibc.h"
#include "mbed_port.h"

ntshell_t ntshell;


void ntShellThread(void)
{

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
