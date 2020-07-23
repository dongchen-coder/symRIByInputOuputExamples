import os
import re
import matplotlib.pyplot as plt

# ref->i->j->symRI
symbolicHist = {}

def recordSymRI(conf, dslCode):
	conf = conf.replace("trangle_ref_","")
	conf = conf.split("_iter_")
	ref_id = int(conf[0])
	i = int(conf[1].split("_")[0])
	j = int(conf[1].split("_")[1])

	if (ref_id not in symbolicHist.keys()):
		symbolicHist[ref_id] = {}
	if (i not in symbolicHist[ref_id].keys()):
		symbolicHist[ref_id][i] = {}
	symbolicHist[ref_id][i][j] = dslCode
	return

def removeUnbalancedParenthesis(code):

	pIndex = []
	pString = ""
	for i in range(len(code)):
		c = code[i]
		if (c == '(' or c == ')'):
			pIndex.append(i)
			pString += c
	
	currentLeftParenthesis = 0
	toRemove = []
	for i in range(len(pString)):
		c = pString[i]
		if currentLeftParenthesis == 0 and c == ')':
			toRemove.append(pIndex[i])
		elif c == "(":
			currentLeftParenthesis += 1
		else:
			currentLeftParenthesis -= 1	

	currentRightParenthesis = 0
	for i in range(len(pString)):
		c = pString[len(pString) - i - 1]
		if currentRightParenthesis == 0 and c == '(':
			toRemove.append(pIndex[i])
		elif c == "(":
			currentRightParenthesis += 1
		else:
			currentRightParenthesis -= 1

	codeList = list(code)
	for i in toRemove:
		codeList[i] = ""
	code = "".join(codeList)
	
	return code


def evaluateIfStatement(dslCode):
	if ('(' not in dslCode):
		return dslCode
	if (dslCode[4] == 'T'):
		if (dslCode[14] != '('):
			value = ""
			i = 14
			while(dslCode[i] != ' ' and i < len(dslCode)):
				value += dslCode[i]
				i += 1
			return value
		else:
			pCnt = 1
			value = ""
			i = 14
			while(pCnt != 0 and i < len(dslCode)):
				if (dslCode[i] == '(' and i != 14):
					pCnt += 1
				if (dslCode[i] == ')'):
					pCnt -= 1
				value += dslCode[i]
				i += 1
			#print "eval true", value
			return evaluateIfStatement(value)
	if (dslCode[4] == 'F'):
		i = 15
		pCnt = 0
		while(True):
			if (i == len(dslCode)):
				break
			if (dslCode[i] == '('):
				pCnt += 1
			if (dslCode[i] == ')'):
				pCnt -= 1
			if (pCnt == 0 and dslCode[i] == 'e' and i+3 < len(dslCode) and dslCode[i+3] == 'e'):
				i = i + 5
				break
			i += 1

		value = ""
		while(i+1 < len(dslCode)):
			value += dslCode[i]
			i += 1
		#print "eval false", value
		return evaluateIfStatement(value)

def evaluateSingleCode(i, j, sizei, sizej, dslCode):

	#print dslCode
	
	dslCode = dslCode.replace("sizei ", str(sizei)+" ")
	dslCode = dslCode.replace("sizej ", str(sizej)+" ")
	dslCode = dslCode.replace("i ", str(i)+" ")
	dslCode = dslCode.replace("j ", str(j)+" ")
	dslCode = dslCode.replace("sizei)", str(sizei)+")")
	dslCode = dslCode.replace("sizej)", str(sizej)+")")
	dslCode = dslCode.replace("i)", str(i)+")")
	dslCode = dslCode.replace("j)", str(j)+")")
	dslCode = dslCode.replace("!", "not")
	dslCode = dslCode.replace("&&", "and")
	dslCodeList = re.split('if | then | else ', dslCode)
	#if (len(dslCodeList) > 4): 
	#	print dslCode
	#	print dslCodeList
	dslCodeList = [removeUnbalancedParenthesis(x) for x in dslCodeList]
	dslCodeListValue = []

	for term in dslCodeList:
		if term == "" or term == " " or term == "	":
			dslCodeListValue.append("")
			continue
		exec("result = " + term)
		dslCodeListValue.append(result)
	
	for i in range(len(dslCodeList)):
		for j in range(len(dslCodeList)):
			if (i >= j):
				continue
			if (dslCodeList[i] in dslCodeList[j]):
				tmp = dslCodeList[j]
				dslCodeList[j] = dslCodeList[i]
				dslCodeList[i] = tmp
				tmp = dslCodeListValue[j]
				dslCodeListValue[j] = dslCodeListValue[i]
				dslCodeListValue[i] = tmp

	for i in range(len(dslCodeListValue)):
		if (dslCodeListValue[i] != ""):
			dslCode = dslCode.replace(dslCodeList[i], str(dslCodeListValue[i]))

	#if (evaluateIfStatement(dslCode) == None):
	#	print dslCode
	#	print dslCodeList
	#	print dslCodeListValue
	#	print evaluateIfStatement(dslCode)

	return evaluateIfStatement(dslCode)

def evaluate(sizei, sizej):
	histogram = {}
	for ref in symbolicHist.keys():
		for i in range(32):
			if (i not in symbolicHist[ref].keys()):
				continue
			for j in range(32):
				if (j not in symbolicHist[ref][i].keys()):
					continue
				#print i, j, sizei, sizej, symbolicHist[ref][i][j]
				ri = int(evaluateSingleCode(i*(sizei/32), j*(sizej/32), sizei, sizej, symbolicHist[ref][i][j]))
				if (ri in histogram.keys()):
					histogram[ri] += 1
				else:
					histogram[ri] = 1
	return histogram
		
def readTraceFile(sizei, sizej):
	histogram = {}
	f = open("./histoToMatch/trangle_" + str(sizei) + "_" + str(sizej) + ".txt", 'r')
	for line in f:
		lineList = line.split()
		ri = int(lineList[4])
		if (ri in histogram.keys()):
			histogram[ri] += 1
		else:
			histogram[ri] = 1
	f.close()
	return histogram

def plotHistoToCompare(histogram_64_64_predicted, histogram_64_64_trace):
	sortedRi = sorted(histogram_64_64_predicted.keys())
	if (-1 in sortedRi): sortedRi.remove(-1)
	if (0 in sortedRi): sortedRi.remove(0)
	cnt = 0
	for x in sortedRi:
		cnt += histogram_64_64_predicted[x]
	plt.bar(sortedRi, [float(histogram_64_64_predicted[x]) / cnt for x in sortedRi], color = 'b', width = 0.4)

	sortedRi = sorted(histogram_64_64_trace.keys())
	if (-1 in sortedRi): sortedRi.remove(-1)
	if (0 in sortedRi): sortedRi.remove(0)
	cnt = 0
	for x in sortedRi:
		cnt += histogram_64_64_trace[x]
	plt.bar([x+0.5 for x in sortedRi], [float(histogram_64_64_trace[x]) / cnt for x in sortedRi], color = 'r', width = 0.4)
	
	plt.ylabel("Percentage")
	plt.xlabel("Reuse intervals")
	plt.show()
	return

path = "../synResult/"
files = os.listdir(path)

succeed = 0
total = 0

for name in files:
	f = open(path+name, 'r')
	total += 1
	for line in f:
		if ("(^0^)" in line):
			succeed += 1
			conf = name.replace("_result.txt", "")
			line.replace("\n","")
			prog = line[ line.find(':')+2 : len(line)].replace("\n","")
			recordSymRI(conf, prog)
		#if ("(T^T)" in line):
		#	print name.replace("_result.txt", ""), line.replace("\n","")
	f.close()

print "total", total, "succeed", succeed, float(succeed)/total, "failed", total-succeed, float(total-succeed)/total

histogram_64_64_predicted = evaluate(64, 64)
print histogram_64_64_predicted

histogram_64_64_trace = readTraceFile(64, 64)
print histogram_64_64_trace

plotHistoToCompare(histogram_64_64_predicted, histogram_64_64_trace)
