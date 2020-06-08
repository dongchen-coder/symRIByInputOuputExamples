#ifndef BOTTOMUPSEARCH_H
#define BOTTOMUPSEARCH_H

#include "langDef.hpp"
#include <future>
#include <vector>
using namespace std;

string bottomUp(future<string>& futureObj,
                int depthBound,
                vector<string> intOps,
                vector<string> boolOps,
                vector<string> vars,
                vector<string> constants,
                vector<map<string, int> > inputOutputs);

#endif
