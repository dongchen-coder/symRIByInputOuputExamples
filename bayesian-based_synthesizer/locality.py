try:
    import binutil  # required to import from dreamcoder modules
except ModuleNotFoundError:
    import bin.binutil  # alt import if called as module

import datetime
import os
import random
import argparse
import sys
import contextlib

from dreamcoder.ec import commandlineArguments, ecIterator
from dreamcoder.grammar import Grammar
from dreamcoder.program import Primitive
from dreamcoder.task import Task
from dreamcoder.type import arrow, tint, tboolean
from dreamcoder.utilities import numberOfCPUs



# Primitives
def _loc_addition(x, y): return lambda x, y: x + y
def _loc_substraction(x, y): return lambda x, y: x - y
def _loc_multiplication(x, y): return lambda x, y: x * y
def _loc_division(x, y): return lambda x: x / y
def _loc_ite(x, y, z): return lambda x, y, z: y if x else z
def _loc_le(x, y): return lambda x, y: x < y
def _loc_not(x): return lambda x: not x
def _loc_and(x, y): return lambda x, y: x and y
def _loc_div8(x): return lambda x: x / 8

def get_tint_task(item):
    task_type = arrow(tint, tint)
    if (item["name"] in ["add_train", "sub_train", "mul_train", "div_train"]):
        task_type = arrow(tint, tint, tint)
    if (item["name"] in ["ite_train"]):
        task_type = arrow(tboolean, tint, tint, tint)
    if (item["name"] in ["not_train"]):
        task_type = arrow(tboolean, tboolean)
    if (item["name"] in ["and_train"]):
        task_type = arrow(tboolean, tboolean, tboolean)
    if (item["name"] in ["le_train"]):
        task_type = arrow(tint, tint, tboolean)
    if (item["name"] in ["ri_test"]):
        task_type = arrow(tint, tint, tint, tint)
    if (item["name"] in ["loc_train_1", "loc_train_2"]):
        task_type = arrow(tint, tint, tint, tint)
    return Task(
        item["name"],
        task_type,
        [(ex["i"], ex["o"]) for ex in item["examples"]],
    )

def get_loc_task(file_path):
    with open(file_path, 'r') as f:
        ioes = []
        loc_task_type = [arrow(tint, *[tint] * (i + 1)) for i in range(20)]
        for line in f:
            lineList = line.split()
            inputs = lineList[0:-2][1::2]
            output = int(float(lineList[-1]))
            inputs_tuple = tuple(map(int, inputs))
            task_type = loc_task_type[int(len(inputs))-1]
            ioes.append((inputs_tuple, output))

        return Task(
            file_path.split('/')[-1],
            task_type,
            ioes,
        )

def get_loc_tasks_in_folder(folder_path):
    tasks = []
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            file_path = os.path.join(root, file)
            if not file.startswith('.') and os.path.getsize(file_path) > 0:
                print(file_path)
                if (os.path.getsize(file_path) == 0):
                    print("Warning", file_path, "is Empty")
                loc_task = get_loc_task(file_path)
                tasks.append(loc_task)
    return tasks


def process_folder(args, folder_path):

    #folder_path = "/machine/input-output_examples/stencil/src_only"
    loc_tasks = get_loc_tasks_in_folder(folder_path)

    #file_path = "./stencil_refsrc_0_isrc_16_1.ri.cls32_ds8"
    #loc_task = get_loc_task(file_path)

    # Options more or less copied from list.py
    #args = commandlineArguments(
    #    enumerationTimeout=50, activation='tanh',
    #    iterations=10, recognitionTimeout=7200,
    #    a=3, maximumFrontier=100, topK=5, pseudoCounts=30.0,
    #    helmholtzRatio=0.5, structurePenalty=1.,
    #    CPUs=numberOfCPUs())

    timestamp = datetime.datetime.now().isoformat()
    outdir = 'experimentOutputs/locality/'
    os.makedirs(outdir, exist_ok=True)
    outprefix = outdir + timestamp
    args.update({"outputPrefix": outprefix})

    # Create list of primitives

    primitives = [
        Primitive("loc_add", arrow(tint, tint, tint), _loc_addition),
        Primitive("loc_sub", arrow(tint, tint, tint), _loc_substraction),
        Primitive("loc_mul", arrow(tint, tint, tint), _loc_multiplication),
        #Primitive("loc_div", arrow(tint, tint, tint), _loc_division),
        Primitive("loc_ite", arrow(tboolean, tint, tint, tint), _loc_ite),
        Primitive("loc_le", arrow(tint, tint, tboolean), _loc_le),
        Primitive("0", tint, 0),
        Primitive("1", tint, 1),
        Primitive("2", tint, 2),
        Primitive("not", arrow(tboolean, tboolean), _loc_not),
        Primitive("and", arrow(tboolean, tboolean, tboolean), _loc_and),
        Primitive("3", tint, 3),
        #Primitive("4", tint, 4),
        Primitive("5", tint, 5),
        #Primitive("6", tint, 6),
        Primitive("7", tint, 7),
        Primitive("loc_div8", arrow(tint, tint), _loc_div8),
        #Primitive("true", tboolean, True),
        #Primitive("false", tboolean, False),
    ]

    # Create grammar
    grammar = Grammar.uniform(primitives)

    # Training data
    def addGen():
        x = random.choice(range(500))
        y = random.choice(range(500))
        return {"i": (x, y), "o": x+y}

    def subGen():
        x = random.choice(range(500))
        y = random.choice(range(500))
        return {"i": (x, y), "o": x-y}

    def mulGen():
        x = random.choice(range(500))
        y = random.choice(range(500))
        return {"i": (x, y), "o": x*y}

    def divGen():
        x = random.choice(range(500))
        y = random.choice(range(1, 500))
        return {"i": (x, y), "o": int(x/y)}

    def iteGen():
        x = random.choice([False, True])
        y = random.choice(range(500))
        z = random.choice(range(500))
        return {"i": (x, y, z), "o": y if x else z}

    def leGen():
        x = random.choice(range(500))
        y = random.choice(range(500))
        return {"i": (x, y), "o": x < y}

    def notGen():
        x = random.choice([True, False])
        return {"i": (x, ), "o": not x}

    def andGen():
        x = random.choice([True, False])
        y = random.choice([True, False])
        return {"i": (x, y), "o": x and y}

    def locTrainGen_1():
        i = random.choice(range(5))
        j = random.choice(range(5))
        b = random.choice([4, 8, 16, 32])
        return {"i": (i, j, b), "o": 2 if (i < b and j < b) else 0}

    def locTrainGen_2():
        i = random.choice(range(5))
        j = random.choice(range(5))
        b = random.choice([4, 8, 16, 32])
        return {"i": (i, j, b), "o": 2 if (i < b) else 0}

    training_examples = [
        #{"name": "add_train", "examples": [addGen() for _ in range(10)]},
        #{"name": "sub_train", "examples": [subGen() for _ in range(10)]},
        #{"name": "mul_train", "examples": [mulGen() for _ in range(10)]},
        #{"name": "div_train", "examples": [divGen() for _ in range(5000)]},
        #{"name": "ite_train", "examples": [iteGen() for _ in range(10)]},
        #{"name": "le_train",  "examples": [leGen()  for _ in range(10)]},
        #{"name": "not_train", "examples": [notGen() for _ in range(10)]},
        #{"name": "and_train", "examples": [andGen() for _ in range(10)]},
        #{"name": "loc_train_1", "examples": [locTrainGen_1() for _ in range(15)]},
        {"name": "loc_train_2", "examples": [locTrainGen_2() for _ in range(15)]},
    ]
    #training = [get_tint_task(item) for item in training_examples]
    #training.append(loc_task)
    training = loc_tasks

    print(training)

    # Testing data
    testing_examples = [
        {"name": "ri_test", "examples": [{"i": (15, 1, 8), "o": 0}, {"i": (15, 1, 12), "o": 0}, {"i": (15, 1, 16), "o": 2}, {"i": (15, 1, 20), "o": 2}]}
    ]
    testing = [get_tint_task(item) for item in testing_examples]

    # EC iterate
    generator = ecIterator(grammar,
                           training,
                           testingTasks=testing,
                           **args)
    for i, _ in enumerate(generator):
        print('ecIterator count {}'.format(i))

@contextlib.contextmanager
def redirect_output_and_errors(file_path):
    original_stdout = sys.stdout
    original_stderr = sys.stderr
    try:
        with open(file_path, 'w') as file:
            sys.stdout = file
            sys.stderr = file
            yield
    finally:
        sys.stdout = original_stdout
        sys.stderr = original_stderr

if __name__ == "__main__":
    args = commandlineArguments(
        enumerationTimeout=50, activation='tanh',
        iterations=10, recognitionTimeout=7200,
        a=3, maximumFrontier=100, topK=5, pseudoCounts=30.0,
        helmholtzRatio=0.5, structurePenalty=1.,
        CPUs=numberOfCPUs())
    
    root_folder_path = "/machine/input-output_examples"
    subfolders = []
    for root, dirs, files in os.walk(root_folder_path):
        # iterate by bench
        #for dir in dirs:
        #    subfolders.append(os.path.join(root, dir))
        # iterate by bench/spec
        if not dirs:
            subfolders.append(root)

    for folder_path in subfolders:
        #folder_path = "/machine/input-output_examples/stencil/src_only"
        log_path = folder_path.replace("input-output_examples", "logs") + ".txt"
        os.makedirs(os.path.dirname(log_path), exist_ok=True)

        with redirect_output_and_errors(log_path):
            try:
                process_folder(args, folder_path)
            except Exception as e:
                print(e)
