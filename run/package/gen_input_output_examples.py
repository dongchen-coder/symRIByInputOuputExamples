import sys
import os
from gen_raw_data import *
from gen_ioe_from_raw_data import *
from sample_raw_data import *

# gen input-output examples for [bench, number of parameters] with train sizes
def gen_input_output_examples(bench_parms, train_sizes, num_of_samples_for_bounds, sample_rate_for_src_iteration, max_sampled_iterations):

    [bench, n_paras, cache_config] = bench_parms
    paras = [p for p in itertools.product(train_sizes, repeat = n_paras)]
    if (len(paras) > num_of_samples_for_bounds):
        paras = random.sample(paras, num_of_samples_for_bounds)
    
    # init path to raw data
    print(bench, "Init raw data paths")
    init_raw_data_paths("../data/raw_data/", bench)

    # gen raw data
    print(bench, "Gen raw data, num of paras", len(paras))
    gen_raw_data(bench, paras, cache_config, "csv")        

    # init path to sampled raw data
    # print("Init sampled raw data paths *",)
    # init_sampled_raw_data_paths("../data/sampled_raw_data/", bench)

    # sample raw data
    # print("Sample raw data *",)
    # sample_raw_data(bench, paras, cache_config, num_of_samples_for_examples)

    # init path to input-output examples
    print("Init input-output examples paths *",)
    init_ioe_paths("../data/input-output_examples/", bench)
    # gen input-output examples for all benchmarks
    print("Gen input-output examples *",)
    gen_ioe_from_raw_csv_data(bench, cache_config, sample_rate_for_src_iteration, max_sampled_iterations)

    return

    
