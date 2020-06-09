#ifndef BOTTOMUPSEARCH_H
#define BOTTOMUPSEARCH_H

#include "langDef.hpp"
#include <future>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;

string bottomUp(future<string>& futureObj,
                promise<string>& exitSignal,
                int depthBound,
                vector<string> intOps,
                vector<string> boolOps,
                vector<string> vars,
                vector<string> constants,
                vector<map<string, int> > inputOutputs);

#endif
