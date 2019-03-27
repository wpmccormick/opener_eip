#include "eip_device.h"

void EipDevice::LoadAsmIn_Callback(const eip_device::EipDataAsmIn::ConstPtr& msg)
{
   memcpy(g_assembly_data064, msg->raw_plc_data.data(), INPUT_ASSEMBLY_BUFFER_SIZE);
}

//Callback for loading Explicit Assembly
void EipDevice::LoadAsmExp_Callback(const eip_device::EipDataAsmExp::ConstPtr& msg)
{
   memcpy(g_assembly_data09A, msg->raw_plc_data.data(), EXPLICIT_ASSEMBLY_BUFFER_SIZE);
}
