import os

def get_failed_ioe_with_no_sym_ri(cache_config, benches, ioe_path, sym_ri_path):
    failed_ioe = {}
    for mode in ["src_only", "src_enhanced", "src_snk"]:
        print cache_config, mode, "------------------------"
        failed_ioe[mode] = {}
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
            failed_ioe[mode][bench] = failed_ioe_files
            print bench, len(ioe_files), len(failed_ioe_files),
        print ""
    return failed_ioe
    
if __name__ == "__main__":
    
    benches = ["2mm", "3mm", "adi", "atax", "bicg", "cholesky", "correlation", "covariance", "deriche", "doitgen", "durbin", "fdtd_2d", "floyd_warshall", "gemm", "gemver", "gesummv", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "lu", "ludcmp", "mvt", "nussinov", "seidel_2d", "symm", "syr2d", "syrk", "trisolv", "trmm"]

    ioe_path = "./data/input-output_examples/"
    sym_ri_path = "./data/sym_ri/"

    failed_ioe = get_failed_ioe_with_no_sym_ri("clS32_ds8", benches, ioe_path, sym_ri_path)
    
