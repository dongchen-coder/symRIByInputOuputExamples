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
        char readBuffer[1000] = {'\n'};
        read(fd[0], readBuffer, sizeof(readBuffer));
        close(fd[0]);
        
        int acturalSize = 0;
        while(acturalSize < 1000) {
            if (readBuffer[acturalSize] != '\n') {
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
    string searchedProg = searchNodeOnePass(timeBoundInSeconds, node);
    
    /* search a solution for corrent node */
    if (searchedProg == "") {
        if (splitInputOutputTreeNode(node)) {
            cout << "Split current node, succeed" << endl;
            string cond = searchNodeOnePass(timeBoundInSeconds, node);
            if (cond != "") {
                string tcase = searchNode(timeBoundInSeconds, node->left);
                string fcase = searchNode(timeBoundInSeconds, node->right);
                searchedProg = "(if " + cond + " then " + tcase + " else " + fcase + ")";
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
    return searchNode(timeBoundInSeconds, inputOutputTree);
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

/*
Dumping funcions
*/
void unification::dumpInputOutputTree() {
    dumpInputOutputTreeNode(inputOutputTree, "");
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
