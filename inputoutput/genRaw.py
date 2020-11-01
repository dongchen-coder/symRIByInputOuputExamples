import os

train_sizes = [4, 8, 12, 16, 20, 24]

BENCH_BIN_DIR = "../bin/bench_bin"
RIS_ELM_RAW_DIR = "./raw_ris_per_size_ELM"
RIS_CLS_RAW_DIR = "./raw_ris_per_size_CLS32_DS8"

bench_1para= ["stencil", "cholesky", "durbin", "floyd_warshall", "gemver", "gesummv", "lu", "ludcmp", "mvt", "nussinov", "stencil", "trisolv"]
bench_2para= ["heat_3d", "trangle adi", "atax bicg", "convolution_2d", "correlation", "covariance", "deriche", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "seidel_2d", "symm", "syr2d", "syrk", "trmm"]
bench_3para= ["doitgen", "convolution_3d", "doitgen", "fdtd_2d", "gemm"]  
bench_4para= ["2mm"]
bench_5para= ["3mm"]

for bench in bench_1para:
    for size1 in train_sizes:
        cmd = BENCH_BIN_DIR + "/" + bench + "_ELM " + str(size1) + " > " + RIS_ELM_RAW_DIR + "/" + bench + "/" + bench + "_" + str(size1) + ".txt"
        os.system(cmd)
        cmd = BENCH_BIN_DIR + "/" + bench + "_CLS32_DS8 " + str(size1) + " > " + RIS_CLS_RAW_DIR + "/" + bench + "/" + bench + "_" + str(size1) + ".txt"
        os.system(cmd)

for bench in bench_1para:
    for size1 in train_sizes:
        for size2 in train_sizes:
            cmd = BENCH_BIN_DIR + "/" + bench + "_ELM " + str(size1) + " " + str(size2) " > " + RIS_ELM_RAW_DIR + "/" + bench + "/" + bench + "_" + str(size1) + "_" + str(size2) + ".txt"
            os.system(cmd)
            cmd = BENCH_BIN_DIR + "/" + bench + "_CLS32_DS8 " + str(size1) + " " + str(size2) " > " + RIS_CLS_RAW_DIR + "/" + bench + "/" + bench + "_" + str(size1) + "_" + str(size2) + ".txt"
            os.system(cmd)


