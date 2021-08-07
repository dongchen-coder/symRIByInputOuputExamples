#ifndef BOTTOMUPSEARCH_H
#define BOTTOMUPSEARCH_H

#include "langDef.hpp"
#include "typeDef.hpp"
#include <algorithm>
#include <future>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

#define DEBUG

class bottomUpSearch {
public:
    bottomUpSearch(int depthBound,
                   vector<string> intOps,
                   vector<string> boolOps,
                   vector<string> vars,
                   vector<string> constants,
                   bool isPred,
                   vector<string> rulesToApply,
                   inputOutputs_t inputOutputs);
    
    /* search function */
    string search();
    
    /* dump language used */
    void dumpLangDef();
    
private:
    /* dump one program */
    inline string dumpProgram(BaseType* p);
    
    /* Grow program list */
    void grow(int prog_generation);
    //void grow_with_specific_operations(vector<string> opertions);
    
    /* Eliminate equalivlent programs */
    inline BaseType* elimOneProgWithRules(BaseType* pi, BaseType* pj);
    void elimEquvalents();
    
    /* Check whether there is a correct program in program list */
    inline string getCorrect(int prog_generation);
    
    /* Dumping function */
    void dumpPlist();
    void dumpPlist(vector<BaseType*> pList);
    inline int getPlistSize();
    
    /* grow expression rules */
    vector<int> getTimesLexicalOrder(IntType* prog);
    bool isGrowRuleSatisfied(BaseType* i, BaseType* j, BaseType* k, string op, int prog_generation);
    
    /* Construct one expression: op i j */
    BaseType* growOneExpr(BaseType* i, BaseType* j, BaseType* k, string op, int prog_generation);
    
    /* Temporal program evaluation result record */
    map<pair<BaseType*, int>, int> _intResultRecord;
    map<pair<BaseType*, int>, int> _boolResultRecord;
    
    /* Evaluate program */
    inline int evaluateIntProgram(BaseType* p, int inputOutputId);
    inline bool evaluateBoolProgram(BaseType* p, int inputOutputId);
    
    /* Check whether program pi and pj are equal (based on input output examples) */
    inline bool checkTwoProgramsEqual(BaseType* pi, BaseType* pj);
    
    /* Check program p is correct or not */
    bool isCorrect(BaseType* p);
    
    /* Program list */
    vector<BaseType*> _pList;
    
    /* Input-output examples */
    inputOutputs_t _inputOutputs;

    /* Language defination */
    int _depthBound;
    vector<string> _intOps;
    vector<string> _boolOps;
    vector<string> _vars;
    vector<string> _constants;
    bool _isPred;
    int _num_of_vars;
    
    map<string, int> _vars_orders;
    
    vector<string> _rulesToApply;
};
#endif
