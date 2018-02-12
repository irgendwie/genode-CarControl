#include "ComAPI.h"

#include "Constants.h"
#include "ErrorCodes.h"
#include "Defines.h"

#include <base/printf.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sstream>
#include <string.h>
#include <queue>


using namespace std;
#define BUFFER_SIZE 1024

ComAPI::ComAPI(int ConnectionType) : timer(), terminal(), SeriellToCan()
{
    handle = RQ_INVALID_HANDLE;
    ComAPI::ConnectionType = ConnectionType;
}

/********************** Functions *****************************/
/**
 * Writes to the device
 * @param  str Stuff that needs to be written
 * @return     RQ Status Flags
 */
int ComAPI::WriteSerial(std::string str)
{
    size_t countSent = terminal.write(str.c_str(), str.length());

    //Verify whether the Transmitted Data on UART was Successful or Not
    if (countSent < str.length())
        return RQ_ERR_TRANSMIT_FAILED;

    return RQ_SUCCESS;
}
/**
 * Reads from the Serial Port
 */
int ComAPI::ReadSerial(std::string &str, std::string command, bool isplusminus)
{
    int countRcv;

    char buf[BUFFER_SIZE + 1] = "";

    str = "";
    countRcv = terminal.read(buf, BUFFER_SIZE);
    str.append(buf, countRcv);

    if (countRcv < 0)
    {
        return RQ_ERR_SERIAL_RECEIVE;
    }

    if (isplusminus)
    {
        if (str.length() < 2)
            return RQ_INVALID_RESPONSE;

        str = str.substr(str.length() - 2, 1);
        return RQ_SUCCESS;
    }

    std::string::size_type pos = str.rfind(command + "=");
    if (pos == std::string::npos)
        return RQ_INVALID_RESPONSE;

    pos += command.length() + 1;

    std::string::size_type carriage = str.find("\r", pos);
    if (carriage == std::string::npos)
        return RQ_INVALID_RESPONSE;

    str = str.substr(pos, carriage - pos);

    return RQ_SUCCESS;
}

/**
 * Calls the IssueCommand(std::string, std::string, std::string, std::string&,bool) Method
 * @param  commandType CommandTypes: !,?,~,^ (SetCommand, GetValue, GetConfig,SetConfig)
 * @param  command     The Command to be Executed
 * @param  index       The Index of the Command
 * @param  args        Arguments for the command
 * @param  response    Return value
 * @param  isplusminus Get expects a '=' while Set expects an '+' or '-'
 * @return             RQ Status Flags
 */
int ComAPI::IssueCommand(std::string commandType, int command, int index, std::string args, std::string &response, bool isplusminus)
{
    int status = RQ_UNRECOGNIZED_DEVICE;
    response = "";
    if (ConnectionType == CONNECTION_USB
            || ConnectionType == CONNECTION_COM)
    {
        char commandItem[10];
        // Command to hex
        sprintf(commandItem, "$%02X", command);
        // Write Command To Device
        string test = commandType + commandItem + " " + to_string(index) + (args == "" ? "" : " " + args) + "\r";
        if ((status = WriteSerial(commandType + commandItem + " " + to_string(index) + (args == "" ? "" : " " + args) + "\r")) != RQ_SUCCESS)
            return RQ_ERR_TRANSMIT_FAILED;
        // **** Wait
        timer.msleep(10);
        // **** Read from Port
        return ReadSerial(response, commandItem, isplusminus);
    }
    else
        return status;
}
/**
 * Calls the IssueCommand(std::string, std::string, std::string, std::string&,bool) Method
 * @param  commandType CommandTypes: !,?,~,^ (SetCommand, GetValue, GetConfig,SetConfig)
 * @param  command     The Command to be Executed
 * @param  response    Return value
 * @param  isplusminus Get expects a '=' while Set expects an '+' or '-'
 * @return             RQ Status Flags
 */
int ComAPI::IssueCommand(std::string commandType, int command, std::string &response, bool isplusminus)
{
    return IssueCommand(commandType, command, 0, "", response, isplusminus);
}
