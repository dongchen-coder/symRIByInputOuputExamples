import os
import itertools
from random import shuffle

numOfSymBounds = {"cholesky" : 1, "durbin" : 1, "floyd_warshall" : 1, "gemver" : 1, "gesummv" : 1, "lu" : 1, "ludcmp" : 1, "mvt" : 1, "nussinov" : 1, "stencil" : 1, "trisolv" : 1, "trangle" : 2, "adi" : 2, "atax" : 2, "bicg" : 2, "convolution_2d" : 2, "correlation" : 2, "covariance" : 2, "deriche" : 2, "gramschmidt" : 2, "heat_3d" : 2, "jacobi_1d" : 2, "jacobi_2d" : 2, "seidel_2d" : 2, "symm" : 2, "syr2d" : 2, "syrk" : 2, "trmm" : 2, "convolution_3d" : 3, "doitgen" : 3, "fdtd_2d" : 3, "gemm" : 3, "2mm" : 4, "3mm" : 5}

symBoundValueTrain = [4, 8, 16, 32]

samplingRate = 0.2

# refSrc -> refSnk -> srcIdx
# srcSnkIdx = {}

srcIdx = {}

for mode in ["raw_ris_per_size_ELM", "raw_ris_per_size_CLS32_DS8"]:
    benches = os.listdir(mode)
    for bench in benches:
        if (bench != "stencil"):
            continue
        if (bench in numOfSymBounds.keys()):
            confs = [p for p in itertools.product(symBoundValueTrain, repeat=numOfSymBounds[bench])]
            idxSrc = []
            for conf in confs:
                confStr = ""
                for size in conf:
                    confStr += "_" + str(size)
                fileName = "./" + mode + "/" + bench + "/" + bench + confStr + ".txt"
                if (os.path.exists(fileName)):
                    lines = open(fileName, "r")
                    for line in lines:
                        line = line.replace("\n", "")
                        lineTmp = line.split(",")
                        srcInfo = lineTmp[1].split(" ")
                        snkInfo = lineTmp[2].split(" ")
                        refSrc = srcInfo[0]
                        refSnk = snkInfo[0]
                        idxSrc = ""
                        for idx in srcInfo[1 : ]:
                            idxSrc += " " + str(idx)
                        #print refSrc, refSnk, idxSrc
                        '''
                        if (refSrc not in srcSnkIdx.keys()):
                            srcSnkIdx[refSrc] = {}
                        if (refSnk not in srcSnkIdx[refSrc].keys()):
                            srcSnkIdx[refSrc][refSnk] = []
                        if (idxSrc not in srcSnkIdx[refSrc][refSnk]):
                            srcSnkIdx[refSrc][refSnk].append(idxSrc)
                        '''
                        if (refSrc not in srcIdx.keys()):
                            srcIdx[refSrc] = []
                        if (idxSrc not in srcIdx[refSrc]):
                            srcIdx[refSrc].append(idxSrc)
                    lines.close()
            numOfLoops = len(idxSrc.split(" ")) - 1
            rate = 1
            for i in range(numOfLoops):
                rate *= samplingRate
            
            reservedLines = []
            for refSrc in srcIdx.keys():
                #print len(srcIdx[refSrc]), rate
                sampleNum = int(len(srcIdx[refSrc]) * rate)
                shuffle(srcIdx[refSrc])
                for x in srcIdx[refSrc][0 : sampleNum]:
                    reservedLines.append(refSrc + x)
            #print reservedLines
        
            for conf in confs:
                confStr = ""
                for size in conf:
                    confStr += "_" + str(size)
                iFileName = "./" + mode + "/" + bench + "/" + bench + confStr + ".txt"
                oFileName = "./" + mode + "_sampled/" + bench + "/" + bench + confStr + ".srcOnlySample.txt"
                if (os.path.exists(iFileName)):
                     iLines = open(iFileName, "r")
                     oFile = open(oFileName, 'w')
                     for line in iLines:
                        srcInfo = line.split(",")[1]
                        if (srcInfo in reservedLines):
                            oFile.write(line)
                     iLines.close()
                     oFile.close()
                
    

