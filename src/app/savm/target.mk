TARGET = savm
SRC_CC = main.cc savm.cc SensorDataOut.pb.cc CommandDataIn.pb.cc
INC_DIR += $(REP_DIR)/include/savm/
LIBS += base libmosquitto stdcxx lwip libprotobuf pthread
