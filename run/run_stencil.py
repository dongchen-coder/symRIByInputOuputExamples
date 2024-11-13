import sys
import os
import time
sys.path.append('./package')
sys.path.append('./package/ioe_gen')
from gen_input_output_examples import gen_input_output_examples
from gen_sym_ri import gen_sym_ri
from gen_traced_data import gen_trace
from summarize_sym_ri import summerize_sym_ri

syn_config = {
    "constants_for_predicate" : " -CONSTANTSPRED 1 2",
    "constants_for_term" : " -CONSTANTSTERM 0 1 2 3 4 5 6 7",
    "int_ops_for_term" : " -INTOPSTERM VAR NUM PLUS TIMES MINUS DIV",
    "search_time_for_terms_in_seconds" : " -SEARCHTIMEFORTERMSINSECONDS 240",
    "search_time_for_preds_in_seconds" : " -SEARCHTIMEFORPREDSINSECONDS 240",
    "rules_to_apply" : " -RULESTOAPPLY SrcOnly"
}

num_of_cpus = 10
num_of_samples_for_bounds = 10**18
sample_rate_for_src_iteration = 0.1
max_sampled_iterations = 200
num_of_ri_examples_in_total = 200
cache_config = "cls32_ds8"


def run_single_config(bench, n_parms, verify_sizes):
    start_time = time.time()
    gen_trace(bench, verify_sizes[bench], cache_config)
    end_time = time.time()
    print(f"Time gen_trace took {end_time - start_time} seconds")
    
    start_time = time.time()
    gen_input_output_examples([bench, n_parms, cache_config], train_sizes, num_of_samples_for_bounds, sample_rate_for_src_iteration, max_sampled_iterations)
    end_time = time.time()
    print(f"gen_input_output_examples took {end_time - start_time} seconds")

    start_time = time.time()
    gen_sym_ri(bench, cache_config, syn_config, num_of_cpus, num_of_ri_examples_in_total)
    end_time = time.time()
    print(f"gen_sym_ri took {end_time - start_time} seconds")

    start_time = time.time()
    summerize_sym_ri(bench, cache_config)
    end_time = time.time()
    print(f"Fourth function took {end_time - start_time} seconds")


if __name__ == "__main__":
    
    all_bench_n_parms = {"stencil": 1}
    train_sizes = [8, 12, 16, 20, 32]
    verify_sizes = {"stencil": [64]}

    max_ris = [50, 100, 200, 500]
    timeouts = [40, 80, 120, 240]

    bench = "stencil"
    result_folder = "../data/" + bench + "_diff_configs_res"
    os.system("mkdir -p " + result_folder)
    for max_ri in max_ris:
        for timeout in timeouts:
            syn_config["search_time_for_terms_in_seconds"] = " -SEARCHTIMEFORTERMSINSECONDS " + str(timeout)
            syn_config["search_time_for_preds_in_seconds"] = " -SEARCHTIMEFORPREDSINSECONDS " + str(timeout)
            num_of_ri_examples_in_total = max_ri
            print("============================================" ,bench, max_ri, timeout)
            run_single_config(bench, all_bench_n_parms[bench], verify_sizes)
            os.system("mkdir -p " + result_folder + "/" + str(max_ri) + "_" + str(timeout))
            os.system("cp ../data/sym_ri/all/" + bench + ".*" + " " + result_folder + "/" + str(max_ri) + "_" + str(timeout) + "/")
