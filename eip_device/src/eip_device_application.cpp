/*******************************************************************************
 * Copyright (c) 2012, Rockwell Automation, Inc.
 * All rights reserved.
 *
 ******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

extern "C" {
  #include "opener_api.h"
  #include "appcontype.h"
  #include "trace.h"
  #include "cipidentity.h"
  #include "typedefs.h"
}

#include "eip_device.h"

#define INPUT_ASSEMBLY_NUM                100 //0x064
#define OUTPUT_ASSEMBLY_NUM               150 //0x096
#define CONFIG_ASSEMBLY_NUM               151 //0x097
#define HEARTBEAT_INPUT_ONLY_ASSEMBLY_NUM  152 //0x098
#define HEARTBEAT_LISTEN_ONLY_ASSEMBLY_NUM 153 //0x099
#define EXPLICT_ASSEMBLY_NUM              154 //0x09A

/* global variables for demo application (4 assembly data fields)  ************/

extern CipUint g_encapsulation_inactivity_timeout;
extern EipDevice eipDevice;

EipUint8 g_assembly_data064[32]; /* Input */
EipUint8 g_assembly_data096[32]; /* Output */
EipUint8 g_assembly_data097[10]; /* Config */
EipUint8 g_assembly_data09A[32]; /* Explicit */

EipStatus ApplicationInitialization(void) {
  /* create 3 assembly object instances*/
  /*INPUT*/
  CreateAssemblyObject( INPUT_ASSEMBLY_NUM, g_assembly_data064,
                        sizeof(g_assembly_data064) );

  /*OUTPUT*/
  CreateAssemblyObject( OUTPUT_ASSEMBLY_NUM, g_assembly_data096,
                        sizeof(g_assembly_data096) );

  /*CONFIG*/
  CreateAssemblyObject( CONFIG_ASSEMBLY_NUM, g_assembly_data097,
                        sizeof(g_assembly_data097) );

  /*Heart-beat output assembly for Input only connections */
  CreateAssemblyObject(HEARTBEAT_INPUT_ONLY_ASSEMBLY_NUM, NULL, 0);

  /*Heart-beat output assembly for Listen only connections */
  CreateAssemblyObject(HEARTBEAT_LISTEN_ONLY_ASSEMBLY_NUM, NULL, 0);

  /* assembly for explicit messaging */
  CreateAssemblyObject( EXPLICT_ASSEMBLY_NUM, g_assembly_data09A,
                        sizeof(g_assembly_data09A) );

  ConfigureExclusiveOwnerConnectionPoint(0, OUTPUT_ASSEMBLY_NUM,
                                         INPUT_ASSEMBLY_NUM,
                                         CONFIG_ASSEMBLY_NUM);
  ConfigureInputOnlyConnectionPoint(0,
                                    HEARTBEAT_INPUT_ONLY_ASSEMBLY_NUM,
                                    INPUT_ASSEMBLY_NUM,
                                    CONFIG_ASSEMBLY_NUM);
  ConfigureListenOnlyConnectionPoint(0,
                                     HEARTBEAT_LISTEN_ONLY_ASSEMBLY_NUM,
                                     INPUT_ASSEMBLY_NUM,
                                     CONFIG_ASSEMBLY_NUM);

  return kEipStatusOk;
}

void HandleApplication(void) {
  /* check if application needs to trigger an connection */
}

void CheckIoConnectionEvent(unsigned int output_assembly_id,
                            unsigned int input_assembly_id,
                            IoConnectionEvent io_connection_event) {
  /* maintain a correct output state according to the connection state*/

  eipDevice.device_status.status = io_connection_event;
  switch(io_connection_event)
  {
    case kIoConnectionEventClosed:
      eipDevice.device_status.description = "Device Closed";
      break;
    case kIoConnectionEventOpened:
      eipDevice.device_status.description = "Device Opened";
      break;
    case kIoConnectionEventTimedOut:
      eipDevice.device_status.description = "Device Timed Out";
      break;
    default:
      eipDevice.device_status.description = "Device Status Not Defined";
  }

  (void) output_assembly_id; /* suppress compiler warning */
  (void) input_assembly_id; /* suppress compiler warning */
}

EipStatus AfterAssemblyDataReceived(CipInstance *instance) {
  EipStatus status = kEipStatusOk;

  /*handle the data received e.g., update outputs of the device */
  switch (instance->instance_number) {
    case OUTPUT_ASSEMBLY_NUM : break;
    case EXPLICT_ASSEMBLY_NUM: break;
    case CONFIG_ASSEMBLY_NUM :
      status = kEipStatusOk;
      break;
    default:
      OPENER_TRACE_INFO(
        "Unknown assembly instance ind AfterAssemblyDataReceived");
      break;
  }
  return status;
}

EipBool8 BeforeAssemblyDataSend(CipInstance *pa_pstInstance) {
  /*update data to be sent e.g., read inputs of the device */
  /*In this sample app we mirror the data from out to inputs on data receive
   * therefore we need nothing to do here. Just return true to inform that
   * the data is new.
   */

  if (pa_pstInstance->instance_number == EXPLICT_ASSEMBLY_NUM) {
    /* do something interesting with the existing data
     * for the explicit get-data-attribute message */
  }
  return true;
}

EipStatus ResetDevice(void) {
  /* add reset code here*/
  CloseAllConnections();
  return kEipStatusOk;
}

EipStatus ResetDeviceToInitialConfiguration(void) {
  /*rest the parameters */
  g_encapsulation_inactivity_timeout = 120;
  /*than perform device reset*/
  ResetDevice();
  return kEipStatusOk;
}

void *
CipCalloc(size_t number_of_elements,
          size_t size_of_element) {
  return calloc(number_of_elements, size_of_element);
}

void CipFree(void *data) {
  free(data);
}

void RunIdleChanged(EipUint32 run_idle_value) {
  OPENER_TRACE_INFO("Run/Idle handler triggered\n");
  if( (0x0001 & run_idle_value) == 1 ) {
    CipIdentitySetExtendedDeviceStatus(kAtLeastOneIoConnectionInRunMode);
  } else {
    CipIdentitySetExtendedDeviceStatus(
      kAtLeastOneIoConnectionEstablishedAllInIdleMode);
  }
  (void) run_idle_value;
}

