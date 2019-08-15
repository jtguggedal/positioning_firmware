#include <stdint.h>

#include "i_am_alive.h"
#include "config.h"
#include "log.h"
#include "mesh_app_utils.h"
#include "app_timer.h"
#include "hal.h"
#include "ethernet.h"
#include "command_system.h"
#include "socket.h"
#include "device_state_manager.h"

APP_TIMER_DEF(IM_ALIVE_TIMER);

void send_i_am_alive_message(void)
{
//    uint8_t buf[50];<<<<<<<<<
//    uint8_t len = 0;
//    uint8_t own_MAC[6] = {0};
//    get_own_MAC(own_MAC);
    
//    sprintf((char *)&buf[0], "I AM ALIVE - %02x:%02x:%02x:%02x:%02x:%02x", own_MAC[0], own_MAC[1], own_MAC[2], own_MAC[3], own_MAC[4], own_MAC[5]);
    dsm_local_unicast_address_t node_element_address;
    dsm_local_unicast_addresses_get(&node_element_address);
    
    command_system_package_t package;
    package.identifier = 0xDEADFACE;
    package.opcode = CMD_I_AM_ALIVE;
    get_own_MAC((uint8_t*)&package.mac);
    get_own_IP((uint8_t*)&package.payload.i_am_alive_package.ip);
    package.payload.i_am_alive_package.element_address = node_element_address.address_start;

    send_over_ethernet((uint8_t*)&package , sizeof(command_system_package_t));
}

void i_am_alive_timer_handler(void * p_unused){
//    __LOG(LOG_SRC_APP, LOG_LEVEL_INFO, "I AM ALIVE TIMER\n");
    send_i_am_alive_message();
}

void i_am_alive_timer_init(void)
{
  ERROR_CHECK(app_timer_create(&IM_ALIVE_TIMER, APP_TIMER_MODE_REPEATED, i_am_alive_timer_handler));
}

void i_am_alive_timer_start(void)
{
  ERROR_CHECK(app_timer_start(IM_ALIVE_TIMER, HAL_MS_TO_RTC_TICKS(I_AM_ALIVE_SENDING_INTERVAL), NULL));
}