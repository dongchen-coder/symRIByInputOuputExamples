#ifndef UNIFICATION_H
#define UNIFICATION_H

#include "bottomUpSearch.hpp"
#include "typeDef.hpp"
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DEBUG

using namespace std;

struct inputOutputTreeNode {
    inputOutputs_t inputOutputs;
    string searchedProg;
    inputOutputTreeNode *left;
    inputOutputTreeNode *right;
    inputOutputTreeNode() {
        inputOutputs = inputOutputs_t ();
        left = NULL;
        right = NULL;
        searchedProg = "";
    }
    inputOutputTreeNode(inputOutputs_t ios) : inputOutputs(ios), left(nullptr), right(nullptr), searchedProg("") {}
    inputOutputTreeNode(inputOutputs_t ios, inputOutputTreeNode *left, inputOutputTreeNode *right) : inputOutputs(ios), left(left), right(right), searchedProg("") {}
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
                
                vector<string> rulesToApply,
                
                inputOutputs_t inputOutputs);
    
    string search(int searchTimeForTermsInSeconds, int searchTimeForPredsInSeconds);
    
    /* Dumping fucntions */
    void dumpLangDef();
    void dumpInputOutputTree();
    void dumpSearchedProgram();
    string getSearchedProgram();
    
private:
    /* Dumping fucntions */
    void dumpInputOutputTreeNode(inputOutputTreeNode* node, string space="");
    
    /* Search node */
    string searchNodeOnePass(int timeBoundInSeconds, inputOutputTreeNode* node);
    string searchNode(int searchTimeForTermsInSeconds, int searchTimeForPredsInSeconds, inputOutputTreeNode* node);
    
    /* Split current tree node of inputoutput examples */
    bool splitInputOutputTreeNode(inputOutputTreeNode* node, int splitMode);
    
    /* backtracing, merge the split node */
    void backtracing(inputOutputTreeNode* node);
    
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
    
    /* Rules to apple */
    vector<string> rulesToApply;
};


#endif
