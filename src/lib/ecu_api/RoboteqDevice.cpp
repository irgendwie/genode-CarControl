#include <iostream>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <time.h>
#include <sstream>
#include <unistd.h>
#include "ErrorCodes.h"
#include "RoboteqDevice.h"
#include <base/printf.h>

using namespace std;

RoboteqDevice::RoboteqDevice(int type) : com(type)
{}
RoboteqDevice::~RoboteqDevice()
{}
/**
 * Checks if the Device is Connected (Only calling ComAPI)
 * @return connected?
 */
bool RoboteqDevice::IsConnected()
{
    return true;//com.IsConnected();
}
/**
 * Send the rquested Command to the Controller
 * @param  configItem  Determines which Command is issued
 * @param  index       Determines which Value will be returned
 * @param  value       Determines what value is issued
 * @return             RQ Status flags
 */
int RoboteqDevice::SetConfig(int configItem, int index, int value)
{
    string response;
    if (configItem < 0 || configItem > 255)
        return RQ_INVALID_CONFIG_ITEM;

    if (index < 0)
        return RQ_INDEX_OUT_RANGE;

    int status = com.IssueCommand("^", configItem, index, to_string(value), response, true);
    if (status != RQ_SUCCESS)
        return status;
    if (response != "+")
        return RQ_SET_CONFIG_FAILED;

    return RQ_SUCCESS;
}
/**
 * Calls the SetConfig(int, int, int) Method with index set to 1
 * @param  configItem Determines which Command is issued
 * @param  value      Determines what value is issued
 * @return            RQ Status Flags
 */
int RoboteqDevice::SetConfig(int configItem, int value)
{
    return SetConfig(configItem, 1, value);
}
/**
 * !! USE ONLY IF YOU KNOW WHAT YOU ARE DOING !! Not supported ATM
 * @param  configItem Determines which Command is issued
 * @param  str        args to pass
 * @return            RQ Status Flags
 */
int RoboteqDevice::SetRawConfig(int configItem, string str)
{
    string response;

    if (configItem < 0 || configItem > 255)
        return RQ_INVALID_CONFIG_ITEM;

    int status = com.IssueCommand("^", configItem, 0, str, response, true);
    if (status != RQ_SUCCESS)
        return status;
    if (response != "+")
        return RQ_SET_CONFIG_FAILED;

    return RQ_SUCCESS;
}
/**
 * Sends the requested command to the Controller
 * @param  commandItem Determines which Command is issued
 * @param  index       Determines which Value will be returned
 * @param  value       Determines what value is issued
 * @return             RQ Status flags
 */
int RoboteqDevice::SetCommand(int commandItem, int index, int value)
{
    string response;

    if (commandItem < 0 || commandItem > 255)
        return RQ_INVALID_COMMAND_ITEM;

    if (index < 0)
        return RQ_INDEX_OUT_RANGE;
    string toString = to_string(value);
    int status = com.IssueCommand("!", commandItem, index, toString , response, true);
    //PDBG("status %s", status == RQ_SUCCESS ? "success" : "failed");
    //if (status != RQ_SUCCESS) {
    //    return status;
    //if (response != "+")
    //    PERR("Set Command failed %d", status);
    //    return RQ_SET_COMMAND_FAILED;
    //}

    return status;
}
/**
 * Calls SetCommand(int, int, int) Method with index set to 1
 * @param  commandItem Determines which Command is issued
 * @param  value       The Value send to the Controller
 * @return             RQ Status Flags
 */
int RoboteqDevice::SetCommand(int commandItem, int value)
{
    return SetCommand(commandItem, 1, value);
}
/**
 * Calls SetCommand(int, int, int) with index to 1 and value to 0
 * @param  commandItem Determines which Command is issued
 * @return             RQ Status Flags
 */
int RoboteqDevice::SetCommand(int commandItem)
{
    return SetCommand(commandItem, 1, 0);
}
/**
 * Sends the requested configItem to the Controller
 * @param  configItem    Determines which Command is issued
 * @param  index         Determines which Value will be returned
 * @param  result        Value returned by the Controller
 * @return               RQ Status Flags
 */
int RoboteqDevice::GetConfig(int configItem, int index, int &result)
{
    string response;

    if (configItem < 0 || configItem > 255)
        return RQ_INVALID_CONFIG_ITEM;

    if (index < 0)
        return RQ_INDEX_OUT_RANGE;

    int status = com.IssueCommand("~", configItem, index, "", response);
    if (status != RQ_SUCCESS)
        return status;

    istringstream iss(response);
    iss >> result;

    if (iss.fail())
        return RQ_GET_CONFIG_FAILED;

    return RQ_SUCCESS;
}
/**
 * Calls the GetConfig(int, int, int&) Method with index set to 1
 * @param  configItem    Determines which Command is issued
 * @param  result        Value returned by the Controller
 * @return               RQ Status Flags
 */
int RoboteqDevice::GetConfig(int configItem, int &result)
{
    return GetConfig(configItem, 1, result);
}
/**
 * Calls the GetValue(int, int, int&) Method with index set to 1
 * @param  operatingItem Determines which Command is issued
 * @param  result        Value returned by the Controller
 * @return               RQ Status Flags
 */
int RoboteqDevice::GetValue(int operatingItem, int &result)
{
    return GetValue(operatingItem, 1, result);
}
/**
 * Returns the Raw Output
 * @param  operatingItem Determines whicht Command is issued
 * @param  result        Returns the string ( raw )
 * @return               RQ Status Flags
 */
int RoboteqDevice::GetRawConfig(int operatingItem, std::string &result)
{
    if (operatingItem < 0 || operatingItem > 255)
        return RQ_INVALID_OPER_ITEM;

    return com.IssueCommand("~", operatingItem, 0, "", result);;
}
/**
 * The Response of the Controller is parsed and stored in the result array
 * @param  operatingItem Determines which Command is issued
 * @param  index         Determines which Value will be returned
 * @param  result        Value returned by the Controller
 * @return               RQ Status Flags
 */
int RoboteqDevice::GetValue(int operatingItem, int index, int &result)
{
    string response;

    if (operatingItem < 0 || operatingItem > 255)
        return RQ_INVALID_OPER_ITEM;

    if (index < 0)
        return RQ_INDEX_OUT_RANGE;


    int status = com.IssueCommand("?", operatingItem, index, "", response);
    if (status != RQ_SUCCESS)
        return status;

    istringstream iss(response);
    iss >> result;

    if (iss.fail())
        return RQ_GET_VALUE_FAILED;

    return RQ_SUCCESS;
}
/**
 * Returns the Raw Output
 * @param  operatingItem Determines whicht Command is issued
 * @param  result        Returns the string ( raw )
 * @return               RQ Status Flags
 */
int RoboteqDevice::GetRawValue(int operatingItem, string &result)
{
    if (operatingItem < 0 || operatingItem > 255)
        return RQ_INVALID_OPER_ITEM;

    return com.IssueCommand("?", operatingItem, 0, "", result);;
}
