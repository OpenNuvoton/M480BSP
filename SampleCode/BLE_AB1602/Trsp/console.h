/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    console.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __CONSLE_HH
#define __CONSLE_HH

/*!
     @defgroup PAGE_API_LIBRARY_CONSOLE console.h
     @{
        @page PAGE_API_LIBRARY_CONSOLE console.h
        console.h is an convient shell terminal API set which allow user to get/set command in shell terminal.

*/

/*************************************************************/
/*Macro Definitions*/
/*************************************************************/

/*!
     @name The return value definition
     @{
*/
#define RET_SUCCESS 0
#define RET_NOT_FOUND -1
#define RET_INVALID_PARAM -2
#define RET_WRONG_PRARM_NUMBER -3
#define RET_CONSOLE_EXIT -4
/*!  @} */

/*************************************************************/
/*Type Definitions*/
/*************************************************************/

/*!
    @brief Callback function of the registered @ref console_cmd_tbl
    @param context Command context
    @param argc Number of parameters
    @param argv Parameter array
*/
typedef int (*cmd_func_t)(void *context, int argc, char** argv);

/*!
    @brief Shell terminal command table for @ref AB_console_init
*/
typedef struct console_cmd_tbl
{
    char *name;                                /**< Command name */
    cmd_func_t cmd;                            /**< Callback function */
    const struct console_cmd_tbl *argv1_tbl;   /**< Next command */
} console_cmds_t;

/*************************************************************/
/*Type Definitions*/
/*************************************************************/
/*!
    @brief Shell Terminal Initialize
    @param prompt The prompt characters (ex. shell >)
    @param send_data Peripheral type (UART, BT ...)
    @param cmds The command set @ref console_cmds_t
*/
void AB_console_init(const char* prompt, void (*send_data)(const unsigned char *buf, unsigned short len), console_cmds_t *cmds);

/*!
    @brief Handle the data from peripheral
    @param dat The data which got from peripheral
    @param len the data length of dat
    @return true if success, else console not exist.
*/
bool AB_console_handle(uint8_t *dat, uint16_t len);

/*!
    @brief User input
*/
void AB_console_UserInput(char *title, cmd_func_t func);

/*! @} */

#endif
