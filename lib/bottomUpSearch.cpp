#include "bottomUpSearch.hpp"
/******************************************
    Constructor
 */
bottomUpSearch::bottomUpSearch(int depthBound,
                               vector<string> intOps,
                               vector<string> boolOps,
                               vector<string> vars,
                               vector<string> constants,
                               vector<map<string, int> > inputOutputs,
                               string searchMode) {
    this->depthBound = depthBound;
    this->intOps = intOps;
    this->boolOps = boolOps;
    this->vars = vars;
    this->constants = constants;
    this->inputOutputs = inputOutputs;
    this->searchMode = searchMode;
    
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
    if (dynamic_cast<Var*>(p) != nullptr) {
        Var* var = dynamic_cast<Var*>(p);
        return var->toString();
    }
    else if (dynamic_cast<Num*>(p) != nullptr) {
        Num* num = dynamic_cast<Num*>(p);
        return num->toString();
    }
    else if (dynamic_cast<F*>(p) != nullptr) {
        F* f = dynamic_cast<F*>(p);
        return f->toString();
    }
    else if (dynamic_cast<Plus*>(p) != nullptr) {
        Plus* plus = dynamic_cast<Plus*>(p);
        return plus->toString();
    }
    else if (dynamic_cast<Minus*>(p) != nullptr) {
        Minus* minus = dynamic_cast<Minus*>(p);
        return minus->toString();
    }
    else if (dynamic_cast<Times*>(p) != nullptr) {
        Times* times = dynamic_cast<Times*>(p);
        return times->toString();
    }
    else if (dynamic_cast<Leftshift*>(p) != nullptr) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(p);
        return leftshift->toString();
    }
    else if (dynamic_cast<Rightshift*>(p) != nullptr) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(p);
        return rightshift->toString();
    }
    else if (dynamic_cast<Lt*>(p) != nullptr) {
        Lt* lt = dynamic_cast<Lt*>(p);
        return lt->toString();
    }
    else if (dynamic_cast<And*>(p) != nullptr) {
        And* a = dynamic_cast<And*>(p);
        return a->toString();
    }
    else if (dynamic_cast<Not*>(p) != nullptr) {
        Not* n = dynamic_cast<Not*>(p);
        return n->toString();
    }
    else if (dynamic_cast<Ite*>(p) != nullptr) {
        Ite* ite = dynamic_cast<Ite*>(p);
        return ite->toString();
    }
    return "NoExpr";
}

void bottomUpSearch::dumpPlist(vector<BaseType*> pList) {
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
    Specify and check  growing rules
*/
bool bottomUpSearch::isGrowRuleSatisfied(BaseType* i, BaseType* j, BaseType* k, string op, int depthBound) {
    /* basic rules */
    if (op == "PLUS") {
        if (dynamic_cast<IntType*>(i) != nullptr && dynamic_cast<IntType*>(j) != nullptr) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            if (inti->depth() >= depthBound || intj->depth() >= depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    else if (op == "MINUS") {
        if (dynamic_cast<IntType*>(i) != nullptr && dynamic_cast<IntType*>(j) != nullptr) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            if (inti->depth() >= depthBound || intj->depth() >= depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    else if (op == "LEFTSHIFT") {
        if (dynamic_cast<IntType*>(i) != nullptr && dynamic_cast<IntType*>(j) != nullptr) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            if (inti->depth() >= depthBound || intj->depth() >= depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    else if (op == "RIGHTSHIFT") {
        if (dynamic_cast<IntType*>(i) != nullptr && dynamic_cast<IntType*>(j) != nullptr) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            if (inti->depth() >= depthBound || intj->depth() >= depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    else if (op == "TIMES") {
        if (dynamic_cast<IntType*>(i) != nullptr && dynamic_cast<IntType*>(j) != nullptr) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            if (inti->depth() >= depthBound || intj->depth() >= depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    else if (op == "ITE") {
        if (dynamic_cast<BoolType*>(i) != nullptr && dynamic_cast<IntType*>(j) != nullptr && dynamic_cast<IntType*>(k) != nullptr) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            IntType* intk = dynamic_cast<IntType*>(k);
            if (booli->depth() >= depthBound || intj->depth() >= depthBound || intk->depth() >= depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    else if (op == "NOT") {
        if (dynamic_cast<BoolType*>(i) != nullptr) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            if (booli->depth() >= depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    else if (op == "AND") {
        if (dynamic_cast<BoolType*>(i) != nullptr && dynamic_cast<BoolType*>(j) != nullptr) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            BoolType* boolj = dynamic_cast<BoolType*>(j);
            if (booli->depth() >= depthBound || boolj->depth() >= depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    else if (op == "LT") {
        if (dynamic_cast<IntType*>(i) != nullptr && dynamic_cast<IntType*>(j) != nullptr) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            if (inti->depth() >= depthBound || intj->depth() >= depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    
    /* Search mode specified rules */
    if (searchMode == "PerSrcIter") {
       
    }
    else if (searchMode == "PerSrcSnk") {
        /* rules for variables */
        if (i->getNumOfSymbolsInProg("Isrc0") + j->getNumOfSymbolsInProg("Isrc0") > 1) {
            return false;
        }
        if (i->getNumOfSymbolsInProg("Isrc1") + j->getNumOfSymbolsInProg("Isrc1") > 1) {
            return false;
        }
        if (i->getNumOfSymbolsInProg("Isnk0") + j->getNumOfSymbolsInProg("Isnk0") > 1) {
            return false;
        }
        if (i->getNumOfSymbolsInProg("Isnk1") + j->getNumOfSymbolsInProg("Isnk1") > 1) {
            return false;
        }
        
        /* rules for PLUS */
        if (op == "PLUS") {
            /* do not do two single variable plus */
            if (dynamic_cast<Var*>(i) != nullptr && dynamic_cast<Var*>(j) != nullptr) {
                return false;
            }
            /* do not do two constant plus excrpt "1 + -1" */
            if (dynamic_cast<Num*>(i) != nullptr && dynamic_cast<Num*>(j) != nullptr) {
                Num* numi = dynamic_cast<Num*>(i);
                Num* numj = dynamic_cast<Num*>(j);
                if (!(numi->toString() == "1" && numj->toString() == "-1")) {
                    return false;
                }
            }
        }
        /* rules for MINUS */
        else if (op == "MINUS") {
            /* Isnk - Isrc */
            if (dynamic_cast<Var*>(i) != nullptr && dynamic_cast<Var*>(j) != nullptr) {
                Var* vari = dynamic_cast<Var*>(i);
                Var* varj = dynamic_cast<Var*>(j);
                if (vari->toString().substr(0, 4) != "Isnk" ||
                    varj->toString().substr(0, 4) != "Isrc") {
                    return false;
                }
            }
            /* X - C exclude C - C */
            else if (dynamic_cast<Num*>(j) != nullptr) {
                if (dynamic_cast<Num*>(i) != nullptr) {
                    return false;
                }
            }
            /* exclude C - X */
            else if (dynamic_cast<Num*>(i) != nullptr && dynamic_cast<Var*>(j) != nullptr) {
                return false;
            }
        }
        /* rules for TIMES */
        else if (op == "TIMES") {
            /* exclude B * B */
            if (dynamic_cast<Var*>(i) != nullptr && dynamic_cast<Var*>(j) != nullptr) {
                Var* vari = dynamic_cast<Var*>(i);
                Var* varj = dynamic_cast<Var*>(j);
                if (varj->toString().substr(0, 1) != "B" ||
                    vari->toString().substr(0, 1) != "B") {
                    return false;
                }
            }
            /* exclude B * C */
            else if (dynamic_cast<Num*>(i) != nullptr && dynamic_cast<Num*>(i) != nullptr) {
                return false;
            }
            /* exclude I * I */
            //else if () {
                
            //}
        }
    }
    else {
        
    }
    
    return true;
}

/******************************************
    Grow program list
*/
BaseType* bottomUpSearch::growOneExpr(BaseType* i, BaseType* j, BaseType* k, string op, int depthBound) {
    if (op == "PLUS") {
        if (isGrowRuleSatisfied(i, j, k, op, depthBound)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Plus* plus = new Plus(inti, intj);
            return dynamic_cast<BaseType*>(plus);
        }
    }
    else if (op == "MINUS") {
        if (isGrowRuleSatisfied(i, j, k, op, depthBound)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Minus* minus = new Minus(inti, intj);
            return dynamic_cast<BaseType*>(minus);
        }
    }
    else if (op == "LEFTSHIFT") {
        if (isGrowRuleSatisfied(i, j, k, op, depthBound)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Leftshift* leftshift = new Leftshift(inti, intj);
            return dynamic_cast<BaseType*>(leftshift);
        }
    }
    else if (op == "RIGHTSHIFT") {
        if (isGrowRuleSatisfied(i, j, k, op, depthBound)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Rightshift* rightshift = new Rightshift(inti, intj);
            return dynamic_cast<BaseType*>(rightshift);
        }
    }
    else if (op == "TIMES") {
        if (isGrowRuleSatisfied(i, j, k, op, depthBound)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Times* times = new Times(inti, intj);
            return dynamic_cast<BaseType*>(times);
        }
    }
    else if (op == "ITE") {
        if (isGrowRuleSatisfied(i, j, k, op, depthBound)) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            IntType* intk = dynamic_cast<IntType*>(k);
            Ite* ite = new Ite(booli, intj, intk);
            return dynamic_cast<BaseType*>(ite);
        }
    }
    else if (op == "F") {
        F* f = new F();
        return dynamic_cast<BaseType*>(f);
    }
    else if (op == "NOT") {
        if (dynamic_cast<BoolType*>(i) != nullptr) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            if (booli->depth() < depthBound) {
                Not* n = new Not(booli);
                return dynamic_cast<BaseType*>(n);
            }
        }
    }
    else if (op == "AND") {
        if (isGrowRuleSatisfied(i, j, k, op, depthBound)) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            BoolType* boolj = dynamic_cast<BoolType*>(j);
            And* a = new And(booli, boolj);
            return dynamic_cast<BaseType*>(a);
        }
    }
    else if (op == "LT") {
        if (isGrowRuleSatisfied(i, j, k, op, depthBound)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Lt* lt = new Lt(inti, intj);
            return dynamic_cast<BaseType*>(lt);
        }
    }
    return nullptr;
}


vector<BaseType*> bottomUpSearch::grow() {
    
    vector<BaseType*> newPList;
    
    for (int i = 0; i < intOps.size(); i++) {
        string op = intOps[i];
        /* communitive op */
        if (op == "PLUS" || op == "TIMES") {
            for (int j = 0; j < pList.size(); j++) {
                for (int k = j; k < pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(pList[j], pList[k], nullptr, op, depthBound);
                    if (newExpr != nullptr) {
                        newPList.push_back(newExpr);
                    }
                }
            }
        }
        /* non-communitie op */
        if (op == "MINUS" || op == "LEFTSHIFT" || op == "RIGHTSHIFT") {
            for (int j = 0; j < pList.size(); j++) {
                for (int k = 0; k < pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(pList[j], pList[k], nullptr, op, depthBound);
                    if (newExpr != nullptr) {
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
                        if (newExpr != nullptr) {
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
            BaseType* newExpr = growOneExpr(nullptr, nullptr, nullptr, op, depthBound);
            if (newExpr != nullptr) {
                newPList.push_back(newExpr);
            }
        }
        if (op == "NOT") {
            for (int j = 0; j < pList.size(); j++) {
                BaseType* newExpr = growOneExpr(pList[j], nullptr, nullptr, op, depthBound);
                if (newExpr != nullptr) {
                    newPList.push_back(newExpr);
                }
            }
        }
        if (op == "AND") {
            for (int j = 0; j < pList.size(); j++) {
                for (int k = j+1; k < pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(pList[j], pList[k], nullptr, op, depthBound);
                    if (newExpr != nullptr) {
                        newPList.push_back(newExpr);
                    }
                }
            }
        }
        if (op == "LT") {
            for (int j = 0; j < pList.size(); j++) {
                for (int k = 0; k < pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(pList[j], pList[k], nullptr, op, depthBound);
                    if (newExpr != nullptr) {
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
    else if (dynamic_cast<Var*>(p)) {
        Var* var = dynamic_cast<Var*>(p);
        pValue = var->interpret(inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Plus*>(p)) {
        Plus* plus = dynamic_cast<Plus*>(p);
        pValue = plus->interpret(inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Minus*>(p)) {
        Minus* minus = dynamic_cast<Minus*>(p);
        pValue = minus->interpret(inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Leftshift*>(p)) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(p);
        pValue = leftshift->interpret(inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Rightshift*>(p)) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(p);
        pValue = rightshift->interpret(inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Times*>(p)) {
        Times* times = dynamic_cast<Times*>(p);
        pValue = times->interpret(inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Ite*>(p)) {
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
    else if (dynamic_cast<Not*>(p)) {
        Not* n = dynamic_cast<Not*>(p);
        pValue = n->interpret(inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<And*>(p)) {
        And* a = dynamic_cast<And*>(p);
        pValue = a->interpret(inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Lt*>(p)) {
        Lt* lt = dynamic_cast<Lt*>(p);
        pValue = lt->interpret(inputOutputs[inputOutputId]);
    }
    
    boolResultRecord[make_pair(p, inputOutputId)] = pValue;
    return pValue;
}

bool bottomUpSearch::checkTwoProgramsEqual(BaseType* pi, BaseType* pj) {
    
    if (dynamic_cast<IntType*>(pi) != nullptr && dynamic_cast<IntType*>(pj) != nullptr) {
        for (int i = 0; i < inputOutputs.size(); i++) {
            int iValue = evaluateIntProgram(pi, i);
            int jValue = evaluateIntProgram(pj, i);
            
            if (iValue != jValue) {
                return false;
            }
        }
    }
    else if (dynamic_cast<BoolType*>(pi) != nullptr && dynamic_cast<BoolType*>(pj) != nullptr) {
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
        //srand((unsigned)time(nullptr));
        //programToKeep.push_back(eqPList[rand() % eqPList.size()]);
        /* always keep the first program, which is short in depth */
        programToKeep.push_back(eqPList[0]);
        
        //dumpPlist(eqPList);
        //cout << "Keep " << dumpProgram(eqPList[0]) << endl;
    }
    
    boolResultRecord.clear();
    intResultRecord.clear();
    
    pList = programToKeep;
    return programToKeep;
}

/******************************************
    Check correct
 */
bool bottomUpSearch::isCorrect(BaseType* p) {
    if (dynamic_cast<IntType*>(p) != nullptr) {
        for (int i = 0; i < inputOutputs.size(); i++) {
            int pValue = evaluateIntProgram(p, i);
            if (pValue != inputOutputs[i]["_out"]) {
                return false;
            }
        }
    }
    if (dynamic_cast<BoolType*>(p) != nullptr) {
        /* all true or all false are both correct program */
        bool allFalse = true;
        bool allTrue = true;
#ifdef DEBUG
        bool firstFalse = true;
        bool firstTrue = true;
#endif
        for (int i = 0; i < inputOutputs.size(); i++) {
            
            if (!(inputOutputs[i]["_out"] == 0 || inputOutputs[i]["_out"] == 1)) {
                return false;
            }
            int pValue = evaluateBoolProgram(p, i);
            
            if (pValue != inputOutputs[i]["_out"]) {
                allTrue = false;
#ifdef DEBUG
                if (firstFalse) {
                    BoolType* boolcheck = dynamic_cast<BoolType*>(p);
                    if (boolcheck->toString() == "(Isrc1 < B0)") {
                        if (pValue != inputOutputs[i]["_out"]) {
                            cout << "First false NotEqual " << pValue << " _out " << inputOutputs[i]["_out"] << endl ;
                            
                            for (auto it = inputOutputs[i].begin(), eit = inputOutputs[i].end(); it != eit; ++it) {
                                cout << it->first << " " <<
                                it->second << " ";
                            }
                            
                            cout << endl;
                        }
                    }
                }
                firstFalse = false;
#endif
            } else {
                allFalse = false;
#ifdef DEBUG
                if (firstTrue) {
                    BoolType* boolcheck = dynamic_cast<BoolType*>(p);
                    if (boolcheck->toString() == "(Isrc1 < B0)") {
                        if (pValue == inputOutputs[i]["_out"]) {
                            cout << "First true NotEqual " << pValue << " _out " << inputOutputs[i]["_out"] << endl ;
                            
                            for (auto it = inputOutputs[i].begin(), eit = inputOutputs[i].end(); it != eit; ++it) {
                                cout << it->first << " " <<
                                it->second << " ";
                            }
                            
                            cout << endl;
                        }
                    }
                }
                firstTrue = false;
#endif
            }

            if (!allTrue && !allFalse) {
#ifdef DEBUG
                BoolType* boolcheck = dynamic_cast<BoolType*>(p);
                if (boolcheck->toString() == "(Isrc1 < B0)") {
                    cout << "allTrue " << allTrue << " allFalse " << allFalse << endl;
                }
#endif
                return false;
            }
        }
        if (allFalse == true) {
            BoolType* booli = dynamic_cast<BoolType*>(p);
            p = new Not(booli);
        }
    }
    return true;
}

string bottomUpSearch::getCorrect() {
    for (int i = 0; i < pList.size(); i++) {
        if (isCorrect(pList[i])) {
#ifdef DEBUG
            cout << "SynProg: " << dumpProgram(pList[i]) << endl;
#endif
            return dumpProgram(pList[i]);
        }
    }
    return "";
}

string bottomUpSearch::search() {
#ifdef DEBUG
    cout << "Init pList size " << getPlistSize() << ", check correct" << endl;
#endif
    //dumpPlist();
    while (getCorrect() == "") {
#ifdef DEBUG
        cout << "Current pList size " << getPlistSize() << ", grow" << endl;
#endif
        //dumpPlist();
        grow();
        //dumpPlist();
#ifdef DEBUG
        cout << "Current pList size " << getPlistSize() << ", eliminate equvalents" << endl;
#endif
        elimEquvalents();
        //dumpPlist();
#ifdef DEBUG
        cout << "Current pList size " << getPlistSize() << ", check correct" << endl;
#endif
    }
    
    return getCorrect();
}
