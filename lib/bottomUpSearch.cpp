#include "bottomUpSearch.hpp"



/******************************************
    Constructor
 */
bottomUpSearch::bottomUpSearch(int depthBound,
                               vector<string> intOps,
                               vector<string> boolOps,
                               vector<string> vars,
                               vector<string> constants,
                               bool isPred,
                               vector<string> rulesToApply,
                               inputOutputs_t inputOutputs) {
    this->_depthBound = depthBound;
    this->_intOps = intOps;
    this->_boolOps = boolOps;
    this->_vars = vars;
    this->_constants = constants;
    this->_inputOutputs = inputOutputs;
    this->_isPred = isPred;
    this->_rulesToApply = rulesToApply;
    
    for(auto varStr : vars) {
        Var* var = new Var(varStr);
        BaseType* baseVar = dynamic_cast<BaseType*>(var);
        this->_pList.push_back(baseVar);
    }
    for (auto numStr : constants) {
        Num* num = new Num(stoi(numStr));
        BaseType* baseNum = dynamic_cast<BaseType*>(num);
        this->_pList.push_back(baseNum);
    }
}

/******************************************
    Dump Program list
*/
inline string bottomUpSearch::dumpProgram(BaseType* p) {
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
    for (auto prog : pList) {
        cout << dumpProgram(prog);
        if (prog != pList.back()) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    return;
}

void bottomUpSearch::dumpPlist() {
    cout << "[";
    for (auto prog : _pList) {
        cout << dumpProgram(prog);
        if (prog != _pList.back()) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    return;
}

inline int bottomUpSearch::getPlistSize() {
    return _pList.size();
}

void bottomUpSearch::dumpLangDef() {
    cout << "Dump language used:" << endl;
    cout << "    intOps: ";
    for (auto op : _intOps) cout << op << " ";
    cout << endl;
    cout << "    boolOps: ";
    for (auto op : _boolOps) cout << op << " ";
    cout << endl;
    cout << "    constants: ";
    for (auto c : _constants) cout << c << " ";
    cout << endl;
    cout << "    vars: ";
    for (auto v : _vars) cout << v << " ";
    cout << endl;
}

/******************************************
    Specify and check  growing rules
*/
bool bottomUpSearch::isGrowRuleSatisfied(BaseType* i, BaseType* j, BaseType* k, string op) {
    /* basic rules */
    if (op == "PLUS") {
        if (dynamic_cast<IntType*>(i) != nullptr && dynamic_cast<IntType*>(j) != nullptr) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            if (inti->depth() >= _depthBound || intj->depth() >= _depthBound) {
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
            if (inti->depth() >= _depthBound || intj->depth() >= _depthBound) {
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
            if (inti->depth() >= _depthBound || intj->depth() >= _depthBound) {
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
            if (inti->depth() >= _depthBound || intj->depth() >= _depthBound) {
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
            if (inti->depth() >= _depthBound || intj->depth() >= _depthBound) {
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
            if (booli->depth() >= _depthBound || intj->depth() >= _depthBound || intk->depth() >= _depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    else if (op == "NOT") {
        if (dynamic_cast<BoolType*>(i) != nullptr) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            if (booli->depth() >= _depthBound) {
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
            if (booli->depth() >= _depthBound || boolj->depth() >= _depthBound) {
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
            if (inti->depth() >= _depthBound || intj->depth() >= _depthBound) {
                return false;
            }
        } else {
            return false;
        }
    }
    
    /* Search mode specified rules */
    if (find(_rulesToApply.begin(), _rulesToApply.end(), "PerSrcIter") != _rulesToApply.end() ) {
       
    }
    else if (find(_rulesToApply.begin(), _rulesToApply.end(), "PerSrcSnk") != _rulesToApply.end() ) {
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
BaseType* bottomUpSearch::growOneExpr(BaseType* i, BaseType* j, BaseType* k, string op) {
    if (op == "PLUS") {
        if (isGrowRuleSatisfied(i, j, k, op)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Plus* plus = new Plus(inti, intj);
            return dynamic_cast<BaseType*>(plus);
        }
    }
    else if (op == "MINUS") {
        if (isGrowRuleSatisfied(i, j, k, op)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Minus* minus = new Minus(inti, intj);
            return dynamic_cast<BaseType*>(minus);
        }
    }
    else if (op == "LEFTSHIFT") {
        if (isGrowRuleSatisfied(i, j, k, op)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Leftshift* leftshift = new Leftshift(inti, intj);
            return dynamic_cast<BaseType*>(leftshift);
        }
    }
    else if (op == "RIGHTSHIFT") {
        if (isGrowRuleSatisfied(i, j, k, op)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Rightshift* rightshift = new Rightshift(inti, intj);
            return dynamic_cast<BaseType*>(rightshift);
        }
    }
    else if (op == "TIMES") {
        if (isGrowRuleSatisfied(i, j, k, op)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Times* times = new Times(inti, intj);
            return dynamic_cast<BaseType*>(times);
        }
    }
    else if (op == "ITE") {
        if (isGrowRuleSatisfied(i, j, k, op)) {
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
        if (isGrowRuleSatisfied(i, j, k, op)) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            Not* n = new Not(booli);
            return dynamic_cast<BaseType*>(n);
        }
    }
    else if (op == "AND") {
        if (isGrowRuleSatisfied(i, j, k, op)) {
            BoolType* booli = dynamic_cast<BoolType*>(i);
            BoolType* boolj = dynamic_cast<BoolType*>(j);
            And* a = new And(booli, boolj);
            return dynamic_cast<BaseType*>(a);
        }
    }
    else if (op == "LT") {
        if (isGrowRuleSatisfied(i, j, k, op)) {
            IntType* inti = dynamic_cast<IntType*>(i);
            IntType* intj = dynamic_cast<IntType*>(j);
            Lt* lt = new Lt(inti, intj);
            return dynamic_cast<BaseType*>(lt);
        }
    }
    return nullptr;
}

void bottomUpSearch::grow() {
    
    vector<BaseType*> newPList;
    
    for (auto op : _intOps) {
        
        /* communitive op */
        if (op == "PLUS" || op == "TIMES") {
            for (int j = 0; j < _pList.size(); j++) {
                for (int k = j; k < _pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(_pList[j], _pList[k], nullptr, op);
                    if (newExpr != nullptr) {
                        newPList.push_back(newExpr);
                    }
                }
            }
        }
        /* non-communitie op */
        else if (op == "MINUS" || op == "LEFTSHIFT" || op == "RIGHTSHIFT") {
            for (int j = 0; j < _pList.size(); j++) {
                for (int k = 0; k < _pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(_pList[j], _pList[k], nullptr, op);
                    if (newExpr != nullptr) {
                        newPList.push_back(newExpr);
                    }
                }
            }
        }
        else if (op == "ITE") {
            for (int j = 0; j < _pList.size(); j++) {
                for (int k = 0; k < _pList.size(); k++) {
                    for (int l = 0; l < _pList.size(); l++) {
                        BaseType* newExpr = growOneExpr(_pList[j], _pList[k], _pList[l], op);
                        if (newExpr != nullptr) {
                            newPList.push_back(newExpr);
                        }
                    }
                }
            }
        }
    }
    
    
    for (auto op : _boolOps) {
        
        if (op == "F") {
            BaseType* newExpr = growOneExpr(nullptr, nullptr, nullptr, op);
            if (newExpr != nullptr) {
                newPList.push_back(newExpr);
            }
        }
        else if (op == "NOT") {
            for (int j = 0; j < _pList.size(); j++) {
                BaseType* newExpr = growOneExpr(_pList[j], nullptr, nullptr, op);
                if (newExpr != nullptr) {
                    newPList.push_back(newExpr);
                }
            }
        }
        else if (op == "AND") {
            for (int j = 0; j < _pList.size(); j++) {
                for (int k = j+1; k < _pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(_pList[j], _pList[k], nullptr, op);
                    if (newExpr != nullptr) {
                        newPList.push_back(newExpr);
                    }
                }
            }
        }
        else if (op == "LT") {
            for (int j = 0; j < _pList.size(); j++) {
                for (int k = 0; k < _pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(_pList[j], _pList[k], nullptr, op);
                    if (newExpr != nullptr) {
                        newPList.push_back(newExpr);
                    }
                }
            }
        }
    }
    
    _pList.insert(_pList.end(), newPList.begin(), newPList.end());
    return;
}

/******************************************
    Eliminate equvalent programs
*/
inline int bottomUpSearch::evaluateIntProgram(BaseType* p, int inputOutputId) {
    
    if (_intResultRecord.find(make_pair(p, inputOutputId)) != _intResultRecord.end()) {
        return _intResultRecord[make_pair(p, inputOutputId)];
    }
    
    int pValue;
    if (dynamic_cast<Num*>(p)) {
        Num* num = dynamic_cast<Num*>(p);
        pValue = num->interpret();
    }
    else if (dynamic_cast<Var*>(p)) {
        Var* var = dynamic_cast<Var*>(p);
        pValue = var->interpret(_inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Plus*>(p)) {
        Plus* plus = dynamic_cast<Plus*>(p);
        pValue = plus->interpret(_inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Times*>(p)) {
        Times* times = dynamic_cast<Times*>(p);
        pValue = times->interpret(_inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Minus*>(p)) {
        Minus* minus = dynamic_cast<Minus*>(p);
        pValue = minus->interpret(_inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Leftshift*>(p)) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(p);
        pValue = leftshift->interpret(_inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Rightshift*>(p)) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(p);
        pValue = rightshift->interpret(_inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Ite*>(p)) {
        Ite* ite = dynamic_cast<Ite*>(p);
        pValue = ite->interpret(_inputOutputs[inputOutputId]);
    }
    
    _intResultRecord[make_pair(p, inputOutputId)] = pValue;
    return pValue;
}

inline bool bottomUpSearch::evaluateBoolProgram(BaseType* p, int inputOutputId) {
    if (_boolResultRecord.find(make_pair(p, inputOutputId)) != _boolResultRecord.end()) {
        return _boolResultRecord[make_pair(p, inputOutputId)];
    }
    
    bool pValue;
    if (dynamic_cast<F*>(p)) {
        F* f = dynamic_cast<F*>(p);
        pValue = f->interpret();
    }
    else if (dynamic_cast<Not*>(p)) {
        Not* n = dynamic_cast<Not*>(p);
        pValue = n->interpret(_inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<And*>(p)) {
        And* a = dynamic_cast<And*>(p);
        pValue = a->interpret(_inputOutputs[inputOutputId]);
    }
    else if (dynamic_cast<Lt*>(p)) {
        Lt* lt = dynamic_cast<Lt*>(p);
        pValue = lt->interpret(_inputOutputs[inputOutputId]);
    }
    
    _boolResultRecord[make_pair(p, inputOutputId)] = pValue;
    return pValue;
}

inline bool bottomUpSearch::checkTwoProgramsEqual(BaseType* pi, BaseType* pj) {
    
    if (dynamic_cast<IntType*>(pi) != nullptr && dynamic_cast<IntType*>(pj) != nullptr) {
        for (int i = 0; i < _inputOutputs.size(); i++) {
            int iValue = evaluateIntProgram(pi, i);
            int jValue = evaluateIntProgram(pj, i);
            
            if (iValue != jValue) {
                return false;
            }
        }
    }
    else if (dynamic_cast<BoolType*>(pi) != nullptr && dynamic_cast<BoolType*>(pj) != nullptr) {
        for (int i = 0; i < _inputOutputs.size(); i++) {
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

void bottomUpSearch::elimEquvalents() {
    vector<BaseType*> programToKeep;
    vector<bool> eqFlag(_pList.size() ,false);
    
    for (int i = 0; i < _pList.size(); i++) {
        if (eqFlag[i] == true) {
            continue;
        }
        BaseType* pi = _pList[i];
        
        //cout << "        Check equals for: " << dumpProgram(pi) << endl;
        
        vector<BaseType*> eqPList;
        eqPList.push_back(pi);
        
        for (int j = i+1; j < _pList.size(); j++) {
            BaseType* pj = _pList[j];
            
            if (checkTwoProgramsEqual(pi, pj)) {
                
                eqFlag[j] = true;
                eqPList.push_back(pj);
                
                if ((pj->getNumOfSymbolsInProg("B") == 0 && pj->getNumOfSymbolsInProg() < pi->getNumOfSymbolsInProg()) ||
                    (pj->getNumOfSymbolsInProg("B") != 0 && pj->getNumOfSymbolsInProg("Isrc") < pi->getNumOfSymbolsInProg("Isrc"))) {
                    
                    //cout << pj->toString() << " " << pj->getNumOfSymbolsInProg() << " " << pi->toString() << " " << pi->getNumOfSymbolsInProg() << endl;
                    eqPList[0] = pj;
                    eqPList[eqPList.size() - 1] = pi;
                    /* remove pi's record */
                    for (int inputOutputId = 0; inputOutputId < _inputOutputs.size(); inputOutputId++) {
                        _boolResultRecord.erase(make_pair(pi, inputOutputId));
                        _intResultRecord.erase(make_pair(pi, inputOutputId));
                    }
                    pi = pj;
                }
                else {
                    /* remove pj's record */
                    for (int inputOutputId = 0; inputOutputId < _inputOutputs.size(); inputOutputId++) {
                        _boolResultRecord.erase(make_pair(pj, inputOutputId));
                        _intResultRecord.erase(make_pair(pj, inputOutputId));
                    }
                }
                
            }
        }
        for (int inputOutputId = 0; inputOutputId < _inputOutputs.size(); inputOutputId++) {
            _boolResultRecord.erase(make_pair(pi, inputOutputId));
            _intResultRecord.erase(make_pair(pi, inputOutputId));
        }
        
        /* random choose program to keep */
        //srand((unsigned)time(nullptr));
        //programToKeep.push_back(eqPList[rand() % eqPList.size()]);
        /* always keep the first program, which is short in depth */
        programToKeep.push_back(eqPList[0]);
        
        //cout << " Keep " << eqPList[0]->toString() << endl;
        //dumpPlist(eqPList);
        //cout << "Keep " << dumpProgram(eqPList[0]) << endl;
    }
    
    _boolResultRecord.clear();
    _intResultRecord.clear();
    
    //dumpPlist(programToKeep);
    _pList = programToKeep;
    return;
}

/******************************************
    Check correct
 */
bool bottomUpSearch::isCorrect(BaseType* p) {
    if (_isPred) {
        if (dynamic_cast<BoolType*>(p) != nullptr) {
                /* all true or all false are both correct program */
                bool allFalse = true;
                bool allTrue = true;
        #ifdef DEBUG
                bool firstFalse = true;
                bool firstTrue = true;
        #endif
                for (int i = 0; i < _inputOutputs.size(); i++) {
                    
                    if (!(_inputOutputs[i]["_out"] == 0 || _inputOutputs[i]["_out"] == 1)) {
                        return false;
                    }
                    int pValue = evaluateBoolProgram(p, i);
                    
                    if (pValue != _inputOutputs[i]["_out"]) {
                        allTrue = false;
        #ifdef DEBUG
                        if (firstFalse) {
                            BoolType* boolcheck = dynamic_cast<BoolType*>(p);
                            if (boolcheck->toString() == "(Isrc1 < B0)") {
                                if (pValue != _inputOutputs[i]["_out"]) {
                                    cout << "First false NotEqual " << pValue << " _out " << _inputOutputs[i]["_out"] << endl ;
                                    
                                    for (auto it = _inputOutputs[i].begin(), eit = _inputOutputs[i].end(); it != eit; ++it) {
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
                                if (pValue == _inputOutputs[i]["_out"]) {
                                    cout << "First true NotEqual " << pValue << " _out " << _inputOutputs[i]["_out"] << endl ;
                                    
                                    for (auto it = _inputOutputs[i].begin(), eit = _inputOutputs[i].end(); it != eit; ++it) {
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
        else {
            return false;
        }
    } else {
        if (dynamic_cast<IntType*>(p) != nullptr) {
            for (int i = 0; i < _inputOutputs.size(); i++) {
                int pValue = evaluateIntProgram(p, i);
                if (pValue != _inputOutputs[i]["_out"]) {
                    return false;
                }
            }
        } else {
            return false;
        }
    }
    
    return true;
}

inline string bottomUpSearch::getCorrect() {
    for (auto prog : _pList) {
        if (isCorrect(prog)) {
#ifdef DEBUG
            cout << "SynProg: " << dumpProgram(prog) << endl;
#endif
            return dumpProgram(prog);
        }
    }
    return "";
}

string bottomUpSearch::search() {
#ifdef DEBUG
    cout << "Init pList size " << getPlistSize() << ", check correct" << endl;
#endif
    //dumpPlist();
    elimEquvalents();
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
