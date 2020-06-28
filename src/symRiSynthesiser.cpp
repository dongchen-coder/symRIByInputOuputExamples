#include "../lib/bottomUpSearch.hpp"
#include "../lib/unification.hpp"
#include <vector>
#include <future>
#include <chrono>
#include <thread>
#include <functional>
#include <string>
#include <fstream>
using namespace std;

/*
Language configuration
*/
void langConfiguration(int* depthBoundPred,
                       vector<string>* intOpsPred,
                       vector<string>* boolOpsPred,
                       vector<string>* varsPred,
                       vector<string>* constantsPred,
                       int* depthBoundTerm,
                       vector<string>* intOpsTerm,
                       vector<string>* boolOpsTerm,
                       vector<string>* varsTerm,
                       vector<string>* constantsTerm,
                       vector<map<string, int> > inputOutputs) {
    
    *depthBoundPred = 6;
    /*
     specify the language u use
     */
    intOpsPred->push_back("VAR");
    //intOpsPred->push_back("NUM");
    intOpsPred->push_back("PLUS");
    //intOpsPred->push_back("MINUS");
    //intOpsPred->push_back("TIMES");
    //intOpsPred->push_back("ITE");
    
    boolOpsPred->push_back("F");
    boolOpsPred->push_back("AND");
    
    boolOpsPred->push_back("NOT");
    boolOpsPred->push_back("LT");
    
    //constantsPred->push_back("0");
    //constantsPred->push_back("1");
    constantsPred->push_back("2");
    //constantsPred->push_back("3");
    //constantsPred->push_back("4");
    //constantsPred->push_back("5");
    //constantsPred->push_back("6");
    //constantsPred->push_back("-1");
    
    *depthBoundTerm = 6;
    
    intOpsTerm->push_back("VAR");
    intOpsTerm->push_back("NUM");
    intOpsTerm->push_back("PLUS");
    //intOpsTerm->push_back("MINUS");
    intOpsTerm->push_back("TIMES");
    //intOpsTerm->push_back("ITE");
    
    //boolOpsTerm->push_back("F");
    //boolOpsTerm->push_back("AND");
    //boolOpsTerm->push_back("NOT");
    //boolOpsTerm->push_back("LT");
    
    //constantsTerm->push_back("0");
    constantsTerm->push_back("1");
    constantsTerm->push_back("2");
    constantsTerm->push_back("3");
    constantsTerm->push_back("4");
    constantsTerm->push_back("5");
    constantsTerm->push_back("6");
    constantsTerm->push_back("7");
    constantsTerm->push_back("8");
    constantsTerm->push_back("9");
    constantsTerm->push_back("10");
    constantsTerm->push_back("11");
    constantsTerm->push_back("12");
    constantsTerm->push_back("-1");
    
    /*
     varables are extracted from inputoutput examples
     */
    if (!inputOutputs.empty()) {
        for (map<string, int>::iterator it = inputOutputs[0].begin(), eit = inputOutputs[0].end(); it != eit; ++it) {
            if (it->first != "_out") {
                varsPred->push_back(it->first);
                varsTerm->push_back(it->first);
            }
        }
    }
    
    return;
}

bool readInputOutput(string fileName, vector<map<string, int> >* inputOutputs) {
    ifstream ifs;
    ifs.open(fileName, ifstream::in);
    string line;
    
    while (getline(ifs, line)) {
        string var = "";
        string value = "";
        int spaceCnt = 0;
        map<string, int> inputOutput;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ' ') {
                if (spaceCnt % 2 == 0) {
                    value = "";
                } else {
                    if (isdigit(value[0])) {
                        inputOutput[var] = stoi(value);
                    } else {
                        cout << "value need to be int" << endl;
                        return false;
                    }
                    var = "";
                }
                spaceCnt ++;
            } else {
                if (spaceCnt % 2 == 0) {
                    var.push_back(line[i]);
                } else {
                    value.push_back(line[i]);
                }
            }
        }
        if (isdigit(value[0])) {
            inputOutput[var] = stoi(value);
        } else if (value == "X") {
            inputOutput[var] = -1;
        } else {
            cout << "value need to be int" << endl;
            return false;
        }
        inputOutputs->push_back(inputOutput);
    }
    
    cout << "Input output examples:" << endl;
    for (vector<map<string, int> >::iterator it = inputOutputs->begin(), eit = inputOutputs->end(); it != eit; ++it) {
        cout << "    ";
        for (map<string, int>::iterator it_m = (*it).begin(), eit_m = (*it).end(); it_m != eit_m; ++it_m) {
            if (it_m->first != "_out") {
                cout << it_m->first << " " << it_m->second << " ";
            }
        }
        cout << "   _out " << (*it)["_out"] << endl;
    }
    return true;
}

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        cout << "Error: command line only need inputoutput file name" << endl;
        return 0;
    }
    
    /*
     read input output files
     */
    string fileName(argv[1]);
    vector<map<string, int> > inputOutputs;
    if (!readInputOutput(fileName, &inputOutputs)) {
        cout << "Error reading files" << endl;
        return 0;
    }
    
    /*
     language configuration
    */
    int depthBoundPred;
    vector<string> intOpsPred;
    vector<string> boolOpsPred;
    vector<string> varsPred;
    vector<string> constantsPred;
    int depthBoundTerm;
    vector<string> intOpsTerm;
    vector<string> boolOpsTerm;
    vector<string> varsTerm;
    vector<string> constantsTerm;
    
    langConfiguration(&depthBoundPred, &intOpsPred, &boolOpsPred, &varsPred, &constantsPred,
                      &depthBoundTerm, &intOpsTerm, &boolOpsTerm, &varsTerm, &constantsTerm,
                      inputOutputs);
    
    unification* uni = new unification(depthBoundPred, intOpsPred, boolOpsPred, varsPred, constantsPred,
                                       depthBoundTerm, intOpsTerm, boolOpsTerm, varsTerm, constantsTerm,
                                       inputOutputs);
    uni->dumpLangDef();
    uni->search(20);
    uni->dumpInputOutputTree();
    uni->dumpSearchedProgram();
    
    return 0;
}
