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

bool parser(int argc, char* argv[],
            string* fileName,
            int* searchTimeInSeconds,
            int* depthBoundPred,
            vector<string>* intOpsPred,
            vector<string>* boolOpsPred,
            vector<string>* varsPred,
            vector<string>* constantsPred,
            int* depthBoundTerm,
            vector<string>* intOpsTerm,
            vector<string>* boolOpsTerm,
            vector<string>* varsTerm,
            vector<string>* constantsTerm) {
    
    for (int i = 1; i < argc; i++) {
        
        string argvi(argv[i]);
        
        if (argvi == "-FILE") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                *fileName = argvi;
            } else {
                cout << "-FILE: error in providing file name" << endl;
                return false;
            }
        }
        else if (argvi == "-DEPTHBOUNDPRED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *depthBoundPred = stoi(argv[i]);
                } else {
                    return false;
                }
            } else {
                cout << "-DEPTHBOUNDPRED: error in specifying the depth of the predicate program" << endl;
                return false;
            }
        }
        else if (argvi == "-INTOPSPRED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    intOpsPred->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                cout << "-INTOPSPRED: error in specifying the int ops for predicate language" << endl;
                return false;
            }
        }
        else if (argvi == "-BOOLOPSPRED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    boolOpsPred->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                cout << "-BOOLOPSPRED: error in specifying the bool ops for predicate language" << endl;
                return false;
            }
        }
        else if (argvi == "-VARSPRED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    varsPred->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                cout << "-VARSPRED: error in specifying the variables allowed in predicate language" << endl;
                return false;
            }
        }
        else if (argvi == "-CONSTANTSPRED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && isdigit(argvi[0])) {
                    constantsPred->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                cout << "-CONSTANTSPRED: error in specifying the constants allowed in predicate language" << endl;
                return false;
            }
        }
        else if (argvi == "-DEPTHBOUNDTERM") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *depthBoundTerm = stoi(argv[i]);
                } else {
                    return false;
                }
            } else {
                cout << "-DEPTHBOUNDTERM: error in specifying the depth of the term program" << endl;
                return false;
            }
        }
        else if (argvi == "-INTOPSTERM") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    intOpsTerm->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                cout << "-INTOPSTERM: error in specifying the int ops in the term language" << endl;
                return false;
            }
        }
        else if (argvi == "-BOOLOPSTERM") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    boolOpsTerm->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                cout << "-BOOLOPSTERM: error in specifying the bool ops in the term language" << endl;
                return false;
            }
        }
        else if (argvi == "-VARSTERM") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    varsTerm->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                cout << "-VARSTERM: error in specifying the variables allowed in the term language" << endl;
                return false;
            }
        }
        else if (argvi == "-CONSTANTSTERM") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && isdigit(argvi[0])) {
                    constantsTerm->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                cout << "-CONSTANTSTERM: error in specifying the constants in the term language" << endl;
                return false;
            }
        }
        else if (argvi == "-SEARCHTIMEINSECONDS") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *searchTimeInSeconds = stoi(argv[i]);
                } else {
                    
                    return false;
                }
            } else {
                cout << "-SEARCHTIMEINSECONDS: error in specifying the search time" << endl;
                return false;
            }
        } else {
            cout << "error in providing command line arguments" << endl;
            return false;
        }
    }
    
    return true;
}

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
    
    if (*depthBoundPred == -1) {
        *depthBoundPred = 6;
    }
    /*
     specify the language u use
     */
    if (intOpsPred->size() == 0) {
        intOpsPred->push_back("VAR");
        //intOpsPred->push_back("NUM");
        intOpsPred->push_back("PLUS");
        //intOpsPred->push_back("MINUS");
        //intOpsPred->push_back("TIMES");
        //intOpsPred->push_back("ITE");
    }
      
    if (boolOpsPred->size() == 0) {
        boolOpsPred->push_back("F");
        boolOpsPred->push_back("AND");
        boolOpsPred->push_back("NOT");
        boolOpsPred->push_back("LT");
    }
    
    if (constantsPred->size() == 0) {
        //constantsPred->push_back("0");
        //constantsPred->push_back("1");
        constantsPred->push_back("2");
        //constantsPred->push_back("3");
        //constantsPred->push_back("4");
        //constantsPred->push_back("5");
        //constantsPred->push_back("6");
        //constantsPred->push_back("-1");
    }
    
    if (*depthBoundTerm == -1) {
        *depthBoundTerm = 6;
    }
    
    if (intOpsTerm->size() == 0) {
        intOpsTerm->push_back("VAR");
        intOpsTerm->push_back("NUM");
        intOpsTerm->push_back("PLUS");
        //intOpsTerm->push_back("MINUS");
        intOpsTerm->push_back("TIMES");
        //intOpsTerm->push_back("ITE");
    }
    
    if (boolOpsTerm->size() == 0) {
        //boolOpsTerm->push_back("F");
        //boolOpsTerm->push_back("AND");
        //boolOpsTerm->push_back("NOT");
        //boolOpsTerm->push_back("LT");
    }
    
    if (constantsTerm->size() == 0) {
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
    }
    
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
/*
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
*/
    return true;
}


int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        cout << "Error: command line options:" << endl;
        cout << "      -FILE : specify path with the name of input-output-example file" << endl;
        cout << "    Optional specification for predicate language" << endl;
        cout << "      -DEPTHBOUNDPRED : specify the depth of a predicate program" << endl;
        cout << "      -INTOPSPRED : specify the int ops for the predication language" << endl;
        cout << "      -BOOLOPSPRED : specify the bool ops for the predication language" << endl;
        cout << "      -VARSPRED : specify the variables allowed in the predication language" << endl;
        cout << "      -CONSTANTSPRED : specify the constants allowed in the predication language" << endl;
        cout << "    Optional specification for term language" << endl;
        cout << "      -DEPTHBOUNDTERM : specify the depth of a term program" << endl;
        cout << "      -INTOPSTERM : specify the int ops for the term language" << endl;
        cout << "      -BOOLOPSTERM : specify the bool ops for the term language" << endl;
        cout << "      -VARSTERM : specify the variables allowed in the term language" << endl;
        cout << "      -CONSTANTSTERM : specify the constants allowed in the term language" << endl;
        cout << "    Optional to specify the search time (default to 20 seconds)"<< endl;
        cout << "      -SEARCHTIMEINSECONDS : specify the search time in seconds" << endl;
        
        return 0;
    }
    
    /*
     parse command line
     */
    string fileName;
    int depthBoundPred = -1;
    vector<string> intOpsPred;
    vector<string> boolOpsPred;
    vector<string> varsPred;
    vector<string> constantsPred;
    int depthBoundTerm = -1;
    vector<string> intOpsTerm;
    vector<string> boolOpsTerm;
    vector<string> varsTerm;
    vector<string> constantsTerm;
    
    int searchTimeInSeconds = 20;
    
    if ( parser(argc, argv,
               &fileName, &searchTimeInSeconds,
               &depthBoundPred, &intOpsPred, &boolOpsPred, &varsPred, &constantsPred,
               &depthBoundTerm, &intOpsTerm, &boolOpsTerm, &varsTerm, &constantsTerm) == false ) {
        cout << "Error in parsing command lines" << endl;
        return 0;
    }
    
    /*
     read input output files
     */
    vector<map<string, int> > inputOutputs;
    if (!readInputOutput(fileName, &inputOutputs)) {
        cout << "Error reading files" << endl;
        return 0;
    }
    
    /*
     language configuration
    */
    langConfiguration(&depthBoundPred, &intOpsPred, &boolOpsPred, &varsPred, &constantsPred,
                      &depthBoundTerm, &intOpsTerm, &boolOpsTerm, &varsTerm, &constantsTerm,
                      inputOutputs);
    
    unification* uni = new unification(depthBoundPred, intOpsPred, boolOpsPred, varsPred, constantsPred,
                                       depthBoundTerm, intOpsTerm, boolOpsTerm, varsTerm, constantsTerm,
                                       inputOutputs);
    //uni->dumpLangDef();
    uni->search(searchTimeInSeconds);
    //uni->dumpInputOutputTree();
    uni->dumpSearchedProgram();
    
    return 0;
}
