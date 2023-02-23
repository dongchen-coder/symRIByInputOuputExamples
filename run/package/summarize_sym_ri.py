import os
from paths import *

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
    print "Start to summerize " + bench, cache_config
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

def read_sym_ri(bench, parms, spec, df, ref_ids, iter_vecs, cache_config):
    iter_sym_ri_map = {}
    if (spec == 'src_only' and isinstance(ref_ids, int)):
        for iter_vec in iter_vecs:
            src_id = str(ref_ids)
            src_iv_ = iter_vec.replace(' ', '_')
            file_name = bench + '_refsrc_' + src_id + '_isrc_' + src_iv_ + '.ri.' + cache_config
            sym_ri_file = sym_ri_path + bench + "/" + file_name + '.' + spec
            f = open(sym_ri_file, 'r')
            for line in f:
                if ("(^0^)" in line):
                    prog = line.replace("Searched Program (^0^) :", "Prog:")
                    iter_sym_ri_map[iter_vec] = prog.replace('\n','')
                else:
                    iter_sym_ri_map[iter_vec] = 'Prog: -1'
            f.close()
    if ((spec == 'src_snk' or spec == 'src_snk_plus') and isinstance(ref_ids, tuple)):
        for iter_vec in iter_vecs:
            src_id = str(ref_ids[0])
            snk_id = str(ref_ids[1])
            src_iv_ = iter_vec.replace(' ', '_')
            file_name = bench + '_refsrc_' + src_id + '_refsnk_' + snk_id + '_isrc_' + src_iv_ + '.ri.' + cache_config
            sym_ri_file = sym_ri_path + bench + "/" + file_name + '.' + spec
            f = open(sym_ri_file, 'r')
            for line in f:
                if ("(^0^)" in line):
                    prog = line.replace("Searched Program (^0^) :", "Prog:")
                    iter_sym_ri_map[iter_vec] = prog.replace('\n','')
                else:
                    iter_sym_ri_map[iter_vec] = 'Prog: -1'
            f.close()
    return iter_sym_ri_map