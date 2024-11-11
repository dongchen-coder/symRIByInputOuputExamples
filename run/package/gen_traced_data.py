import os
import itertools

def gen_trace(bench, size, cache_config):
    cmd = "mkdir -p ../data/traced_data/" + cache_config + "/" + bench
    os.system(cmd)
    
    sizes_str = [str(x) for x in list(size)]
    sizes_str_space = " ".join(sizes_str)
    sizes_str = "_".join(sizes_str)

    print(bench, size)

    trace_file = "../data/traced_data/" + cache_config + "/" + bench + "/" + bench + "_" + cache_config + "_" + sizes_str + "_trace.txt"
    if (os.path.exists(trace_file)):
        return
    tracing_cmd = "../bench/bench_bin/" + bench +  "_" + cache_config + "_trace " + sizes_str_space
    cmd = tracing_cmd + " > " + trace_file
    os.system(cmd)
