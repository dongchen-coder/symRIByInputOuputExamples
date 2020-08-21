#ifndef EXTRACTINPUTOUTPUTFORSINGLERI_H
#define EXTRACTINPUTOUTPUTFORSINGLERI_H

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
using namespace std;

/* Split helper function */
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);

/* Filter RI */
void filterSrcIter();
vector<vector<uint64_t> > samplingBorderInner(vector< vector<uint64_t> > idxs, double samplingRate);

/* Read RI from files */
void processSingleRiFile(string name, string fileSuffix, vector<uint64_t> symbolic_bounds);
void readAllRi(string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds);


/* Dump RI */
void dumpPerRefRi(vector<uint64_t> sizes);

/* Generate inputoutput example */
void genInputOutputExample(string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds, double samplingRate);

#endif
