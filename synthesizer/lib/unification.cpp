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
                         vector<string> rulesToApply,
                         inputOutputs_t inputOutputs) {
    
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
    
    this->rulesToApply = rulesToApply;
    
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
    if (pipe(fd) < 0) throw runtime_error("Open pipe failed");
    
    pid_t pid = fork();
    
    string searchedProg = "";
    
    if (pid == 0) {
        unsigned secsLeft = timeBoundInSeconds;
        alarm(secsLeft); // no handler (terminate proc)
        
        /* do the search */
        if (node->left != NULL && node->right != NULL) {
            bottomUpSearch* bus = new bottomUpSearch(depthBoundPred,
                                                     intOpsPred,
                                                     boolOpsPred,
                                                     varsPred,
                                                     constantsPred,
                                                     true,
                                                     this->rulesToApply,
                                                     node->inputOutputs);
            searchedProg = bus->search();
        } else {
            bottomUpSearch* bus = new bottomUpSearch(depthBoundTerm,
                                                     intOpsTerm,
                                                     boolOpsTerm,
                                                     varsTerm,
                                                     constantsTerm,
                                                     false,
                                                     this->rulesToApply,
                                                     node->inputOutputs);
            searchedProg = bus->search();
        }
        secsLeft = alarm(0);
        // maybe write (MAX_SECONDS - secsLeft) to a file
        
        /* write searched program to pipe, to parent process */
        close(fd[0]);
        if (write(fd[1], searchedProg.c_str(), searchedProg.size()) < 0) throw runtime_error("Wrtie pipe failed");
        close(fd[1]);
        
        exit(0);
    } else {
    
        int status;
        wait(&status);
        
        /* read searched program in pipe, to child process */
        close(fd[1]);
        char readBuffer[1000] = {0};
        if (read(fd[0], readBuffer, sizeof(readBuffer)) < 0) throw runtime_error("Read pipe failed");
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
                cout << "Time out for bottom up search" << endl;
#endif
            }
            else {
#ifdef DEBUG
                // child interrupted by another signal
                cout << "interrupted by another signal in bottom up search" << endl;
#endif
            }
        }
        else {
#ifdef DEBUG
            // child ran to completion
            if (searchedProg == "") {
                cout << "Complete, failed to find program" << endl;
            }
            else {
                cout << "Complete, program found " << searchedProg << endl;
            }
#endif
        }
    }
    
    return searchedProg;
}

string unification::searchNode(int searchTimeForTermsInSeconds,
                               int searchTimeForPredsInSeconds,
                               inputOutputTreeNode* node) {
    if (node == nullptr) return "";
    
#ifdef DEBUG
    cout << endl << "Start search node " << node << endl;
#endif
    
#ifdef DEBUG
    dumpInputOutputTreeNode(node, "");
#endif
    
    string searchedProg = searchNodeOnePass(searchTimeForTermsInSeconds, node);
    
    /* search a solution for corrent node */
    if (searchedProg == "") {
#ifdef DEBUG
        cout << "Failed, try to split node: ";
#endif
        for (int mode = 0; mode < 2; mode++) {
            bool is_split_succeed = splitInputOutputTreeNode(node, mode);
            if (is_split_succeed) {
#ifdef DEBUG
                cout << "Split current node, succeed" << endl;
                cout << "Start search condition, ";
#endif
                string cond = searchNodeOnePass(searchTimeForPredsInSeconds, node);
                if (cond != "") {
#ifdef DEBUG
                    cout << "Find condition " << cond << endl;
#endif
                    string tcase = searchNode(searchTimeForTermsInSeconds, searchTimeForPredsInSeconds, node->left);
                    if (tcase != "") {
                        string fcase = searchNode(searchTimeForTermsInSeconds, searchTimeForPredsInSeconds, node->right);
                        if (fcase != "") {
                            searchedProg = "(if " + cond + " then " + tcase + " else " + fcase + ")";
                        }
                        else {
#ifdef DEBUG
                            cout << "Search fcase failed" << endl;
#endif
                        }
                    }
                    else {
#ifdef DEBUG
                        cout << "Search tcase failed" << endl;
#endif
                    }
                }
                else {
#ifdef DEBUG
                    cout << "faild" << endl;
#endif
                }
            }
            else {
#ifdef DEBUG
                cout << "Split current node, failed" << endl;
#endif
                searchedProg = "";
            }
            if (searchedProg != "") {
                break;
            }
            if (is_split_succeed) {
                backtracing(node);
            }
        }
    }
    
    node->searchedProg = searchedProg;
    
    return searchedProg;
}

string unification::search(int searchTimeForTermsInSeconds, int searchTimeForPredsInSeconds) {
#ifdef DEBUG
    cout << "--------------------------------------, search start" << endl;
#endif
    
    inputOutputs_t leftInputOutputs;
    inputOutputs_t rightInputOutputs;
    
    return searchNode(searchTimeForTermsInSeconds, searchTimeForPredsInSeconds, inputOutputTree);
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
    for (const auto op : intOpsPred) cout << op << " ";
    cout << endl;
    cout << "        boolOps: ";
    for (const auto op : boolOpsPred) cout << op << " ";
    cout << endl;
    cout << "        constants: ";
    for (const auto c : constantsPred) cout << c << " ";
    cout << endl;
    cout << "        vars: ";
    for (const auto v : varsPred) cout << v << " ";
    cout << endl;
    
    cout << "    Term language:" << endl;
    cout << "        program depth bound: " << depthBoundTerm << endl;
    cout << "        intOps: ";
    for (const auto op : intOpsTerm) cout << op << " ";
    cout << endl;
    cout << "        boolOps: ";
    for (const auto op : boolOpsTerm) cout << op << " ";
    cout << endl;
    cout << "        constants: ";
    for (const auto c : constantsTerm) cout << c << " ";
    cout << endl;
    cout << "        vars: ";
    for (const auto v : varsTerm) cout << v << " ";
    cout << endl;
}

/*
   Split inputoutput example to subsets, different split methods:
    (1) Split half and half
    (2) Split by freqency
*/
bool unification::splitInputOutputTreeNode(inputOutputTreeNode* node, int splitMode) {
    
    vector<int> outputs;
    for (auto ioe : node->inputOutputs) {
        outputs.push_back(ioe["_out"]);
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
        if (outputs.front() == 0) {
            if (outputs.back() == 0) {
                half_size = outputs.size() / 2;
                splitFlag = true;
                allSameValue = true;
            } else {
                half_size = 0;
                while(half_size < outputs.size() && outputs[half_size] == 0) {
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
        inputOutputs_t leftInputOutputs;
        inputOutputs_t rightInputOutputs;
        if (allSameValue == true) {
            for (int i = 0; i < half_size; i++) {
                leftInputOutputs.push_back(node->inputOutputs[i]);
            }
            for (int i = half_size; i < node->inputOutputs.size(); i++) {
                rightInputOutputs.push_back(node->inputOutputs[i]);
            }
        } else {
            for (auto &ioe : node->inputOutputs) {
                if (ioe["_out"] <= outputs[half_size-1]) {
                    leftInputOutputs.push_back(ioe);
                    ioe["_out"] = true;
                } else {
                    rightInputOutputs.push_back(ioe);
                    ioe["_out"] = false;
                }
            }
        }
#ifdef DEBUG
        cout << "Split to two: left size " << leftInputOutputs.size() << " right size " << rightInputOutputs.size() << endl;
        cout << "LeftOut: [";
        for (auto ioe : leftInputOutputs) {
            cout << ioe["_out"] << " ";
        }
        cout << "]" << endl;
        cout << "RightOut: [";
        for (auto ioe : rightInputOutputs) {
            cout << ioe["_out"] << " ";
        }
        cout << "]" << endl;
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
        for (auto out : outputs) {
            if (out != prevOut) {
                currCnt = 0;
            }
            currCnt++;
            if (currCnt > maxCnt) {
                maxCnt = currCnt;
                mostFreqOut = out;
            }
            prevOut = out;
        }
        
        /* do the split */
        inputOutputs_t leftInputOutputs;
        inputOutputs_t rightInputOutputs;
        if (maxCnt == 1) {
            leftInputOutputs.push_back(node->inputOutputs.front());
            for (auto ioe : node->inputOutputs) {
                if (ioe != node->inputOutputs.front()) {
                    rightInputOutputs.push_back(ioe);
                }
            }
#ifdef DEBUG
            cout << "Split to two: left size " << leftInputOutputs.size() << " right size " << rightInputOutputs.size() << endl;
#endif
        } else {
            for (auto ioe : node->inputOutputs) {
                if (ioe["_out"] == mostFreqOut) {
                    leftInputOutputs.push_back(ioe);
                } else {
                    rightInputOutputs.push_back(ioe);
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
    
    if (node != nullptr && node->left != nullptr) {
        for (auto ioe : node->left->inputOutputs) {
            node->inputOutputs.push_back(ioe);
        }
        node->left->inputOutputs.clear();
        delete(node->left);
    }
    if (node != nullptr && node->right != nullptr) {
        for (auto ioe : node->right->inputOutputs) {
            node->inputOutputs.push_back(ioe);
        }
        node->right->inputOutputs.clear();
        delete(node->right);
    }
    node->left = nullptr;
    node->right = nullptr;
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
    if (node != nullptr) {
        for (auto ioe : node->inputOutputs) {
            cout << space;
            for (auto varValue : ioe) {
                if (varValue.first != "_out") {
                    cout << varValue.first << " " << varValue.second << " ";
                }
            }
            cout << "_out " << ioe["_out"] << endl;
        }
        
        dumpInputOutputTreeNode(node->left, space + "L---");
        dumpInputOutputTreeNode(node->right, space + "R---");
    }
}

void unification::dumpSearchedProgram() {
#ifdef DEBUG
    cout << "--------------------------------------, dump search result start" << endl;
#endif
    if (inputOutputTree != nullptr && inputOutputTree->searchedProg != "") {
        cout << "Searched Program (^0^) : " << inputOutputTree->searchedProg << endl;
    } else {
        cout << "Not yet found, (T^T)" << endl;
    }
#ifdef DEBUG
    cout << "--------------------------------------" << endl;
#endif
}

string unification::getSearchedProgram() {
    if (inputOutputTree != nullptr && inputOutputTree->searchedProg != "") {
        return "Searched Program (^0^) : " + inputOutputTree->searchedProg;
    }
    return "Not yet founded, (T^T)";
}


