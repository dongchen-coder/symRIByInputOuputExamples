import re

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
            #print("eval true", value)
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
        #print("eval false", value)
        return evaluateIfStatement(value)

def evaluateSingleCode(idx, symBoundForPred, dslCode):
    
    #print(idx, symBoundForPred, dslCode)
 
    dslCode = dslCode.replace("\n", "")
    for i in range(len(symBoundForPred)):
        dslCode = dslCode.replace("b" + str(i), str(symBoundForPred[i]))
    for i in idx.keys():
        dslCode = dslCode.replace(i, str(idx[i]))
    dslCode = dslCode.replace("!", "not")
    dslCode = dslCode.replace("&&", "and")
    dslCodeList = re.split('if | then | else ', dslCode)

    #print(dslCode)
    #print(dslCodeList)

    #if (len(dslCodeList) > 4): 
    #    print(dslCode)
    #    print(dslCodeList)
    
    dslCodeList = [removeUnbalancedParenthesis(x) for x in dslCodeList]
    dslCodeListValue = []

    #print(dslCodeList)

    for term in dslCodeList:
        if term == "" or term == " " or term == "    ":
            dslCodeListValue.append("")
            continue
        result = eval(term)
        dslCodeListValue.append(result)
    
    #print(dslCodeListValue)

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

    #print(dslCode)

    #if (evaluateIfStatement(dslCode) == None):
    #    print(dslCode)
    #    print(dslCodeList)
    #    print(dslCodeListValue)
    #    print(evaluateIfStatement(dslCode))

    return evaluateIfStatement(dslCode)
