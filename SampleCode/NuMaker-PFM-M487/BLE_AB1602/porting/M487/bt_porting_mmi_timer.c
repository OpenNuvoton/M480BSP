#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "M480.h"
#include "ab_queue.h"

/******************************************************************************
 * typedef
 ******************************************************************************/
typedef struct
{
    uint32_t hit_tick;
    uint32_t id;
    void(*mmi_timer_cb)(void *parm);
    void *parm;
    uint16_t later_tick;
    bool repeat;
} __attribute__((packed)) mmi_entry;



/******************************************************************************
 * Variable
 ******************************************************************************/
static void *mmi_queue = NULL;
static uint32_t mmi_tick = 0;

/******************************************************************************
 * Prototype
 ******************************************************************************/
void Drv_MMITimerDisable(void);

/******************************************************************************
 * Private Functions
 ******************************************************************************/
static void mmi_timer_isr(void)
{
    uint32_t cnt;
    mmi_entry *entry;

    mmi_tick++;

    cnt = AB_queue_count(mmi_queue);

    if(!cnt)
    {
        Drv_MMITimerDisable();
    }

    //find complte callback
    while(cnt)
    {
        cnt--;
        entry = AB_queue_pop(mmi_queue);

        if(entry->hit_tick <= mmi_tick)
        {
            entry->mmi_timer_cb(entry->parm);
            if(entry->repeat)
            {
                entry->hit_tick = entry->later_tick + mmi_tick;
                AB_queue_push(mmi_queue, entry);
            }
            else
            {
                AB_queue_entry_free(entry);
            }
        }
        else
            AB_queue_push(mmi_queue, entry);
    }
}

static void Drv_MMITimerEnable(uint32_t unit_100_ms, void (*foo)(void))
{
    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 10 * unit_100_ms);
    TIMER_Start(TIMER0);
}

/*isr*/
void TMR0_IRQHandler(void)
{
    if(TIMER_GetIntFlag(TIMER0) == 1)
    {
        /* Clear Timer0 time-out interrupt flag */
        TIMER_ClearIntFlag(TIMER0);
        mmi_timer_isr();
    }
}

/******************************************************************************
 * Public Functions
 ******************************************************************************/
void Drv_MMITimerDisable()
{
    TIMER_Stop(TIMER0);
}

void Ab_MMITimerSet(uint32_t id, bool repeat, uint32_t ms, void (*cb)(void*),
                    void *cb_parm)
{
    mmi_entry *entry;

    if(!mmi_queue)
    {
        mmi_queue = AB_queue_alloc();
    }

    entry = AB_queue_entry_alloc(sizeof(mmi_entry));

    entry->hit_tick = (ms + 1)/100 + mmi_tick;
    entry->mmi_timer_cb = cb;
    entry->parm = cb_parm;
    entry->id = id;
    entry->repeat = repeat;
    entry->later_tick = (ms + 1)/100;

    AB_queue_push(mmi_queue, entry);


    if(AB_queue_count(mmi_queue) == 1)
        Drv_MMITimerEnable(1, NULL);

}

void Ab_MMITimerUnset(uint32_t id)
{
    mmi_entry *entry;
    uint32_t cnt;

    //ndis_enter_critical();

    cnt = AB_queue_count(mmi_queue);

    //find complte callback
    while(cnt)
    {
        cnt--;
        entry = AB_queue_pop(mmi_queue);

        if(entry)
        {
            if(entry->id == id)
            {
                AB_queue_entry_free(entry);
            }
            else
                AB_queue_push(mmi_queue, entry);
        }
    };

    //ndis_exit_critical();

}


/*--------------------------------------------------------------------------------------------------------------*/
/* Airoha MMITimer Init                                                                                         */
/*--------------------------------------------------------------------------------------------------------------*/
void Airoha1602_MMITimerInit()
{
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);

    TIMER_EnableInt(TIMER0);
    NVIC_EnableIRQ(TMR0_IRQn);
}


