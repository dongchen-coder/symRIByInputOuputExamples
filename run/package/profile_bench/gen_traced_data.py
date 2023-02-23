import os
from paths import *

def gen_trace(bench, parms, cache_config):
    parms_str_space = get_parms_str_space(parms)
    parms_str_underline = get_parms_str_underline(parms)
    cmd = bench_bin_path + bench + "_" + cache_config + "_trace " + parms_str_space + " > ../data/traced_data/" + cache_config + "/" + bench + "/" + bench + "_" + cache_config + "_" + parms_str_underline + "_trace.txt"
    os.system(cmd)