import os

path = "./synResult/"
files = os.listdir(path)

for name in files:
	f = open(path+name, 'r')
	for line in f:
		if ("(T^T)" in line):
			print name.replace("_result.txt", ""), line.replace("\n","")
			os.system("./bin/symRiSymthesiser ./inputoutput/" + name.replace("_result", "") + " > ./synResult/" + name)
	f.close()

