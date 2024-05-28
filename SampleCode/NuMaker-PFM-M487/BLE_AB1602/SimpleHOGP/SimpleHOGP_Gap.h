#ifndef __SIMPLE_HOGP_GAP_HH
#define __SIMPLE_HOGP_GAP_HH
#include <stdint.h>
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)//hhwu
#include "arm_compat.h"
#endif
#include "bt.h"
#include <stdio.h>
/******************************************************************************/
/*Defines                                                                     */
/******************************************************************************/
typedef struct
{
    uint8_t is_bonded : 1;
    uint8_t gap_state : 3;
    uint8_t link_encrypted : 1; //supported only 1 links
    uint8_t reserved : 3;
} SimpleHOGP_Gap_Status;

typedef enum
{
    SIMPLE_INIT_FAIL,
    SIMPLE_NOT_INITED,
    SIMPLE_IDLE,
    SIMPLE_ADV_REQUESTING,
    SIMPLE_ADVING,
    SIMPLE_CONNECTED
} SimpleHOGP_Gap_State;

/******************************************************************************/
/*Variable                                                                     */
/******************************************************************************/
extern SimpleHOGP_Gap_Status gap_status;

/******************************************************************************/
/*Public function                                                             */
/******************************************************************************/
static __inline uint8_t SimpleHOGP_Gap_Bonded()
{
    return gap_status.is_bonded;
}


static __inline uint8_t SimpleHOGP_Gap_LinkEncrypted()
{
    return gap_status.link_encrypted;
}

static __inline SimpleHOGP_Gap_State SimpleHOGP_Gap_State_Get()
{
    return (SimpleHOGP_Gap_State)gap_status.gap_state;
}

static __inline void SimpleHOGP_Gap_State_Set(SimpleHOGP_Gap_State sta)
{
#if 1 //debug
    if(sta != gap_status.gap_state)
    {
        gap_status.gap_state = sta;
        printf("gap state=> ");
        switch(gap_status.gap_state)
        {
        case SIMPLE_INIT_FAIL:
            printf("init fail\n");
            break;
        case SIMPLE_NOT_INITED:
            printf("not init\n");
            break;
        case SIMPLE_IDLE:
            printf("idle\n");
            break;
        case SIMPLE_ADV_REQUESTING:
            printf("adv requesting\n");
            break;
        case SIMPLE_ADVING:
            printf("advertising\n");
            break;
        case SIMPLE_CONNECTED:
            printf("connect\n");
            break;
        }
    }
#endif

}

void SimpleHOGP_Gap_Init(uint8_t addr[6], char *name);
void SimpleHOGP_bt_evt_hdl(bt_evt_t *evt);
void SimpleHOGP_Gap_Enter_Adv(void);

ble_addr_t * SimpleHOGP_Gap_Get_BondedPeer(void);
uint8_t *SimpleHOGP_Gap_GetDeviceName(void);


#endif
