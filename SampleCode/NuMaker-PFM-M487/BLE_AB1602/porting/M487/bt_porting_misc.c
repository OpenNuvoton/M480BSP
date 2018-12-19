#include <stdint.h>
#include <stdlib.h>
#include "M480.h"
#include "bt_porting.h"
/******************************************************************************
 * typedef
 ******************************************************************************/

/******************************************************************************
 * Variable
 ******************************************************************************/
volatile uint32_t CRITICAL_DEPTH = 0;
uint8_t is_airoha_1602_module_on = 0;

extern const int hci_builtin_ab1602;
extern const int hci_h4_ab1602;

/******************************************************************************
 * Prototype
 ******************************************************************************/
extern void Airoha1602_PinInit(void);
extern void Airoha1602_MMITimerInit(void);

/******************************************************************************
 * Private Functions
 ******************************************************************************/
void DRV_TRNG_Get(uint8_t *buf, uint8_t len)
{
    int seed, i;
    seed = FMC_ReadUID(0);
    srand(seed);
    for(i = 0; i < len; i++)
        buf[i] = (uint8_t)rand();
}

void DRV_MCU_ClearCache(void)
{
    return;
}

void OS_delay_us(uint32_t us)
{
    CLK_SysTickDelay(us);
}

/******************************************************************************
 * Public Functions
 ******************************************************************************/
uint32_t Airoha_PortingInit()
{
    Airoha1602_PinInit();
    Airoha1602_MMITimerInit();

    return (uint32_t)&hci_builtin_ab1602 || (uint32_t)&hci_h4_ab1602;
}
