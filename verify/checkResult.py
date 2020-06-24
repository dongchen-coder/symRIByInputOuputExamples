import os

path = "../synResult/"
files = os.listdir(path)

succeed = 0
failed = 0
total = 0

symbolicHist = {}

for name in files:
	f = open(path+name, 'r')
	total += 1
	for line in f:
		if ("(^0^)" in line):
			succeed += 1
			print name.replace("_result.txt", ""), line.replace("\n","")
			prog = line[ line.find(':')+2 : len(line)].replace("\n","")
			if prog in symbolicHist.keys():
				symbolicHist[prog] += 1
			else:
				symbolicHist[prog] = 1  
		if ("(T^T)" in line):
			failed += 1
			print name.replace("_result.txt", ""), line.replace("\n","")
			#os.system("./bin/symRiSymthesiser ./inputoutput/" + name.replace("_result.txt", "") + ".txt > ./synResult/" + name)
			#exit()
			if "NYI" in symbolicHist.keys():
				symbolicHist["NYI"] += 1
			else:
				symbolicHist["NYI"] = 1
	f.close()

for prog in symbolicHist.keys():
    print prog, symbolicHist[prog]
print "total", total, "succeed", succeed, float(succeed)/total, "(-1 "+str(float(symbolicHist["-1"])/total)+")", "failed", failed, float(failed)/total
