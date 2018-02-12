//   PROTOTYPE SETTER:
//   int SetSomething(int PORT, int VALUE)
//      int status = RQ_INVALID_CONFIG_ITEM;
//      if (CheckRange(PORT, MIN, MAX) && CheckRange(VALUE, MIN, MAX))
//          status = device.SetCommand(CMD, PORT, VALUE);
//      return status;
//
//   PROTOTYPE GETTER:
//   int GetSomething(int PORT, int& VALUE)
//      int status = RQ_INVALID_CONFIG_ITEM;
//      if (CheckRange(PORT, MIN, MAX))
//          status =  device.GetConfig(CMD, PORT, VALUE);
//      return status;
//      
//  Also dont use block comments

#ifndef __CoreAPI__
#define __CoreAPI__

#include "RoboteqDevice.h"

class CoreAPI
{
private:
    RoboteqDevice device;
    inline bool CheckRange(int val, int min, int max);
    inline bool CheckMotor(int mot);
    inline void ExtractDINA(int mot, int &val);
protected:
public:
    /*****************************************************/
    int SetMotorSpeedAccel(int speed, int accel);
    int SetMotorSpeedDecel(int speed, int decel);
    int SetMotorSpeedRel(int speed);
    int SetMotorSpeedAbs(int speed);

    int SetAbsoluteDesiredPosition(int port, int value);
    int SetMotorPositionVelocity(int port, int value);
    int SetNextPositionVelocity(int port, int value);
    int SetEncoderCounter(int port, int value);
    int SetBrushlessCounter(int port, int value);
    int SetUserIntegerVariables(int num, int value);
    int SetUserIntegerBool(int num, int value);
    int SetAcceleration(int port, int accel);
    int SetNextAcceleration(int port, int accel);
    int SetDeceleration(int port, int decel);
    int SetNextDeceleration(int port, int decel);
    int SetDigitalOuts(int port);
    int SetResetDigitalOuts(int port);
    int SetLoadHomeCounter(int port);
    int SetEmergencyStop();
    int SetReleaseEmergencyStop();
    int SetEmergencyStop(int port);
    int SetRelativeDesiredPosition(int port, int value);
    int SetNextAbsoluteDesiredPosition(int port, int value);
    int SetNextRelativeDesiredPosition(int port, int value);
    int SetSaveConfig();

    // CONFIG
    int SetScriptingAutostart(int val);
    int SetAnalogCenterSafety(int val);
    int SetChannelPriorities(int port, int val);
    int SetSerialTimout(int val);
    int SetLinearity(int val);
    int SetAnalogMinMaxSafety(int val);
    int SetEncoderMode(int mot, int val);
    int SetEncoderPPR(int val);
    int SetEncoderLowLimitCount(int val);
    int SetEncoderHighLimitCount(int val);
    int SetEncoderCounterLoadAtHomePosition(int val);
    int SetEncoderLowLimitAction(int mot, int val);
    int SetEncoderHighLimitAction(int mot, int val);
    int SetDigitalInput(int port, int val);
    int SetDigitalInputAction(int port, int mot, int val);
    int SetAnalogInputMode(int port, int val);
    int SetAnalogInputAction(int port, int mot, int val);
    int SetAnalogInputMin(int port, int val);
    int SetAnalogInputCenter(int port, int val);
    int SetAnalogInputMax(int port, int val);
    int SetAnalogInputPolarity(int port, int val);
    int SetAnalogDeadband(int port, int val);
    int SetAnalogMinAction(int port, int mot, int val);
    int SetAnalogMaxAction(int port, int mot, int val);
    int SetPulseInputMode(int port, int val);
    int SetPulseInputAction(int port, int mot, int val);
    int SetPulseMin(int port, int val);
    int SetPulseMax(int port, int val);
    int SetPulseCenter(int port, int val);
    int SetPulseDeadbeand(int port, int val);
    int SetPulseMinAction(int port, int mot, int val);
    int SetPulseMaxAction(int port, int mot, int val);
    int SetPulseLinearity(int port, int val);
    int SetDigitalOutputActiveLevel(int port, int val);
    int SetDigitalOutputAction(int port, int mot, int val);
    int SetPWMFrequency(int val);
    int SetOvervoltageLimit(int val);
    int SetUndervoltageLimit(int val);
    int SetBrakeActivationDelay(int val);
    int SetShortCircuitThreshold(int val);
    int SetNumPoles(int mot, int val);
    int SetBrushlessFeedback(int mot, int val);
    int SetBrushlessStallDetection(int mot, int val);
    int SetEncoderLowLimit(int mot, int val);
    int SetEncoderHighLimitAction(int port, int mot, int val);
    int SetEncoderLowLimitAction(int port, int mot, int val);
    int SetMotorAmpsLimit(int val);
    int SetMotorAmpsTriggerValue(int val);
    int SetMotorAmpsTriggerAction(int mot, int val);
    int SetMotorAmpsTriggerDelay(int val);
    int SetMotorMaxPowerForward(int val);
    int SetMotorMaxPowerReverse(int val);
    int SetMotorMaxRPM(int val);
    int SetMotorOperatingMode(int val);
    int SetMotorDefaultVelocity(int val);
    int SetMotorMaxTurns(int val);
    int SetProportionalGain(int val);
    int SetIntegrationalGain(int val);
    int SetDifferentialGain(int val);
    int SetMotorIntCap(int val);
    int SetLoopErrorMode(int val);

    //int SetTelemetryString(std::string &str);
    //int SetEncoderHighLimit(int mot, int val);
    //int SetBrushlessHomeCounter(int mot, int val);
    /******************************************************/
    int GetMotorPower(int &power);
    int GetMotorRPM(int &rpm);
    int GetMotorAmps(int &amps);
    int GetBatteryVolt(int &volt);
    int GetControllerVolt(int &volt);
    int Get5VOutput(int &volt);
    int GetMotorTemperature(int &temp);
    int GetMCUTemperature(int &temp);
    // CONFIG
    int GetMotorControllerType(std::string &val);
    int GetMotorControllerFirmware(std::string &val);
    int GetLoopError(int &val);
    int GetScriptingAutostart(int &val);
    int GetAnalogCenterSafety(int &val);
    int GetTelemetryString(std::string &str);
    int GetChannelPriorities(int port, int &val);
    int GetSerialTimeout(int &val);
    int GetLinearity(int &val);
    int GetAnalogMinMaxSafety(int &val);
    int GetBrushlessCountRelative(int &val);
    int GetEncoderMode(int mot, int &val);
    int GetEncoderPPR(int &val);
    int GetEncoderLowLimitCount(int &val);
    int GetEncoderHighLimitCount(int &val);
    int GetEncoderCounterLoadAtHomePosition(int &val);
    int GetEncoderLowLimitAction(int mot, int &val);
    int GetEncoderHighLimitAction(int mot, int &val);
    int GetDigitalInput(int port, int &val);
    int GetDigitalInputAction(int port, int mot, int &val);
    int GetAnalogInputMode(int port, int &val);
    int GetAnalogInputAction(int port, int &val);
    int GetAnalogInputMin(int port, int &val);
    int GetAnalogInputCenter(int port, int &val);
    int GetAnalogInputMax(int port, int &val);
    int GetAnalogInputPolarity(int port, int &val);
    int GetAnalogDeadband(int port, int &val);
    int GetAnalogMinAction(int port, int &val);
    int GetAnalogMaxAction(int port, int &val);
    int GetPulseInputMode(int port, int &val);
    int GetPulseInputAction(int port, int mot, int &val);
    int GetPulseMin(int port, int &val);
    int GetPulseMax(int port, int &val);
    int GetPulseCenter(int port, int &val);
    int GetPulseDeadbeand(int port, int &val);
    int GetPulseMinAction(int port, int mot, int &val);
    int GetPulseMaxAction(int port, int mot, int &val);
    int GetPulseLinearity(int port, int &val);
    int GetDigitalOutputActiveLevel(int port, int &val);
    int GetDigitalOutputAction(int port, int mot, int &val);
    int GetPWMFrequency(int &val);
    int GetOvervoltageLimit(int &val);
    int GetUndervoltageLimit(int &val);
    int GetBrakeActivationDelay(int &val);
    int GetShortCircuitThreshold(int &val);
    int GetNumPoles(int mot, int &val);
    int GetBrushlessFeedback(int mot, int &val);
    int GetBrushlessStallDetection(int mot, int &val);
    int GetEncoderLowLimit(int mot, int &val);
    int GetEncoderHighLimit(int mot, int &val);
    int GetBrushlessHomeCounter(int mot, int &val);
    int GetEncoderHighLimitAction(int port, int mot, int &val);
    int GetEncoderLowLimitAction(int port, int mot, int &val);
    int GetMotorAmpsLimit(int &val);
    int GetMotorAmpsTriggerValue(int &val);
    int GetMotorAmpsTriggerAction(int mot, int &val);
    int GetMotorAmpsTriggerDelay(int &val);
    int GetMotorMaxPowerForward(int &val);
    int GetMotorMaxPowerReverse(int &val);
    int GetMotorMaxRPM(int &val);
    int GetAcceleration(int &val);
    int GetDeacceleration(int &val);
    int GetMotorOperatingMode(int &val);
    int GetMotorDefaultVelocity(int &val);
    int GetMotorMaxTurns(int &val);
    int GetProportionalGain(int &val);
    int GetIntegrationalGain(int &val);
    int GetDifferentialGain(int &val);
    int GetMotorIntCap(int &val);
    int GetLoopErrorMode(int &val);

    int GetAbsoluteDesiredPosition(int port, int &value);
    int GetMotorPositionVelocity(int port, int &value);
    int GetEncoderCounter(int port, int &value);
    int GetBrushlessCounter(int port, int &value);
    int GetUserIntegerVariables(int num, int &value);
    int GetUserIntegerBool(int num, int &value);
    int GetDigitalOuts(int port, int &value);

    bool IsConnected();

    // TODO
    //int GetNextPositionVelocity(int port, int &value);
    /********************** Constructor **************************/
    CoreAPI(int ConnectionType);
    ~CoreAPI();
};

#endif
