def scaleIter(idx, trainIBound, predIBound):
    scaled_idx = {}
    
    #print(idx, trainIBound, predIBound)
    
    if (len(trainIBound) != len(predIBound) or len(trainIBound) != len(idx)):
        for i in range(len(idx)):
            scaled_idx["isrc" + str(i)] = idx[i]
        return scaled_idx
    
    for i in range(len(idx)):
        if (predIBound[i][1] != None and predIBound[i][0] != None and predIBound[i][1] != "X" and predIBound[i][0] != "X" and trainIBound[i][1] != trainIBound[i][0]):
            scaled_idx["isrc" + str(i)] = predIBound[i][0] + (predIBound[i][1] - predIBound[i][0]) * (idx[i] - trainIBound[i][0]) / (trainIBound[i][1] - trainIBound[i][0])
        elif (predIBound[i][1] != None and predIBound[i][1] != "X" and trainIBound[i][1] != 0):
            scaled_idx["isrc" + str(i)] = idx[i] * (predIBound[i][1] / trainIBound[i][1])
        else:
            scaled_idx["isrc" + str(i)] = idx[i]
    
    return scaled_idx
