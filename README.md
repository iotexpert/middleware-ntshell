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

### Add function prototype
The function prototype of commands is
```
typedef int (*USRCMDFUNC)(int argc, char **argv);
```
Then I could create a user command function by making the prototype
```
static int usrcmd_printargs(int argc, char **argv);
```
### Add function to command table
The command table is an array of structures.  The sturcture contains the 
* A string of the command
* A text description - used by help
* A function pointer to the command
```
typedef struct {
    char *cmd;
    char *desc;
    USRCMDFUNC func;
} cmd_table_t;

static const cmd_table_t cmdlist[] = {
    { "help", "This is a description text string for help command.", usrcmd_help },
    { "info", "This is a description text string for info command.", usrcmd_info },
    { "clear", "Clear the screen", usrcmd_clear },
    { "printargs","print the list of arguments", usrcmd_printargs},
};
```
### Write Command
The command simply process the arguments of that command.  In this case I just print out the number of arguments (also known as argc) and then print out the arguments 1 by 1.
```
static int usrcmd_printargs(int argc, char **argv)
{
    printf("ARGC = %d\n",argc);

    for(int i =0;i<argc;i++)
    {
        printf("argv[%d] = %s\n",i,argv[i]);
    }
    return 0;

}
```

