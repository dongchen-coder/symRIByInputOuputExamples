#ifndef UNIFICATION_H
#define UNIFICATION_H

#include "bottomUpSearch.hpp"
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

struct inputOutputTreeNode {
    vector<map<string, int> > inputOutputs;
    string searchedProg;
    inputOutputTreeNode *left;
    inputOutputTreeNode *right;
    inputOutputTreeNode() {
        inputOutputs = vector<map<string, int> >();
        left = NULL;
        right = NULL;
        searchedProg = "";
    }
    inputOutputTreeNode(vector<map<string, int> > ios) : inputOutputs(ios), left(nullptr), right(nullptr), searchedProg("") {}
    inputOutputTreeNode(vector<map<string, int> > ios, inputOutputTreeNode *left, inputOutputTreeNode *right) : inputOutputs(ios), left(left), right(right), searchedProg("") {}
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
    
    string search(int timeBoundInSeconds);
    
    /* Dumping fucntions */
    void dumpLangDef();
    void dumpInputOutputTree();
    void dumpSearchedProgram();
    
private:
    /* Dumping fucntions */
    void dumpInputOutputTreeNode(inputOutputTreeNode* node, string space="");
    
    /* Search node */
    string searchNodeOnePass(int timeBoundInSeconds, inputOutputTreeNode* node);
    string searchNode(int timeBoundInSeconds, inputOutputTreeNode* node);
    
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
