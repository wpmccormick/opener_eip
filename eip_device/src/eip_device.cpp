#include "eip_device.h"

void EipDevice::toplcCallback(const eip_device::EipDataToPLC::ConstPtr& msg)
{
   memcpy(g_assembly_data064, msg->raw_plc_data.data(), 32);
}
