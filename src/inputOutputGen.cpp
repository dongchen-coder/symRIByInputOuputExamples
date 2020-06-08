#include "../lib/extractInputOutputForSingleRI.hpp"
#include <vector>
using namespace std;

bool parser(int argc, char* argv[], vector<int>* sizes, string* name, int* loopDepth) {
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
        } else if (argvi == "-LOOPDEPTH") {
            i++;
            argvi = argv[i];
            if (i < argc || isdigit(argvi[0])) {
                *loopDepth = stoi(argvi);
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
    vector<int> sizes;
    string name;
    int loopDepth;
    if(!parser(argc, argv, &sizes, &name, &loopDepth)) {
        cout << "Error in parsing command line" << endl;
        return 0;
    }
    
    readAllRi(name, sizes);
    dumpPerRefRi(sizes);
    genInputOutputExample(name, sizes);
    
    return 0;
}

