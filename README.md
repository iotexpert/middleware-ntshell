# middleware-ntshell

An Implementation of NTShell for MBEDOS and PSoC6/FreeRTOS

This library is a modified (very slightly) version of the Natural Tiny Shell by Shinichiro Nakamura (CuBeatSystems).  This project his hosted at https://www.cubeatsystems.com/ntshell/

The NTShell is a really simple shell for smallish embedded systems.  It understands VT100 terminals and provides nice features like command history.

I provided a configuration of ntshell that works with stdin/stdout using normal printf, getchar, putchar etc.

Inside of the project I included a template directory which contains example code which will work with MBED and the PSoC 6 SDK.  In both cases the NTShell is located inside of a thread and both examples include some user commands inside of usrcmd.h/c

I built a thread inside of usrcmd.c which you will need to start wherever you start the other threads.  The task function is named usrcmd_task and is defined in usrcmd.h

# Add library to your Modus Toolbox project using the library manager
By far the easiest way to add this library to your project is to update your Library manager to know about the IoT Expert projects, middleware and board support packages.  To do this update the file "~/.modustoolbox/manifest.loc" by adding
* https://github.com/iotexpert/mtb2-iotexpert-manifests/raw/master/iotexpert-super-manifest.xml

I describe this in detail at
https://github.com/iotexpert/mtb2-iotexpert-manifests

When you start the library manager you will now see the IoT Expert Library with NT Shell.

# How to manually add ntshell library using Modus 2.2 (Modus Flow)
For the "Modus Flow" you need to create a file called "deps/middleware-ntshell.mtb" with a connection to the library.  The easiest method to create this is:
* echo "https://github.com/iotexpert/middleware-ntshell#latest-v2.X#$$ASSET_REPO$$/middleware-ntshell/latest-v2.X" > deps/middleware-ntshell.mtb
* make getlibs

# How to manually add ntshell library using Modus 2.1 (dot lib flow)
If you are using the "dot lib flow from Modus Toolbox 2.1" you can create a dot lib like this:

To use this with a project you need to create a "dot lib" file inside of your project.  That file should contain the URL for the library.  On the command line you need to run the three commands:
* echo "https://github.com/iotexpert/middleware-ntshell/#master" > middleware-ntshell.lib
* make getlibs

# Get the source templates
To get everything going the easiest thing to do is coply the command templates into your project.

Copy the template usrcmd.h and usrcmd.c from the correct location either

* cp ../mtb_shared/middleware-ntshell/latest-v2.X/template/psoc6sdk/usrcmd.* .

or

* cp libs/middleware-ntshell/template/psoc6sdk/usrcmd.* .

Then modify your main.c to include the neccesary includes

```
#include "usrcmd.h"
```

Then add the startup of the task (which is defined in usercmd.h).  The ntshell inside of the usrcmd_task function uses stdio and needs more stack.  I picked 4 empircally by printing out stack sizes.

```
xTaskCreate(nts_task, "nt shell task", configMINIMAL_STACK_SIZE*4,0 /* args */ ,0 /* priority */, 0);
```


# How to add to MBED OS

To use this project add it to your mbed project with
* mbed add git@github.com:iotexpert/middleware-ntshell.git

or

* mbed add https://github.com/iotexpert/middleware-ntshell.git

Then copy the template files into your project
* cp mbed-os-ntshell/template/mbed/* .

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
# Adding Commands
Adding commands to the shell is the same for MBEDOS and the PSoC6 SDK

## To add commands
In the file usrcmd.c you need to make three changes
1. Add a function prototype for your command
2. Add the new command to the cmdlist array
3. Write your actual function

## Add function prototype
The function prototype for command functions is:
```
typedef int (*USRCMDFUNC)(int argc, char **argv);
```
Here is an example of a command function prototype that will print out the arguments.
```
static int usrcmd_printargs(int argc, char **argv);
```
## Add function to command table
The command table is an array of structures.  The structure contains: 
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
## Write Command

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


