#ifndef UNIFICATION_H
#define UNIFICATION_H

#include "bottomUpSearch.hpp"
#include <algorithm>
#include <vector>
using namespace std;

struct inputOutputTreeNode {
    vector<map<string, int> > inputOutputs;
    inputOutputTreeNode *left;
    inputOutputTreeNode *right;
    inputOutputTreeNode() {
        inputOutputs = vector<map<string, int> >();
        left = NULL;
        right = NULL;
    }
    inputOutputTreeNode(vector<map<string, int> > ios) : inputOutputs(ios), left(nullptr), right(nullptr) {}
    inputOutputTreeNode(vector<map<string, int> > ios, inputOutputTreeNode *left, inputOutputTreeNode *right) : inputOutputs(ios), left(left), right(right) {}
};

class unification {
public:
    unification(int depthBoundPred,
                vector<string> intOpsPred,
                vector<string> boolOpsPred,
                vector<string> varsPred,
                vector<string> constantsPred,
                int depthBoundTerm,
                vector<string> intOpsTerm,
                vector<string> boolOpsTerm,
                vector<string> varsTerm,
                vector<string> constantsTerm,
                vector<map<string, int> > inputOutputs);
    
    string search();
    
    /* Dumping fucntions */
    void dumpLangDef();
    
private:
    /* Dumping fucntions */
    void dumpInputOutputTree(inputOutputTreeNode* node, string space="");
    
    /* Split current tree node of inputoutput examples */
    bool splitInputOutputTreeNode(inputOutputTreeNode* node);
    
    /* Cluster the input-output examples to subsets for divde-and-conqure */
    inputOutputTreeNode* inputOutputTree;
    
    /* Language definition for predicates */
    int depthBoundPred;
    vector<string> intOpsPred;
    vector<string> boolOpsPred;
    vector<string> varsPred;
    vector<string> constantsPred;
    
    /* Language definition for terms */
    int depthBoundTerm;
    vector<string> intOpsTerm;
    vector<string> boolOpsTerm;
    vector<string> varsTerm;
    vector<string> constantsTerm;
};


#endif
