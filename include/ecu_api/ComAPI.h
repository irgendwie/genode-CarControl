/*
  HOW TO INCLUDE ANOTHER CONNECTION:
    1. Add a ConnectionType and make the IssueCommand call your methods
    2. Generate a WriteXY Method
        2.1 The Parameters can include: commandType, the Command, index, args, response
        2.2 If The Write was successfull set response to "+"
    3. Generate a ReadXY Method
        3.1 The Parameters can include: commandType, command, index, response, isplusminus
        3.2 If the Read was successfull return the result in response
*/
#ifndef __ComAPI__
#define __ComAPI__
#include "Mapping.h"
#include <string>
#include <terminal_session/connection.h>
#include <timer_session/connection.h>

typedef struct can_frame can_frame_t;

class ComAPI
{
private:
    Mapping SeriellToCan;
    int handle;
    int ConnectionType;
    char *IntegerToChar(int in);
    Terminal::Connection terminal;
    Timer::Connection timer;

    int WriteSerial(std::string str);
    int ReadAll(std::string &str);
    int ReadSerial(std::string &str, std::string command, bool isplusminuss);
public:
    /********************** Functions ****************************/
    int IssueCommand(std::string commandType, int command, int index, std::string args, std::string &response, bool isplusminus = false);
    int IssueCommand(std::string commandType, int command, std::string &response, bool isplusminus = false);
    /********************** Constructor **************************/
    ComAPI(int ConnectionType);
};

#endif
