import os

def summerizeForBenchWithFormat(bench, inOutFormat):
    files = os.listdir("./" + bench)
    outputFile = open("./all/" + bench + inOutFormat, "w")
    
    for f in files:
        name = f
        if (inOutFormat not in name):
            continue
        
        f = open("./"+bench+"/"+f, 'r')
        for line in f:
            if ("(^0^)" in line):
                prog = line.replace("Searched Program (^0^) :", "Prog:")
                outputFile.write(name + " " + prog)
        f.close()
    outputFile.close()

def summerizeForBench(bench):
    print "Start to summerize " + bench
    if (not os.path.isdir("./" + bench)):
        return
    files = os.listdir("./" + bench)
    
    summerizeForBenchWithFormat(bench, ".RI.ELM.ris_refsrc_Isrc_Psrc")
    summerizeForBenchWithFormat(bench, ".RI.CLS32_DS8.ris_refsrc_Isrc_Psrc")
    summerizeForBenchWithFormat(bench, ".RI.ELM.ris_refsrc_Isrc_Psrc_refsnk")
    summerizeForBenchWithFormat(bench, ".RI.CLS32_DS8.ris_refsrc_Isrc_Psrc_refsnk")
    summerizeForBenchWithFormat(bench, ".RI.ELM.ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk")
    summerizeForBenchWithFormat(bench, ".RI.CLS32_DS8.ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk")
    IsnkCnt = 0
    exsitFlag = True
    while(exsitFlag):
        exsitFlag = False
        for f in files:
            if (".Isnk"+str(IsnkCnt) in f):
                exsitFlag = True
                break
        if (exsitFlag == False):
            break
        summerizeForBenchWithFormat(bench, ".Isnk"+str(IsnkCnt)+".ELM.ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk")
        summerizeForBenchWithFormat(bench, ".Isnk"+str(IsnkCnt)+".CLS32_DS8.ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk")
        IsnkCnt += 1

    return

benches = ["stencil", "2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm", "convolution_2d", "convolution_3d", "trangle"]

#benches = ["stencil"]

for bench in benches:
    summerizeForBench(bench)
