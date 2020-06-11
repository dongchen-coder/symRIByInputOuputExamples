LIB_DIR=./lib
SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin

CC=g++
CFLAGS=-I.
DEPS = extractInputOutputForSingleRI #bottomUpSearch extractInputOutputForSingleRI langDef symRiSynthesiser

symRiSynthesiser.o:
	$(CC) -std=c++11 -c $(SRC_DIR)/symRiSynthesiser.cpp -o $(OBJ_DIR)/symRiSynthesiser.o

langDef.o:
	$(CC) -std=c++11 -c $(LIB_DIR)/langDef.cpp -o $(OBJ_DIR)/langDef.o

bottomUpSearch.o:
	$(CC) -std=c++11 -c $(LIB_DIR)/bottomUpSearch.cpp -o $(OBJ_DIR)/bottomUpSearch.o

extractInputOutputForSingleRI.o:
	$(CC) -std=c++11 -c $(LIB_DIR)/extractInputOutputForSingleRI.cpp -o $(OBJ_DIR)/extractInputOutputForSingleRI.o

inputOutputGen.o:
	$(CC) -std=c++11 -c $(SRC_DIR)/inputOutputGen.cpp -o $(OBJ_DIR)/inputOutputGen.o

gen: extractInputOutputForSingleRI.o inputOutputGen.o symRiSynthesiser.o langDef.o bottomUpSearch.o
	$(CC) -o $(BIN_DIR)/inputOutputGen $(OBJ_DIR)/extractInputOutputForSingleRI.o $(OBJ_DIR)/inputOutputGen.o
	$(CC) -o $(BIN_DIR)/symRiSymthesiser $(OBJ_DIR)/symRiSynthesiser.o $(OBJ_DIR)/langDef.o $(OBJ_DIR)/bottomUpSearch.o