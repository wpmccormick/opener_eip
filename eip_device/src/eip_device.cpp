#include "eip_device.h"

void EipDevice::LoadAsmIn_Callback(const eip_device::EipDataAsmIn::ConstPtr& msg)
{
  //clear out stale data
  memset(g_assembly_data064, 0, INPUT_ASSEMBLY_BUFFER_SIZE);
  //load data from message
  memcpy(g_assembly_data064, msg->raw_plc_data.data(), msg->raw_plc_data.size());
}

//Callback for loading Explicit Assembly
void EipDevice::LoadAsmExp_Callback(const eip_device::EipDataAsmExp::ConstPtr& msg)
{
  //clear out stale data
  memset(g_assembly_data09A, 0, EXPLICIT_ASSEMBLY_BUFFER_SIZE);
  //load data from message
  memcpy(g_assembly_data09A, msg->raw_plc_data.data(), msg->raw_plc_data.size());
}
