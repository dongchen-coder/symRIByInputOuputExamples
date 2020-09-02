import os

def readSymbolicHistSrc(path, benchName):
    symbolicHistSrc = {}
    if (os.path.exists(path + benchName + "_src.txt")):
        f_src = open(path + benchName + "_src.txt", "r")
        for line in f_src:
            line = line.replace("\n", "")
            prog = line[line.find(' Prog:') + 7: len(line)]
            prog = prog.replace("\n", "")
            
            conf = line[0 : line.find(' Prog:')]
            conf = conf.replace("_src_result.txt", "")
            conf = conf.replace(benchName + "_refsrc_","")
            conf = conf.replace("_itersrc_", " ")
            conf = conf.split(" ")
            ref_id = int(conf[0])
            idxs_str = conf[1].split("_")
            idxs = []
            for idx in idxs_str:
                idxs.append(int(idx))
            idxs = tuple(idxs)
            
            if (ref_id not in symbolicHistSrc.keys()):
                symbolicHistSrc[ref_id] = {}
            symbolicHistSrc[ref_id][idxs] = prog
        f_src.close()
    
    return symbolicHistSrc

def readSymbolicHistSrcsnk(path, benchName):
    symbolicHistSrcsnk = {}
    if (os.path.exists(path + benchName + "_srcsnk.txt")):
        f_srcsnk = open(path + benchName + "_srcsnk.txt", "r")
        for line in f_srcsnk:
            line = line.replace("\n", "")
            prog = line[line.find(' Prog:') + 7: len(line)]
            prog = prog.replace("\n", "")
            
            conf = line[0 : line.find(' Prog:')]
            conf = conf.replace("_srcsnk_result.txt", "")
            conf = conf.replace(benchName + "_refsrc_", "")
            conf = conf.replace("_refsnk_", " ")
            conf = conf.replace("_iter_", " ")
            conf = conf.split(" ")
            ref_src_id = int(conf[0])
            ref_snk_id = int(conf[1])
            
            if (ref_src_id not in symbolicHistSrcsnk.keys()):
                symbolicHistSrcsnk[ref_src_id] = {}
            symbolicHistSrcsnk[ref_src_id][ref_snk_id] = prog
        f_srcsnk.close()
    
    return symbolicHistSrcsnk

def readSymbolicIBoundsSrc(path, benchName):
    symbolicIBoundsSrc = {}
    if (os.path.exists(path + benchName + "_IBound_result.txt")):
        f_IBound = open(path + benchName + "_IBound_result.txt", "r")
        for line in f_IBound:
            line = line.replace("\n", "")
            prog = line[line.find(' Prog:') + 7: len(line)]
            
            conf = line[0 : line.find(' Prog:')]
            conf = conf.replace("_IBound", "")
            conf = conf.replace("refsrc_", "")
            conf = conf.split("_")
            ref_src_id = int(conf[0])
            Isrc = conf[1].replace("I", "Isrc")

            if (ref_src_id not in symbolicIBoundsSrc.keys()):
                symbolicIBoundsSrc[ref_src_id] = {}
            
            if (Isrc not in symbolicIBoundsSrc[ref_src_id].keys()):
                if ("min" in line):
                    symbolicIBoundsSrc[ref_src_id][Isrc] = [prog, ""]
                if ("max" in line):
                    symbolicIBoundsSrc[ref_src_id][Isrc] = ["", prog]
            else:
                if ("min" in line):
                    symbolicIBoundsSrc[ref_src_id][Isrc][0] = prog
                if ("max" in line):
                    symbolicIBoundsSrc[ref_src_id][Isrc][1] = prog

        f_IBound.close()

    print symbolicIBoundsSrc

    return symbolicIBoundsSrc

def readSymbolicIBoundsSrcsnk(path, benchName):
    symbolicIBoundsSrcsnk = {}
    return symbolicIBoundsSrcsnk

def readTraceFile(name, symBoundValueForPred):
    histogram = {}

    fName = "../histoToMatch/" + name + "/" + name;
    for bound in symBoundValueForPred:
        fName += "_" + str(bound)
    fName += ".txt"
    
    if (os.path.exists(fName)):
        f = open(fName, 'r')
        for line in f:
            lineList = line.split()
            ri = int(lineList[0])
            cnt = int(lineList[1])
            histogram[ri] = cnt
        f.close()
    
    return histogram

