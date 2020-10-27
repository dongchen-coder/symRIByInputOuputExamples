import os

path_IBound = "./ris_Ibound/"
path_srcOnly = "./ris_refsrc_Isrc_Psrc/"
path_srcEnhanced = "./ris_refsrc_Isrc_Psrc_refsnk/"  
path_srcSnk = "./ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk/"

benches = ["2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm"]

for mode in ["ELM", "CLS32_DS8"]:
    for bench in benches:
        if (os.path.exists(path_IBound + bench)):
            files = os.listdir(path_IBound + bench)
            cnt = 0
            for f in files:
                if (mode in f):
                    cnt += 1
            print bench, mode, cnt
