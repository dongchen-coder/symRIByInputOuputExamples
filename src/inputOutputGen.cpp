#include "../lib/extractInputOutputForSingleRI.hpp"
#include <vector>
using namespace std;

bool parser(int argc, char* argv[], vector<uint64_t>* sizes, string* name, int* numOfLoopBounds) {
    for (int i = 1; i < argc; i++) {
        string argvi(argv[i]);
        if (argvi == "-NAME") {
            i++;
            argvi = argv[i];
            if (i < argc) {
                *name = argvi;
            } else {
                return false;
            }
        } else if (argvi == "-SIZES") {
            i++;
            argvi = argv[i];
            if (i >= argc || !isdigit(argvi[0])) {
                return false;
            }
            while(isdigit(argvi[0])) {
                sizes->push_back(stoi(argvi));
                i++;
                argvi = argv[i];
            }
            i--;
        } else if (argvi == "-NUMOFLOOPBOUNDS") {
            i++;
            argvi = argv[i];
            if (i < argc || isdigit(argvi[0])) {
                *numOfLoopBounds = stoi(argvi);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    vector<uint64_t> sizes;
    string name;
    int numOfSymbolicLoopBounds;
    if(!parser(argc, argv, &sizes, &name, &numOfSymbolicLoopBounds)) {
        cout << "Error in parsing command line" << endl;
        return 0;
    } else {
        cout << "finished reading arguments" << endl;
        cout << "name: " << name << endl;
        cout << "sizes: ";
        for (int i = 0; i < sizes.size(); i++) cout << sizes[i] << " ";
        cout << endl;
        cout << "num of symbolic loop bounds: " << numOfSymbolicLoopBounds << endl;
    }
    
    /* read all ri into a map */
    readAllRi(name, sizes, numOfSymbolicLoopBounds);
    
    dumpPerRefRi(sizes);
    
    /* construct inputoutput examples for each iteration */
    genInputOutputExample(name, sizes, numOfSymbolicLoopBounds);
    
    return 0;
}

