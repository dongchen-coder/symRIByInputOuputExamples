import os


def init_ioe_paths(path, bench):
    os.system("mkdir -p " + path + "/" + bench)   
    os.system("rm -rf " + path + "/" + bench + "/src_only")
    os.system("rm -rf " + path + "/" + bench + "/src_enhanced")
    os.system("rm -rf " + path + "/" + bench + "/src_snk")
    os.system("rm -rf " + path + "/" + bench + "/ibound")
    os.system("mkdir -p " + path + "/" + bench + "/src_only")
    os.system("mkdir -p " + path + "/" + bench + "/src_enhanced")
    os.system("mkdir -p " + path + "/" + bench + "/src_snk")
    os.system("mkdir -p " + path + "/" + bench + "/ibound")
    return


def gen_ioe_from_raw_data(bench, n_paras, train_size, cacheconfig):
    
    train_size_str = ' '.join(map(str, train_size))
   
    for mode in ['-FORMATSRCITERPOS', '-FORMATSRCITERPOSSNK', '-FORMATSRCITERPOSSNKITERPOS', '-FORMATSRCSHAPE']:
        cmd = "../input-output_example_gen/bin/inputOutputGen -NAME " + bench + " -SIZES " + train_size_str + " -NUMOFLOOPBOUNDS " + str(n_paras)  + " " + mode + " -CACHECONFIG " + cacheconfig
        os.system(cmd)

    return

