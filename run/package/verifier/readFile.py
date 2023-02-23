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
    
    info = line[0 : line.find('.ri.') + 1]
    
    if ("_refsrc_" in info and "_isrc_" in info):
        refSrc = int(info[info.find("_refsrc_") + 8 : info.find("_isrc_")])
    
    if ("_Psrc_" in info):
        if ("_isrc_" in info):
            IsrcStr = info[info.find("_isrc_") + 6 : info.find("_psrc_")]
            Isrc = IsrcStr.split("_")
            Isrc = [int(x) for x in Isrc]
            Isrc = tuple(Isrc)
        if ("_refsnk_" in info):
            Psrc = int(info[info.find("_psrc_") + 6 : info.find("_refsnk_")])
        else:
            Psrc = int(info[info.find("_psrc_") + 6 : ])
    else:
        if ("_isrc_" in info and "_refsnk_" not in info):
            IsrcStr = info[info.find("_isrc_") + 6 : info.find(".")]
            Isrc = IsrcStr.split("_")
            Isrc = [int(x) for x in Isrc]
            Isrc = tuple(Isrc)
        if ("_isrc_" in info and "_refsnk_" in info):
            IsrcStr = info[info.find("_isrc_") + 6 : info.find("_refsnk_")]
            Isrc = IsrcStr.split("_")
            Isrc = [int(x) for x in Isrc]
            Isrc = tuple(Isrc)
    
    if ("_refsnk_" in info):
        refSnk = int(info[info.find("_refsnk_") + 8 : info.find(".")])
    
    return [refSrc, Isrc, Psrc, refSnk, prog]

def read_sym_ri(sym_ri_file):
    symbolicHist = {}
    
    if (os.path.exists(sym_ri_file)):
        f = open(sym_ri_file, "r")
        print "reading", sym_ri_file
        
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
    else:
        print "file: ", sym_ri_file, "does not exsits"
    
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

def readSymbolicIBounds(sym_ibound_file):
    symbolicIBound = {}
    
    if (os.path.exists(sym_ibound_file)):
        print "reading", sym_ibound_file
        
        f = open(sym_ibound_file, "r")
        for line in f:
            if ("Prog" not in line):
                continue
            #if (mode == "src" and "_refsnk_" in line):
            #    continue
            #if (mode == "src_snk" and "_refsnk_" not in line):
            #    continue
            
            #print line,
            [refSrc, refSnk, I, prog] = decodeLineIbound(line)
            #print [refSrc, refSnk, I, prog]
            
            
            if (refSrc not in symbolicIBound.keys()):
                symbolicIBound[refSrc] = {}
            if ("min" in I):
                I_idx = int(I.replace("imin",""))
                if (I_idx not in symbolicIBound[refSrc].keys()):
                    symbolicIBound[refSrc][I_idx] = [prog, "X"]
                else:
                    symbolicIBound[refSrc][I_idx][0] = prog
            if ("max" in I):
                I_idx = int(I.replace("imax",""))
                if (I_idx not in symbolicIBound[refSrc].keys()):
                    symbolicIBound[refSrc][I_idx] = ["X", prog]
                else:
                    symbolicIBound[refSrc][I_idx][1] = prog
            
    else:
        print "file:", sym_ibound_file, "does not exsit"
        
    return symbolicIBound

# read Isnk
def decodeLineIsnk(line):
    refSrc = ""
    refSnk = ""
    Isrc = []
    prog = ""
    
    line = line.replace("\n","")
    info = line.split(".")[0]
    prog = line[line.find("Prog:") + 6 : ]
    
    refSrc = int(info[info.find("_refsrc_") + 8 : info.find("_isrc_")])
    refSnk = int(info[info.find("_refsnk_") + 8 : ])
    Isrc = info[info.find("_isrc_") + 6 : info.find("_refsnk_")]
    Isrc = Isrc.split("_")
    Isrc = [int(x) for x in Isrc]
    Isrc = tuple(Isrc)
    
    return [refSrc, refSnk, Isrc, prog]

def read_sym_isnk(benchName, surfix):
    symbolicIsnk = {}
    IsnkIdx = 0

    while(os.path.exists(benchName + ".isnk" + str(IsnkIdx) + "." + surfix)):
        f = open(benchName + ".isnk" + str(IsnkIdx) + "." + surfix, "r")
        
        print "reading", benchName + ".isnk" + str(IsnkIdx) + "." + surfix
        
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
                if (Isrc in symbolicIsnk[refSrc][refSnk].keys()):
                    symbolicIsnk[refSrc][refSnk][Isrc].append(prog)
                
        IsnkIdx += 1
    
    return symbolicIsnk

# read trace
def readTraceFile(file_name, symBoundValueForPred, cacheConfig):
    histogram = {}

    for bound in symBoundValueForPred:
        file_name += "_" + str(bound)
    file_name += "_trace.txt"
        
    if (os.path.exists(file_name)):
        print "reading", file_name
        f = open(file_name, 'r')
        for line in f:
            lineList = line.split()
            ri = int(lineList[0])
            cnt = int(lineList[1])
            histogram[ri] = cnt
        f.close()
    else:
        print "file:", file_name, "does not exist"
    
    return histogram

