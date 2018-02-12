/********** BRUN ***************/
#define BRUN_DISABLED 0
#define BRUN_DELAYED 1
#define BRUN_ACTIVATED 2

/******** Command Priorities *******/
#define CPRI_DISABLED 0
#define CPRI_SERIAL 1
#define CPRI_RC 2
#define CPRI_ANALOG 3

/********* Linearity **************/
#define LIN_LINEAR 0
#define LIN_EXP_WEAK 1
#define LIN_EXP_MEDIUM 2
#define LIN_EXP_STRONG 3
#define LIN_LOG_WEAK 4
#define LIN_LOG_MEDIUM 5
#define LIN_LOG_STRONG 6

/******** Encode Usage ************/
#define ENC_UNUSED 0
#define ENC_COMMAND 1
#define ENC_FEEDBACK 2

/*********** Motor Numbers ********/
#define MOT1 16
#define MOT2 32
#define MOT12 48

/************ DINA ****************/
#define DINA_NO_ACTION 0
#define DINA_SAFETY_STOP 1
#define DINA_EMERGENCY_STOP 2
#define DINA_MOTOR_STOP 3
#define DINA_FORWARD_LIMIT_SWITCH 4
#define DINA_REVERSE_LIMIT_SWITCH 5
#define DINA_INVERT_DIRECTION 6
#define DINA_RUN_MICROBASIC 7
#define DINA_LOAD_HOME_VALUE 8
#define DINA_MOT1 32
#define DINA_MOT2 64
#define DINA_MOT12 96

/************ AMOD ****************/
#define AMOD_DISABLED 0
#define AMOD_ABSOLUTE 1
#define AMOD_RELATIVE 2

/********** Polarity **************/
#define APOL_UNINVERTED 0
#define APOL_INVERTED 1

/************* Deadband ************/
#define DB_MIN 0
#define DB_MAX 50

/************* Pulse Mode **********/
#define PMOD_DISABLED 0
#define PMOD_PULSE_WIDTH 1
#define PMOD_FREQUENCY 2
#define PMOD_PERIOD 3

/********* Digital Output ***********/
#define DOL_ACTIVE_HIGH 0
#define DOL_ACTIVE_LOW 1

#define DOA_NO_ACTION 0
#define DOA_MOTOR_ON 1
#define DOA_OVERVOLTAGE 2
#define DOA_OVERTEMPERATURE 3
#define DOA_MIRROR_STATUS_LED 4
#define DOA_NO_MOSFET_FAILURE 5

/********** Short Circuit **********/
#define THLD_HIGH_SENSITIVITY 0
#define THLD_MEDIUM_SENSITIVITY 1
#define THLD_LOW_SENSITIVITY 2
#define THLD_DISABLED 3

/********* Feedback **************/
#define BLFB_HALL_SENSOR 0
#define BLFB_ENCODER 1

/********* Stall Detection *******/
#define BLSTD_DISABLED 0
#define BLSTD_250MS_OVER_10 1
#define BLSTD_500OMS_0VER_25 2
#define BLSTD_1000MS_OVER_50 3

/****** Motor Operatin Mode ******/
#define MMOD_OPEN_LOOP_SPEED 0
#define MMOD_CLOSED_LOOP_SPEED 1
#define MMOD_CLOSED_LOOP_POSITION_RELATIVE 2
#define MMOD_closed_LOPP_COUNT_POSITION 3
#define MMOD_CLOSED_LOOP_POSITION_TRACKING 4
#define MMOD_TORQUE 5

/********* LOOP ERROR Detection *******/
#define CLERD_DISABLED 0
#define CLERD_250msGreater100 1
#define CLERD_500msGreater250 2
#define CLERD_1000msGreater500 3

/************** General ***************/
#define MAX_DIGITAL_INPUTS 6
#define MAX_ANALOG_INPUTS 6
#define MAX_DIGITAL_OUTPUTS 2
#define MAX_OVERVOLTAGE 500


/*************** COM *******************/
#define CONNECTION_USB 0
#define CONNECTION_CAN 1
#define CONNECTION_COM 2

#define MAX_RPM 2500
