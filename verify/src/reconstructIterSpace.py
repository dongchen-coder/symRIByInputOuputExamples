from evaluate import *
import itertools

def is_Int(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

def reconstructIterSpace(symBounds, boundValueForPred):
    iterSpaceMinMax = []
    for key in symBounds.keys():
        minMax = []
        minMax.append( evaluateSingleCode({}, boundValueForPred, symBounds[key][0]) )
        minMax.append( evaluateSingleCode({}, boundValueForPred, symBounds[key][1]) )
        iterSpaceMinMax.append(minMax)
    
    iterSpaceSingleDimension = []
    for item in iterSpaceMinMax:
        iterSpaceSingleDimension.append( range(int(item[0]), int(item[1])) )

    iterSpace = []
    for singleDimension in iterSpaceSingleDimension:
        if (iterSpace == []):
            for item in singleDimension:
                iterSpace.append([item])
        else:
            iterSpace_new = []
            for item in singleDimension:
                for point in iterSpace:
                    iterSpace_new.append(point + [item])
            iterSpace = list(iterSpace_new)
    
    return iterSpace

def getRangeForEachDimension(symBounds, boundValue):

    iterSpaceMinMax = []
    for key in symBounds.keys():
        minMax = []
        minMax.append( evaluateSingleCode({}, boundValue, symBounds[key][0]) )
        minMax.append( evaluateSingleCode({}, boundValue, symBounds[key][1]) )
        
        if (is_Int(minMax[0])):
            minMax[0] = int(minMax[0])
        else:
            minMax[0] = None
        if (is_Int(minMax[1])):
            minMax[1] = int(minMax[1])
        else:
            minMax[1] = None
        
        iterSpaceMinMax.append(minMax)

    return iterSpaceMinMax
