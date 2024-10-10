#include "langDef.hpp"

/******************************************
 * helper functions
 */
template <typename T>
void updateDepthIfMatch(BaseType* casePtr, int& depth) {
    if (auto castedPtr = dynamic_cast<T*>(casePtr)) {
        depth = max(depth, castedPtr->depth()) + 1;
    }
}

/******************************************
 Base types: int and bool
 */
BaseType::BaseType() {};

string BaseType::to_string() {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->to_string();
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->to_string();
    }
    else {
        throw runtime_error("BaseType::to_string() operates on UNKNOWN type!");
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
    return _generation;
}

void BaseType::set_generation(int generation) {
    _generation = generation;
}

vector<int> BaseType::get_lexical_order(int num_of_vars, map<string, int>& vars_orders) {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->get_lexical_order(num_of_vars, vars_orders);
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->get_lexical_order(num_of_vars, vars_orders);
    }
    else {
        throw runtime_error("BaseType::get_lexical_order() operates on UNKNOWN type!");
    }
}

int BaseType::get_number_of_ops(string op_name) {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->get_number_of_ops(op_name);
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->get_number_of_ops(op_name);
    }
    else {
        throw runtime_error("BaseType::get_number_of_ops() operates on UNKNOWN type!");
    }
}

int BaseType::get_number_of_vars(string var_name) {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->get_number_of_vars(var_name);
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->get_number_of_vars(var_name);
    }
    else {
        throw runtime_error("BaseType::get_number_of_vars() operates on UNKNOWN type!");
    }
}

int BaseType::get_exponent_of_var(string var_name) {
    if (auto intType = dynamic_cast<IntType*>(this)) {
        return intType->get_exponent_of_var(var_name);
    }
    else if (auto boolType = dynamic_cast<BoolType*>(this)) {
        return boolType->get_exponent_of_var(var_name);
    }
    else {
        throw runtime_error("BaseType::get_exponent_of_var() operates on UNKNOWN type!");
    }
}

/*
 Int and Bool type
 */

IntType::IntType() {};

string IntType::to_string() {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->to_string();
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->to_string();
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->to_string();
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->to_string();
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->to_string();
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->to_string();
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->to_string();
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->to_string();
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->to_string();
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->to_string();
    }
    else {
        throw runtime_error("IntType::to_string() operates on UNKNOWN type!");
    }
}

int IntType::interpret(input_output_t env) {
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

vector<int> IntType::get_lexical_order(int num_of_vars, map<string, int>& vars_orders) {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->get_lexical_order(num_of_vars, vars_orders);
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->get_lexical_order(num_of_vars, vars_orders);
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->get_lexical_order(num_of_vars, vars_orders);
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->get_lexical_order(num_of_vars, vars_orders);
    }
    else {
        throw runtime_error("IntType::get_lexical_order() operates on UNKNOWN type!");
    }
}

int IntType::get_number_of_ops(string op_name) {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->get_number_of_ops(op_name);
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->get_number_of_ops(op_name);
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->get_number_of_ops(op_name);
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->get_number_of_ops(op_name);
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->get_number_of_ops(op_name);
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->get_number_of_ops(op_name);
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->get_number_of_ops(op_name);
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->get_number_of_ops(op_name);
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->get_number_of_ops(op_name);
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->get_number_of_ops(op_name);
    }
    else {
        throw runtime_error("IntType::get_number_of_ops() operates on UNKNOWN type!");
    }
}

int IntType::get_number_of_vars(string var_name) {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->get_number_of_vars(var_name);
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->get_number_of_vars(var_name);
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->get_number_of_vars(var_name);
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->get_number_of_vars(var_name);
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->get_number_of_vars(var_name);
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->get_number_of_vars(var_name);
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->get_number_of_vars(var_name);
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->get_number_of_vars(var_name);
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->get_number_of_vars(var_name);
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->get_number_of_vars(var_name);
    }
    else {
        throw runtime_error("IntType::get_number_of_vars() operates on UNKNOWN type");
    }
}

int IntType::get_exponent_of_var(string var_name) {
    if (auto num = dynamic_cast<Num*>(this)) {
        return num->get_exponent_of_var(var_name);
    }
    else if (auto var = dynamic_cast<Var*>(this)) {
        return var->get_exponent_of_var(var_name);
    }
    else if (auto plus = dynamic_cast<Plus*>(this)) {
        return plus->get_exponent_of_var(var_name);
    }
    else if (auto minus = dynamic_cast<Minus*>(this)) {
        return minus->get_exponent_of_var(var_name);
    }
    else if (auto times = dynamic_cast<Times*>(this)) {
        return times->get_exponent_of_var(var_name);
    }
    else if (auto div = dynamic_cast<Div*>(this)) {
        return div->get_exponent_of_var(var_name);
    }
    else if (auto mn = dynamic_cast<Min*>(this)) {
        return mn->get_exponent_of_var(var_name);
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(this)) {
        return leftshift->get_exponent_of_var(var_name);
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(this)) {
        return rightshift->get_exponent_of_var(var_name);
    }
    else if (auto ite = dynamic_cast<Ite*>(this)) {
        return ite->get_exponent_of_var(var_name);
    }
    else {
        throw runtime_error("IntType::get_exponent_of_var() operates on UNKOWN type!");
    }
}

BoolType::BoolType() {};

string BoolType::to_string() {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->to_string();
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->to_string();
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->to_string();
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->to_string();
    }
    else {
        throw runtime_error("BoolType::to_string() operates on UNKOWN type!");
    }
}

bool BoolType::interpret(input_output_t env) {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->interpret();
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->interpret(env);
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->interpret(env);
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->interpret(env);
    }
    else {
        throw runtime_error("BoolType::interpret() operates on UNKOWN type!");
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

vector<int> BoolType::get_lexical_order(int num_of_vars, map<string, int>& vars_orders) {
    if (auto n = dynamic_cast<Not*>(this)) {
        return n->get_lexical_order(num_of_vars, vars_orders);
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->get_lexical_order(num_of_vars, vars_orders);
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->get_lexical_order(num_of_vars, vars_orders);
    }
    else {
        throw runtime_error("BoolType::get_lexical_order() operates on UNKOWN type!");
    }
}

int BoolType::get_number_of_ops(string op_name) {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->get_number_of_ops(op_name);
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->get_number_of_ops(op_name);
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->get_number_of_ops(op_name);
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->get_number_of_ops(op_name);
    }
    else {
        throw runtime_error("BoolType::get_number_of_ops() operates on UNKOWN type!");
    }
}

int BoolType::get_number_of_vars(string var_name) {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->get_number_of_vars(var_name);
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->get_number_of_vars(var_name);
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->get_number_of_vars(var_name);
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->get_number_of_vars(var_name);
    }
    else {
        throw runtime_error("BoolType::get_number_of_vars() operates on UNKOWN type!");
    }
}

int BoolType::get_exponent_of_var(string var_name) {
    if (auto f = dynamic_cast<F*>(this) ) {
        return f->get_exponent_of_var(var_name);
    }
    else if (auto n = dynamic_cast<Not*>(this)) {
        return n->get_exponent_of_var(var_name);
    }
    else if (auto a = dynamic_cast<And*>(this)) {
        return a->get_exponent_of_var(var_name);
    }
    else if (auto lt = dynamic_cast<Lt*>(this)) {
        return lt->get_exponent_of_var(var_name);
    }
    else {
        throw runtime_error("BoolType::get_exponent_of_var() operates on UNKOWN type!");
    }
}

/******************************************
Constructs: False
*/
F::F() {
    set_generation(0);
};

string F::to_string() {
    return "false";
}
    
bool F::interpret() {
    return false;
}
    
int F::depth() {
    return 1;
}

int F::get_number_of_ops(string op_name) {
    return 0;
}

int F::get_number_of_vars(string var_name) {
    if (var_name == "false" || var_name == "ALL") {
        return 1;
    }
    return 0;
}

int F::get_exponent_of_var(string var_name) {
    return 0;
}

/******************************************
Constructs: Var
*/
Var::Var(string name) {
    _name = name;
    set_generation(0);
}
    
string Var::to_string() {
    return _name;
}
    
int Var::interpret(input_output_t env) {
    if (env.find(_name) == env.end()) throw runtime_error("Var::interpret(): _name " + _name + " is not found in env");
    return env[_name];
}
    
int Var::depth() {
    return 1;
}

vector<int> Var::get_lexical_order(int num_of_vars, map<string, int>& vars_orders) {
    vector<int> lex(num_of_vars, 0);
    if (vars_orders.find(this->to_string()) == vars_orders.end()) throw runtime_error("Var::get_lexical_order() var not found in keys of vars_orders");
    if (vars_orders[this->to_string()] > lex.size()) throw runtime_error("Var::get_lexical_order() number of vars is greater than lex vector size");
    if (vars_orders[this->to_string()] == 0) throw runtime_error("Var::get_lexical_order() var's index is 0");
    lex[vars_orders[this->to_string()]-1]++;
    return lex;
}

int Var::get_number_of_ops(string op_name) {
    return 0;
}

int Var::get_number_of_vars(string var_name) {
    if (var_name == "ALL" ||
        var_name == "VAR" ||
        var_name == _name ||
        (var_name.size() < _name.size() && var_name == _name.substr(0, var_name.size())) ) {
        return 1;
    }
    return 0;
}

int Var::get_exponent_of_var(string var_name) {
    if (var_name == _name ||
        (var_name.size() < _name.size() && var_name == _name.substr(0, var_name.size())) ) {
        return 1;
    }
    return 0;
}

/******************************************
Constructs: Num
*/
Num::Num(int val) {
    _num = val;
    set_generation(0);
}

Num::Num(Num* a, Num* b, string op) {
    if (a == nullptr) throw runtime_error("Num a is null");
    if (b == nullptr) throw runtime_error("Num b is null");
    
    if (op == "TIMES") _num = a->interpret() * b->interpret();
    else if (op == "PLUS") _num = a->interpret() + b->interpret();
    else throw runtime_error("Num::Num() UNKOWN op type");
    set_generation( max(a->get_generation(), b->get_generation()) + 1);
}
    
string Num::to_string() {
    return std::to_string(_num);
}
    
int Num::interpret() {
    return _num;
}
    
int Num::depth() {
    return 1;
}

vector<int> Num::get_lexical_order(int num_of_vars, map<string, int>& vars_orders) {
    vector<int> lex(num_of_vars, 0);
    return lex;
}

int Num::get_number_of_ops(string op_name) {
    return 0;
}

int Num::get_number_of_vars(string var_name) {
    if (var_name == std::to_string(_num) || var_name == "ALL" || var_name == "NUM") {
        return 1;
    }
    return 0;
}

int Num::get_exponent_of_var(string var_name) {
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
    set_generation(max(left->get_generation(), right->get_generation()) + 1);
}

string Plus::to_string() {
    return "(" + _left->to_string() + " + " + _right->to_string() + ")";
}
    
int Plus::interpret(input_output_t env) {
    return _left->interpret(env) + _right->interpret(env);
}
    
int Plus::depth() {
    return max(_left->depth(), _right->depth()) + 1;
}

IntType* Plus::get_left() {
    return _left;
}
IntType* Plus::get_right() {
    return _right;
}

vector<string> Plus::getTerms() {
    vector<string> terms;
    
    if (dynamic_cast<Var*>(_left)) {
        terms.push_back(_left->to_string());
    }
    else if (auto left_times = dynamic_cast<Times*>(_left)) {
        if (dynamic_cast<Num*>(left_times->get_left())) {
            terms.push_back(left_times->get_right()->to_string());
        } else {
            terms.push_back(_left->to_string());
        }
    }
    
    if (dynamic_cast<Var*>(_right)) {
        terms.push_back(_right->to_string());
    }
    else if (auto right_times = dynamic_cast<Times*>(_right)) {
        if (dynamic_cast<Num*>(right_times->get_right())) {
            terms.push_back(right_times->get_right()->to_string());
        } else {
            terms.push_back(_right->to_string());
        }
    }
    else if (auto right_plus = dynamic_cast<Plus*>(_right)) {
        vector<string> terms_right = right_plus->getTerms();
        terms.insert(terms.end(), terms_right.begin(), terms_right.end());
    }
    return terms;
}

vector<int> Plus::get_lexical_order(int num_of_vars, map<string, int>& vars_orders) {
    if (_right == nullptr) throw runtime_error("Plus::get_lexical_order() _right is null");
    return _right->get_lexical_order(num_of_vars, vars_orders);
}

int Plus::get_number_of_ops(string op_name) {
    if (op_name == "PLUS" || op_name == "ALL") {
        return _left->get_number_of_ops(op_name) + _left->get_number_of_ops(op_name) + 1;
    }
    return _left->get_number_of_ops(op_name) + _left->get_number_of_ops(op_name);
}

int Plus::get_number_of_vars(string var_name) {
    return _left->get_number_of_vars(var_name) + _right->get_number_of_vars(var_name);
}

int Plus::get_exponent_of_var(string var_name) {
    return max(_left->get_exponent_of_var(var_name), _right->get_exponent_of_var(var_name));
}

/******************************************
Constructs: Minus
*/
Minus::Minus(IntType* left, IntType* right) {
    if (left == nullptr) throw runtime_error("Minus: left is null");
    if (right == nullptr) throw runtime_error("Minus: right is null");
    _left = left;
    _right = right;
    set_generation( max(left->get_generation(), right->get_generation()) + 1 );
}
    
string Minus::to_string() {
    return "(" + _left->to_string() + " - " + _right->to_string() + ")";
}

int Minus::interpret(input_output_t env) {
    return _left->interpret(env) - _right->interpret(env);
}
    
int Minus::depth() {
    return max(_left->depth(), _right->depth()) + 1;
}

int Minus::get_number_of_ops(string op_name) {
    if (op_name == "MINUS" || op_name == "ALL") {
        return _left->get_number_of_ops(op_name) + _right->get_number_of_ops(op_name) + 1;
    }
    return _left->get_number_of_ops(op_name) + _right->get_number_of_ops(op_name);
}

int Minus::get_number_of_vars(string var_name) {
    return _left->get_number_of_vars(var_name) + _right->get_number_of_vars(var_name);
}

int Minus::get_exponent_of_var(string var_name) {
    return max(_left->get_exponent_of_var(var_name), _right->get_exponent_of_var(var_name));
}

/******************************************
Constructs: Times
*/
Times::Times(IntType* left, IntType* right) {
    if (left == nullptr) throw runtime_error("Times: left is null");
    if (right == nullptr) throw runtime_error("Times: right is null");
    _left = left;
    _right = right;
    set_generation( max(left->get_generation(), right->get_generation()) + 1);
}

string Times::to_string() {
    return "(" + _left->to_string() + " * " + _right->to_string() + ")";
}
    
int Times::interpret(input_output_t env) {
    return _left->interpret(env) * _right->interpret(env);
}
    
int Times::depth() {
    return max(_left->depth(), _right->depth()) + 1;
}

IntType* Times::get_left() {
    return _left;
}
IntType* Times::get_right() {
    return _right;
}

vector<string> Times::get_factors() {
    vector<string> factors;
    if (dynamic_cast<Var*>(_left)) {
        factors.push_back(_left->to_string());
    }
    if (dynamic_cast<Var*>(_right)) {
        factors.push_back(_right->to_string());
    }
    if (auto right_times = dynamic_cast<Times*>(_right)) {
        vector<string> factors_right = right_times->get_factors();
        factors.insert(factors.end(), factors_right.begin(), factors_right.end());
    }
    return factors;
}

vector<int> Times::get_lexical_order(int num_of_vars, map<string, int>& vars_orders) {
    if (_left == nullptr) throw runtime_error("Times::get_lexical_order() left is null");
    if (_right == nullptr) throw runtime_error("Times::get_lexical_order() right is null");
    
    vector<int> lex_left(num_of_vars, 0);
    vector<int> lex_right(num_of_vars, 0);

    if (auto left_num = dynamic_cast<Num*>(_left)) {
        lex_left = left_num->get_lexical_order(num_of_vars, vars_orders);
    }
    else if (auto left_var = dynamic_cast<Var*>(_left)) {
        lex_left = left_var->get_lexical_order(num_of_vars, vars_orders);
    }
    else {
        throw runtime_error("Times::get_lexical_order left is not a type of NUM/VAR");
    }
    if (auto right_var = dynamic_cast<Var*>(_right)) {
        lex_right = right_var->get_lexical_order(num_of_vars, vars_orders);
    }
    else if (auto right_times = dynamic_cast<Times*>(_right)) {
        lex_right = right_times->get_lexical_order(num_of_vars, vars_orders);
    }
    else {
        throw runtime_error("Times::get_lexical_order right is not a type of NUM/VAR");
    }
    for (int i = 0; i < num_of_vars; i++) {
        lex_left[i] += lex_right[i];
    }
    return lex_left;
}

int Times::get_number_of_ops(string op_name) {
    if (op_name == "TIMES" || op_name == "ALL") {
        return _left->get_number_of_ops(op_name) + _right->get_number_of_ops(op_name) + 1;
    }
    return _left->get_number_of_ops(op_name) + _right->get_number_of_ops(op_name);
}

int Times::get_number_of_vars(string var_name) {
    return _left->get_number_of_vars(var_name) + _right->get_number_of_vars(var_name);
}

int Times::get_exponent_of_var(string var_name) {
    return _left->get_exponent_of_var(var_name) + _right->get_exponent_of_var(var_name);
}

/******************************************
Constructs: Min
*/
Min::Min(IntType* left, IntType* right) {
    if (left == nullptr) throw runtime_error("Min: left is null");
    if (right == nullptr) throw runtime_error("Min: right is null");
    _left = left;
    _right = right;
    set_generation( max(left->get_generation(), right->get_generation()) + 1 );
}
string Min::to_string() {
    return "min( " + _left->to_string() + " , " + _right->to_string() + " )";
}
int Min::interpret(input_output_t env) {
    return min(_left->interpret(env), _right->interpret(env));
}

int Min::depth() {
    return max(_left->depth(), _right->depth()) + 1;
}

int Min::get_number_of_ops(string op_name) {
    if (op_name == "MIN" || op_name == "ALL") {
        return _left->get_number_of_ops(op_name) + _right->get_number_of_ops(op_name) + 1;
    }
    return _left->get_number_of_ops(op_name) + _right->get_number_of_ops(op_name);
}

int Min::get_number_of_vars(string var_name) {
    return _left->get_number_of_vars(var_name) + _right->get_number_of_vars(var_name);
}

int Min::get_exponent_of_var(string var_name) {
    return max(_left->get_exponent_of_var(var_name), _right->get_exponent_of_var(var_name));
}

/******************************************
Constructs: Div
*/

Div::Div(IntType* dividend, IntType* divisor) {
    if (dividend == nullptr) throw runtime_error("Div: dividend is null");
    if (divisor == nullptr) throw runtime_error("Div: divisor is null");
    _dividend = dividend;
    _divisor = divisor;
    set_generation( max(dividend->get_generation(), divisor->get_generation()) + 1 );
}

string Div::to_string() {
    return "(" + _dividend->to_string() + " / " + _divisor->to_string() + ")";
}

int Div::interpret(input_output_t env) {
    int divisor = _divisor->interpret(env);
    // safe division
    if (divisor == 0) return 0;
    return _dividend->interpret(env) / divisor;
}

int Div::depth() {
    return max(_dividend->depth(), _divisor->depth()) + 1;
}

int Div::get_number_of_ops(string op_name) {
    if (op_name == "DIV" || op_name == "ALL") {
        return _dividend->get_number_of_ops(op_name) + _divisor->get_number_of_ops(op_name) + 1;
    }
    return _dividend->get_number_of_ops(op_name) + _divisor->get_number_of_ops(op_name);
}

int Div::get_number_of_vars(string var_name) {
    return _dividend->get_number_of_vars(var_name) + _divisor->get_number_of_vars(var_name);
}

int Div::get_exponent_of_var(string var_name) {
    return _dividend->get_exponent_of_var(var_name) - _divisor->get_exponent_of_var(var_name);
}

/******************************************
Constructs: Div8
*/
Div8::Div8(IntType* dividend) {
    if (dividend == nullptr) throw runtime_error("Div8: dividend is null");
    _dividend = dividend;
    set_generation( dividend->get_generation() + 1 );
}

string Div8::to_string() {
    return "(" + _dividend->to_string() + " / 8)";
}

int Div8::interpret(input_output_t env) {
    return _dividend->interpret(env) / 8;
}

int Div8::depth() {
    return _dividend->depth() + 1;
}

int Div8::get_number_of_ops(string op_name) {
    if (op_name == "DIV8" || op_name == "ALL") {
        return _dividend->get_number_of_ops(op_name) + 1;
    }
    return _dividend->get_number_of_ops(op_name);
}

int Div8::get_number_of_vars(string var_name) {
    return _dividend->get_number_of_vars(var_name);
}

int Div8::get_exponent_of_var(string var_name) {
    return _dividend->get_exponent_of_var(var_name);
}

/******************************************
Constructs: Leftshift
*/
Leftshift::Leftshift(IntType* value, IntType* offset) {
    if (value == nullptr) throw runtime_error("Leftshift: value is null");
    if (offset == nullptr) throw runtime_error("Leftshift: offset is null");
    _value = value;
    _offset = offset;
    set_generation( max(value->get_generation(), offset->get_generation()) + 1 );
}

string Leftshift::to_string() {
    return "(" + _value->to_string() + " << " + _offset->to_string() + ")";
}
    
int Leftshift::interpret(input_output_t env) {
    return _value->interpret(env) << _offset->interpret(env);
}
    
int Leftshift::depth() {
    return max(_value->depth(), _offset->depth()) + 1;
}

int Leftshift::get_number_of_ops(string op_name) {
    if (op_name == "LEFTSHIFT" || op_name == "ALL") {
        return _value->get_number_of_ops(op_name) + _offset->get_number_of_ops(op_name) + 1;
    }
    return _value->get_number_of_ops(op_name) + _offset->get_number_of_ops(op_name);
}

int Leftshift::get_number_of_vars(string var_name) {
    return _value->get_number_of_vars(var_name) + _offset->get_number_of_vars(var_name);
}

int Leftshift::get_exponent_of_var(string var_name) {
    return max(_value->get_exponent_of_var(var_name), _offset->get_exponent_of_var(var_name));
}

/******************************************
Constructs: Leftshift
*/
Rightshift::Rightshift(IntType* value, IntType* offset) {
    if (value == nullptr) throw runtime_error("Rightshift: value is null");
    if (offset == nullptr) throw runtime_error("Rightshift: offset is null");
    _value = value;
    _offset = offset;
    set_generation( max(value->get_generation(), offset->get_generation()) + 1 );
}
    
string Rightshift::to_string() {
    return "(" + _value->to_string() + " >> " + _offset->to_string() + ")";
}
    
int Rightshift::interpret(input_output_t env) {
    return _value->interpret(env) >> _offset->interpret(env);
}
    
int Rightshift::depth() {
    return max(_value->depth(), _offset->depth()) + 1;
}

int Rightshift::get_number_of_ops(string op_name) {
    if (op_name == "RIGHTSHIFT" || op_name == "ALL") {
        return _value->get_number_of_ops(op_name) + _offset->get_number_of_ops(op_name) + 1;
    }
    return _value->get_number_of_ops(op_name) + _offset->get_number_of_ops(op_name);
}

int Rightshift::get_number_of_vars(string var_name) {
    return _value->get_number_of_vars(var_name) + _offset->get_number_of_vars(var_name);
}

int Rightshift::get_exponent_of_var(string var_name) {
    return max(_value->get_exponent_of_var(var_name), _offset->get_exponent_of_var(var_name));
}

/******************************************
Constructs: Lt
*/
Lt::Lt(IntType* left, IntType* right) {
    if (left == nullptr) throw runtime_error("Lt: left is null");
    if (right == nullptr) throw runtime_error("Lt: right is null");
    _left = left;
    _right = right;
    set_generation( max(left->get_generation(), right->get_generation()) + 1 );
}

string Lt::to_string() {
    return "(" + _left->to_string() + " < " + _right->to_string() + ")";
}
    
bool Lt::interpret(input_output_t env) {
    return _left->interpret(env) < _right->interpret(env);
}
    
int Lt::depth() {
    return max(_left->depth(), _right->depth()) + 1;
}

IntType* Lt::get_left() {
    return _left;
}
IntType* Lt::get_right() {
    return _right;
}

vector<int> Lt::get_lexical_order(int num_of_vars, map<string, int>& vars_orders) {
    vector<int> left_lex = _left->get_lexical_order(num_of_vars, vars_orders);
    vector<int> right_lex = _right->get_lexical_order(num_of_vars, vars_orders);
    left_lex.insert(left_lex.end(), right_lex.begin(), right_lex.end());
    return left_lex;
}

int Lt::get_number_of_ops(string op_name) {
    if (op_name == "LT" || op_name == "ALL") {
        return _left->get_number_of_ops(op_name) + _right->get_number_of_ops(op_name) + 1;
    }
    return _left->get_number_of_ops(op_name) + _right->get_number_of_ops(op_name);
}

int Lt::get_number_of_vars(string var_name) {
    return _left->get_number_of_vars(var_name) + _right->get_number_of_vars(var_name);
}

int Lt::get_exponent_of_var(string var_name) {
    return max(_left->get_exponent_of_var(var_name), _right->get_exponent_of_var(var_name));
}

/******************************************
Constructs: And
*/
And::And(BoolType* left, BoolType* right) {
    if (left == nullptr) throw runtime_error("And: value is null");
    if (right == nullptr) throw runtime_error("And: offset is null");
    _left = left;
    _right = right;
    set_generation( max(left->get_generation(), right->get_generation()) + 1);
}

string And::to_string() {
    return "(" + _left->to_string() + " && " + _right->to_string() + ")";
}
    
bool And::interpret(input_output_t env) {
    return _left->interpret(env) && _right->interpret(env);
}
    
int And::depth() {
    return max(_left->depth(), _right->depth()) + 1;
}

BoolType* And::get_left() {
    return _left;
}
BoolType* And::get_right() {
    return _right;
}

vector<int> And::get_lexical_order(int num_of_vars, map<string, int>& vars_orders) {
    return _right->get_lexical_order(num_of_vars, vars_orders);
}

int And::get_number_of_ops(string op_name) {
    if (op_name == "AND" || op_name == "ALL") {
        return _left->get_number_of_ops(op_name) + _right->get_number_of_ops(op_name) + 1;
    }
    return _left->get_number_of_ops(op_name) + _right->get_number_of_ops(op_name);
}

int And::get_number_of_vars(string var_name) {
    return _left->get_number_of_vars(var_name) + _right->get_number_of_vars(var_name);
}

int And::get_exponent_of_var(string var_name) {
    return max(_left->get_exponent_of_var(var_name), _right->get_exponent_of_var(var_name));
}

/******************************************
Constructs: Not
*/
Not::Not(BoolType* left) {
    if (left == nullptr) throw runtime_error("Not: value is null");
    _left = left;
    set_generation( left->get_generation() + 1 );
}

string Not::to_string() {
    return "(! " + _left->to_string() + ")";
}
    
bool Not::interpret(input_output_t env) {
    return !(_left->interpret(env));
}
    
int Not::depth() {
    return _left->depth() + 1;
}

vector<int> Not::get_lexical_order(int num_of_vars, map<string, int>& vars_orders) {
    return _left->get_lexical_order(num_of_vars, vars_orders);
}

int Not::get_number_of_ops(string op_name) {
    if (op_name == "NOT" || op_name == "ALL") {
        return _left->get_number_of_ops(op_name) + 1;
    }
    return _left->get_number_of_ops(op_name);
}

int Not::get_number_of_vars(string var_name) {
    return _left->get_number_of_vars(var_name);
}

int Not::get_exponent_of_var(string var_name) {
    return _left->get_exponent_of_var(var_name);
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
    set_generation( max(cond->get_generation(), max(tcase->get_generation(), fcase->get_generation())) + 1 );
}

string Ite::to_string() {
    return "(if " + _cond->to_string() + " then " + _tcase->to_string() + " else " + _fcase->to_string() + ")";
}
    
int Ite::interpret(input_output_t env) {
    return _cond->interpret(env) ? _tcase->interpret(env) : _fcase->interpret(env);
}
    
int Ite::depth() {
    return max(_cond->depth(), max(_tcase->depth(), _fcase->depth())) + 1;
}

int Ite::get_number_of_ops(string op_name) {
    if (op_name == "ITE" || op_name == "ALL") {
        return _cond->get_number_of_ops(op_name) + _tcase->get_number_of_ops(op_name) + _fcase->get_number_of_ops(op_name) + 1;
    }
    return _cond->get_number_of_ops(op_name) + _tcase->get_number_of_ops(op_name) + _fcase->get_number_of_ops(op_name);
}

int Ite::get_number_of_vars(string var_name) {
    return _cond->get_number_of_vars(var_name) + _tcase->get_number_of_vars(var_name) + _fcase->get_number_of_vars(var_name);
}

int Ite::get_exponent_of_var(string var_name) {
    return max(_cond->get_exponent_of_var(var_name), max(_tcase->get_exponent_of_var(var_name), _fcase->get_exponent_of_var(var_name)));
}
