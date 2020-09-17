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
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
    virtual ~BaseType() {};
};

class IntType : public BaseType {
public:
    IntType();
    string toString();
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
    virtual ~IntType() {};
};

class BoolType : public BaseType {
public:
    BoolType();
    string toString();
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
    virtual ~BoolType() {};
};

class F : public BoolType {
public:
    F();
    string toString();
    bool interpret();
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Var : public IntType {
private:
    string _name;
public:
    Var(string name);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Num : public IntType {
private:
    int _num;
public:
    Num(int val);
    string toString();
    int interpret();
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Plus : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Plus(IntType* left, IntType* right);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Minus : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Minus(IntType* left, IntType* right);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Times : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Times(IntType* left, IntType* right);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Div : public IntType {
private:
    IntType* _dividend;
    IntType* _divisor;
public:
    Div(IntType* dividend, IntType* divisor);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Leftshift : public IntType {
private:
    IntType* _value;
    IntType* _offset;
public:
    Leftshift(IntType* value, IntType* offset);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Rightshift : public IntType {
private:
    IntType* _value;
    IntType* _offset;
public:
    Rightshift(IntType* value, IntType* offset);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Min : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Min(IntType* left, IntType* right);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Lt : public BoolType {
private:
    IntType* _left;
    IntType* _right;
public:
    Lt(IntType* left, IntType* right);
    string toString();
    bool interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class And : public BoolType {
private:
    BoolType* _left;
    BoolType* _right;
public:
    And(BoolType* left, BoolType* right);
    string toString();
    bool interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Not : public BoolType {
private:
    BoolType* _left;
public:
    Not(BoolType* left);
    string toString();
    bool interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

class Ite : public IntType {
private:
    BoolType* _cond;
    IntType* _tcase;
    IntType* _fcase;
public:
    Ite(BoolType* cond, IntType* tcase, IntType* fcase);
    string toString();
    int interpret(inputOutput_t env);
    int depth();
    int getNumOfOpsInProg(string opName);
    int getNumOfSymbolsInProg(string symbolName);
};

#endif
