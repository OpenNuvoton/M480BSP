#ifndef AB_MOUNT_HCI_HH
#define AB_MOUNT_HCI_HH
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
bool hci_send(uint8_t *buf, uint8_t len);
bool hci_mount(void (*rxdat_cb) (uint8_t* buf, uint8_t len));

#endif
