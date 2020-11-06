from multiprocessing import Pool
import logging
import threading
import shlex
import subprocess
import os

def processFile(f):
    name = f[2].replace(".txt","")
    if (f[0] == "IMinMax"):
        #os.system("./bin/symRiSymthesiser -FILE ./inputoutput/" + f[0] + "/" + f[1] +  "/" + f[2] + " -CONSTANTSPRED 1 2 -INTOPSTERM VAR NUM PLUS TIMES MINUS -MODE PerSrcIter -SEARCHTIMEFORTERMSINSECONDS 40 -SEARCHTIMEFORPREDSINSECONDS 80 > ./synResult/" + f[1] + "/" + name + "_IBound_result.txt")
        output = ""
        cmd = "./bin/symRiSymthesiser -FILE ./inputoutput/" + f[0] + "/" + f[1] +  "/" + f[2] + " -CONSTANTSPRED 1 2 -INTOPSTERM VAR NUM PLUS TIMES MINUS -MODE PerSrcIter -SEARCHTIMEFORTERMSINSECONDS 40 -SEARCHTIMEFORPREDSINSECON    DS 80"
        process = subprocess.Popen([cmd], stdout = subprocess.PIPE, shell=True)
        output = [f[1] + "/" + name, process.stdout.read()]
    if (f[0] == "ris_per_iter_refsrc"):
        print "Start", f[3]
        cmd = "./bin/symRiSymthesiser -FILE ./inputoutput/" + f[0] + "/" + f[1] +  "/" + f[2] + " -CONSTANTSPRED 1 2 -INTOPSTERM VAR NUM PLUS TIMES MINUS -MODE PerSrcIter -SEARCHTIMEFORTERMSINSECONDS 40 -SEARCHTIMEFORPREDSINSECONDS 80"
        #print cmd
        os.system(cmd)
        print "End", f[3]
        
        '''
        output = ""
        cmd = "./bin/symRiSymthesiser -FILE ./inputoutput/" + f[0] + "/" + f[1] +  "/" + f[2] + " -CONSTANTSPRED 1 2 -INTOPSTERM VAR NUM PLUS TIMES MINUS -MODE PerSrcIter -SEARCHTIMEFORTERMSINSECONDS 40 -SEARCHTIMEFORPREDSINSECONDS 80"
        process = subprocess.Popen([cmd], stdout = subprocess.PIPE, shell=True)
        output = [f[1] + "/" + name, process.stdout.read()]
        '''
    return

if __name__ == '__main__':

    #benches = ["stencil", "2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm", "convolution_2d", "convolution_3d", "trangle"]
    benches = ["stencil"]

    for bench in benches:
        os.system("rm -r -f ./synResult/" + bench)
        os.system("mkdir -p ./synResult/" + bench)

    files = []
    
    for bench in benches:
        filesForBench = os.listdir("./inputoutput/ris_per_iter_refsrc/" + bench)
        files += [["ris_per_iter_refsrc", bench, f, benches.index(bench)] for f in filesForBench]
    '''
    for bench in benches:
        filesForBench = os.listdir("./inputoutput/IMinMax/" + bench)
        for f in filesForBench:
            if ("snk" not in f):
                files.append(["IMinMax",bench, f])
    '''
    p = Pool(60)
    p.map(processFile, files)
    p.close()
    p.join()
