#include <stdio.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "pscon.h"

//----------------------------------------------------------------------------------------------------------------------
static int pc_Terminal;

char pc_TstGetCh(void)
{
   char ch=0;
   read(pc_Terminal,&ch,1);
   return ch;
}

void pc_TstPutCh(char ch)
{
   write(pc_Terminal,&ch,1);
}

static struct termios oldattr, newattr;
int pc_InitTrmCon(void)
{
   pc_Terminal = open("/dev/tty", O_RDWR | O_NOCTTY);
   if (pc_Terminal<=0) {
      return pc_Terminal;
   }
   tcgetattr( STDIN_FILENO, &oldattr );
   newattr=oldattr;
   newattr.c_lflag &= ~(ICANON | ECHO);
   newattr.c_oflag &= ~(OCRNL);
   newattr.c_iflag &= ~(IGNCR | ICRNL);
   tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
   tcsetattr( STDOUT_FILENO, TCSANOW, &newattr );
   return pc_Terminal;
}

void pc_DeInitTrmCon(void)
{
   close(pc_Terminal);
   tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
   tcsetattr( STDOUT_FILENO, TCSANOW, &newattr );
}

//----------------------------------------------------------------------------------------------------------------------
void Fun1(void)
{
    printf("\n\rFun1 z 2\n\r");
}

void Fun2(void)
{
    printf("\n\rFun2 z 2\n\r");
}

void Exit(void)
{
    exit(0);
}

struct pc_Cmd pcCmds[] =
{
    {"cmd1", Fun1},
    {"cmd2", Fun2},
    {"exit", Exit}
};


int main()
{
   printf("START\n");
   pc_InitTrmCon();
   pc_Console();
   pc_DeInitTrmCon();
   printf("\nEND\n");
   return 0;
}
