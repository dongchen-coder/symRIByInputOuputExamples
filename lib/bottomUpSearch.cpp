#include "bottomUpSearch.hpp"
/******************************************
    Constructor
 */
bottomUpSearch::bottomUpSearch(int depthBound,
                               vector<string> intOps,
                               vector<string> boolOps,
                               vector<string> vars,
                               vector<string> constants,
                               vector<map<string, int> > inputOutputs) {
    this->depthBound = depthBound;
    this->intOps = intOps;
    this->boolOps = boolOps;
    this->vars = vars;
    this->constants = constants;
    this->inputOutputs = inputOutputs;
    
    for (int i = 0; i < vars.size(); i++) {
        Var* var = new Var(vars[i]);
        BaseType* baseVar = dynamic_cast<BaseType*>(var);
        this->pList.push_back(baseVar);
    }
    for (int i = 0; i < constants.size(); i++) {
        Num* num = new Num(stoi(constants[i]));
        BaseType* baseNum = dynamic_cast<BaseType*>(num);
        this->pList.push_back(baseNum);
    }
}

/******************************************
    Dump Program list
*/
string bottomUpSearch::dumpProgram(BaseType* p) {
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

void bottomUpSearch::dumpPlist() {
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

int bottomUpSearch::getPlistSize() {
    return pList.size();
}

void bottomUpSearch::dumpLangDef() {
    cout << "Dump language used:" << endl;
    cout << "    intOps: ";
    for (vector<string>::iterator it = intOps.begin(), eit = intOps.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
    cout << "    boolOps: ";
    for (vector<string>::iterator it = boolOps.begin(), eit = boolOps.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
    cout << "    constants: ";
    for (vector<string>::iterator it = constants.begin(), eit = constants.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
    cout << "    vars: ";
    for (vector<string>::iterator it = vars.begin(), eit = vars.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
}

/******************************************
    Grow program list
*/
BaseType* bottomUpSearch::growOneExpr(BaseType* i, BaseType* j, BaseType* k, string op, int depthBound) {
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


vector<BaseType*> bottomUpSearch::grow() {
    
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
int bottomUpSearch::evaluateIntProgram(BaseType* p, int inputOutputId) {
    
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
        pValue = var->interpret(inputOutputs[inputOutputId]);
    }
    if (dynamic_cast<Plus*>(p)) {
        Plus* plus = dynamic_cast<Plus*>(p);
        pValue = plus->interpret(inputOutputs[inputOutputId]);
    }
    if (dynamic_cast<Times*>(p)) {
        Times* times = dynamic_cast<Times*>(p);
        pValue = times->interpret(inputOutputs[inputOutputId]);
    }
    if (dynamic_cast<Ite*>(p)) {
        Ite* ite = dynamic_cast<Ite*>(p);
        pValue = ite->interpret(inputOutputs[inputOutputId]);
    }
    
    intResultRecord[make_pair(p, inputOutputId)] = pValue;
    return pValue;
}

bool bottomUpSearch::evaluateBoolProgram(BaseType* p, int inputOutputId) {
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
        pValue = n->interpret(inputOutputs[inputOutputId]);
    }
    if (dynamic_cast<And*>(p)) {
        And* a = dynamic_cast<And*>(p);
        pValue = a->interpret(inputOutputs[inputOutputId]);
    }
    if (dynamic_cast<Lt*>(p)) {
        Lt* lt = dynamic_cast<Lt*>(p);
        pValue = lt->interpret(inputOutputs[inputOutputId]);
    }
    
    boolResultRecord[make_pair(p, inputOutputId)] = pValue;
    return pValue;
}

bool bottomUpSearch::checkTwoProgramsEqual(BaseType* pi, BaseType* pj) {
    
    if (dynamic_cast<IntType*>(pi) != 0 && dynamic_cast<IntType*>(pj) != 0) {
        for (int i = 0; i < inputOutputs.size(); i++) {
            int iValue = evaluateIntProgram(pi, i);
            int jValue = evaluateIntProgram(pj, i);
            
            if (iValue != jValue) {
                return false;
            }
        }
    }
    else if (dynamic_cast<BoolType*>(pi) != 0 && dynamic_cast<BoolType*>(pj) != 0) {
        for (int i = 0; i < inputOutputs.size(); i++) {
            bool iValue = evaluateBoolProgram(pi, i);
            bool jValue = evaluateBoolProgram(pj, i);
            if (iValue != jValue) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

vector<BaseType*> bottomUpSearch::elimEquvalents() {
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
            
            if (checkTwoProgramsEqual(pi, pj)) {
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
bool bottomUpSearch::isCorrect(BaseType* p) {
    if (dynamic_cast<IntType*>(p) != 0) {
        for (int i = 0; i < inputOutputs.size(); i++) {
            int pValue = evaluateIntProgram(p, i);
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

string bottomUpSearch::getCorrect() {
    for (int i = 0; i < pList.size(); i++) {
        if (isCorrect(pList[i])) {
            cout << "SynProg: " << dumpProgram(pList[i]) << endl;
            //exitSignal.set_value("dumpProgram(pList[i])");
            return dumpProgram(pList[i]);
        }
    }
    return "";
}

string bottomUpSearch::search() {
    
    cout << "Init pList size " << getPlistSize() << ", check correct" << endl;
    while (getCorrect() == "") {
        cout << "Current pList size " << getPlistSize() << ", grow" << endl;
        // dumpPlist();
        grow();
        // dumpPlist();
        cout << "Current pList size " << getPlistSize() << ", eliminate equvalents" << endl;
        elimEquvalents();
        // dumpPlist();
        cout << "Current pList size " << getPlistSize() << ", check correct" << endl;
    }
    
    return getCorrect();
}

/******************************************
 Bottom Up Search main function
*/
/*
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
 */
