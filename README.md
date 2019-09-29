# mbed-os-ntshell
An MBED Implementation of NTShell

This library a modified (very slightly) version of the Natural Tiny Shell by Shinichiro Nakamura (CuBeatSystems).  This project his hosted at https://www.cubeatsystems.com/ntshell/

The NTShell is a really simple shell for smallish embedded systems.  It understands VT100 terminal projects and provides nice features like command history.

I configured the ntshell to work with stdin/stdout using normal printf, getchar, putchar etc.

Inside of the project I included a template directory which contains the NTShell inside of a thread (ntShellThread.h/c) and all of the user commands inside of usrcmd.h/c

As a developer you can add commands to the shell by adding code to the usrcmd.h/.c

## To use ntshell inside of your project
To use this project add it to your mbed project with
* mbed add git@github.com:iotexpert/mbed-os-ntshell.git

* mbed add https://github.com/iotexpert/mbed-os-ntshell.git

Then copy the template files into your project
* cp mbed-os-ntshell/template/* .

Finally modify your main.cpp to start the ntShellThread

```
#include "mbed.h"
#include "ntShellThread.h"

Thread ntShellThreadHandle;

DigitalOut led1(LED1);

int main()
{
    printf("Started NTShellThread\n");
    ntShellThreadHandle.start(ntShellThread);
    while(1)
    {
        led1 = !led1;
        wait(0.5);
    }

}
```
### To add commands
In the file usrcmd.c you need to make three changes
1. Add a function prototype for your command
2. Add the new command to the cmdlist array
3. Write your actual function
