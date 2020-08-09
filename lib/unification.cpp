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
string unification::searchNodeOnePass(int timeBoundInSeconds, string searchMode, inputOutputTreeNode* node) {
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
            bottomUpSearch* bus = new bottomUpSearch(depthBoundPred, intOpsPred, boolOpsPred, varsPred, constantsPred, node->inputOutputs, searchMode);
            searchedProg = bus->search();
        } else {
            bottomUpSearch* bus = new bottomUpSearch(depthBoundTerm, intOpsTerm, boolOpsTerm, varsTerm, constantsTerm, node->inputOutputs, searchMode);
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
#ifdef DEBUG
                // child interrupted by alarm signal
                cout << "Time out for bottem up search" << endl;
#endif
            }else{
#ifdef DEBUG
                // child interrupted by another signal
                cout << "interrupted by another signal in bottem up search" << endl;
#endif
            }
        }else{
#ifdef DEBUG
            // child ran to completion
            cout << "Complete, program found " << searchedProg << endl;
#endif
        }
    }
    
    return searchedProg;
}

string unification::searchNode(int timeBoundInSeconds, string searchMode, inputOutputTreeNode* node) {
    if (node == NULL) {
        return "";
    }
#ifdef DEBUG
    cout << endl << "Start search node " << node << endl;
#endif
 
#ifdef DEBUG
    dumpInputOutputTreeNode(node, "");
#endif
    
    string searchedProg = searchNodeOnePass(timeBoundInSeconds, searchMode, node);
    
    /* search a solution for corrent node */
    if (searchedProg == "") {
#ifdef DEBUG
        cout << "Failed, try to split node: ";
#endif
        for (int mode = 0; mode < 2; mode++) {
            if (splitInputOutputTreeNode(node, mode)) {
#ifdef DEBUG
                cout << "Split current node, succeed" << endl;
                cout << "Start search condition, ";
#endif
                string cond = searchNodeOnePass(timeBoundInSeconds, searchMode, node);
                if (cond != "") {
#ifdef DEBUG
                    cout << "succeed" << endl;
#endif
                    string tcase = searchNode(timeBoundInSeconds, searchMode, node->left);
                    string fcase = searchNode(timeBoundInSeconds, searchMode, node->right);
                    if (tcase == "" || fcase == "") {
#ifdef DEBUG
                        if (tcase == "") {
                            cout << "Search tcase failed" << endl;
                        }
                        if (fcase == "") {
                            cout << "Search fcase failed" << endl;
                        }
#endif
                        searchedProg = "";
                    } else {
                        searchedProg = "(if " + cond + " then " + tcase + " else " + fcase + ")";
                    }
                } else {
#ifdef DEBUG
                    cout << "faild" << endl;
#endif
                }
            } else {
#ifdef DEBUG
                cout << "Split current node, failed" << endl;
#endif
                searchedProg = "";
            }
            if (searchedProg != "") {
                break;
            } else {
                backtracing(node);
            }
        }
    }
    
    node->searchedProg = searchedProg;
    
    return searchedProg;
}

string unification::search(int timeBoundInSeconds, string searchMode) {
#ifdef DEBUG
    cout << "--------------------------------------, search start" << endl;
#endif
    return searchNode(timeBoundInSeconds, searchMode, inputOutputTree);
#ifdef DEBUG
    cout << "--------------------------------------" << endl;
#endif
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
   Split inputoutput example to subsets, different split methods:
    (1) Split half and half
    (2) Split by freqency
*/
bool unification::splitInputOutputTreeNode(inputOutputTreeNode* node, int splitMode) {
    
    vector<int> outputs;
    for (vector<map<string, int> >::iterator it = node->inputOutputs.begin(), eit = node->inputOutputs.end(); it != eit; ++it) {
        outputs.push_back((*it)["_out"]);
    }
    
#ifdef DEBUG
    cout << "Current node size " << outputs.size() << " ";
#endif
    
    if (outputs.size() < 2) {
        return false;
    }
    
    sort(outputs.begin(), outputs.end());
    
    /* half and half split */
    if (splitMode == 0) {
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
#ifdef DEBUG
        cout << "Split to two: left size " << leftInputOutputs.size() << " right size " << rightInputOutputs.size() << endl;
#endif
        node->left = new inputOutputTreeNode(leftInputOutputs);
        node->right = new inputOutputTreeNode(rightInputOutputs);
        return true;
    }
    /* frequent based spliting */
    else if (splitMode == 1) {
        /* find the most frequent appearing output */
        int maxCnt = 0;
        int mostFreqOut = -1;
        int currCnt = 0;
        int prevOut = -7; // some number will never appear in the output
        for (vector<int>::iterator it = outputs.begin(), eit = outputs.end(); it != eit; ++it) {
            if (*it != prevOut) {
                currCnt = 0;
            }
            currCnt++;
            if (currCnt > maxCnt) {
                maxCnt = currCnt;
                mostFreqOut = *it;
            }
            prevOut = *it;
        }
        /* do the split */
        vector<map<string, int> > leftInputOutputs;
        vector<map<string, int> > rightInputOutputs;
        if (maxCnt == 1) {
            leftInputOutputs.push_back(node->inputOutputs.front());
            for (vector<map<string, int> >::iterator it = node->inputOutputs.begin(), eit = node->inputOutputs.end(); it != eit; ++it) {
                if (*it != node->inputOutputs.front()) {
                    rightInputOutputs.push_back(*it);
                }
            }
#ifdef DEBUG
            cout << "Split to two: left size " << leftInputOutputs.size() << " right size " << rightInputOutputs.size() << endl;
#endif
        } else {
            for (vector<map<string, int> >::iterator it = node->inputOutputs.begin(), eit = node->inputOutputs.end(); it != eit; ++it) {
                if ((*it)["_out"] == mostFreqOut) {
                    leftInputOutputs.push_back(*it);
                } else {
                    rightInputOutputs.push_back(*it);
                }
            }
#ifdef DEBUG
            cout << "Split to two: left size " << leftInputOutputs.size() << " right size " << rightInputOutputs.size() << endl;
#endif
        }
        node->left = new inputOutputTreeNode(leftInputOutputs);
        node->right = new inputOutputTreeNode(rightInputOutputs);
        
        return true;
    } else {
        return false;
    }
}

/*
 backtracing, merget split node
 */
void unification::backtracing(inputOutputTreeNode* node) {
    node->inputOutputs.clear();
    for (vector<map<string, int> >::iterator it = node->left->inputOutputs.begin(), eit = node->left->inputOutputs.end(); it != eit; ++it) {
        node->inputOutputs.push_back(*it);
    }
    for (vector<map<string, int> >::iterator it = node->right->inputOutputs.begin(), eit = node->right->inputOutputs.end(); it != eit; ++it) {
        node->inputOutputs.push_back(*it);
    }
    delete(node->left);
    delete(node->right);
    node->left = NULL;
    node->right = NULL;
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
#ifdef DEBUG
    cout << "--------------------------------------, dump search result start" << endl;
#endif
    if (inputOutputTree != NULL) {
        if (inputOutputTree->searchedProg != "") {
            cout << "Searched Program (^0^) : " << inputOutputTree->searchedProg << endl;
        } else {
            cout << "Not yet founded, (T^T)" << endl;
        }
    } else {
        cout << "Not yet founded, (T^T)" << endl;
    }
#ifdef DEBUG
    cout << "--------------------------------------" << endl;
#endif
}
