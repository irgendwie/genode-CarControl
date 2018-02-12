#include "CoreAPI.h"

#include <sstream>
#include <stdlib.h>
#include <string>

#include "ErrorCodes.h"
#include "Constants.h"
#include "Defines.h"

/**************************************************************/
/************************ Constructor *************************/
/**************************************************************/
CoreAPI::CoreAPI(int ConnectionType) : device(ConnectionType)
{}
CoreAPI::~CoreAPI() {}

/**************************************************************/
/************************ SETTER ******************************/
/**************************************************************/
/**************************************************************/
/************************ RUNTIME *****************************/
/**************************************************************/
/**
* Sets the maximum acceleration and sets the speed step by step
* @param  speed Resulting Speed
* @param  accel Acceleration
* @return       RRQ Status Flags
*/
int CoreAPI::SetMotorSpeedAccel(int speed, int accel)
{
    int status;
    if ((status = CoreAPI::SetAcceleration(1, accel)) != RQ_SUCCESS)
        return RQ_INVALID_RESPONSE;

    if ((status = CoreAPI::SetMotorSpeedAbs(speed)) != RQ_SUCCESS)
        return RQ_INVALID_RESPONSE;

    return RQ_SUCCESS;
}
/**
* Lowers Motorspeed to speed descending according to decel
* @param  speed Desired speed
* @param  decel Deacceleration
* @return       RQ Status Flags
*/
int CoreAPI::SetMotorSpeedDecel(int speed, int decel)
{
    int status;
    if ((status = CoreAPI::SetDeceleration(1, decel)) != RQ_SUCCESS)
        return RQ_INVALID_RESPONSE;

    if ((status = CoreAPI::SetMotorSpeedAbs(speed)) != RQ_SUCCESS)
        return RQ_INVALID_RESPONSE;

    return RQ_SUCCESS;
}
/**
* Sets Motorspeed according to a value between 0 and 1000
* @param  speed Desired Speed
* @return       RQ Status Flags
*/
int CoreAPI::SetMotorSpeedRel(int speed)
{
    int status = device.SetCommand(_MOTCMD, speed);
    return status;
}
/**
* Sets the Motorspeed in RPM
* @param  speed Desired Speed in RPM
* @return       RQ Status Flags
*/
int CoreAPI::SetMotorSpeedAbs(int speed)
{
    int status = device.SetCommand(_GO, 1, speed);
    return status;
}
/**
 * \test
 * (_P) see p. 169
 * @param  port  Port
 * @param  value Value
 * @return       RQ Status Flags
 */
int CoreAPI::SetAbsoluteDesiredPosition(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2)
            && CheckRange(value, CPRI_DISABLED, CPRI_ANALOG))
        status = device.SetCommand(_P, port, value);
    return  status;
}
/**
 * \test
 * (_S) see p. 171
 * @param  port  Port
 * @param  value Value
 * @return       RQ Status Flags
 */
int CoreAPI::SetMotorPositionVelocity(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2) && CheckRange(value, 0, MAX_RPM))
        status = device.SetCommand(_S, port, value);
    return status;
}
/**
 * \test
 * (_SX) see p. 171
 * @param  port  Port
 * @param  value Value
 * @return       RQ Status Flags
 */
int CoreAPI::SetNextPositionVelocity(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2)
            && CheckRange(value, 0, MAX_RPM))
        status = device.SetCommand(_SX, port, value);
    return status;
}
/**
 * \test
 * (_C) see p. 166
 * @param  port  Port
 * @param  value Value
 * @return       RQ Status Flags
 */
int CoreAPI::SetEncoderCounter(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_C, port, value);
    return status;
}
/**
 * \test
 * (_CB) see p. 166
 * @param  port  Port
 * @param  value Value
 * @return       RQ Status Flags
 */
int CoreAPI::SetBrushlessCounter(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_CB, port, value);
    return status;
}
/**
 * \test
 * Sets the User Variables (_VAR) see p. 171
 * @param  num   Number 0 - 16
 * @param  value Integer Value to Set
 * @return       RQ Status Flags
 */
int CoreAPI::SetUserIntegerVariables(int num, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(num, 0, 16))
        status = device.SetCommand(_VAR, num, value);
    return status;
}
/**
 * \test
 * Sets the User Variables (_B) see p. 165
 * @param  num   Number 0 - 16
 * @param  value Integer Value to Set
 * @return       RQ Status Flags
 */
int CoreAPI::SetUserIntegerBool(int num, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(num, 0, 32))
        status = device.SetCommand(_B, num, value);
    return status;
}
/**
 * \test
 * Sets the Acceleration ( _AC) see p. 165
 * @param  port  Motor 1 or 2
 * @param  value Acceleration
 * @return       RQ Status Flags
 */
int CoreAPI::SetAcceleration(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_AC, port, value);
    return status;
}
/**
 * \test
 * Sets the next Acceleration ( _AX) see p.165
 * @param  port  Motor 1 or 2
 * @param  value Acceleration
 * @return       RQ Status Flags
 */
int CoreAPI::SetNextAcceleration(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_AX, port, value);
    return status;
}
/**
 * \test
 * Sets the Deacceleration ( _DC) see p.167
 * @param  port  Motor 1 or 2
 * @param  value Acceleration
 * @return       RQ Status Flags
 */
int CoreAPI::SetDeceleration(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_DC, port, value);
    return status;
}
/**
 * \test
 * Sets the next Deacceleration ( _DX) see p.168
 * @param  port  Motor 1 or 2
 * @param  value Acceleration
 * @return       RQ Status Flags
 */
int CoreAPI::SetNextDeceleration(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_DX, port, value);
    return status;
}
/**
 * \test
 * Enables the Digital Outputs ( _D1) see p.167
 * @param  port  Outputs: 0 - MAX_DIGITAL_OUTPUTS
 * @return       RQ Status Flags
 */
int CoreAPI::SetDigitalOuts(int port)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_DIGITAL_OUTPUTS))
        status = device.SetCommand(_D1, port);
    return status;
}
/**
 * \test
 * Reset the Digital Outputs ( _D0) see p.167
 * @param  port  Outputs: 0 - MAX_DIGITAL_OUTPUTS
 * @return       RQ Status Flags
 */
int CoreAPI::SetResetDigitalOuts(int port)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_DIGITAL_OUTPUTS))
        status = device.SetCommand(_D0, port);
    return status;
}
/**
 * \test
 * (_H) see p.169
 * @param  port  Port
 * @return       RQ Status Flags
 */
int CoreAPI::SetLoadHomeCounter(int port)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_H, port);
    return status;
}
/**
 * \test
 * Trigger Emeregency Stop (_EX) see p.168
 * @return RQ Status Flags
 */
int CoreAPI::SetEmergencyStop()
{
    return device.SetCommand(_EX, 0, 0);;
}
/**
 * \test
 * Release Emergency Stop (_MG) see p.169
 * @return RQ Status Flags
 */
int CoreAPI::SetReleaseEmergencyStop()
{
    return device.SetCommand(_MG, 0, 0);
}
/**
 * \test
 * Trigger Emeregency Stop on specified Motor (_MS) see p.169
 * @param  port Motor: 1 or 2
 * @return RQ Status Flags
 */
int CoreAPI::SetEmergencyStop(int port)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_MS, port);
    return status;
}
/**
 * \test
 * (_PR) see p.170
 * @param  port  Port
 * @param  value Value
 * @return       RQ Status Flags
 */
int CoreAPI::SetRelativeDesiredPosition(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_PR, port, value);
    return status;
}
/**
 * \test
 * (_PX) see p.170
 * @param  port  Port
 * @param  value Value
 * @return       RQ Status Flags
 */
int CoreAPI::SetNextAbsoluteDesiredPosition(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_PX, port, value);
    return status;
}
/**
 * (_PRX) see p.170
 * @param  port  Port
 * @param  value Value
 * @return       RQ Status Flags
 */
int CoreAPI::SetNextRelativeDesiredPosition(int port, int value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.SetCommand(_PRX, port, value);
    return status;
}
/**
 * \test
 * Saves the Config to the Flash (_EES) see p.168
 * @return RQ Status Flags
 */
int CoreAPI::SetSaveConfig()
{
    return device.SetCommand(_EES, 0);
}
/**************************************************************/
/************************ CONFIG ******************************/
/**************************************************************/

/**
* Sets the Scripting Autostart Mode (_BRUN) see p.196
* @param  val BRUN_DISABLED | BRUN_DELAYED | BRUN_ACTIVATED
* @return       RQ Status Flags
*/
int CoreAPI::SetScriptingAutostart(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, BRUN_DISABLED, BRUN_ACTIVATED) )
        status = device.SetConfig(_BRUN, val);
    return status;
}
/**
* Sets the Linearity (_CLIN) see p.197
* @param  val  LIN_LINEAR | LIN_EXP_WEAK | LIN_EXP_MEDIUM | LIN_EXP_STRONG | LIN_LOG_WEAK | LIN_LOG_MEDIUM | LIN_LOG_STRONG
* @return       RQ Status Flags
*/
int CoreAPI::SetLinearity(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, LIN_LINEAR, LIN_LOG_STRONG))
        status = device.SetConfig(_CLIN, val);
    return status;
}
/**
* Sets the Serial Timout (_RWD) see p.198
* @param  val Range: 0 - 65000
* @return       RQ Status Flags
*/
int CoreAPI::SetSerialTimout(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, 0, 6500))
        status = device.SetConfig(_RWD, val);
    return status;
}
/**
* Sets the ChannelPriorities (_CPRI) p.197
* @param port Port: 1 - 3
* @param  val CPRI_DISABLED | CPRI_SERIAL | CPRI_RC | CPRI_ANALOG
* @return     RQ Status Flags
*/
int CoreAPI::SetChannelPriorities(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 3)
            && CheckRange(val, CPRI_DISABLED, CPRI_ANALOG))
        status = device.SetConfig(_CPRI, port, val);
    return  status;
}
/*int CoreAPI::SetTelemetryString(std::string &str)
{
    return device.SetRawConfig(_TELS, str);
}*/
/**
* Sets the AnalogCenterSafety (_ACS) see p. 196
* @param  value sets ACS
* @return       RQ Status Flags
*/
int CoreAPI::SetAnalogCenterSafety(int value)
{
    return device.SetConfig(_ACS, value);
}
/**
* Sets Analog within Min & Max Safety (_AMS) see p. 196
* @param  val Sets AMS
* @return     RQ Status Flags
*/
int CoreAPI::SetAnalogMinMaxSafety(int val)
{
    return device.SetConfig(_AMS, val);
}
/**
* Sets the Encoder Usage (_EMOD) see p. 210
* @param  mot   Motor: MOT1 | MOT2
* @param  val Desired Value: ENC_UNUSED | ENC_COMMAND | ENC_FEEDBACK
* @return       RQ Status Flags
*/
int CoreAPI::SetEncoderMode(int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, ENC_UNUSED, ENC_FEEDBACK))
        status =  device.SetConfig(_EMOD, mot + val);
    return status;
}
/**
* Set the Encoder PPR Value (_EPPR) see p.210
* @param  val Desired Value: Range 1 - 5000 default: 100
* @return     RQ Status Flags
*/
int CoreAPI::SetEncoderPPR(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, 1, 5000))
        status =  device.SetConfig(_EPPR, val);
    return status;
}
/**
* Encoder Low Count Limit (_ELL) see p.209
* @param  val Desired Value
* @return     RQ Status Flags
*/
int CoreAPI::SetEncoderLowLimitCount(int val)
{
    return device.SetConfig(_ELL, val);
}
/**
* Encoder High Count Limit (_EHL) see p.208
* @param  val Desired Value
* @return     RQ Status Flags
*/
int CoreAPI::SetEncoderHighLimitCount(int val)
{
    return device.SetConfig(_EHL, val);
}
/**
* Encoder Counter Load at Home Position (_EHOME) see p.209
* @param  val Desired Value
* @return     RQ Status Flags
*/
int CoreAPI::SetEncoderCounterLoadAtHomePosition(int val)
{
    return device.SetConfig(_EHOME, val);
}
/**
* Gets the Encoder High Limit Action (_EHLA) see p.209
* @param  mot Motor: MOT1 | MOT2
* @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                            DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
* @return     RQ_Status_Flags
*/
int CoreAPI::SetEncoderLowLimitAction(int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, DINA_NO_ACTION, DINA_LOAD_HOME_VALUE)
            && CheckMotor(mot))
        status = device.SetConfig(_ELLA, mot + val);
    return  status;
}

/**
* Gets the Encoder High Limit Action (_EHLA) see p.209
* @param  mot Motor: MOT1 | MOT2
* @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                            DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
* @return     RQ_Status_Flags
*/
int CoreAPI::SetEncoderHighLimitAction(int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, DINA_NO_ACTION, DINA_LOAD_HOME_VALUE)
            && CheckMotor(mot))
        status = device.SetConfig(_EHLA, mot + val);
    return status;
}
/**
 * Set the Digital Inputs for each port (_DINL) see p. 200
 * @param  port Port number 0 - MAX_DIGITAL_INPUTS
 * @param  val  Desired Value: 0 -> active low, 1 -> active high
 * @return      RQ Status Flags
 */
int CoreAPI::SetDigitalInput(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_DIGITAL_INPUTS) && CheckRange(val, 0, 1))
        status = device.SetConfig(_DINL, port, val);
    return status;
}
/**
 * Sets the Digital Input Action if a port is triggered (_DINA) see p.199
 * @param  port Port: 0 - MAX_DIGITAL_INPUTS
 * @param  mot  Motor: DINA_MOT1 || DINA_MOT2 || DINA_MOT12
 * @param  val  DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                              DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return      RQ Status Flags
 */
int CoreAPI::SetDigitalInputAction(int port, int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if ((mot == DINA_MOT1 || mot == DINA_MOT2 || mot == DINA_MOT12) &&
            CheckRange(port, 0, MAX_DIGITAL_INPUTS)
            && CheckRange(val, DINA_NO_ACTION, DINA_LOAD_HOME_VALUE))
        status = device.SetConfig(_DINA, port, val + mot);
    return  status;
}
/**
 * Sets the Analog Input Mode (_AMOD) see p.204
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  AMOD Values: AMOD_DISABLED | AMOD_ABSOLUTE | AMOD_RELATIVE
 * @return      RQ Status Flags
 */
int CoreAPI::SetAnalogInputMode(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, AMOD_DISABLED, AMOD_RELATIVE))
        status = device.SetConfig(_AMOD, port, val);
    return status;
}

/**
 * Sts the Analog Input Actions for each port (_AINA) see p.202
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val  Returns the USAGE: ENC_UNUSED | ENC_COMMAND | ENC_FEEDBACK
 * @return      RQ Status Flags
 */
int CoreAPI::SetAnalogInputAction(int port, int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, ENC_UNUSED, ENC_FEEDBACK)
            && CheckMotor(mot))
        status = device.SetConfig(_AINA, port, mot + val);
    return status;
}
/**
 * Set Analog Input Range for each Point (_AMIN) see p. 203
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Min: 0 - 5000 mV default: 100mV
 * @return      RQ Status Flags
 */
int CoreAPI::SetAnalogInputMin(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, 0, 5000))
        status = device.SetConfig(_AMIN, port, val);
    return status;
}
/**
 * Sets the Analog Input Center (_ACTR) see p. 201
 * @param  port Port: 0 - MAX_ANALOG_INPUT
 * @param  val  Center: 0 - 5000 default: 2500
 * @return      RQ Status Flags
 */
int CoreAPI::SetAnalogInputCenter(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, 0, 5000))
        status = device.SetConfig(_ACTR, port, val);
    return status;
}
/**
 * Sets the Analog Input Max (_AMAX) see p. 203
 * @param  port Port: 0 - MAX_ANALOG_INPUT
 * @param  val  Max: 0 - 5000 default: 4900
 * @return      RQ Status Flags
 */
int CoreAPI::SetAnalogInputMax(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.SetConfig(_AMAX, port, val);
    return status;
}
/**
 * Sets the Analog Input Polarity for every port (_APOL) see p.204
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Polarity: APOL_UNINVERTED | APOL_INVERTED
 * @return      RQ Status Flags
 */
int CoreAPI::SetAnalogInputPolarity(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, APOL_UNINVERTED, APOL_INVERTED))
        status = device.SetConfig(_APOL, port, val);
    return status;
}
/**
 * Sets the Analog Deadband (_ADB) see p.201
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Deadband: 0 - 50
 * @return      RQ Status Flags
 */
int CoreAPI::SetAnalogDeadband(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, DB_MIN, DB_MAX))
        status = device.SetConfig(_ADB, port, val);
    return  status;
}
/**
 * Sets the Action on Analog Min (_AMINA) see p.201
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return      RQ Status Flags
 */
int CoreAPI::SetAnalogMinAction(int port, int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, DINA_NO_ACTION, DINA_LOAD_HOME_VALUE)
            && CheckMotor(mot))
        status =  device.SetConfig(_AMINA, port, mot + val);
    return status;
}
/**
 * Sets the Action on Analog Max (_AMAXA) see p.201
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return      RQ Status Flags
 */
int CoreAPI::SetAnalogMaxAction(int port, int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, DINA_NO_ACTION, DINA_LOAD_HOME_VALUE)
            && CheckMotor(mot))
        return  device.SetConfig(_AMAXA, port, mot + val);
    return status;
}
/**
 * Sets the Pulse Input Mode (_PMOD) see p. 207
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  PM Values:  PMOD_DISABLED  |  PMOD_PULSE_WIDTH |  PMOD_FREQUENCY |  PMOD_PERIOD
 * @return      RQ Status Flags
 */
int CoreAPI::SetPulseInputMode(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, PMOD_DISABLED, PMOD_PERIOD))
        status =  device.SetConfig(_PMOD, port, val);
    return status;
}
/**
 * Sets the Action on a Pulse (_PINA) see p.206
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Action: ENC_COMMAND | ENC_FEEDBACK | ENC_UNUSED
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @return      RQ Status Flags
 */
int CoreAPI::SetPulseInputAction(int port, int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckMotor(mot)
            && CheckRange(val, ENC_UNUSED, ENC_FEEDBACK))
    {
        status = device.SetConfig(_PINA, port, mot + val);
    }
    return status;
}
/**
 * Sets the Pulse Min Range (_PMIN) see p.207
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Minimum: 0 - 65000 us default: 1000
 * @return      RQ Status Flags
 */
int CoreAPI::SetPulseMin(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS) && CheckRange(val, 0, 65000))
    {
        status = device.SetConfig(_PMIN, port, val);
    }
    return status;
}
/**
 * Sets the Pulse Max Range (_PMAX) see p.206
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Minimum: 0 - 65000 us default: 2000
 * @return      RQ Status Flags
 */
int CoreAPI::SetPulseMax(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS) && CheckRange(val, 0, 65000))
    {
        status = device.SetConfig(_PMAX, port, val);
    }
    return status;
}
/**
 * Sets the Pulse Min Range (_PMIN) see p.205
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Minimum: 0 - 65000 us default: 1500
 * @return      RQ Status Flags
 */
int CoreAPI::SetPulseCenter(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS) && CheckRange(val, 0, 65000))
    {
        status = device.SetConfig(_PCTR, port, val);
    }
    return status;
}
/**
 * Gets the Pulse Input Deadband (_PDB) see p. 205
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Deadband: 0 - 50 default: 0
 * @return      RQ Status Flags
 */
int CoreAPI::SetPulseDeadbeand(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS) && CheckRange(val, 0, 50))
    {
        status = device.SetConfig(_PDB, port, val);
    }
    return status;
}
/**
 * Gets the Action on Max Pulse (_PMAX) see p.207
 * @param  port Port: 0 - Max_ANALOG_INPUTS
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @return      RQ Status Flags
 */
int CoreAPI::SetPulseMaxAction(int port, int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, DINA_NO_ACTION, DINA_LOAD_HOME_VALUE)
            && CheckMotor(mot))
    {
        status = device.SetConfig(_PMAXA, port, val + mot);
    }
    return status;
}
/**
 * Gets the Action on Min Pulse (_PMAX) see p.207
 * @param  port Port: 0 - Max_ANALOG_INPUTS
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @return      RQ Status Flags
 */
int CoreAPI::SetPulseMinAction(int port, int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, DINA_NO_ACTION, DINA_LOAD_HOME_VALUE)
            && CheckMotor(mot))
    {
        status = device.SetConfig(_PMINA, port, val + mot);
    }
    return status;
}
/**
 * Sets the Linearity on the Pulse Input (_PLIN) see p.206
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Linearty: LIN_LINEAR | LIN_EXP_WEAK | LIN_EXP_MEDIUM | LIN_EXP_STRONG | LIN_LOG_WEAK | LIN_LOG_MEDIUM | LIN_LOG_STRONG
 * @return      RQ Status Flags
 */
int CoreAPI::SetPulseLinearity(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS)
            && CheckRange(val, LIN_LINEAR, LIN_LOG_STRONG))
    {
        status = device.SetConfig(_PLIN, port, val);
    }
    return status;
}
/**
 * Sets the Digital Output Active Levels (_DOL) see p.200
 * @param  port Port: 0 - MAX_DIGITAL_OUTPUTS
 * @param  val  Active Level: DOL_ACTIVE_HIGH | DOL_ACTIVE_LOW
 * @return      RQ Status Flags
 */
int CoreAPI::SetDigitalOutputActiveLevel(int port, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_DIGITAL_OUTPUTS)
            && CheckRange(val, DOL_ACTIVE_LOW, DOL_ACTIVE_HIGH))
    {
        status = device.SetConfig(_DOL, port,  val);
    }
    return status;
}
/**
 * Sets the Digital Output Action (_DOA) see p.200
 * @param  port Port: 0 - MAX_DIGITAL_OUTPUTS
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val  Actions: DOA_NO_ACTION | DOA_MOTOR_ON | DOA_OVERVOLTAGE | DOA_OVERTEMPERATURE  | DOA_MIRROR_STATUS_LED | DOA_NO_MOSFET_FAILURE
 * @return      RQ Status Flags
 */
int CoreAPI::SetDigitalOutputAction(int port, int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_DIGITAL_OUTPUTS)
            && CheckRange(val, DOA_NO_ACTION, DOA_NO_MOSFET_FAILURE)
            && CheckMotor(mot))
    {
        status = device.SetConfig(_DOA, port, val + mot);
    }
    return status;
}
/**
 * Gets the PWM Frequency (_PWMF) see p.215
 * @param  val PWM Frequency multiplied with 10, Range: 10 - 200 (1 - 20kHz)
 * @return     RQ Status Flags
 */
int CoreAPI::SetPWMFrequency(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, 10, 200))
        status = device.SetConfig(_PWMF, val);
    return status;
}
/**
 * Sets the Overvoltage Limit, at this point an overvoltage signal is issued (_OVL) see p.214
 * @param  val Overvoltage Limit multiplied by 10: Range 100 - MAX_OVERVOLTAGE
 * @return     RQ Status Flags
 */
int CoreAPI::SetOvervoltageLimit(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, 100, MAX_OVERVOLTAGE))
        status = device.SetConfig(_OVL, val);
    return status;
}
/**
 * Sets the Undervoltage Limit, This parameter sets the voltage below which the controller will turn off its power stage. (_UVL) see p.215
 * @param  val Overvoltage Limit multiplied by 10: Range 50 - MAX_OVERVOLTAGE
 * @return     RQ Status Flags
 */
int CoreAPI::SetUndervoltageLimit(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, 50, MAX_OVERVOLTAGE))
        status = device.SetConfig(_UVL, val);
    return status;
}
/**
 * Sets the Break Delay (_BKD) see p.214
 * @param  val Delay in ms
 * @return     RQ Status Flags
 */
int CoreAPI::SetBrakeActivationDelay(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (val >= 0)
        status = device.SetConfig(_BKD, val);
    return status;
}
/**
 * Sets the Short Circuit Detection Sensitivity (_THLD) see p.215
 * @param  val Sensitivity: THLD_HIGH_SENSITIVITY | THLD_MEDIUM_SENSITIVITY | THLD_LOW_SENSITIVITY | THLD_DISABLED
 * @return     RQ Status Flags
 */
int CoreAPI::SetShortCircuitThreshold(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, THLD_HIGH_SENSITIVITY, THLD_DISABLED))
        status = device.SetConfig(_THLD, val);
    return status;
}
/**
 * Gets the Number of Poles of the BL Motor (_BPOL) see p.213
 * @param  mot Motor: 1 or 2
 * @param  val [description]
 * @return     [description]
 */
int CoreAPI::SetNumPoles(int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(mot, 0, 2))
        status = device.SetConfig(_BPOL, mot, val);
    return status;
}
/**
 * Sets the selected Encoder (_BLFB) see p.212
 * @param  mot Motor: 1 or 2
 * @param  val Feedback: BLFB_HALL_SENSOR | BLFB_ENCODER
 * @return     RQ Status Flags
 */
int CoreAPI::SetBrushlessFeedback(int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(mot, 0, 2) && CheckRange(val, BLFB_HALL_SENSOR, BLFB_ENCODER))
    {
        status = device.SetConfig(_BLFB, mot, val);
    }
    return status;
}
/**
 * Set the Stall Detection Mode (_BLSTD) see p.213
 * @param  mot Motor: 0 or 1
 * @param  val Detection Modes: BLSTD_DISABLED | BLSTD_250MS_OVER_10  | BLSTD_500OMS_0VER_25 | BLSTD_1000MS_OVER_50 3
 * @return     RQ Status Flags
 */
int CoreAPI::SetBrushlessStallDetection(int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(mot, 0, 2) && CheckRange(val, BLSTD_DISABLED, BLSTD_1000MS_OVER_50))
        status = device.SetConfig(_BLSTD, mot, val);
    return status;
}
/**
 * (_BLL) see p.212
 * @param  mot Motor: 1 or 2
 * @param  val Counter: default -2000
 * @return     RQ Status Flags
 */
int CoreAPI::SetEncoderLowLimit(int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(mot, 0, 2))
        status = device.SetConfig(_BLL, mot, val);
    return status;
}
/**
 * Encoder High Limit Action (_BHLA) see p.211
 * @param  port Port: 1 or 2
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return      RQ Status Flags
 */
int CoreAPI::SetEncoderHighLimitAction(int port, int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2)
            && CheckMotor(mot)
            && CheckRange(val, DINA_NO_ACTION, DINA_LOAD_HOME_VALUE))
        status = device.SetConfig(_BHLA, port, mot + val);
    return status;
}
/**
 * Encoder Low Limit Action (_BHLA) see p.211
 * @param  port Port: 1 or 2
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return      RQ Status Flags
 */
int CoreAPI::SetEncoderLowLimitAction(int port, int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2)
            && CheckMotor(mot)
            && CheckRange(val, DINA_NO_ACTION, DINA_LOAD_HOME_VALUE))
        status = device.SetConfig(_BLLA, port, val + mot);
    return status;
}
/**
 * Amps Limit (_ALIM) see p.216
 * @param  val Amps multiplied with 10: 10A to Datasheet Max, default: 75% of Max
 * @return     RQ Status Flags
 */
int CoreAPI::SetMotorAmpsLimit(int val)
{
    return device.SetConfig(_ALIM, val);
}
/**
 * Amps Trigger Value (_ATRIG) see p.217
 * @param  val Amps multiplied with 10: 10A to Datasheet Max, default: 75% of Max
 * @return     RQ Status Flags
 */
int CoreAPI::SetMotorAmpsTriggerValue(int val)
{
    return device.SetConfig(_ATRIG, val);
}
/**
 * Amps Trigger Action (_ATGA) see p.217
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return     RQ Status Flags
 */
int CoreAPI::SetMotorAmpsTriggerAction(int mot, int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckMotor(mot)
            && CheckRange(val, DINA_NO_ACTION, DINA_LOAD_HOME_VALUE))
        status = device.SetConfig(_ATGA, val + mot);
    return status;
}
/**
 * Amps Trigger Delay (_ATGD) see p.217
 * @param  val Delay in ms
 * @return     RQ Status Delay
 */
int CoreAPI::SetMotorAmpsTriggerDelay(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (val > 0)
        status = device.SetConfig(_ATGD, val);
    return status;
}
/**
 * Max Power Forward (_MXPF) see p.220
 * @param  val Power: 25 - 100, default: 100
 * @return     RQ Status Flags
 */
int CoreAPI::SetMotorMaxPowerForward(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, 25, 100))
        status = device.SetConfig(_MXPF, val);
    return status;
}
/**
 * Max Power Forward (_MXPR) see p.221
 * @param  val Power: 25 - 100, default: 100
 * @return     RQ Status Flags
 */
int CoreAPI::SetMotorMaxPowerReverse(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, 25, 100))
        status = device.SetConfig(_MXPR, val);
    return  status;
}
/**
 * Max RPM (_MXRPM) see p.221
 * @param  val RPM: 10 - 65000, default: 3000
 * @return     RQ Status Flags
 */
int CoreAPI::SetMotorMaxRPM(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, 25, 65000))
        status = device.SetConfig(_MXRPM, val);
    return  status;
}
/**
 * Gets the Motor Operating Mode (_MMOD) see p.220
 * @param  val Mode: MMOD_OPEN_LOOP_SPEED | MMOD_CLOSED_LOOP_SPEED | MMOD_CLOSED_LOOP_POSITION_RELATIVE
 *                   | MMOD_closed_LOPP_COUNT_POSITION | MMOD_CLOSED_LOOP_POSITION_TRACKING | MMOD_TORQUE
 * @return     RQ Status Flags
 */
int CoreAPI::SetMotorOperatingMode(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, MMOD_OPEN_LOOP_SPEED, MMOD_TORQUE))
        status = device.SetConfig(_MMOD, val);
    return status;
}
/**
 * Gets the Velocity value in RPM (_MVEL) see p.220 !! Use !S in operating Mode !!
 * @param  val Velocity
 * @return     RQ Status Flags
 */
int CoreAPI::SetMotorDefaultVelocity(int val)
{
    return device.SetConfig(_MVEL, val);
}
/**
 * Gets the Turns between Limits (_MXTRN) see p.221
 * @param  val Turns multiplied with 10
 * @return     RQ Status Flags
 */
int CoreAPI::SetMotorMaxTurns(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (val > 0)
        status = device.SetConfig(_MXTRN, val * 10);
    return status;
}
/**
 * Gets the Proportional Gain for the Channel (_KP) see p.219
 * @param  val Gain multiplied with 10
 * @return     RQ Status Flags
 */
int CoreAPI::SetProportionalGain(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (val > 0)
        status = device.SetConfig(_KP, val * 10);
    return status;
}
/**
 * Gets the PID Integral Gain (_KI) see p.219
 * @param  val Gain multiplied with 10
 * @return     RQ Status Flags
 */
int CoreAPI::SetIntegrationalGain(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (val > 0)
        status = device.SetConfig(_KI, val * 10);
    return status;
}
/**
 * Gets the PID Differential Gain (_KD) see p.218
 * @param  val Gain multiplied with 10
 * @return     RQ Status Flags
 */
int CoreAPI::SetDifferentialGain(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (val > 0)
        status = device.SetConfig(_KD, val * 10);
    return status;
}
/**
 * Gets the PID Integral Cap (_ICAP) see p. 218
 * @param  val Integral cap in %: 1 - 100, default: 100
 * @return     RQ Status Flags
 */
int CoreAPI::SetMotorIntCap(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, 1, 100))
        status = device.SetConfig(_ICAP, val);
    return  status;
}
/**
 * Gets the Loop Error Detection Mode (_CLERD) see p.218
 * @param  val Detections Modes: CLERD_DISABLED | CLERD_250msGreater100 | CLERD_500msGreater250 | CLERD_1000msGreater500
 * @return     RQ Status Flags
 */
int CoreAPI::SetLoopErrorMode(int val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(val, CLERD_DISABLED, CLERD_1000msGreater500))
        status = device.SetConfig(_CLERD, val);
    return status;
}

/**************************************************************/
/************************ GETTER ******************************/
/**************************************************************/
/**************************************************************/
/*********************** RUNTIME ******************************/
/**************************************************************/
/**
 * \test
* Gets the Motorpower (_MOTPWR / _P)
* @param  result Returns the actual Motorpower (Range 0 - 1000)
* @return        RQ Status Flags
*/
int CoreAPI::GetMotorPower(int &result)
{
    int status = device.GetValue(_MOTPWR, result);
    return status;
}
/**
 * \test
* Gets the Motor amps (_MOTAMPS / _A)
* @param  amps Returns the Motoramps
* @return       RQ Status Flags
*/
int CoreAPI::GetMotorAmps(int &amps)
{
    int status = device.GetValue(_MOTAMPS, amps);
    return status;
}
/**
 * \test
* Gets the Loop Error Count (_LPERR / _E)
* @param  err Returns the number of Errors
* @return      RQ Status Flags
*/
int CoreAPI::GetLoopError(int &err)
{
    int status = device.GetValue(_LPERR, err);
    return status;
}
/**
 * \test
* Gets the Motor RPM (_BLSPEED / _BS)
* @param  rpm Returns the current RPM
* @return      RQ Status Flags
*/
int CoreAPI::GetMotorRPM(int &rpm)
{
    int status = device.GetValue(_BLSPEED, rpm);
    return status;

}
/**
 * \test
* Gets the Controller Voltage (_VOLTS 0)
* @param  volt Returns the Controller Volt ( 126 => 12.6V)
* @return       RQ Status Flags
*/
int CoreAPI::GetControllerVolt(int &volt)
{
    int status = device.GetValue(_VOLTS, 0, volt);
    return status;
}
/**
 * \test
* Gets the 5V Output (_VOLTS 2)
* @param  volt Returns the Controller Volt ( 5023 => 5.023V)
* @return      RQ Status Flags
*/
int CoreAPI::Get5VOutput(int &volt)
{
    int status = device.GetValue(_VOLTS, 2, volt);
    return status;
}
/**
 * \test
* Gets the Battery Voltage (_VOLTS 1)
* @param  volt Returns the Controller Volt ( 120 => 12.0V)
* @return      RQ Status Flags
*/
int CoreAPI::GetBatteryVolt(int &volt)
{
    int status = device.GetValue(_VOLTS, 1, volt);
    return status;
}
/**
 * \test
* FGets the Motor Temperature (_Temp 1)
* @param  temp Returns the Temperature in Celsius
* @return      RQ Status Flags
*/
int CoreAPI::GetMotorTemperature(int &temp)
{
    int status = device.GetValue(_TEMP, 1, temp);
    return status;
}
/**
 * \test
* Gets the Controller Temperature (_TEMP 2)
* @param  temp Returns the Temperature in Celsius
* @return      RQ Status Flags
*/
int CoreAPI::GetMCUTemperature(int &temp)
{
    int status = device.GetValue(_TEMP, 2, temp);
    return status;
}
/**
 * \test
 * (_P) see p.184
 * @param  port  Port
 * @param  value Return Value
 * @return       RQ Status Flags
 */
int CoreAPI::GetAbsoluteDesiredPosition(int port, int &value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.GetValue(_P, port, value);
    return  status;
}
/**
 * \test
 * (_S) see p.185
 * @param  port  Port
 * @param  value Return Value
 * @return       RQ Status Flags
 */
int CoreAPI::GetMotorPositionVelocity(int port, int &value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.GetValue(_S, port, value);
    return status;
}
/**
 * \test
 * (_C) see p.176
 * @param  port  Port
 * @param  value Return Value
 * @return       RQ Status Flags
 */
int CoreAPI::GetEncoderCounter(int port, int &value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.GetValue(_C, value);
    return status;
}
/**
 * \test
 * (_CB) see p.176
 * @param  port  Port
 * @param  value Return Value
 * @return       RQ Status Flags
 */
int CoreAPI::GetBrushlessCounter(int port, int &value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2))
        status = device.GetValue(_CB, port, value);
    return status;
}
/**
 * \test
 * Gets a User Integer Variable (_VAR) see p.187
 * @param  num   Which One
 * @param  value Return Value
 * @return       RQ Status Flags
 */
int CoreAPI::GetUserIntegerVariables(int num, int &value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(num, 0, 16))
        status = device.GetValue(_VAR, num, value);
    return status;
}
/**
 * \test
 * Gets a User Bool Variable (_B) see p.174
 * @param  num   Which One
 * @param  value Return Value
 * @return       RQ Status Flags
 */
int CoreAPI::GetUserIntegerBool(int num, int &value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(num, 0, 32))
        status = device.GetValue(_B, num, value);
    return status;
}
/**
 * \test
 * Gets whether a Digital Out is on or off (_DO) see p.
 * @param  port  Port
 * @param  value Return Value
 * @return       RQ Status Flags
 */
int CoreAPI::GetDigitalOuts(int port, int &value)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_DIGITAL_OUTPUTS))
        status = device.GetValue(_DO, port, value);
    return status;
}
/**************************************************************/
/************************ CONFIG ******************************/
/**************************************************************/

/**
* Gets the MotorController Type (_TRN) see p.186
* @param  type Returns the Motorcontroler type
* @return      RQ Status Flags
*/
int CoreAPI::GetMotorControllerType(std::string &type)
{
    std::string response;
    int status = device.GetRawValue(_TRN, response);
    std::istringstream iss(response);
    iss.ignore(256, ':');
    iss >> type;
    return status;
}
/**
* Gets the Firmwareversion (_FID) see p.180
* @param  firmware Returns the Motorcontroler Firmware Version
* @return          RQ Status Flags
*/
int CoreAPI::GetMotorControllerFirmware(std::string &firmware)
{
    return device.GetRawValue(_FID, firmware);
}
/**
* Gets the Scripting Autostart Mode (_BRUN) see p.196
* @param  val BRUN_DISABLED | BRUN_DELAYED | BRUN_ACTIVATED
* @return       RQ Status Flags
*/
int CoreAPI::GetScriptingAutostart(int &val)
{
    return device.GetConfig(_BRUN, val);
}
/**
* Gets the AnalogCenterSafety (_ACS) see p. 196
* @param  val is Analog Safety enabled
* @return       RQ Status Flags
*/
int CoreAPI::GetAnalogCenterSafety(int &val)
{
    return device.GetConfig(_ACS, val);;
}
/**
* Gets the Telemetry String (_TELS) p.199
* @param  str Telemetry String
* @return     RQ Status Flags
*/
int CoreAPI::GetTelemetryString(std::string &str)
{
    return device.GetRawConfig(_TELS, str);
}
/**
* Gets the ChannelPriorities (_CPRI) p.197
* @param  port Port: 1 - 3
* @param  val The Array represents the priority (first to third), the content is CP_X
* @return     RQ Status Flags
*/
int CoreAPI::GetChannelPriorities(int port, int &val)
{
    int status;
    if (CheckRange(port, 0, 3))
        status = device.GetConfig(_CPRI, port, val);
    return status;
}
/**
* Gets the Serial Timout (_RWD)  see p. 198
* @param  val Returns the Serial Timeout
* @return       RQ Status Flags
*/
int CoreAPI::GetSerialTimeout(int &val)
{
    return device.GetConfig(_RWD, val);
}
/**
* Gets the Linearity (_CLIN) see p.197
* @param  val Return the Linearity Values ( LIN_X)
* @return       RQ Status Flags
*/
int CoreAPI::GetLinearity(int &val)
{
    return device.GetConfig(_CLIN, val);
}
/**
* Gets Analog within Min & Max Safety (_AMS) see p.196
* @param  val Is Analog Safety enabled
* @return     RQ Status Flags
*/
int CoreAPI::GetAnalogMinMaxSafety(int &val)
{
    return device.GetConfig(_AMS, val);;
}
/**
* Read Brushless Count Relative (_CBR) see p.177
* @param  val Return Value
* @return     [description]
*/
int CoreAPI::GetBrushlessCountRelative(int &val)
{
    return device.GetConfig(_CBR, val);
}
/**
* Gets the Encoder Mode (_EMOD) see p.210
* @param  mot   Select the Motor: MOT1 | MOT2
* @param  val Returns the USAGE: ENC_UNUSED | ENC_COMMAND | ENC_FEEDBACK
* @return       RQ Status Flags
*/
int CoreAPI::GetEncoderMode(int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckMotor(mot))
    {
        status = device.GetConfig(_EMOD, val);
        ExtractDINA(mot, val);
    }
    return status;
}
/**
* Gets the Encoder PPR Value (_EPPR) see p.210
* @param  val Return Value, Range 1 - 5000 default: 100
* @return     RQ Status Flags
*/
int CoreAPI::GetEncoderPPR(int &val)
{
    return device.GetConfig(_EPPR, val);
}
/**
* Gets the Encoder Low Count Limit (_ELL) see p.209
* @param  val Returns the Low Limit Count
* @return     RQ Status Flags
*/
int CoreAPI::GetEncoderLowLimitCount(int &val)
{
    return device.GetConfig(_ELL, val);
}
/**
* Gets the Encoder High Count Limit (_ELL) see p.208
* @param  val Returns the Low Limit Count
* @return     RQ Status Flags
*/
int CoreAPI::GetEncoderHighLimitCount(int &val)
{
    return device.GetConfig(_EHL, val);
}
/**
* Gets the Encoder Counter Load at Home Position (_EHOME) see p.209
* @param  val Returns
* @return     RQ Status Flags
*/
int CoreAPI::GetEncoderCounterLoadAtHomePosition(int &val)
{
    return device.GetConfig(_EHOME, val);
}
/**
* Gets the Encoder Low Limit Action (_EHLA) see p.209
* @param  mot Motor: MOT1 | MOT2
* @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                            DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
* @return     RQ_Status_Flags
*/
int CoreAPI::GetEncoderLowLimitAction(int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckMotor(mot))
    {
        status = device.GetConfig(_ELLA, val);
        ExtractDINA(mot, val);
    }
    return status;
}
/**
* Gets the Encoder High Limit Action (_EHLA) see p.209
* @param  mot Motor: MOT1 | MOT2
* @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                            DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
* @return     RQ_Status_Flags
*/
int CoreAPI::GetEncoderHighLimitAction(int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckMotor(mot))
    {
        status = device.GetConfig(_EHLA, val);
        ExtractDINA(mot, val);
    }
    return status;
}
/**
 * Gets the Digital Input Active Level for each port (_DINL) see p.200
 * @param  port Which port
 * @param  val  High or Low
 * @return      RQ Status Flags
 */
int CoreAPI::GetDigitalInput(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_DIGITAL_INPUTS))
        status = device.GetConfig(_DINL, port, val);
    return status;
}
/**
 * Gets the Digital Input Action if a port is triggered (_DINA) see p.199
 * @param  port Port: 0 - MAX_DIGITAL_INPUTS
 * @param  mot  Motor: DINA_MOT1 | DINA_MOT2 | DINA_MOT12
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return      RQ Status Flags
 */
int CoreAPI::GetDigitalInputAction(int port, int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if ((mot == DINA_MOT1 || mot == DINA_MOT2 || mot == DINA_MOT12)
            && CheckRange(port, 0, MAX_DIGITAL_INPUTS))
    {
        status = device.GetConfig(_DINA, port, val);
        if ((val & mot) != 0)
            val = val & ~DINA_MOT12;
    }
    return status;
}
/**
 * Gets the Analog Input Mode (_AMOD) see p.204
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  AMOD Values: AMOD_DISABLED | AMOD_ABSOLUTE | AMOD_RELATIVE
 * @return      RQ Status Flags
 */
int CoreAPI::GetAnalogInputMode(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_AMOD, port, val);
    return status;
}
/**
 * Gets the Analog Input Actions for each port (_AINA) see p.202
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Returns the USAGE: ENC_UNUSED | ENC_COMMAND | ENC_FEEDBACK
 * @return      RQ Status Flags
 */
int CoreAPI::GetAnalogInputAction(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_AINA, port, val);
    return status;
}
/**
 * Get Analog Input Range for each Point (_AMIN) see p. 203
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Min: 0 - 5000 mV default: 100mV
 * @return      RQ Status Flags
 */
int CoreAPI::GetAnalogInputMin(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_AMIN, port, val);
    return status;
}
/**
 * Gets the Analog Input Center (_ACTR) see p. 201
 * @param  port Port: 0 - MAX_ANALOG_INPUT
 * @param  val  Center: 0 - 5000 default: 2500
 * @return      RQ Status Flags
 */
int CoreAPI::GetAnalogInputCenter(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_ACTR, port, val);
    return status;
}
/**
 * Gets the Analog Input Max (_AMAX) see p. 203
 * @param  port Port: 0 - MAX_ANALOG_INPUT
 * @param  val  Max: 0 - 5000 default: 4900
 * @return      RQ Status Flags
 */
int CoreAPI::GetAnalogInputMax(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_AMAX, port, val);
    return status;
}
/**
 * Gets the Analog Input Polarity for every port (_APOL) see p.204
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Polarity: POL_UNINVERTED | POL_INVERTED
 * @return      RQ Status Flags
 */
int CoreAPI::GetAnalogInputPolarity(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status =  device.GetConfig(_APOL, port, val);
    return status;
}
/**
 * Gets the Analog Deadband (_ADB) see p.201
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Deadband: 0 - 50
 * @return      RQ Status Flags
 */
int CoreAPI::GetAnalogDeadband(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_ADB, port, val);
    return status;
}
/**
 * Gets the Action on Analog Min (_AMINA) see p.201
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return      RQ Status Flags
 */
int CoreAPI::GetAnalogMinAction(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_AMINA, port, val);
    return status;
}
/**
 * Gets the Action on Analog Max (_AMAXA
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return      RQ Status Flags
 */
int CoreAPI::GetAnalogMaxAction(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status =  device.GetConfig(_AMAXA, port, val);
    return status;
}
/**
 * Gets the Pulse Operating Mode (_PMOD) see p. 207
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  PM Values:  PM_DISABLED  |  PM_PULSE_WIDTH |  PM_FREQUENCY |  PM_PERIOD
 * @return      RQ Status Flags
 */
int CoreAPI::GetPulseInputMode(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status =  device.GetConfig(_PMOD, port, val);
    return status;
}
/**
 * Gets the Action on a Pulse (_PINA) see p.206
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Action: ENC_COMMAND | ENC_FEEDBACK | ENC_UNUSED
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @return      RQ Status Flags
 */
int CoreAPI::GetPulseInputAction(int port, int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS) && CheckMotor(mot))
        status = device.GetConfig(_PINA, port, val);
    ExtractDINA(mot, val);
    return status;
}
/**
 * Gets the Pulse Min Range (_PMIN) see p.207
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Minimum: 0 - 65000 us default: 1000
 * @return      RQ Status Flags
 */
int CoreAPI::GetPulseMin(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_PMIN, port, val);
    return status;
}
/**
 * Gets the Pulse Max Range (_PMAX) see p.206
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Minimum: 0 - 65000 us default: 2000
 * @return      RQ Status Flags
 */
int CoreAPI::GetPulseMax(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_PMAX, port, val);
    return status;
}
/**
 * Gets the Pulse Center Range (_PCTR) see p.205
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Minimum: 0 - 65000 us default: 1500
 * @return      RQ Status Flags
 */
int CoreAPI::GetPulseCenter(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_PCTR, port, val);
    return status;
}
/**
 * Gets the Pulse Input Deadband (_PDB) see p. 205
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Deadband: 0 - 50 default: 0
 * @return      RQ Status Flags
 */
int CoreAPI::GetPulseDeadbeand(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_PDB, port, val);
    return status;
}
/**
 * Gets the Action on Max Pulse (_PMAX) see p.207
 * @param  port Port: 0 - Max_ANALOG_INPUTS
 * @param  val  DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                              DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @return      RQ Status Flags
 */
int CoreAPI::GetPulseMaxAction(int port, int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
    {
        status = device.GetConfig(_PMAXA, port, val);
        ExtractDINA(mot, val);
    }
    return status;
}
/**
 * Gets the Action on Min Pulse (_PMAX) see p.207
 * @param  port Port: 0 - Max_ANALOG_INPUTS
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @return      RQ Status Flags
 */
int CoreAPI::GetPulseMinAction(int port, int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
    {
        status = device.GetConfig(_PMINA, port, val);
        ExtractDINA(mot, val);
    }
    return status;
}
/**
 * Gets the Linearity on the Pulse Input (_PLIN) see p.206
 * @param  port Port: 0 - MAX_ANALOG_INPUTS
 * @param  val  Linearty: LIN_LINEAR | LIN_EXP_WEAK | LIN_EXP_MEDIUM | LIN_EXP_STRONG | LIN_LOG_WEAK | LIN_LOG_MEDIUM | LIN_LOG_STRONG
 * @return      RQ Status Flags
 */
int CoreAPI::GetPulseLinearity(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_ANALOG_INPUTS))
        status = device.GetConfig(_PLIN, port, val);
    return status;
}
/**
 * Gets the Digital Output Active Levels (_DOL) see p.200
 * @param  port Port: 0 - MAX_DIGITAL_OUTPUTS
 * @param  val  Active Level: DO_ACTIVE_HIGH | DO_ACTIVE_LOW
 * @return      RQ Status Flags
 */
int CoreAPI::GetDigitalOutputActiveLevel(int port, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_DIGITAL_OUTPUTS))
        status = device.GetConfig(_DOL, port, val);
    return status;
}
/**
 * Gets the Digital Output Action (_DOA) see p.200
 * @param  port Port: 0 - MAX_DIGITAL_OUTPUTS
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val  Actions: DO_NO_ACTION | DO_MOTOR_ON | DO_OVERVOLTAGE | DO_OVERTEMPERATURE  | DO_MIRROR_STATUS_LED | DO_NO_MOSFET_FAILURE
 * @return      RQ Status Flags
 */
int CoreAPI::GetDigitalOutputAction(int port, int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, MAX_DIGITAL_OUTPUTS) && CheckMotor(mot))
    {
        status = device.GetConfig(_DOA, port, val);
        ExtractDINA(mot, val);
    }
    return status;
}
/**
 * Gets the PWM Frequency (_PWMF) see p.215
 * @param  val PWM Frequency multiplied with 10, Range: 10 - 200 (1 - 20kHz)
 * @return     RQ Status Flags
 */
int CoreAPI::GetPWMFrequency(int &val)
{
    return device.GetConfig(_PWMF, val);
}
/**
 * Gets the Overvoltage Limit, at this point an overvoltage signal is issued (_OVL)
 * @param  val Overvoltage Limit multiplied by 10: Range 100 - MAX_OVERVOLTAGE
 * @return     RQ Status Flags
 */
int CoreAPI::GetOvervoltageLimit(int &val)
{
    return device.GetConfig(_OVL, val);
}
/**
 * Gets the Undervoltage Limit (_UVL) see p.215
 * @param  val Overvoltage Limit multiplied by 10: Range 50 - MAX_OVERVOLTAGE
 * @return     RQ Status Flags
 */
int CoreAPI::GetUndervoltageLimit(int &val)
{
    return device.GetConfig(_UVL, val);
}
/**
 * Gets the Break Delay (_BKD) see p. 214
 * @param  val Delay in ms
 * @return     RQ Status Flags
 */
int CoreAPI::GetBrakeActivationDelay(int &val)
{
    return device.GetConfig(_BKD, val);
}
/**
 * Gets the Short Circuit Detection Sensitivity (_THLD) see p.215
 * @param  val Sensitivity: THLD_HIGH_SENSITIVITY | THLD_MEDIUM_SENSITIVITY | THLD_LOW_SENSITIVITY | THLD_DISABLED
 * @return     RQ Status Flags
 */
int CoreAPI::GetShortCircuitThreshold(int &val)
{
    return device.GetConfig(_THLD, val);
}

/**
 * Gets the Number of Poles of the BL Motor (_BPOL) see p.213
 * @param  mot Motor: 1 or 2
 * @param  val [description]
 * @return     [description]
 */
int CoreAPI::GetNumPoles(int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(mot, 0, 2))
        status = device.GetConfig(_BPOL, mot, val);
    return status;
}
/**
 * Gets the selected Encoder (_BLFB) see p.212
 * @param  mot Motor: 1 or 2
 * @param  val Feedback: BLFB_HALL_SENSOR | BLFB_ENCODER
 * @return     RQ Status Flags
 */
int CoreAPI::GetBrushlessFeedback(int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(mot, 0, 2))
        status = device.GetConfig(_BLFB, mot, val);
    return status;
}

/**
 * Get the Stall Detection Mode (_BLSTD) see p.213
 * @param  mot Motor: 1 or 2
 * @param  val Detection Modes: BLSTD_DISABLED | BLSTD_250MS_OVER_10  | BLSTD_500OMS_0VER_25 | BLSTD_1000MS_OVER_50 3
 * @return     RQ Status Flags
 */
int CoreAPI::GetBrushlessStallDetection(int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(mot, 0, 2))
        status = device.GetConfig(_BLSTD, mot, val);
    return status;
}
/**
 * (_BLL) see p.212
 * @param  mot Motor: 1 or 2
 * @param  val Counter: default -2000
 * @return     RQ Status Flags
 */
int CoreAPI::GetEncoderLowLimit(int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(mot, 0, 2))
        status = device.GetConfig(_BLL, mot, val);
    return status;
}
/**
 * Gets the Brushless Counter High Limit (_BHL) see p.211
 * @param  mot Motor: 1 or 2
 * @param  val Counter default -2000
 * @return     RQ Status Flags
 */
int CoreAPI::GetEncoderHighLimit(int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(mot, 0, 2))
        status = device.GetConfig(_BHL, mot, val);
    return status;
}
/**
 * Brushless Counter Load at Home Position (_BHOME) see p.211
 * @param  mot Motor: 1 or 2
 * @param  val Counter
 * @return     RQ Status Flags
 */
int CoreAPI::GetBrushlessHomeCounter(int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(mot, 0, 2))
        status = device.GetConfig(_BHOME, mot, val);
    return status;
}
/**
 * Encoder High Limit Action (_BHLA) see p.211
 * @param  port Port: 1 or 2
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return      RQ Status Flags
 */
int CoreAPI::GetEncoderHighLimitAction(int port, int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2) && CheckMotor(mot))
    {
        status = device.GetConfig(_BHLA, port, val);
        ExtractDINA(mot, val);
    }
    return status;
}
/**
 * Encoder Low Limit Action (_BHLA) see p.211
 * @param  port Port: 1 or 2
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return      RQ Status Flags
 */
int CoreAPI::GetEncoderLowLimitAction(int port, int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckRange(port, 0, 2) && CheckMotor(mot))
    {
        status = device.GetConfig(_BLLA, port, val);
        ExtractDINA(mot, val);
    }
    return status;
}
/**
 * Amps Limit (_ALIM) see p.216
 * @param  val Amps multiplied with 10: 10A to Datasheet Max, default: 75% of Max
 * @return     RQ Status Flags
 */
int CoreAPI::GetMotorAmpsLimit(int &val)
{
    return device.GetConfig(_ALIM, val);
}
/**
 * Amps Trigger Value (_ATRIG) see p.217
 * @param  val Amps multiplied with 10: 10A to Datasheet Max, default: 75% of Max
 * @return     RQ Status Flags
 */
int CoreAPI::GetMotorAmpsTriggerValue(int &val)
{
    return device.GetConfig(_ATRIG, val);
}
/**
 * Amps Trigger Action (_ATGA) see p.217
 * @param  mot  Motor: MOT1 | MOT2 | MOT12
 * @param  val DINA Values:  DINA_NO_ACTION | DINA_SAFETY_STOP | DINA_EMERGENCY_STOP | DINA_MOTOR_STOP | DINA_FORWARD_LIMIT_SWITCH |
                             DINA_REVERSE_LIMIT_SWITCH | DINA_INVERT_DIRECTION | DINA_RUN_MICROBASIC | DINA_LOAD_HOME_VALUE
 * @return     RQ Status Flags
 */
int CoreAPI::GetMotorAmpsTriggerAction(int mot, int &val)
{
    int status = RQ_INVALID_CONFIG_ITEM;
    if (CheckMotor(mot))
    {
        status = device.GetConfig(_ATGA, val);
        ExtractDINA(mot, val);
    }
    return status;
}
/**
 * Amps Trigger Delay (_ATGD) see p.217
 * @param  val Delay in ms
 * @return     RQ Status Delay
 */
int CoreAPI::GetMotorAmpsTriggerDelay(int &val)
{
    return device.GetConfig(_ATGD, val);
}
/**
 * Max Power Forward (_MXPF) see p.220
 * @param  val Power: 25 - 100, default: 100
 * @return     RQ Status Flags
 */
int CoreAPI::GetMotorMaxPowerForward(int &val)
{
    return device.GetConfig(_MXPF, val);
}
/**
 * Max Power Forward (_MXPR) see p.221
 * @param  val Power: 25 - 100, default: 100
 * @return     RQ Status Flags
 */
int CoreAPI::GetMotorMaxPowerReverse(int &val)
{
    return device.GetConfig(_MXPR, val);
}
/**
 * Max RPM (_MXRPM) see p.221
 * @param  val RPM: 10 - 65000, default: 3000
 * @return     RQ Status Flags
 */
int CoreAPI::GetMotorMaxRPM(int &val)
{
    return device.GetConfig(_MXRPM, val);
}
/**
 * Get Acceleration time in 0.1 RPM per seconds (_MAC) see p.219
 * @param  val Accel: 100 to 32000
 * @return     RQ Status Flags
 */
int CoreAPI::GetAcceleration(int &val)
{
    return device.GetConfig(_MAC, val);
}
/**
 * Gets Deceleration time in 0.1 RPM per second (_MDEC) see p.220
 * @param  val Deccel: 100 - 32000
 * @return     RQ Status Flags
 */
int CoreAPI::GetDeacceleration(int &val)
{
    return device.GetConfig(_MDEC, val);
}
/**
 * Gets the Motor Operating Mode (_MMOD) see p.220
 * @param  val Mode: MMOD_OPEN_LOOP_SPEED | MMOD_CLOSED_LOOP_SPEED | MMOD_CLOSED_LOOP_POSITION_RELATIVE
 *                   | MMOD_closed_LOPP_COUNT_POSITION | MMOD_CLOSED_LOOP_POSITION_TRACKING | MMOD_TORQUE
 * @return     RQ Status Flags
 */
int CoreAPI::GetMotorOperatingMode(int &val)
{
    return device.GetConfig(_MMOD, val);
}
/**
 * Gets the Velocity value in RPM (_MVEL) see p.220
 * @param  val Velocity
 * @return     RQ Status Flags
 */
int CoreAPI::GetMotorDefaultVelocity(int &val)
{
    return device.GetConfig(_MVEL, val);
}
/**
 * Gets the Turns between Limits (_MXTRN) see p.221
 * @param  val Turns multiplied with 10
 * @return     RQ Status Flags
 */
int CoreAPI::GetMotorMaxTurns(int &val)
{
    return device.GetConfig(_MXTRN, val);
}
/**
 * Gets the Proportional Gain for the Channel (_KP) see p.219
 * @param  val Gain multiplied with 10
 * @return     RQ Status Flags
 */
int CoreAPI::GetProportionalGain(int &val)
{
    return device.GetConfig(_KP, val);
}
/**
 * Gets the PID Integral Gain (_KI) see p.219
 * @param  val Gain multiplied with 10
 * @return     RQ Status Flags
 */
int CoreAPI::GetIntegrationalGain(int &val)
{
    return device.GetConfig(_KI, val);
}
/**
 * Gets the PID Differential Gain (_KD) see p.218
 * @param  val Gain multiplied with 10
 * @return     RQ Status Flags
 */
int CoreAPI::GetDifferentialGain(int &val)
{
    return device.GetConfig(_KD, val);
}
/**
 * Gets the PID Integral Cap (_ICAP) see p. 218
 * @param  val Integral cap in %: 1 - 100, default: 100
 * @return     RQ Status Flags
 */
int CoreAPI::GetMotorIntCap(int &val)
{
    return device.GetConfig(_ICAP, val);
}
/**
 * Gets the Loop Error Detection Mode (_CLERD) see p.218
 * @param  val Detections Modes: CLERD_DISABLED | CLERD_250msGreater100 | CLERD_500msGreater250 | CLERD_1000msGreater500
 * @return     RQ Status Flags
 */
int CoreAPI::GetLoopErrorMode(int &val)
{
    return device.GetConfig(_CLERD, val);
}
/**
 * Device Connected
 * @return bool
 */
bool CoreAPI::IsConnected()
{
    return device.IsConnected();
}
/**************************************************************/
/************************ INLINE ******************************/
/**************************************************************/
bool inline CoreAPI::CheckRange(int val, int min, int max)
{
    return val >= min && val <= max;
}
bool inline CoreAPI::CheckMotor(int mot)
{
    return mot == MOT1 || mot == MOT2 || mot == MOT12;
}
void inline CoreAPI::ExtractDINA(int mot, int &val)
{
    if ((val & mot) != 0)
        val = val & ~MOT12;
}
