import os
import itertools
import random


def init_sampled_raw_data_paths(path, bench):
    
    for target in ["elm", "cls32_ds8", "ibound"]:
        os.system("mkdir -p " + path + target)
        os.system("rm -rf " + path + target + "/" + bench)
        os.system("mkdir -p " + path + target + "/" + bench)

    return


def sample_raw_data(bench, n_paras, train_sizes, target, n_samples):

    paras = [p for p in itertools.product(train_sizes, repeat = n_paras)]
    src_idxs = set()
    for p in paras:
        p_str = map(str, p)
        p_underscore = '_'.join(p_str)
        file_name = "./data/raw_data/" + target + "/" + bench + "/" + bench + "_" + p_underscore + ".txt"
        if (os.path.exists(file_name)):
            f = open(file_name, 'r')
            for line in f:
                line_list = line.split(",")
                src_info = line_list[1]
                src_idxs.add(src_info)
            f.close()
    
    sampled_src_idxs = src_idxs
    if (n_samples < len(src_idxs)):
        sampled_src_idxs = random.sample(src_idxs, n_samples)    

    for p in paras:
        p_str = map(str, p)
        p_underscore = '_'.join(p_str)
        read_file_name = "./data/raw_data/" + target + "/" + bench + "/" + bench + "_" + p_underscore + ".txt"
        if (os.path.exists(read_file_name)):
            rf = open(read_file_name, 'r')
            write_file_name = "./data/sampled_raw_data/" + target + "/" + bench + "/" + bench + "_" + p_underscore + ".txt"
            wf = open(write_file_name, 'w')
            for line in rf:
                line_list = line.split(",")
                src_info = line_list[1]
                if (src_info in sampled_src_idxs):
                    wf.write(line)
            rf.close()
            wf.close()

    return






'''
samplingRate = 0.2

# refSrc -> refSnk -> srcIdx
# srcSnkIdx = {}

srcIdx = {}

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
                    lineCnt = 0
                    for line in lines:
                        lineCnt += 1
                        if (lineCnt % 1000 == 0):
                            print lineCnt
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
                        
                        if (refSrc not in srcSnkIdx.keys()):
                            srcSnkIdx[refSrc] = {}
                        if (refSnk not in srcSnkIdx[refSrc].keys()):
                            srcSnkIdx[refSrc][refSnk] = []
                        if (idxSrc not in srcSnkIdx[refSrc][refSnk]):
                            srcSnkIdx[refSrc][refSnk].append(idxSrc)
                        
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
                
    
'''
