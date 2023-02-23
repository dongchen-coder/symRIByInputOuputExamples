import os
import itertools
import random

def sample_raw_data(bench, parms_train, cache_config, n_samples):
    src_idxs = set()
    print parms_train
    for p in parms_train:
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
        sampled_src_idxs = random.sample(src_idxs, n_samples)

    for p in parms_train:
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


'''
def sample_raw_data(bench, n_paras, train_sizes, target, n_samples):

    paras = [p for p in itertools.product(train_sizes, repeat = n_paras)]
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
'''
