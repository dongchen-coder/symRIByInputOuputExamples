#ifndef LANGDEF_H
#define LANGDEF_H
#include <iostream>
#include <limits>
#include <map>
#include "typeDef.hpp"
using namespace std;

class BaseType {
public:
    BaseType();
    string toString();
    int depth();
    int get_generation();
    void set_generation(int generation);
    vector<int> getLexicalOrder(int num_of_vars, map<string, int>& vars_orders);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
    virtual ~BaseType() {};
};

class IntType : public BaseType {
public:
    IntType();
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    vector<int> getLexicalOrder(int num_of_vars, map<string, int>& vars_orders);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
    virtual ~IntType() {};
};

class BoolType : public BaseType {
public:
    BoolType();
    string toString();
    int depth();
    int get_generation();
    void set_generation(int generation);
    vector<int> getLexicalOrder(int num_of_vars, map<string, int>& vars_orders);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
    virtual ~BoolType() {};
};

class F : public BoolType {
private:
    int _generation;
public:
    F();
    string toString();
    bool interpret();
    int depth();
    int get_generation();
    void set_generation(int generation);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Var : public IntType {
private:
    string _name;
    int _generation;
public:
    Var(string name);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    vector<int> getLexicalOrder(int num_of_vars, map<string, int>& vars_orders);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Num : public IntType {
private:
    int _num;
    int _generation;
public:
    Num(int val);
    Num(Num* a, Num* b, string op);
    string toString();
    int interpret();
    int depth();
    int get_generation();
    void set_generation(int generation);
    vector<int> getLexicalOrder(int num_of_vars, map<string, int>& vars_orders);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Plus : public IntType {
private:
    IntType* _left;
    IntType* _right;
    int _generation;
public:
    Plus(IntType* left, IntType* right);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    IntType* getLeft();
    IntType* getRight();
    vector<string> getTerms();
    vector<int> getLexicalOrder(int num_of_vars, map<string, int>& vars_orders);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Minus : public IntType {
private:
    IntType* _left;
    IntType* _right;
    int _generation;
public:
    Minus(IntType* left, IntType* right);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Times : public IntType {
private:
    IntType* _left;
    IntType* _right;
    int _generation;
public:
    Times(IntType* left, IntType* right);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    IntType* getLeft();
    IntType* getRight();
    vector<string> getFactors();
    vector<int> getLexicalOrder(int num_of_vars, map<string, int>& vars_orders);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Div : public IntType {
private:
    IntType* _dividend;
    IntType* _divisor;
    int _generation;
public:
    Div(IntType* dividend, IntType* divisor);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Leftshift : public IntType {
private:
    IntType* _value;
    IntType* _offset;
    int _generation;
public:
    Leftshift(IntType* value, IntType* offset);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Rightshift : public IntType {
private:
    IntType* _value;
    IntType* _offset;
    int _generation;
public:
    Rightshift(IntType* value, IntType* offset);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Min : public IntType {
private:
    IntType* _left;
    IntType* _right;
    int _generation;
public:
    Min(IntType* left, IntType* right);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Lt : public BoolType {
private:
    IntType* _left;
    IntType* _right;
    int _generation;
public:
    Lt(IntType* left, IntType* right);
    string toString();
    bool interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    IntType* getLeft();
    IntType* getRight();
    vector<int> getLexicalOrder(int num_of_vars, map<string, int>& vars_orders);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class And : public BoolType {
private:
    BoolType* _left;
    BoolType* _right;
    int _generation;
public:
    And(BoolType* left, BoolType* right);
    string toString();
    bool interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    BoolType* getLeft();
    BoolType* getRight();
    vector<int> getLexicalOrder(int num_of_vars, map<string, int>& vars_orders);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Not : public BoolType {
private:
    BoolType* _left;
    int _generation;
public:
    Not(BoolType* left);
    string toString();
    bool interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    vector<int> getLexicalOrder(int num_of_vars, map<string, int>& vars_orders);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

class Ite : public IntType {
private:
    BoolType* _cond;
    IntType* _tcase;
    IntType* _fcase;
    int _generation;
public:
    Ite(BoolType* cond, IntType* tcase, IntType* fcase);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int get_generation();
    void set_generation(int generation);
    int getNumberOfOpsInProg(string opName);
    int getNumberOfVarsInProg(string varName);
    int getExponentOfVarInProg(string varName);
};

#endif
