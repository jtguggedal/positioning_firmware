#ifndef TIME_SYNC_V1_CONTROLLER_H__
#define TIME_SYNC_V1_CONTROLLER_H__

#include <stdbool.h>
#include <stdint.h> 

#include "access.h"
#include "time_sync_v1_common.h"

typedef struct
{
    timestamp_t timestamp;
    uint16_t addr;
} sync_data_t;

typedef struct
{
    sync_data_t sender;
    sync_data_t reciver;
} sync_event_t;

/* Object type for rssi server instances. */
typedef struct __time_sync_controller_t time_sync_controller_t;

/** Event callback function type */ 
typedef void (*time_sync_controller_evt_cb_t)(sync_event_t sync_event);

/* Rssi server instance structure */
struct __time_sync_controller_t
{
    access_model_handle_t model_handle;
    time_sync_controller_evt_cb_t time_sync_controller_handler;
};

/* Initializes the time sync controller model.
 *
 * @param[in,out] p_server Pointer to the server instance structure.
 * @param[in] element_index Element index to use when registering the time sync controller.
 *
 * @retval NRF_SUCCESS The model was successfully initialized.
 * @retval NRF_ERROR_NULL NULL pointer in function arguments
 *
 * @see access_model_add()
 */
uint32_t time_sync_controller_init(time_sync_controller_t * p_server, uint16_t element_index, time_sync_controller_evt_cb_t time_sync_controller_handler);


void send_timestamp(void);

void sync_set_pub_timer(bool on_off);

/** @} */

#endif
