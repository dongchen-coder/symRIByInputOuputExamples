POLY_BENCH_DIR=./poly_bench
FFT_BENCH_DIR=./fft_bench
BENCH_BIN_DIR=./bench_bin


bench=stencil stencil_tiled 2mm 3mm adi atax bicg cholesky correlation covariance deriche doitgen durbin fdtd_2d floyd_warshall gemm gemver gesummv gramschmidt heat_3d jacobi_1d jacobi_2d lu ludcmp mvt nussinov seidel_2d symm syr2d syrk trisolv trmm convolution_2d convolution_3d trangle

CC=g++
CCFLAG= -std=c++11 -O2 -pipe #-save-temps=obj

bench_gen:
	mkdir -p $(BENCH_BIN_DIR)
	echo "#define PROFILE_CSV" >  ./utility/rt_conf.h
	echo "#define CLS 32"      >> ./utility/rt_conf.h
	echo "#define DS 8"        >> ./utility/rt_conf.h
	$(foreach name, $(bench), $(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/$(name)_cls32_ds8_csv $(POLY_BENCH_DIR)/$(name).cpp ;)
	$(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/bit_reversal_cls32_ds8_csv $(FFT_BENCH_DIR)/bit_reversal.cpp
	echo "#define PROFILE_CSV" >  ./utility/rt_conf.h
	echo "#define CLS 1"       >> ./utility/rt_conf.h
	echo "#define DS 1"        >> ./utility/rt_conf.h
	$(foreach name, $(bench), $(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/$(name)_elm_csv $(POLY_BENCH_DIR)/$(name).cpp ;)
	$(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/bit_reversal_elm_csv $(FFT_BENCH_DIR)/bit_reversal.cpp 
	echo "#define PROFILE_IBOUND_CSV" >  ./utility/rt_conf.h
	echo "#define CLS 32"             >> ./utility/rt_conf.h
	echo "#define DS 8"               >> ./utility/rt_conf.h
	$(foreach name, $(bench), $(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/$(name)_ibound_csv $(POLY_BENCH_DIR)/$(name).cpp ;)
	$(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/bit_reversal_ibound_csv $(FFT_BENCH_DIR)/bit_reversal.cpp 

trace_gen:
	echo "#define TRACE"  >  ./utility/rt_conf.h
	echo "#define CLS 32" >> ./utility/rt_conf.h
	echo "#define DS 8"   >> ./utility/rt_conf.h	
	$(foreach name, $(bench), $(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/$(name)_cls32_ds8_trace $(POLY_BENCH_DIR)/$(name).cpp ;)
	$(CC) -std=c++11 -O -o $(BENCH_BIN_DIR)/bit_reversal_cls32_ds8_trace $(FFT_BENCH_DIR)/bit_reversal.cpp 
