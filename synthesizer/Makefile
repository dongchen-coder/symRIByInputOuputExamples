LIB_DIR=./lib
SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin

CC=g++
CCFLAG= -std=c++11 -O2 -pipe #-save-temps=obj

symRiSynthesiser.o:
	$(CC) ${CCFLAG} -c $(SRC_DIR)/symRiSynthesiser.cpp -o $(OBJ_DIR)/symRiSynthesiser.o

langDef.o:
	$(CC) ${CCFLAG} -c $(LIB_DIR)/langDef.cpp -o $(OBJ_DIR)/langDef.o

bottomUpSearch.o:
	$(CC) ${CCFLAG} -c $(LIB_DIR)/bottomUpSearch.cpp -o $(OBJ_DIR)/bottomUpSearch.o

unification.o:
	$(CC) ${CCFLAG} -c $(LIB_DIR)/unification.cpp -o $(OBJ_DIR)/unification.o

sampler.o:
	$(CC) ${CCFLAG} -c $(LIB_DIR)/sampler.cpp -o $(OBJ_DIR)/sampler.o

gen: symRiSynthesiser.o langDef.o bottomUpSearch.o unification.o sampler.o
	$(CC) ${CCFLAG} -pthread -o $(BIN_DIR)/symRiSymthesiser $(OBJ_DIR)/symRiSynthesiser.o $(OBJ_DIR)/langDef.o $(OBJ_DIR)/bottomUpSearch.o $(OBJ_DIR)/unification.o $(OBJ_DIR)/sampler.o

