import sys
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

num_of_cpus = 8
num_of_samples_for_bounds = 10**18
sample_rate_for_src_iteration = 0.1
max_sampled_iterations = 200
num_of_ri_examples_in_total = 200
cache_config = "cls32_ds8"

if __name__ == "__main__":
    
    all_bench_n_parms = {"stencil": 1, "stencil_tiled": 2}
    train_sizes = [8, 12, 16, 20, 32]
    verify_sizes = {"stencil": [64], "stencil_tiled": [64, 16]}

    for bench, n_parms in all_bench_n_parms.items():
        gen_trace(bench, verify_sizes[bench], cache_config)
        gen_input_output_examples([bench, n_parms, cache_config], train_sizes, num_of_samples_for_bounds, sample_rate_for_src_iteration, max_sampled_iterations)
        gen_sym_ri(bench, cache_config, syn_config, num_of_cpus, num_of_ri_examples_in_total)
        summerize_sym_ri(bench, cache_config)
