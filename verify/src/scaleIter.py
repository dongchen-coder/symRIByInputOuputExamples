def scaleIter(idx, trainIBound, predIBound):
    scaled_idx = {}
    for i in range(len(idx)):
        if (predIBound[i][1] == None or trainIBound[i][1] == None):
            scaled_idx["Isrc" + str(i)] = idx[i]
        elif (predIBound[i][1] == 0 or trainIBound[i][1] == 0):
            scaled_idx["Isrc" + str(i)] = idx[i]
        else:
            scaled_idx["Isrc" + str(i)] = idx[i] * (predIBound[i][1] / trainIBound[i][1])
    return scaled_idx
