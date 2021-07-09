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

    plt.figure(figsize = (4, 3))
    
    sortedRi = sorted(histogram_src_predicted.keys())
    if (len(sortedRi) != 0):
        if (-1 in sortedRi): sortedRi.remove(-1)
        if (0 in sortedRi): sortedRi.remove(0)
        cnt = 0
        for x in sortedRi:
            cnt += histogram_src_predicted[x]
        plt.bar([x + 0.2 for x in sortedRi], [float(histogram_src_predicted[x]) / cnt for x in sortedRi], color = 'b', width = 0.2, alpha=0.3, label = "SrcOnly")

    sortedRi = sorted(histogram_srcEnhance_predicted.keys())
    if (len(sortedRi) != 0):
        if (-1 in sortedRi): sortedRi.remove(-1)
        if (0 in sortedRi): sortedRi.remove(0)
        cnt = 0
        for x in sortedRi:
            cnt += histogram_srcEnhance_predicted[x]
        plt.bar([x + 0.4 for x in sortedRi], [float(histogram_srcEnhance_predicted[x]) / cnt for x in sortedRi], color = 'y', width = 0.2, alpha=0.3, label = "SrcEnhanced")

    sortedRi = sorted(histogram_srcsnk_predicted.keys())
    if (len(sortedRi) != 0):
        if (-1 in sortedRi): sortedRi.remove(-1)
        if (0 in sortedRi): sortedRi.remove(0)
        cnt = 0
        for x in sortedRi:
            cnt += histogram_srcsnk_predicted[x]
        plt.bar([x + 0.6 for x in sortedRi], [float(histogram_srcsnk_predicted[x]) / cnt for x in sortedRi], color = 'g', width = 0.2, alpha=0.3, label = "SrcSnk")

    sortedRi = sorted(histogram_trace.keys())
    if (len(sortedRi) != 0):
        if (-1 in sortedRi): sortedRi.remove(-1)
        if (0 in sortedRi): sortedRi.remove(0)
        cnt = 0
        for x in sortedRi:
            cnt += histogram_trace[x]
        plt.bar(sortedRi, [float(histogram_trace[x]) / cnt for x in sortedRi], color = 'r', width = 0.2, alpha=0.3, label = "Trace")
    
    plt.ylabel("Percentage", fontsize = 16)
    plt.xlabel("Reuse Intervals", fontsize = 16)
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()
    plt.title(benchName + conf, fontsize = 16)
    plt.subplots_adjust(left=0.2, right = 0.98, top = 0.9, bottom = 0.2)
    plt.savefig("../figures/" + benchName + "_" + cacheConfig + "_RIHisto" + conf + ".pdf")
    plt.clf()
    return

def plotMRToCompare(histogram_src_predicted, histogram_srcEnhance_predicted, histogram_srcsnk_predicted, histogram_trace, benchName, cacheConfig, conf):
    
    mr_src_predicted = RItoMR(histogram_src_predicted)
    mr_srcEnhanced_predicted = RItoMR(histogram_srcEnhance_predicted)
    mr_srcsnk_predicted = RItoMR(histogram_srcsnk_predicted)
    
    mr_trace = RItoMR(histogram_trace)
    
    plt.figure(figsize = (4, 3))
    
    plt.plot(mr_src_predicted.keys(), [mr_src_predicted[x] for x in mr_src_predicted.keys()], color = 'b', label = "SrcOnly", alpha=0.3, linestyle = "--")
    plt.plot(mr_srcEnhanced_predicted.keys(), [mr_srcEnhanced_predicted[x] for x in mr_srcEnhanced_predicted.keys()], color = 'y', label = "SrcEnhanced", alpha=0.3, linestyle = "-.")
    plt.plot(mr_srcsnk_predicted.keys(), [mr_srcsnk_predicted[x] for x in mr_srcsnk_predicted.keys()], color = 'g', label = "SrcSnk", alpha=0.3, linestyle = ":")
    plt.plot(mr_trace.keys(), [mr_trace[x] for x in mr_trace.keys()], color = 'r', label = "Trace", alpha=0.3, linestyle = "-")

    plt.xlabel("Cache Size", fontsize = 9)
    plt.ylabel("Miss Ratio", fontsize = 9)
    plt.xscale("log")
    plt.legend()
    plt.title(benchName + conf, fontsize = 9)
    plt.subplots_adjust(left=0.13, right = 0.98, top = 0.93, bottom = 0.15)
    plt.savefig("../figures/" + benchName + "_" + cacheConfig + "_MR" + conf + ".pdf")
    plt.clf()
    
    return mr_src_predicted, mr_srcEnhanced_predicted, mr_srcsnk_predicted, mr_trace

def plotFigAll(all_mr_src, all_mr_srcEnhanced, all_mr_srcsnk, all_mr_trace):
    fig = plt.figure(figsize=(6,8))
    fig_cnt = 1
    
    benches = sorted(all_mr_src.keys())
    
    for benchName in benches:
        ax = fig.add_subplot(10, 3, fig_cnt)
        ax.set_title(benchName.replace("_","-"), fontsize = 10, y = 0.6, x = 0.6)
        l1 = ax.plot(all_mr_src[benchName].keys(), [all_mr_src[benchName][x] for x in all_mr_src[benchName].keys()], color = 'b', alpha=0.3, linestyle = '--')[0]
        l2 = ax.plot(all_mr_srcEnhanced[benchName].keys(), [all_mr_srcEnhanced[benchName][x] for x in all_mr_srcEnhanced[benchName].keys()], color = 'y', alpha=0.3, linestyle = '-.')[0]
        l3 = ax.plot(all_mr_srcsnk[benchName].keys(), [all_mr_srcsnk[benchName][x] for x in all_mr_srcsnk[benchName].keys()], color = 'g', alpha=0.3, linestyle = ':')[0]
        l4 = ax.plot(all_mr_trace[benchName].keys(), [all_mr_trace[benchName][x] for x in all_mr_trace[benchName].keys()], color = 'r', alpha=0.3, linestyle = '-')[0]
        ax.set_xscale('log')
        
        if (fig_cnt == 16):
            ax.set_ylabel('Miss Ratio', fontsize = 9, labelpad = 1)
        if (fig_cnt == 29):
            ax.set_xlabel('Cache Size (KB)', fontsize = 9, labelpad = 1)
        
        if (fig_cnt == 1):
            fig.legend([l1, l2, l3, l4], ["SrcOnly", "SrcEnhanced", "SrcSnk", "Trace"], ncol = 4, mode="expand", loc = "upper center")
        fig_cnt += 1
    
    
    plt.tight_layout(pad=0.4, w_pad=0.4, h_pad=-0.9)
    plt.subplots_adjust(left=0.09, right = 0.98, top = 0.95, bottom = 0.07)
    #plt.show()
    plt.savefig("../figures/allMR.pdf")
    return

