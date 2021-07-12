import sys
import os
sys.path.insert(1, './package/ioe_gen')
from gen_raw_data import *
from gen_ioe_from_raw_data import *
from sample_raw_data import *

if __name__ ==  "__main__":
    train_sizes = [4, 6, 8, 12, 20]
    
    bench_n_paras = {"correlation" : 2}
    #bench_n_paras = {"stencil" : 1, "stencil_tiled" : 2, "cholesky" : 1, "durbin" : 1, "floyd_warshall" : 1, "gemver" : 1, "gesummv" : 1, "lu" : 1, "ludcmp" : 1, "mvt" : 1, "nussinov" : 1, "stencil" : 1, "trisolv" : 1, 'stencil_tiled' : 2, "heat_3d" : 2, "trangle" : 2, "adi" : 2, "atax" : 2, "bicg" : 2, "convolution_2d" : 2, "correlation" : 2, "covariance" : 2, "deriche" : 2, "gramschmidt" : 2, "heat_3d" : 2, "jacobi_1d" : 2, "jacobi_2d" : 2, "seidel_2d" : 2, "symm" : 2, "syr2d" : 2, "syrk" : 2, "trmm" : 2, "doitgen" : 3, "convolution_3d" : 3, "doitgen" : 3, "fdtd_2d" : 3, "gemm" : 3, "2mm" : 4, "3mm" : 5}

    # gen input-output examples for all benchmarks
    for bench, n_paras in bench_n_paras.items():
        # init path to raw data
        init_raw_data_paths("./data/raw_data/", bench)
        # gen raw data
        gen_raw_data(bench, n_paras, train_sizes, "cls32_ds8")

        # init path to sampled raw data
        init_sampled_raw_data_paths("./data/sampled_raw_data/", bench)
        # sample raw data
        sample_raw_data(bench, n_paras, train_sizes, "cls32_ds8", 500)

        # init path to input-output examples
        init_ioe_paths("./data/input-output_examples/", bench)
        # gen input-output examples for all benchmarks
        gen_ioe_from_raw_data(bench, n_paras, train_sizes, "cls32_ds8")

