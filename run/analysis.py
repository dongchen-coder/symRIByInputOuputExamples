import os

ioe_path = "./data/input-output_examples/"
sym_ri_path = "./data/sym_ri/"

benches = ["2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm"]


for cache_config in ["elm", "clS32_ds8"]:
    for mode in ["src_only", "src_enhanced", "src_snk"]:
        print cache_config, mode, "************************************"
        for bench in benches:
            ios_files = []
            sym_ri_files = []
            if (os.path.exists(ioe_path + bench + '/' + mode)):
                ios_files = os.listdir(ioe_path + bench + '/' + mode)
            if (os.path.exists(sym_ri_path + bench)):
                sym_ri_files = os.listdir(sym_ri_path + bench)
            #ios_files = [x[0:x.index('.')] for x in ios_files]        
            sym_ri_files = [x[0:-len(mode)] for x in sym_ri_files]
            print sym_ri_files


