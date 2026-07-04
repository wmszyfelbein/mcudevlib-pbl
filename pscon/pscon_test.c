/******************************************* PiUE - Wojciech M. Szyfelbein  ********************************************
* PROJECT:                  PiUE Simple Console                                                                        *
* FILENAME:                 pscon.c                                                                                    *
* AUTHOR:                   Wojciech M. Szyfelbein                                                                     *
* INFO:                     Example application for console                                                            *
******************************************** PiUE - Wojciech M. Szyfelbein  *******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#if defined(__linux__)
#include <sys/ioctl.h>
#include <termios.h>
#endif // __linux__

#if defined(WIN32)
#include <conio.h>
#endif //defined(WIN32) || defined(WIN64)

#include "pscon.h"

#ifdef __linux__

static struct termios oldattr, newattr;
void pc_InitTrmCon(void)
{
   tcgetattr( STDIN_FILENO, &oldattr );
   newattr=oldattr;
   newattr.c_lflag &= ~(ICANON | ECHO);
   newattr.c_oflag &= ~(OCRNL);
   newattr.c_iflag &= ~(IGNCR | ICRNL);
   tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
   tcsetattr( STDOUT_FILENO, TCSANOW, &newattr );
}

void pc_DeInitTrmCon(void)
{
   tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
   tcsetattr( STDOUT_FILENO, TCSANOW, &newattr );
}

#define _getch getchar

#endif // __linux__

#if defined(WIN32) || defined(WIN64)

#define pc_InitTrmCon()
#define pc_DeInitTrmCon()

#endif // defined(WIN32) || defined(WIN64)

char pc_TstGetCh(void)
{
   return (char)_getch();
}

void pc_TstPutCh(char ch)
{
   (void)putchar((int)ch);
}


//----------------------------------------------------------------------------------------------------------------------
#if pc_UseOptions==0
void Fun1(void)
{
    printf("\n\rFun1 z 2\n\r");
}

void Fun2(void)
{
    printf("\n\rFun2 z 2\n\r");
}
#endif
#if pc_UseOptions==1
void Fun1p(void)
{
    printf("\n\rFun1 z 2\n\r");
}

void Fun2p(void)
{
    printf("\n\rFun2 z 2\n\r");
}
#endif //pc_UseOptions==0

void Exit(void)
{
    printf("Exit\n\r");
    exit(0);
}

#if pc_UseOptions==0
pc_BeginCmdArr
    pc_DefineCmd("cmd1", Fun1),
    pc_DefineCmd("cmd2", Fun2),
    pc_DefineCmd("exit", Exit),
pc_EndCmdArr;
#endif

#if pc_UseOptions==1
pc_BeginCmdArr
    pc_BeginCmd("cmd1p",Fun1p)
        pc_DefineParam('1',pc_otFlag),
        pc_DefineParam('3',pc_otFlag),
        pc_DefineParam('3',pc_otEnd),
    pc_EndCmd,
    pc_BeginCmd("cmd2p",Fun2p)
        pc_DefineParam('1',pc_otFlag),
        pc_DefineParam('3',pc_otFlag),
        pc_DefineParam('3',pc_otEnd),
    pc_EndCmd,
    pc_BeginCmd("exit",Exit)
        pc_DefineParam('3',pc_otEnd),
    pc_EndCmd,
    pc_EndCmdList
pc_EndCmdArr;
#endif



int main()
{
    pc_InitTrmCon();
    while (pc_ConType == pc_cConTypeConcurrence) pc_Console();
    pc_DeInitTrmCon();
    return 0;
}
