import os

def summerizeForBenchWithFormat(bench, inOutFormat):
    files = os.listdir("./data/sym_ri/" + bench)
    outputFile = open("./data/sym_ri/all/" + bench + inOutFormat, "w")
    
    for f in files:
        name = f
        #if (inOutFormat not in name):
        #    continue
        if (not name.endswith(inOutFormat)):
            continue
        
        f = open("./data/sym_ri/"+bench+"/"+f, 'r')
        for line in f:
            if ("(^0^)" in line):
                prog = line.replace("Searched Program (^0^) :", "Prog:")
                outputFile.write(name + " " + prog)
        f.close()
    outputFile.close()

def summerizeForBench(bench, cache_config):
    print "Start to summerize " + bench, cache_config
    if (not os.path.isdir("./data/sym_ri/" + bench)):
        return
    files = os.listdir("./data/sym_ri/" + bench)
    
    summerizeForBenchWithFormat(bench, ".ri."+cache_config+".src_only")
    summerizeForBenchWithFormat(bench, ".ri."+cache_config+".src_enhanced")
    summerizeForBenchWithFormat(bench, ".ri."+cache_config+".src_snk")

    isnk_id = 0
    while(True):
        exsitFlag = False
        for f in files:
            if (".isnk"+str(isnk_id) in f):
                exsitFlag = True
                break
        if (exsitFlag == False):
            break
        summerizeForBenchWithFormat(bench, ".isnk"+str(isnk_id)+"."+cache_config+".src_snk")
        isnk_id += 1
    
    summerizeForBenchWithFormat(bench, ".ibound")

    return

if __name__ == "__main__":

    os.system("rm -rf ./data/sym_ri/all")
    os.system("mkdir -p ./data/sym_ri/all")

    benches = ["stencil", "stencil_tiled", "2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm", "convolution_2d", "convolution_3d", "trangle"]

    #benches = ["stencil"]

    for bench in benches:
        summerizeForBench(bench, "elm")
        summerizeForBench(bench, "cls32_ds8")
