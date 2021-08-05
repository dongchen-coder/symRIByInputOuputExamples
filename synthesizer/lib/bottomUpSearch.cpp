#include "bottomUpSearch.hpp"
/******************************************
    Constructor
 */

// Support definition
#define GET_NUM_OF_OPS(prog, op)            ( prog->getNumberOfOpsInProg(op) )
#define GET_NUM_OF_SYMS(prog, sym)          ( prog->getNumberOfVarsInProg(sym) )
#define GET_LENGTH(prog)                    ( GET_NUM_OF_SYMS(prog, "ALL") + GET_NUM_OF_OPS(prog, "ALL") )
#define GET_EXP(prog, sym)                  ( prog->getExponentOfVarInProg(sym))

#define CHECK_NO_SYM(prog, sym)             ( GET_NUM_OF_SYMS(prog, sym) == 0 )
#define HAS_SYM(prog, sym)                  ( GET_NUM_OF_SYMS(prog, sym) > 0 )
#define CHECK_LESS_SYM(pi, pj, sym)         ( GET_NUM_OF_SYMS(pi, sym) < GET_NUM_OF_SYMS(pj, sym) )
#define CHECK_EQ_SYM(pi, pj, sym)           ( GET_NUM_OF_SYMS(pi, sym) == GET_NUM_OF_SYMS(pj, sym) )

#define DEPTH_SHOTER(pi, pj)                ( pi->depth() < pj->depth() )
#define LENGTH_SHOTER(pi, pj)               ( GET_LENGTH(pi) < GET_LENGTH(pj) )

// NO SYM
#define NO_SYM_1(prog)                      ( CHECK_NO_SYM(pi, "ALL") )
#define NO_SYM_2(pi, pj)                    ( CHECK_NO_SYM(pi, "ALL") && CHECK_NO_SYM(pj, "ALL") )

#define GET_LENGTH_SHOTER(pi, pj)           ( LENGTH_SHOTER(pi, pj) ? pi : pj )

// B SYM ONLY
#define B_SYM_ONLY_1(prog)                  ( !NO_SYM_1(prog) && CHECK_NO_SYM(prog, "I") )
#define B_SYM_ONLY_2(pi, pj)                ( !NO_SYM_2(pi, pj) && CHECK_NO_SYM(pi, "I") && CHECK_NO_SYM(pj, "I") )

// I SYM ONLY
#define I_SYM_ONLY_1(prog)                  ( !NO_SYM_1(prog) && CHECK_NO_SYM(prog, "B") )
#define I_SYM_ONLY_2(pi, pj)                ( !NO_SYM_2(pi, pj) && CHECK_NO_SYM(pi, "B") && CHECK_NO_SYM(pj, "B") )

// BOTH SYM
#define BOTH_SYM_1(prog)                    ( !CHECK_NO_SYM(prog, "B") && !CHECK_NO_SYM(prog, "I") )
#define BOTH_SYM_2(pi, pj)                  ( BOTH_SYM_1(pi) && BOTH_SYM_1(pj) )

// LENGTH RULE
#define GET_LENGTH_SHOTER(pi, pj)           ( LENGTH_SHOTER(pi, pj) ? pi : pj )
#define GET_LESS_SYM(pi, pj, sym)           ( CHECK_EQ_SYM(pi, pj, sym) ? pi : pj )

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
    if (auto var = dynamic_cast<Var*>(p)) {
        return var->toString();
    }
    else if (auto num = dynamic_cast<Num*>(p)) {
        return num->toString();
    }
    else if (auto f = dynamic_cast<F*>(p)) {
        return f->toString();
    }
    else if (auto plus = dynamic_cast<Plus*>(p)) {
        return plus->toString();
    }
    else if (auto minus = dynamic_cast<Minus*>(p)) {
        return minus->toString();
    }
    else if (auto times = dynamic_cast<Times*>(p)) {
        return times->toString();
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(p)) {
        return leftshift->toString();
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(p)) {
        return rightshift->toString();
    }
    else if (auto lt = dynamic_cast<Lt*>(p)) {
        return lt->toString();
    }
    else if (auto a = dynamic_cast<And*>(p)) {
        return a->toString();
    }
    else if (auto n = dynamic_cast<Not*>(p)) {
        return n->toString();
    }
    else if (auto ite = dynamic_cast<Ite*>(p)) {
        return ite->toString();
    }
    else {
        throw runtime_error("bottomUpSearch::dumpProgram() operates on UNKNOWN type!");
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
bool bottomUpSearch::isGrowRuleSatisfied(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int prog_generation) {
    // depth rule
    if (operand_a && operand_a->depth() >= _depthBound) return false;
    if (operand_b && operand_b->depth() >= _depthBound) return false;
    if (operand_c && operand_c->depth() >= _depthBound) return false;
    
    // generation rule
    int cur_generation = 0;
    if (operand_a) cur_generation = max(cur_generation, operand_a->depth());
    if (operand_b) cur_generation = max(cur_generation, operand_b->depth());
    if (operand_c) cur_generation = max(cur_generation, operand_c->depth());
    if (cur_generation + 1 != prog_generation) return false;
    
    // value rule
    auto a = dynamic_cast<Num*>(operand_a);
    auto b = dynamic_cast<Num*>(operand_b);
    if (a && b) {
        if (op != "TIMES") return false;
        int num_a = a->interpret();
        int num_b = b->interpret();
        int num_c = num_a * num_b;
        if (num_c < 2 || num_a < 2 || num_b < 2) return false;
    }
    if (a && b == nullptr) {
        int num_a = a->interpret();
        if (num_a < 2 && op == "TIMES") return false;
        if (num_a == 0 && op == "PLUS") return false;
    }
    if (a == nullptr && b) {
        int num_b = b->interpret();
        if (num_b < 2 && op == "TIMES") return false;
        if (num_b == 0 && op == "PLUS") return false;
    }
    
    // type rule
    if (op == "PLUS" || op == "MINUS" || op == "TIMES" || op == "LT" || op == "LEFTSHIFT" || op == "RIGHTSHIFT") {
        if (!(dynamic_cast<IntType*>(operand_a) && dynamic_cast<IntType*>(operand_b))) {
            return false;
        }
    }
    else if (op == "NOT") {
        if (!dynamic_cast<BoolType*>(operand_a)) {
            return false;
        }
    }
    else if (op == "AND") {
        if (!(dynamic_cast<BoolType*>(operand_a) && dynamic_cast<BoolType*>(operand_b))) {
            return false;
        }
    }
    else if (op == "ITE") {
        if (!(dynamic_cast<BoolType*>(operand_a) && dynamic_cast<IntType*>(operand_b) && dynamic_cast<IntType*>(operand_c))) {
            return false;
        }
    }
    else {
        throw runtime_error("bottomUpSearch::isGrowRuleSatisfied() operates on UNKNOWN type: " + op);
    }
    
    // form rule
    if (op == "PLUS" || op == "MINUS" || op == "TIMES" || op == "LEFTSHIFT" || op == "RIGHTSHIFT") {
        int num_in_a = operand_a->getNumberOfVarsInProg("NUM");
        int num_in_b = operand_b->getNumberOfVarsInProg("NUM");
        int plus_in_b = operand_b->getNumberOfOpsInProg("PLUS");
        // Num can only appear in left operand of TIMES
        if (op == "TIMES" && num_in_b != 0) return false;
        
        // Only one constant term on the left
        if (op == "PLUS" && dynamic_cast<Num*>(operand_a) && plus_in_b+1 < num_in_b) return false;
        
        // limiting appearance of Num
        if (op == "PLUS" && dynamic_cast<Plus*>(operand_a) && dynamic_cast<Plus*>(operand_b) && num_in_a + num_in_b > 1) return false;
        if (op == "PLUS" && dynamic_cast<Plus*>(operand_a) && dynamic_cast<Num*>(operand_b) && num_in_a + num_in_b > 1) return false;
        if (op == "PLUS" && dynamic_cast<Num*>(operand_a) && dynamic_cast<Plus*>(operand_b) && num_in_a + num_in_b > 1) return false;
        
        // limiting the form to be a0 * x^n0 + a1 * y^n1 + a0
        if (op == "PLUS" && operand_a->getNumberOfOpsInProg("PLUS") != 0 && operand_b->getNumberOfOpsInProg("PLUS")) return false;
        
        if (op == "TIMES" && dynamic_cast<Times*>(operand_a) && dynamic_cast<Times*>(operand_b) && num_in_a + num_in_b > 1) return false;
        if (op == "TIMES" && dynamic_cast<Times*>(operand_a) && dynamic_cast<Num*>(operand_b) && num_in_a + num_in_b > 1) return false;
        if (op == "TIMES" && dynamic_cast<Num*>(operand_a) && dynamic_cast<Times*>(operand_b) && num_in_a + num_in_b > 1) return false;
        
        if (op == "MINUS" && dynamic_cast<Minus*>(operand_a) && dynamic_cast<Minus*>(operand_b) && num_in_a + num_in_b > 1) return false;
        if (op == "LEFTSHIFT" && dynamic_cast<Leftshift*>(operand_a) && dynamic_cast<Leftshift*>(operand_b) && num_in_a + num_in_b > 1) return false;
        if (op == "RIGHTSHIFT" && dynamic_cast<Rightshift*>(operand_a) && dynamic_cast<Rightshift*>(operand_b) && num_in_a + num_in_b > 1) return false;
    }
    // remove expr "Nun < Num"
    if (op == "LT" && dynamic_cast<Num*>(operand_a) && dynamic_cast<Num*>(operand_b)) {
        return false;
    }
    
    
    return true;
}

/******************************************
    Grow program list
*/
inline BaseType* bottomUpSearch::growOneExpr(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int prog_generation) {
    // check rules
    if (op == "F" || !isGrowRuleSatisfied(operand_a, operand_b, operand_c, op, prog_generation)) {
        return nullptr;
    }
    // constant expression, only grow constant expression by times
    if (auto a = dynamic_cast<Num*>(operand_a)) {
        if (auto b = dynamic_cast<Num*>(operand_b)) {
            return dynamic_cast<BaseType*>(new Num(a->interpret() * b->interpret()));
        }
    }
    
    if (op == "PLUS") {
        Plus* plus = new Plus(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(plus);
    }
    else if (op == "MINUS") {
        Minus* minus = new Minus(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(minus);
    }
    else if (op == "LEFTSHIFT") {
        Leftshift* leftshift = new Leftshift(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(leftshift);
    }
    else if (op == "RIGHTSHIFT") {
        Rightshift* rightshift = new Rightshift(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(rightshift);
    }
    else if (op == "TIMES") {
        Times* times = new Times(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(times);
    }
    else if (op == "ITE") {
        Ite* ite = new Ite(dynamic_cast<BoolType*>(operand_a), dynamic_cast<IntType*>(operand_b), dynamic_cast<IntType*>(operand_c));
        return dynamic_cast<BaseType*>(ite);
    }
    else if (op == "F") {
        F* f = new F();
        return dynamic_cast<BaseType*>(f);
    }
    else if (op == "NOT") {
        Not* n = new Not(dynamic_cast<BoolType*>(operand_a));
        return dynamic_cast<BaseType*>(n);
    }
    else if (op == "AND") {
        And* a = new And(dynamic_cast<BoolType*>(operand_a), dynamic_cast<BoolType*>(operand_b));
        return dynamic_cast<BaseType*>(a);
    }
    else if (op == "LT") {
        Lt* lt = new Lt(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(lt);
    }
    else {
        throw runtime_error("bottomUpSearch::growOneExpr() operates on UNKNOWN type!");
    }
    
    return nullptr;
}

void bottomUpSearch::grow(int prog_generation) {
    
    vector<BaseType*> newPList;
     
    for (auto op : _intOps) {
        
        /* communitive op */
        if (op == "PLUS" || op == "TIMES") {
            for (int j = 0; j < _pList.size(); j++) {
                for (int k = j; k < _pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(_pList[j], _pList[k], nullptr, op, prog_generation);
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
                    BaseType* newExpr = growOneExpr(_pList[j], _pList[k], nullptr, op, prog_generation);
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
                        BaseType* newExpr = growOneExpr(_pList[j], _pList[k], _pList[l], op, prog_generation);
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
            BaseType* newExpr = growOneExpr(nullptr, nullptr, nullptr, op, prog_generation);
            if (newExpr != nullptr) {
                newPList.push_back(newExpr);
            }
        }
        else if (op == "NOT") {
            for (int j = 0; j < _pList.size(); j++) {
                BaseType* newExpr = growOneExpr(_pList[j], nullptr, nullptr, op, prog_generation);
                if (newExpr != nullptr) {
                    newPList.push_back(newExpr);
                }
            }
        }
        else if (op == "AND") {
            for (int j = 0; j < _pList.size(); j++) {
                for (int k = j+1; k < _pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(_pList[j], _pList[k], nullptr, op, prog_generation);
                    if (newExpr != nullptr) {
                        newPList.push_back(newExpr);
                    }
                }
            }
        }
        else if (op == "LT") {
            for (int j = 0; j < _pList.size(); j++) {
                for (int k = 0; k < _pList.size(); k++) {
                    BaseType* newExpr = growOneExpr(_pList[j], _pList[k], nullptr, op, prog_generation);
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
    if (auto num = dynamic_cast<Num*>(p)) {
        pValue = num->interpret();
    }
    else if (auto var = dynamic_cast<Var*>(p)) {
        pValue = var->interpret(_inputOutputs[inputOutputId]);
    }
    else if (auto plus = dynamic_cast<Plus*>(p)) {
        pValue = plus->interpret(_inputOutputs[inputOutputId]);
    }
    else if (auto times = dynamic_cast<Times*>(p)) {
        pValue = times->interpret(_inputOutputs[inputOutputId]);
    }
    else if (auto minus = dynamic_cast<Minus*>(p)) {
        pValue = minus->interpret(_inputOutputs[inputOutputId]);
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(p)) {
        pValue = leftshift->interpret(_inputOutputs[inputOutputId]);
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(p)) {
        pValue = rightshift->interpret(_inputOutputs[inputOutputId]);
    }
    else if (auto ite = dynamic_cast<Ite*>(p)) {
        pValue = ite->interpret(_inputOutputs[inputOutputId]);
    }
    else {
        throw runtime_error("bottomUpSearch::evaluateIntProgram() operates on UNKNOWN type!");
    }
    
    _intResultRecord[make_pair(p, inputOutputId)] = pValue;
    return pValue;
}

inline bool bottomUpSearch::evaluateBoolProgram(BaseType* p, int inputOutputId) {
    if (_boolResultRecord.find(make_pair(p, inputOutputId)) != _boolResultRecord.end()) {
        return _boolResultRecord[make_pair(p, inputOutputId)];
    }
    
    bool pValue;
    if (auto f = dynamic_cast<F*>(p)) {
        pValue = f->interpret();
    }
    else if (auto n = dynamic_cast<Not*>(p)) {
        pValue = n->interpret(_inputOutputs[inputOutputId]);
    }
    else if (auto a = dynamic_cast<And*>(p)) {
        pValue = a->interpret(_inputOutputs[inputOutputId]);
    }
    else if (auto lt = dynamic_cast<Lt*>(p)) {
        pValue = lt->interpret(_inputOutputs[inputOutputId]);
    }
    else {
        throw runtime_error("bottomUpSearch::evaluateBoolProgram() operates on UNKNOWN type!");
    }
    
    _boolResultRecord[make_pair(p, inputOutputId)] = pValue;
    return pValue;
}

inline bool bottomUpSearch::checkTwoProgramsEqual(BaseType* pi, BaseType* pj) {
    
    if (dynamic_cast<IntType*>(pi) && dynamic_cast<IntType*>(pj)) {
        for (int i = 0; i < _inputOutputs.size(); i++) {
            if (evaluateIntProgram(pi, i) != evaluateIntProgram(pj, i)) {
                return false;
            }
        }
    }
    else if (dynamic_cast<BoolType*>(pi) && dynamic_cast<BoolType*>(pj)) {
        for (int i = 0; i < _inputOutputs.size(); i++) {
            if (evaluateBoolProgram(pi, i) != evaluateBoolProgram(pj, i)) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

inline BaseType* bottomUpSearch::elimOneProgWithRules(BaseType* pi, BaseType* pj) {
    
    if (pi == nullptr) {
        return pj;
    }
    if (pj == nullptr) {
        return pi;
    }
    
    BaseType* progToKeep = pi;
        
    // Apply common rules
    if (NO_SYM_2(pi, pj) ) {
        progToKeep = GET_LENGTH_SHOTER(pi, pj);
    }
    
    // Apply different rules for predicts and terms
    if (_isPred) {
        if (HAS_SYM(pi, "B") > 0 && HAS_SYM(pj, "B") > 0) {
            if (HAS_SYM(pi, "Isrc") > 0 && HAS_SYM(pj, "Isrc") > 0) {
                if (HAS_SYM(pi, "Isnk") > 0 && HAS_SYM(pj, "Isnk") > 0) {
                    progToKeep = GET_LESS_SYM(pi, pj, "ALL");
                } else {
                    if (HAS_SYM(pi, "Isnk") > 0) {
                        progToKeep = pj;
                    } else if (HAS_SYM(pj, "Isnk") > 0) {
                        progToKeep = pi;
                    } else {
                        if (GET_EXP(pi, "Isrc") < GET_EXP(pj, "Isrc")) {
                            progToKeep = pi;
                        } else if (GET_EXP(pi, "Isrc") > GET_EXP(pj, "Isrc")) {
                            progToKeep = pj;
                        } else {
                            if (GET_EXP(pi, "B") < GET_EXP(pj, "B")) {
                                progToKeep = pi;
                            } else if (GET_EXP(pi, "B") > GET_EXP(pj, "B")) {
                                progToKeep = pj;
                            } else {
                                progToKeep = GET_LESS_SYM(pi, pj, "ALL");
                            }
                        }
                    }
                }
            } else {
                if (HAS_SYM(pi, "Isrc") > 0) {
                    progToKeep = pi;
                } else if (HAS_SYM(pj, "Isrc") > 0) {
                    progToKeep = pj;
                } else {
                    if (GET_NUM_OF_SYMS(pi, "B") < GET_NUM_OF_SYMS(pj, "B")) {
                        progToKeep = pi;
                    } else if (GET_NUM_OF_SYMS(pi, "B") > GET_NUM_OF_SYMS(pj, "B")) {
                        progToKeep = pj;
                    } else {
                        progToKeep = GET_LENGTH_SHOTER(pi, pj);
                    }
                }
            }
        } else {
            if (HAS_SYM(pi, "B") > 0) {
                progToKeep = pi;
            } else if (HAS_SYM(pj, "B") > 0) {
                progToKeep = pj;
            } else {
                progToKeep = GET_LENGTH_SHOTER(pi, pj);
            }
        }
        
        /*
        if (BOTH_SYM_2(pi, pj)) {
            progToKeep = GET_LESS_SYM(pi, pj, "ALL");
        } else {
            if (BOTH_SYM_1(pi)) {
                progToKeep = pi;
            } else if (BOTH_SYM_1(pj)) {
                progToKeep = pj;
            } else {
                progToKeep = GET_LESS_SYM(pi, pj, "ALL");
            }
        }
        */
    } else {
        
        if (HAS_SYM(pi, "B") > 0 && HAS_SYM(pj, "B") > 0) {
            if (HAS_SYM(pi, "Isrc") > 0 && HAS_SYM(pj, "Isrc") > 0) {
                if (HAS_SYM(pi, "Isnk") > 0 && HAS_SYM(pj, "Isnk") > 0) {
                    progToKeep = GET_LESS_SYM(pi, pj, "ALL");;
                } else {
                    if (HAS_SYM(pi, "Isnk") > 0) {
                        progToKeep = pi;
                    } else if (HAS_SYM(pj, "Isnk") > 0) {
                        progToKeep = pj;
                    } else {
                        progToKeep = GET_LESS_SYM(pi, pj, "ALL");
                    }
                }
            } else {
                if (HAS_SYM(pi, "Isrc") > 0) {
                    progToKeep = pj;
                } else if (HAS_SYM(pj, "Isrc") > 0) {
                    progToKeep = pi;
                } else {
                    progToKeep = GET_LESS_SYM(pi, pj, "ALL");
                }
            }
        } else {
            if (HAS_SYM(pi, "B") > 0) {
                progToKeep = pi;
            } else if (HAS_SYM(pj, "B") > 0) {
                progToKeep = pj;
            } else {
                progToKeep = GET_LENGTH_SHOTER(pi, pj);
            }
        }
        
        /*
        if (B_SYM_ONLY_2(pi, pj)) {
            return GET_LENGTH_SHOTER(pi, pj);
        } else {
            if (CHECK_LESS_SYM(pi, pj, "I")) {
                return pi;
                
            } else {
                return pj;
            }
        }
        */
    }
    
    if (progToKeep == pi) {
        for (int inputOutputId = 0; inputOutputId < _inputOutputs.size(); inputOutputId++) {
            _boolResultRecord.erase(make_pair(pj, inputOutputId));
            _intResultRecord.erase(make_pair(pj, inputOutputId));
        }
    } else {
        for (int inputOutputId = 0; inputOutputId < _inputOutputs.size(); inputOutputId++) {
            _boolResultRecord.erase(make_pair(pi, inputOutputId));
            _intResultRecord.erase(make_pair(pi, inputOutputId));
        }
    }
    
    return progToKeep;
}

void bottomUpSearch::elimEquvalents() {
    vector<BaseType*> progToKeepList;
    vector<bool> eqFlag(_pList.size() ,false);
    
    for (int i = 0; i < _pList.size(); i++) {
        if (eqFlag[i] == true) {
            continue;
        }
        BaseType* pi = _pList[i];
        
        /* Find all programs that equal */
        vector<BaseType*> eqPList;
        eqPList.push_back(pi);
        for (int j = i+1; j < _pList.size(); j++) {
            BaseType* pj = _pList[j];
            
            if (checkTwoProgramsEqual(pi, pj)) {
                eqFlag[j] = true;
                eqPList.push_back(pj);
            }
        }
        
        /* Find the program to keep */
        BaseType* progToKeep = nullptr;
        for (auto prog : eqPList) {
            //if (eqPList.size() > 1) cout << prog->toString() << " ";
            progToKeep = elimOneProgWithRules(progToKeep, prog);
        }
        //if (eqPList.size() > 1) cout << endl;
        
        for (int inputOutputId = 0; inputOutputId < _inputOutputs.size(); inputOutputId++) {
            _boolResultRecord.erase(make_pair(pi, inputOutputId));
            _intResultRecord.erase(make_pair(pi, inputOutputId));
        }
        
        /* random choose program to keep */
        //srand((unsigned)time(nullptr));
        //programToKeep.push_back(eqPList[rand() % eqPList.size()]);
        /* always keep the first program, which is short in depth */
        progToKeepList.push_back(progToKeep);
    }
    
    _boolResultRecord.clear();
    _intResultRecord.clear();
    _pList = progToKeepList;
    return;
}

/******************************************
    Check correct
 */
bool bottomUpSearch::isCorrect(BaseType* p) {
    if (_isPred) {
        if (dynamic_cast<BoolType*>(p)) {
                /* all true or all false are both correct program */
                bool allFalse = true;
                bool allTrue = true;
        
                for (int i = 0; i < _inputOutputs.size(); i++) {
                    
                    if (!(_inputOutputs[i]["_out"] == 0 || _inputOutputs[i]["_out"] == 1)) {
                        return false;
                    }
                    
                    if (evaluateBoolProgram(p, i) != _inputOutputs[i]["_out"]) {
                        allTrue = false;
                    } else {
                        allFalse = false;
                    }

                    if (!allTrue && !allFalse) {
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
    }
    else {
        if (dynamic_cast<IntType*>(p)) {
            for (int i = 0; i < _inputOutputs.size(); i++) {
                if (evaluateIntProgram(p, i) != _inputOutputs[i]["_out"]) {
                    return false;
                }
            }
        }
        else {
            return false;
        }
    }
    
    return true;
}

inline string bottomUpSearch::getCorrect(int prog_generation) {
    for (auto prog : _pList) {
        if (prog->depth() == prog_generation && isCorrect(prog)) {
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
    
    int prog_generation = 1;
    while (getCorrect(prog_generation) == "") {
#ifdef DEBUG
        cout << "Current pList size " << getPlistSize() << ", grow" << endl;
#endif
        //dumpPlist();
        prog_generation++;
        grow(prog_generation);
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
    
    return getCorrect(prog_generation);
}
