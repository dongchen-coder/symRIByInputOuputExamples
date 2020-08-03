#ifndef BOTTOMUPSEARCH_H
#define BOTTOMUPSEARCH_H

#include "langDef.hpp"
#include <future>
#include <chrono>
#include <thread>
#include <vector>

//#define DEBUG

using namespace std;

class bottomUpSearch {
public:
    bottomUpSearch(int depthBound,
                   vector<string> intOps,
                   vector<string> boolOps,
                   vector<string> vars,
                   vector<string> constants,
                   vector<map<string, int> > inputOutputs);
    
    /* search function */
    string search();
    
    /* dump language used */
    void dumpLangDef();
    
private:
    /* dump one program */
    string dumpProgram(BaseType* p);
    
    /* Grow program list */
    vector<BaseType*> grow();
    
    /* Eliminate equalivlent programs */
    vector<BaseType*> elimEquvalents();
    
    /* Check whether there is a correct program in program list */
    string getCorrect();
    
    /* Dumping function */
    void dumpPlist();
    void dumpPlist(vector<BaseType*> pList);
    int getPlistSize();
    
    /* Construct one expression: op i j */
    BaseType* growOneExpr(BaseType* i, BaseType* j, BaseType* k, string op, int depthBound);
    
    /* Temporal program evaluation result record */
    map<pair<BaseType*, int>, int> intResultRecord;
    map<pair<BaseType*, int>, int> boolResultRecord;
    
    /* Evaluate program */
    int evaluateIntProgram(BaseType* p, int inputOutputId);
    bool evaluateBoolProgram(BaseType* p, int inputOutputId);
    
    /* Check whether program pi and pj are equal (based on input output examples) */
    bool checkTwoProgramsEqual(BaseType* pi, BaseType* pj);
    
    /* Check program p is correct or not */
    bool isCorrect(BaseType* p);
    
    /* Program list */
    vector<BaseType*> pList;
    
    /* Input-output examples */
    vector<map<string, int> > inputOutputs;
    
    /* Language defination */
    int depthBound;
    vector<string> intOps;
    vector<string> boolOps;
    vector<string> vars;
    vector<string> constants;
};
#endif
