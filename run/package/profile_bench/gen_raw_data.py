import os
import itertools

bench_bin_path = "../bench/bench_bin/"
raw_data_path = "../data/raw_data/"

def gen_raw_data_for_ioe(bench, parms, cache_config, file_format):
    parms_str = map(str, parms)
    parms_space = " ".join(parms_str)
    parms_underscore = "_".join(parms_str);

    exe_surfix = "_" + file_format
    
    cmd = bench_bin_path + bench + "_" + cache_config + exe_surfix + " " + parms_space +  " > " + raw_data_path + cache_config + "/" + bench + "/" + bench + "_" + parms_underscore + "." + file_format    
    print cmd
    os.system(cmd)
    
    cmd = bench_bin_path + bench + "_ibound" + exe_surfix + " " + parms_space +  " > " + raw_data_path + "ibound/" + bench + "/" + bench + "_" + parms_underscore + "." + file_format
    print cmd
    os.system(cmd)
    return
