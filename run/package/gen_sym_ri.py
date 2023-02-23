from multiprocessing import Pool
import logging
import threading
import shlex
import subprocess
import os
import random
from paths import *

# paths to exec and result files

data_path = "../data/input-output_examples/"


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

cmd_option = constantsForPredicate + constantsForTerm + intOpsForTerm + searchTimeForTermsInSeconds + searchTimeForPredsInSeconds

'''
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
'''

def gen_sym_ri(bench, parms, spec, df, ref_ids, iter_vecs, cache_config):
    if (spec == 'src_only' and isinstance(ref_ids, int)):
        for iter_vec in iter_vecs:
            src_id = str(ref_ids)
            src_iv_ = iter_vec.replace(' ', '_')
            file_name = bench + '_refsrc_' + src_id + '_isrc_' + src_iv_ + '.ri.' + cache_config
            ioe_file = ioe_path + bench + '/' + spec + '/' + file_name
            cmd = syn_bin + " -FILE " + ioe_file + cmd_option + " > " + sym_ri_path + bench + "/" + file_name + '.' + spec
            os.system(cmd)
    if ((spec == 'src_snk' or spec == 'src_snk_plus') and isinstance(ref_ids, tuple)):
        for iter_vec in iter_vecs:
            src_id = str(ref_ids[0])
            snk_id = str(ref_ids[1])
            src_iv_ = iter_vec.replace(' ', '_')
            file_name = bench + '_refsrc_' + src_id + '_refsnk_' + snk_id + '_isrc_' + src_iv_ + '.ri.' + cache_config
            ioe_file = ioe_path + bench + '/' + spec + '/' + file_name
            cmd = syn_bin + " -FILE " + ioe_file + cmd_option + " > " + sym_ri_path + bench + "/" + file_name + '.' + spec
            os.system(cmd)
    return

def get_sym_bound(bench, parms, df):
    src_ref_id = df['source reference ID'][0]
    num_of_nested_loops = len(df['iteration vector'][0].strip().split(' '))
    loop_name = ['loop ' + str(x) for x in range(num_of_nested_loops)]
    if num_of_nested_loops <= 1:
        df['loop 0'] = df['iteration vector']
    else:
        df[loop_name] = df['iteration vector'].str.split(' ', num_of_nested_loops - 1, expand=True)

    for i in range(num_of_nested_loops):
        df['loop ' + str(i)] = df['loop ' + str(i)].astype(int)

    for i in range(num_of_nested_loops):
        min_bound_file_name = bench + '_refsrc_' + str(src_ref_id) + '.imin' + str(i) + '.ibound'
        min_bound_file = ioe_data_path + bench + '/ibound/' + min_bound_file_name
        max_bound_file_name = bench + '_refsrc_' + str(src_ref_id) + '.imax' + str(i) + '.ibound'
        max_bound_file = ioe_data_path + bench + '/ibound/' + max_bound_file_name
        cmd = syn_bin + " -FILE " + min_bound_file + cmd_option + " > " + sym_ri_path + bench + "/" + min_bound_file_name
        os.system(cmd)
        cmd = syn_bin + " -FILE " + max_bound_file + cmd_option + " > " + sym_ri_path + bench + "/" + max_bound_file_name
        os.system(cmd)
    return