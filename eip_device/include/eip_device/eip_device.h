#ifndef EIP_DEVICE_H
#define EIP_DEVICE_H

#define INPUT_ASSEMBLY_NUM                100 //0x064
#define OUTPUT_ASSEMBLY_NUM               150 //0x096
#define CONFIG_ASSEMBLY_NUM               151 //0x097
#define HEARTBEAT_INPUT_ONLY_ASSEMBLY_NUM  152 //0x098
#define HEARTBEAT_LISTEN_ONLY_ASSEMBLY_NUM 153 //0x099
#define EXPLICT_ASSEMBLY_NUM              154 //0x09A

#define INPUT_ASSEMBLY_BUFFER_SIZE  32
#define OUTPUT_ASSEMBLY_BUFFER_SIZE  32
#define CONFIG_ASSEMBLY_BUFFER_SIZE  10
#define EXPLICIT_ASSEMBLY_BUFFER_SIZE  32

#include <iostream>
#include <string>
#include<memory>

extern "C" {
  #include "typedefs.h"
}

#include <eip_device/EipDataAsmIn.h>
#include <eip_device/EipDataAsmOut.h>
#include <eip_device/EipDataAsmExp.h>
#include <eip_device/EipDataAsmCfg.h>
#include <eip_device/EipDeviceStatus.h>


extern EipUint8 g_assembly_data064[INPUT_ASSEMBLY_BUFFER_SIZE]; /* Input */
extern EipUint8 g_assembly_data096[OUTPUT_ASSEMBLY_BUFFER_SIZE]; /* Output */
extern EipUint8 g_assembly_data097[CONFIG_ASSEMBLY_BUFFER_SIZE]; /* Config */
extern EipUint8 g_assembly_data09A[EXPLICIT_ASSEMBLY_BUFFER_SIZE]; /* Explicit */

class EipDevice
{
public:

  EipDevice() {device_status.status = -1; device_status.description = "Initialize";}
  //Callback for loading Input Assembly
  void LoadAsmIn_Callback(const eip_device::EipDataAsmIn::ConstPtr& msg);
  //Callback for loading Explicit Assembly
  void LoadAsmExp_Callback(const eip_device::EipDataAsmExp::ConstPtr& msg);

  eip_device::EipDeviceStatus device_status;
  eip_device::EipDataAsmIn data_asm_in;
  eip_device::EipDataAsmOut data_asm_out;
  eip_device::EipDataAsmCfg data_asm_cfg;
  eip_device::EipDataAsmExp data_asm_exp;
};

#endif // EIP_DEVICE_H


