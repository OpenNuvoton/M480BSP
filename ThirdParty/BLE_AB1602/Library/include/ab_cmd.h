#ifndef __AB_VCMD_HH
#define __AB_VCMD_HH
#include <stdint.h>
#include <stdbool.h>
/*--------------------------------------------------------------------------------------------*/
/* Type Define                                                                                */
/*--------------------------------------------------------------------------------------------*/
typedef struct
{    
    uint16_t op;
    uint8_t len;
    uint8_t *param;
}AB_CMD;

typedef struct
{
    uint16_t rlen;
    uint8_t *param;
}AB_RESP;

typedef struct
{
    bool (*rxcb)(uint8_t* buf, uint16_t len);
    bool (*handlers)(AB_CMD *cmd, AB_RESP *resp);
    void (*txcb)(uint8_t* buf, uint16_t len);
}AB_CMD_DECODER;

typedef bool (*AB_CMD_HANDLER)(AB_CMD *cmd, AB_RESP *resp);

/*--------------------------------------------------------------------------------------------*/
/* Define                                                                                     */
/*--------------------------------------------------------------------------------------------*/
#include "ab_cmd_opcode.h"
#define AB_HANDLER_MAX 3
/*--------------------------------------------------------------------------------------------*/
/* Public                                                                                     */
/*--------------------------------------------------------------------------------------------*/

void AB_CmdTransport(uint8_t* rbuf, uint16_t rlen, void (*txcb)(uint8_t* tbuf, uint16_t tlen));
bool AB_CmdSetDecoder(AB_CMD_DECODER *decoder);
bool AB_CmdSetHandler(uint8_t index, AB_CMD_HANDLER handler);

#endif
