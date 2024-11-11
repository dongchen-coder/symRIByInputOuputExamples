import os
import itertools
import random


def init_sampled_raw_data_paths(path, bench):
    
    for target in ["elm", "cls32_ds8", "ibound"]:
        os.system("mkdir -p " + path + target)
        os.system("rm -rf " + path + target + "/" + bench)
        os.system("mkdir -p " + path + target + "/" + bench)

    return


def sample_raw_data(bench, paras, target, n_samples):

    src_idxs = set()
    for p in paras:
        p_str = map(str, p)
        p_underscore = '_'.join(p_str)
        file_name = "../data/raw_data/" + target + "/" + bench + "/" + bench + "_" + p_underscore + ".txt"
        if (os.path.exists(file_name)):
            f = open(file_name, 'r')
            for line in f:
                line_list = line.split(",")
                src_info = line_list[1]
                src_idxs.add(src_info)
            f.close()

    sampled_src_idxs = src_idxs
    if (n_samples < len(src_idxs)):
        print("the number of source indices in larger than the number of samples", len(src_idxs), "reduce to", n_samples)
        sampled_src_idxs = random.sample(src_idxs, n_samples)    

    for p in paras:
        p_str = map(str, p)
        p_underscore = '_'.join(p_str)
        read_file_name = "../data/raw_data/" + target + "/" + bench + "/" + bench + "_" + p_underscore + ".txt"
        if (os.path.exists(read_file_name)):
            rf = open(read_file_name, 'r')
            write_file_name = "../data/sampled_raw_data/" + target + "/" + bench + "/" + bench + "_" + p_underscore + ".txt"
            wf = open(write_file_name, 'w')
            for line in rf:
                line_list = line.split(",")
                src_info = line_list[1]
                if (src_info in sampled_src_idxs):
                    wf.write(line)
            rf.close()
            wf.close()

    return

