#include "../lib/extractInputOutputForSingleRI.hpp"
#include <vector>
#include <exception>
using namespace std;

bool parser(int argc, char* argv[], vector<uint64_t>* sizes, string* name, int* numOfLoopBounds, double* samplingRate) {
    for (int i = 1; i < argc; i++) {
        string argvi(argv[i]);
        if (argvi == "-NAME") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                *name = argvi;
            }
            else {
                return false;
            }
        }
        else if (argvi == "-SIZES") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    while(isdigit(argvi[0])) {
                        sizes->push_back(stoi(argvi));
                        i++;
                        argvi = argv[i];
                    }
                    i--;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else if (argvi == "-NUMOFLOOPBOUNDS") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *numOfLoopBounds = stoi(argvi);
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else if (argvi == "-SAMPLINGRATE") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                bool is_double;
                string::size_type sz;
                try {
                    *samplingRate = stod(argvi, &sz);
                    is_double = true;
                }
                catch (exception &e) {
                    is_double = false;
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    /* configurations */
    vector<uint64_t> sizes;
    string name;
    int numOfSymbolicLoopBounds;
    double samplingRate = 1;
    
    if(!parser(argc, argv, &sizes, &name, &numOfSymbolicLoopBounds, &samplingRate)) {
        cout << "Error in parsing command line" << endl;
        return 0;
    } else {
        cout << "finished reading arguments" << endl;
        cout << "name: " << name << endl;
        cout << "sizes: ";
        for (int i = 0; i < sizes.size(); i++) cout << sizes[i] << " ";
        cout << endl;
        cout << "num of symbolic loop bounds: " << numOfSymbolicLoopBounds << endl;
        cout << "sampling rate: " << samplingRate << endl;
    }
    
    /* read all ri into a map */
    readAllRi(name, sizes, numOfSymbolicLoopBounds);
    
    dumpPerRefRi(sizes);
    
    /* construct inputoutput examples for each iteration */
    genInputOutputExample(name, sizes, numOfSymbolicLoopBounds, samplingRate);
    
    return 0;
}

