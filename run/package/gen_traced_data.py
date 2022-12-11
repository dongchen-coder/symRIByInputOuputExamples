import os
import itertools

def gen_trace(bench_n_paras, train_sizes, cache_config):
    [bench, n_paras] = bench_n_paras

    cmd = "mkdir -p ../data/traced_data/" + cache_config
    os.system(cmd)
    cmd = "rm -rf ../data/traced_data/" + cache_config + "/" + bench
    os.system(cmd)
    cmd = "mkdir -p ../data/traced_data/" + cache_config + "/" + bench
    os.system(cmd)
    
    for train_size in itertools.combinations(train_sizes, n_paras):
        sizes_str = [str(x) for x in list(train_size)]
        sizes_str_space = " ".join(sizes_str)
        sizes_str = "_".join(sizes_str)
        cmd = "../bench/bench_bin/" + bench +  "_" + cache_config + "_trace " + sizes_str_space + " > ../data/traced_data/" + cache_config + "/" + bench + "/" + bench + "_" + cache_config + "_" + sizes_str + "_trace.txt"
        os.system(cmd)
