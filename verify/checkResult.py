import os
import re
import matplotlib.pyplot as plt

# ref->[idx0, idx1, idx2, ...]->symRI
symbolicHist = {}

def recordSymRI(bench, conf, dslCode):
	if ("_refsnk_" in conf):
		conf = conf.replace(bench + "_refsrc_", "")
		conf = conf.replace("_refsnk_", " ")
		conf = conf.replace("_iter_", " ")
		conf = conf.split(" ")
		
		ref_src_id = int(conf[0])
		ref_snk_id = int(conf[1])
		idxs_str = conf[2].split("_")
		idxs = []
		for idx in idxs_str:
			idxs.append(int(idx))
		idxs = tuple(idxs)
	else:
		conf = conf.replace(bench + "_refsrc_","")
		conf = conf.replace("_iter_", " ")
		conf = conf.split(" ")
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

def RItoMR(riHisto):
	maxRI = 0
	totalNumRI = 0
	for ri in riHisto.keys():
		if (maxRI < ri):
			maxRI = ri
		totalNumRI += riHisto[ri]

	accumulateNumRI = 0.0
	
	riSortedReverse = sorted(riHisto.keys())
	riSortedReverse.reverse()
	P = {}
	for ri in riSortedReverse:
		P[ri] = accumulateNumRI / totalNumRI
		accumulateNumRI += riHisto[ri]
	P[0] = 1
	
	sumP = 0.0
	t = 0
	prev_t = 0
	MR_pred = -1
	MR = {}
	for c in range(maxRI+1):
		while(sumP < c and t <= maxRI):
			if (t in P):
				sumP += P[t]
				prev_t = t
			else:
				sumP += P[prev_t]
			t += 1
		if (MR_pred != -1):
			MR[c] = P[prev_t]
			MR_pred = P[prev_t]
		else:
			if (MR_pred - P[prev_t] < 0.0001):
				MR[c] = P[prev_t]
				MR_pred = P[prev_t]
	
	return MR

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

def evaluate(symbolicHistToUse, symBoundForPred, method):

	histogram = {}
	
	if (method == "src"):
		for ref in symbolicHistToUse.keys():
			for idx in symbolicHistToUse[ref].keys():
				scaled_idx = scaleIndexByCodeStructure(idx)	
				ri = int(evaluateSingleCode(scaled_idx, symBoundForPred, symbolicHistToUse[ref][idx]))
				if (ri in histogram.keys()):
					histogram[ri] += 1
				else:
					histogram[ri] = 1
	if (method == "srcsnk"):
		for ref in symbolicHistToUse.keys():
			for idx in symbolicHistToUse[ref].keys():
				scaled_idx = scaleIndexByCodeStructure(idx) 
				ri = int(evaluateSingleCode(scaled_idx, symBoundForPred, symbolicHistToUse[ref][idx]))
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

def plotHistoToCompare(histogram_src_predicted, histogram_srcsnk_predicted, histogram_trace, bench, conf):
	sortedRi = sorted(histogram_src_predicted.keys())
	if (len(sortedRi) != 0):
		if (-1 in sortedRi): sortedRi.remove(-1)
		if (0 in sortedRi): sortedRi.remove(0)
		cnt = 0
		for x in sortedRi:
			cnt += histogram_src_predicted[x]
		plt.bar(sortedRi, [float(histogram_src_predicted[x]) / cnt for x in sortedRi], color = 'b', width = 0.4, alpha=0.3, label = "SymbolicRI-SRC")

	sortedRi = sorted(histogram_srcsnk_predicted.keys())
	if (len(sortedRi) != 0):
		if (-1 in sortedRi): sortedRi.remove(-1)
		if (0 in sortedRi): sortedRi.remove(0)
		cnt = 0
		for x in sortedRi:
			cnt += histogram_srcsnk_predicted[x]
		plt.bar(sortedRi, [float(histogram_srcsnk_predicted[x]) / cnt for x in sortedRi], color = 'b', width = 0.4, alpha=0.3, label = "SymbolicRI-SRCSNK")

	sortedRi = sorted(histogram_trace.keys())
	if (len(sortedRi) != 0):
		if (-1 in sortedRi): sortedRi.remove(-1)
		if (0 in sortedRi): sortedRi.remove(0)
		cnt = 0
		for x in sortedRi:
			cnt += histogram_trace[x]
		plt.bar(sortedRi, [float(histogram_trace[x]) / cnt for x in sortedRi], color = 'r', width = 0.4, alpha=0.3, label = "Trace")
	
	plt.ylabel("Percentage")
	plt.xlabel("Reuse intervals")
	plt.xscale('log')
	plt.yscale('log')
	plt.legend()
	plt.title(bench + conf)
	plt.savefig("./visualCompare/" + bench + conf + "_RIHisto" + ".pdf")
	plt.clf()
	return

def plotMRToCompare(mr_src_predicted, mr_srcsnk_predicted, mr_trace, bench, conf):

	plt.plot(mr_src_predicted.keys(), [mr_src_predicted[x] for x in mr_src_predicted.keys()], color = 'b', label = "SymbolibRI-SRC->MR", alpha=0.3)
	plt.plot(mr_srcsnk_predicted.keys(), [mr_srcsnk_predicted[x] for x in mr_srcsnk_predicted.keys()], color = 'b', label = "SymbolibRI-SRCSNK->MR", alpha=0.3)
	plt.plot(mr_trace.keys(), [mr_trace[x] for x in mr_trace.keys()], color = 'r', label = "TraceRI->MR", alpha=0.3)

	plt.xlabel("Cache Size")
	plt.ylabel("Miss Ratio")
	plt.xscale("log")
	plt.legend()
	plt.title(bench + conf)
	plt.savefig("./visualCompare/" + bench + conf + "_MR" + ".pdf")
	plt.clf()
	return

def checkSingleBench(benchName, path, numOfSymBounds, symBoundValueForPred):
	
	f_src = open(path + benchName + "_src.txt", "r")	
	f_srcsnk = open(path + benchName + "_srcsnk.txt", "r")

	for line in f_src:
		conf = line[0 : line.find(' Prog:')]
		conf = conf.replace("_src_result.txt", "")	
		prog = line[line.find(' Prog:') + 7: len(line)]	
		recordSymRI(benchName, conf, prog)
	f_src.close()
	symbolicHistSrc = dict(symbolicHist)
	symbolicHist.clear()

	for line in f_srcsnk:
		conf = line[0 : line.find(' Prog:')]
		conf = conf.replace("_srcsnk_result.txt", "")  
		prog = line[line.find(' Prog:') + 7: len(line)]
		recordSymRI(benchName, conf, prog)
	f_srcsnk.close()
	symbolicHistSrcsnk = symbolicHist
	symbolicHist.clear()

	confs = []

	if (numOfSymBounds <= 1):
		for conf in symBoundValueForPred:
			confs.append("_" + str(conf))
	else:
		for conf in symBoundValueForPred:
			confs.append("_" + str(conf))
		for i in range(numOfSymBounds - 1):
			confs_new = []
			for conf in confs:
				for bound in symBoundValueForPred:
					confs_new.append(conf + "_" + str(bound))

	for conf in confs:
		print "start to predict the RI distribution for ", conf

		boundValueForPredStr = conf.split("_")
		boundValueForPred = []
		for boundValue in boundValueForPredStr:
			if (boundValue != ""):
				boundValueForPred.append(int(boundValue))
		print boundValueForPred
		
		histogram_src_predicted = evaluate(symbolicHistSrc, boundValueForPred, "src")
		if (0 in histogram_src_predicted.keys()):
			del histogram_src_predicted[0]
		print "histogram_src_predicted", histogram_src_predicted

		histogram_srcsnk_predicted = evaluate(symbolicHistSrc, boundValueForPred, "srcsnk")
		if (0 in histogram_srcsnk_predicted.keys()):
			del histogram_srcsnk_predicted[0]
		print "histogram_srcsnk_predicted", histogram_srcsnk_predicted

		histogram_trace = readTraceFile(benchName, boundValueForPred)
		if (0 in histogram_trace.keys()):
			del histogram_trace[0]
		print "histogram_trace", histogram_trace
	
		plotHistoToCompare(histogram_src_predicted, histogram_srcsnk_predicted, histogram_trace, benchName, conf)
		
		mr_src_predicted = RItoMR(histogram_src_predicted)
		mr_srcsnk_predicted = RItoMR(histogram_srcsnk_predicted)
		mr_trace = RItoMR(histogram_trace)
		plotMRToCompare(mr_src_predicted, mr_srcsnk_predicted, mr_trace, benchName, conf)

	return

if __name__ == "__main__":

	path = "../synResult/all/"

	numOfSymBounds = {"cholesky" : 1, "durbin" : 1, "floyd_warshall" : 1, "gemver" : 1, "gesummv" : 1, "lu" : 1, "ludcmp" : 1, "mvt" : 1, "nussinov" : 1, "stencil" : 1, "trisolv" : 1, "trangle" : 2, "adi" : 2, "atax" : 2, "bicg" : 2, "convolution_2d" : 2, "correlation" : 2, "covariance" : 2, "deriche" : 2, "gramschmidt" : 2, "heat_3d" : 2, "jacobi_1d" : 2, "jacobi_2d" : 2, "seidel_2d" : 2, "symm" : 2, "syr2d" : 2, "syrk" : 2, "trmm" : 2, "convolution_3d" : 3, "doitgen" : 3, "fdtd_2d" : 3, "gemm" : 3, "2mm" : 4, "3mm" : 5}

	symBoundValueForPred = [64, 128, 256]  
	
	for benchName in numOfSymBounds.keys():
		#if (benchName == "stencil"):
		checkSingleBench(benchName, path, numOfSymBounds[benchName], symBoundValueForPred)
