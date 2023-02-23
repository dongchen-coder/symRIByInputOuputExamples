import os
from random import sample

f = open('failed.txt','r')
ioes = []
for line in f:
    line_list = line.split();
    tmp = []
    for i in range(len(line_list)):
        if (i % 2 == 1):
            tmp.append(line_list[i])
    ioes.append(tmp)
f.close()

n_ioes = len(ioes)
n_inputs = len(ioes[0])-1

f = open('failed.sk', 'w')
sym_ri_prog = 'int sym_ri(int['+str(n_inputs)+'] input) {\nif( input[??] < input[??] + ??  )\nreturn ?? + ?? * input[??];\nelse\nreturn ??;\n}\n'
f.write(sym_ri_prog)

main_prog = "harness void main(int x) {\nint["+str(n_inputs)+"]["+str(n_ioes)+"] inputs = {";

ioes.sort(key = lambda x : x[-1])

inputs = []
outputs = []
for ioe in ioes:
    if (ioe[-1] == '0'):
        continue
    inputs.append(ioe[0:-1])
    outputs.append(ioe[-1])

for one_input in inputs:
    main_prog += "{";
    for elm in one_input:
        main_prog += elm+','
    main_prog = main_prog[:-1]
    main_prog += '},'
main_prog = main_prog[:-1]
main_prog += '};\nint['+str(n_ioes)+'] outputs = {'
for elm in outputs:
    main_prog += elm+','
main_prog = main_prog[:-1]
main_prog += '};\nrepeat(i:'+str(n_ioes)+'){\nassert sym_ri(inputs[i]) == outputs[i];\n}\nreturn;\n}\n'

f.write(main_prog)
f.close()
  
