from readFile import *
from evaluate import *
from reconstructIterSpace import *
from scaleIter import *
from RTtoMRandPlot import *
import itertools

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
                #print idx, scaled_idx
                ri = evaluateSingleCode(scaled_idx, boundValueForPred, symbolicHistToUse[ref_src_id][idx])

                if (ri == None):
                    continue
                ri = int(ri)
                if (ri in histogram.keys()):
                    histogram[ri] += 1 * scaleSampleNumber(len(idx))
                else:
                    histogram[ri] = 1 * scaleSampleNumber(len(idx))
    
    if (method == "src_enhanced"):
        for ref_src_id in symbolicHistToUse.keys():
            trainIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], [32] * len(boundValueForPred))
            predIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], boundValueForPred)
            for ref_snk_id in symbolicHistToUse[ref_src_id].keys():
                for idx in symbolicHistToUse[ref_src_id][ref_snk_id].keys():
                    scaled_idx = scaleIter(idx, trainIBound, predIBound)
                    ri = evaluateSingleCode(scaled_idx, boundValueForPred, symbolicHistToUse[ref_src_id][ref_snk_id][idx])
                
                    if (ri == None):
                        continue
                    ri = int(ri)
                
                    if (ri in histogram.keys()):
                        histogram[ri] += 1 * scaleSampleNumber(len(idx))
                    else:
                        histogram[ri] = 1 * scaleSampleNumber(len(idx))
        
    if (method == "src_snk"):
        [symbolicHistSrcSnk, symbolicIsnk] = symbolicHistToUse
        for ref_src_id in symbolicHistSrcSnk.keys():
            trainIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], [32] * len(boundValueForPred))
            predIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], boundValueForPred)
            
            for ref_snk_id in symbolicHistSrcSnk[ref_src_id].keys():
                for idx in symbolicHistSrcSnk[ref_src_id][ref_snk_id].keys():
                    
                    prog = symbolicHistSrcSnk[ref_src_id][ref_snk_id][idx]
                    
                    #print prog
                    
                    scaled_idx = scaleIter(idx, trainIBound, predIBound)
                    
                    if ("isnk" in prog):
                        if (ref_snk_id not in symbolicIsnk[ref_src_id].keys() or idx not in symbolicIsnk[ref_src_id][ref_snk_id].keys()):
                            print "No key", idx
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
                    
                    if (ri == None):
                        continue
                    ri = int(ri)
                    
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
    print "Filtered", negCnt
    return filteredHistogram

def checkSingleBench(bench_name, num_of_sym_bound, value_assigned_for_prediction, cache_config):
    
    sym_ri_path = "../../data/sym_ri/all/"
    # read symbolic RI
    sym_ri_src_only        = read_sym_ri(sym_ri_path + bench_name + ".ri." + cache_config + ".src_only")
    sym_ri_src_enhanced    = read_sym_ri(sym_ri_path + bench_name + ".ri." + cache_config + ".src_enhanced")
    sym_ri_src_snk         = read_sym_ri(sym_ri_path + bench_name + ".ri." + cache_config + ".src_snk")
    sym_isnk               = read_sym_isnk(bench_name, cache_config + ".src_snk")
    sym_ibound_src_only    = readSymbolicIBounds(sym_ri_path + bench_name + ".ibound")
    
    #print len(sym_ri_src_only)
    #print len(sym_ri_src_enhanced)
    #print len(sym_ri_src_snk)
    #print len(sym_isnk)
    #print len(sym_ibound_src_only)
    
    # generate confs to predict
    #confs = value_assigned_for_prediction
    value_assigned_for_prediction_str = "_".join(map(str, value_assigned_for_prediction))
    
    predicted_mr_src_only = {}
    predicted_mr_src_enhanced = {}
    predicted_mr_src_snk ={}
    traced_mr = {}
    
    # predict for each conf
    print "start to predict the RI distribution for ", value_assigned_for_prediction
    
    predicted_histogram_src_only = evaluate(sym_ri_src_only, sym_ibound_src_only, value_assigned_for_prediction, "src_only")
    predicted_histogram_src_only = filterRIHisto(predicted_histogram_src_only)
    print "predicted_histogram_src_only", predicted_histogram_src_only
    
    predicted_histogram_src_enhanced = evaluate(sym_ri_src_enhanced, sym_ibound_src_only, value_assigned_for_prediction, "src_enhanced")
    predicted_histogram_src_enhanced = filterRIHisto(predicted_histogram_src_enhanced)
    print "predicted_histogram_src_enhanced", predicted_histogram_src_enhanced
                
    predicted_histogram_src_snk = evaluate([sym_ri_src_snk, sym_isnk], sym_ibound_src_only, value_assigned_for_prediction, "src_snk")
    predicted_histogram_src_snk = filterRIHisto(predicted_histogram_src_snk)
    print "predicted_histogram_src_snk", predicted_histogram_src_snk
    
    traced_histogram = readTraceFile(bench_name, value_assigned_for_prediction, cache_config)
    traced_histogram = filterRIHisto(traced_histogram)
    print "traced_histogram", traced_histogram
    
    plotHistoToCompare(predicted_histogram_src_only, predicted_histogram_src_enhanced, predicted_histogram_src_snk, traced_histogram, bench_name, cache_config, value_assigned_for_prediction_str)
        
    predicted_mr_src_only, predicted_mr_src_enhanced, predicted_mr_src_snk, traced_mr = plotMRToCompare(predicted_histogram_src_only, predicted_histogram_src_enhanced, predicted_histogram_src_snk, traced_histogram, bench_name, cache_config, value_assigned_for_prediction_str)
    
    return predicted_mr_src_only, predicted_mr_src_enhanced, predicted_mr_src_snk, traced_mr

if __name__ == "__main__":

    num_of_symbolic_bounds = {"cholesky" : 1, "durbin" : 1, "floyd_warshall" : 1, "gemver" : 1, "gesummv" : 1, "lu" : 1, "ludcmp" : 1, "mvt" : 1, "nussinov" : 1, "stencil" : 1, "trisolv" : 1, "trangle" : 2, "adi" : 2, "atax" : 2, "bicg" : 2, "convolution_2d" : 2, "correlation" : 2, "covariance" : 2, "deriche" : 2, "gramschmidt" : 2, "heat_3d" : 2, "jacobi_1d" : 2, "jacobi_2d" : 2, "seidel_2d" : 2, "symm" : 2, "syr2d" : 2, "syrk" : 2, "trmm" : 2, "convolution_3d" : 3, "doitgen" : 3, "fdtd_2d" : 3, "gemm" : 3, "2mm" : 4, "3mm" : 5, "stencil_tiled" : 2}

    all_predicted_mr_src_only = {}
    all_predicted_mr_src_enhanced = {}
    all_predicted_mr_src_snk = {}
    all_traced_mr = {}

    for bench_name in num_of_symbolic_bounds.keys():
        if (bench_name != "stencil"): #and bench_name != "stencil_tiled"):
            continue
        
        # assign 32 to all symbolic bounds
        value_assigned_for_prediction = [32] * num_of_symbolic_bounds[bench_name]
        
        predicted_mr_src_only, predicted_mr_src_enhanced, predicted_mr_src_snk, traced_mr = checkSingleBench(bench_name, num_of_symbolic_bounds[bench_name], value_assigned_for_prediction, "cls32_ds8")
        
        all_predicted_mr_src_only[bench_name] = predicted_mr_src_only
        all_predicted_mr_src_enhanced[bench_name] = predicted_mr_src_enhanced
        all_predicted_mr_src_snk[bench_name] = predicted_mr_src_snk
        all_traced_mr[bench_name] = traced_mr
    
    plotFigAll(all_predicted_mr_src_only, all_predicted_mr_src_enhanced, all_predicted_mr_src_snk, all_traced_mr)

    
