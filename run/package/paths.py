bench_bin_path = "../bench/bench_bin/"
traced_data_path = "../data/traced_data/"
raw_data_path = "../data/raw_data/"
ioe_data_path = "../data/input-output_examples/"
ioe_path = '../data/input-output_examples/'
syn_bin = "../search-based_synthesizer/bin/symRiSymthesiser"
sym_ri_path = "../data/sym_ri/"

def get_parms_str(parms):
    return [str(x) for x in list(parms)]

def get_parms_str_space(parms):
    parms_str = get_parms_str(parms)
    return " ".join(parms_str)

def get_parms_str_underline(parms):
    parms_str = get_parms_str(parms)
    return "_".join(parms_str)
