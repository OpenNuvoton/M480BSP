/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    ab_queue.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __AB_QUEUE_HH_
#define __AB_QUEUE_HH_
#include <sys/queue.h>
#include <stdint.h>

/*! 
     @defgroup PAGE_API_LIBRARY_QUEUE ab_queue.h
     @{
        @page PAGE_API_LIBRARY_QUEUE ab_queue.h 
        ab_queue.h is a queue management API set.
        
*/

/*!
    @brief Allocate a queue
*/
void * AB_queue_alloc(void);

/*!
    @brief Release a queue
    @param queue The queue @ref AB_queue_alloc
*/
void AB_queue_free(void *queue);

/*!
    @brief Query entry and data memory allocation
    @param size data memory size
*/
void * AB_queue_entry_alloc(uint32_t size);

/*!
    @brief Release a queue enrty and data memory
    @param dat The queue @ref AB_queue_entry_alloc
*/
void AB_queue_entry_free(void *dat);

/*!
    @brief Push a queue enrty into a queue
    @param queue The queue @ref AB_queue_alloc
    @param dat The queue entry @ref AB_queue_entry_alloc
*/
void AB_queue_push(void *queue, void *dat);

/*!
    @brief Push a queue enrty into a queue front
    @param queue The queue @ref AB_queue_alloc
    @param dat The queue entry @ref AB_queue_entry_alloc
*/
void AB_queue_push_front(void *queue, void *dat);

/*!
    @brief Pop a queue enrty from a queue
    @param queue The queue @ref AB_queue_alloc
*/
void * AB_queue_pop(void *queue);

/*!
    @brief Query the first queue enrty from a queue
    @param queue The queue @ref AB_queue_alloc
*/
void *AB_queue_first(void *queue);

/*!
    @brief Query the next queue enrty from current queue entry 
    @param queue The queue @ref AB_queue_alloc
    @param dat The queue entry @ref AB_queue_entry_alloc
*/
void *AB_queue_next(void *queue, void* dat);

/*!
    @brief Insert a queue enrty in current queue entry 
    @param queue The queue @ref AB_queue_alloc
    @param inqueue The queue entry @ref AB_queue_entry_alloc
    @param inserted The queue entry @ref AB_queue_entry_alloc
*/
void AB_queue_insert_after(void *queue, void* inqueue, void *inserted);

/*!
    @brief Query the queue entry of queue
    @param queue The queue @ref AB_queue_alloc
*/
uint32_t AB_queue_count(void *queue);

/*! @} */

#endif
