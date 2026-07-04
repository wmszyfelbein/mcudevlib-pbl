/******************************************* PiUE - Wojciech M. Szyfelbein  ********************************************
* PROJECT:                  PiUE Simple Console                                                                        *
* FILENAME:                 pscon.h                                                                                    *
* AUTHOR:                   Wojciech M. Szyfelbein                                                                     *
* INFO:                     This file consist declaration of all console function and needed types and macros          *
******************************************* PiUE - Wojciech M. Szyfelbein  ********************************************/

#ifndef PCON_H_INCLUDED
#define PCON_H_INCLUDED

#include <stdint.h>

#include "pscon_conf.h"

#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Option definition struct
 *
 *  This structure consist all data to define one option for the command.
 */
struct pc_Option
{
    pc_OptNameType Opt;                 //!<Character to identify option (one char only)
    pc_OptTypeType Type;                //!<Type of option defined in enum pc_OptionType
};

/*! \brief Defines types of options
 *
 *  This structure consist all data to define one option for the command.
 */
enum pc_OptionType:char
{
    pc_otEnd,                           //!<To identify last empty option in array
    pc_otFlag,                          //!<switch flags, only one letter
    pc_otInt8,                         //!<integer value, can use 0xHex 0bBinary 0Octal
    pc_otUInt8,                         //!<integer value, can use 0xHex 0bBinary 0Octal
    pc_otInt,                           //!<integer value, can use 0xHex 0bBinary 0Octal
    pc_otUInt,                          //!<integer value, can use 0xHex 0bBinary 0Octal
    pc_otStr,                           //!<string value
};

/*! \brief Command definition struct
 *
 *  This structure consist all data to define one command
 */
struct pc_Cmd
{
    char *Cmd;                          //!<Command string
    void (*Fun)(pc_IndexType iCmd);     //!<Command function which be called when command was entered
#if pc_UseOptions==1
    struct pc_Option *Opts;             //!<Pointer to array of options defines
#endif
};

/*! \brief Array of all defined commands
 *
 *  In this array should be all pointers to defined commands
 */
extern struct pc_Cmd const pcCmds[];

#define pc_BeginCmdArr struct pc_Cmd const pcCmds[]=(struct pc_Cmd[]) {
#define pc_EndCmdArr }

#if pc_UseOptions==0
#define pc_DefineCmd(name,fun) {.Cmd=name,.Fun=fun}
#endif

#if pc_UseOptions==1
#define pc_BeginCmd(name,fun) (struct pc_Cmd const){.Cmd=name,.Fun=fun,\
    .Opts=(struct pc_Option*) (struct pc_Option const[]) {
#define pc_EndCmd }}
#define pc_EndCmdList (struct pc_Cmd const){nullptr,.Fun=nullptr,.Opts=nullptr}
#define pc_DefineParam(opt,type) (struct pc_Option const){.Opt=opt,.Type=type}
#define pcEndParamList pc_DefineParam('\0',pc_otEnd)
#endif // pc_UseOptions

/*! \brief
 *
 *  Function realize command is entered
 */
extern void pc_DoCmd(void);

/*! \brief
 *
 *  Function
 */
extern enum pc_OptionType pc_GetNextPrmType(pc_IndexType iCmdCnt);

/*! \brief
 *
 *  Function
 */
 #if pc_UseOptions==1
extern char pc_GetNextPrmFlag(void);
extern int32_t pc_GetNextPrmINT32(void);
extern uint32_t pc_GetNextPrmUINT32(pc_IndexType iCmd);
extern char* pc_GetNextPrmSTR(void);

extern void pc_PrintPSConsoleVer(pc_IndexType iCmd);
#endif // pc_UseOptions
/*! \brief Run console enter task (thread or concurrence)
 *
 *  Detailed description starts here.
 */
extern void pc_Console(void);

#ifdef __cplusplus
}
#endif

#endif // PCON_H_INCLUDED


