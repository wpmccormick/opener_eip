#ifndef EIP_DEVICE_H
#define EIP_DEVICE_H

#include <iostream>
#include <string>
#include<memory>

extern "C" {
  #include "typedefs.h"
}

#include <eip_device/EipDataToPLC.h>
#include <eip_device/EipDataFmPLC.h>
#include <eip_device/EipConfig.h>
#include <eip_device/EipDeviceStatus.h>


extern EipUint8 g_assembly_data064[32]; /* Input */
extern EipUint8 g_assembly_data096[32]; /* Output */
extern EipUint8 g_assembly_data097[10]; /* Config */
extern EipUint8 g_assembly_data09A[32]; /* Explicit */

class EipDevice
{
public:

  EipDevice() {device_status.status = -1; device_status.description = "Initialize";}
  void toplcCallback(const eip_device::EipDataToPLC::ConstPtr& msg);

  eip_device::EipDeviceStatus device_status;
  eip_device::EipDataToPLC data_toplc;
  eip_device::EipDataFmPLC data_fmplc;
  eip_device::EipConfig data_config;
};

#endif // EIP_DEVICE_H


