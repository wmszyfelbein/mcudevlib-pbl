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

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Command definition struct
 *
 *  This structure consist all data to define one command
 */
struct pc_Cmd
{
    char *Cmd;                          //!<Command string
    void (*Fun)(void);                  //!<Command function which be called when command was entered
};

/*! \brief Array of all defined commands
 *
 *  In this array should be all pointers to defined commands
 */
extern struct pc_Cmd pcCmds[];

/*! \brief
 *
 *  Function realize command is entered
 */
extern void pc_DoCmd(void);

/*! \brief Run console enter task (thread or concurrence)
 *
 *  Detailed description starts here.
 */
extern void pc_Console(void);

enum
{
    pc_CmdReady=-1,
};

#ifdef __cplusplus
}
#endif

#endif // PCON_H_INCLUDED


