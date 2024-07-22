import sys
sys.path.append('./package')
sys.path.append('./package/ioe_gen')
from gen_input_output_examples import *
from gen_sym_ri import *
from gen_traced_data import *
from summarize_sym_ri import *

if __name__ ==  "__main__":
    all_bench_n_parms = {"stencil" : 1, "stencil_tiled" : 2, "cholesky" : 1, "durbin" : 1, "floyd_warshall" : 1, "gemver" : 1, "gesummv" : 1, "lu" : 1, "ludcmp" : 1, "mvt" : 1, "nussinov" : 1, "stencil" : 1, "trisolv" : 1, 'stencil_tiled' : 2, "heat_3d" : 2, "trangle" : 2, "adi" : 2, "atax" : 2, "bicg" : 2, "convolution_2d" : 2, "correlation" : 2, "covariance" : 2, "deriche" : 2, "gramschmidt" : 2, "heat_3d" : 2, "jacobi_1d" : 2, "jacobi_2d" : 2, "seidel_2d" : 2, "symm" : 2, "syr2d" : 2, "syrk" : 2, "trmm" : 2, "doitgen" : 3, "convolution_3d" : 3, "doitgen" : 3, "fdtd_2d" : 3, "gemm" : 3, "2mm" : 4, "3mm" : 5}   
    #all_bench_n_parms = {"stencil" : 1}
    train_sizes = [8, 12, 16, 20]
    
    for bench in all_bench_n_parms.keys():
        #gen_trace([bench, all_bench_n_parms[bench]], train_sizes, "cls32_ds8")
        gen_input_output_examples([bench, all_bench_n_parms[bench]], train_sizes)
        #gen_sym_ri(bench)
        #summerize_sym_ri(bench, "cls32_ds8")
