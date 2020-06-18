#ifndef LANGDEF_H
#define LANGDEF_H
#include <iostream>
#include <map>
using namespace std;

class BaseType {
public:
    BaseType();
    virtual ~BaseType() {};
};

class IntType : public BaseType {
public:
    IntType();
    int depth();
    virtual ~IntType() {};
};

class BoolType : public BaseType {
public:
    BoolType();
    int depth();
    virtual ~BoolType() {};
};

class F : public BoolType {
public:
    F();
    string toString();
    bool interpret();
    int depth();
};

class Var : public IntType {
private:
    string _name;
public:
    Var(string name);
    string toString();
    int interpret(map<string, int> env);
    int depth();
};

class Num : public IntType {
private:
    int _num;
public:
    Num(int val);
    string toString();
    int interpret();
    int depth();
};

class Plus : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Plus(IntType* left, IntType* right);
    string toString();
    int interpret(map<string, int> env);
    int depth();
};

class Minus : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Minus(IntType* left, IntType* right);
    string toString();
    int interpret(map<string, int> env);
    int depth();
};

class Times : public IntType {
private:
    IntType* _left;
    IntType* _right;
public:
    Times(IntType* left, IntType* right);
    string toString();
    int interpret(map<string, int> env);
    int depth();
};

class Leftshift : public IntType {
private:
    IntType* _value;
    IntType* _offset;
public:
    Leftshift(IntType* value, IntType* offset);
    string toString();
    int interpret(map<string, int> env);
    int depth();
};

class Rightshift : public IntType {
private:
    IntType* _value;
    IntType* _offset;
public:
    Rightshift(IntType* value, IntType* offset);
    string toString();
    int interpret(map<string, int> env);
    int depth();
};

class Lt : public BoolType {
private:
    IntType* _left;
    IntType* _right;
public:
    Lt(IntType* left, IntType* right);
    string toString();
    bool interpret(map<string, int> env);
    int depth();
};

class And : public BoolType {
private:
    BoolType* _left;
    BoolType* _right;
public:
    And(BoolType* left, BoolType* right);
    string toString();
    bool interpret(map<string, int> env);
    int depth();
};

class Not : public BoolType {
private:
    BoolType* _left;
public:
    Not(BoolType* left);
    string toString();
    bool interpret(map<string, int> env);
    int depth();
};

class Ite : public IntType {
private:
    BoolType* _cond;
    IntType* _tcase;
    IntType* _fcase;
public:
    Ite(BoolType* cond, IntType* tcase, IntType* fcase);
    string toString();
    int interpret(map<string, int> env);
    int depth();
};

#endif
