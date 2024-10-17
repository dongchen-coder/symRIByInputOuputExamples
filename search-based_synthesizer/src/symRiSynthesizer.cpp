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
            string* file_name,
            int* search_time_for_terms_in_seconds,
            int* search_time_for_predicates_in_seconds,
            int* depth_bound_for_predicate,
            vector<string>* int_ops_for_predicate,
            vector<string>* bool_ops_for_predicate,
            vector<string>* vars_in_predicate,
            vector<string>* constants_in_predicate,
            int* depth_bound_for_term,
            vector<string>* int_ops_for_term,
            vector<string>* bool_ops_for_term,
            vector<string>* vars_in_term,
            vector<string>* constants_in_term,
            vector<string>* rules_to_apply,
            string* bench_name,
            int* ref_id,
            int* num_growing_speed,
            int* num_growing_upperbound) {
    
    for (int i = 1; i < argc; i++) {
        
        string argvi(argv[i]);
        
        if (argvi == "-FILE") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                *file_name = argvi;
                string tmp = argvi.substr(argvi.rfind("/") + 1);
                if (tmp.find("_") == string::npos) throw runtime_error("can not extract bench name from file name");
                *bench_name = tmp.substr(0, tmp.find("_"));
                if (tmp.find("refsrc_") == string::npos) throw runtime_error("can not extract ref id from file name");
                tmp = argvi.substr(argvi.rfind("refsrc_") + 7);
                *ref_id = stoi(tmp.substr(0, tmp.find("_")));
                continue;
            }
            throw runtime_error("-FILE: error in providing file name");
        }
        else if (argvi == "-DEPTHBOUNDPRED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *depth_bound_for_predicate = stoi(argv[i]);
                    continue;
                }
                throw runtime_error("-DEPTHBOUNDPRED: error in specifying the depth of the predicate program");
            }
        }
        else if (argvi == "-INTOPSPRED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    int_ops_for_predicate->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                throw runtime_error("-INTOPSPRED: error in specifying the int ops for predicate language");
            }
        }
        else if (argvi == "-BOOLOPSPRED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    bool_ops_for_predicate->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                throw runtime_error("-BOOLOPSPRED: error in specifying the bool ops for predicate language");
            }
        }
        else if (argvi == "-VARSPRED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    vars_in_predicate->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                throw runtime_error("-VARSPRED: error in specifying the variables allowed in predicate language");
            }
        }
        else if (argvi == "-CONSTANTSPRED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && isdigit(argvi[0])) {
                    constants_in_predicate->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                throw runtime_error("-CONSTANTSPRED: error in specifying the constants allowed in predicate language");
            }
        }
        else if (argvi == "-DEPTHBOUNDTERM") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *depth_bound_for_term = stoi(argv[i]);
                } else {
                    return false;
                }
            } else {
                throw runtime_error("-DEPTHBOUNDTERM: error in specifying the depth of the term program");
            }
        }
        else if (argvi == "-INTOPSTERM") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    int_ops_for_term->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                throw runtime_error("-INTOPSTERM: error in specifying the int ops in the term language");
            }
        }
        else if (argvi == "-BOOLOPSTERM") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    bool_ops_for_term->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                throw runtime_error("-BOOLOPSTERM: error in specifying the bool ops in the term language");
            }
        }
        else if (argvi == "-VARSTERM") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    vars_in_term->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                throw runtime_error("-VARSTERM: error in specifying the variables allowed in the term language");
            }
        }
        else if (argvi == "-CONSTANTSTERM") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && isdigit(argvi[0])) {
                    constants_in_term->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                throw runtime_error("-CONSTANTSTERM: error in specifying the constants in the term language");
            }
        }
        else if (argvi == "-SEARCHTIMEFORTERMSINSECONDS") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *search_time_for_terms_in_seconds = stoi(argv[i]);
                } else {
                    return false;
                }
            } else {
                throw runtime_error("-SEARCHTIMEFORTERMSINSECONDS: error in specifying the search time");
            }
        }
        else if (argvi == "-SEARCHTIMEFORPREDSINSECONDS") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *search_time_for_predicates_in_seconds = stoi(argv[i]);
                } else {
                    return false;
                }
            } else {
                throw runtime_error("-SEARCHTIMEFORPREDSINSECONDS: error in specifying the search time");
            }
        }
        else if (argvi == "-RULESTOAPPLY") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                while(argvi[0] != '-' && !isdigit(argvi[0])) {
                    rules_to_apply->push_back(argvi);
                    i++;
                    if (i >= argc) {
                        break;
                    }
                    argvi = argv[i];
                }
                i--;
            } else {
                throw runtime_error("-RULESTOAPPLY: error in specifying the bool ops in the term language");
            }
        }
        else if (argvi == "-NUMGROWSPEED") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *num_growing_speed = stoi(argvi);
                    continue;
                }
            }
            throw runtime_error("-NUMGROWSPEED: error in specifying the growing speed of the number");
        }
        else if (argvi == "-NUMGROWUPPERBOUND") {
            i++;
            if (i < argc) {
                argvi = argv[i];
                if (isdigit(argvi[0])) {
                    *num_growing_upperbound = stoi(argvi);
                    continue;
                }
            }
            throw runtime_error("-NUMGROWUPPERBOUND: error in specifying the upper bound of the constant number");
        }
        else {
            throw runtime_error("error in providing command line arguments");
        }
    }
    
    return true;
}

/*
Language configuration
*/
void language_configuration(int* depth_bound_for_predicate,
                       vector<string>* int_ops_for_predicate,
                       vector<string>* bool_ops_for_predicate,
                       vector<string>* vars_in_predicate,
                       vector<string>* constants_in_predicate,
                       int* depth_bound_for_term,
                       vector<string>* int_ops_for_term,
                       vector<string>* bool_ops_for_term,
                       vector<string>* vars_in_term,
                       vector<string>* constants_in_term,
                       input_outputs_t input_outputs) {
    
    if (*depth_bound_for_predicate == -1) {
        *depth_bound_for_predicate = 6;
    }
    /*
     specify the language u use
     */
    if (int_ops_for_predicate->size() == 0) {
        int_ops_for_predicate->push_back("VAR");
        int_ops_for_predicate->push_back("NUM");
        int_ops_for_predicate->push_back("PLUS");
        //int_ops_for_predicate->push_back("MINUS");
        int_ops_for_predicate->push_back("TIMES");
        //int_ops_for_predicate->push_back("ITE");
    }
      
    if (bool_ops_for_predicate->size() == 0) {
        bool_ops_for_predicate->push_back("F");
        bool_ops_for_predicate->push_back("AND");
        bool_ops_for_predicate->push_back("NOT");
        bool_ops_for_predicate->push_back("LT");
    }
    
    if (constants_in_predicate->size() == 0) {
        constants_in_predicate->push_back("0");
        constants_in_predicate->push_back("1");
        constants_in_predicate->push_back("2");
        constants_in_predicate->push_back("3");
        constants_in_predicate->push_back("5");
        constants_in_predicate->push_back("7");
        constants_in_predicate->push_back("11");
        constants_in_predicate->push_back("13");
        constants_in_predicate->push_back("17");
        constants_in_predicate->push_back("19");
        constants_in_predicate->push_back("23");
        constants_in_predicate->push_back("29");
        constants_in_predicate->push_back("31");
        constants_in_predicate->push_back("41");
        constants_in_predicate->push_back("43");
        constants_in_predicate->push_back("47");
        constants_in_predicate->push_back("53");
    }
    
    if (*depth_bound_for_term == -1) {
        *depth_bound_for_term = 6;
    }
    
    if (int_ops_for_term->size() == 0) {
        int_ops_for_term->push_back("VAR");
        int_ops_for_term->push_back("NUM");
        int_ops_for_term->push_back("PLUS");
        int_ops_for_term->push_back("TIMES");
        
        //int_ops_for_term->push_back("MINUS");
        //int_ops_for_term->push_back("ITE");
    }
    
    if (constants_in_term->size() == 0) {
        constants_in_term->push_back("0");
        constants_in_term->push_back("1");
        constants_in_term->push_back("2");
        constants_in_term->push_back("3");
        constants_in_term->push_back("5");
        constants_in_term->push_back("7");
        constants_in_term->push_back("11");
        constants_in_term->push_back("13");
        constants_in_term->push_back("17");
        constants_in_predicate->push_back("19");
        constants_in_predicate->push_back("23");
        constants_in_predicate->push_back("29");
        constants_in_predicate->push_back("31");
        constants_in_predicate->push_back("41");
        constants_in_predicate->push_back("43");
        constants_in_predicate->push_back("47");
        constants_in_predicate->push_back("53");
    }
    
    /*
     varables are extracted from inputoutput examples
     */
    if (!input_outputs.empty()) {
        for (auto varValue : input_outputs[0]) {
            if (varValue.first != "_out") {
                vars_in_predicate->push_back(varValue.first);
                vars_in_term->push_back(varValue.first);
            }
        }
    }
    
    return;
}

void filterNonKeyIOEs(input_outputs_t* input_outputs) {
    // find the set of bound variables and values
    set<string> bound_vars;
    set<int> bound_value;
    for (auto ioe : *input_outputs) {
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
    for (auto ioe : *input_outputs) {
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
    auto it = input_outputs->begin();
    while(it != input_outputs->end()) {
        auto ioe = *it;
        vector<int> bound_vec;
        for (int i = 0; i < m; i++) {
            bound_vec.push_back(bound_value_to_index[ioe["b" + to_string(i)]]);
        }
        if (find(non_key_ioes.begin(), non_key_ioes.end(), bound_vec) == non_key_ioes.end()) {
            //it = input_outputs->erase(it);
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
    it = input_outputs->begin();
    while(it != input_outputs->end()) {
        auto ioe = *it;
        vector<int> bound_vec;
        for (int i = 0; i < m; i++) {
            bound_vec.push_back(bound_value_to_index[ioe["b" + to_string(i)]]);
        }
        if (find(non_key_ioes.begin(), non_key_ioes.end(), bound_vec) != non_key_ioes.end()) {
            it = input_outputs->erase(it);
        } else {
            ++it;
        }
    }
    
}

bool readInputOutput(string file_name, input_outputs_t* input_outputs) {
    ifstream ifs;
    ifs.open(file_name, ifstream::in);
    string line;
    
    while (getline(ifs, line)) {
        input_output_t input_output;
        
        stringstream ss(line);
        string var;
        int value;
        while (ss >> var) {
            ss >> value;
            input_output[var] = value;
        }
        
        if (!input_output.empty()) {
            //input_output["_out"] /= 10;
            input_outputs->push_back(input_output);
        }
    }
    
    ifs.close();
    
    //cout << "Resize IOE " << input_outputs->size() << " to ";
    //filterNonKeyIOEs(input_outputs);
    //cout << input_outputs->size() << endl;
    
    return true;
}

void writeSearchedProgram(string file_name, string prog) {
    ofstream ofs;
    size_t pos = file_name.find("/ris_per_iter_refsrc/");
    if (pos != string::npos) {
        pos = file_name.find_last_of("/");
        string conf = file_name.substr(pos+1, file_name.size());
        string header = file_name.substr(0, pos);
        pos = header.find_last_of("/");
        file_name.replace(0, pos, "./synResult/");
        file_name.replace(file_name.size() - 4, file_name.size(), "_src.txt");
        ofs.open(file_name);
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
    string file_name = "";
    int depth_bound_for_predicate = -1;
    vector<string> int_ops_for_predicate;
    vector<string> bool_ops_for_predicate;
    vector<string> vars_in_predicate;
    vector<string> constants_in_predicate;
    int depth_bound_for_term = -1;
    vector<string> int_ops_for_term;
    vector<string> bool_ops_for_term;
    vector<string> vars_in_term;
    vector<string> constants_in_term;
    
    int search_time_for_terms_in_seconds = 20;
    int search_time_for_predicates_in_seconds = 20;
    
    vector<string> rules_to_apply;
    
    string bench_name = "";
    int ref_id = 0;
    
    int num_growing_speed = 1;
    int num_growing_upperbound = 100;
    
    if ( parser(argc, argv,
               &file_name, &search_time_for_terms_in_seconds, &search_time_for_predicates_in_seconds,
               &depth_bound_for_predicate, &int_ops_for_predicate, &bool_ops_for_predicate, &vars_in_predicate, &constants_in_predicate,
               &depth_bound_for_term, &int_ops_for_term, &bool_ops_for_term, &vars_in_term, &constants_in_term,
               &rules_to_apply,
               &bench_name, &ref_id,
               &num_growing_speed, &num_growing_upperbound) == false ) {
        cout << "Error in parsing command lines" << endl;
        return 0;
    }
    
    /*
     read input output files
     */
    input_outputs_t input_outputs;
    if (!readInputOutput(file_name, &input_outputs)) {
        cout << "Error reading files" << endl;
        return 0;
    }
    
    /* sample inputouput Files */
    //sampler s(0.1);
    //input_outputs = s.randomSampling(input_outputs);
    
#ifdef DEBUG
    if (rules_to_apply.empty()) {
        cout << "No mode specific rules specified" << endl;
    }
    else {
        cout << "Applying rules: " << endl;
        for (auto rule : rules_to_apply) {
            cout << rule << " ";
        }
        cout << endl;
    }
#endif
        
    /*
     language configuration
    */
    language_configuration(&depth_bound_for_predicate, &int_ops_for_predicate, &bool_ops_for_predicate, &vars_in_predicate, &constants_in_predicate,
                      &depth_bound_for_term, &int_ops_for_term, &bool_ops_for_term, &vars_in_term, &constants_in_term,
                      input_outputs);
    
    unification* uni = new unification(depth_bound_for_predicate, int_ops_for_predicate, bool_ops_for_predicate, vars_in_predicate, constants_in_predicate,
                                       depth_bound_for_term, int_ops_for_term, bool_ops_for_term, vars_in_term, constants_in_term,
                                       rules_to_apply,
                                       bench_name, ref_id,
                                       num_growing_speed, num_growing_upperbound,
                                       input_outputs);
#ifdef DEBUG
    cout << "Search time: terms " << search_time_for_terms_in_seconds << " predications " << search_time_for_predicates_in_seconds << endl;
    uni->dump_language_defination();
#endif

    uni->search(search_time_for_terms_in_seconds, search_time_for_predicates_in_seconds);

#ifdef DEBUG
    uni->dump_searched_program();
#endif

    //writeSearchedProgram(file_name, uni->getSearchedProgram());
    uni->dump_searched_program();
    
    return 0;
}
