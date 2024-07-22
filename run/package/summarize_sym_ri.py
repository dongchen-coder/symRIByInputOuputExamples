import os

def summerize_for_bench_with_format(bench, inOutFormat):
    files = os.listdir("../data/sym_ri/" + bench)
    outputFile = open("../data/sym_ri/all/" + bench + inOutFormat, "w")
    
    for f in files:
        name = f
        #if (inOutFormat not in name):
        #    continue
        if (not name.endswith(inOutFormat)):
            continue
        
        f = open("../data/sym_ri/"+bench+"/"+f, 'r')
        for line in f:
            if ("(^0^)" in line):
                prog = line.replace("Searched Program (^0^) :", "Prog:")
                outputFile.write(name + " " + prog)
        f.close()
    outputFile.close()

def summerize_sym_ri(bench, cache_config):
    print("Start to summerize " + bench, cache_config)
    if (not os.path.isdir("../data/sym_ri/" + bench)):
        return
    files = os.listdir("../data/sym_ri/" + bench)
    
    summerize_for_bench_with_format(bench, ".ri."+cache_config+".src_only")
    summerize_for_bench_with_format(bench, ".ri."+cache_config+".src_snk")
    summerize_for_bench_with_format(bench, ".ri."+cache_config+".src_snk_plus")

    isnk_id = 0
    while(True):
        exsitFlag = False
        for f in files:
            if (".isnk"+str(isnk_id) in f):
                exsitFlag = True
                break
        if (exsitFlag == False):
            break
        summerize_for_bench_with_format(bench, ".isnk"+str(isnk_id)+"."+cache_config+".src_snk_plus")
        isnk_id += 1
    
    summerize_for_bench_with_format(bench, ".ibound")
