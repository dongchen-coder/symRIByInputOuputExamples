#include "../lib/bottomUpSearch.hpp"
#include "../lib/unification.hpp"
#include "../lib/sampler.hpp"
#include "../lib/typeDef.hpp"
#include <vector>
#include <future>
#include <chrono>
#include <thread>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//#define DEBUG

bool parser(int argc, char* argv[],
            string* fileName,
            int* searchTimeForTermsInSeconds,
            int* searchTimeForPredsInSeconds,
            int* depthBoundPred,
            vector<string>* intOpsPred,
            vector<string>* boolOpsPred,
            vector<string>* varsPred,
            vector<string>* constantsPred,
            int* depthBoundTerm,
            vector<string>* intOpsTerm,
            vector<string>* boolOpsTerm,
            vector<string>* varsTerm,
            vector<string>* constantsTerm,
            vector<string>* rulesToApply) {
    
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
        else if (argvi == "-SEARCHTIMEFORTERMSINSECONDS") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *searchTimeForTermsInSeconds = stoi(argv[i]);
                } else {
                    return false;
                }
            } else {
                cout << "-SEARCHTIMEFORTERMSINSECONDS: error in specifying the search time" << endl;
                return false;
            }
        }
        else if (argvi == "-SEARCHTIMEFORPREDSINSECONDS") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *searchTimeForPredsInSeconds = stoi(argv[i]);
                } else {
                    return false;
                }
            } else {
                cout << "-SEARCHTIMEFORPREDSINSECONDS: error in specifying the search time" << endl;
                return false;
            }
        }
        else if (argvi == "-RULESTOAPPLY") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    rulesToApply->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                cout << "-RULESTOAPPLY: error in specifying the bool ops in the term language" << endl;
                return false;
            }
        }
        else {
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
                       inputOutputs_t inputOutputs) {
    
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
        for (auto varValue : inputOutputs[0]) {
            if (varValue.first != "_out") {
                varsPred->push_back(varValue.first);
                varsTerm->push_back(varValue.first);
            }
        }
    }
    
    return;
}

void filterNonKeyIOEs(inputOutputs_t* inputOutputs) {
    // find the set of bound variables and values
    set<string> bound_vars;
    set<int> bound_value;
    for (auto ioe : *inputOutputs) {
        for (auto [var, cnt] : ioe) {
            if (var.find("b") != string::npos) {
                bound_vars.insert(var);
                bound_value.insert(cnt);
            }
        }
    }
    map<int, int> bound_value_to_index;
    int index = 0;
    for (auto v : bound_value) {
        bound_value_to_index[v] = index;
        index++;
    }
    
    // replace bound variables from values to indices
    map<vector<int>, int> bound_space;
    int m = bound_vars.size();
    for (auto ioe : *inputOutputs) {
        vector<int> bound_vec;
        for (int i = 0; i < m; i++) {
            bound_vec.push_back(bound_value_to_index[ioe["b" + to_string(i)]]);
        }
        bound_space[bound_vec] = ioe["_out"];
    }
    
    // mark non-key ioe in bound_space
    set<vector<int>> non_key_ioes;
    for (auto [vec0, value0] : bound_space) {
        int same_cnt = 0;
        for (auto [vec1, value1] : bound_space) {
            int distant = 0;
            for (int i = 0; i < vec0.size(); i++) {
                distant += (vec0[i] - vec1[i]) * (vec0[i] - vec1[i]);
            }
            if (distant == 1 && value0 != value1)
                same_cnt++;
        }
        if (same_cnt == 0) {
            non_key_ioes.insert(vec0);
        }
    }
    
    map<int, set<vector<int>>> reserved_ioes;
    auto it = inputOutputs->begin();
    while(it != inputOutputs->end()) {
        auto ioe = *it;
        vector<int> bound_vec;
        for (int i = 0; i < m; i++) {
            bound_vec.push_back(bound_value_to_index[ioe["b" + to_string(i)]]);
        }
        if (find(non_key_ioes.begin(), non_key_ioes.end(), bound_vec) == non_key_ioes.end()) {
            //it = inputOutputs->erase(it);
            //} else {
            reserved_ioes[ioe["_out"]].insert(bound_vec);
        }
        ++it;
    }
    
    for (auto [out, set_v] : reserved_ioes) {
        for (int i = 1; i < set_v.size()-1; i++) {
            auto v1 = *next(set_v.begin(), i-1);
            auto v2 = *next(set_v.begin(), i);
            auto v3 = *next(set_v.begin(), i+1);
            vector<int> diff_v1_v2;
            vector<int> diff_v2_v3;
            for (int j = 0; j < v1.size(); j++) {
                diff_v1_v2.push_back(v2[j]-v1[j]);
            }
            for (int j = 0; j < v2.size(); j++) {
                diff_v2_v3.push_back(v3[j]-v2[j]);
            }
            if (diff_v1_v2 == diff_v2_v3) {
                non_key_ioes.insert(v2);
            }
        }
    }
    
    //cout << bound_space.size() << " ";
    //cout << non_key_ioes.size() << endl;
    
    it = inputOutputs->begin();
    while(it != inputOutputs->end()) {
        auto ioe = *it;
        vector<int> bound_vec;
        for (int i = 0; i < m; i++) {
            bound_vec.push_back(bound_value_to_index[ioe["b" + to_string(i)]]);
        }
        if (find(non_key_ioes.begin(), non_key_ioes.end(), bound_vec) != non_key_ioes.end()) {
            it = inputOutputs->erase(it);
        } else {
            ++it;
        }
    }
    
}

bool readInputOutput(string fileName, inputOutputs_t* inputOutputs) {
    ifstream ifs;
    ifs.open(fileName, ifstream::in);
    string line;
    
    while (getline(ifs, line)) {
        inputOutput_t inputOutput;
        
        stringstream ss(line);
        string var;
        int value;
        while (ss >> var) {
            ss >> value;
            inputOutput[var] = value;
        }
        
        if (!inputOutput.empty())
            inputOutputs->push_back(inputOutput);
        
    }
    
    ifs.close();
    
    //cout << "Resize IOE " << inputOutputs->size() << " to ";
    filterNonKeyIOEs(inputOutputs);
    //cout << inputOutputs->size() << endl;
    
    return true;
}

void writeSearchedProgram(string fileName, string prog) {
    ofstream ofs;
    size_t pos = fileName.find("/ris_per_iter_refsrc/");
    if (pos != string::npos) {
        pos = fileName.find_last_of("/");
        string conf = fileName.substr(pos+1, fileName.size());
        string header = fileName.substr(0, pos);
        pos = header.find_last_of("/");
        fileName.replace(0, pos, "./synResult/");
        fileName.replace(fileName.size() - 4, fileName.size(), "_src.txt");
        ofs.open(fileName);
        if (ofs.is_open()) {
            ofs << conf << " " << prog;
        }
        ofs.close();
    }
    return;
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
        cout << "      -SEARCHTIMEFORTERMSSINSECONDS : specify the search time for terms in seconds" << endl;
        cout << "      -SEARCHTIMEFORPREDSINSECONDS : specify the search time for preds in seconds" << endl;
        cout << "    Optional to sepcify the search rules to apply" << endl;
        cout << "      -RULESTOAPPLY : specify search mode (SrcOnly, SrcEnhanced, SrcSnk)" << endl;
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
    
    int searchTimeForTermsInSeconds = 20;
    int searchTimeForPredsInSeconds = 20;
    
    vector<string> rulesToApply;
    
    if ( parser(argc, argv,
               &fileName, &searchTimeForTermsInSeconds, &searchTimeForPredsInSeconds,
               &depthBoundPred, &intOpsPred, &boolOpsPred, &varsPred, &constantsPred,
               &depthBoundTerm, &intOpsTerm, &boolOpsTerm, &varsTerm, &constantsTerm,
               &rulesToApply) == false ) {
        cout << "Error in parsing command lines" << endl;
        return 0;
    }
    
    /*
     read input output files
     */
    inputOutputs_t inputOutputs;
    if (!readInputOutput(fileName, &inputOutputs)) {
        cout << "Error reading files" << endl;
        return 0;
    }
    
    /* sample inputouput Files */
    //sampler s(0.1);
    //inputOutputs = s.randomSampling(inputOutputs);
    
    /*
     output search mode
     */
    
#ifdef DEBUG
    if (rulesToApply.empty()) {
        cout << "No mode specific rules specified" << endl;
    }
    else {
        cout << "Applying rules: " << endl;
        for (auto rule : rulesToApply) {
            cout << rule << " ";
        }
        cout << endl;
    }
#endif
    
    /*
     language configuration
    */
    langConfiguration(&depthBoundPred, &intOpsPred, &boolOpsPred, &varsPred, &constantsPred,
                      &depthBoundTerm, &intOpsTerm, &boolOpsTerm, &varsTerm, &constantsTerm,
                      inputOutputs);
    
    unification* uni = new unification(depthBoundPred, intOpsPred, boolOpsPred, varsPred, constantsPred,
                                       depthBoundTerm, intOpsTerm, boolOpsTerm, varsTerm, constantsTerm,
                                       rulesToApply,
                                       inputOutputs);
#ifdef DEBUG
    cout << "Search time: terms " << searchTimeForTermsInSeconds << " predications " << searchTimeForPredsInSeconds << endl;
    uni->dumpLangDef();
#endif

    uni->search(searchTimeForTermsInSeconds, searchTimeForPredsInSeconds);

#ifdef DEBUG
    uni->dumpSearchedProgram();
#endif

    //writeSearchedProgram(fileName, uni->getSearchedProgram());
    uni->dumpSearchedProgram();
    
    return 0;
}
