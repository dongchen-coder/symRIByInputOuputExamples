#include "langDef.hpp"

/******************************************
 Base types: int and bool
 */
BaseType::BaseType() {};

string BaseType::toString() {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->toString();
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->toString();
    }
    else {
        throw runtime_error("BaseType::toString() operates on UNKNOWN type!");
    }
}

int BaseType::depth() {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->depth();
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->depth();
    }
    else {
        throw runtime_error("BaseType::depth() operates on UNKNOWN type!");
    }
}

int BaseType::get_generation() {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->get_generation();
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->get_generation();
    }
    else {
        throw runtime_error("BaseType::get_generation() operates on UNKNOWN type!");
    }
}

void BaseType::set_generation(int generation) {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->set_generation(generation);
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->set_generation(generation);
    }
    else {
        throw runtime_error("BaseType::set_generation() operates on UNKNOWN type!");
    }
}

vector<int> BaseType::getLexicalOrder(int num_of_vars, map<string, int>& vars_orders) {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->getLexicalOrder(num_of_vars, vars_orders);
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->getLexicalOrder(num_of_vars, vars_orders);
    }
    else {
        throw runtime_error("BaseType::getLexicalOrder() operates on UNKNOWN type!");
    }
}

int BaseType::getNumberOfOpsInProg(string opName) {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->getNumberOfOpsInProg(opName);
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->getNumberOfOpsInProg(opName);
    }
    else {
        throw runtime_error("BaseType::getNumberOfOpsInProg() operates on UNKNOWN type!");
    }
}

int BaseType::getNumberOfVarsInProg(string varName) {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->getNumberOfVarsInProg(varName);
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->getNumberOfVarsInProg(varName);
    }
    else {
        throw runtime_error("BaseType::getNumberOfVarsInProg() operates on UNKNOWN type!");
    }
}

int BaseType::getExponentOfVarInProg(string varName) {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->getExponentOfVarInProg(varName);
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->getExponentOfVarInProg(varName);
    }
    else {
        throw runtime_error("BaseType::getExponentOfVarInProg() operates on UNKNOWN type!");
    }
}

/*
 Int and Bool type
 */

IntType::IntType() {};

string IntType::toString() {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->toString();
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->toString();
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->toString();
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->toString();
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->toString();
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->toString();
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->toString();
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->toString();
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->toString();
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->toString();
    }
    else {
        throw runtime_error("IntType::toString() operates on UNKNOWN type!");
    }
}

int IntType::interpret(inputOutput_t env) {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->interpret();
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->interpret(env);
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->interpret(env);
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->interpret(env);
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->interpret(env);
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->interpret(env);
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->interpret(env);
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->interpret(env);
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->interpret(env);
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->interpret(env);
    }
    else {
        throw runtime_error("IntType::interpret() operates on UNKNOWN type!");
    }
}

int IntType::depth() {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->depth();
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->depth();
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->depth();
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->depth();
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->depth();
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->depth();
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->depth();
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->depth();
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->depth();
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->depth();
    }
    else {
        throw runtime_error("IntType::depth() operates on UNKNOWN type!");
    }
}

int IntType::get_generation() {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->get_generation();
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->get_generation();
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->get_generation();
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->get_generation();
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->get_generation();
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->get_generation();
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->get_generation();
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->get_generation();
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->get_generation();
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->get_generation();
    }
    else {
        throw runtime_error("IntType::get_generation() operates on UNKNOWN type!");
    }
}

void IntType::set_generation(int generation) {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->set_generation(generation);
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->set_generation(generation);
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->set_generation(generation);
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->set_generation(generation);
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->set_generation(generation);
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->set_generation(generation);
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->set_generation(generation);
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->set_generation(generation);
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->set_generation(generation);
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->set_generation(generation);
    }
    else {
        throw runtime_error("IntType::set_generation() operates on UNKNOWN type!");
    }
}

vector<int> IntType::getLexicalOrder(int num_of_vars, map<string, int>& vars_orders) {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->getLexicalOrder(num_of_vars, vars_orders);
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->getLexicalOrder(num_of_vars, vars_orders);
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->getLexicalOrder(num_of_vars, vars_orders);
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->getLexicalOrder(num_of_vars, vars_orders);
    }
    else {
        throw runtime_error("IntType::getLexicalOrder() operates on UNKNOWN type!");
    }
}

int IntType::getNumberOfOpsInProg(string opName) {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->getNumberOfOpsInProg(opName);
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->getNumberOfOpsInProg(opName);
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->getNumberOfOpsInProg(opName);
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->getNumberOfOpsInProg(opName);
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->getNumberOfOpsInProg(opName);
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->getNumberOfOpsInProg(opName);
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->getNumberOfOpsInProg(opName);
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->getNumberOfOpsInProg(opName);
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->getNumberOfOpsInProg(opName);
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->getNumberOfOpsInProg(opName);
    }
    else {
        throw runtime_error("IntType::getNumberOfOpsInProg() operates on UNKNOWN type!");
    }
}

int IntType::getNumberOfVarsInProg(string varName) {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->getNumberOfVarsInProg(varName);
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->getNumberOfVarsInProg(varName);
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->getNumberOfVarsInProg(varName);
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->getNumberOfVarsInProg(varName);
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->getNumberOfVarsInProg(varName);
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->getNumberOfVarsInProg(varName);
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->getNumberOfVarsInProg(varName);
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->getNumberOfVarsInProg(varName);
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->getNumberOfVarsInProg(varName);
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->getNumberOfVarsInProg(varName);
    }
    else {
        throw runtime_error("IntType::getNumberOfVarsInProg() operates on UNKNOWN type");
    }
}

int IntType::getExponentOfVarInProg(string varName) {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->getExponentOfVarInProg(varName);
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->getExponentOfVarInProg(varName);
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->getExponentOfVarInProg(varName);
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->getExponentOfVarInProg(varName);
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->getExponentOfVarInProg(varName);
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->getExponentOfVarInProg(varName);
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->getExponentOfVarInProg(varName);
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->getExponentOfVarInProg(varName);
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->getExponentOfVarInProg(varName);
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->getExponentOfVarInProg(varName);
    }
    else {
        throw runtime_error("IntType::getExponentOfVarInProg() operates on UNKOWN type!");
    }
}


BoolType::BoolType() {};

string BoolType::toString() {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->toString();
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->toString();
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->toString();
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->toString();
    }
    else {
        throw runtime_error("BoolType::toString() operates on UNKOWN type!");
    }
}

int BoolType::depth() {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->depth();
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->depth();
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->depth();
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->depth();
    }
    else {
        throw runtime_error("BoolType::depth() operates on UNKOWN type!");
    }
}

int BoolType::get_generation() {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->get_generation();
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->get_generation();
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->get_generation();
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->get_generation();
    }
    else {
        throw runtime_error("BoolType::get_generation() operates on UNKOWN type!");
    }
}

void BoolType::set_generation(int generation) {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->set_generation(generation);
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->set_generation(generation);
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->set_generation(generation);
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->set_generation(generation);
    }
    else {
        throw runtime_error("BoolType::set_generation() operates on UNKOWN type!");
    }
}

vector<int> BoolType::getLexicalOrder(int num_of_vars, map<string, int>& vars_orders) {
    if (auto n = dynamic_cast<Not*>(this)) {
        return n->getLexicalOrder(num_of_vars, vars_orders);
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->getLexicalOrder(num_of_vars, vars_orders);
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->getLexicalOrder(num_of_vars, vars_orders);
    }
    else {
        throw runtime_error("BoolType::getLexicalOrder() operates on UNKOWN type!");
    }
}

int BoolType::getNumberOfOpsInProg(string opName) {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->getNumberOfOpsInProg(opName);
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->getNumberOfOpsInProg(opName);
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->getNumberOfOpsInProg(opName);
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->getNumberOfOpsInProg(opName);
    }
    else {
        throw runtime_error("BoolType::getNumberOfOpsInProg() operates on UNKOWN type!");
    }
}

int BoolType::getNumberOfVarsInProg(string varName) {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->getNumberOfVarsInProg(varName);
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->getNumberOfVarsInProg(varName);
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->getNumberOfVarsInProg(varName);
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->getNumberOfVarsInProg(varName);
    }
    else {
        throw runtime_error("BoolType::getNumberOfVarsInProg() operates on UNKOWN type!");
    }
}

int BoolType::getExponentOfVarInProg(string varName) {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->getExponentOfVarInProg(varName);
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->getExponentOfVarInProg(varName);
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->getExponentOfVarInProg(varName);
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->getExponentOfVarInProg(varName);
    }
    else {
        throw runtime_error("BoolType::getExponentOfVarInProg() operates on UNKOWN type!");
    }
}

/******************************************
Constructs: False
*/
F::F() {
    _generation = 0;
};

string F::toString() {
    return "false";
}
    
bool F::interpret() {
    return false;
}
    
int F::depth() {
    return 1;
}

int F::get_generation() {
    return _generation;
}

void F::set_generation(int generation) {
    _generation = generation;
}

int F::getNumberOfOpsInProg(string opName) {
    return 0;
}

int F::getNumberOfVarsInProg(string varName) {
    if (varName == "false" || varName == "ALL") {
        return 1;
    }
    return 0;
}

int F::getExponentOfVarInProg(string varName) {
    return 0;
}

/******************************************
Constructs: Var
*/
Var::Var(string name) {
    _name = name;
    _generation = 0;
}
    
string Var::toString() {
    return _name;
}
    
int Var::interpret(inputOutput_t env) {
    if (env.find(_name) == env.end()) throw runtime_error("Var::interpret(): _name " + _name + " is not found in env");
    return env[_name];
}
    
int Var::depth() {
    return 1;
}

int Var::get_generation() {
    return _generation;
}

void Var::set_generation(int generation) {
    _generation = generation;
}

vector<int> Var::getLexicalOrder(int num_of_vars, map<string, int>& vars_orders) {
    vector<int> lex(num_of_vars, 0);
    if (vars_orders.find(this->toString()) == vars_orders.end()) throw runtime_error("Var::getLexicalOrder() var not found in keys of vars_orders");
    if (vars_orders[this->toString()] > lex.size()) throw runtime_error("Var::getLexicalOrder() number of vars is greater than lex vector size");
    if (vars_orders[this->toString()] == 0) throw runtime_error("Var::getLexicalOrder() var's index is 0");
    lex[vars_orders[this->toString()]-1]++;
    return lex;
}

int Var::getNumberOfOpsInProg(string opName) {
    return 0;
}

int Var::getNumberOfVarsInProg(string varName) {
    if (varName == "ALL" ||
        varName == "VAR" ||
        varName == _name ||
        (varName.size() < _name.size() && varName == _name.substr(0, varName.size())) ) {
        return 1;
    }
    return 0;
}

int Var::getExponentOfVarInProg(string varName) {
    if (varName == _name ||
        (varName.size() < _name.size() && varName == _name.substr(0, varName.size())) ) {
        return 1;
    }
    return 0;
}

/******************************************
Constructs: Num
*/
Num::Num(int val) {
    _num = val;
    _generation = 0;
}

Num::Num(Num* a, Num* b, string op) {
    if (a == nullptr) throw runtime_error("Num a is null");
    if (b == nullptr) throw runtime_error("Num b is null");
    
    if (op == "TIMES") _num = a->interpret() * b->interpret();
    else if (op == "PLUS") _num = a->interpret() + b->interpret();
    else throw runtime_error("Num::Num() UNKOWN op type");
    _generation = max(a->get_generation(), b->get_generation()) + 10;
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

int Num::get_generation() {
    return _generation;
}

void Num::set_generation(int generation) {
    _generation = generation;
}

vector<int> Num::getLexicalOrder(int num_of_vars, map<string, int>& vars_orders) {
    vector<int> lex(num_of_vars, 0);
    return lex;
}

int Num::getNumberOfOpsInProg(string opName) {
    return 0;
}

int Num::getNumberOfVarsInProg(string varName) {
    if (varName == to_string(_num) || varName == "ALL" || varName == "NUM") {
        return 1;
    }
    return 0;
}

int Num::getExponentOfVarInProg(string varName) {
    return 0;
}

/******************************************
Constructs: Plus
*/
Plus::Plus(IntType* left, IntType* right) {
    if (left == nullptr) throw runtime_error("Plus: left is null");
    if (right == nullptr) throw runtime_error("Plus: right is null");
    _left = left;
    _right = right;
    _generation = max(left->get_generation(), right->get_generation()) + 1;
}

string Plus::toString() {
    string output = "(";
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        output += left->toString();
    }
    else {
        throw runtime_error("Plus::toString() operates on UNKNOWN type!");
    }
    
    output += " + ";
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        output += right->toString();
    }
    else {
        throw runtime_error("Plus::toString() operates on UNKNOWN type!");
    }
    
    output += ")";
    return output;
}
    
int Plus::interpret(inputOutput_t env) {
    int output;
    if (auto left = dynamic_cast<Var*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        output = left->interpret();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        output = left->interpret(env);
    }
    else {
        throw runtime_error("Plus::interpret() operates on UNKNOWN type!");
    }
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        output += right->interpret(env);
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        output += right->interpret();
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        output += right->interpret(env);
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        output += right->interpret(env);
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        output += right->interpret(env);
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        output += right->interpret(env);
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        output += right->interpret(env);
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        output += right->interpret(env);
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        output += right->interpret(env);
    }
    else {
        throw runtime_error("Plus::interpret() operates on UNKNOWN type!");
    }
    
    return output;
}
    
int Plus::depth() {
    int depth;
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        depth = left->depth();
    }
    else {
        throw runtime_error("Plus::depth() operates on UNKNOWN type!");
    }
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else {
        throw runtime_error("Plus::interpret() operates on UNKNOWN type!");
    }
    
    return depth;
}

int Plus::get_generation() {
    return _generation;
}

void Plus::set_generation(int generation) {
    _generation = generation;
}

IntType* Plus::getLeft() {
    return _left;
}
IntType* Plus::getRight() {
    return _right;
}

vector<string> Plus::getTerms() {
    vector<string> terms;
    
    if (dynamic_cast<Var*>(_left)) {
        terms.push_back(_left->toString());
    }
    else if (auto left_times = dynamic_cast<Times*>(_left)) {
        if (dynamic_cast<Num*>(left_times->getLeft())) {
            terms.push_back(left_times->getRight()->toString());
        } else {
            terms.push_back(_left->toString());
        }
    }
    
    if (dynamic_cast<Var*>(_right)) {
        terms.push_back(_right->toString());
    }
    else if (auto right_times = dynamic_cast<Times*>(_right)) {
        if (dynamic_cast<Num*>(right_times->getRight())) {
            terms.push_back(right_times->getRight()->toString());
        } else {
            terms.push_back(_right->toString());
        }
    }
    else if (auto right_plus = dynamic_cast<Plus*>(_right)) {
        vector<string> terms_right = right_plus->getTerms();
        terms.insert(terms.end(), terms_right.begin(), terms_right.end());
    }
    return terms;
}

vector<int> Plus::getLexicalOrder(int num_of_vars, map<string, int>& vars_orders) {
    if (_right == nullptr) throw runtime_error("Plus::getLexicalOrder() _right is null");
    return _right->getLexicalOrder(num_of_vars, vars_orders);
}

int Plus::getNumberOfOpsInProg(string opName) {
    if (opName == "PLUS" || opName == "ALL") {
        return _left->getNumberOfOpsInProg(opName) + _left->getNumberOfOpsInProg(opName) + 1;
    }
    return _left->getNumberOfOpsInProg(opName) + _left->getNumberOfOpsInProg(opName);
}

int Plus::getNumberOfVarsInProg(string varName) {
    return _left->getNumberOfVarsInProg(varName) + _right->getNumberOfVarsInProg(varName);
}

int Plus::getExponentOfVarInProg(string varName) {
    return max(_left->getExponentOfVarInProg(varName), _right->getExponentOfVarInProg(varName));
}

/******************************************
Constructs: Minus
*/
Minus::Minus(IntType* left, IntType* right) {
    if (left == nullptr) throw runtime_error("Minus: left is null");
    if (right == nullptr) throw runtime_error("Minus: right is null");
    _left = left;
    _right = right;
    _generation = max(left->get_generation(), right->get_generation()) + 1;
}
    
string Minus::toString() {
    string output = "(";
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        output += left->toString();
    }
    else {
        throw runtime_error("Plus::toString() operates on UNKNOWN type!");
    }
    
    output += " - ";
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        output += right->toString();
    }
    else {
        throw runtime_error("Plus::toString() operates on UNKNOWN type!");
    }
    
    output += ")";
    return output;
}

int Minus::interpret(inputOutput_t env) {
    int output;
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        output = left->interpret();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        output = left->interpret(env);
    }
    else {
        throw runtime_error("Minus::interpret() operates on UNKNOWN type!");
    }
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        output -= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        output -= right->interpret();
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        output -= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        output -= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        output -= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        output -= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        output -= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        output -= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        output -= right->interpret(env);
    }
    else {
        throw runtime_error("Minus::interpret() operates on UNKNOWN type!");
    }
    
    return output;
}
    
int Minus::depth() {
    int depth;
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        depth = left->depth();
    }
    else {
        throw runtime_error("Minus::depth() operates on UNKNOWN type!");
    }
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else {
        throw runtime_error("Minus::depth() operates on UNKNOWN type!");
    }
    
    return depth;
}

int Minus::get_generation() {
    return _generation;
}

void Minus::set_generation(int generation) {
    _generation = generation;
}

int Minus::getNumberOfOpsInProg(string opName) {
    if (opName == "MINUS" || opName == "ALL") {
        return _left->getNumberOfOpsInProg(opName) + _right->getNumberOfOpsInProg(opName) + 1;
    }
    return _left->getNumberOfOpsInProg(opName) + _right->getNumberOfOpsInProg(opName);
}

int Minus::getNumberOfVarsInProg(string varName) {
    return _left->getNumberOfVarsInProg(varName) + _right->getNumberOfVarsInProg(varName);
}

int Minus::getExponentOfVarInProg(string varName) {
    return max(_left->getExponentOfVarInProg(varName), _right->getExponentOfVarInProg(varName));
}

/******************************************
Constructs: Times
*/
Times::Times(IntType* left, IntType* right) {
    if (left == nullptr) throw runtime_error("Times: left is null");
    if (right == nullptr) throw runtime_error("Times: right is null");
    _left = left;
    _right = right;
    //_left = new IntType;
    //_right = new IntType;
    //memcpy(_left, left, sizeof(IntType));
    //memcpy(_right, right, sizeof(IntType));
    _generation = max(left->get_generation(), right->get_generation()) + 1;
}
    
string Times::toString() {
    string output = "(";
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        output += left->toString();
    }
    else {
        throw runtime_error("Times::toString() operates on UNKNOWN type!");
    }
    
    output += " * ";
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        output += right->toString();
    }
    else {
        throw runtime_error("Times::toString() operates on UNKNOWN type!");
    }
    
    output += ")";
    return output;
}
    
int Times::interpret(inputOutput_t env) {
    int output;
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        output = left->interpret();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        output = left->interpret(env);
    }
    else {
        throw runtime_error("Times::interpret() operates on UNKNOWN type!");
    }
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        output *= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        output *= right->interpret();
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        output *= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        output *= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        output *= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        output *= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        output *= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        output *= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        output *= right->interpret(env);
    }
    else {
        throw runtime_error("Times::interpret() operates on UNKNOWN type!");
    }
    
    return output;
}
    
int Times::depth() {
    int depth;
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        depth = left->depth();
    }
    else {
        throw runtime_error("Times::depth() operates on UNKNOWN type!");
    }
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else {
        throw runtime_error("Times::depth() operates on UNKNOWN type!");
    }
    
    return depth;
}

int Times::get_generation() {
    return _generation;
}

void Times::set_generation(int generation) {
    _generation = generation;
}

IntType* Times::getLeft() {
    return _left;
}
IntType* Times::getRight() {
    return _right;
}

vector<string> Times::getFactors() {
    vector<string> factors;
    if (dynamic_cast<Var*>(_left)) {
        factors.push_back(_left->toString());
    }
    if (dynamic_cast<Var*>(_right)) {
        factors.push_back(_right->toString());
    }
    if (auto right_times = dynamic_cast<Times*>(_right)) {
        vector<string> factors_right = right_times->getFactors();
        factors.insert(factors.end(), factors_right.begin(), factors_right.end());
    }
    return factors;
}

vector<int> Times::getLexicalOrder(int num_of_vars, map<string, int>& vars_orders) {
    if (_left == nullptr) throw runtime_error("Times::getLexicalOrder() left is null");
    if (_right == nullptr) throw runtime_error("Times::getLexicalOrder() right is null");
    
    vector<int> lex_left(num_of_vars, 0);
    vector<int> lex_right(num_of_vars, 0);

    if (auto left_num = dynamic_cast<Num*>(_left)) {
        lex_left = left_num->getLexicalOrder(num_of_vars, vars_orders);
    }
    else if (auto left_var = dynamic_cast<Var*>(_left)) {
        lex_left = left_var->getLexicalOrder(num_of_vars, vars_orders);
    }
    else {
        throw runtime_error("Times::getLexicalOrder left is not a type of NUM/VAR");
    }
    if (auto right_var = dynamic_cast<Var*>(_right)) {
        lex_right = right_var->getLexicalOrder(num_of_vars, vars_orders);
    }
    else if (auto right_times = dynamic_cast<Times*>(_right)) {
        lex_right = right_times->getLexicalOrder(num_of_vars, vars_orders);
    }
    else {
        throw runtime_error("Times::getLexicalOrder right is not a type of NUM/VAR");
    }
    for (int i = 0; i < num_of_vars; i++) {
        lex_left[i] += lex_right[i];
    }
    return lex_left;
}

int Times::getNumberOfOpsInProg(string opName) {
    if (opName == "TIMES" || opName == "ALL") {
        return _left->getNumberOfOpsInProg(opName) + _right->getNumberOfOpsInProg(opName) + 1;
    }
    return _left->getNumberOfOpsInProg(opName) + _right->getNumberOfOpsInProg(opName);
}

int Times::getNumberOfVarsInProg(string varName) {
    return _left->getNumberOfVarsInProg(varName) + _right->getNumberOfVarsInProg(varName);
}

int Times::getExponentOfVarInProg(string varName) {
    return _left->getExponentOfVarInProg(varName) + _right->getExponentOfVarInProg(varName);
}

/******************************************
Constructs: Min
*/
Min::Min(IntType* left, IntType* right) {
    if (left == nullptr) throw runtime_error("Min: left is null");
    if (right == nullptr) throw runtime_error("Min: right is null");
    _left = left;
    _right = right;
    _generation = max(left->get_generation(), right->get_generation()) + 1;
}
string Min::toString() {
    string output = " min( ";
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        output += left->toString();
    }
    else {
        throw runtime_error("Min::toString() operates on UNKNOWN type!");
    }
    
    output += " , ";
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        output += right->toString();
    }
    else {
        throw runtime_error("Min::toString() operates on UNKNOWN type!");
    }
    
    output += " ) ";
    return output;
}
int Min::interpret(inputOutput_t env) {
    int leftValue;
    int rightValue;
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        leftValue = left->interpret();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        leftValue = left->interpret(env);
    }
    else {
        throw runtime_error("Min::interpret() operates on UNKNOWN type!");
    }
    
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        rightValue = right->interpret();
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        rightValue = right->interpret(env);
    }
    else {
        throw runtime_error("Min::interpret() operates on UNKNOWN type!");
    }
    
    return min(leftValue, rightValue);
}

int Min::depth() {
    int depth;
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        depth = left->depth();
    }
    else {
        throw runtime_error("Min::depth() operates on UNKNOWN type!");
    }
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else {
        throw runtime_error("Min::depth() operates on UNKNOWN type!");
    }
    
    return depth;
}

int Min::get_generation() {
    return _generation;
}

void Min::set_generation(int generation) {
    _generation = generation;
}

int Min::getNumberOfOpsInProg(string opName) {
    if (opName == "MIN" || opName == "ALL") {
        return _left->getNumberOfOpsInProg(opName) + _right->getNumberOfOpsInProg(opName) + 1;
    }
    return _left->getNumberOfOpsInProg(opName) + _right->getNumberOfOpsInProg(opName);
}

int Min::getNumberOfVarsInProg(string varName) {
    return _left->getNumberOfVarsInProg(varName) + _right->getNumberOfVarsInProg(varName);
}

int Min::getExponentOfVarInProg(string varName) {
    return max(_left->getExponentOfVarInProg(varName), _right->getExponentOfVarInProg(varName));
}

/******************************************
Constructs: Div
*/

Div::Div(IntType* dividend, IntType* divisor) {
    if (dividend == nullptr) throw runtime_error("Div: dividend is null");
    if (divisor == nullptr) throw runtime_error("Div: divisor is null");
    _dividend = dividend;
    _divisor = divisor;
    _generation = max(dividend->get_generation(), divisor->get_generation()) + 1;
}

string Div::toString() {
    string output = "(";
    
    if (auto dividend = dynamic_cast<Var*>(_dividend)) {
        output += dividend->toString();
    }
    else if (auto dividend = dynamic_cast<Num*>(_dividend)) {
        output += dividend->toString();
    }
    else if (auto dividend = dynamic_cast<Plus*>(_dividend)) {
        output += dividend->toString();
    }
    else if (auto dividend = dynamic_cast<Times*>(_dividend)) {
        output += dividend->toString();
    }
    else if (auto dividend = dynamic_cast<Div*>(_dividend)) {
        output += dividend->toString();
    }
    else if (auto dividend = dynamic_cast<Min*>(_dividend)) {
        output += dividend->toString();
    }
    else if (auto dividend = dynamic_cast<Minus*>(_dividend)) {
        output += dividend->toString();
    }
    else if (auto dividend = dynamic_cast<Leftshift*>(_dividend)) {
        output += dividend->toString();
    }
    else if (auto dividend = dynamic_cast<Rightshift*>(_dividend)) {
        output += dividend->toString();
    }
    else {
        throw runtime_error("Div::toString() operates on UNKNOWN type!");
    }
    
    output += " / ";
    
    if (auto divisor = dynamic_cast<Var*>(_divisor)) {
        output += divisor->toString();
    }
    else if (auto divisor = dynamic_cast<Num*>(_divisor)) {
        output += divisor->toString();
    }
    else if (auto divisor = dynamic_cast<Plus*>(_divisor)) {
        output += divisor->toString();
    }
    else if (auto divisor = dynamic_cast<Times*>(_divisor)) {
        output += divisor->toString();
    }
    else if (auto divisor = dynamic_cast<Div*>(_divisor)) {
        output += divisor->toString();
    }
    else if (auto divisor = dynamic_cast<Min*>(_divisor)) {
        output += divisor->toString();
    }
    else if (auto divisor = dynamic_cast<Minus*>(_divisor)) {
        output += divisor->toString();
    }
    else if (auto divisor = dynamic_cast<Leftshift*>(_divisor)) {
        output += divisor->toString();
    }
    else if (auto divisor = dynamic_cast<Rightshift*>(_divisor)) {
        output += divisor->toString();
    }
    else {
        throw runtime_error("Div::toString() operates on UNKNOWN type!");
    }
    
    output += ")";
    return output;
}

int Div::interpret(inputOutput_t env) {
    int dividendValue;
    int divisorValue;
    
    if (auto dividend = dynamic_cast<Var*>(_dividend)) {
        dividendValue = dividend->interpret(env);
    }
    else if (auto dividend = dynamic_cast<Num*>(_dividend)) {
        dividendValue = dividend->interpret();
    }
    else if (auto dividend = dynamic_cast<Plus*>(_dividend)) {
        dividendValue = dividend->interpret(env);
    }
    else if (auto dividend = dynamic_cast<Times*>(_dividend)) {
        dividendValue = dividend->interpret(env);
    }
    else if (auto dividend = dynamic_cast<Div*>(_dividend)) {
        dividendValue = dividend->interpret(env);
    }
    else if (auto dividend = dynamic_cast<Min*>(_dividend)) {
        dividendValue = dividend->interpret(env);
    }
    else if (auto dividend = dynamic_cast<Minus*>(_dividend))  {
        dividendValue = dividend->interpret(env);
    }
    else if (auto dividend = dynamic_cast<Leftshift*>(_dividend)) {
        dividendValue = dividend->interpret(env);
    }
    else if (auto dividend = dynamic_cast<Rightshift*>(_dividend)) {
        dividendValue = dividend->interpret(env);
    }
    else {
        throw runtime_error("Div::interpret() operates on UNKNOWN type!");
    }
    
    if (auto divisor = dynamic_cast<Var*>(_divisor)) {
        divisorValue = divisor->interpret(env);
    }
    else if (auto divisor = dynamic_cast<Num*>(_divisor)) {
        divisorValue = divisor->interpret();
    }
    else if (auto divisor = dynamic_cast<Plus*>(_divisor)) {
        divisorValue = divisor->interpret(env);
    }
    else if (auto divisor = dynamic_cast<Times*>(_divisor)) {
        divisorValue = divisor->interpret(env);
    }
    else if (auto divisor = dynamic_cast<Div*>(_divisor)) {
        divisorValue = divisor->interpret(env);
    }
    else if (auto divisor = dynamic_cast<Min*>(_divisor)) {
        divisorValue = divisor->interpret(env);
    }
    else if (auto divisor = dynamic_cast<Minus*>(_divisor)) {
        divisorValue = divisor->interpret(env);
    }
    else if (auto divisor = dynamic_cast<Leftshift*>(_divisor)) {
        divisorValue = divisor->interpret(env);
    }
    else if (auto divisor = dynamic_cast<Rightshift*>(_divisor)) {
        divisorValue = divisor->interpret(env);
    }
    else {
        throw runtime_error("Div::interpret() operates on UNKNOWN type!");
    }
    
    if (divisorValue == 0) {
        throw runtime_error("Divided by 0!");
    } else {
        return dividendValue / divisorValue;
    }
}

int Div::depth() {
    int depth;
    
    if (auto dividend = dynamic_cast<Var*>(_dividend)) {
        depth = dividend->depth();
    }
    else if (auto dividend = dynamic_cast<Num*>(_dividend)) {
        depth = dividend->depth();
    }
    else if (auto dividend = dynamic_cast<Plus*>(_dividend)) {
        depth = dividend->depth();
    }
    else if (auto dividend = dynamic_cast<Times*>(_dividend)) {
        depth = dividend->depth();
    }
    else if (auto dividend = dynamic_cast<Div*>(_dividend)) {
        depth = dividend->depth();
    }
    else if (auto dividend = dynamic_cast<Min*>(_dividend)) {
        depth = dividend->depth();
    }
    else if (auto dividend = dynamic_cast<Minus*>(_dividend))  {
        depth = dividend->depth();
    }
    else if (auto dividend = dynamic_cast<Leftshift*>(_dividend)) {
        depth = dividend->depth();
    }
    else if (auto dividend = dynamic_cast<Rightshift*>(_dividend)) {
        depth = dividend->depth();
    }
    else {
        throw runtime_error("Div::depth() operates on UNKNOWN type!");
    }
    
    if (auto divisor = dynamic_cast<Var*>(_divisor)) {
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (auto divisor = dynamic_cast<Num*>(_divisor)) {
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (auto divisor = dynamic_cast<Plus*>(_divisor)) {
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (auto divisor = dynamic_cast<Times*>(_divisor)) {
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (auto divisor = dynamic_cast<Div*>(_divisor)) {
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (auto divisor = dynamic_cast<Min*>(_divisor)) {
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (auto divisor = dynamic_cast<Minus*>(_divisor)) {
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (auto divisor = dynamic_cast<Leftshift*>(_divisor)) {
        depth = max(depth, divisor->depth()) + 1;
    }
    else if (auto divisor = dynamic_cast<Rightshift*>(_divisor)) {
        depth = max(depth, divisor->depth()) + 1;
    }
    else {
        throw runtime_error("Div::depth() operates on UNKNOWN type!");
    }
    
    return depth;
}

int Div::get_generation() {
    return _generation;
}

void Div::set_generation(int generation) {
    _generation = generation;
}

int Div::getNumberOfOpsInProg(string opName) {
    if (opName == "DIV" || opName == "ALL") {
        return _dividend->getNumberOfOpsInProg(opName) + _divisor->getNumberOfOpsInProg(opName) + 1;
    }
    return _dividend->getNumberOfOpsInProg(opName) + _divisor->getNumberOfOpsInProg(opName);
}

int Div::getNumberOfVarsInProg(string varName) {
    return _dividend->getNumberOfVarsInProg(varName) + _divisor->getNumberOfVarsInProg(varName);
}

int Div::getExponentOfVarInProg(string varName) {
    return _dividend->getExponentOfVarInProg(varName) - _divisor->getExponentOfVarInProg(varName);
}

/******************************************
Constructs: Leftshift
*/
Leftshift::Leftshift(IntType* value, IntType* offset) {
    if (value == nullptr) throw runtime_error("Leftshift: value is null");
    if (offset == nullptr) throw runtime_error("Leftshift: offset is null");
    _value = value;
    _offset = offset;
    _generation = max(value->get_generation(), offset->get_generation()) + 1;
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
    else {
        throw runtime_error("Leftshift::toString() operates on UNKNOWN type!");
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
    else {
        throw runtime_error("Leftshift::toString() operates on UNKNOWN type!");
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
    else {
        throw runtime_error("Leftshift::interpret() operates on UNKNOWN type!");
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
    else {
        throw runtime_error("Leftshift::interpret() operates on UNKNOWN type!");
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
    else {
        throw runtime_error("Leftshift::depth() operates on UNKNOWN type!");
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
    else {
        throw runtime_error("Leftshift::depth() operates on UNKNOWN type!");
    }
    
    return depth;
}

int Leftshift::get_generation() {
    return _generation;
}

void Leftshift::set_generation(int generation) {
    _generation = generation;
}

int Leftshift::getNumberOfOpsInProg(string opName) {
    if (opName == "LEFTSHIFT" || opName == "ALL") {
        return _value->getNumberOfOpsInProg(opName) + _offset->getNumberOfOpsInProg(opName) + 1;
    }
    return _value->getNumberOfOpsInProg(opName) + _offset->getNumberOfOpsInProg(opName);
}

int Leftshift::getNumberOfVarsInProg(string varName) {
    return _value->getNumberOfVarsInProg(varName) + _offset->getNumberOfVarsInProg(varName);
}

int Leftshift::getExponentOfVarInProg(string varName) {
    return max(_value->getExponentOfVarInProg(varName), _offset->getExponentOfVarInProg(varName));
}

/******************************************
Constructs: Leftshift
*/
Rightshift::Rightshift(IntType* value, IntType* offset) {
    if (value == nullptr) throw runtime_error("Rightshift: value is null");
    if (offset == nullptr) throw runtime_error("Rightshift: offset is null");
    _value = value;
    _offset = offset;
    _generation = max(value->get_generation(), offset->get_generation()) + 1;
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
    else {
        throw runtime_error("Rightshift::toString() operates on UNKNOWN type!");
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
    else {
        throw runtime_error("Rightshift::toString() operates on UNKNOWN type!");
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
    else {
        throw runtime_error("Rightshift::interpret() operates on UNKNOWN type!");
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
    else {
        throw runtime_error("Rightshift::interpret() operates on UNKNOWN type!");
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
    else {
        throw runtime_error("Rightshift::interpret() operates on UNKNOWN type!");
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
    else {
        throw runtime_error("Rightshift::interpret() operates on UNKNOWN type!");
    }
    
    return depth;
}

int Rightshift::get_generation() {
    return _generation;
}

void Rightshift::set_generation(int generation) {
    _generation = generation;
}

int Rightshift::getNumberOfOpsInProg(string opName) {
    if (opName == "RIGHTSHIFT" || opName == "ALL") {
        return _value->getNumberOfOpsInProg(opName) + _offset->getNumberOfOpsInProg(opName) + 1;
    }
    return _value->getNumberOfOpsInProg(opName) + _offset->getNumberOfOpsInProg(opName);
}

int Rightshift::getNumberOfVarsInProg(string varName) {
    return _value->getNumberOfVarsInProg(varName) + _offset->getNumberOfVarsInProg(varName);
}

int Rightshift::getExponentOfVarInProg(string varName) {
    return max(_value->getExponentOfVarInProg(varName), _offset->getExponentOfVarInProg(varName));
}

/******************************************
Constructs: Lt
*/
Lt::Lt(IntType* left, IntType* right) {
    if (left == nullptr) throw runtime_error("Lt: left is null");
    if (right == nullptr) throw runtime_error("Lt: right is null");
    _left = left;
    _right = right;
    _generation = max(left->get_generation(), right->get_generation()) + 1;
}

string Lt::toString() {
    string output = "(";
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        output += left->toString();
    }
    else {
        throw runtime_error("Lt::toString() operates on UNKNOWN type!");
    }
    
    output += " < ";
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        output += right->toString();
    }
    else {
        throw runtime_error("Lt::toString() operates on UNKNOWN type!");
    }
    
    output += ")";
    return output;
}
    
bool Lt::interpret(inputOutput_t env) {
    int leftValue;
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        leftValue = left->interpret();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        leftValue = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        leftValue = left->interpret(env);
    }
    else {
        throw runtime_error("Lt::interpret() operates on UNKNOWN type!");
    }
    
    int rightValue;
    if (auto right = dynamic_cast<Var*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        rightValue = right->interpret();
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        rightValue = right->interpret(env);
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        rightValue = right->interpret(env);
    }
    else {
        throw runtime_error("Lt::interpret() operates on UNKNOWN type!");
    }
    
    return leftValue < rightValue;
}
    
int Lt::depth() {
    int depth;
    
    if (auto left = dynamic_cast<Var*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Num*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Plus*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Times*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Div*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Min*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Minus*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Leftshift*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Rightshift*>(_left)) {
        depth = left->depth();
    }
    else {
        throw runtime_error("Lt::depth() operates on UNKNOWN type!");
    }
    
    if (auto right = dynamic_cast<Var*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Num*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Plus*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Times*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Div*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Min*>(_right))  {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Minus*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Leftshift*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Rightshift*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else {
        throw runtime_error("Lt::depth() operates on UNKNOWN type!");
    }
    
    return depth;
}

int Lt::get_generation() {
    return _generation;
}

void Lt::set_generation(int generation) {
    _generation = generation;
}

IntType* Lt::getLeft() {
    return _left;
}
IntType* Lt::getRight() {
    return _right;
}

vector<int> Lt::getLexicalOrder(int num_of_vars, map<string, int>& vars_orders) {
    vector<int> left_lex = _left->getLexicalOrder(num_of_vars, vars_orders);
    vector<int> right_lex = _right->getLexicalOrder(num_of_vars, vars_orders);
    left_lex.insert(left_lex.end(), right_lex.begin(), right_lex.end());
    return left_lex;
}

int Lt::getNumberOfOpsInProg(string opName) {
    if (opName == "LT" || opName == "ALL") {
        return _left->getNumberOfOpsInProg(opName) + _right->getNumberOfOpsInProg(opName) + 1;
    }
    return _left->getNumberOfOpsInProg(opName) + _right->getNumberOfOpsInProg(opName);
}

int Lt::getNumberOfVarsInProg(string varName) {
    return _left->getNumberOfVarsInProg(varName) + _right->getNumberOfVarsInProg(varName);
}

int Lt::getExponentOfVarInProg(string varName) {
    return max(_left->getExponentOfVarInProg(varName), _right->getExponentOfVarInProg(varName));
}

/******************************************
Constructs: And
*/
And::And(BoolType* left, BoolType* right) {
    if (left == nullptr) throw runtime_error("And: value is null");
    if (right == nullptr) throw runtime_error("And: offset is null");
    _left = left;
    _right = right;
    _generation = max(left->get_generation(), right->get_generation()) + 1;
}

string And::toString() {
    string output = "(";
    
    if (auto left = dynamic_cast<F*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Lt*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<And*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Not*>(_left)) {
        output += left->toString();
    }
    else {
        throw runtime_error("And::toString() operates on UNKNOWN type!");
    }
    
    output += " && ";
    
    if (auto right = dynamic_cast<F*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Lt*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<And*>(_right)) {
        output += right->toString();
    }
    else if (auto right = dynamic_cast<Not*>(_right)) {
        output += right->toString();
    }
    else {
        throw runtime_error("And::toString() operates on UNKNOWN type!");
    }
    
    output += ")";
    return output;
}
    
bool And::interpret(inputOutput_t env) {
    bool output;
    
    if (auto left = dynamic_cast<F*>(_left)) {
        output = left->interpret();
    }
    else if (auto left = dynamic_cast<Lt*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<And*>(_left)) {
        output = left->interpret(env);
    }
    else if (auto left = dynamic_cast<Not*>(_left)) {
        output = left->interpret(env);
    }
    else {
        throw runtime_error("And::interpret() operates on UNKNOWN type!");
    }
    
    if (auto right = dynamic_cast<F*>(_right)) {
        output &= right->interpret();
    }
    else if (auto right = dynamic_cast<Lt*>(_right)) {
        output &= right->interpret(env);
    }
    else if (auto right = dynamic_cast<And*>(_right)) {
        output &= right->interpret(env);
    }
    else if (auto right = dynamic_cast<Not*>(_right)) {
        output &= right->interpret(env);
    }
    else {
        throw runtime_error("And::interpret() operates on UNKNOWN type!");
    }
    
    return output;
}
    
int And::depth() {
    int depth;
    
    if (auto left = dynamic_cast<F*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Lt*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<And*>(_left)) {
        depth = left->depth();
    }
    else if (auto left = dynamic_cast<Not*>(_left)) {
        depth = left->depth();
    }
    else {
        throw runtime_error("And::depth() operates on UNKNOWN type!");
    }
    
    if (auto right = dynamic_cast<F*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Lt*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<And*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else if (auto right = dynamic_cast<Not*>(_right)) {
        depth = max(depth, right->depth()) + 1;
    }
    else {
        throw runtime_error("And::depth() operates on UNKNOWN type!");
    }
    
    return depth;
}

int And::get_generation() {
    return _generation;
}

void And::set_generation(int generation) {
    _generation = generation;
}

BoolType* And::getLeft() {
    return _left;
}
BoolType* And::getRight() {
    return _right;
}

vector<int> And::getLexicalOrder(int num_of_vars, map<string, int>& vars_orders) {
    return _right->getLexicalOrder(num_of_vars, vars_orders);
}

int And::getNumberOfOpsInProg(string opName) {
    if (opName == "AND" || opName == "ALL") {
        return _left->getNumberOfOpsInProg(opName) + _right->getNumberOfOpsInProg(opName) + 1;
    }
    return _left->getNumberOfOpsInProg(opName) + _right->getNumberOfOpsInProg(opName);
}

int And::getNumberOfVarsInProg(string varName) {
    return _left->getNumberOfVarsInProg(varName) + _right->getNumberOfVarsInProg(varName);
}

int And::getExponentOfVarInProg(string varName) {
    return max(_left->getExponentOfVarInProg(varName), _right->getExponentOfVarInProg(varName));
}

/******************************************
Constructs: Not
*/
Not::Not(BoolType* left) {
    if (left == nullptr) throw runtime_error("Not: value is null");
    _left = left;
    _generation = left->get_generation() + 1;
}

string Not::toString() {
    string output = "(! ";
    
    if (auto left = dynamic_cast<F*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Lt*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<And*>(_left)) {
        output += left->toString();
    }
    else if (auto left = dynamic_cast<Not*>(_left)) {
        output += left->toString();
    }
    else {
        throw runtime_error("Not::toString() operates on UNKNOWN type!");
    }
    
    output += " )";
    return output;
}
    
bool Not::interpret(inputOutput_t env) {
    if (auto left = dynamic_cast<F*>(_left)) {
        return !(left->interpret());
    }
    else if (auto left = dynamic_cast<Lt*>(_left)) {
        return !(left->interpret(env));
    }
    else if (auto left = dynamic_cast<And*>(_left)) {
        return !(left->interpret(env));
    }
    else if (auto left = dynamic_cast<Not*>(_left)) {
        return !(left->interpret(env));
    }
    else {
        throw runtime_error("Not::interpret() operates on UNKNOWN type!");
    }
}
    
int Not::depth() {
    if (auto left = dynamic_cast<F*>(_left)) {
        return left->depth();
    }
    else if (auto left = dynamic_cast<Lt*>(_left)) {
        return left->depth();
    }
    else if (auto left = dynamic_cast<And*>(_left)) {
        return left->depth();
    }
    else if (auto left = dynamic_cast<Not*>(_left)) {
        return left->depth();
    } else {
        throw runtime_error("Not::depth() operates on UNKNOWN type!");
    }
}

int Not::get_generation() {
    return _generation;
}

void Not::set_generation(int generation) {
    _generation = generation;
}

vector<int> Not::getLexicalOrder(int num_of_vars, map<string, int>& vars_orders) {
    return _left->getLexicalOrder(num_of_vars, vars_orders);
}

int Not::getNumberOfOpsInProg(string opName) {
    if (opName == "NOT" || opName == "ALL") {
        return _left->getNumberOfOpsInProg(opName) + 1;
    }
    return _left->getNumberOfOpsInProg(opName);
}

int Not::getNumberOfVarsInProg(string varName) {
    return _left->getNumberOfVarsInProg(varName);
}

int Not::getExponentOfVarInProg(string varName) {
    return _left->getExponentOfVarInProg(varName);
}

/******************************************
Constructs: Ite
*/
Ite::Ite(BoolType* cond, IntType* tcase, IntType* fcase) {
    if (cond == nullptr) throw runtime_error("Ite: cond is null");
    if (tcase == nullptr) throw runtime_error("Ite: tcase is null");
    if (fcase == nullptr) throw runtime_error("Ite: fcase is null");
    _cond = cond;
    _tcase = tcase;
    _fcase = fcase;
    _generation = max(cond->get_generation(), max(tcase->get_generation(), fcase->get_generation())) + 1;
}

string Ite::toString() {
    string output = "(if ";
    
    if (auto cond = dynamic_cast<F*>(_cond)) {
        output += cond->toString();
    }
    else if (auto cond = dynamic_cast<Lt*>(_cond)) {
        output += cond->toString();
    }
    else if (auto cond = dynamic_cast<And*>(_cond)) {
        output += cond->toString();
    }
    else if (auto cond = dynamic_cast<Not*>(_cond)) {
        output += cond->toString();
    }
    else {
        throw runtime_error("Ite::toString() operates on UNKNOWN type!");
    }
    
    output += " then ";
    
    if (auto tcase = dynamic_cast<Var*>(_tcase)) {
        output += tcase->toString();
    }
    else if (auto tcase = dynamic_cast<Num*>(_tcase)) {
        output += tcase->toString();
    }
    else if (auto tcase = dynamic_cast<Plus*>(_tcase)) {
        output += tcase->toString();
    }
    else if (auto tcase = dynamic_cast<Times*>(_tcase)) {
        output += tcase->toString();
    }
    else if (auto tcase = dynamic_cast<Div*>(_tcase)) {
        output += tcase->toString();
    }
    else if (auto tcase = dynamic_cast<Min*>(_tcase)) {
        output += tcase->toString();
    }
    else if (auto tcase = dynamic_cast<Minus*>(_tcase)) {
        output += tcase->toString();
    }
    else if (auto tcase = dynamic_cast<Leftshift*>(_tcase)) {
        output += tcase->toString();
    }
    else if (auto tcase = dynamic_cast<Rightshift*>(_tcase)) {
        output += tcase->toString();
    }
    else {
        throw runtime_error("Ite::toString() operates on UNKNOWN type!");
    }
    
    output += " else ";
    
    if (auto fcase = dynamic_cast<Var*>(_fcase)) {
        output += fcase->toString();
    }
    else if (auto fcase = dynamic_cast<Num*>(_fcase)) {
        output += fcase->toString();
    }
    else if (auto fcase = dynamic_cast<Plus*>(_fcase)) {
        output += fcase->toString();
    }
    else if (auto fcase = dynamic_cast<Times*>(_fcase)) {
        output += fcase->toString();
    }
    else if (auto fcase = dynamic_cast<Div*>(_fcase)) {
        output += fcase->toString();
    }
    else if (auto fcase = dynamic_cast<Min*>(_fcase)) {
        output += fcase->toString();
    }
    else if (auto fcase = dynamic_cast<Minus*>(_fcase)) {
        output += fcase->toString();
    }
    else if (auto fcase = dynamic_cast<Leftshift*>(_fcase)) {
        output += fcase->toString();
    }
    else if (auto fcase = dynamic_cast<Rightshift*>(_fcase)) {
        output += fcase->toString();
    }
    else {
        throw runtime_error("Ite::toString() operates on UNKNOWN type!");
    }
    
    output += " )";
    return output;
}
    
int Ite::interpret(inputOutput_t env) {
    bool condValue;
    int tcaseValue;
    int fcaseValue;
    
    if (auto cond = dynamic_cast<F*>(_cond)) {
        condValue = cond->interpret();
    }
    else if (auto cond = dynamic_cast<Lt*>(_cond)) {
        condValue = cond->interpret(env);
    }
    else if (auto cond = dynamic_cast<And*>(_cond)) {
        condValue = cond->interpret(env);
    }
    else if (auto cond = dynamic_cast<Not*>(_cond)) {
        condValue = cond->interpret(env);
    }
    else {
        throw runtime_error("Ite::interpret() operates on UNKOWN type!");
    }
    
    if (auto tcase = dynamic_cast<Var*>(_tcase)) {
        tcaseValue = tcase->interpret(env);
    }
    else if (auto tcase = dynamic_cast<Num*>(_tcase)) {
        tcaseValue = tcase->interpret();
    }
    else if (auto tcase = dynamic_cast<Plus*>(_tcase)) {
        tcaseValue = tcase->interpret(env);
    }
    else if (auto tcase = dynamic_cast<Times*>(_tcase)) {
        tcaseValue = tcase->interpret(env);
    }
    else if (auto tcase = dynamic_cast<Div*>(_tcase)) {
        tcaseValue = tcase->interpret(env);
    }
    else if (auto tcase = dynamic_cast<Min*>(_tcase)) {
        tcaseValue = tcase->interpret(env);
    }
    else if (auto tcase = dynamic_cast<Minus*>(_tcase)) {
        tcaseValue = tcase->interpret(env);
    }
    else if (auto tcase = dynamic_cast<Leftshift*>(_tcase)) {
        tcaseValue = tcase->interpret(env);
    }
    else if (auto tcase = dynamic_cast<Rightshift*>(_tcase)) {
        tcaseValue = tcase->interpret(env);
    }
    else {
        throw runtime_error("Ite::interpret() operates on UNKOWN type!");
    }
    
    if (auto fcase = dynamic_cast<Var*>(_fcase)) {
        fcaseValue = fcase->interpret(env);
    }
    else if (auto fcase = dynamic_cast<Num*>(_fcase)) {
        fcaseValue = fcase->interpret();
    }
    else if (auto fcase = dynamic_cast<Plus*>(_fcase)) {
        fcaseValue = fcase->interpret(env);
    }
    else if (auto fcase = dynamic_cast<Times*>(_fcase)) {
        fcaseValue = fcase->interpret(env);
    }
    else if (auto fcase = dynamic_cast<Div*>(_fcase)) {
        fcaseValue = fcase->interpret(env);
    }
    else if (auto fcase = dynamic_cast<Min*>(_fcase)) {
        fcaseValue = fcase->interpret(env);
    }
    else if (auto fcase = dynamic_cast<Minus*>(_fcase)) {
        fcaseValue = fcase->interpret(env);
    }
    else if (auto fcase = dynamic_cast<Leftshift*>(_fcase)) {
        fcaseValue = fcase->interpret(env);
    }
    else if (auto fcase = dynamic_cast<Rightshift*>(_fcase)) {
        fcaseValue = fcase->interpret(env);
    }
    else {
        throw runtime_error("Ite::interpret() operates on UNKOWN type!");
    }
    
    return condValue ? tcaseValue : fcaseValue;
}
    
int Ite::depth() {
    int depth;
    
    if (auto cond = dynamic_cast<F*>(_cond)) {
        depth = cond->depth();
    }
    else if (auto cond = dynamic_cast<Lt*>(_cond)) {
        depth = cond->depth();
    }
    else if (auto cond = dynamic_cast<And*>(_cond)) {
        depth = cond->depth();
    }
    else if (auto cond = dynamic_cast<Not*>(_cond)) {
        depth = cond->depth();
    }
    else {
        throw runtime_error("Ite::depth() operates on UNKOWN type!");
    }
    
    if (auto tcase = dynamic_cast<Var*>(_tcase)) {
        depth = max(depth, tcase->depth());
    }
    else if (auto tcase = dynamic_cast<Num*>(_tcase)) {
        depth = max(depth, tcase->depth());
    }
    else if (auto tcase = dynamic_cast<Plus*>(_tcase)) {
        depth = max(depth, tcase->depth());
    }
    else if (auto tcase = dynamic_cast<Times*>(_tcase)) {
        depth = max(depth, tcase->depth());
    }
    else if (auto tcase = dynamic_cast<Div*>(_tcase)) {
        depth = max(depth, tcase->depth());
    }
    else if (auto tcase = dynamic_cast<Min*>(_tcase)) {
        depth = max(depth, tcase->depth());
    }
    else if (auto tcase = dynamic_cast<Minus*>(_tcase)) {
        depth = max(depth, tcase->depth());
    }
    else if (auto tcase = dynamic_cast<Leftshift*>(_tcase)) {
        depth = max(depth, tcase->depth());
    }
    else if (auto tcase = dynamic_cast<Rightshift*>(_tcase)) {
        depth = max(depth, tcase->depth());
    }
    else {
        throw runtime_error("Ite::depth() operates on UNKOWN type!");
    }
    
    if (auto fcase = dynamic_cast<Var*>(_fcase)) {
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (auto fcase = dynamic_cast<Num*>(_fcase)) {
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (auto fcase = dynamic_cast<Plus*>(_fcase)) {
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (auto fcase = dynamic_cast<Times*>(_fcase)) {
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (auto fcase = dynamic_cast<Div*>(_fcase)) {
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (auto fcase = dynamic_cast<Min*>(_fcase)) {
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (auto fcase = dynamic_cast<Minus*>(_fcase)) {
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (auto fcase = dynamic_cast<Leftshift*>(_fcase)) {
        depth = max(depth, fcase->depth()) + 1;
    }
    else if (auto fcase = dynamic_cast<Rightshift*>(_fcase)) {
        depth = max(depth, fcase->depth()) + 1;
    }
    else {
        throw runtime_error("Ite::depth() operates on UNKOWN type!");
    }
    
    return depth;
}

int Ite::get_generation() {
    return _generation;
}

void Ite::set_generation(int generation) {
    _generation = generation;
}

int Ite::getNumberOfOpsInProg(string opName) {
    if (opName == "ITE" || opName == "ALL") {
        return _cond->getNumberOfOpsInProg(opName) + _tcase->getNumberOfOpsInProg(opName) + _fcase->getNumberOfOpsInProg(opName) + 1;
    }
    return _cond->getNumberOfOpsInProg(opName) + _tcase->getNumberOfOpsInProg(opName) + _fcase->getNumberOfOpsInProg(opName);
}

int Ite::getNumberOfVarsInProg(string varName) {
    return _cond->getNumberOfVarsInProg(varName) + _tcase->getNumberOfVarsInProg(varName) + _fcase->getNumberOfVarsInProg(varName);
}

int Ite::getExponentOfVarInProg(string varName) {
    return max(_cond->getExponentOfVarInProg(varName), max(_tcase->getExponentOfVarInProg(varName), _fcase->getExponentOfVarInProg(varName)));
}
