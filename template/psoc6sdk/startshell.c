
// You need these includes

#include "ntshell.h"
#include "ntlibc.h"
#include "psoc6_ntshell_port.h"

// Global variable with a handle to the shell
ntshell_t ntshell;

void ntShellTask()
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

// this will start the task

xTaskCreate(ntShellTask, "nt shell task", configMINIMAL_STACK_SIZE*2,0 /* args */ ,0 /* priority */, 0);
