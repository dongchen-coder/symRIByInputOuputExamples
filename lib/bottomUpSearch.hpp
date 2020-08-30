#ifndef BOTTOMUPSEARCH_H
#define BOTTOMUPSEARCH_H

#include "langDef.hpp"
#include "typeDef.hpp"
#include <future>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

//#define DEBUG

class bottomUpSearch {
public:
    bottomUpSearch(int depthBound,
                   vector<string> intOps,
                   vector<string> boolOps,
                   vector<string> vars,
                   vector<string> constants,
                   inputOutputs_t inputOutputs,
                   string searchMode);
    
    /* search function */
    string search();
    
    /* dump language used */
    void dumpLangDef();
    
private:
    /* dump one program */
    string dumpProgram(BaseType* p);
    
    /* Grow program list */
    void grow();
    
    /* Eliminate equalivlent programs */
    void elimEquvalents();
    
    /* Check whether there is a correct program in program list */
    string getCorrect();
    
    /* Dumping function */
    void dumpPlist();
    void dumpPlist(vector<BaseType*> pList);
    int getPlistSize();
    
    /* grow expression rules */
    bool isGrowRuleSatisfied(BaseType* i, BaseType* j, BaseType* k, string op, int depthBound);
    
    /* Construct one expression: op i j */
    BaseType* growOneExpr(BaseType* i, BaseType* j, BaseType* k, string op, int depthBound);
    
    /* Temporal program evaluation result record */
    map<pair<BaseType*, int>, int> intResultRecord;
    map<pair<BaseType*, int>, int> boolResultRecord;
    
    /* Evaluate program */
    inline int evaluateIntProgram(BaseType* p, int inputOutputId);
    inline bool evaluateBoolProgram(BaseType* p, int inputOutputId);
    
    /* Check whether program pi and pj are equal (based on input output examples) */
    inline bool checkTwoProgramsEqual(BaseType* pi, BaseType* pj);
    
    /* Check program p is correct or not */
    bool isCorrect(BaseType* p);
    
    /* Program list */
    vector<BaseType*> pList;
    
    /* Input-output examples */
    inputOutputs_t inputOutputs;
    
    /* Search mode */
    string searchMode;

    /* Language defination */
    int depthBound;
    vector<string> intOps;
    vector<string> boolOps;
    vector<string> vars;
    vector<string> constants;
};
#endif
