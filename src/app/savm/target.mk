TARGET = savm
SRC_CC = main.cc savm.cc
SRC_PROTO = SensorDataOut.proto CommandDataIn.proto
LIBS += base libmosquitto stdcxx lwip libprotobuf pthread
