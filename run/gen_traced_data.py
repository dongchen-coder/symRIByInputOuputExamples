import os                                                                                                                                                                             

bench_n_paras = {"stencil" : 1, "cholesky" : 1, "durbin" : 1, "floyd_warshall" : 1, "gemver" : 1, "gesummv" : 1, "lu" : 1, "ludcmp" : 1, "mvt" : 1, "nussinov" : 1, "stencil" : 1, "trisolv" : 1, 'stencil_tiled' : 2, "heat_3d" : 2, "trangle" : 2, "adi" : 2, "atax" : 2, "bicg" : 2, "convolution_2d" : 2, "correlation" : 2, "covariance" : 2, "deriche" : 2, "gramschmidt" : 2, "heat_3d" : 2, "jacobi_1d" : 2, "jacobi_2d" : 2, "seidel_2d" : 2, "symm" : 2, "syr2d" : 2, "syrk" : 2, "trmm" : 2, "doitgen" : 3, "convolution_3d" : 3, "doitgen" : 3, "fdtd_2d" : 3, "gemm" : 3, "2mm" : 4, "3mm" : 5}

for cache_config in ['cls32_ds8']:
    cmd = "mkdir -p ../data/traced_data/" + cache_config
    os.system(cmd)
    for bench, n_paras in bench_n_paras.items():
        cmd = "rm -rf ../data/traced_data/" + cache_config + "/" + bench
        os.system(cmd)
        cmd = "mkdir -p ../data/traced_data/" + cache_config + "/" + bench
        os.system(cmd)
        for verify_size in [32]:
            sizes_str = [str(verify_size)] * n_paras
            sizes_str_space = " ".join(sizes_str)
            sizes_str = "_".join(sizes_str)
            cmd = "../input-output_example_gen/bin/bench_bin/" + bench +  "_" + cache_config + "_trace " + sizes_str_space + " > ../data/traced_data/" + cache_config + "/" + bench + "/" + bench + "_" + cache_config + "_" + sizes_str + "_trace.txt"
            os.system(cmd)
