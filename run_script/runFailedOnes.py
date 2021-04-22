import os

path = "./synResult/"
files = os.listdir(path)

for name in files:
	f = open(path+name, 'r')
	flag = False
	for line in f:
		if ("(^0^)" in line):
			flag = True
	f.close()
	if (flag == False):
		print name.replace("_result.txt", ""), line.replace("\n","")
		os.system("./bin/symRiSymthesiser ./inputoutput/" + name.replace("_result", "") + " > ./synResult/" + name)

