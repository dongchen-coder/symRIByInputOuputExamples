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
    if (dynamic_cast<Var*>(this) != 0) {
        Var* var = dynamic_cast<Var*>(this);
        output = var->toString();
    }
    if (dynamic_cast<Plus*>(this) != 0) {
        Plus* plus = dynamic_cast<Plus*>(this);
        output = plus->toString();
    }
    if (dynamic_cast<Minus*>(this) != 0) {
        Minus* minus = dynamic_cast<Minus*>(this);
        output = minus->toString();
    }
    if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        output = times->toString();
    }
    if (dynamic_cast<Leftshift*>(this) != 0) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(this);
        output = leftshift->toString();
    }
    if (dynamic_cast<Rightshift*>(this) != 0) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(this);
        output = rightshift->toString();
    }
    if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        output = times->toString();
    }
    if (dynamic_cast<Ite*>(this) != 0) {
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
    if (dynamic_cast<Var*>(this) != 0) {
        Var* var = dynamic_cast<Var*>(this);
        depth = var->depth();
    }
    if (dynamic_cast<Plus*>(this) != 0) {
        Plus* plus = dynamic_cast<Plus*>(this);
        depth = plus->depth();
    }
    if (dynamic_cast<Minus*>(this) != 0) {
        Minus* minus = dynamic_cast<Minus*>(this);
        depth = minus->depth();
    }
    if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        depth = times->depth();
    }
    if (dynamic_cast<Leftshift*>(this) != 0) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(this);
        depth = leftshift->depth();
    }
    if (dynamic_cast<Rightshift*>(this) != 0) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(this);
        depth = rightshift->depth();
    }
    if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        depth = times->depth();
    }
    if (dynamic_cast<Ite*>(this) != 0) {
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
    if (dynamic_cast<Var*>(this) != 0) {
        Var* var = dynamic_cast<Var*>(this);
        numOfOpsInProg = var->getNumOfOpsInProg(opName);
    }
    if (dynamic_cast<Plus*>(this) != 0) {
        Plus* plus = dynamic_cast<Plus*>(this);
        numOfOpsInProg = plus->getNumOfOpsInProg(opName);
    }
    if (dynamic_cast<Minus*>(this) != 0) {
        Minus* minus = dynamic_cast<Minus*>(this);
        numOfOpsInProg = minus->getNumOfOpsInProg(opName);
    }
    if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        numOfOpsInProg = times->getNumOfOpsInProg(opName);
    }
    if (dynamic_cast<Leftshift*>(this) != 0) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(this);
        numOfOpsInProg = leftshift->getNumOfOpsInProg(opName);
    }
    if (dynamic_cast<Rightshift*>(this) != 0) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(this);
        numOfOpsInProg = rightshift->getNumOfOpsInProg(opName);
    }
    if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        numOfOpsInProg = times->getNumOfOpsInProg(opName);
    }
    if (dynamic_cast<Ite*>(this) != 0) {
        Ite* ite = dynamic_cast<Ite*>(this);
        numOfOpsInProg = ite->getNumOfOpsInProg(opName);
    }
    return numOfOpsInProg;
}

int IntType::getNumOfSymbolsInProg(string symbolName) {
    int numOfSymbolsInProg;
    if (dynamic_cast<Num*>(this) != 0) {
        Num* num = dynamic_cast<Num*>(this);
        numOfSymbolsInProg = num->getNumOfSymbolsInProg(symbolName);
    }
    if (dynamic_cast<Var*>(this) != 0) {
        Var* var = dynamic_cast<Var*>(this);
        numOfSymbolsInProg = var->getNumOfSymbolsInProg(symbolName);
    }
    if (dynamic_cast<Plus*>(this) != 0) {
        Plus* plus = dynamic_cast<Plus*>(this);
        numOfSymbolsInProg = plus->getNumOfSymbolsInProg(symbolName);
    }
    if (dynamic_cast<Minus*>(this) != 0) {
        Minus* minus = dynamic_cast<Minus*>(this);
        numOfSymbolsInProg = minus->getNumOfSymbolsInProg(symbolName);
    }
    if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        numOfSymbolsInProg = times->getNumOfSymbolsInProg(symbolName);
    }
    if (dynamic_cast<Leftshift*>(this) != 0) {
        Leftshift* leftshift = dynamic_cast<Leftshift*>(this);
        numOfSymbolsInProg = leftshift->getNumOfSymbolsInProg(symbolName);
    }
    if (dynamic_cast<Rightshift*>(this) != 0) {
        Rightshift* rightshift = dynamic_cast<Rightshift*>(this);
        numOfSymbolsInProg = rightshift->getNumOfSymbolsInProg(symbolName);
    }
    if (dynamic_cast<Times*>(this) != 0) {
        Times* times = dynamic_cast<Times*>(this);
        numOfSymbolsInProg = times->getNumOfSymbolsInProg(symbolName);
    }
    if (dynamic_cast<Ite*>(this) != 0) {
        Ite* ite = dynamic_cast<Ite*>(this);
        numOfSymbolsInProg = ite->getNumOfSymbolsInProg(symbolName);
    }
    return numOfSymbolsInProg;
}

BoolType::BoolType() {};

string BoolType::toString() {
    string output;
    if (dynamic_cast<F*>(this) != 0) {
        F* f = dynamic_cast<F*>(this);
        output = f->toString();
    }
    if (dynamic_cast<Not*>(this) != 0) {
        Not* n = dynamic_cast<Not*>(this);
        output = n->toString();
    }
    if (dynamic_cast<And*>(this) != 0) {
        And* a = dynamic_cast<And*>(this);
        output = a->toString();
    }
    if (dynamic_cast<Lt*>(this) != 0) {
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
    if (dynamic_cast<Not*>(this) != 0) {
        Not* n = dynamic_cast<Not*>(this);
        depth = n->depth();
    }
    if (dynamic_cast<And*>(this) != 0) {
        And* a = dynamic_cast<And*>(this);
        depth = a->depth();
    }
    if (dynamic_cast<Lt*>(this) != 0) {
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
    if (dynamic_cast<Not*>(this) != 0) {
        Not* n = dynamic_cast<Not*>(this);
        numOfOpsInProg = n->getNumOfOpsInProg(opName);
    }
    if (dynamic_cast<And*>(this) != 0) {
        And* a = dynamic_cast<And*>(this);
        numOfOpsInProg = a->getNumOfOpsInProg(opName);
    }
    if (dynamic_cast<Lt*>(this) != 0) {
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
    if (dynamic_cast<Not*>(this) != 0) {
        Not* n = dynamic_cast<Not*>(this);
        numOfSymbolsInProg = n->getNumOfSymbolsInProg(symbolName);
    }
    if (dynamic_cast<And*>(this) != 0) {
        And* a = dynamic_cast<And*>(this);
        numOfSymbolsInProg = a->getNumOfSymbolsInProg(symbolName);
    }
    if (dynamic_cast<Lt*>(this) != 0) {
        Lt* lt = dynamic_cast<Lt*>(this);
        numOfSymbolsInProg = lt->getNumOfSymbolsInProg(symbolName);
    }
    return numOfSymbolsInProg;
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
    if (symbolName == "false") {
        return 1;
    }
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
    if (symbolName == "" || symbolName == _name) {
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
    if (symbolName == to_string(_num)) {
        return 1;
    }
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output += left->toString();
    }
    
    output += " + ";
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output = left->interpret();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output = left->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->interpret(env);
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->interpret();
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->interpret(env);
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->interpret(env);
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    
    return depth;
}

int Plus::getNumOfOpsInProg(string opName) {
    if (opName == "PLUS") {
        return _left->getNumOfOpsInProg(opName) + _left->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _left->getNumOfOpsInProg(opName);
}

int Plus::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output += left->toString();
    }
    
    output += " - ";
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output = left->interpret();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output = left->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output -= right->interpret(env);
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output -= right->interpret();
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output -= right->interpret(env);
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output -= right->interpret(env);
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
         Minus* right = dynamic_cast<Minus*>(_right);
        output -= right->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output -= right->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    return depth;
}

int Minus::getNumOfOpsInProg(string opName) {
    if (opName == "MINUS") {
        return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName);
}

int Minus::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output += left->toString();
    }
    
    output += " * ";
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output = left->interpret();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output = left->interpret(env);
    }
    
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output *= right->interpret(env);
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output *= right->interpret();
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output *= right->interpret(env);
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output *= right->interpret(env);
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output *= right->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output *= right->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    return depth;
}

int Times::getNumOfOpsInProg(string opName) {
    if (opName == "TIMES") {
        return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName);
}

int Times::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
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
    if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        output += value->toString();
    }
    if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        output += value->toString();
    }
    if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        output += value->toString();
    }
    if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        output += value->toString();
    }
    if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        output += value->toString();
    }
    if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        output += value->toString();
    }
    
    output += " << ";
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Rightshift*>(_offset) != 0) {
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
    if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        output = value->interpret();
    }
    if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        output = value->interpret(env);
    }
    if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        output = value->interpret(env);
    }
    if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        output = value->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        output = value->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        output = value->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        output = output << offset->interpret(env);
    }
    if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        output = output << offset->interpret();
    }
    if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        output = output << offset->interpret(env);
    }
    if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        output = output << offset->interpret(env);
    }
    if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        output = output << offset->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        output = output << offset->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_offset) != 0) {
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
    if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        depth = value->depth();
    }
    if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        depth = value->depth();
    }
    if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        depth = value->depth();
    }
    if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        depth = value->depth();
    }
    if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        depth = value->depth();
    }
    if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        depth = value->depth();
    }
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Rightshift*>(_offset) != 0) {
        Rightshift* offset = dynamic_cast<Rightshift*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    return depth;
}

int Leftshift::getNumOfOpsInProg(string opName) {
    if (opName == "LEFTSHIFT") {
        return _value->getNumOfOpsInProg(opName) + _offset->getNumOfOpsInProg(opName) + 1;
    }
    return _value->getNumOfOpsInProg(opName) + _offset->getNumOfOpsInProg(opName);
}

int Leftshift::getNumOfSymbolsInProg(string symbolName) {
    return _value->getNumOfSymbolsInProg(symbolName) + _offset->getNumOfSymbolsInProg(symbolName);
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
    if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        output += value->toString();
    }
    if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        output += value->toString();
    }
    if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        output += value->toString();
    }
    if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        output += value->toString();
    }
    if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        output += value->toString();
    }
    if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        output += value->toString();
    }
    
    output += " >> ";
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        output += offset->toString();
    }
    if (dynamic_cast<Rightshift*>(_offset) != 0) {
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
    if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        output = value->interpret();
    }
    if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        output = value->interpret(env);
    }
    if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        output = value->interpret(env);
    }
    if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        output = value->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        output = value->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        output = value->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        output = output >> offset->interpret(env);
    }
    if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        output = output >> offset->interpret();
    }
    if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        output = output >> offset->interpret(env);
    }
    if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        output = output >> offset->interpret(env);
    }
    if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        output = output >> offset->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        output = output >> offset->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_offset) != 0) {
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
    if (dynamic_cast<Num*>(_value) != 0) {
        Num* value = dynamic_cast<Num*>(_value);
        depth = value->depth();
    }
    if (dynamic_cast<Plus*>(_value) != 0) {
        Plus* value = dynamic_cast<Plus*>(_value);
        depth = value->depth();
    }
    if (dynamic_cast<Times*>(_value) != 0) {
        Times* value = dynamic_cast<Times*>(_value);
        depth = value->depth();
    }
    if (dynamic_cast<Minus*>(_value) != 0) {
        Minus* value = dynamic_cast<Minus*>(_value);
        depth = value->depth();
    }
    if (dynamic_cast<Leftshift*>(_value) != 0) {
        Leftshift* value = dynamic_cast<Leftshift*>(_value);
        depth = value->depth();
    }
    if (dynamic_cast<Rightshift*>(_value) != 0) {
        Rightshift* value = dynamic_cast<Rightshift*>(_value);
        depth = value->depth();
    }
    
    if (dynamic_cast<Var*>(_offset) != 0) {
        Var* offset = dynamic_cast<Var*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Num*>(_offset) != 0) {
        Num* offset = dynamic_cast<Num*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Plus*>(_offset) != 0) {
        Plus* offset = dynamic_cast<Plus*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Times*>(_offset) != 0) {
        Times* offset = dynamic_cast<Times*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Minus*>(_offset) != 0) {
        Minus* offset = dynamic_cast<Minus*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Leftshift*>(_offset) != 0) {
        Leftshift* offset = dynamic_cast<Leftshift*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    if (dynamic_cast<Rightshift*>(_offset) != 0) {
        Rightshift* offset = dynamic_cast<Rightshift*>(_offset);
        depth = max(depth, offset->depth()) + 1;
    }
    return depth;
}

int Rightshift::getNumOfOpsInProg(string opName) {
    if (opName == "RIGHTSHIFT") {
        return _value->getNumOfOpsInProg(opName) + _offset->getNumOfOpsInProg(opName) + 1;
    }
    return _value->getNumOfOpsInProg(opName) + _offset->getNumOfOpsInProg(opName);
}

int Rightshift::getNumOfSymbolsInProg(string symbolName) {
    return _value->getNumOfSymbolsInProg(symbolName) + _offset->getNumOfSymbolsInProg(symbolName);
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        output += left->toString();
    }
    
    output += " < ";
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        leftValue = left->interpret();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        leftValue = left->interpret(env);
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        leftValue = left->interpret(env);
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        leftValue = left->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        leftValue = left->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        leftValue = left->interpret(env);
    }
    
    int rightValue;
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        rightValue = right->interpret(env);
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        rightValue = right->interpret();
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        rightValue = right->interpret(env);
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        rightValue = right->interpret(env);
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        rightValue = right->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        rightValue = right->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
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
    if (dynamic_cast<Num*>(_left) != 0) {
        Num* left = dynamic_cast<Num*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Plus*>(_left) != 0) {
        Plus* left = dynamic_cast<Plus*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Times*>(_left) != 0) {
        Times* left = dynamic_cast<Times*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Minus*>(_left) != 0) {
        Minus* left = dynamic_cast<Minus*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Leftshift*>(_left) != 0) {
        Leftshift* left = dynamic_cast<Leftshift*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Rightshift*>(_left) != 0) {
        Rightshift* left = dynamic_cast<Rightshift*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<Var*>(_right) != 0) {
        Var* right = dynamic_cast<Var*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Num*>(_right) != 0) {
        Num* right = dynamic_cast<Num*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Plus*>(_right) != 0) {
        Plus* right = dynamic_cast<Plus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Times*>(_right) != 0) {
        Times* right = dynamic_cast<Times*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Minus*>(_right) != 0) {
        Minus* right = dynamic_cast<Minus*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Leftshift*>(_right) != 0) {
        Leftshift* right = dynamic_cast<Leftshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Rightshift*>(_right) != 0) {
        Rightshift* right = dynamic_cast<Rightshift*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    return depth;
}

int Lt::getNumOfOpsInProg(string opName) {
    if (opName == "LT") {
        return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName);
}

int Lt::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
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
    if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Not*>(_left) != 0) {
        Not* left = dynamic_cast<Not*>(_left);
        output += left->toString();
    }
    
    output += " && ";
    
    if (dynamic_cast<F*>(_right) != 0) {
        F* right = dynamic_cast<F*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Lt*>(_right) != 0) {
        Lt* right = dynamic_cast<Lt*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<And*>(_right) != 0) {
        And* right = dynamic_cast<And*>(_right);
        output += right->toString();
    }
    if (dynamic_cast<Not*>(_right) != 0) {
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
    if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        output = left->interpret(env);
    }
    if (dynamic_cast<Not*>(_left) != 0) {
        Not* left = dynamic_cast<Not*>(_left);
        output = left->interpret(env);
    }
    
    if (dynamic_cast<F*>(_right) != 0) {
        F* right = dynamic_cast<F*>(_right);
        output &= right->interpret();
    }
    if (dynamic_cast<Lt*>(_right) != 0) {
        Lt* right = dynamic_cast<Lt*>(_right);
        output &= right->interpret(env);
    }
    if (dynamic_cast<And*>(_right) != 0) {
        And* right = dynamic_cast<And*>(_right);
        output &= right->interpret(env);
    }
    if (dynamic_cast<Not*>(_right) != 0) {
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
    if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Not*>(_left) != 0) {
        Not* left = dynamic_cast<Not*>(_left);
        depth = left->depth();
    }
    
    if (dynamic_cast<F*>(_right) != 0) {
        F* right = dynamic_cast<F*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Lt*>(_right) != 0) {
        Lt* right = dynamic_cast<Lt*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<And*>(_right) != 0) {
        And* right = dynamic_cast<And*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    if (dynamic_cast<Not*>(_right) != 0) {
        Not* right = dynamic_cast<Not*>(_right);
        depth = max(depth, right->depth()) + 1;
    }
    return depth;
}

int And::getNumOfOpsInProg(string opName) {
    if (opName == "AND") {
        return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName) + _right->getNumOfOpsInProg(opName);
}

int And::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName) + _right->getNumOfSymbolsInProg(symbolName);
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
    if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        output += left->toString();
    }
    if (dynamic_cast<Not*>(_left) != 0) {
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
    if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        leftValue = left->interpret(env);
    }
    if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        leftValue = left->interpret(env);
    }
    if (dynamic_cast<Not*>(_left) != 0) {
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
    if (dynamic_cast<Lt*>(_left) != 0) {
        Lt* left = dynamic_cast<Lt*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<And*>(_left) != 0) {
        And* left = dynamic_cast<And*>(_left);
        depth = left->depth();
    }
    if (dynamic_cast<Not*>(_left) != 0) {
        Not* left = dynamic_cast<Not*>(_left);
        depth = left->depth();
    }
    return depth+1;
}

int Not::getNumOfOpsInProg(string opName) {
    if (opName == "NOT") {
        return _left->getNumOfOpsInProg(opName) + 1;
    }
    return _left->getNumOfOpsInProg(opName);
}

int Not::getNumOfSymbolsInProg(string symbolName) {
    return _left->getNumOfSymbolsInProg(symbolName);
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
    if (dynamic_cast<Lt*>(_cond) != 0) {
        Lt* cond = dynamic_cast<Lt*>(_cond);
        output += cond->toString();
    }
    if (dynamic_cast<And*>(_cond) != 0) {
        And* cond = dynamic_cast<And*>(_cond);
        output += cond->toString();
    }
    if (dynamic_cast<Not*>(_cond) != 0) {
        Not* cond = dynamic_cast<Not*>(_cond);
        output += cond->toString();
    }
    
    output += " then ";
    
    if (dynamic_cast<Var*>(_tcase) != 0) {
        Var* tcase = dynamic_cast<Var*>(_tcase);
        output += tcase->toString();
    }
    if (dynamic_cast<Num*>(_tcase) != 0) {
        Num* tcase = dynamic_cast<Num*>(_tcase);
        output += tcase->toString();
    }
    if (dynamic_cast<Plus*>(_tcase) != 0) {
        Plus* tcase = dynamic_cast<Plus*>(_tcase);
        output += tcase->toString();
    }
    if (dynamic_cast<Times*>(_tcase) != 0) {
        Times* tcase = dynamic_cast<Times*>(_tcase);
        output += tcase->toString();
    }
    if (dynamic_cast<Minus*>(_tcase) != 0) {
        Minus* tcase = dynamic_cast<Minus*>(_tcase);
        output += tcase->toString();
    }
    if (dynamic_cast<Leftshift*>(_tcase) != 0) {
        Leftshift* tcase = dynamic_cast<Leftshift*>(_tcase);
        output += tcase->toString();
    }
    if (dynamic_cast<Rightshift*>(_tcase) != 0) {
        Rightshift* tcase = dynamic_cast<Rightshift*>(_tcase);
        output += tcase->toString();
    }
    
    output += " else ";
    
    if (dynamic_cast<Var*>(_fcase) != 0) {
        Var* fcase = dynamic_cast<Var*>(_fcase);
        output += fcase->toString();
    }
    if (dynamic_cast<Num*>(_fcase) != 0) {
        Num* fcase = dynamic_cast<Num*>(_fcase);
        output += fcase->toString();
    }
    if (dynamic_cast<Plus*>(_fcase) != 0) {
        Plus* fcase = dynamic_cast<Plus*>(_fcase);
        output += fcase->toString();
    }
    if (dynamic_cast<Times*>(_fcase) != 0) {
        Times* fcase = dynamic_cast<Times*>(_fcase);
        output += fcase->toString();
    }
    if (dynamic_cast<Minus*>(_fcase) != 0) {
        Minus* fcase = dynamic_cast<Minus*>(_fcase);
        output += fcase->toString();
    }
    if (dynamic_cast<Leftshift*>(_fcase) != 0) {
        Leftshift* fcase = dynamic_cast<Leftshift*>(_fcase);
        output += fcase->toString();
    }
    if (dynamic_cast<Rightshift*>(_fcase) != 0) {
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
    if (dynamic_cast<Lt*>(_cond) != 0) {
        Lt* cond = dynamic_cast<Lt*>(_cond);
        condValue = cond->interpret(env);
    }
    if (dynamic_cast<And*>(_cond) != 0) {
        And* cond = dynamic_cast<And*>(_cond);
        condValue = cond->interpret(env);
    }
    if (dynamic_cast<Not*>(_cond) != 0) {
        Not* cond = dynamic_cast<Not*>(_cond);
        condValue = cond->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_tcase) != 0) {
        Var* tcase = dynamic_cast<Var*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    if (dynamic_cast<Num*>(_tcase) != 0) {
        Num* tcase = dynamic_cast<Num*>(_tcase);
        tcaseValue = tcase->interpret();
    }
    if (dynamic_cast<Plus*>(_tcase) != 0) {
        Plus* tcase = dynamic_cast<Plus*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    if (dynamic_cast<Times*>(_tcase) != 0) {
        Times* tcase = dynamic_cast<Times*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    if (dynamic_cast<Minus*>(_tcase) != 0) {
        Minus* tcase = dynamic_cast<Minus*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_tcase) != 0) {
        Leftshift* tcase = dynamic_cast<Leftshift*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_tcase) != 0) {
        Rightshift* tcase = dynamic_cast<Rightshift*>(_tcase);
        tcaseValue = tcase->interpret(env);
    }
    
    if (dynamic_cast<Var*>(_fcase) != 0) {
        Var* fcase = dynamic_cast<Var*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    if (dynamic_cast<Num*>(_fcase) != 0) {
        Num* fcase = dynamic_cast<Num*>(_fcase);
        fcaseValue = fcase->interpret();
    }
    if (dynamic_cast<Plus*>(_fcase) != 0) {
        Plus* fcase = dynamic_cast<Plus*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    if (dynamic_cast<Times*>(_fcase) != 0) {
        Times* fcase = dynamic_cast<Times*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    if (dynamic_cast<Minus*>(_fcase) != 0) {
        Minus* fcase = dynamic_cast<Minus*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    if (dynamic_cast<Leftshift*>(_fcase) != 0) {
        Leftshift* fcase = dynamic_cast<Leftshift*>(_fcase);
        fcaseValue = fcase->interpret(env);
    }
    if (dynamic_cast<Rightshift*>(_fcase) != 0) {
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
    if (dynamic_cast<Lt*>(_cond) != 0) {
        Lt* cond = dynamic_cast<Lt*>(_cond);
        depth = cond->depth();
    }
    if (dynamic_cast<And*>(_cond) != 0) {
        And* cond = dynamic_cast<And*>(_cond);
        depth = cond->depth();
    }
    if (dynamic_cast<Not*>(_cond) != 0) {
        Not* cond = dynamic_cast<Not*>(_cond);
        depth = cond->depth();
    }
    
    if (dynamic_cast<Var*>(_tcase) != 0) {
        Var* tcase = dynamic_cast<Var*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    if (dynamic_cast<Num*>(_tcase) != 0) {
        Num* tcase = dynamic_cast<Num*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    if (dynamic_cast<Plus*>(_tcase) != 0) {
        Plus* tcase = dynamic_cast<Plus*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    if (dynamic_cast<Times*>(_tcase) != 0) {
        Times* tcase = dynamic_cast<Times*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    if (dynamic_cast<Minus*>(_tcase) != 0) {
        Minus* tcase = dynamic_cast<Minus*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    if (dynamic_cast<Leftshift*>(_tcase) != 0) {
        Leftshift* tcase = dynamic_cast<Leftshift*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    if (dynamic_cast<Rightshift*>(_tcase) != 0) {
        Rightshift* tcase = dynamic_cast<Rightshift*>(_tcase);
        depth = max(depth, tcase->depth());
    }
    
    if (dynamic_cast<Var*>(_fcase) != 0) {
        Var* fcase = dynamic_cast<Var*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    if (dynamic_cast<Num*>(_fcase) != 0) {
        Num* fcase = dynamic_cast<Num*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    if (dynamic_cast<Plus*>(_fcase) != 0) {
        Plus* fcase = dynamic_cast<Plus*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    if (dynamic_cast<Times*>(_fcase) != 0) {
        Times* fcase = dynamic_cast<Times*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    if (dynamic_cast<Minus*>(_fcase) != 0) {
        Minus* fcase = dynamic_cast<Minus*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    if (dynamic_cast<Leftshift*>(_fcase) != 0) {
        Leftshift* fcase = dynamic_cast<Leftshift*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    if (dynamic_cast<Rightshift*>(_fcase) != 0) {
        Rightshift* fcase = dynamic_cast<Rightshift*>(_fcase);
        depth = max(depth, fcase->depth()) + 1;
    }
    
    return depth;
}

int Ite::getNumOfOpsInProg(string opName) {
    if (opName == "ITE") {
        return _cond->getNumOfOpsInProg(opName) + _tcase->getNumOfOpsInProg(opName) + _fcase->getNumOfOpsInProg(opName) + 1;
    }
    return _cond->getNumOfOpsInProg(opName) + _tcase->getNumOfOpsInProg(opName) + _fcase->getNumOfOpsInProg(opName);
}

int Ite::getNumOfSymbolsInProg(string symbolName) {
    return _cond->getNumOfSymbolsInProg(symbolName) + _tcase->getNumOfSymbolsInProg(symbolName) + _fcase->getNumOfSymbolsInProg(symbolName);
}
