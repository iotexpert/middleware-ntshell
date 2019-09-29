#include "mbed.h"

#ifndef MBED_PORT_H
#define MBED_PORT_H

#ifdef __cplusplus
extern "C"
{
#endif

int ntshell_read(char *buf, int cnt, void *extobj);
int ntshell_write(const char *buf, int cnt, void *extobj);
int ntshell_callback(const char *text, void *extobj);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

