import os
import itertools

def init_raw_data_paths(path, bench):
    
    for target in ["elm", "cls32_ds8", "ibound"]:
        os.system("mkdir -p " + path + target)
        os.system("rm -rf " + path + target + "/" + bench)
        os.system("mkdir -p " + path + target + "/" + bench)

    return

def gen_raw_data(bench, n_paras, train_sizes, target):
    print bench
    paras = [p for p in itertools.product(train_sizes, repeat = n_paras)]
    for p in paras:
        p_str = map(str, p)
        p_space = ' '.join(p_str)
        p_underscore = '_'.join(p_str)
        cmd = "../input-output_example_gen/bin/bench_bin/" + bench + "_" + target + " " + p_space +  " > " + "./data/generated_raw_data/" + target + "/" + bench + "/" + bench + "_" + p_underscore + ".txt"
        #print cmd
        os.system(cmd)
        cmd = "../input-output_example_gen/bin/bench_bin/" + bench + "_ibound " + p_space +  " > " + "./data/generated_raw_data/ibound/" + bench + "/" + bench + "_" + p_underscore + ".txt"        
        #print cmd
        os.system(cmd)
    return


