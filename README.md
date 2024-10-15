# Symbolic Reuse Interval Synthesizer By Input-output Examples

This project is trying to explore synthesizing symbolic reuse interval expressions with input-output examples.

# How to run this code

## Generate executables to produce the data from PolyBench
```sh
cd bench
make bench_gen
make trace_gen
```

## Run the system to reorgnize the raw data and synthesis the Symbolic Reuse Interval
```sh
cd run
python run.py
```