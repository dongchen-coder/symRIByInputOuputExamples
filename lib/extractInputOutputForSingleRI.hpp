#ifndef EXTRACTINPUTOUTPUTFORSINGLERI_H
#define EXTRACTINPUTOUTPUTFORSINGLERI_H

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

void processSingleRiFile(string name, int isize, int jsize);
void readAllRi(string name, vector<int> sizes);

void dumpPerRefRi(vector<int> sizes);

void genInputOutputExample(string name, vector<int> sizes);

#endif
