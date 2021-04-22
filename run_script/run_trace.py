import os

def combinations_with_replacement(iterable, r):
    n = len(iterable)
    if (not n and r):
        return
    indices = [0] * r
    yield tuple(iterable[i] for i in indices)
    while True:
        for i in reversed(range(r)):
            if indices[i] != n - 1:
                break
            else:
                return
            indices[i:] = [indices[i] + 1] * (r - i)
            yield tuple(pool[i] for i in indices)
    return

def list_to_string(sizes, spliter):
    sizes_str = ""
    for elm in sizes:
        sizes_str += spliter + str(elm)
    return sizes_str

verify_sizes = [30]

BENCH_BIN_DIR = "../bin/bench_bin"
RIS_MATCH_DIR="../verify/histoToMatch"

benches = {}
benches[1] = ['stencil']#["stencil", "cholesky", "durbin", "floyd_warshall", "gemver", "gesummv", "lu", "ludcmp", "mvt", "nussinov", "stencil", "trisolv"]
benches[2] = ['stencil_tiled']#["heat_3d", "trangle", "adi", "atax", "bicg", "convolution_2d", "correlation", "covariance", "deriche", "gramschmidt", "heat_3d", "jacobi_1d", "jacobi_2d", "seidel_2d", "symm", "syr2d", "syrk", "trmm"]
benches[3] = []#["doitgen", "convolution_3d", "doitgen", "fdtd_2d", "gemm"]  
benches[4] = []#["2mm"]
benches[5] = []#["3mm"]


for cls_ds in ["_ELM", "_CLS32_DS8"]:
    print cls_ds,
    output_dir = RIS_MATCH_DIR + cls_ds
    
    for bench in benches[1] + benches[2] + benches[3] + benches[4] + benches[5]:
        os.system("rm -r " + output_dir +  "/" + bench)
        os.system("mkdir " + output_dir + "/" + bench)

    for para_num in [1, 2, 3, 4, 5]:
        sizes = list(combinations_with_replacement(verify_sizes, para_num))
        for bench in benches[para_num]:
            print bench,
            for size in sizes:
                cmd = BENCH_BIN_DIR + "/" + bench + cls_ds + "_trace" + list_to_string(size, " ") + " > " + output_dir + "/" + bench + "/" + bench + list_to_string(size, "_") + ".txt"
                os.system(cmd)
        
    print "DONE"
