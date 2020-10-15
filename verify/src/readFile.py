import os

# read RI
def decodeLineRI(line):
    
    refSrc = ""
    Isrc = []
    Psrc = ""
    refSnk = ""
    
    prog = ""
    
    line = line.replace("\n", "")
    prog = line[line.find(' Prog:') + 7: len(line)]
    
    info = line[0 : line.find('.')]
    
    if ("_refsrc_" in info and "_Isrc_" in info):
        refSrc = int(info[info.find("_refsrc_") + 8 : info.find("_Isrc_")])
    if ("_Isrc_" in info and "_Psrc_" in info):
        IsrcStr = info[info.find("_Isrc_") + 6 : info.find("_Psrc_")]
        Isrc = IsrcStr.split("_")
        Isrc = [int(x) for x in Isrc]
        Isrc = tuple(Isrc)
    if ("_Psrc_" in info):
        if ("_refsnk_" in info):
            Psrc = int(info[info.find("_Psrc_") + 6 : info.find("_refsnk_")])
        else:
            Psrc = int(info[info.find("_Psrc_") + 6 : ])
    if ("_refsnk_" in info):
        refSnk = int(info[info.find("_refsnk_") + 8 : ])
    
    return [refSrc, Isrc, Psrc, refSnk, prog]

def readSymbolicHist(benchName, surfix):
    symbolicHist = {}
    path = "../../synResult/all/"
    if (os.path.exists(path + benchName + surfix)):
        f = open(path + benchName + surfix, "r")
        for line in f:
            if ("Prog" not in line):
                continue
            
            [refSrc, Isrc, Psrc, refSnk, prog] = decodeLineRI(line)
            
            if (refSrc not in symbolicHist.keys()):
                symbolicHist[refSrc] = {}
            if (refSnk == ""):
                symbolicHist[refSrc][Isrc] = prog
            else:
                if (refSnk not in symbolicHist[refSrc].keys()):
                    symbolicHist[refSrc][refSnk] = {}
                symbolicHist[refSrc][refSnk][Isrc] = prog
        f.close()
    return symbolicHist

# read Ibound
def decodeLineIbound(line):
    refSrc = ""
    refSnk = ""
    I = ""
    prog = ""

    line = line.replace("\n", "")

    info = line.split('.')[0]
    I = line.split('.')[1]

    if ("refsnk" in line):
        refSnk = int(info[info.find("_refsnk_") + 8 : ])
        refSrc = int(info[info.find("_refsrc_") + 8 : info.find("_refsnk_")])
    else:
        refSrc = int(info[info.find("_refsrc_") + 8 : ])

    prog = line[line.find("Prog:") + 6 : ]
    return [refSrc, refSnk, I, prog]

def readSymbolicIBounds(benchName, mode, surfix):
    symbolicIBound = {}
    path = "../../synResult/all/"
    
    if (os.path.exists(path + benchName + surfix)):
        f = open(path + benchName + surfix, "r")
        for line in f:
            if ("Prog" not in line):
                continue
            if (mode == "src" and "_refsnk_" in line):
                continue
            if (mode == "srcsnk" and "_refsnk_" not in line):
                continue
            
            [refSrc, refSnk, I, prog] = decodeLineIbound(line)
            
            if (mode == "src"):
                if (refSrc not in symbolicIBound.keys()):
                    symbolicIBound[refSrc] = {}
                if ("min" in I):
                    I_idx = int(I.replace("Imin",""))
                    if (I_idx not in symbolicIBound[refSrc].keys()):
                        symbolicIBound[refSrc][I_idx] = [prog, "X"]
                    else:
                        symbolicIBound[refSrc][I_idx][0] = prog
                if ("max" in I):
                    I_idx = int(I.replace("Imax",""))
                    if (I not in symbolicIBound[refSrc].keys()):
                        symbolicIBound[refSrc][I_idx] = ["X", prog]
                    else:
                        symbolicIBound[refSrc][I_idx][1] = prog
            elif (mode == "srcsnk"):
                if (refSrc not in symbolicIBound.keys()):
                    symbolicIBound[refSrc] = {}
                if (refSnk not in symbolicIBound[refSrc].keys()):
                    symbolicIBound[refSrc][refSnk] = {}
                if ("min" in I):
                    I_idx = int(I.replace("Imin",""))
                    if (I_idx not in symbolicIBound[refSrc][refSnk].keys()):
                        symbolicIBound[refSrc][refSnk][I_idx] = [prog, "X"]
                    else:
                        symbolicIBound[refSrc][refSnk][I_idx][0] = prog
                if ("max" in I):
                    I_idx = int(I.replace("Imax",""))
                    if (I_idx not in symbolicIBound[refSrc][refSnk].keys()):
                        symbolicIBound[refSrc][refSnk][I_idx] = ["X", prog]
                    else:
                        symbolicIBound[refSrc][refSnk][I_idx][1] = prog
                
    return symbolicIBound

# read Isnk
def decodeLineIsnk(line):
    refSrc = ""
    refSnk = ""
    Isrc = []
    prog = ""
    
    line = line.replace("\n","")
    info = line.split(".")[0]
    
    refSrc = int(info[info.find("_refsrc_") + 8 : info.find("_Isrc_")])
    refSnk = int(info[info.find("_refsnk_") + 8 : ])
    Isrc = info[info.find("_Isrc_") + 6 : info.find("_Psrc_")]
    Isrc = Isrc.split("_")
    Isrc = [int(x) for x in Isrc]
    Isrc = tuple(Isrc)
    prog = line[line.find("Prog:") + 6 : ]
    
    return [refSrc, refSnk, Isrc, prog]

def readSymbolicIsnk(benchName, surfix):
    symbolicIsnk = {}
    path = "../../synResult/all/"
    IsnkIdx = 0
    while(os.path.exists(path + benchName + ".Isnk" + str(IsnkIdx) + "." + surfix)):
        f = open(path + benchName + ".Isnk" + str(IsnkIdx) + "." + surfix, "r")
        for line in f:
            if ("Prog" not in line):
                continue
            [refSrc, refSnk, Isrc, prog] = decodeLineIsnk(line)
            
            if (refSrc not in symbolicIsnk):
                symbolicIsnk[refSrc] = {}
            if (refSnk not in symbolicIsnk[refSrc].keys()):
                symbolicIsnk[refSrc][refSnk] = {}
            if (IsnkIdx == 0):
                symbolicIsnk[refSrc][refSnk][Isrc] = [prog]
            else:
                symbolicIsnk[refSrc][refSnk][Isrc].append(prog)
            
        IsnkIdx += 1
    return symbolicIsnk

# read trace
def readTraceFile(name, symBoundValueForPred, cacheConfig):
    histogram = {}

    fName = "../histoToMatch_" + cacheConfig + "/" + name + "/" + name;
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

