#ifndef __RoboteqDevice_H_
#define __RoboteqDevice_H_

#include "ComAPI.h"

class RoboteqDevice
{
private:
    ComAPI com;
public:
    bool IsConnected();
    void Disconnect();

    int SetConfig(int configItem, int index, int value);
    int SetConfig(int configItem, int value);
    int SetRawConfig(int configItem, std::string str);

    int SetCommand(int commandItem, int index, int value);
    int SetCommand(int commandItem, int value);
    int SetCommand(int commandItem);

    int GetConfig(int configItem, int index, int &result);
    int GetConfig(int configItem, int &result);
    int GetRawConfig(int configItem, std::string &result);

    int GetValue(int operatingItem, int index, int &result);
    int GetValue(int operatingItem, int &result);
    int GetRawValue(int operatingItem, std::string &result);

    RoboteqDevice(int type);
    ~RoboteqDevice();
};

#endif
