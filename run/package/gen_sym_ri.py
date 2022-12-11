from multiprocessing import Pool
import logging
import threading
import shlex
import subprocess
import os
import random

# paths to exec and result files
syn_bin = "../search-based_synthesizer/bin/symRiSymthesiser"
data_path = "../data/input-output_examples/"
result_path = "../data/sym_ri/"

# benches to process
benches = ["stencil", "2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm", "convolution_2d", "convolution_3d", "trangle"]
#benches = ["bit_reversal"]

# synthesizer configuration
constantsForPredicate = " -CONSTANTSPRED 1 2"
constantsForTerm = " -CONSTANTSTERM 0 1 2 3 4 5 6"
intOpsForTerm = " -INTOPSTERM VAR NUM PLUS TIMES MINUS"
searchTimeForTermsInSeconds = " -SEARCHTIMEFORTERMSINSECONDS 20"
searchTimeForPredsInSeconds = " -SEARCHTIMEFORPREDSINSECONDS 40"
rulesToApply = " -RULESTOAPPLY SrcOnly"

# clear all generated sym RI
def clearSymRI(bench):
    os.system("rm -rf " + result_path + bench)
    os.system("mkdir -p " + result_path + bench)

# process each input-output file
def processIOEFile(example):
    [folder, bench, f] = example
    cmd_option = constantsForPredicate + constantsForTerm + intOpsForTerm + searchTimeForTermsInSeconds + searchTimeForPredsInSeconds
        
    global rulesToApply
    if (f[0] == "src_snk_plus"):
        rulesToApply = " -RULESTOAPPLY SrcSnk"
    cmd_option += rulesToApply

    suffix = ''
    if (folder != "ibound"):
        suffix = "." + folder
   
    cmd = syn_bin + " -FILE " + data_path + bench + "/" + folder + "/" + f + cmd_option + " > " + result_path + bench + "/" + f + suffix
    print cmd
    os.system(cmd)    

def init_files_to_process(bench):
    files_to_process = []
    for folder in ["ibound", "src_only", "src_snk", "src_snk_plus"]:
        filesInFolder = os.listdir(data_path + bench + "/" + folder)
        filesCLS = filter(lambda x : "cls32_ds8" in x or "ibound" in x, filesInFolder)
        if (len(filesCLS) > 200 and folder != "ibound"):
            random.shuffle(filesCLS)
            filesCLS = filesCLS[0:200]
        files_to_process += [[folder, bench, f] for f in filesCLS]
    return files_to_process   

def gen_sym_ri(bench):
    clearSymRI(bench)
    files = init_files_to_process(bench)
    
    p = Pool(4)
    p.map(processIOEFile, files)
    p.close()
    p.join()
