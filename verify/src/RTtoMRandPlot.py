import matplotlib.pyplot as plt

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

def plotHistoToCompare(histogram_src_predicted, histogram_srcEnhance_predicted, histogram_srcsnk_predicted, histogram_trace, benchName, cacheConfig, conf):
    sortedRi = sorted(histogram_src_predicted.keys())
    if (len(sortedRi) != 0):
        if (-1 in sortedRi): sortedRi.remove(-1)
        if (0 in sortedRi): sortedRi.remove(0)
        cnt = 0
        for x in sortedRi:
            cnt += histogram_src_predicted[x]
        plt.bar(sortedRi, [float(histogram_src_predicted[x]) / cnt for x in sortedRi], color = 'b', width = 0.4, alpha=0.3, label = "SymbolicRI-SRC")

    sortedRi = sorted(histogram_srcEnhance_predicted.keys())
    if (len(sortedRi) != 0):
        if (-1 in sortedRi): sortedRi.remove(-1)
        if (0 in sortedRi): sortedRi.remove(0)
        cnt = 0
        for x in sortedRi:
            cnt += histogram_srcEnhance_predicted[x]
        plt.bar(sortedRi, [float(histogram_srcEnhance_predicted[x]) / cnt for x in sortedRi], color = 'y', width = 0.4, alpha=0.3, label = "SymbolicRI-SRCENHANCE")

    sortedRi = sorted(histogram_srcsnk_predicted.keys())
    if (len(sortedRi) != 0):
        if (-1 in sortedRi): sortedRi.remove(-1)
        if (0 in sortedRi): sortedRi.remove(0)
        cnt = 0
        for x in sortedRi:
            cnt += histogram_srcsnk_predicted[x]
        plt.bar(sortedRi, [float(histogram_srcsnk_predicted[x]) / cnt for x in sortedRi], color = 'g', width = 0.4, alpha=0.3, label = "SymbolicRI-SRCSNK")

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
    plt.title(benchName + conf)
    plt.savefig("../visualCompare/" + benchName + "_" + cacheConfig + "_RIHisto" + conf + ".pdf")
    plt.clf()
    return

def plotMRToCompare(histogram_src_predicted, histogram_srcEnhance_predicted, histogram_srcsnk_predicted, histogram_trace, benchName, cacheConfig, conf):
    
    mr_src_predicted = RItoMR(histogram_src_predicted)
    mr_srcEnhanced_predicted = RItoMR(histogram_srcEnhance_predicted)
    mr_srcsnk_predicted = RItoMR(histogram_srcsnk_predicted)
    
    mr_trace = RItoMR(histogram_trace)

    plt.plot(mr_src_predicted.keys(), [mr_src_predicted[x] for x in mr_src_predicted.keys()], color = 'b', label = "SymbolibRI-SRC->MR", alpha=0.3)
    plt.plot(mr_srcEnhanced_predicted.keys(), [mr_srcEnhanced_predicted[x] for x in mr_srcEnhanced_predicted.keys()], color = 'y', label = "SymbolicRI-SRCENHANCE->MR", alpha=0.3)
    plt.plot(mr_srcsnk_predicted.keys(), [mr_srcsnk_predicted[x] for x in mr_srcsnk_predicted.keys()], color = 'g', label = "SymbolibRI-SRCSNK->MR", alpha=0.3)
    plt.plot(mr_trace.keys(), [mr_trace[x] for x in mr_trace.keys()], color = 'r', label = "TraceRI->MR", alpha=0.3)

    plt.xlabel("Cache Size")
    plt.ylabel("Miss Ratio")
    plt.xscale("log")
    plt.legend()
    plt.title(benchName + conf)
    plt.savefig("../visualCompare/" + benchName + "_" + cacheConfig + "_MR" + conf + ".pdf")
    plt.clf()
    return
