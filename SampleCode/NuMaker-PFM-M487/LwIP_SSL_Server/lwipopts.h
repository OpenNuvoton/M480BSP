/**
 * @file
 *
 * lwIP Options Configuration
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/*
 * Include user defined options first. Anything not defined in these files
 * will be set to standard values. Override anything you dont like!
 */

#define NO_SYS                          0
#define MEM_ALIGNMENT                   4
#define LWIP_STATS                      0
#define LWIP_SOCKET_SET_ERRNO           0

#define LWIP_RAND                       xTaskGetTickCount
#define LWIP_DNS                        1
//#define LWIP_DHCP                       1
#define LWIP_POSIX_SOCKETS_IO_NAMES     1
#define SO_REUSE                        1
#if defined ( __GNUC__ ) && !(__CC_ARM) && !(__ICCARM__) && !(__ARMCC_VERSION)
#define LWIP_TIMEVAL_PRIVATE            0
#include <sys/time.h>   //Include the correct header file that defines struct timeval.
#endif

#define TCPIP_THREAD_STACKSIZE          350
#define TCPIP_THREAD_PRIO               2
#define TCPIP_MBOX_SIZE                 10
#define DEFAULT_TCP_RECVMBOX_SIZE       5
#define DEFAULT_ACCEPTMBOX_SIZE         5
#define DEFAULT_UDP_RECVMBOX_SIZE       5
#define DEFAULT_RAW_RECVMBOX_SIZE       5

#define MEM_SIZE                        10000

#endif /* __LWIPOPTS_H__ */
