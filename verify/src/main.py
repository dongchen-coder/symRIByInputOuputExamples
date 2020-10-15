from readFile import *
from evaluate import *
from reconstructIterSpace import *
from scaleIter import *
from RTtoMRandPlot import *
import itertools

def evaluate(symbolicHistToUse, symBoundsToUse, boundValueForPred, method):
    histogram = {}

    if (method == "src"):
        for ref_src_id in symbolicHistToUse.keys():
            trainIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], [32] * len(boundValueForPred))
            predIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], boundValueForPred)
            for idx in symbolicHistToUse[ref_src_id].keys():
                scaled_idx = scaleIter(idx, trainIBound, predIBound)
                ri = evaluateSingleCode(scaled_idx, boundValueForPred, symbolicHistToUse[ref_src_id][idx])

                if (ri == None):
                    continue
                ri = int(ri)

                if (ri in histogram.keys()):
                    histogram[ri] += 1
                else:
                    histogram[ri] = 1
    
    if (method == "srcEnhance"):
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
                        histogram[ri] += 1
                    else:
                        histogram[ri] = 1
        
    if (method == "srcsnk"):
        [symbolicHistSrcSnk, symbolicIsnk] = symbolicHistToUse
        for ref_src_id in symbolicHistSrcSnk.keys():
            trainIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], [32] * len(boundValueForPred))
            predIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], boundValueForPred)
            for ref_snk_id in symbolicHistSrcSnk[ref_src_id].keys():
                for idx in symbolicHistSrcSnk[ref_src_id][ref_snk_id].keys():
                    prog = symbolicHistSrcSnk[ref_src_id][ref_snk_id][idx]
                    
                    scaled_idx = scaleIter(idx, trainIBound, predIBound)
                    
                    if ("Isnk" in prog):
                        if (idx not in symbolicIsnk[ref_src_id][ref_snk_id].keys()):
                            print "No key", idx
                            continue
                        else:
                            Isnkv = symbolicIsnk[ref_src_id][ref_snk_id][idx]
                            Isnkv_value = []
                            for Isnk in Isnkv:
                                value = evaluateSingleCode(scaled_idx, boundValueForPred, Isnk)
                                Isnkv_value.append(value)
                            for Isnk_idx in range(len(Isnkv_value)):
                                if ("Isnk" + str(Isnk_idx) in prog):
                                    prog = prog.replace("Isnk" + str(Isnk_idx), Isnkv_value[Isnk_idx])
                            
                    ri = evaluateSingleCode(scaled_idx, boundValueForPred, prog)
                    
                    if (ri == None):
                        continue
                    ri = int(ri)
                    
                    if (ri in histogram.keys()):
                        histogram[ri] += 1
                    else:
                        histogram[ri] = 1
    
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

def checkSingleBench(benchName, numOfSymBounds, symBoundValueForPred, cacheConfig):
    
    # read symbolic RI
    symbolicHistSrc        = readSymbolicHist(benchName, ".RI." + cacheConfig + ".ris_refsrc_Isrc_Psrc")
    symbolicHistSrcEnhance = readSymbolicHist(benchName, ".RI." + cacheConfig + ".ris_refsrc_Isrc_Psrc_refsnk")
    symbolicHistSrcSnk     = readSymbolicHist(benchName, ".RI." + cacheConfig + ".ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk")
    #print symbolicHistSrc
    #print symbolicHistSrcEnhance
    #print symbolicHistSrcSnk
    
    # need to read Isnk
    symbolicIsnk = readSymbolicIsnk(benchName, cacheConfig + ".ris_refsrc_Isrc_Psrc_refsnk_Isnk_Psnk")
    # print symbolicIsnk
    
    #read symbolic Ibound
    symbolicIboundSrc      = readSymbolicIBounds(benchName, "src", "." + cacheConfig + ".ris_Ibound")
    symbolicIboundSrcSnk   = readSymbolicIBounds(benchName, "srcsnk", "." + cacheConfig + ".ris_Ibound")
    #print symbolicHistSrcSnk
    #print symbolicIboundSrcSnk
    
    # generate confs to predict
    confs = []
    #confs = list(itertools.permutations(symBoundValueForPred))
    confs = [p for p in itertools.product(symBoundValueForPred, repeat=numOfSymBounds)]
    confs_str = []
    for conf in confs:
        tmp = ""
        for c in conf:
            tmp += "_" + str(c)
        confs_str.append(tmp)
    
    # predict for each conf
    for conf in confs_str:
        print "start to predict the RI distribution for ", conf

        boundValueForPredStr = conf.split("_")
        boundValueForPred = []
        for boundValue in boundValueForPredStr:
            if (boundValue != ""):
                boundValueForPred.append(int(boundValue))
        
        histogram_src_predicted = evaluate(symbolicHistSrc, symbolicIboundSrc, boundValueForPred, "src")
        histogram_src_predicted = filterRIHisto(histogram_src_predicted)
        print "histogram_src_predicted", histogram_src_predicted
        
        histogram_srcEnhance_predicted = evaluate(symbolicHistSrcEnhance, symbolicIboundSrc, boundValueForPred, "srcEnhance")
        histogram_srcEnhance_predicted = filterRIHisto(histogram_srcEnhance_predicted)
        print "histogram_srcEnhance_predicted", histogram_srcEnhance_predicted
                
        histogram_srcsnk_predicted = evaluate([symbolicHistSrcSnk, symbolicIsnk], symbolicIboundSrc, boundValueForPred, "srcsnk")
        histogram_srcsnk_predicted = filterRIHisto(histogram_srcsnk_predicted)
        print "histogram_srcsnk_predicted", histogram_srcsnk_predicted
        
        histogram_trace = readTraceFile(benchName, boundValueForPred, cacheConfig)
        histogram_trace = filterRIHisto(histogram_trace)
        print "histogram_trace", histogram_trace
        
        plotHistoToCompare(histogram_src_predicted, histogram_srcEnhance_predicted, histogram_srcsnk_predicted, histogram_trace, benchName, cacheConfig, conf)
        
        plotMRToCompare(histogram_src_predicted, histogram_srcEnhance_predicted, histogram_srcsnk_predicted, histogram_trace, benchName, cacheConfig, conf)

    return


if __name__ == "__main__":

    numOfSymBounds = {"cholesky" : 1, "durbin" : 1, "floyd_warshall" : 1, "gemver" : 1, "gesummv" : 1, "lu" : 1, "ludcmp" : 1, "mvt" : 1, "nussinov" : 1, "stencil" : 1, "trisolv" : 1, "trangle" : 2, "adi" : 2, "atax" : 2, "bicg" : 2, "convolution_2d" : 2, "correlation" : 2, "covariance" : 2, "deriche" : 2, "gramschmidt" : 2, "heat_3d" : 2, "jacobi_1d" : 2, "jacobi_2d" : 2, "seidel_2d" : 2, "symm" : 2, "syr2d" : 2, "syrk" : 2, "trmm" : 2, "convolution_3d" : 3, "doitgen" : 3, "fdtd_2d" : 3, "gemm" : 3, "2mm" : 4, "3mm" : 5}

    symBoundValueForPred = [32, 64, 128]  
   
    for benchName in numOfSymBounds.keys():
        if (benchName == "stencil"):
            checkSingleBench(benchName, numOfSymBounds[benchName], symBoundValueForPred, "ELM")
            checkSingleBench(benchName, numOfSymBounds[benchName], symBoundValueForPred, "CLS32_DS8")
