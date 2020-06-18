#include "langDef.hpp"

/******************************************
 Base types: int and bool
 */
BaseType::BaseType() {};

IntType::IntType() {};

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

BoolType::BoolType() {};

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

/******************************************
Constructs: Var
*/
Var::Var(string name) {
    _name = name;
}
    
string Var::toString() {
    return _name;
}
    
int Var::interpret(map<string, int> env) {
    return env[_name];
}
    
int Var::depth() {
    return 1;
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
    
int Plus::interpret(map<string, int> env) {
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

int Minus::interpret(map<string, int> env) {
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
    
int Times::interpret(map<string, int> env) {
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
    
int Leftshift::interpret(map<string, int> env) {
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
    
int Rightshift::interpret(map<string, int> env) {
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
    
bool Lt::interpret(map<string, int> env) {
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
    
bool And::interpret(map<string, int> env) {
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
    
bool Not::interpret(map<string, int> env) {
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
    
int Ite::interpret(map<string, int> env) {
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

