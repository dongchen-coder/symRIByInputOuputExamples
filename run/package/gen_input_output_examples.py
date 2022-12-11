import sys
import os
from gen_raw_data import *
from gen_ioe_from_raw_data import *
from sample_raw_data import *

# gen input-output examples for [bench, number of parameters] with train sizes
def gen_input_output_examples(bench_parms, train_sizes):
    
    print bench_parms
    [bench, n_paras] = bench_parms
        
    # init path to raw data
    init_raw_data_paths("../data/raw_data/", bench)
    # gen raw data
    gen_raw_data(bench, n_paras, train_sizes, "cls32_ds8", "csv")        

    # init path to sampled raw data
    init_sampled_raw_data_paths("../data/sampled_raw_data/", bench)
    # sample raw data
    sample_raw_data(bench, n_paras, train_sizes, "cls32_ds8", 500)

    # init path to input-output examples
    init_ioe_paths("../data/input-output_examples/", bench)
    # gen input-output examples for all benchmarks
    gen_ioe_from_raw_csv_data(bench, n_paras, train_sizes, "cls32_ds8")
