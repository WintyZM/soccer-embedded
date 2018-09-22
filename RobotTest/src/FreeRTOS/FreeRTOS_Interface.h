/**
  *****************************************************************************
  * @file    FreeRTOS_Interface.h
  * @author  Izaak Niksan
  * @brief   TODO -- brief description of file
  *
  * @defgroup Header
  * @ingroup  FreeRTOS_Interface
  * @{
  *****************************************************************************
  */


#ifndef __FREERTOS_INTERFACE_H__
#define __FREERTOS_INTERFACE_H__



/********************************* Includes **********************************/
#include "FreeRTOS_Interface.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "cmsis_os.h"

namespace freertos {
// Classes and structs
// ----------------------------------------------------------------------------
#define xQueueReceive( xQueue, pvBuffer, xTicksToWait ) xQueueGenericReceive( ( xQueue ), ( pvBuffer ), ( xTicksToWait ), pdFALSE );
#define xQueueSend( xQueue, pvItemToQueue, xTicksToWait ) xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ), queueSEND_TO_BACK );
#define xSemaphoreTake( xSemaphore, xBlockTime )        xQueueGenericReceive( ( QueueHandle_t ) ( xSemaphore ), NULL, ( xBlockTime ), pdFALSE );
//Also defined as xQueueGenericSend()
#define xSemaphoreGive( xSemaphore )        xQueueGenericSend( ( QueueHandle_t ) ( xSemaphore ), NULL, semGIVE_BLOCK_TIME, queueSEND_TO_BACK );


class FreeRTOS_Interface{
public:
    //TODO: Why aren't the typedefs from portmacro.h (ie BaseType_t) not being picked up?
    virtual ~FreeRTOS_Interface() {}
    virtual BaseType_t xTaskNotifyWait( uint32_t ulBitsToClearOnEntry, uint32_t ulBitsToClearOnExit, uint32_t *pulNotificationValue, TickType_t xTicksToWait );
    virtual BaseType_t xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait, const BaseType_t xJustPeeking );
    virtual BaseType_t xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait, const BaseType_t xCopyPosition );
    virtual void vTaskDelayUntil( TickType_t * const pxPreviousWakeTime, const TickType_t xTimeIncrement );
    virtual osStatus osDelay (uint32_t millisec);

};

} // end namespace freertos

/**
 * @}
 */
/* end - Header */

#endif /* __FREERTOS_INTERFACE_H__ */
