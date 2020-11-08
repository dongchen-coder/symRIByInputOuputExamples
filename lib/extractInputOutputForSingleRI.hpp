#ifndef EXTRACTINPUTOUTPUTFORSINGLERI_H
#define EXTRACTINPUTOUTPUTFORSINGLERI_H

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <iomanip>
using namespace std;

//#define WITHPOS
//#define DEBUG

/* Split helper function */
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);

/* Filter RI */
void filterSrcIter();
vector<vector<uint64_t> > samplingBorderInner(vector< vector<uint64_t> > idxs, double samplingRate);
vector<vector<uint64_t> > samplingRandom(vector< vector<uint64_t> > idxs, double samplingRate);

/* gen train sizes for bounds */
vector<vector<uint64_t> > genTrainSizes(vector<uint64_t> sizes, int numOfSymbolicLoopBounds);

/* Read RI from files */
void processSingleRiFile(string cacheConfig, string name, string fileSuffix, vector<uint64_t> symbolic_bounds);
void readAllRi(string cacheConfig, string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds);
void processSingleIBoundFile(string name, string fileSuffix, vector<uint64_t> symbolic_bounds);
void readAllIBound(string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds);


/* Dump RI */
void dumpPerRefRi(vector<uint64_t> sizes);

/* Generate inputoutput example */
void genInOutWithFormatSrcIterPos(string cacheConfig, string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds, double samplingRate);
void genInOutWithFormatSrcIterPosSnk(string cacheConfig, string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds, double samplingRate);
void genInOutWithFormatSrcIterPosSnkIterPos(string cacheConfig, string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds, double samplingRate);
void genInOutWithFormatSrcShapeFromReuses(string cacheConfig, string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds);
void genInOutWithFormatSrcShapeFromAccesses(string name, vector<uint64_t> sizes, int numOfSymbolicLoopBounds);
#endif
