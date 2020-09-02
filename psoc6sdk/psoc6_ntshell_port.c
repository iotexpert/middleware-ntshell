#include "ntshell.h"
#include "ntlibc.h"
#include "usrcmd.h"
#include <stdio.h>

int ntshell_read(char *buf, int cnt, void *extobj)
{
  int i;
  (void)extobj;
  for (i = 0; i < cnt; i++) {
    buf[i] = getchar();
  }
  return cnt;
}

int ntshell_write(const char *buf, int cnt, void *extobj)
{
  int i;
  (void)extobj;
  for (i = 0; i < cnt; i++) {
    putchar(buf[i]);
  }
  fflush(stdout);
  return cnt;
}

int ntshell_callback(const char *text, void *extobj)
{
  ntshell_t *ntshell = (ntshell_t *)extobj;
  (void)ntshell;
  (void)extobj;
  if (ntlibc_strlen(text) > 0) {

      usrcmd_execute(text);
  }
  return 0;
}
