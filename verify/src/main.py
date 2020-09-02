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
            
            #print symBoundsToUse[ref_src_id]

            #idxs = reconstructIterSpace(symBoundsToUse[ref_src_id], boundValueForPred)
            #print symbolicHistToUse[ref_src_id].keys()
    
            trainIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], [32] * len(boundValueForPred))
            predIBound = getRangeForEachDimension(symBoundsToUse[ref_src_id], boundValueForPred)            

            #print trainIBound
            #print predIBound

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
        
    if (method == "srcsnk"):
        return
    return histogram

def checkSingleBench(benchName, path, numOfSymBounds, symBoundValueForPred):
    
    print benchName

    # read symbolic RI
    symbolicHistSrc = readSymbolicHistSrc(path, benchName)
    symbolicHistSrcsnk = readSymbolicHistSrcsnk(path, benchName)
    #print "srcHist", symbolicHistSrc
    #print "srcsnkHist", symbolicHistSrcsnk

    # read I bounds
    symbolicIBoundsSrc = readSymbolicIBoundsSrc(path, benchName)
    symbolicIBoundsSrcsnk = readSymbolicIBoundsSrcsnk(path, benchName)
    #print "srcIBound", symbolicIBoundsSrc
    #print "srcsnkIBound", symbolicIBoundsSrcsnk

    
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
        #print boundValueForPred
        
        histogram_src_predicted = evaluate(symbolicHistSrc, symbolicIBoundsSrc, boundValueForPred, "src")
        if (0 in histogram_src_predicted.keys()):
            del histogram_src_predicted[0]
        #print "histogram_src_predicted", histogram_src_predicted
        
        
        histogram_srcsnk_predicted = {}
        '''
        histogram_srcsnk_predicted = evaluate(symbolicHistSrcsnk, symbolicIBoundsSrcsnk, boundValueForPred, "srcsnk")
        if (0 in histogram_srcsnk_predicted.keys()):
            del histogram_srcsnk_predicted[0]
        print "histogram_srcsnk_predicted", histogram_srcsnk_predicted
        '''
        
        histogram_trace = readTraceFile(benchName, boundValueForPred)
        if (0 in histogram_trace.keys()):
            del histogram_trace[0]
        #print "histogram_trace", histogram_trace
        
        plotHistoToCompare(histogram_src_predicted, histogram_srcsnk_predicted, histogram_trace, benchName, conf)
        
        mr_src_predicted = RItoMR(histogram_src_predicted)
        mr_srcsnk_predicted = RItoMR(histogram_srcsnk_predicted)
        mr_trace = RItoMR(histogram_trace)
        plotMRToCompare(mr_src_predicted, mr_srcsnk_predicted, mr_trace, benchName, conf)

    return


if __name__ == "__main__":

    path = "../../synResult/all/"

    numOfSymBounds = {"cholesky" : 1, "durbin" : 1, "floyd_warshall" : 1, "gemver" : 1, "gesummv" : 1, "lu" : 1, "ludcmp" : 1, "mvt" : 1, "nussinov" : 1, "stencil" : 1, "trisolv" : 1, "trangle" : 2, "adi" : 2, "atax" : 2, "bicg" : 2, "convolution_2d" : 2, "correlation" : 2, "covariance" : 2, "deriche" : 2, "gramschmidt" : 2, "heat_3d" : 2, "jacobi_1d" : 2, "jacobi_2d" : 2, "seidel_2d" : 2, "symm" : 2, "syr2d" : 2, "syrk" : 2, "trmm" : 2, "convolution_3d" : 3, "doitgen" : 3, "fdtd_2d" : 3, "gemm" : 3, "2mm" : 4, "3mm" : 5}

    symBoundValueForPred = [32, 64, 128]  

    benchNames = ["gesummv", "correlation", "seidel_2d", "bicg", "jacobi_1d", "ludcmp", "covariance", "symm", "heat_3d", "atax", "trangle", "syrk", "mvt"] 
   
    for benchName in numOfSymBounds.keys():
        if (benchName not in benchNames):
            checkSingleBench(benchName, path, numOfSymBounds[benchName], symBoundValueForPred)
