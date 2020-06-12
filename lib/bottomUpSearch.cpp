#include "bottomUpSearch.hpp"
/******************************************
    Dump Program list
*/
string dumpProgram(BaseType* p) {
    if (dynamic_cast<Var*>(p) != 0) {
        Var* var = dynamic_cast<Var*>(p);
        return var->toString();
    }
    if (dynamic_cast<Num*>(p) != 0) {
        Num* num = dynamic_cast<Num*>(p);
        return num->toString();
    }
    if (dynamic_cast<F*>(p) != 0) {
        F* f = dynamic_cast<F*>(p);
        return f->toString();
    }
    if (dynamic_cast<Plus*>(p) != 0) {
        Plus* plus = dynamic_cast<Plus*>(p);
        return plus->toString();
    }
    if (dynamic_cast<Times*>(p) != 0) {
        Times* times = dynamic_cast<Times*>(p);
        return times->toString();
    }
    if (dynamic_cast<Lt*>(p) != 0) {
        Lt* lt = dynamic_cast<Lt*>(p);
        return lt->toString();
    }
    if (dynamic_cast<And*>(p) != 0) {
        And* a = dynamic_cast<And*>(p);
        return a->toString();
    }
    if (dynamic_cast<Not*>(p) != 0) {
        Not* n = dynamic_cast<Not*>(p);
        return n->toString();
    }
    if (dynamic_cast<Ite*>(p) != 0) {
        Ite* ite = dynamic_cast<Ite*>(p);
        return ite->toString();
    }
    return "";
}

void dumpPlist(vector<BaseType*> pList) {
    cout << "[";
    for (int i = 0; i < pList.size(); i++) {
        cout << dumpProgram(pList[i]);
        if (i + 1 < pList.size()) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    return;
}

/******************************************
    Grow program list
*/
BaseType* growOneExpr(BaseType* i, BaseType* j, BaseType* k, string op, int depthBound) {
    if (op == "PLUS") {
        if (dynamic_cast<IntType*>(i) != 0 && dynamic_cast<IntType*>(j) != 0) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            if (inti->depth() < depthBound && intj->depth() < depthBound) {
                Plus* plus = new Plus(inti, intj);
                return dynamic_cast<BaseType*>(plus);
            }
        }
    }
    if (op == "TIMES") {
        if (dynamic_cast<IntType*>(i) != 0 && dynamic_cast<IntType*>(j) != 0) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            if (inti->depth() < depthBound && intj->depth() < depthBound) {
                Times* times = new Times(inti, intj);
                return dynamic_cast<BaseType*>(times);
            }
        }
    }
    if (op == "ITE") {
        if (dynamic_cast<BoolType*>(i) != 0 && dynamic_cast<IntType*>(j) != 0 && dynamic_cast<IntType*>(k) != 0) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            IntType* intk = dynamic_cast<IntType*>(k);
            if (booli->depth() < depthBound && intj->depth() < depthBound && intk->depth() < depthBound) {
                Ite* ite = new Ite(booli, intj, intk);
                return dynamic_cast<BaseType*>(ite);
            }
        }
    }
    
    if (op == "F") {
        F* f = new F();
        return dynamic_cast<BaseType*>(f);
    }
    
    if (op == "NOT") {
        if (dynamic_cast<BoolType*>(i) != 0) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            if (booli->depth() < depthBound) {
                Not* n = new Not(booli);
                return dynamic_cast<BaseType*>(n);
            }
        }
    }
    
    if (op == "AND") {
        if (dynamic_cast<BoolType*>(i) != 0 && dynamic_cast<BoolType*>(j) != 0) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            BoolType* boolj = dynamic_cast<BoolType*>(j);
            if (booli->depth() < depthBound && boolj->depth() < depthBound) {
                And* a = new And(booli, boolj);
                return dynamic_cast<BaseType*>(a);
            }
        }
    }
    
    if (op == "LT") {
        if (dynamic_cast<IntType*>(i) != 0 && dynamic_cast<IntType*>(j) != 0) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            if (inti->depth() < depthBound && intj->depth() < depthBound) {
                Lt* lt = new Lt(inti, intj);
                return dynamic_cast<BaseType*>(lt);
            }
        }
    }
    return NULL;
}


vector<BaseType*> grow(vector<string> intOps,
                       vector<string> boolOps,
                       vector<BaseType*> pList,
                       int depthBound) {
    
    vector<BaseType*> newPList;
    
    for (int i = 0; i < intOps.size(); i++) {
        string op = intOps[i];
        if (op == "PLUS" || op == "TIMES") {
            for (int j = 0; j < pList.size(); j++) {
                for (int k = 0; k < pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(pList[j], pList[k], NULL, op, depthBound);
                    if (newExpr != NULL) {
                        newPList.push_back(newExpr);
                    }
                }
            }
        }
        if (op == "ITE") {
            for (int j = 0; j < pList.size(); j++) {
                for (int k = 0; k < pList.size(); k++) {
                    for (int l = 0; l < pList.size(); l++) {
                        BaseType* newExpr = growOneExpr(pList[j], pList[k], pList[l], op, depthBound);
                        if (newExpr != NULL) {
                            newPList.push_back(newExpr);
                        }
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < boolOps.size(); i++) {
        string op = boolOps[i];
        if (op == "F") {
            BaseType* newExpr = growOneExpr(NULL, NULL, NULL, op, depthBound);
            if (newExpr != NULL) {
                newPList.push_back(newExpr);
            }
        }
        if (op == "NOT") {
            for (int j = 0; j < pList.size(); j++) {
                BaseType* newExpr = growOneExpr(pList[j], NULL, NULL, op, depthBound);
                if (newExpr != NULL) {
                    newPList.push_back(newExpr);
                }
            }
        }
        if (op == "AND" || op == "LT") {
            for (int j = 0; j < pList.size(); j++) {
                for (int k = 0; k < pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(pList[j], pList[k], NULL, op, depthBound);
                    if (newExpr != NULL) {
                        newPList.push_back(newExpr);
                    }
                }
            }
        }
    }
    
    pList.insert(pList.end(), newPList.begin(), newPList.end());
    return pList;
}

/******************************************
    Eliminate equvalent programs
*/
map<pair<BaseType*, int>, int> intResultRecord;
int executeIntProgram(BaseType* p, map<string, int> inputOutput, int inputOutputId) {
    
    if (intResultRecord.find(make_pair(p, inputOutputId)) != intResultRecord.end()) {
        return intResultRecord[make_pair(p, inputOutputId)];
    }
    
    int pValue;
    if (dynamic_cast<Num*>(p)) {
        Num* num = dynamic_cast<Num*>(p);
        pValue = num->interpret();
    }
    if (dynamic_cast<Var*>(p)) {
        Var* var = dynamic_cast<Var*>(p);
        pValue = var->interpret(inputOutput);
    }
    if (dynamic_cast<Plus*>(p)) {
        Plus* plus = dynamic_cast<Plus*>(p);
        pValue = plus->interpret(inputOutput);
    }
    if (dynamic_cast<Times*>(p)) {
        Times* times = dynamic_cast<Times*>(p);
        pValue = times->interpret(inputOutput);
    }
    if (dynamic_cast<Ite*>(p)) {
        Ite* ite = dynamic_cast<Ite*>(p);
        pValue = ite->interpret(inputOutput);
    }
    
    intResultRecord[make_pair(p, inputOutputId)] = pValue;
    return pValue;
}

map<pair<BaseType*, int>, bool> boolResultRecord;
bool executeBoolProgram(BaseType* p, map<string, int> inputOutput, int inputOutputId) {
    if (boolResultRecord.find(make_pair(p, inputOutputId)) != boolResultRecord.end()) {
        return boolResultRecord[make_pair(p, inputOutputId)];
    }
    
    bool pValue;
    if (dynamic_cast<F*>(p)) {
        F* f = dynamic_cast<F*>(p);
        pValue = f->interpret();
    }
    if (dynamic_cast<Not*>(p)) {
        Not* n = dynamic_cast<Not*>(p);
        pValue = n->interpret(inputOutput);
    }
    if (dynamic_cast<And*>(p)) {
        And* a = dynamic_cast<And*>(p);
        pValue = a->interpret(inputOutput);
    }
    if (dynamic_cast<Lt*>(p)) {
        Lt* lt = dynamic_cast<Lt*>(p);
        pValue = lt->interpret(inputOutput);
    }
    
    boolResultRecord[make_pair(p, inputOutputId)] = pValue;
    return pValue;
}

bool checkTwoProgramsEqual(BaseType* pi, BaseType* pj, vector<map<string, int> > inputOutputs) {
    
    if (dynamic_cast<IntType*>(pi) != 0 && dynamic_cast<IntType*>(pj) != 0) {
        for (int i = 0; i < inputOutputs.size(); i++) {
            int iValue = executeIntProgram(pi, inputOutputs[i], i);
            int jValue = executeIntProgram(pj, inputOutputs[i], i);
            /*
            if (dumpProgram(pi) == "sizei" && dumpProgram(pj) == "sizej") {
                
                for (map<string, int>::iterator it_m = inputOutputs[i].begin(), eit_m = inputOutputs[i].end(); it_m != eit_m; ++it_m) {
                    if (it_m->first != "_out") {
                        cout << it_m->first << " " << it_m->second << " ";
                    }
                }
                cout << "   _out " << inputOutputs[i]["_out"] << endl;
                
                cout << "check " << iValue << " " << jValue << endl;
            }
            */
            if (iValue != jValue) {
                return false;
            }
        }
    }
    else if (dynamic_cast<BoolType*>(pi) != 0 && dynamic_cast<BoolType*>(pj) != 0) {
        for (int i = 0; i < inputOutputs.size(); i++) {
            bool iValue = executeBoolProgram(pi, inputOutputs[i], i);
            bool jValue = executeBoolProgram(pj, inputOutputs[i], i);
            if (iValue != jValue) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

vector<BaseType*> elimEquvalents(vector<BaseType*> pList, vector<map<string, int> > inputOutputs) {
    vector<BaseType*> programToKeep;
    vector<bool> eqFlag(pList.size() ,false);
    
    for (int i = 0; i < pList.size(); i++) {
        if (eqFlag[i] == true) {
            continue;
        }
        BaseType* pi = pList[i];
        
        //cout << "        Check equals for: " << dumpProgram(pi) << endl;
        
        vector<BaseType*> eqPList;
        eqPList.push_back(pi);
        
        for (int j = i+1; j < pList.size(); j++) {
            BaseType* pj = pList[j];
            //if (dumpProgram(pi) == "sizei") {
            //    cout << "    " << dumpProgram(pi) << " "  << pi << " " << dumpProgram(pj) << " " << pj << endl;
            //}
            if (checkTwoProgramsEqual(pi, pj, inputOutputs)) {
                eqFlag[j] = true;
                eqPList.push_back(pj);
                
                /* remove pj's record */
                for (int inputOutputId = 0; inputOutputId < inputOutputs.size(); inputOutputId++) {
                    boolResultRecord.erase(make_pair(pj, inputOutputId));
                    intResultRecord.erase(make_pair(pj, inputOutputId));
                }
            }
        }
        for (int inputOutputId = 0; inputOutputId < inputOutputs.size(); inputOutputId++) {
            boolResultRecord.erase(make_pair(pi, inputOutputId));
            intResultRecord.erase(make_pair(pi, inputOutputId));
        }
        
        /* random choose program to keep */
        //srand((unsigned)time(NULL));
        //programToKeep.push_back(eqPList[rand() % eqPList.size()]);
        /* always keep the first program, which is short in depth */
        programToKeep.push_back(eqPList[0]);
        
        //dumpPlist(eqPList);
    }
    
    boolResultRecord.clear();
    intResultRecord.clear();
    return programToKeep;
}

/******************************************
    Check correct
 */
bool isCorrect(BaseType* p, vector<map<string, int> > inputOutputs) {
    if (dynamic_cast<IntType*>(p) != 0) {
        for (int i = 0; i < inputOutputs.size(); i++) {
            int pValue = executeIntProgram(p, inputOutputs[i], i);
            if (pValue != inputOutputs[i]["_out"]) {
                return false;
            }
        }
    }
    if (dynamic_cast<BoolType*>(p) != 0) {
        return false;
    }
    return true;
}

/******************************************
 Bottom Up Search main function
*/
string bottomUp(future<string>& futureObj,
                promise<string>& exitSignal,
                int depthBound,
                vector<string> intOps,
                vector<string> boolOps,
                vector<string> vars,
                vector<string> constants,
                vector<map<string, int> > inputOutputs) {

    vector<BaseType*> pList;
    for (int i = 0; i < vars.size(); i++) {
        Var* var = new Var(vars[i]);
        BaseType* baseVar = dynamic_cast<BaseType*>(var);
        pList.push_back(baseVar);
    }
    for (int i = 0; i < constants.size(); i++) {
        Num* num = new Num(stoi(constants[i]));
        BaseType* baseNum = dynamic_cast<BaseType*>(num);
        pList.push_back(baseNum);
    }
    
    cout << "------------------------Start search correct program------------------------" << endl;
    cout << "Init PList size: " << pList.size() << endl;
    cout << "Check Correct" << endl;
    for (int i = 0; i < pList.size(); i++) {
        if (isCorrect(pList[i], inputOutputs)) {
            cout << "SynProg: " << dumpProgram(pList[i]) << endl;
            return dumpProgram(pList[i]);
        }
    }
    
    while(futureObj.wait_for(chrono::milliseconds(0)) == std::future_status::timeout) {
        cout << "Grow" << endl;
        pList = grow(intOps, boolOps, pList, depthBound);
        //dumpPlist(pList);
        cout << "    PList size: " << pList.size() << endl;
        
        cout << "Elim" << endl;
        pList = elimEquvalents(pList, inputOutputs);
        //dumpPlist(pList);
        cout << "    PList size: " << pList.size() << endl;
        
        cout << "Check Correct" << endl;
        for (int i = 0; i < pList.size(); i++) {
            if (isCorrect(pList[i], inputOutputs)) {
                cout << "SynProg: " << dumpProgram(pList[i]) << endl;
                exitSignal.set_value("dumpProgram(pList[i])");
                return dumpProgram(pList[i]);
            }
        }
        
        boolResultRecord.clear();
        intResultRecord.clear();
        
        cout << "------------------------Finished one iteration------------------------" << endl;
    }
    
    return "NYI";
}
