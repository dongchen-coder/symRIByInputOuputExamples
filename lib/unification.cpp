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
string unification::searchNodeOnePass(int timeBoundInSeconds, inputOutputTreeNode* node) {
    if (node == NULL) {
        return "";
    }
    
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    
    string searchedProg = "";
    
    if (pid == 0) {
        unsigned secsLeft = timeBoundInSeconds;
        alarm(secsLeft); // no handler (terminate proc)
        
        /* do the search */
        if (node->left != NULL && node->right != NULL) {
            bottomUpSearch* bus = new bottomUpSearch(depthBoundPred, intOpsPred, boolOpsPred, varsPred, constantsPred, node->inputOutputs);
            searchedProg = bus->search();
        } else {
            bottomUpSearch* bus = new bottomUpSearch(depthBoundTerm, intOpsTerm, boolOpsTerm, varsTerm, constantsTerm, node->inputOutputs);
            searchedProg = bus->search();
        }
        secsLeft = alarm(0);
        // maybe write (MAX_SECONDS - secsLeft) to a file
        
        /* write searched program to pipe, to parent process */
        close(fd[0]);
        write(fd[1], searchedProg.c_str(), searchedProg.size());
        close(fd[1]);
        
        exit(0);
    } else {
    
        int status;
        wait(&status);
        
        /* read searched program in pipe, to child process */
        close(fd[1]);
        char readBuffer[1000] = {0};
        read(fd[0], readBuffer, sizeof(readBuffer));
        close(fd[0]);
        
        int acturalSize = 0;
        while(acturalSize < 1000) {
            if (readBuffer[acturalSize] != 0) {
                acturalSize++;
            } else {
                break;
            }
        }
        searchedProg.assign(readBuffer, acturalSize);
        
        /* check child process status */
        if (WIFSIGNALED(status)) {
            // child was interrupted
            if (WTERMSIG(status) == SIGALRM) {
                // child interrupted by alarm signal
                cout << "Time out for bottem up search" << endl;
            }else{
                // child interrupted by another signal
                cout << "interrupted by another signal in bottem up search" << endl;
            }
        }else{
            // child ran to completion
            cout << "Complete, program found " << searchedProg << endl;
        }
    }
    
    return searchedProg;
}

string unification::searchNode(int timeBoundInSeconds, inputOutputTreeNode* node) {
    if (node == NULL) {
        return "";
    }
    cout << endl << "Start search node " << node << endl;
    dumpInputOutputTreeNode(node, "");
    
    string searchedProg = searchNodeOnePass(timeBoundInSeconds, node);
    
    /* search a solution for corrent node */
    if (searchedProg == "") {
        if (splitInputOutputTreeNode(node)) {
            cout << "Split current node, succeed" << endl;
            string cond = searchNodeOnePass(timeBoundInSeconds, node);
            if (cond != "") {
                string tcase = searchNode(timeBoundInSeconds, node->left);
                string fcase = searchNode(timeBoundInSeconds, node->right);
                if (tcase == "" || fcase == "") {
                    if (tcase == "") {
                        cout << "Search tcase failed" << endl;
                    }
                    if (fcase == "") {
                        cout << "Search fcase failed" << endl;
                    }
                    searchedProg = "";
                } else {
                    searchedProg = "(if " + cond + " then " + tcase + " else " + fcase + ")";
                }
            }
        } else {
            cout << "Split current node, failed" << endl;
            searchedProg = "";
        }
    }
    
    node->searchedProg = searchedProg;
    
    return searchedProg;
}

string unification::search(int timeBoundInSeconds) {
    cout << "--------------------------------------, search start" << endl;
    return searchNode(timeBoundInSeconds, inputOutputTree);
    cout << "--------------------------------------" << endl;
}

/*
    Dump language definition
 */
void unification::dumpLangDef() {
    cout << "Language used in Unification:" << endl;
    
    cout << "    Predicate language:" << endl;
    cout << "        program depth bound: " << depthBoundPred << endl;
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
    cout << "        program depth bound: " << depthBoundTerm << endl;
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

/*
   Split inputoutput example to subsets
*/
bool unification::splitInputOutputTreeNode(inputOutputTreeNode* node) {
    
    vector<int> outputs;
    for (vector<map<string, int> >::iterator it = node->inputOutputs.begin(), eit = node->inputOutputs.end(); it != eit; ++it) {
        outputs.push_back((*it)["_out"]);
    }
    
    cout << "Current node size " << outputs.size() << " ";
    
    if (outputs.size() < 2) {
        return false;
    }
    
    sort(outputs.begin(), outputs.end());
    
    bool splitFlag = false;
    bool allSameValue = false;
    size_t half_size = outputs.size() / 2;
    
    //cout << "splitFlag " << splitFlag << " half_size " << half_size << endl;
    /* Check if there is -1 in outputs. If there is,
       (1) split -1 into a group and others in the other group
       (2) if all -1, split half and half
     */
    if (outputs.front() == -1) {
        if (outputs.back() == -1) {
            half_size = outputs.size() / 2;
            splitFlag = true;
            allSameValue = true;
        } else {
            half_size = 0;
            while(half_size < outputs.size() && outputs[half_size] == -1) {
                half_size++;
            }
            splitFlag = true;
        }
    }
    
    //cout << "splitFlag " << splitFlag << " half_size " << half_size << endl;
    /* Find split size, split into half size first, try grow first half */
    if (splitFlag == false) {
        half_size = outputs.size() / 2;
        while (half_size >= 1 && half_size < outputs.size() && outputs[half_size - 1] == outputs[half_size]) {
            half_size++;
        }
        if (half_size != 0 && half_size != outputs.size()) {
            splitFlag = true;
        }
    }
    
    //cout << "splitFlag " << splitFlag << " half_size " << half_size << endl;
    /* if grow first half failed, try grow second half */
    if (splitFlag == false) {
        half_size = outputs.size() / 2;
        while (half_size >= 1 && half_size < outputs.size() && outputs[half_size - 1] == outputs[half_size]) {
            half_size--;
        }
        if (half_size != 0 && half_size != outputs.size()) {
            splitFlag = true;
        }
    }
    
    //cout << "splitFlag " << splitFlag << " half_size " << half_size << endl;
    /* all same value but not -1 */
    if (splitFlag == false) {
        half_size = outputs.size() / 2;
        allSameValue = true;
    }
    
    //cout << "splitFlag " << splitFlag << " half_size " << half_size << endl;
    /* found split size, do the split */
    vector<map<string, int> > leftInputOutputs;
    vector<map<string, int> > rightInputOutputs;
    if (allSameValue == true) {
        for (int i = 0; i < half_size; i++) {
            leftInputOutputs.push_back(node->inputOutputs[i]);
        }
        for (int i = half_size; i < node->inputOutputs.size(); i++) {
            rightInputOutputs.push_back(node->inputOutputs[i]);
        }
    } else {
        for (vector<map<string, int> >::iterator it = node->inputOutputs.begin(), eit = node->inputOutputs.end(); it != eit; ++it) {
            if ((*it)["_out"] <= outputs[half_size-1]) {
                leftInputOutputs.push_back(*it);
                (*it)["_out"] = true;
                //cout << "Left " << (*it)["_out"] << endl;
            } else {
                rightInputOutputs.push_back(*it);
                (*it)["_out"] = false;
                //cout << "Right " << (*it)["_out"] << endl;
            }
        }
    }
    
    cout << "Split to two: left size " << leftInputOutputs.size() << " right size " << rightInputOutputs.size() << endl;
    
    node->left = new inputOutputTreeNode(leftInputOutputs);
    node->right = new inputOutputTreeNode(rightInputOutputs);
    
    return true;
}

/*
Dumping funcions
*/
void unification::dumpInputOutputTree() {
    cout << "--------------------------------------, dump tree after search" << endl;
    dumpInputOutputTreeNode(inputOutputTree, "");
    cout << "--------------------------------------" << endl;
}

void unification::dumpInputOutputTreeNode(inputOutputTreeNode* node, string space) {
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
        cout << "Searched Program: " << node->searchedProg << endl;
        dumpInputOutputTreeNode(node->left, space + "L---");
        dumpInputOutputTreeNode(node->right, space + "R---");
    }
}

void unification::dumpSearchedProgram() {
    cout << "--------------------------------------, dump search result start" << endl;
    if (inputOutputTree != NULL) {
        if (inputOutputTree->searchedProg != "") {
            cout << "Searched Program (^0^) : " << inputOutputTree->searchedProg << endl;
        } else {
            cout << "Not yet founded, (T^T)" << endl;
        }
    } else {
        cout << "Not yet founded, (T^T)" << endl;
    }
    cout << "--------------------------------------" << endl;
}
