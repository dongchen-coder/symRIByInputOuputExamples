from multiprocessing import Pool
import logging
import threading
import shlex
import subprocess
import os
import random

# paths to exec and result files
syn_bin = "../search-based_synthesizer/build/src/symRiSynthesizer"
data_path = "../data/input-output_examples/"
result_path = "../data/sym_ri/"

# clear all generated sym RI
def clearSymRI(bench):
    os.system("rm -rf " + result_path + bench)
    os.system("mkdir -p " + result_path + bench)

# process each input-output file
def processIOEFile(example):
    print(example)
    [folder, bench, f, syn_config] = example
    
    cmd_option = syn_config["constants_for_predicate"] + syn_config["constants_for_term"] + syn_config["int_ops_for_term"] + syn_config["search_time_for_terms_in_seconds"] + syn_config["search_time_for_preds_in_seconds"]

    if (f[0] == "src_snk_plus"):
        syn_config["rules_to_apply"] = " -RULESTOAPPLY SrcSnk"
    cmd_option += syn_config["rules_to_apply"]

    suffix = ''
    if (folder != "ibound"):
        suffix = "." + folder
   
    cmd = syn_bin + " -FILE " + data_path + bench + "/" + folder + "/" + f + cmd_option + " > " + result_path + bench + "/" + f + suffix
    print(cmd)
    os.system(cmd)    

def init_files_to_process(bench):
    files_to_process = []
    for folder in ["ibound", "src_only", "src_snk", "src_snk_plus"]:
        filesInFolder = os.listdir(data_path + bench + "/" + folder)
        filesCLS = list(filter(lambda x : "cls32_ds8" in x or "ibound" in x, filesInFolder))
        if (len(filesCLS) > 200 and folder != "ibound"):
            random.shuffle(filesCLS)
            filesCLS = filesCLS[0:200]
        files_to_process += [[folder, bench, f] for f in filesCLS]
    return files_to_process   

def gen_sym_ri(bench, syn_config, num_of_cpus):
    
    clearSymRI(bench)
    files = init_files_to_process(bench)
    
    p = Pool(num_of_cpus)
    examples = [f+[syn_config] for f in files]
    p.map(processIOEFile, examples)
    p.close()
    p.join()
