import os
import re
import matplotlib.pyplot as plt

# ref->[idx0, idx1, idx2, ...]->symRI
symbolicHist = {}

def recordSymRI(bench, conf, dslCode):
	conf = conf.replace(bench + "_ref_","")
	conf = conf.split("_iter_")
	ref_id = int(conf[0])

	idxs_str = conf[1].split("_")
	idxs = []
	
	for idx in idxs_str:
		idxs.append(int(idx))

	idxs = tuple(idxs)

	if (ref_id not in symbolicHist.keys()):
		symbolicHist[ref_id] = {}
	
	symbolicHist[ref_id][idxs] = dslCode
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

def evaluateSingleCode(scaled_idx, symBoundForPred, dslCode):

	#print dslCode
	dslCode = dslCode.replace("\n", "")
	for i in range(len(symBoundForPred)):
		dslCode = dslCode.replace("B" + str(i), str(symBoundForPred[i]))
	for i in range(len(scaled_idx)):
		dslCode = dslCode.replace("I" + str(i), str(scaled_idx[i]))
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

def scaleIndexByCodeStructure(idx):
	
	scaled_idx = []
	for i in idx:
		scaled_idx.append(i * 2)

	return scaled_idx

def evaluate(symBoundForPred):

	# should reverse the procedure

	histogram = {}
	'''
	numOfSymBound = len(symBoundForPred)

	totalNumberOfIdx = 1
	for bound in symBoundForPred:
		totalNumberOfIdx *= int(bound)

	symBoundForPredRev = symBoundForPred
	symBoundForPredRev.reverse()
	
	idxs = []
	
	print "totalNumberOfIdx", totalNumberOfIdx
	for i in range(totalNumberOfIdx):
		idx = [] 
		for bound in symBoundForPredRev:
			idx.append(i % bound)
			i = i / bound
		idx.reverse()
		idxs.append(tuple(idx))
	
	print "idxs", idxs
	'''
	for ref in symbolicHist.keys():
		for idx in symbolicHist[ref].keys():
			scaled_idx = scaleIndexByCodeStructure(idx)	
			ri = int(evaluateSingleCode(scaled_idx, symBoundForPred, symbolicHist[ref][idx]))
			if (ri in histogram.keys()):
				histogram[ri] += 1
			else:
				histogram[ri] = 1
	return histogram
		
def readTraceFile(name, symBoundValueForPred):
	histogram = {}

	fName = "./histoToMatch/" + name + "/" + name;
	for bound in symBoundValueForPred:
		fName += "_" + str(bound)
	fName += ".txt"

	f = open(fName, 'r')
	for line in f:
		lineList = line.split()
		ri = int(lineList[-1])
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
	plt.xscale('log')
	plt.show()
	return

def checkSingleBench(bench, path, numOfSymBounds):
	
	f = open(path, "r")	

	succeed = 0
	total = 0
	
	for line in f:
		conf = line[0 : line.find(' Prog:')]
		conf = conf.replace("_result.txt", "")	
		prog = line[line.find(' Prog:') + 7: len(line)]	
		recordSymRI(bench, conf, prog)

	f.close()

	#print symbolicHist
	if (total != 0):
		print "total", total, "succeed", succeed, float(succeed)/total, "failed", total-succeed, float(total-succeed)/total
	else:
		print "No Symbolic RI"

	symBoundValueForPred = [64] * numOfSymBounds
	print "start to predict the RI distribution for", symBoundValueForPred

	histogram_predicted = evaluate(symBoundValueForPred)
	print histogram_predicted

	histogram_trace = readTraceFile(bench, symBoundValueForPred)
	print histogram_trace
	
	plotHistoToCompare(histogram_predicted, histogram_trace)

	return

if __name__ == "__main__":

	path = "../synResult/all/"
	benches = os.listdir(path)

	numOfSymBounds = {"cholesky" : 1, "durbin" : 1, "floyd_warshall" : 1, "gemver" : 1, "gesummv" : 1, "lu" : 1, "ludcmp" : 1, "mvt" : 1, "nussinov" : 1, "stencil" : 1, "trisolv" : 1, "trangle" : 2, "adi" : 2, "atax" : 2, "bicg" : 2, "convolution_2d" : 2, "correlation" : 2, "covariance" : 2, "deriche" : 2, "gramschmidt" : 2, "heat_3d" : 2, "jacobi_1d" : 2, "jacobi_2d" : 2, "seidel_2d" : 2, "symm" : 2, "syr2d" : 2, "syrk" : 2, "trmm" : 2, "convolution_3d" : 3, "doitgen" : 3, "fdtd_2d" : 3, "gemm" : 3, "2mm" : 4, "3mm" : 5}

	for bench in benches:
		name = bench.replace(".txt", "")
		if (name == "cholesky"):
			checkSingleBench(name, path+bench, numOfSymBounds[name])
