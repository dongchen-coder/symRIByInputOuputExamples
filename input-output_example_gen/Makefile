LIB_DIR=./lib
SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin

BENCH_DIR=./bench
BENCH_BIN_DIR=./bin/bench_bin

RIS_RAW_DIR=./inputoutput/raw_ris_per_size
IBOUND_RAW_DIR=./inputoutput/raw_ibound
INPUTOUTPUT_DIRS=./inputoutput/ris_refsrc_Isrc_Psrc ./inputoutput/ris_refsrc_Isrc_Psrc_refsnk ./inputoutput/ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk ./inputoutput/ris_Ibound

RIS_MATCH_DIR=./verify/histoToMatch_CLS32_DS8

bench=stencil stencil_tiled 2mm 3mm adi atax bicg cholesky correlation covariance deriche doitgen durbin fdtd_2d floyd_warshall gemm gemver gesummv gramschmidt heat_3d jacobi_1d jacobi_2d lu ludcmp mvt nussinov seidel_2d symm syr2d syrk trisolv trmm convolution_2d convolution_3d trangle

CC=g++
CCFLAG= -std=c++11 -O2 -pipe #-save-temps=obj

extractInputOutputForSingleRI.o:
	$(CC) ${CCFLAG} -c $(LIB_DIR)/extractInputOutputForSingleRI.cpp -o $(OBJ_DIR)/extractInputOutputForSingleRI.o

inputOutputGen.o:
	$(CC) ${CCFLAG} -c $(SRC_DIR)/inputOutputGen.cpp -o $(OBJ_DIR)/inputOutputGen.o

gen: extractInputOutputForSingleRI.o inputOutputGen.o
	$(CC) ${CCFLAG} -o $(BIN_DIR)/inputOutputGen $(OBJ_DIR)/extractInputOutputForSingleRI.o $(OBJ_DIR)/inputOutputGen.o

bench_gen:
	mkdir -p $(BENCH_BIN_DIR)
	echo "#define PROFILE" >  $(BENCH_DIR)/utility/rt_conf.h
	echo "#define CLS 32" >> $(BENCH_DIR)/utility/rt_conf.h
	echo "#define DS 8" >> $(BENCH_DIR)/utility/rt_conf.h
	$(foreach name, $(bench), $(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/$(name)_cls32_ds8 $(BENCH_DIR)/$(name).cpp ;)
	echo "#define PROFILE" >  $(BENCH_DIR)/utility/rt_conf.h
	echo "#define CLS 1" >> $(BENCH_DIR)/utility/rt_conf.h
	echo "#define DS 1" >> $(BENCH_DIR)/utility/rt_conf.h
	$(foreach name, $(bench), $(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/$(name)_elm $(BENCH_DIR)/$(name).cpp ;)
	echo "#define PROFILE_IBOUND" >  $(BENCH_DIR)/utility/rt_conf.h
	echo "#define CLS 32" >> $(BENCH_DIR)/utility/rt_conf.h
	echo "#define DS 8" >> $(BENCH_DIR)/utility/rt_conf.h
	$(foreach name, $(bench), $(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/$(name)_ibound $(BENCH_DIR)/$(name).cpp ;)

trace_gen:
	echo "#define TRACE" >  $(BENCH_DIR)/utility/rt_conf.h
	echo "#define CLS 32" >> $(BENCH_DIR)/utility/rt_conf.h
	echo "#define DS 8" >> $(BENCH_DIR)/utility/rt_conf.h	
	$(foreach name, $(bench), $(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/$(name)_cls32_ds8_trace $(BENCH_DIR)/$(name).cpp ;)
	
