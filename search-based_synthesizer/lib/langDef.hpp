#ifndef LANGDEF_H
#define LANGDEF_H
#include <iostream>
#include <limits>
#include <map>
#include "typeDef.hpp"
using namespace std;

class BaseType {
private:
    int _generation;
public:
    BaseType();
    string to_string();
    int depth();
    int get_generation();
    void set_generation(int generation);
    vector<int> get_lexical_order(int num_of_vars, map<string, int>& vars_orders);
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
    virtual ~BaseType() {};
};

class IntType : public BaseType {
public:
    IntType();
    string to_string();
    int interpret(input_output_t env);
    int depth();
    vector<int> get_lexical_order(int num_of_vars, map<string, int>& vars_orders);
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
    virtual ~IntType() {};
};

class BoolType : public BaseType {
public:
    BoolType();
    string to_string();
    bool interpret(input_output_t env);
    int depth();
    vector<int> get_lexical_order(int num_of_vars, map<string, int>& vars_orders);
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
    virtual ~BoolType() {};
};

class F : public BoolType {
public:
    F();
    string to_string();
    bool interpret();
    int depth();
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Var : public IntType {
private:
    string _name;
public:
    Var(string name);
    string to_string();
    int interpret(input_output_t env);
    int depth();
    vector<int> get_lexical_order(int num_of_vars, map<string, int>& vars_orders);
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Num : public IntType {
private:
    int _num;
public:
    Num(int val);
    Num(Num* a, Num* b, string op);
    string to_string();
    int interpret();
    int depth();
    vector<int> get_lexical_order(int num_of_vars, map<string, int>& vars_orders);
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Plus : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Plus(IntType* left, IntType* right);
    string to_string();
    int interpret(input_output_t env);
    int depth();
    IntType* get_left();
    IntType* get_right();
    vector<string> getTerms();
    vector<int> get_lexical_order(int num_of_vars, map<string, int>& vars_orders);
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Minus : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Minus(IntType* left, IntType* right);
    string to_string();
    int interpret(input_output_t env);
    int depth();
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Times : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Times(IntType* left, IntType* right);
    string to_string();
    int interpret(input_output_t env);
    int depth();
    IntType* get_left();
    IntType* get_right();
    vector<string> get_factors();
    vector<int> get_lexical_order(int num_of_vars, map<string, int>& vars_orders);
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Div : public IntType {
private:
    IntType* _dividend;
    IntType* _divisor;
public:
    Div(IntType* dividend, IntType* divisor);
    string to_string();
    int interpret(input_output_t env);
    int depth();
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Leftshift : public IntType {
private:
    IntType* _value;
    IntType* _offset;
public:
    Leftshift(IntType* value, IntType* offset);
    string to_string();
    int interpret(input_output_t env);
    int depth();
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Rightshift : public IntType {
private:
    IntType* _value;
    IntType* _offset;
public:
    Rightshift(IntType* value, IntType* offset);
    string to_string();
    int interpret(input_output_t env);
    int depth();
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Min : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Min(IntType* left, IntType* right);
    string to_string();
    int interpret(input_output_t env);
    int depth();
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Lt : public BoolType {
private:
    IntType* _left;
    IntType* _right;
public:
    Lt(IntType* left, IntType* right);
    string to_string();
    bool interpret(input_output_t env);
    int depth();
    IntType* get_left();
    IntType* get_right();
    vector<int> get_lexical_order(int num_of_vars, map<string, int>& vars_orders);
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class And : public BoolType {
private:
    BoolType* _left;
    BoolType* _right;
public:
    And(BoolType* left, BoolType* right);
    string to_string();
    bool interpret(input_output_t env);
    int depth();
    BoolType* get_left();
    BoolType* get_right();
    vector<int> get_lexical_order(int num_of_vars, map<string, int>& vars_orders);
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Not : public BoolType {
private:
    BoolType* _left;
public:
    Not(BoolType* left);
    string to_string();
    bool interpret(input_output_t env);
    int depth();
    vector<int> get_lexical_order(int num_of_vars, map<string, int>& vars_orders);
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

class Ite : public IntType {
private:
    BoolType* _cond;
    IntType* _tcase;
    IntType* _fcase;
public:
    Ite(BoolType* cond, IntType* tcase, IntType* fcase);
    string to_string();
    int interpret(input_output_t env);
    int depth();
    int get_number_of_ops(string op_name);
    int get_number_of_vars(string var_name);
    int get_exponent_of_var(string var_name);
};

#endif
