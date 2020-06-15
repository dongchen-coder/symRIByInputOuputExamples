#include "unification.hpp"
/*
 Constructor
 */
unification::unification(int depthBoundPred,
                         vector<string> intOpsPred,
                         vector<string> boolOpsPred,
                         vector<string> varsPred,
                         vector<string> constantsPred,
                         int depthBoundTerm,
                         vector<string> intOpsTerm,
                         vector<string> boolOpsTerm,
                         vector<string> varsTerm,
                         vector<string> constantsTerm,
                         vector<map<string, int> > inputOutputs) {
    
    this->depthBoundPred = depthBoundPred;
    this->intOpsPred = intOpsPred;
    this->boolOpsPred = boolOpsPred;
    this->varsPred = varsPred;
    this->constantsPred = constantsPred;
    
    this->depthBoundTerm = depthBoundTerm;
    this->intOpsTerm = intOpsTerm;
    this->boolOpsTerm = boolOpsTerm;
    this->varsTerm = varsTerm;
    this->constantsTerm = constantsTerm;
    
    this->inputOutputTree = new inputOutputTreeNode(inputOutputs);
}

/*
 search function
 */
string unification::search() {
    
    //dumpInputOutputTree(inputOutputTree);
    //splitInputOutputTreeNode(inputOutputTree);
    //dumpInputOutputTree(inputOutputTree);
    
    bottomUpSearch* bus = new bottomUpSearch(depthBoundTerm, intOpsTerm, boolOpsTerm, varsTerm, constantsTerm, inputOutputTree->inputOutputs);
    
    while(true) {
        bus->search();
    }
    
    return "";
}

/*
    Dump language definition
 */
void unification::dumpLangDef() {
    cout << "Language used in Unification:" << endl;
    
    cout << "    Predicate language:" << endl;
    cout << "        intOps: ";
    for (vector<string>::iterator it = intOpsPred.begin(), eit = intOpsPred.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
    cout << "        boolOps: ";
    for (vector<string>::iterator it = boolOpsPred.begin(), eit = boolOpsPred.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
    cout << "        constants: ";
    for (vector<string>::iterator it = constantsPred.begin(), eit = constantsPred.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
    cout << "        vars: ";
    for (vector<string>::iterator it = varsPred.begin(), eit = varsPred.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
    
    cout << "    Term language:" << endl;
    cout << "        intOps: ";
    for (vector<string>::iterator it = intOpsTerm.begin(), eit = intOpsTerm.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
    cout << "        boolOps: ";
    for (vector<string>::iterator it = boolOpsTerm.begin(), eit = boolOpsTerm.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
    cout << "        constants: ";
    for (vector<string>::iterator it = constantsTerm.begin(), eit = constantsTerm.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
    cout << "        vars: ";
    for (vector<string>::iterator it = varsTerm.begin(), eit = varsTerm.end(); it != eit; ++it) cout << *it << " ";
    cout << endl;
}

bool unification::splitInputOutputTreeNode(inputOutputTreeNode* node) {
    
    vector<int> outputs;
    for (vector<map<string, int> >::iterator it = node->inputOutputs.begin(), eit = node->inputOutputs.end(); it != eit; ++it) {
        outputs.push_back((*it)["_out"]);
    }
    
    sort(outputs.begin(), outputs.end());
    
    /* split into half size first,  */
    size_t half_size = outputs.size() / 2;
    
    while (half_size > 1 && half_size < outputs.size() && outputs[half_size - 1] == outputs[half_size]) {
        half_size++;
    }
    if (half_size == 0 || half_size == outputs.size()) {
        return false;
    }
    
    vector<map<string, int> > leftInputOutputs;
    vector<map<string, int> > rightInputOutputs;
    
    for (vector<map<string, int> >::iterator it = node->inputOutputs.begin(), eit = node->inputOutputs.end(); it != eit; ++it) {
        if ((*it)["_out"] <= outputs[half_size-1]) {
            leftInputOutputs.push_back(*it);
            (*it)["_out"] = true;
        } else {
            rightInputOutputs.push_back(*it);
            (*it)["_out"] = false;
        }
    }
    
    node->left = new inputOutputTreeNode(leftInputOutputs);
    node->right = new inputOutputTreeNode(rightInputOutputs);
    
    return true;
}

void unification::dumpInputOutputTree(inputOutputTreeNode* node, string space) {
    if (node != NULL) {
        for (vector<map<string, int> >::iterator it = node->inputOutputs.begin(), eit = node->inputOutputs.end(); it != eit; ++it) {
            cout << space;
            for (map<string, int>::iterator vit = (*it).begin(), evit = (*it).end(); vit != evit; ++vit) {
                if (vit->first != "_out") {
                    cout << vit->first << " " << vit->second << " ";
                }
            }
            cout << "_out " << (*it)["_out"] << endl;
        }
        dumpInputOutputTree(node->left, space + "L---");
        dumpInputOutputTree(node->right, space + "R---");
    }
    return;
}
