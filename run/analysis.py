import os

def get_failed_ioe_with_no_sym_ri(cache_config, benches, ioe_path, sym_ri_path):
    failed_ioes = {}
    for mode in ["src_only", "src_enhanced", "src_snk", "ibound"]:
        print cache_config, mode, "------------------------"
        failed_ioes[mode] = {}
        for bench in benches:
            ioe_files = []
            sym_ri_files = []
            if (os.path.exists(ioe_path + bench + '/' + mode)):
                ioe_files = os.listdir(ioe_path + bench + '/' + mode)
            if (os.path.exists(sym_ri_path + bench)):
                sym_ri_files = os.listdir(sym_ri_path + bench)
            
            failed_ioe_files = []
            for sym_ri_file in sym_ri_files:
                if (mode in sym_ri_file):
                    f = open(sym_ri_path + bench + "/" + sym_ri_file)
                    first_line = f.readline()
                    if ("(^0^)" not in first_line):
                        failed_ioe_files.append(sym_ri_file)
            failed_ioes[mode][bench] = failed_ioe_files
            print bench, len(ioe_files), len(failed_ioe_files),
        print ""
    return failed_ioes

def run_failed_ioes(cache_config, failed_ioes, ioe_path, sym_ri_path):
    for mode in failed_ioes.keys():
        for bench in failed_ioes[mode].keys():
            for file_name in failed_ioes[mode][bench]:
                ioe_file = ioe_path + bench + '/' + mode + '/' + file_name.replace("."+mode,"")
                synthesizer_conf = " -CONSTANTSPRED 1 2 -CONSTANTSTERM 0 1 2 3 4 5 6 -INTOPSTERM VAR NUM PLUS TIMES MINUS -SEARCHTIMEFORTERMSINSECONDS 5 -SEARCHTIMEFORPREDSINSECONDS 5 "
                cmd = ""
                if mode == "src_only" or mode == "ibound":
                    cmd = "../synthesizer/bin/symRiSymthesiser -FILE "+ ioe_file + synthesizer_conf + "-RULESTOAPPLY SrcOnly > " + sym_ri_path+bench+"/"+file_name
                if mode == "src_enhanced":
                    cmd = "../synthesizer/bin/symRiSymthesiser -FILE "+ ioe_file + synthesizer_conf + "-RULESTOAPPLY SrcEnhanced > " + sym_ri_path+bench+"/"+file_name
                if mode == "src_snk":
                    cmd = "../synthesizer/bin/symRiSymthesiser -FILE "+ ioe_file + synthesizer_conf + "-RULESTOAPPLY SrcSnk > " + sym_ri_path+bench+"/"+file_name
                print cmd
                os.system(cmd)
                exit()
    return

if __name__ == "__main__":
    
    benches = ["2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm"]

    ioe_path = "./data/input-output_examples/"
    sym_ri_path = "./data/sym_ri/"

    failed_ioes = get_failed_ioe_with_no_sym_ri("cls32_ds8", benches, ioe_path, sym_ri_path)
    run_failed_ioes("cls32_dc8", failed_ioes, ioe_path, sym_ri_path)
