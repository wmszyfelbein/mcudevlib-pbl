/******************************************* PiUE - Wojciech M. Szyfelbein  ********************************************
* FILENAME:                 pscon_conf.h                                                                               *
* AUTHOR:                   Wojciech M. Szyfelbein                                                                     *
* DESCRIPTION:                                                                                                         *
*		This file define of base types                                                                                 *
******************************************* PiUE - Wojciech M. Szyfelbein  ********************************************/

#ifndef PSCON_CONF_H_INCLUDED
#define PSCON_CONF_H_INCLUDED

#include <stdint.h>


//!Defines type used to any index/counter type. Char type generates small (on tested) code in 8b micro-controller.
//!For 16+b should be int..
#define pc_IndexType char

//!Size of input buffer. Type of array is char
#define pc_InBufferSize (10)

//!pc_ConType - Execution type.
#define pc_ConType (pc_cConTypeConcurrence)
//!pc_ConTypeThread - There is a special thread for execute console. pc_GetChar - macro should block thread
#define pc_ConTypeThread (1)
//!pc_cConTypeConcurrence - There in not a thread for console. Library remember state of between call pc_Console.
#define pc_cConTypeConcurrence (0)

//!Defines function to put function
#define pc_PutChar(x) pc_TstPutCh(x)
//!Defines function to get char from the input
#define pc_GetChar pc_TstGetCh

//!Defines how many commands in command array
#define pc_CmdCnt (3)

//!Info string displayed if command not in command array
#define pc_sInfoNoCmd "Command doasn't exist"



extern char pc_TstGetCh(void);
extern void pc_TstPutCh(char ch);

#endif // PSCON_CONF_H_INCLUDED
