#include "langDef.hpp"

/******************************************
 Base types: int and bool
 */
BaseType::BaseType() {};

string BaseType::toString() {
    if (dynamic_cast<IntType*>(this)) {
        IntType* intType = dynamic_cast<IntType*>(this);
        return intType->toString();
    }
    else if (dynamic_cast<BoolType*>(this)) {
        BoolType* boolType = dynamic_cast<BoolType*>(this);
        return boolType->toString();
    }
    return "";
}

int BaseType::depth() {
    if (dynamic_cast<IntType*>(this)) {
        IntType* intType = dynamic_cast<IntType*>(this);
        return intType->depth();
    }
    else if (dynamic_cast<BoolType*>(this)) {
        BoolType* boolType = dynamic_cast<BoolType*>(this);
        return boolType->depth();
    }
    return 0;
}

int BaseType::getNumOfOpsInProg(string opName) {
    if (dynamic_cast<IntType*>(this)) {
        IntType* intType = dynamic_cast<IntType*>(this);
        return intType->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<BoolType*>(this)) {
        BoolType* boolType = dynamic_cast<BoolType*>(this);
        return boolType->getNumOfOpsInProg(opName);
    }
    return 0;
}

int BaseType::getNumOfSymbolsInProg(string symbolName) {
    if (dynamic_cast<IntType*>(this)) {
        IntType* intType = dynamic_cast<IntType*>(this);
        return intType->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<BoolType*>(this)) {
        BoolType* boolType = dynamic_cast<BoolType*>(this);
        return boolType->getNumOfSymbolsInProg(symbolName);
    }
    return 0;
}

int BaseType::getExponentOfSymbolInProg(string symbolName) {
    if (dynamic_cast<IntType*>(this)) {
        IntType* intType = dynamic_cast<IntType*>(this);
        return intType->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<BoolType*>(this)) {
        BoolType* boolType = dynamic_cast<BoolType*>(this);
        return boolType->getExponentOfSymbolInProg(symbolName);
    }
    return 0;
}

/*
 Int and Bool type
 */

IntType::IntType() {};

string IntType::toString() {
    string output;
    if (dynamic_cast<Num*>(this) != 0) {
        Num* num = dynamic_cast<Num*>(this);
        output = num->toString();
    }
    else if (dynamic_cast<Var*>(this) != 0) {
        Var* var = dynamic_cast<Var*>(this);
        output = var->toString();
    }
    else if (dynamic_cast<Plus*>(this) != 0) {
        Plus* plus = dynamic_cast<Plus*>(this);
        output = plus->toString();
    }
    else if (dynamic_cast<Minus*>(this) != 0) {
        Minus* minus = dynamic_cast<Minus*>(this);
        output = minus->toString();
    }
    else if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        output = times->toString();
    }
    else if (dynamic_cast<Div*>(this) != 0) {
        Div* div = dynamic_cast<Div*>(this);
        output = div->toString();
    }
    else if (dynamic_cast<Min*>(this) != 0) {
        Min* mn = dynamic_cast<Min*>(this);
        output = mn->toString();
    }
    else if (dynamic_cast<Leftshift*>(this) != 0) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(this);
        output = leftshift->toString();
    }
    else if (dynamic_cast<Rightshift*>(this) != 0) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(this);
        output = rightshift->toString();
    }
    else if (dynamic_cast<Ite*>(this) != 0) {
        Ite* ite = dynamic_cast<Ite*>(this);
        output = ite->toString();
    }
    return output;
}

int IntType::depth() {
    int depth;
    if (dynamic_cast<Num*>(this) != 0) {
        Num* num = dynamic_cast<Num*>(this);
        depth = num->depth();
    }
    else if (dynamic_cast<Var*>(this) != 0) {
        Var* var = dynamic_cast<Var*>(this);
        depth = var->depth();
    }
    else if (dynamic_cast<Plus*>(this) != 0) {
        Plus* plus = dynamic_cast<Plus*>(this);
        depth = plus->depth();
    }
    else if (dynamic_cast<Minus*>(this) != 0) {
        Minus* minus = dynamic_cast<Minus*>(this);
        depth = minus->depth();
    }
    else if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        depth = times->depth();
    }
    else if (dynamic_cast<Div*>(this) != 0) {
        Div* div = dynamic_cast<Div*>(this);
        depth = div->depth();
    }
    else if (dynamic_cast<Min*>(this) != 0) {
        Min* mn = dynamic_cast<Min*>(this);
        depth = mn->depth();
    }
    else if (dynamic_cast<Leftshift*>(this) != 0) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(this);
        depth = leftshift->depth();
    }
    else if (dynamic_cast<Rightshift*>(this) != 0) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(this);
        depth = rightshift->depth();
    }
    else if (dynamic_cast<Ite*>(this) != 0) {
        Ite* ite = dynamic_cast<Ite*>(this);
        depth = ite->depth();
    }
    return depth;
}

int IntType::getNumOfOpsInProg(string opName) {
    int numOfOpsInProg;
    if (dynamic_cast<Num*>(this) != 0) {
        Num* num = dynamic_cast<Num*>(this);
        numOfOpsInProg = num->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Var*>(this) != 0) {
        Var* var = dynamic_cast<Var*>(this);
        numOfOpsInProg = var->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Plus*>(this) != 0) {
        Plus* plus = dynamic_cast<Plus*>(this);
        numOfOpsInProg = plus->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Minus*>(this) != 0) {
        Minus* minus = dynamic_cast<Minus*>(this);
        numOfOpsInProg = minus->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        numOfOpsInProg = times->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Div*>(this) != 0) {
        Div* div = dynamic_cast<Div*>(this);
        numOfOpsInProg = div->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Min*>(this) != 0) {
        Min* mn = dynamic_cast<Min*>(this);
        numOfOpsInProg = mn->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Leftshift*>(this) != 0) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(this);
        numOfOpsInProg = leftshift->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Rightshift*>(this) != 0) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(this);
        numOfOpsInProg = rightshift->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Ite*>(this) != 0) {
        Ite* ite = dynamic_cast<Ite*>(this);
        numOfOpsInProg = ite->getNumOfOpsInProg(opName);
    }
    return numOfOpsInProg;
}

int IntType::getNumOfSymbolsInProg(string symbolName) {
    int numOfSymbolsInProg = 0;
    if (dynamic_cast<Num*>(this) != 0) {
        Num* num = dynamic_cast<Num*>(this);
        numOfSymbolsInProg = num->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Var*>(this) != 0) {
        Var* var = dynamic_cast<Var*>(this);
        numOfSymbolsInProg = var->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Plus*>(this) != 0) {
        Plus* plus = dynamic_cast<Plus*>(this);
        numOfSymbolsInProg = plus->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Minus*>(this) != 0) {
        Minus* minus = dynamic_cast<Minus*>(this);
        numOfSymbolsInProg = minus->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        numOfSymbolsInProg = times->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Div*>(this) != 0) {
        Div* div = dynamic_cast<Div*>(this);
        numOfSymbolsInProg = div->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Min*>(this) != 0) {
        Min* mn = dynamic_cast<Min*>(this);
        numOfSymbolsInProg = mn->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Leftshift*>(this) != 0) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(this);
        numOfSymbolsInProg = leftshift->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Rightshift*>(this) != 0) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(this);
        numOfSymbolsInProg = rightshift->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Ite*>(this) != 0) {
        Ite* ite = dynamic_cast<Ite*>(this);
        numOfSymbolsInProg = ite->getNumOfSymbolsInProg(symbolName);
    }
    return numOfSymbolsInProg;
}

int IntType::getExponentOfSymbolInProg(string symbolName) {
    int numOfExponent = 0;
    if (dynamic_cast<Num*>(this) != 0) {
        Num* num = dynamic_cast<Num*>(this);
        numOfExponent = num->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Var*>(this) != 0) {
        Var* var = dynamic_cast<Var*>(this);
        numOfExponent = var->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Plus*>(this) != 0) {
        Plus* plus = dynamic_cast<Plus*>(this);
        numOfExponent = plus->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Minus*>(this) != 0) {
        Minus* minus = dynamic_cast<Minus*>(this);
        numOfExponent = minus->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        numOfExponent = times->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Div*>(this) != 0) {
        Div* div = dynamic_cast<Div*>(this);
        numOfExponent = div->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Min*>(this) != 0) {
        Min* mn = dynamic_cast<Min*>(this);
        numOfExponent = mn->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Leftshift*>(this) != 0) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(this);
        numOfExponent = leftshift->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Rightshift*>(this) != 0) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(this);
        numOfExponent = rightshift->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Ite*>(this) != 0) {
        Ite* ite = dynamic_cast<Ite*>(this);
        numOfExponent = ite->getExponentOfSymbolInProg(symbolName);
    }
    return numOfExponent;
}


BoolType::BoolType() {};

string BoolType::toString() {
    string output;
    if (dynamic_cast<F*>(this) != 0) {
        F* f = dynamic_cast<F*>(this);
        output = f->toString();
    }
    else if (dynamic_cast<Not*>(this) != 0) {
        Not* n = dynamic_cast<Not*>(this);
        output = n->toString();
    }
    else if (dynamic_cast<And*>(this) != 0) {
        And* a = dynamic_cast<And*>(this);
        output = a->toString();
    }
    else if (dynamic_cast<Lt*>(this) != 0) {
        Lt* lt = dynamic_cast<Lt*>(this);
        output = lt->toString();
    }
    return output;
}

int BoolType::depth() {
    int depth;
    if (dynamic_cast<F*>(this) != 0) {
        F* f = dynamic_cast<F*>(this);
        depth = f->depth();
    }
    else if (dynamic_cast<Not*>(this) != 0) {
        Not* n = dynamic_cast<Not*>(this);
        depth = n->depth();
    }
    else if (dynamic_cast<And*>(this) != 0) {
        And* a = dynamic_cast<And*>(this);
        depth = a->depth();
    }
    else if (dynamic_cast<Lt*>(this) != 0) {
        Lt* lt = dynamic_cast<Lt*>(this);
        depth = lt->depth();
    }
    return depth;
}

int BoolType::getNumOfOpsInProg(string opName) {
    int numOfOpsInProg;
    if (dynamic_cast<F*>(this) != 0) {
        F* f = dynamic_cast<F*>(this);
        numOfOpsInProg = f->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Not*>(this) != 0) {
        Not* n = dynamic_cast<Not*>(this);
        numOfOpsInProg = n->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<And*>(this) != 0) {
        And* a = dynamic_cast<And*>(this);
        numOfOpsInProg = a->getNumOfOpsInProg(opName);
    }
    else if (dynamic_cast<Lt*>(this) != 0) {
        Lt* lt = dynamic_cast<Lt*>(this);
        numOfOpsInProg = lt->getNumOfOpsInProg(opName);
    }
    return numOfOpsInProg;
}

int BoolType::getNumOfSymbolsInProg(string symbolName) {
    int numOfSymbolsInProg;
    if (dynamic_cast<F*>(this) != 0) {
        F* f = dynamic_cast<F*>(this);
        numOfSymbolsInProg = f->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Not*>(this) != 0) {
        Not* n = dynamic_cast<Not*>(this);
        numOfSymbolsInProg = n->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<And*>(this) != 0) {
        And* a = dynamic_cast<And*>(this);
        numOfSymbolsInProg = a->getNumOfSymbolsInProg(symbolName);
    }
    else if (dynamic_cast<Lt*>(this) != 0) {
        Lt* lt = dynamic_cast<Lt*>(this);
        numOfSymbolsInProg = lt->getNumOfSymbolsInProg(symbolName);
    }
    return numOfSymbolsInProg;
}

int BoolType::getExponentOfSymbolInProg(string symbolName) {
    int numOfExponent;
    if (dynamic_cast<F*>(this) != 0) {
        F* f = dynamic_cast<F*>(this);
        numOfExponent = f->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Not*>(this) != 0) {
        Not* n = dynamic_cast<Not*>(this);
        numOfExponent = n->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<And*>(this) != 0) {
        And* a = dynamic_cast<And*>(this);
        numOfExponent = a->getExponentOfSymbolInProg(symbolName);
    }
    else if (dynamic_cast<Lt*>(this) != 0) {
        Lt* lt = dynamic_cast<Lt*>(this);
        numOfExponent = lt->getExponentOfSymbolInProg(symbolName);
    }
    return numOfExponent;
}

/******************************************
Constructs: False
*/
F::F() {};

string F::toString() {
    return "false";
}
    
bool F::interpret() {
    return false;
}
    
int F::depth() {
    return 1;
}

int F::getNumOfOpsInProg(string opName) {
    return 0;
}

int F::getNumOfSymbolsInProg(string symbolName) {
    if (symbolName == "false" || symbolName == "ALL") {
        return 1;
    }
    return 0;
}

int F::getExponentOfSymbolInProg(string symbolName) {
    return 0;
}

/******************************************
Constructs: Var
*/
Var::Var(string name) {
    _name = name;
}
    
string Var::toString() {
    return _name;
}
    
int Var::interpret(inputOutput_t env) {
    return env[_name];
}
    
int Var::depth() {
    return 1;
}

int Var::getNumOfOpsInProg(string opName) {
    return 0;
}

int Var::getNumOfSymbolsInProg(string symbolName) {
    if (symbolName == "ALL" ||
        symbolName == "VAR" ||
        symbolName == _name ||
        (symbolName.size() < _name.size() && symbolName == _name.substr(0, symbolName.size())) ) {
        return 1;
    }
    return 0;
}

int Var::getExponentOfSymbolInProg(string symbolName) {
    if (symbolName == _name ||
        (symbolName.size() < _name.size() && symbolName == _name.substr(0, symbolName.size())) ) {
        return 1;
    }
    return 0;
}

/******************************************
Constructs: Num
*/
Num::Num(int val) {
    _num = val;
}
    
string Num::toString() {
    return to_string(_num);
}
    
int Num::interpret() {
    return _num;
}
    
int Num::depth() {
    return 1;
}

int Num::getNumOfOpsInProg(string opName) {
    return 0;
}

int Num::getNumOfSymbolsInProg(string symbolName) {
    if (symbolName == to_string(_num) || symbolName == "ALL" || symbolName == "NUM") {
        return 1;
    }
    return 0;
}

int Num::getExponentOfSymbolInProg(string symbolName) {
    return 0;
}

/******************************************
Constructs: Plus
*/
Plus::Plus(IntType* left, IntType* right) {
    _left = left;
    _right = right;
}

string Plus::toString() {
    string output = "(";
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output += left->toString();
    }
    
    output += " + ";
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        output += right->toString();
    }
    
    output += ")";
    return output;
}
    
int Plus::interpret(inputOutput_t env) {
    int output;
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output = left->interpret();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output = left->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->interpret(env);
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->interpret();
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->interpret(env);
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->interpret(env);
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        output += right->interpret(env);
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        output += right->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        output += right->interpret(env);
    }
    
    return output;
}
    
int Plus::depth() {
    int depth;
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    
    return depth;
}

int Plus::getNumOfOpsInProg(string opName) {
    if (opName == "PLUS" || opName == "ALL") {
        return _left->getNumOfOpsInProg(opName) + _left->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _left->getNumOfOpsInProg(opName);
}

int Plus::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
}

int Plus::getExponentOfSymbolInProg(string symbolName) {
    return max(_left->getExponentOfSymbolInProg(symbolName), _right->getExponentOfSymbolInProg(symbolName));
}

/******************************************
Constructs: Minus
*/
Minus::Minus(IntType* left, IntType* right) {
    _left = left;
    _right = right;
}
    
string Minus::toString() {
    string output = "(";
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output += left->toString();
    }
    
    output += " - ";
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        output += right->toString();
    }
    output += ")";
    return output;
}

int Minus::interpret(inputOutput_t env) {
    int output;
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output = left->interpret();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output = left->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output -= right->interpret(env);
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output -= right->interpret();
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output -= right->interpret(env);
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output -= right->interpret(env);
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        output -= right->interpret(env);
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        output -= right->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
         Minus* right = dynamic_cast<Minus*>(_right);
        output -= right->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output -= right->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        output -= right->interpret(env);
    }
    return output;
}
    
int Minus::depth() {
    int depth;
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    return depth;
}

int Minus::getNumOfOpsInProg(string opName) {
    if (opName == "MINUS" || opName == "ALL") {
        return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName);
}

int Minus::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
}

int Minus::getExponentOfSymbolInProg(string symbolName) {
    return max(_left->getExponentOfSymbolInProg(symbolName), _right->getExponentOfSymbolInProg(symbolName));
}

/******************************************
Constructs: Times
*/
Times::Times(IntType* left, IntType* right) {
    _left = left;
    _right = right;
}
    
string Times::toString() {
    string output = "(";
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output += left->toString();
    }
    
    output += " * ";
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        output += right->toString();
    }
    output += ")";
    return output;
}
    
int Times::interpret(inputOutput_t env) {
    int output;
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output = left->interpret();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output = left->interpret(env);
    }
    
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output *= right->interpret(env);
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output *= right->interpret();
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output *= right->interpret(env);
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output *= right->interpret(env);
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        output *= right->interpret(env);
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        output *= right->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output *= right->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output *= right->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        output *= right->interpret(env);
    }
    
    return output;
}
    
int Times::depth() {
    int depth;
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    return depth;
}

int Times::getNumOfOpsInProg(string opName) {
    if (opName == "TIMES" || opName == "ALL") {
        return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName);
}

int Times::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
}

int Times::getExponentOfSymbolInProg(string symbolName) {
    return _left->getExponentOfSymbolInProg(symbolName) + _right->getExponentOfSymbolInProg(symbolName);
}

/******************************************
Constructs: Min
*/
Min::Min(IntType* left, IntType* right) {
    _left = left;
    _right = right;
}
string Min::toString() {
    string output = " min( ";
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output += left->toString();
    }
    
    output += " , ";
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        output += right->toString();
    }
    output += " ) ";
    return output;
}
int Min::interpret(inputOutput_t env) {
    int leftValue;
    int rightValue;
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        leftValue = left->interpret();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        leftValue = left->interpret(env);
    }
    
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        rightValue = right->interpret();
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        rightValue = right->interpret(env);
    }
    
    return min(leftValue, rightValue);
}
int Min::depth() {
    int depth;
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    return depth;
}
int Min::getNumOfOpsInProg(string opName) {
    if (opName == "MIN" || opName == "ALL") {
        return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName);
}
int Min::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
}

int Min::getExponentOfSymbolInProg(string symbolName) {
    return max(_left->getExponentOfSymbolInProg(symbolName), _right->getExponentOfSymbolInProg(symbolName));
}

/******************************************
Constructs: Div
*/

Div::Div(IntType* dividend, IntType* divisor) {
    _dividend = dividend;
    _divisor = divisor;
}

string Div::toString() {
    string output = "(";
    
    if (dynamic_cast<Var*>(_dividend) != 0) {
        Var* dividend = dynamic_cast<Var*>(_dividend);
        output += dividend->toString();
    }
    else if (dynamic_cast<Num*>(_dividend) != 0) {
        Num* dividend = dynamic_cast<Num*>(_dividend);
        output += dividend->toString();
    }
    else if (dynamic_cast<Plus*>(_dividend) != 0) {
        Plus* dividend = dynamic_cast<Plus*>(_dividend);
        output += dividend->toString();
    }
    else if (dynamic_cast<Times*>(_dividend) != 0) {
        Times* dividend = dynamic_cast<Times*>(_dividend);
        output += dividend->toString();
    }
    else if (dynamic_cast<Div*>(_dividend) != 0) {
        Div* dividend = dynamic_cast<Div*>(_dividend);
        output += dividend->toString();
    }
    else if (dynamic_cast<Min*>(_dividend) != 0) {
        Min* dividend = dynamic_cast<Min*>(_dividend);
        output += dividend->toString();
    }
    else if (dynamic_cast<Minus*>(_dividend) != 0) {
        Minus* dividend = dynamic_cast<Minus*>(_dividend);
        output += dividend->toString();
    }
    else if (dynamic_cast<Leftshift*>(_dividend) != 0) {
        Leftshift* dividend = dynamic_cast<Leftshift*>(_dividend);
        output += dividend->toString();
    }
    else if (dynamic_cast<Rightshift*>(_dividend) != 0) {
        Rightshift* dividend = dynamic_cast<Rightshift*>(_dividend);
        output += dividend->toString();
    }
    
    output += " / ";
    
    if (dynamic_cast<Var*>(_divisor) != 0) {
        Var* divisor = dynamic_cast<Var*>(_divisor);
        output += divisor->toString();
    }
    else if (dynamic_cast<Num*>(_divisor) != 0) {
        Num* divisor = dynamic_cast<Num*>(_divisor);
        output += divisor->toString();
    }
    else if (dynamic_cast<Plus*>(_divisor) != 0) {
        Plus* divisor = dynamic_cast<Plus*>(_divisor);
        output += divisor->toString();
    }
    else if (dynamic_cast<Times*>(_divisor) != 0) {
        Times* divisor = dynamic_cast<Times*>(_divisor);
        output += divisor->toString();
    }
    else if (dynamic_cast<Div*>(_divisor) != 0) {
        Div* divisor = dynamic_cast<Div*>(_divisor);
        output += divisor->toString();
    }
    else if (dynamic_cast<Min*>(_divisor) != 0) {
        Min* divisor = dynamic_cast<Min*>(_divisor);
        output += divisor->toString();
    }
    else if (dynamic_cast<Minus*>(_divisor) != 0) {
        Minus* divisor = dynamic_cast<Minus*>(_divisor);
        output += divisor->toString();
    }
    else if (dynamic_cast<Leftshift*>(_divisor) != 0) {
        Leftshift* divisor = dynamic_cast<Leftshift*>(_divisor);
        output += divisor->toString();
    }
    else if (dynamic_cast<Rightshift*>(_divisor) != 0) {
        Rightshift* divisor = dynamic_cast<Rightshift*>(_divisor);
        output += divisor->toString();
    }
    output += ")";
    return output;
}

int Div::interpret(inputOutput_t env) {
    int dividendValue;
    int divisorValue;
    
    if (dynamic_cast<Var*>(_dividend) != 0) {
        Var* dividend = dynamic_cast<Var*>(_dividend);
        dividendValue = dividend->interpret(env);
    }
    else if (dynamic_cast<Num*>(_dividend) != 0) {
        Num* dividend = dynamic_cast<Num*>(_dividend);
        dividendValue = dividend->interpret();
    }
    else if (dynamic_cast<Plus*>(_dividend) != 0) {
        Plus* dividend = dynamic_cast<Plus*>(_dividend);
        dividendValue = dividend->interpret(env);
    }
    else if (dynamic_cast<Times*>(_dividend) != 0) {
        Times* dividend = dynamic_cast<Times*>(_dividend);
        dividendValue = dividend->interpret(env);
    }
    else if (dynamic_cast<Div*>(_dividend) != 0) {
        Div* dividend = dynamic_cast<Div*>(_dividend);
        dividendValue = dividend->interpret(env);
    }
    else if (dynamic_cast<Min*>(_dividend) != 0) {
        Min* dividend = dynamic_cast<Min*>(_dividend);
        dividendValue = dividend->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_dividend) != 0) {
        Minus* dividend = dynamic_cast<Minus*>(_dividend);
        dividendValue = dividend->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_dividend) != 0) {
        Leftshift* dividend = dynamic_cast<Leftshift*>(_dividend);
        dividendValue = dividend->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_dividend) != 0) {
        Rightshift* dividend = dynamic_cast<Rightshift*>(_dividend);
        dividendValue = dividend->interpret(env);
    }
    
    
    if (dynamic_cast<Var*>(_divisor) != 0) {
        Var* divisor = dynamic_cast<Var*>(_divisor);
        divisorValue = divisor->interpret(env);
    }
    else if (dynamic_cast<Num*>(_divisor) != 0) {
        Num* divisor = dynamic_cast<Num*>(_divisor);
        divisorValue = divisor->interpret();
    }
    else if (dynamic_cast<Plus*>(_divisor) != 0) {
        Plus* divisor = dynamic_cast<Plus*>(_divisor);
        divisorValue = divisor->interpret(env);
    }
    else if (dynamic_cast<Times*>(_divisor) != 0) {
        Times* divisor = dynamic_cast<Times*>(_divisor);
        divisorValue = divisor->interpret(env);
    }
    else if (dynamic_cast<Div*>(_divisor) != 0) {
        Div* divisor = dynamic_cast<Div*>(_divisor);
        divisorValue = divisor->interpret(env);
    }
    else if (dynamic_cast<Min*>(_divisor) != 0) {
        Min* divisor = dynamic_cast<Min*>(_divisor);
        divisorValue = divisor->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_divisor) != 0) {
        Minus* divisor = dynamic_cast<Minus*>(_divisor);
        divisorValue = divisor->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_divisor) != 0) {
        Leftshift* divisor = dynamic_cast<Leftshift*>(_divisor);
        divisorValue = divisor->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_divisor) != 0) {
        Rightshift* divisor = dynamic_cast<Rightshift*>(_divisor);
        divisorValue = divisor->interpret(env);
    }
    
    if (divisorValue == 0) {
        return numeric_limits<int>::max();
    } else {
        return dividendValue / divisorValue;
    }
}

int Div::depth() {
    int depth;
    
    if (dynamic_cast<Var*>(_dividend) != 0) {
        Var* dividend = dynamic_cast<Var*>(_dividend);
        depth = dividend->depth();
    }
    else if (dynamic_cast<Num*>(_dividend) != 0) {
        Num* dividend = dynamic_cast<Num*>(_dividend);
        depth = dividend->depth();
    }
    else if (dynamic_cast<Plus*>(_dividend) != 0) {
        Plus* dividend = dynamic_cast<Plus*>(_dividend);
        depth = dividend->depth();
    }
    else if (dynamic_cast<Times*>(_dividend) != 0) {
        Times* dividend = dynamic_cast<Times*>(_dividend);
        depth = dividend->depth();
    }
    else if (dynamic_cast<Div*>(_dividend) != 0) {
        Div* dividend = dynamic_cast<Div*>(_dividend);
        depth = dividend->depth();
    }
    else if (dynamic_cast<Min*>(_dividend) != 0) {
        Min* dividend = dynamic_cast<Min*>(_dividend);
        depth = dividend->depth();
    }
    else if (dynamic_cast<Minus*>(_dividend) != 0) {
        Minus* dividend = dynamic_cast<Minus*>(_dividend);
        depth = dividend->depth();
    }
    else if (dynamic_cast<Leftshift*>(_dividend) != 0) {
        Leftshift* dividend = dynamic_cast<Leftshift*>(_dividend);
        depth = dividend->depth();
    }
    else if (dynamic_cast<Rightshift*>(_dividend) != 0) {
        Rightshift* dividend = dynamic_cast<Rightshift*>(_dividend);
        depth = dividend->depth();
    }
    
    if (dynamic_cast<Var*>(_divisor) != 0) {
        Var* divisor = dynamic_cast<Var*>(_divisor);
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (dynamic_cast<Num*>(_divisor) != 0) {
        Num* divisor = dynamic_cast<Num*>(_divisor);
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (dynamic_cast<Plus*>(_divisor) != 0) {
        Plus* divisor = dynamic_cast<Plus*>(_divisor);
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (dynamic_cast<Times*>(_divisor) != 0) {
        Times* divisor = dynamic_cast<Times*>(_divisor);
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (dynamic_cast<Div*>(_divisor) != 0) {
        Div* divisor = dynamic_cast<Div*>(_divisor);
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (dynamic_cast<Min*>(_divisor) != 0) {
        Min* divisor = dynamic_cast<Min*>(_divisor);
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (dynamic_cast<Minus*>(_divisor) != 0) {
        Minus* divisor = dynamic_cast<Minus*>(_divisor);
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (dynamic_cast<Leftshift*>(_divisor) != 0) {
        Leftshift* divisor = dynamic_cast<Leftshift*>(_divisor);
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (dynamic_cast<Rightshift*>(_divisor) != 0) {
        Rightshift* divisor = dynamic_cast<Rightshift*>(_divisor);
        depth = max(depth, divisor->depth()) + 1;
    }
    
    return depth;
}

int Div::getNumOfOpsInProg(string opName) {
    if (opName == "DIV" || opName == "ALL") {
        return _dividend->getNumOfOpsInProg(opName) + _divisor->getNumOfOpsInProg(opName) + 1;
    }
    return _dividend->getNumOfOpsInProg(opName) + _divisor->getNumOfOpsInProg(opName);
}

int Div::getNumOfSymbolsInProg(string symbolName) {
    return _dividend->getNumOfSymbolsInProg(symbolName) + _divisor->getNumOfSymbolsInProg(symbolName);
}

int Div::getExponentOfSymbolInProg(string symbolName) {
    return _dividend->getExponentOfSymbolInProg(symbolName) - _divisor->getExponentOfSymbolInProg(symbolName);
}

/******************************************
Constructs: Leftshift
*/
Leftshift::Leftshift(IntType* value, IntType* offset) {
    _value = value;
    _offset = offset;
}

string Leftshift::toString() {
    string output = "(";
    
    if (dynamic_cast<Var*>(_value) != 0) {
        Var* value = dynamic_cast<Var*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Div*>(_value) != 0) {
        Div* value = dynamic_cast<Div*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Min*>(_value) != 0) {
        Min* value = dynamic_cast<Min*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        output += value->toString();
    }
    
    output += " << ";
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Div*>(_offset) != 0) {
        Div* offset = dynamic_cast<Div*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Min*>(_offset) != 0) {
        Min* offset = dynamic_cast<Min*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Rightshift*>(_offset) != 0) {
        Rightshift* offset = dynamic_cast<Rightshift*>(_offset);
        output += offset->toString();
    }
    
    output += ")";
    return output;
}
    
int Leftshift::interpret(inputOutput_t env) {
    int output;
    
    if (dynamic_cast<Var*>(_value) != 0) {
        Var* value = dynamic_cast<Var*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        output = value->interpret();
    }
    else if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Div*>(_value) != 0) {
        Div* value = dynamic_cast<Div*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Min*>(_value) != 0) {
        Min* value = dynamic_cast<Min*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        output = value->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        output = output << offset->interpret(env);
    }
    else if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        output = output << offset->interpret();
    }
    else if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        output = output << offset->interpret(env);
    }
    else if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        output = output << offset->interpret(env);
    }
    else if (dynamic_cast<Div*>(_offset) != 0) {
        Div* offset = dynamic_cast<Div*>(_offset);
        output = output << offset->interpret(env);
    }
    else if (dynamic_cast<Min*>(_offset) != 0) {
        Min* offset = dynamic_cast<Min*>(_offset);
        output = output << offset->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        output = output << offset->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        output = output << offset->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_offset) != 0) {
        Rightshift* offset = dynamic_cast<Rightshift*>(_offset);
        output = output << offset->interpret(env);
    }
    
    return output;
}
    
int Leftshift::depth() {
    int depth;
    
    if (dynamic_cast<Var*>(_value) != 0) {
        Var* value = dynamic_cast<Var*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Div*>(_value) != 0) {
        Div* value = dynamic_cast<Div*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Min*>(_value) != 0) {
        Min* value = dynamic_cast<Min*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        depth = value->depth();
    }
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Div*>(_offset) != 0) {
        Div* offset = dynamic_cast<Div*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Min*>(_offset) != 0) {
        Min* offset = dynamic_cast<Min*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Rightshift*>(_offset) != 0) {
        Rightshift* offset = dynamic_cast<Rightshift*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    return depth;
}

int Leftshift::getNumOfOpsInProg(string opName) {
    if (opName == "LEFTSHIFT" || opName == "ALL") {
        return _value->getNumOfOpsInProg(opName) + _offset->getNumOfOpsInProg(opName) + 1;
    }
    return _value->getNumOfOpsInProg(opName) + _offset->getNumOfOpsInProg(opName);
}

int Leftshift::getNumOfSymbolsInProg(string symbolName) {
    return _value->getNumOfSymbolsInProg(symbolName) + _offset->getNumOfSymbolsInProg(symbolName);
}

int Leftshift::getExponentOfSymbolInProg(string symbolName) {
    return max(_value->getExponentOfSymbolInProg(symbolName), _offset->getExponentOfSymbolInProg(symbolName));
}

/******************************************
Constructs: Leftshift
*/
Rightshift::Rightshift(IntType* value, IntType* offset) {
    _value = value;
    _offset = offset;
}
    
string Rightshift::toString() {
    string output = "(";
    
    if (dynamic_cast<Var*>(_value) != 0) {
        Var* value = dynamic_cast<Var*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Div*>(_value) != 0) {
        Div* value = dynamic_cast<Div*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Min*>(_value) != 0) {
        Min* value = dynamic_cast<Min*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        output += value->toString();
    }
    else if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        output += value->toString();
    }
    
    output += " >> ";
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Div*>(_offset) != 0) {
        Div* offset = dynamic_cast<Div*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Min*>(_offset) != 0) {
        Min* offset = dynamic_cast<Min*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        output += offset->toString();
    }
    else if (dynamic_cast<Rightshift*>(_offset) != 0) {
        Rightshift* offset = dynamic_cast<Rightshift*>(_offset);
        output += offset->toString();
    }
    output += ")";
    return output;
}
    
int Rightshift::interpret(inputOutput_t env) {
    int output;
    
    if (dynamic_cast<Var*>(_value) != 0) {
        Var* value = dynamic_cast<Var*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        output = value->interpret();
    }
    else if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Div*>(_value) != 0) {
        Div* value = dynamic_cast<Div*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Min*>(_value) != 0) {
        Min* value = dynamic_cast<Min*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        output = value->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        output = value->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        output = output >> offset->interpret(env);
    }
    else if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        output = output >> offset->interpret();
    }
    else if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        output = output >> offset->interpret(env);
    }
    else if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        output = output >> offset->interpret(env);
    }
    else if (dynamic_cast<Div*>(_offset) != 0) {
        Div* offset = dynamic_cast<Div*>(_offset);
        output = output >> offset->interpret(env);
    }
    else if (dynamic_cast<Min*>(_offset) != 0) {
        Min* offset = dynamic_cast<Min*>(_offset);
        output = output >> offset->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        output = output >> offset->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        output = output >> offset->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_offset) != 0) {
        Rightshift* offset = dynamic_cast<Rightshift*>(_offset);
        output = output >> offset->interpret(env);
    }
    
    return output;
}
    
int Rightshift::depth() {
    int depth;
    
    if (dynamic_cast<Var*>(_value) != 0) {
        Var* value = dynamic_cast<Var*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Div*>(_value) != 0) {
        Div* value = dynamic_cast<Div*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Min*>(_value) != 0) {
        Min* value = dynamic_cast<Min*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        depth = value->depth();
    }
    else if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        depth = value->depth();
    }
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Div*>(_offset) != 0) {
        Div* offset = dynamic_cast<Div*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Min*>(_offset) != 0) {
        Min* offset = dynamic_cast<Min*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    else if (dynamic_cast<Rightshift*>(_offset) != 0) {
        Rightshift* offset = dynamic_cast<Rightshift*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    return depth;
}

int Rightshift::getNumOfOpsInProg(string opName) {
    if (opName == "RIGHTSHIFT" || opName == "ALL") {
        return _value->getNumOfOpsInProg(opName) + _offset->getNumOfOpsInProg(opName) + 1;
    }
    return _value->getNumOfOpsInProg(opName) + _offset->getNumOfOpsInProg(opName);
}

int Rightshift::getNumOfSymbolsInProg(string symbolName) {
    return _value->getNumOfSymbolsInProg(symbolName) + _offset->getNumOfSymbolsInProg(symbolName);
}

int Rightshift::getExponentOfSymbolInProg(string symbolName) {
    return max(_value->getExponentOfSymbolInProg(symbolName), _offset->getExponentOfSymbolInProg(symbolName));
}

/******************************************
Constructs: Lt
*/
Lt::Lt(IntType* left, IntType* right) {
    _left = left;
    _right = right;
}

string Lt::toString() {
    string output = "(";
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output += left->toString();
    }
    
    output += " < ";
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        output += right->toString();
    }
    output += ")";
    return output;
}
    
bool Lt::interpret(inputOutput_t env) {
    int leftValue;
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        leftValue = left->interpret();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        leftValue = left->interpret(env);
    }
    
    int rightValue;
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        rightValue = right->interpret();
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        rightValue = right->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        rightValue = right->interpret(env);
    }
    return leftValue < rightValue;
}
    
int Lt::depth() {
    int depth;
    
    if (dynamic_cast<Var*>(_left) != 0) {
        Var* left = dynamic_cast<Var*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Div*>(_left) != 0) {
        Div* left = dynamic_cast<Div*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Min*>(_left) != 0) {
        Min* left = dynamic_cast<Min*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Div*>(_right) != 0) {
        Div* right = dynamic_cast<Div*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Min*>(_right) != 0) {
        Min* right = dynamic_cast<Min*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    return depth;
}

int Lt::getNumOfOpsInProg(string opName) {
    if (opName == "LT" || opName == "ALL") {
        return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName);
}

int Lt::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
}

int Lt::getExponentOfSymbolInProg(string symbolName) {
    return max(_left->getExponentOfSymbolInProg(symbolName), _right->getExponentOfSymbolInProg(symbolName));
}

/******************************************
Constructs: And
*/
And::And(BoolType* left, BoolType* right) {
    _left = left;
    _right = right;
}
    
string And::toString() {
    string output = "(";
    
    if (dynamic_cast<F*>(_left) != 0) {
        F* left = dynamic_cast<F*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Not*>(_left) != 0) {
        Not* left = dynamic_cast<Not*>(_left);
        output += left->toString();
    }
    
    output += " && ";
    
    if (dynamic_cast<F*>(_right) != 0) {
        F* right = dynamic_cast<F*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Lt*>(_right) != 0) {
        Lt* right = dynamic_cast<Lt*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<And*>(_right) != 0) {
        And* right = dynamic_cast<And*>(_right);
        output += right->toString();
    }
    else if (dynamic_cast<Not*>(_right) != 0) {
        Not* right = dynamic_cast<Not*>(_right);
        output += right->toString();
    }
    output += ")";
    return output;
}
    
bool And::interpret(inputOutput_t env) {
    bool output;
    
    if (dynamic_cast<F*>(_left) != 0) {
        F* left = dynamic_cast<F*>(_left);
        output = left->interpret();
    }
    else if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        output = left->interpret(env);
    }
    else if (dynamic_cast<Not*>(_left) != 0) {
        Not* left = dynamic_cast<Not*>(_left);
        output = left->interpret(env);
    }
    
    if (dynamic_cast<F*>(_right) != 0) {
        F* right = dynamic_cast<F*>(_right);
        output &= right->interpret();
    }
    else if (dynamic_cast<Lt*>(_right) != 0) {
        Lt* right = dynamic_cast<Lt*>(_right);
        output &= right->interpret(env);
    }
    else if (dynamic_cast<And*>(_right) != 0) {
        And* right = dynamic_cast<And*>(_right);
        output &= right->interpret(env);
    }
    else if (dynamic_cast<Not*>(_right) != 0) {
        Not* right = dynamic_cast<Not*>(_right);
        output &= right->interpret(env);
    }
    return output;
}
    
int And::depth() {
    int depth;
    
    if (dynamic_cast<F*>(_left) != 0) {
        F* left = dynamic_cast<F*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Not*>(_left) != 0) {
        Not* left = dynamic_cast<Not*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<F*>(_right) != 0) {
        F* right = dynamic_cast<F*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Lt*>(_right) != 0) {
        Lt* right = dynamic_cast<Lt*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<And*>(_right) != 0) {
        And* right = dynamic_cast<And*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    else if (dynamic_cast<Not*>(_right) != 0) {
        Not* right = dynamic_cast<Not*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    return depth;
}

int And::getNumOfOpsInProg(string opName) {
    if (opName == "AND" || opName == "ALL") {
        return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName);
}

int And::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
}

int And::getExponentOfSymbolInProg(string symbolName) {
    return max(_left->getExponentOfSymbolInProg(symbolName), _right->getExponentOfSymbolInProg(symbolName));
}

/******************************************
Constructs: Not
*/
Not::Not(BoolType* left) {
    _left = left;
}

string Not::toString() {
    string output = "(! ";
    
    if (dynamic_cast<F*>(_left) != 0) {
        F* left = dynamic_cast<F*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        output += left->toString();
    }
    else if (dynamic_cast<Not*>(_left) != 0) {
        Not* left = dynamic_cast<Not*>(_left);
        output += left->toString();
    }
    output += " )";
    return output;
}
    
bool Not::interpret(inputOutput_t env) {
    bool leftValue;
    if (dynamic_cast<F*>(_left) != 0) {
        F* left = dynamic_cast<F*>(_left);
        leftValue = left->interpret();
    }
    else if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        leftValue = left->interpret(env);
    }
    else if (dynamic_cast<Not*>(_left) != 0) {
        Not* left = dynamic_cast<Not*>(_left);
        leftValue = left->interpret(env);
    }
    return !leftValue;
}
    
int Not::depth() {
    int depth;
    if (dynamic_cast<F*>(_left) != 0) {
        F* left = dynamic_cast<F*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        depth = left->depth();
    }
    else if (dynamic_cast<Not*>(_left) != 0) {
        Not* left = dynamic_cast<Not*>(_left);
        depth = left->depth();
    }
    return depth+1;
}

int Not::getNumOfOpsInProg(string opName) {
    if (opName == "NOT" || opName == "ALL") {
        return _left->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName);
}

int Not::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName);
}

int Not::getExponentOfSymbolInProg(string symbolName) {
    return _left->getExponentOfSymbolInProg(symbolName);
}

/******************************************
Constructs: Ite
*/
Ite::Ite(BoolType* cond, IntType* tcase, IntType* fcase) {
    _cond = cond;
    _tcase = tcase;
    _fcase = fcase;
}
    
string Ite::toString() {
    string output = "(if ";
    
    if (dynamic_cast<F*>(_cond) != 0) {
        F* cond = dynamic_cast<F*>(_cond);
        output += cond->toString();
    }
    else if (dynamic_cast<Lt*>(_cond) != 0) {
        Lt* cond = dynamic_cast<Lt*>(_cond);
        output += cond->toString();
    }
    else if (dynamic_cast<And*>(_cond) != 0) {
        And* cond = dynamic_cast<And*>(_cond);
        output += cond->toString();
    }
    else if (dynamic_cast<Not*>(_cond) != 0) {
        Not* cond = dynamic_cast<Not*>(_cond);
        output += cond->toString();
    }
    
    output += " then ";
    
    if (dynamic_cast<Var*>(_tcase) != 0) {
        Var* tcase = dynamic_cast<Var*>(_tcase);
        output += tcase->toString();
    }
    else if (dynamic_cast<Num*>(_tcase) != 0) {
        Num* tcase = dynamic_cast<Num*>(_tcase);
        output += tcase->toString();
    }
    else if (dynamic_cast<Plus*>(_tcase) != 0) {
        Plus* tcase = dynamic_cast<Plus*>(_tcase);
        output += tcase->toString();
    }
    else if (dynamic_cast<Times*>(_tcase) != 0) {
        Times* tcase = dynamic_cast<Times*>(_tcase);
        output += tcase->toString();
    }
    else if (dynamic_cast<Div*>(_tcase) != 0) {
        Div* tcase = dynamic_cast<Div*>(_tcase);
        output += tcase->toString();
    }
    else if (dynamic_cast<Min*>(_tcase) != 0) {
        Min* tcase = dynamic_cast<Min*>(_tcase);
        output += tcase->toString();
    }
    else if (dynamic_cast<Minus*>(_tcase) != 0) {
        Minus* tcase = dynamic_cast<Minus*>(_tcase);
        output += tcase->toString();
    }
    else if (dynamic_cast<Leftshift*>(_tcase) != 0) {
        Leftshift* tcase = dynamic_cast<Leftshift*>(_tcase);
        output += tcase->toString();
    }
    else if (dynamic_cast<Rightshift*>(_tcase) != 0) {
        Rightshift* tcase = dynamic_cast<Rightshift*>(_tcase);
        output += tcase->toString();
    }
    
    output += " else ";
    
    if (dynamic_cast<Var*>(_fcase) != 0) {
        Var* fcase = dynamic_cast<Var*>(_fcase);
        output += fcase->toString();
    }
    else if (dynamic_cast<Num*>(_fcase) != 0) {
        Num* fcase = dynamic_cast<Num*>(_fcase);
        output += fcase->toString();
    }
    else if (dynamic_cast<Plus*>(_fcase) != 0) {
        Plus* fcase = dynamic_cast<Plus*>(_fcase);
        output += fcase->toString();
    }
    else if (dynamic_cast<Times*>(_fcase) != 0) {
        Times* fcase = dynamic_cast<Times*>(_fcase);
        output += fcase->toString();
    }
    else if (dynamic_cast<Div*>(_fcase) != 0) {
        Div* fcase = dynamic_cast<Div*>(_fcase);
        output += fcase->toString();
    }
    else if (dynamic_cast<Min*>(_fcase) != 0) {
        Min* fcase = dynamic_cast<Min*>(_fcase);
        output += fcase->toString();
    }
    else if (dynamic_cast<Minus*>(_fcase) != 0) {
        Minus* fcase = dynamic_cast<Minus*>(_fcase);
        output += fcase->toString();
    }
    else if (dynamic_cast<Leftshift*>(_fcase) != 0) {
        Leftshift* fcase = dynamic_cast<Leftshift*>(_fcase);
        output += fcase->toString();
    }
    else if (dynamic_cast<Rightshift*>(_fcase) != 0) {
        Rightshift* fcase = dynamic_cast<Rightshift*>(_fcase);
        output += fcase->toString();
    }
    
    output += " )";
    return output;
}
    
int Ite::interpret(inputOutput_t env) {
    bool condValue;
    int tcaseValue;
    int fcaseValue;
    
    if (dynamic_cast<F*>(_cond) != 0) {
        F* cond = dynamic_cast<F*>(_cond);
        condValue = cond->interpret();
    }
    else if (dynamic_cast<Lt*>(_cond) != 0) {
        Lt* cond = dynamic_cast<Lt*>(_cond);
        condValue = cond->interpret(env);
    }
    else if (dynamic_cast<And*>(_cond) != 0) {
        And* cond = dynamic_cast<And*>(_cond);
        condValue = cond->interpret(env);
    }
    else if (dynamic_cast<Not*>(_cond) != 0) {
        Not* cond = dynamic_cast<Not*>(_cond);
        condValue = cond->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_tcase) != 0) {
        Var* tcase = dynamic_cast<Var*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    else if (dynamic_cast<Num*>(_tcase) != 0) {
        Num* tcase = dynamic_cast<Num*>(_tcase);
        tcaseValue = tcase->interpret();
    }
    else if (dynamic_cast<Plus*>(_tcase) != 0) {
        Plus* tcase = dynamic_cast<Plus*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    else if (dynamic_cast<Times*>(_tcase) != 0) {
        Times* tcase = dynamic_cast<Times*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    else if (dynamic_cast<Div*>(_tcase) != 0) {
        Div* tcase = dynamic_cast<Div*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    else if (dynamic_cast<Min*>(_tcase) != 0) {
        Min* tcase = dynamic_cast<Min*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_tcase) != 0) {
        Minus* tcase = dynamic_cast<Minus*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_tcase) != 0) {
        Leftshift* tcase = dynamic_cast<Leftshift*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_tcase) != 0) {
        Rightshift* tcase = dynamic_cast<Rightshift*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_fcase) != 0) {
        Var* fcase = dynamic_cast<Var*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    else if (dynamic_cast<Num*>(_fcase) != 0) {
        Num* fcase = dynamic_cast<Num*>(_fcase);
        fcaseValue = fcase->interpret();
    }
    else if (dynamic_cast<Plus*>(_fcase) != 0) {
        Plus* fcase = dynamic_cast<Plus*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    else if (dynamic_cast<Times*>(_fcase) != 0) {
        Times* fcase = dynamic_cast<Times*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    else if (dynamic_cast<Div*>(_fcase) != 0) {
        Div* fcase = dynamic_cast<Div*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    else if (dynamic_cast<Min*>(_fcase) != 0) {
        Min* fcase = dynamic_cast<Min*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    else if (dynamic_cast<Minus*>(_fcase) != 0) {
        Minus* fcase = dynamic_cast<Minus*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    else if (dynamic_cast<Leftshift*>(_fcase) != 0) {
        Leftshift* fcase = dynamic_cast<Leftshift*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    else if (dynamic_cast<Rightshift*>(_fcase) != 0) {
        Rightshift* fcase = dynamic_cast<Rightshift*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    
    return condValue ? tcaseValue : fcaseValue;
}
    
int Ite::depth() {
    int depth;
    
    if (dynamic_cast<F*>(_cond) != 0) {
        F* cond = dynamic_cast<F*>(_cond);
        depth = cond->depth();
    }
    else if (dynamic_cast<Lt*>(_cond) != 0) {
        Lt* cond = dynamic_cast<Lt*>(_cond);
        depth = cond->depth();
    }
    else if (dynamic_cast<And*>(_cond) != 0) {
        And* cond = dynamic_cast<And*>(_cond);
        depth = cond->depth();
    }
    else if (dynamic_cast<Not*>(_cond) != 0) {
        Not* cond = dynamic_cast<Not*>(_cond);
        depth = cond->depth();
    }
    
    if (dynamic_cast<Var*>(_tcase) != 0) {
        Var* tcase = dynamic_cast<Var*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    else if (dynamic_cast<Num*>(_tcase) != 0) {
        Num* tcase = dynamic_cast<Num*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    else if (dynamic_cast<Plus*>(_tcase) != 0) {
        Plus* tcase = dynamic_cast<Plus*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    else if (dynamic_cast<Times*>(_tcase) != 0) {
        Times* tcase = dynamic_cast<Times*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    else if (dynamic_cast<Div*>(_tcase) != 0) {
        Div* tcase = dynamic_cast<Div*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    else if (dynamic_cast<Min*>(_tcase) != 0) {
        Min* tcase = dynamic_cast<Min*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    else if (dynamic_cast<Minus*>(_tcase) != 0) {
        Minus* tcase = dynamic_cast<Minus*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    else if (dynamic_cast<Leftshift*>(_tcase) != 0) {
        Leftshift* tcase = dynamic_cast<Leftshift*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    else if (dynamic_cast<Rightshift*>(_tcase) != 0) {
        Rightshift* tcase = dynamic_cast<Rightshift*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    
    if (dynamic_cast<Var*>(_fcase) != 0) {
        Var* fcase = dynamic_cast<Var*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (dynamic_cast<Num*>(_fcase) != 0) {
        Num* fcase = dynamic_cast<Num*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (dynamic_cast<Plus*>(_fcase) != 0) {
        Plus* fcase = dynamic_cast<Plus*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (dynamic_cast<Times*>(_fcase) != 0) {
        Times* fcase = dynamic_cast<Times*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (dynamic_cast<Div*>(_fcase) != 0) {
        Div* fcase = dynamic_cast<Div*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (dynamic_cast<Min*>(_fcase) != 0) {
        Min* fcase = dynamic_cast<Min*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (dynamic_cast<Minus*>(_fcase) != 0) {
        Minus* fcase = dynamic_cast<Minus*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (dynamic_cast<Leftshift*>(_fcase) != 0) {
        Leftshift* fcase = dynamic_cast<Leftshift*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (dynamic_cast<Rightshift*>(_fcase) != 0) {
        Rightshift* fcase = dynamic_cast<Rightshift*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    
    return depth;
}

int Ite::getNumOfOpsInProg(string opName) {
    if (opName == "ITE" || opName == "ALL") {
        return _cond->getNumOfOpsInProg(opName) + _tcase->getNumOfOpsInProg(opName) + _fcase->getNumOfOpsInProg(opName) + 1;
    }
    return _cond->getNumOfOpsInProg(opName) + _tcase->getNumOfOpsInProg(opName) + _fcase->getNumOfOpsInProg(opName);
}

int Ite::getNumOfSymbolsInProg(string symbolName) {
    return _cond->getNumOfSymbolsInProg(symbolName) + _tcase->getNumOfSymbolsInProg(symbolName) + _fcase->getNumOfSymbolsInProg(symbolName);
}

int Ite::getExponentOfSymbolInProg(string symbolName) {
    return max(_cond->getExponentOfSymbolInProg(symbolName), max(_tcase->getExponentOfSymbolInProg(symbolName), _fcase->getExponentOfSymbolInProg(symbolName)));
}
