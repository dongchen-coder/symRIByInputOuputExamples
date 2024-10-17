import os
import itertools

def gen_trace(bench_n_paras, train_sizes, cache_config):
    [bench, n_paras] = bench_n_paras

    cmd = "mkdir -p ../data/traced_data/" + cache_config + "/" + bench
    os.system(cmd)
    
    for train_size in itertools.combinations(train_sizes, n_paras):
        sizes_str = [str(x) for x in list(train_size)]
        sizes_str_space = " ".join(sizes_str)
        sizes_str = "_".join(sizes_str)

        trace_file = "../data/traced_data/" + cache_config + "/" + bench + "/" + bench + "_" + cache_config + "_" + sizes_str + "_trace.txt"
        if (os.path.exists(trace_file)):
            continue
        tracing_cmd = "../bench/bench_bin/" + bench +  "_" + cache_config + "_trace " + sizes_str_space
        cmd = tracing_cmd + " > " + trace_file
        os.system(cmd)
