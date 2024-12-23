from readFile import *
from evaluate import *
from reconstructIterSpace import *
from scaleIter import *
from RTtoMRandPlot import *
import json

def scaleSampleNumber(loopDepth):
    return 5 ** loopDepth

def evaluate(symbolicHistToUse, symBoundsToUse, boundValueForPred, method):
    histogram = {}

    if (method == "src_only"):
        for ref_src_id in symbolicHistToUse.keys():
            trainIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], [32] * len(boundValueForPred))
            predIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], boundValueForPred)
            for idx in symbolicHistToUse[ref_src_id].keys():
                
                scaled_idx = scaleIter(idx, trainIBound, predIBound)
                #print(idx, scaled_idx)
                ri = evaluateSingleCode(scaled_idx, boundValueForPred, symbolicHistToUse[ref_src_id][idx])

                if ri is None:
                    continue
                try:
                    ri = int(float(ri))
                except ValueError as e:
                    raise ValueError(f"Cannot convert ri to int: {ri}") from e
                
                if (ri in histogram.keys()):
                    histogram[ri] += 1 * scaleSampleNumber(len(idx))
                else:
                    histogram[ri] = 1 * scaleSampleNumber(len(idx))
    
    if (method == "src_snk"):
        for ref_src_id in symbolicHistToUse.keys():
            trainIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], [32] * len(boundValueForPred))
            predIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], boundValueForPred)
            for ref_snk_id in symbolicHistToUse[ref_src_id].keys():
                for idx in symbolicHistToUse[ref_src_id][ref_snk_id].keys():
                    scaled_idx = scaleIter(idx, trainIBound, predIBound)
                    ri = evaluateSingleCode(scaled_idx, boundValueForPred, symbolicHistToUse[ref_src_id][ref_snk_id][idx])
                
                    if ri is None:
                        continue
                    try:
                        ri = int(float(ri))
                    except ValueError as e:
                        raise ValueError(f"Cannot convert ri to int: {ri}") from e
                
                    if (ri in histogram.keys()):
                        histogram[ri] += 1 * scaleSampleNumber(len(idx))
                    else:
                        histogram[ri] = 1 * scaleSampleNumber(len(idx))
        
    if (method == "src_snk_plus"):
        [symbolicHistSrcSnk, symbolicIsnk] = symbolicHistToUse
        for ref_src_id in symbolicHistSrcSnk.keys():
            trainIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], [32] * len(boundValueForPred))
            predIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], boundValueForPred)
            
            for ref_snk_id in symbolicHistSrcSnk[ref_src_id].keys():
                for idx in symbolicHistSrcSnk[ref_src_id][ref_snk_id].keys():
                    
                    prog = symbolicHistSrcSnk[ref_src_id][ref_snk_id][idx]
                    
                    #print(prog)
                    
                    scaled_idx = scaleIter(idx, trainIBound, predIBound)
                    
                    if ("isnk" in prog):
                        if (ref_snk_id not in symbolicIsnk[ref_src_id].keys() or idx not in symbolicIsnk[ref_src_id][ref_snk_id].keys()):
                            print("No key", idx)
                            continue
                        else:
                            Isnkv = symbolicIsnk[ref_src_id][ref_snk_id][idx]
                            Isnkv_value = []
                            for Isnk in Isnkv:
                                value = evaluateSingleCode(scaled_idx, boundValueForPred, Isnk)
                                Isnkv_value.append(value)
                            for Isnk_idx in range(len(Isnkv_value)):
                                if ("isnk" + str(Isnk_idx) in prog):
                                    prog = prog.replace("isnk" + str(Isnk_idx), Isnkv_value[Isnk_idx])
                    
                    if ("isnk" in prog):
                        continue
                    
                    ri = evaluateSingleCode(scaled_idx, boundValueForPred, prog)
                    
                    if ri is None:
                        continue
                    try:
                        ri = int(float(ri))
                    except ValueError as e:
                        raise ValueError(f"Cannot convert ri to int: {ri}") from e
                    
                    if (ri in histogram.keys()):
                        histogram[ri] += 1 * scaleSampleNumber(len(idx))
                    else:
                        histogram[ri] = 1 * scaleSampleNumber(len(idx))
    
    return histogram

def filterRIHisto(histogram):
    filteredHistogram = {}
    negCnt = 0
    for key in histogram.keys():
        if (key > 0):
            filteredHistogram[key] = histogram[key]
        if (key < 0):
            negCnt += 1
    print("Filtered", negCnt)
    return filteredHistogram

def checkSingleBench(bench_name, num_of_sym_bound, value_assigned_for_prediction, cache_config):
    
    sym_ri_path = "../../data/sym_ri/all/"
    # read symbolic RI
    sym_ri_src_only        = read_sym_ri(sym_ri_path + bench_name + ".ri." + cache_config + ".src_only")
    sym_ri_src_snk    = read_sym_ri(sym_ri_path + bench_name + ".ri." + cache_config + ".src_snk")
    sym_ri_src_snk_plus        = read_sym_ri(sym_ri_path + bench_name + ".ri." + cache_config + ".src_snk_plus")
    sym_isnk               = read_sym_isnk(bench_name, cache_config + ".src_snk")
    sym_ibound_src_only    = readSymbolicIBounds(sym_ri_path + bench_name + ".ibound")
    
    print("sym_ri_src_only", len(sym_ri_src_only))
    print("sym_ri_src_snk", len(sym_ri_src_snk))
    print("sym_ri_src_snk_plus", len(sym_ri_src_snk_plus))
    print("sym_isnk", len(sym_isnk))
    print("sym_ibound_src_only", len(sym_ibound_src_only))
    
    # generate confs to predict
    # confs = value_assigned_for_prediction
    value_assigned_for_prediction_str = "_".join(map(str, value_assigned_for_prediction))
    
    predicted_mr_src_only = {}
    predicted_mr_src_enhanced = {}
    predicted_mr_src_snk ={}
    traced_mr = {}
    
    # predict for each conf
    print("start to predict the RI distribution for ", value_assigned_for_prediction)
    
    predicted_histogram_src_only = evaluate(sym_ri_src_only, sym_ibound_src_only, value_assigned_for_prediction, "src_only")
    predicted_histogram_src_only = filterRIHisto(predicted_histogram_src_only)
    #print("predicted_histogram_src_only", predicted_histogram_src_only)
    
    predicted_histogram_src_snk = evaluate(sym_ri_src_snk, sym_ibound_src_only, value_assigned_for_prediction, "src_snk")
    predicted_histogram_src_snk = filterRIHisto(predicted_histogram_src_snk)
    #print("predicted_histogram_src_enhanced", predicted_histogram_src_enhanced)
                
    predicted_histogram_src_snk_plus = evaluate([sym_ri_src_snk_plus, sym_isnk], sym_ibound_src_only, value_assigned_for_prediction, "src_snk_plus")
    predicted_histogram_src_snk_plus = filterRIHisto(predicted_histogram_src_snk_plus)
    #print("predicted_histogram_src_snk", predicted_histogram_src_snk)
    
    traced_histogram = readTraceFile(bench_name, value_assigned_for_prediction, cache_config)
    traced_histogram = filterRIHisto(traced_histogram)
    #print("traced_histogram", traced_histogram)
    
    plotHistoToCompare(predicted_histogram_src_only, predicted_histogram_src_snk, predicted_histogram_src_snk_plus, traced_histogram, bench_name, cache_config, value_assigned_for_prediction_str)
    
    plotHistoAllBars(predicted_histogram_src_only, predicted_histogram_src_snk, predicted_histogram_src_snk_plus, traced_histogram, bench_name, cache_config, value_assigned_for_prediction_str)    

    predicted_mr_src_only, predicted_mr_src_snk, predicted_mr_src_snk_plus, traced_mr = plotMRToCompare(predicted_histogram_src_only, predicted_histogram_src_snk, predicted_histogram_src_snk_plus, traced_histogram, bench_name, cache_config, value_assigned_for_prediction_str)
    
    return predicted_mr_src_only, predicted_mr_src_snk, predicted_mr_src_snk_plus, traced_mr

def get_falcon_mr(benches):
    path = "../../../falcon-artifact/experiments/data/"
    base_file_name = "perf-polybench-M-"
    falcon_mr = {}
    for bench in benches:
        bench_mr = {}
        for c in [1, 2, 4, 8, 16, 32]:
            file_name = base_file_name +  str(c) + "-" + str(c) + ".json"
            with open(path + file_name) as f:
                data = json.load(f)
                if (bench not in data.keys()):
                    continue
                bench_mr[c] = data[bench]["lazystack-8"]['misses'] / data[bench]["lazystack-8"]['accesses']
        falcon_mr[bench] = bench_mr
    return falcon_mr

def check_stencil():
    stencil_bench_n_parms = {
        "stencil": 1, "stencil_tiled": 2
    }
    stencil_small = {"stencil": [64], "stencil_tiled": [64, 16]}

    all_predicted_mr_src_only = {}
    all_predicted_mr_src_enhanced = {}
    all_predicted_mr_src_snk = {}
    all_traced_mr = {}
    for bench_name in stencil_bench_n_parms.keys():
        value_assigned_for_prediction = stencil_small[bench_name]

        predicted_mr_src_only, predicted_mr_src_snk, predicted_mr_src_snk_plus, traced_mr = checkSingleBench(bench_name, stencil_bench_n_parms[bench_name], value_assigned_for_prediction, "cls32_ds8")
        
        all_predicted_mr_src_only[bench_name] = predicted_mr_src_only
        all_predicted_mr_src_snk[bench_name] = predicted_mr_src_snk
        all_predicted_mr_src_enhanced[bench_name] = predicted_mr_src_snk_plus
        all_traced_mr[bench_name] = traced_mr

if __name__ == "__main__":

    check_stencil()
    exit()

    poly_bench_n_parms = {
        "2mm": 4, "3mm": 5, "adi": 2, "atax": 2, "bicg": 2, "cholesky": 1, "correlation": 2,
        "covariance": 2, "deriche": 2, "doitgen": 3, "durbin": 1, "fdtd-2d": 3, "floyd-warshall": 1,
        "gemm": 3, "gemver": 1, "gesummv": 1, "gramschmidt": 2, "heat-3d": 2, "jacobi-1d": 2,
        "jacobi-2d": 2, "lu": 1, "ludcmp": 1, "mvt": 1, "nussinov": 1, "seidel-2d": 2, "symm": 2,
        "syr2d": 2, "syrk": 2, "trisolv": 1, "trmm": 2
    }
    poly_bench_small = {}
    for bench_name in poly_bench_n_parms.keys():
        poly_bench_small[bench_name] = [40+i*10  for i in range(poly_bench_n_parms[bench_name])]
    poly_bench_medium = {}
    for bench_name in poly_bench_n_parms.keys():
        poly_bench_medium[bench_name] = [180+i*10  for i in range(poly_bench_n_parms[bench_name])]
    poly_bench_large = {}
    for bench_name in poly_bench_n_parms.keys():
        poly_bench_large[bench_name] = [800+i*100  for i in range(poly_bench_n_parms[bench_name])]

    all_predicted_mr_src_only = {}
    all_predicted_mr_src_enhanced = {}
    all_predicted_mr_src_snk = {}
    all_traced_mr = {}

    for bench_name in poly_bench_n_parms.keys():
        #value_assigned_for_prediction = poly_bench_small[bench_name]
        value_assigned_for_prediction = poly_bench_medium[bench_name]

        predicted_mr_src_only, predicted_mr_src_enhanced, predicted_mr_src_snk, traced_mr = checkSingleBench(bench_name, poly_bench_n_parms[bench_name], value_assigned_for_prediction, "cls32_ds8")
        
        all_predicted_mr_src_only[bench_name] = predicted_mr_src_only
        all_predicted_mr_src_enhanced[bench_name] = predicted_mr_src_enhanced
        all_predicted_mr_src_snk[bench_name] = predicted_mr_src_snk
        all_traced_mr[bench_name] = traced_mr
    
    
    # read falcon mr
    all_predicted_mr_falcon = get_falcon_mr(poly_bench_n_parms.keys())
    print(all_predicted_mr_falcon)

    plotFigAll(all_predicted_mr_src_only, all_predicted_mr_src_enhanced, all_predicted_mr_src_snk, all_traced_mr, all_predicted_mr_falcon, [])
    
    
