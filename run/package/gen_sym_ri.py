import os
import random
from concurrent.futures import ProcessPoolExecutor, as_completed
from queue import Queue
from multiprocessing import Manager

# paths to exec and result files
syn_bin = "../search-based_synthesizer/build/src/symRiSynthesizer"
data_path = "../data/input-output_examples/"
result_path = "../data/sym_ri/"

# clear all generated sym RI
def clearSymRI(bench):
    os.system("rm -rf " + result_path + bench)
    os.system("mkdir -p " + result_path + bench)

# process each input-output file
def processIOEFile(example):
    [folder, bench, f, syn_config] = example
    
    cmd_option = syn_config["constants_for_predicate"] + syn_config["constants_for_term"] + syn_config["int_ops_for_term"] + syn_config["search_time_for_terms_in_seconds"] + syn_config["search_time_for_preds_in_seconds"]

    if (f[0] == "src_snk_plus"):
        syn_config["rules_to_apply"] = " -RULESTOAPPLY SrcSnk"
    cmd_option += syn_config["rules_to_apply"]

    suffix = ''
    if (folder != "ibound"):
        suffix = "." + folder
   
    cmd = syn_bin + " -FILE " + data_path + bench + "/" + folder + "/" + f + cmd_option + " > " + result_path + bench + "/" + f + suffix
    os.system(cmd)

def init_files_to_process(bench):
    files_to_process = []
    for folder in ["ibound", "src_only", "src_snk", "src_snk_plus"]:
        filesInFolder = os.listdir(data_path + bench + "/" + folder)
        filesCLS = list(filter(lambda x : "cls32_ds8" in x or "ibound" in x, filesInFolder))
        if (len(filesCLS) > 200 and folder != "ibound"):
            random.shuffle(filesCLS)
            filesCLS = filesCLS[0:200]
        files_to_process += [[folder, bench, f] for f in filesCLS]
    return files_to_process   

def process_task_queue(task_queue, syn_config):
    while not task_queue.empty():
        task = task_queue.get()
        if task is None:
            task_queue.task_done()
            break
        worker_id = os.getpid()
        print(f"Worker {worker_id} processing task: {task}")
        processIOEFile(task + [syn_config])
        print(f"Worker {worker_id} finished task: {task}")
        task_queue.task_done()

def gen_sym_ri(bench, syn_config, num_of_cpus):
    clearSymRI(bench)
    files = init_files_to_process(bench)
    print(f"Total number of jobs to process: {len(files)}")

    with Manager() as manager:
        task_queue = manager.Queue()
        for f in files:
            task_queue.put(f)

        with ProcessPoolExecutor(max_workers=num_of_cpus) as executor:
            futures = [executor.submit(process_task_queue, task_queue, syn_config) for _ in range(num_of_cpus)]
            for _ in range(num_of_cpus):
                task_queue.put(None)
            
            for future in as_completed(futures):
                future.result()  # To raise exceptions if any

        task_queue.join()
