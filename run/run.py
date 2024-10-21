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

num_of_cpus = 64
num_of_samples = 500

if __name__ == "__main__":
    '''
    all_bench_n_parms = {
        "stencil": 1, "stencil_tiled": 2, "cholesky": 1, "durbin": 1, "floyd_warshall": 1,
        "gemver": 1, "gesummv": 1, "lu": 1, "ludcmp": 1, "mvt": 1, "nussinov": 1,
        "trisolv": 1, "heat_3d": 2, "triangle": 2, "adi": 2, "atax": 2, "bicg": 2,
        "convolution_2d": 2, "correlation": 2, "covariance": 2, "deriche": 2,
        "gramschmidt": 2, "jacobi_1d": 2, "jacobi_2d": 2, "seidel_2d": 2, "symm": 2,
        "syr2d": 2, "syrk": 2, "trmm": 2, "doitgen": 3, "convolution_3d": 3,
        "fdtd_2d": 3, "gemm": 3, "2mm": 4, "3mm": 5
    }
    '''
    poly_bench_n_parms = {
        "2mm": 4, "3mm": 5, "adi": 2, "atax": 2, "bicg": 2, "cholesky": 1, "correlation": 2,
        "covariance": 2, "deriche": 2, "doitgen": 3, "durbin": 1, "fdtd-2d": 3, "floyd-warshall": 1,
        "gemm": 3, "gemver": 1, "gesummv": 1, "gramschmidt": 2, "heat-3d": 2, "jacobi-1d": 2,
        "jacobi-2d": 2, "lu": 1, "ludcmp": 1, "mvt": 1, "nussinov": 1, "seidel-2d": 2, "symm": 2,
        "syr2d": 2, "syrk": 2, "trisolv": 1, "trmm": 2
    }
    
    all_bench_n_parms = poly_bench_n_parms
    train_sizes = [8, 12, 16, 20, 32]
    verify_sizes = [32, 64]

    for bench, n_parms in all_bench_n_parms.items():
        gen_trace([bench, n_parms], verify_sizes, "cls32_ds8")
        gen_input_output_examples([bench, n_parms], train_sizes, num_of_samples)
        gen_sym_ri(bench, syn_config, num_of_cpus)
        summerize_sym_ri(bench, "cls32_ds8")
