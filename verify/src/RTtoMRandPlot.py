import matplotlib.pyplot as plt
import numpy as np

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

def plotHistoToCompare(histogram_src_predicted, histogram_src_snk_predicted, histogram_src_snk_plus_predicted, histogram_trace, benchName, cacheConfig, conf):

    plt.figure(figsize = (4, 2))    
    mergedRi = sorted(list(histogram_src_predicted.keys()) + list(histogram_src_snk_predicted.keys()) + list(histogram_src_snk_plus_predicted.keys()) + list(histogram_trace.keys()))
    mergedRi = list(set(mergedRi))
    if (-1 in mergedRi): mergedRi.remove(-1)
    if (0 in mergedRi): mergedRi.remove(0)
    sortedMergedRi = sorted(mergedRi)

    cnt = 0
    for x in sortedMergedRi:
        if (x in histogram_src_predicted.keys()):
            cnt += histogram_src_predicted[x]
    histogram_src_predicted_merged = [(float(histogram_src_predicted[x]) / cnt if x in histogram_src_predicted else 0) for x in sortedMergedRi]

    cnt = 0
    for x in sortedMergedRi:
        if (x in histogram_src_snk_predicted.keys()):
            cnt += histogram_src_snk_predicted[x]
    histogram_src_snk_predicted_merged = [(float(histogram_src_snk_predicted[x]) / cnt if x in histogram_src_snk_predicted else 0) for x in sortedMergedRi]

    cnt = 0
    for x in sortedMergedRi:
        if (x in histogram_src_snk_plus_predicted.keys()):
            cnt += histogram_src_snk_plus_predicted[x]
    histogram_src_snk_plus_predicted_merged = [(float(histogram_src_snk_plus_predicted[x]) / cnt if x in histogram_src_snk_plus_predicted else 0) for x in sortedMergedRi]

    cnt = 0
    for x in sortedMergedRi:
        if (x in histogram_trace.keys()):
            cnt += histogram_trace[x]
    histogram_trace_merged = [(float(histogram_trace[x]) / cnt if x in histogram_trace else 0) for x in sortedMergedRi]

    if (len(sortedMergedRi) != 0):
        plt.bar([x + 0.2 for x in range(len(sortedMergedRi))], histogram_src_predicted_merged, color = '#e66101', width = 0.2, alpha=0.3, label = "src")
        plt.bar([x + 0.4 for x in range(len(sortedMergedRi))], histogram_src_snk_predicted_merged, color = '#fdb863', width = 0.2, alpha=0.3, label = "src-snk")
        plt.bar([x + 0.6 for x in range(len(sortedMergedRi))], histogram_src_snk_plus_predicted_merged, color = '#b2abd2', width = 0.2, alpha=0.3, label = "src-snk+")
        plt.bar([x + 0.8 for x in range(len(sortedMergedRi))], histogram_trace_merged, color = '#5e3c99', width = 0.2, alpha=0.3, label = "trace")
    
    plt.xticks([x + 0.5 for x in range(len(sortedMergedRi))], sortedMergedRi, rotation=45, fontsize=9)
    plt.ylabel("Percentage", fontsize = 9)
    plt.xlabel("Reuse Intervals", fontsize = 9)
    plt.legend(fontsize = 9)
    plt.title(benchName + conf, fontsize = 9)
    plt.subplots_adjust(left=0.13, right = 0.99, top = 0.99, bottom = 0.3)
    plt.savefig("../figures/" + benchName + "_" + cacheConfig + "_RIHisto" + conf + ".pdf")
    plt.clf()
    return

def plotHistoAllBars(histogram_src_predicted, histogram_srcEnhance_predicted, histogram_srcsnk_predicted, histogram_trace, benchName, cacheConfig, conf):

    fig, ax = plt.subplots(figsize = (4, 1.5))    

    ri_src = histogram_src_predicted.keys()
    ri_srcsnk = histogram_srcEnhance_predicted.keys()
    ri_srcsnkplus = histogram_srcsnk_predicted.keys()
    ri_trace = histogram_trace.keys()
    
    all_ri = set(list(ri_src) + list(ri_srcsnk) + list(ri_srcsnkplus) + list(ri_trace))
    if (-1 in all_ri): all_ri.remove(-1)
    if (0 in all_ri): all_ri.remove(0)
    all_ri = sorted(all_ri)

    X = np.arange(len(all_ri))

    if (len(ri_src) != 0):
        cnt = 0
        for x in ri_src:
            if (x > 0):
                cnt += histogram_src_predicted[x]
        percentage = []
        for x in all_ri:
            if (x in ri_src):
                percentage.append(float(histogram_src_predicted[x]) / cnt)
            else:
                percentage.append(0)
        ax.bar(X + 0.00, percentage, color = '#e66101', width = 0.25, label = "src")
    
    if (len(ri_srcsnk) != 0):
        cnt = 0
        for x in ri_srcsnk:
            if (x > 0):
                cnt += histogram_srcEnhance_predicted[x]
        percentage = []
        for x in all_ri:
            if (x in ri_srcsnk):
                percentage.append(float(histogram_srcEnhance_predicted[x]) / cnt)
            else:
                percentage.append(0)
        ax.bar(X + 0.25, percentage, color = '#fdb863', width = 0.25, label = "src-snk")
    
    if (len(ri_srcsnkplus) != 0):
        cnt = 0
        for x in ri_srcsnkplus:
            cnt += histogram_srcsnk_predicted[x]
        percentage = []
        for x in all_ri:
            if (x in ri_srcsnkplus):
                percentage.append(float(histogram_srcsnk_predicted[x]) / cnt)
            else:
                percentage.append(0)
        ax.bar(X + 0.50, percentage, color = '#b2abd2', width = 0.25, label = "src-snk+")

    if (len(ri_trace) != 0):
        cnt = 0
        for x in ri_trace:
            cnt += histogram_trace[x]
        percentage = []
        for x in all_ri:
            if (x in ri_trace):
                percentage.append(float(histogram_trace[x]) / cnt)
            else:
                percentage.append(0)
        ax.bar(X + 0.75, percentage, color = '#5e3c99', width = 0.25, label = "trace")
    
    ax.set_xticks(X)    
    ax.set_xticklabels(all_ri, rotation = 60, fontsize = 10)

    ax.set_ylabel("Percentage", fontsize = 9)
    ax.set_xlabel("Reuse Intervals", fontsize = 9)
    #ax.set_yscale('log')
    ax.legend(fontsize = 9)
    #ax.set_title(benchName + conf, fontsize = 10)
    plt.subplots_adjust(left=0.13, right = 0.99, top = 0.99, bottom = 0.3)
    plt.savefig("../figures/" + benchName + "_" + cacheConfig + "_RIH_" + conf + ".pdf")
    plt.clf()
    return

def plotMRToCompare(histogram_src_predicted, histogram_srcEnhance_predicted, histogram_srcsnk_predicted, histogram_trace, benchName, cacheConfig, conf):
    
    mr_src_predicted = RItoMR(histogram_src_predicted)
    mr_srcEnhanced_predicted = RItoMR(histogram_srcEnhance_predicted)
    mr_srcsnk_predicted = RItoMR(histogram_srcsnk_predicted)
    
    mr_trace = RItoMR(histogram_trace)

    #print("mr src", mr_src_predicted)
    #print("mr srcsnk", mr_srcEnhanced_predicted)
    #print("mr srcsnk+ ", mr_srcsnk_predicted)
    #print("mr trace ", mr_trace)
    
    plt.figure(figsize = (4, 2))
    
    plt.plot(mr_src_predicted.keys(), [mr_src_predicted[x] for x in mr_src_predicted.keys()], color = '#e66101', label = "src", alpha=0.3, linestyle = "--", linewidth=1)
    plt.plot(mr_srcEnhanced_predicted.keys(), [mr_srcEnhanced_predicted[x] for x in mr_srcEnhanced_predicted.keys()], color = '#fdb863', label = "src-snk", alpha=0.3, linestyle = "-.", linewidth=1)
    plt.plot(mr_srcsnk_predicted.keys(), [mr_srcsnk_predicted[x] for x in mr_srcsnk_predicted.keys()], color = '#b2abd2', label = "src-snk+", alpha=0.3, linestyle = ":", linewidth=1)
    plt.plot(mr_trace.keys(), [mr_trace[x] for x in mr_trace.keys()], color = '#5e3c99', label = "trace", alpha=0.3, linestyle = "-", linewidth=1)

    plt.xlabel("Cache Size", fontsize = 9)
    plt.ylabel("Miss Ratio", fontsize = 9)
    plt.xscale("log")
    plt.legend(fontsize = 9)
    #plt.title(benchName + conf, fontsize = 9)
    plt.subplots_adjust(left=0.13, right = 0.99, top = 0.99, bottom = 0.3)
    plt.savefig("../figures/" + benchName + "_" + cacheConfig + "_MR" + conf + ".pdf")
    plt.clf()
    
    return mr_src_predicted, mr_srcEnhanced_predicted, mr_srcsnk_predicted, mr_trace

def plotFigAll(all_mr_src, all_mr_srcEnhanced, all_mr_srcsnk, all_mr_trace, all_predicted_mr_falcon, skipped_benches):
    fig = plt.figure(figsize=(6,8))
    fig_cnt = 1
    
    benches = sorted(all_mr_src.keys())
    
    for benchName in benches:
        if (benchName in skipped_benches):
            continue
        ax = fig.add_subplot(10, 3, fig_cnt)
        ax.set_title(benchName.replace("_","-"), fontsize = 10, y = 0.6, x = 0.6)
        l1 = ax.plot(all_mr_src[benchName].keys(), [all_mr_src[benchName][x] for x in all_mr_src[benchName].keys()], color = '#e66101', alpha=0.3, linestyle = '--')[0]
        l2 = ax.plot(all_mr_srcEnhanced[benchName].keys(), [all_mr_srcEnhanced[benchName][x] for x in all_mr_srcEnhanced[benchName].keys()], color = '#fdb863', alpha=0.3, linestyle = '-.')[0]
        l3 = ax.plot(all_mr_srcsnk[benchName].keys(), [all_mr_srcsnk[benchName][x] for x in all_mr_srcsnk[benchName].keys()], color = '#b2abd2', alpha=0.3, linestyle = ':')[0]
        l4 = ax.plot(all_mr_trace[benchName].keys(), [all_mr_trace[benchName][x] for x in all_mr_trace[benchName].keys()], color = '#5e3c99', alpha=0.3, linestyle = '-')[0]
        x_values = list(all_predicted_mr_falcon[benchName].keys())
        y_values = [all_predicted_mr_falcon[benchName][x] for x in x_values]
        l5 = ax.plot(x_values, y_values, 'o', color='#d73027', markersize=2)[0]

        plt.xscale("log")
        if (fig_cnt == 16):
            ax.set_ylabel('Miss Ratio', fontsize=9, labelpad=1)
        if (fig_cnt == 29):
            ax.set_xlabel('Cache Size (KB)', fontsize=9, labelpad=1)

        if (fig_cnt == 1):
            fig.legend([l1, l2, l3, l4, l5], ["src", "src-snk", "src-snk+", "trace", "falcon"], ncol=5, mode="expand", loc="upper center")
        fig_cnt += 1

    plt.tight_layout(pad=0.4, w_pad=0.4, h_pad=0.5)
    plt.subplots_adjust(left=0.09, right=0.98, top=0.95, bottom=0.07, hspace=0.5)
    plt.savefig("../figures/allMR.pdf")
    return

