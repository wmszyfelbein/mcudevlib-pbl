/******************************************* PiUE - Wojciech M. Szyfelbein  ********************************************
* FILENAME:                 pscon.c                                                                                    *
* AUTHOR:                   Wojciech M. Szyfelbein                                                                     *
* DESCRIPTION:                                                                                                         *
*		                                                                                                               *
******************************************** PiUE - Wojciech M. Szyfelbein  *******************************************/

#include <stdio.h>
#include <stdlib.h>

#include "pscon.h"

static char PCInBuffer[pc_InBufferSize];
static pc_IndexType pc_iCurPos;


static void pc_Print(char* sStr) {
    while(*sStr) pc_PutChar(*sStr++);
}

static pc_IndexType pc_FindStCmd(void)
{
    pc_IndexType iPos;
    for (iPos=0; PCInBuffer[iPos]==' '
        && iPos<pc_InBufferSize; iPos++);
    return iPos;
}

static pc_IndexType pc_FindSpCmd(pc_IndexType iPos)
{
    for(;PCInBuffer[iPos]!='\0' && PCInBuffer[iPos]!=' ' && iPos<pc_InBufferSize; iPos++);
    return iPos;
}

static void pc_PrepNewLine(void)
{
    pc_Print("\r\n");
    pc_iCurPos=0;
}

void pc_GetCmdLine(void) {
    do {
        char cChar=pc_GetChar();
        switch (cChar) {
            case '\b': case '\x7f':
                if (pc_iCurPos==0) continue;
                pc_Print("\b \b");
                pc_iCurPos--;
                continue;
            case '\r':case '\n':
                PCInBuffer[pc_iCurPos++]='\0';
                pc_iCurPos=pc_CmdReady;
                return;
            default:
                if (!(cChar>=' ' && cChar<='~')) continue;
                if (pc_iCurPos>=(pc_InBufferSize-1)) continue;
                PCInBuffer[pc_iCurPos++]=cChar;
        }
        pc_PutChar(cChar);
    } while (pc_ConType == pc_ConTypeThread);
}

void pc_DoCmd(void)
{
    if (pc_iCurPos!=pc_CmdReady) return;
    pc_IndexType iStCmd = pc_FindStCmd();
    pc_IndexType iSpCmd = pc_FindSpCmd(iStCmd);
    pc_IndexType iCmdCnt;
    for(iCmdCnt=0;iCmdCnt<pc_CmdCnt;iCmdCnt++) {
        pc_IndexType iLnChrCnt;
        pc_IndexType iCmdChrCnt;
        for(iLnChrCnt=iStCmd,iCmdChrCnt=0;iLnChrCnt<=iSpCmd;iLnChrCnt++,iCmdChrCnt++) {
            if ((pcCmds[iCmdCnt].Cmd[iCmdChrCnt]=='\0') &&
                ((PCInBuffer[iLnChrCnt]=='\0') || PCInBuffer[iLnChrCnt]==' ')) {
                //command found, do it
                pcCmds[iCmdCnt].Fun();
                pc_PrepNewLine();
                return;
            }
            if ((pcCmds[iCmdCnt].Cmd[iCmdChrCnt]==PCInBuffer[iLnChrCnt]) && (pcCmds[iCmdCnt].Cmd[iCmdChrCnt]!=0))
                continue;
            //command did't find or test next command
            break;
        }
    }
    pc_Print("\r\n"pc_sInfoNoCmd);
    pc_PrepNewLine();
}

void pc_Console(void)
{
    while(1)
    do {
        pc_GetCmdLine();
        pc_DoCmd();
    } while (pc_ConType == pc_ConTypeThread);
}
