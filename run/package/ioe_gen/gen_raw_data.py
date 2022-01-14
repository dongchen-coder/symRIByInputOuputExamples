import os
import itertools

def init_raw_data_paths(path, bench):
    
    for target in ["elm", "cls32_ds8", "ibound"]:
        os.system("mkdir -p " + path + target)
        os.system("rm -rf " + path + target + "/" + bench)
        os.system("mkdir -p " + path + target + "/" + bench)

    return

def gen_raw_data(bench, n_paras, train_sizes, target, file_format):
    print bench
    paras = [p for p in itertools.product(train_sizes, repeat = n_paras)]
    for p in paras:
        p_str = map(str, p)
        p_space = ' '.join(p_str)
        p_underscore = '_'.join(p_str)
        
        exe_surfix = " "
        if (file_format == "csv"):
            exe_surfix = "_csv "

        cmd = "../bench/bench_bin/" + bench + "_" + target + exe_surfix + " " + p_space +  " > " + "./data/raw_data/" + target + "/" + bench + "/" + bench + "_" + p_underscore + "." + file_format
        os.system(cmd)
        
        cmd = "../bench/bench_bin/" + bench + "_ibound" + exe_surfix + p_space +  " > " + "./data/raw_data/ibound/" + bench + "/" + bench + "_" + p_underscore + "." + file_format
        os.system(cmd)
    
    return


