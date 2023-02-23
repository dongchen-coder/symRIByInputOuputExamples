import itertools
import random
import sys
sys.path.append('./package')
sys.path.append('./package/ioe_gen')
sys.path.append('./package/verifier')
sys.path.append("./package/profile_bench")
from paths import *
from gen_traced_data import *
from gen_raw_data import *
from gen_input_output_examples import *
from gen_sym_ri import *
from summarize_sym_ri import *

'''
from gen_sym_ri import *
from summarize_sym_ri import *
from verify import *
'''

def create_folders(benches, cache_config):
    cmds = []

    # folders for traces
    cmds.append("mkdir -p " + traced_data_path + cache_config)
    for bench in benches:
        cmds.append("mkdir -p " + traced_data_path + cache_config + "/" + bench)

    # folders for raw RI and loop bounds
    cmds.append("mkdir -p " + raw_data_path + cache_config)
    for bench in benches:
        cmds.append("mkdir -p " + raw_data_path + cache_config + "/" + bench)
        cmds.append("mkdir -p " + raw_data_path + "ibound" + "/" + bench)

    # folders for ioes
    cmds.append("mkdir -p " + ioe_data_path)
    for bench in benches:
        cmds.append("mkdir -p " + ioe_data_path + bench)
        for ioe_type in ["src_only", "src_snk", "src_snk_plus", "ibound"]:
            cmds.append("mkdir -p " + ioe_data_path + bench + "/" + ioe_type)

    for cmd in cmds:
         os.system(cmd)

def remove_folders(benches, cache_config):
    cmds = []
    cmds.append("rm -r " + traced_data_path + cache_config)
    cmds.append("rm -r " + raw_data_path + cache_config)
    cmds.append("rm -r " + ioe_data_path)
    for cmd in cmds:
        os.system(cmd)
    return

if __name__ ==  "__main__":

    all_bench_n_parms = {"stencil" : 1} # for testing
    #{"stencil" : 1, "stencil_tiled" : 2, "cholesky" : 1, "durbin" : 1, "floyd_warshall" : 1, "gemver" : 1, "gesummv" : 1, "lu" : 1, "ludcmp" : 1, "mvt" : 1, "nussinov" : 1, "stencil" : 1, "trisolv" : 1, 'stencil_tiled' : 2, "heat_3d" : 2, "trangle" : 2, "adi" : 2, "atax" : 2, "bicg" : 2, "convolution_2d" : 2, "correlation" : 2, "covariance" : 2, "deriche" : 2, "gramschmidt" : 2, "heat_3d" : 2, "jacobi_1d" : 2, "jacobi_2d" : 2, "seidel_2d" : 2, "symm" : 2, "syr2d" : 2, "syrk" : 2, "trmm" : 2, "doitgen" : 3, "convolution_3d" : 3, "doitgen" : 3, "fdtd_2d" : 3, "gemm" : 3, "2mm" : 4, "3mm" : 5}
    
    train_sizes = [8, 12, 16, 20]
    cache_config = "cls32_ds8"
    n_samples = 2

    test_size = 32

    remove_folders(all_bench_n_parms.keys(), cache_config)
    create_folders(all_bench_n_parms.keys(), cache_config)

    for bench in all_bench_n_parms.keys():
        n_paras = all_bench_n_parms[bench]
        parms_train = [v for v in itertools.product(train_sizes, repeat=n_paras)]

        # generate raw information
        for parms in parms_train:
            gen_trace(bench, parms, cache_config)
            gen_raw_data_for_ioe(bench, parms, cache_config, "csv")

        # generate input-output examples for ibound
        df_ibound = get_one_dataframe_for_all_params(bench, parms_train, 'ibound', "csv")
        gen_input_output_examples_for_ibound(bench, parms_train, df_ibound)
        get_sym_bound(bench, parms_train, df_ibound)


        # generate input-output examples
        df = get_one_dataframe_for_all_params(bench, parms_train, cache_config, "csv")
        iter_vecs = get_iter_vecs(bench, parms_train, df)

        # sample iteration vectors
        iter_vecs_sampled = {}
        for ref_ids in iter_vecs.keys():
            if len(iter_vecs[ref_ids]) > n_samples:
                vecs = iter_vecs[ref_ids]
                random.shuffle(vecs)
                iter_vecs_sampled[ref_ids] = vecs[0:n_samples]
            else:
                iter_vecs_sampled[ref_ids] = iter_vecs[ref_ids]

        # generate input-output examples
        for spec in ["src_only", "src_snk", "src_snk_plus"]:
            for ref_ids in iter_vecs_sampled.keys():
                gen_input_output_examples(bench, parms_train, spec, df, ref_ids, iter_vecs_sampled[ref_ids], cache_config)

        # synthesis input-output examples
        for spec in ["src_only", "src_snk", "src_snk_plus"]:
            for ref_ids in iter_vecs_sampled.keys():
                gen_sym_ri(bench, parms_train, spec, df, ref_ids, iter_vecs_sampled[ref_ids], cache_config)

        # summarize symbolic RIs
        symbolic_RIs = {}
        for spec in ["src_only", "src_snk", "src_snk_plus"]:
            symbolic_RIs[spec] = {};
            for ref_ids in iter_vecs_sampled.keys():
                symbolic_RIs[spec][ref_ids] = read_sym_ri(bench, parms_train, spec, df, ref_ids, iter_vecs_sampled[ref_ids], cache_config)


        # verify
        # TODO: test size, trace as a reference
        # TODO: bound prediciton
        for spec in ["src_only", "src_snk", "src_snk_plus"]:
            for ref_idx in iter_vecs_sampled.keys():
                for iter_vec in iter_vecs[ref_idx]:
                    # TODO: scale itervec
                    print spec, ref_idx, iter_vec

                '''
                trainIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], [32] * len(boundValueForPred))
                predIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], boundValueForPred)
                evaluateSingleCode(bench, test_size, )
                '''



    ''' 
    all_predicted_mr_src_only = {}
    all_predicted_mr_src_enhanced = {}
    all_predicted_mr_src_snk = {}
    all_traced_mr = {}

    for bench in all_bench_n_parms.keys():
        # assign 32 to all symbolic bounds
        # value_assigned_for_prediction = [32] * num_of_symbolic_bounds[bench_name]
        value_assigned_for_prediction = [32]

        predicted_mr_src_only, predicted_mr_src_enhanced, predicted_mr_src_snk, traced_mr = checkSingleBench(bench, all_bench_n_parms[bench], value_assigned_for_prediction, "cls32_ds8")
        
        all_predicted_mr_src_only[bench] = predicted_mr_src_only
        all_predicted_mr_src_enhanced[bench] = predicted_mr_src_enhanced
        all_predicted_mr_src_snk[bench] = predicted_mr_src_snk
        all_traced_mr[bench] = traced_mr
    
    #plotFigAll(all_predicted_mr_src_only, all_predicted_mr_src_enhanced, all_predicted_mr_src_snk, all_traced_mr, ["stencil", "stencil_tiled", "trangle", "convolution_2d", "convolution_3d"])
    #plotFigAll(all_predicted_mr_src_only, all_predicted_mr_src_enhanced, all_predicted_mr_src_snk, all_traced_mr, ["bit_reversal"])      
    '''