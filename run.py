from multiprocessing import Pool
import logging
import threading
import shlex
import subprocess
import os
import random

def processFile(f):

    if (f[0] == "SrcOnly"):
        cmd = "./bin/symRiSymthesiser -FILE ./inputoutput/ris_refsrc_Isrc_Psrc/" + f[1] +  "/" + f[2] + " -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 20 -SEARCHTIMEFORPREDSINSECONDS 40 -RULESTOAPPLY SrcOnly > ./synResult/" + f[1] + "/" + f[2] + ".ris_refsrc_Isrc_Psrc"
        print cmd
        os.system(cmd)
    if (f[0] == "Ibound"):
        cmd = "./bin/symRiSymthesiser -FILE ./inputoutput/ris_Ibound/" + f[1] +  "/" + f[2] + " -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 20 -SEARCHTIMEFORPREDSINSECONDS 40 -RULESTOAPPLY SrcOnly > ./synResult/" + f[1] + "/" + f[2] + ".ris_Ibound"
        print cmd
        os.system(cmd)
    if (f[0] == "SrcEnhanced"):
        cmd = "./bin/symRiSymthesiser -FILE ./inputoutput/ris_refsrc_Isrc_Psrc_refsnk/" + f[1] +  "/" + f[2] + " -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 20 -SEARCHTIMEFORPREDSINSECONDS 40 -RULESTOAPPLY SrcEnhanced > ./synResult/" + f[1] + "/" + f[2] + ".ris_Ibound"
        print cmd
        os.system(cmd)
    if (f[0] == "SrcSnk"):
        cmd = "./bin/symRiSymthesiser -FILE ./inputoutput/ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk/" + f[1] +  "/" + f[2] + " -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 20 -SEARCHTIMEFORPREDSINSECONDS 40 -RULESTOAPPLY SrcSnk > ./synResult/" + f[1] + "/" + f[2] + ".ris_Ibound"
        print cmd
        os.system(cmd)
    return

if __name__ == '__main__':

    #benches = ["stencil", "2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm", "convolution_2d", "convolution_3d", "trangle"]
    benches = ["stencil"]

    '''
    for bench in benches:
        os.system("rm -r -f ./synResult/" + bench)
        os.system("mkdir -p ./synResult/" + bench)
    '''
    files = []
    '''
    for bench in benches:
        filesForBench = os.listdir("./inputoutput/ris_refsrc_Isrc_Psrc/" + bench)
        filesCLS = []
        for f in filesForBench:
            if ("CLS32_DS8" in f):
                filesCLS.append(f)
        if (len(filesCLS) > 200):
            random.shuffle(filesCLS)
            filesCLS = filesCLS[0:200]
        files += [["SrcOnly", bench, f, benches.index(bench)] for f in filesCLS]
    for bench in benches:
        filesForBench = os.listdir("./inputoutput/ris_Ibound/" + bench)
        files += [["Ibound", bench, f, benches.index(bench)] for f in filesForBench]
    '''
    for bench in benches:
        filesForBench = os.listdir("./inputoutput/ris_refsrc_Isrc_Psrc_refsnk/" + bench)
        filesCLS = []
        for f in filesForBench:
            if ("CLS32_DS8" in f):
                filesCLS.append(f)
        if (len(filesCLS) > 200):
            random.shuffle(filesCLS)
            filesCLS = filesCLS[0:200]
        files += [["SrcEnhanced", bench, f, benches.index(bench)] for f in filesCLS]

    for bench in benches:
        filesForBench = os.listdir("./inputoutput/ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk/" + bench)
        filesCLS = []
        for f in filesForBench:
            if ("CLS32_DS8" in f):
                filesCLS.append(f)
        if (len(filesCLS) > 200):
            random.shuffle(filesCLS)
            filesCLS = filesCLS[0:200]
        files += [["SrcSnk", bench, f, benches.index(bench)] for f in filesCLS]
    
    p = Pool(60)
    p.map(processFile, files)
    p.close()
    p.join()
    
