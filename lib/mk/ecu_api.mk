SRC_CC = RoboteqDevice.cpp ComAPI.cpp CoreAPI.cpp Mapping.cpp

LIBS = base stdcxx

REP_INC_DIR += include/ecu_api

vpath % $(REP_DIR)/src/lib/ecu_api
