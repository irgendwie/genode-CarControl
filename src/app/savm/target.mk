TARGET = savm
SRC_CC = main.cc savm.cc
LIBS += base libmosquitto stdcxx lwip
#INC_DIR += $(call select_from_repositories,include/lwip)
