#include "../lib/bottomUpSearch.hpp"
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
void langConfiguration(int* depthBound,
                       vector<string>* intOps,
                       vector<string>* boolOps,
                       vector<string>* vars,
                       vector<string>* constants,
                       vector<map<string, int> > inputOutputs) {
    
    *depthBound = 4;
    /*
     specify the language u use
     */
    intOps->push_back("VAR");
    intOps->push_back("NUM");
    intOps->push_back("PLUS");
    //intOps.push_back("MINUS");
    //intOps->push_back("TIMES");
    intOps->push_back("ITE");
    
    boolOps->push_back("F");
    boolOps->push_back("AND");
    boolOps->push_back("NOT");
    boolOps->push_back("LT");
    
    //constants->push_back("0");
    //constants->push_back("1");
    //constants->push_back("2");
    //constants->push_back("3");
    //constants->push_back("4");
    constants->push_back("5");
    //constants->push_back("6");
    constants->push_back("-1");
    
    /*
     varables are extracted from inputoutput examples
     */
    if (!inputOutputs.empty()) {
        for (map<string, int>::iterator it = inputOutputs[0].begin(), eit = inputOutputs[0].end(); it != eit; ++it) {
            if (it->first != "_out") {
                vars->push_back(it->first);
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
    int depthBound;
    vector<string> intOps;
    vector<string> boolOps;
    vector<string> vars;
    vector<string> constants;
    langConfiguration(&depthBound, &intOps, &boolOps, &vars, &constants, inputOutputs);
    
    /*
    promise<string> exitSignal;
    future<string> futureObj = exitSignal.get_future();
    thread th(&bottomUp, ref(futureObj), ref(exitSignal),depthBound, intOps, boolOps, vars, constants, inputOutputs);
    this_thread::sleep_for(chrono::seconds(3600));
    exitSignal.set_value("NYI");
    th.join();
     */
    
    bottomUpSearch* bus = new bottomUpSearch(depthBound, intOps, boolOps, vars, constants, inputOutputs);
    
    bus->dumpLangDef();
    
    cout << "Current pList size " << bus->getPlistSize() << ", check correct" << endl;
    while (bus->getCorrect() == "") {
        cout << "Current pList size " << bus->getPlistSize() << ", grow" << endl;
        //bus->dumpPlist();
        bus->grow();
        //bus->dumpPlist();
        cout << "Current pList size " << bus->getPlistSize() << ", eliminate equvalents" << endl;
        bus->elimEquvalents();
        //bus->dumpPlist();
        cout << "Current pList size " << bus->getPlistSize() << ", check correct" << endl;
    }
    
    //cout << "SynProg: " << futureObj.get() << endl;
    
    return 0;
}
