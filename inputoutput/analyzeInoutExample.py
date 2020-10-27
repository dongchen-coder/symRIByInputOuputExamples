import os

path_IBound = "./ris_Ibound/"
path_srcOnly = "./ris_refsrc_Isrc_Psrc/"
path_srcEnhanced = "./ris_refsrc_Isrc_Psrc_refsnk/"  
path_srcSnk = "./ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk/"

benches = ["2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm"]

for mode in ["ELM", "CLS32_DS8"]:
    print mode, "************************************"
    print "IBound----------------"
    for bench in benches:
        if (os.path.exists(path_IBound + bench)):
            files = os.listdir(path_IBound + bench)
            cnt = 0
            for f in files:
                if (mode in f):
                    cnt += 1
            print bench, cnt,
    print ""
    
    print "Isrc----------------"
    for bench in benches:
        if (os.path.exists(path_srcOnly + bench)):
            files = os.listdir(path_srcOnly + bench)
            cnt = 0
            for f in files:
                if (mode in f):
                    cnt += 1
            print bench, cnt,
    print ""
   
    print "IsrcEnhance-----------"
    for bench in benches:
        if (os.path.exists(path_srcEnhanced + bench)):
            files = os.listdir(path_srcEnhanced + bench)
            cnt = 0
            for f in files:
                if (mode in f):
                    cnt += 1
            print bench, cnt,
    print ""

    print "IsrcSnk--------------"
    for bench in benches:
        if (os.path.exists(path_srcSnk + bench)):
            files = os.listdir(path_srcSnk + bench)
            cntRI = 0
            cntSnk = 0
            for f in files:
                if (mode in f and "RI" in f):
                    cntRI += 1
                if (mode in f and "Isnk" in f):
                    cntSnk += 1
            print bench, cntRI, cntSnk,
    print ""

    print "************************************"
   
