#include "Mapping.h"

#include <stdlib.h>
#include <map>
#include "Constants.h"

using namespace std;

static map<int, __u8> ReadMappings_21; // Read
static map<int, __u8> ReadMappings_64; // Read
static map<int, __u8> WriteMappings_20; // Write

Mapping::Mapping()
{
    ReadMappings_21[_A] = 0x0;
    ReadMappings_21[_M] = 0x1;
    ReadMappings_21[_P] = 0x2;
    ReadMappings_21[_S] = 0x3;
    ReadMappings_21[_C] = 0x4;
    ReadMappings_21[_CB] = 0x5;
    ReadMappings_21[_VAR] = 0x6;
    ReadMappings_21[_SR] = 0x7;
    ReadMappings_21[_CR] = 0x8;
    ReadMappings_21[_CBR] = 0x9;
    ReadMappings_21[_BS] = 0xA;
    ReadMappings_21[_BSR] = 0xB;
    ReadMappings_21[_BA] = 0xC;
    ReadMappings_21[_V] = 0xD;
    ReadMappings_21[_D] = 0xE;
    ReadMappings_21[_T] = 0xF;
    ReadMappings_21[_F] = 0x10;
    ReadMappings_21[_FS] = 0x11;
    ReadMappings_21[_FF] = 0x12;
    ReadMappings_21[_DO] = 0x13;
    ReadMappings_21[_E] = 0x14;
    ReadMappings_21[_B] = 0x15;
    ReadMappings_21[_CIS] = 0x16;
    ReadMappings_21[_CIA] = 0x17;
    ReadMappings_21[_CIP] = 0x18;
    ReadMappings_21[_TM] = 0x19;
    ReadMappings_21[_K] = 0x1A;
    ReadMappings_21[_DR] = 0x1B;
    ReadMappings_21[_MA] = 0x1C;
    ReadMappings_21[_MGD] = 0x1D;
    ReadMappings_21[_MGT] = 0x1E;
    ReadMappings_21[_MGM] = 0x1F;
    ReadMappings_21[_MGS] = 0x20;
    // ReadMappings_21[_FM] = 0x20;
    // ****
    ReadMappings_64[_DI] = 0x00;
    ReadMappings_64[_AI] = 0x01;
    ReadMappings_64[_AIC] = 0x02;
    ReadMappings_64[_PI] = 0x03;
    ReadMappings_64[_PIC] = 0x04;
    // ****
    WriteMappings_20[_GO] = 0x00;
    WriteMappings_20[_P] = 0x01;
    WriteMappings_20[_S] = 0x02;
    WriteMappings_20[_C] = 0x03;
    WriteMappings_20[_CB] = 0x04;
    WriteMappings_20[_VAR] = 0x05;
    WriteMappings_20[_AC] = 0x06;
    WriteMappings_20[_DC] = 0x07;
    WriteMappings_20[_DS] = 0x08;
    WriteMappings_20[_D1] = 0x09;
    WriteMappings_20[_D0] = 0x0A;
    WriteMappings_20[_H] = 0x0B;
    WriteMappings_20[_EX] = 0x0C;
    WriteMappings_20[_MG] = 0x0D;
    WriteMappings_20[_MS] = 0x0E;
    WriteMappings_20[_PR] = 0x0F;
    WriteMappings_20[_PX] = 0x10;
    WriteMappings_20[_PRX] = 0x11;
    WriteMappings_20[_AX] = 0x12;
    WriteMappings_20[_DX] = 0x13;
    WriteMappings_20[_SX] = 0x14;
    WriteMappings_20[_B] = 0x15;
    WriteMappings_20[_EES] = 0x17;
}
Mapping::~Mapping() {}

/**
 * Maps the USB/COM Defines to the SDO Objects
 * @param  cmd USB/COM Define
 * @return     SDO Index
 */
__u8 Mapping::GetReadMapping(int cmd)
{
    __u8 mappedCmd = 0;
    if (ReadMappings_21.find(cmd) != ReadMappings_21.end())
        mappedCmd = ReadMappings_21[cmd];
    else
        mappedCmd = ReadMappings_64[(__u8)cmd];
    return mappedCmd;
}
/**
 * Maps the USB/COM Defines to the SDO Objects
 * @param  cmd USB/COM Define
 * @return     SDO Index
 */
__u8 Mapping::GetWriteMapping(int cmd)
{
    __u8 mappedCmd = 0;
    if (WriteMappings_20.find(cmd) != WriteMappings_20.end())
        mappedCmd = WriteMappings_20[cmd];
    return mappedCmd;
}
