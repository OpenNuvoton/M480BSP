/***************************************************************************//**
 * @file     lbk_driver.h
 * @version  1.0.1
 * @brief    M480 MCU USB Host Vendor LBK driver header file
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __LBK_DRIVER_H_
#define __LBK_DRIVER_H_


/*-------------------------------------------------------------*/
/* Vendor LBK device ID  */
#define LBK_VENDOR_ID     0x0416
#define LBK_DEVICE_ID     0xff20

/*-------------------------------------------------------------*/
/* Vendor LBK device vendor commands   */
#define REQ_SET_DATA                   0x01
#define REQ_GET_DATA                   0x12


#define ISO_UTR_NUM       2

typedef int (INT_CB_FUNC)(int status, uint8_t *rdata, int data_len);
typedef int (ISO_CB_FUNC)(uint8_t *rdata, int data_len);


/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
extern void usbh_lbk_init(void);
extern int  lbk_device_is_connected(void);
extern int  lbk_device_is_high_speed(void);
extern int  lbk_device_reset(void);
extern int  lbk_vendor_set_data(uint8_t *buff);
extern int  lbk_vendor_get_data(uint8_t *buff);
extern int  lbk_bulk_write(uint8_t *data_buff, int data_len, int timeout_ticks);
extern int  lbk_bulk_read(uint8_t *data_buff, int data_len, int timeout_ticks);
extern int  lbk_interrupt_in_start(INT_CB_FUNC *func);
extern void lbk_interrupt_in_stop(void);
extern int  lbk_interrupt_out_start(INT_CB_FUNC *func);
extern void lbk_interrupt_out_stop(void);
extern int  lbk_isochronous_in_start(ISO_CB_FUNC *func);
extern void lbk_isochronous_in_stop(void);
extern int  lbk_isochronous_out_start(ISO_CB_FUNC *func);
extern void lbk_isochronous_out_stop(void);

#endif  /* __LBK_DRIVER_H_ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
