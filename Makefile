LIB_DIR=./lib
SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin

BENCH_DIR=./bench
BENCH_BIN_DIR=./bin/bench_bin

RIS_RAW_DIR=./inputoutput/raw_ris_per_size
INPUTOUTPUT_DIRS=./inputoutput/ris_per_iter_refsrc ./inputoutput/ris_per_iter_refsrcsnk ./inputoutput/IMinMax

RIS_MATCH_DIR=./verify/histoToMatch

bench=stencil 2mm 3mm adi atax bicg cholesky correlation covariance deriche doitgen durbin fdtd_2d floyd_warshall gemm gemver gesummv gramschmidt heat_3d jacobi_1d jacobi_2d lu ludcmp mvt nussinov seidel_2d symm syr2d syrk trisolv trmm convolution_2d convolution_3d trangle

bench_1para=stencil #cholesky durbin floyd_warshall gemver gesummv lu ludcmp mvt nussinov stencil trisolv
bench_2para=trangle adi atax bicg convolution_2d correlation covariance deriche gramschmidt heat_3d jacobi_1d jacobi_2d seidel_2d symm syr2d syrk trmm
bench_3para=convolution_3d doitgen fdtd_2d gemm  
bench_4para=2mm
bench_5para=3mm

train_size=4 8 16 32

verify_size=64 128 256

CC=g++

symRiSynthesiser.o:
	$(CC) -std=c++11 -O2 -c $(SRC_DIR)/symRiSynthesiser.cpp -o $(OBJ_DIR)/symRiSynthesiser.o

langDef.o:
	$(CC) -std=c++11 -O2 -c $(LIB_DIR)/langDef.cpp -o $(OBJ_DIR)/langDef.o

bottomUpSearch.o:
	$(CC) -std=c++11 -O2 -c $(LIB_DIR)/bottomUpSearch.cpp -o $(OBJ_DIR)/bottomUpSearch.o

unification.o:
	$(CC) -std=c++11 -O2 -c $(LIB_DIR)/unification.cpp -o $(OBJ_DIR)/unification.o

sampler.o:
	$(CC) -std=c++11 -O2 -c $(LIB_DIR)/sampler.cpp -o $(OBJ_DIR)/sampler.o

extractInputOutputForSingleRI.o:
	$(CC) -std=c++11 -O2 -c $(LIB_DIR)/extractInputOutputForSingleRI.cpp -o $(OBJ_DIR)/extractInputOutputForSingleRI.o

inputOutputGen.o:
	$(CC) -std=c++11 -O2 -c $(SRC_DIR)/inputOutputGen.cpp -o $(OBJ_DIR)/inputOutputGen.o

gen: extractInputOutputForSingleRI.o inputOutputGen.o symRiSynthesiser.o langDef.o bottomUpSearch.o unification.o sampler.o
	$(CC) -O2 -o $(BIN_DIR)/inputOutputGen $(OBJ_DIR)/extractInputOutputForSingleRI.o $(OBJ_DIR)/inputOutputGen.o
	$(CC) -pthread -O2 -o $(BIN_DIR)/symRiSymthesiser $(OBJ_DIR)/symRiSynthesiser.o $(OBJ_DIR)/langDef.o $(OBJ_DIR)/bottomUpSearch.o $(OBJ_DIR)/unification.o $(OBJ_DIR)/sampler.o

bench_gen:
	mkdir -p $(BENCH_BIN_DIR)
	$(foreach name, $(bench), $(CC) -O -o $(BENCH_BIN_DIR)/$(name) $(BENCH_DIR)/$(name).cpp ;)

ris_raw_gen:
	mkdir -p $(RIS_RAW_DIR)
	$(foreach name, $(bench), rm -r -f $(RIS_RAW_DIR)/$(name) ;)
	$(foreach name, $(bench), mkdir -p $(RIS_RAW_DIR)/$(name) ;)
	$(foreach size, $(train_size), \
		$(foreach name, $(bench_1para), $(BENCH_BIN_DIR)/$(name) $(size) > $(RIS_RAW_DIR)/$(name)/$(name)_$(size).txt ;) \
	)
	#$(foreach size1, $(train_size), \
	#	$(foreach size2, $(train_size), \
	#		$(foreach name, $(bench_2para), $(BENCH_BIN_DIR)/$(name) $(size1) $(size2) > $(RIS_RAW_DIR)/$(name)/$(name)_$(size1)_$(size2).txt ;) \
	#	) \
	#)
	#$(foreach size1, $(train_size), \
	#	$(foreach size2, $(train_size), \
	#		$(foreach size3, $(train_size), \
	#			$(foreach name, $(bench_3para), $(BENCH_BIN_DIR)/$(name) $(size1) $(size2) $(size3) > $(RIS_RAW_DIR)/$(name)/$(name)_$(size1)_$(size2)_$(size3).txt ;) \
	#		) \
	#	) \
	#)
	#$(foreach size1, $(train_size), \
	#	$(foreach size2, $(train_size), \
	#		$(foreach size3, $(train_size), \
	#			$(foreach size4, $(train_size), \
	#				$(foreach name, $(bench_4para), $(BENCH_BIN_DIR)/$(name) $(size1) $(size2) $(size3) $(size4) > $(RIS_RAW_DIR)/$(name)/$(name)_$(size1)_$(size2)_$(size3)_$(size4).txt ;) \
	#			) \
	#		) \
	#	) \
	#)
	#$(foreach size1, $(train_size), \
	#	$(foreach size2, $(train_size), \
	#		$(foreach size3, $(train_size), \
	#			$(foreach size4, $(train_size), \
	#				$(foreach size5, $(train_size), \
	#					$(foreach name, $(bench_5para), $(BENCH_BIN_DIR)/$(name) $(size1) $(size2) $(size3) $(size4) $(size5) > $(RIS_RAW_DIR)/$(name)/$(name)_$(size1)_$(size2)_$(size3)_$(size4)_$(size5).txt ;) \
	#				) \
	#			) \
	#		) \
	#	) \
	#)

inputoutput_gen:
	$(foreach name, $(bench), \
		$(foreach dir, $(INPUTOUTPUT_DIRS), rm -r -f $(dir)/$(name) ;) \
	)
	$(foreach name, $(bench), \
		$(foreach dir, $(INPUTOUTPUT_DIRS), mkdir -p $(dir)/$(name) ;) \
	)
	$(foreach name, $(bench_1para), $(BIN_DIR)/inputOutputGen -NAME $(name) -SIZES 4 8 16 32 -NUMOFLOOPBOUNDS 1 -SAMPLINGRATE 0.4 ;)
	#$(foreach name, $(bench_2para), $(BIN_DIR)/inputOutputGen -NAME $(name) -SIZES 4 8 16 32 -NUMOFLOOPBOUNDS 2 ;)
	#$(foreach name, $(bench_3para), $(BIN_DIR)/inputOutputGen -NAME $(name) -SIZES 4 8 16 32 -NUMOFLOOPBOUNDS 3 ;)
	#$(foreach name, $(bench_4para), $(BIN_DIR)/inputOutputGen -NAME $(name) -SIZES 4 8 16 32 -NUMOFLOOPBOUNDS 4 ;)
	#$(foreach name, $(bench_5para), $(BIN_DIR)/inputOutputGen -NAME $(name) -SIZES 4 8 16 32 -NUMOFLOOPBOUNDS 5 ;)

histogramToMatch_gen:
	$(foreach name, $(bench), rm -r $(RIS_MATCH_DIR)/$(name) ;)
	$(foreach name, $(bench), mkdir $(RIS_MATCH_DIR)/$(name) ;)
	$(foreach size, $(verify_size), \
        $(foreach name, $(bench_1para), $(BENCH_BIN_DIR)/$(name) $(size) > $(RIS_MATCH_DIR)/$(name)/$(name)_$(size).txt ;) \
    )
