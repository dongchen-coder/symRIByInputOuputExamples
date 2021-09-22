#include "unification.hpp"
/*
 Constructor
 */
unification::unification(int depth_bound_for_predicate,
                         vector<string> int_ops_in_predicate,
                         vector<string> bool_ops_in_predicate,
                         vector<string> vars_in_predicate,
                         vector<string> constants_in_predicate,
                         int depth_bound_for_term,
                         vector<string> int_ops_in_term,
                         vector<string> bool_ops_in_term,
                         vector<string> vars_in_term,
                         vector<string> constants_in_term,
                         vector<string> rules_to_apply,
                         input_outputs_t input_outputs) {
    
    this->depth_bound_for_predicate = depth_bound_for_predicate;
    this->int_ops_in_predicate = int_ops_in_predicate;
    this->bool_ops_in_predicate = bool_ops_in_predicate;
    this->vars_in_predicate = vars_in_predicate;
    this->constants_in_predicate = constants_in_predicate;
    
    this->depth_bound_for_term = depth_bound_for_term;
    this->int_ops_in_term = int_ops_in_term;
    this->bool_ops_in_term = bool_ops_in_term;
    this->vars_in_term = vars_in_term;
    this->constants_in_term = constants_in_term;
    
    this->rules_to_apply = rules_to_apply;
    
    this->input_output_tree = new input_output_tree_node(input_outputs);
    for (auto ioe : input_outputs) {
        if (ioe["_out"] == 0) {
            this->_has_zero_in_ioes = true;
            break;
        }
    }
}

/*
 search function
 */
string unification::search_node_one_pass(int time_bound_in_seconds, input_output_tree_node* node) {
    if (node == NULL) {
        return "";
    }
    
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    
    string searched_program = "";
    
#ifdef DEBUG
    cerr << "Start child process to run with " << time_bound_in_seconds << " seconds" << endl;
#endif
    
    if (pid == 0) {
        unsigned seconds_left = time_bound_in_seconds;
        alarm(seconds_left); // no handler (terminate proc)
        
        /* do the search */
        if (node->left != NULL && node->right != NULL) {
            bottomUpSearch* bus = new bottomUpSearch(depth_bound_for_predicate,
                                                     int_ops_in_predicate,
                                                     bool_ops_in_predicate,
                                                     vars_in_predicate,
                                                     constants_in_predicate,
                                                     true,
                                                     this->rules_to_apply,
                                                     node->input_outputs);
            searched_program = bus->search();
        } else {
            bottomUpSearch* bus = new bottomUpSearch(depth_bound_for_term,
                                                     int_ops_in_term,
                                                     bool_ops_in_term,
                                                     vars_in_term,
                                                     constants_in_term,
                                                     false,
                                                     this->rules_to_apply,
                                                     node->input_outputs);
            searched_program = bus->search();
        }
        alarm(0);
        // maybe write (MAX_SECONDS - seconds_left) to a file
        
        /* write searched program to pipe, to parent process */
        close(fd[0]);
        write(fd[1], searched_program.c_str(), searched_program.size());
        close(fd[1]);
        
        exit(0);
    } else {
    
        int status;
        wait(&status);
        
        /* read searched program in pipe, to child process */
        close(fd[1]);
        char read_buffer[1000] = {'\0'};
        read(fd[0], read_buffer, sizeof(read_buffer));
        close(fd[0]);
        
        searched_program = read_buffer;
        
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
                cout << "interrupted by another signal in bottom up search: " << status << endl;
#endif
            }
        }
        else {
#ifdef DEBUG
            // child ran to completion
            if (searched_program == "") {
                cout << "Complete, failed to find program" << endl;
            }
            else {
                cout << "Complete, program found " << searched_program << endl;
            }
#endif
        }
    }
    
    return searched_program;
}

string unification::search_node(int search_time_for_terms_in_seconds,
                               int search_time_for_predicates_in_seconds,
                               input_output_tree_node* node) {
    if (node == nullptr) return "";
    
#ifdef DEBUG
    cout << endl << "Start search node " << node << endl;
#endif
    
#ifdef DEBUG
    dump_input_output_tree_node(node, "");
#endif
    
    string searched_program = "";
    if (!_has_zero_in_ioes) searched_program = search_node_one_pass(search_time_for_terms_in_seconds, node);
    _has_zero_in_ioes = false;
    
    /* search a solution for corrent node */
    if (searched_program == "") {
#ifdef DEBUG
        cout << "Failed, try to split node: ";
#endif
        for (int mode = 0; mode < 2; mode++) {
            bool is_split_succeed = split_input_output_tree_node(node, mode);
            if (is_split_succeed) {
#ifdef DEBUG
                cout << "Split current node, succeed" << endl;
                cout << "Start search condition, ";
#endif
                string cond = search_node_one_pass(search_time_for_predicates_in_seconds, node);
                if (cond != "") {
#ifdef DEBUG
                    cout << "Find condition " << cond << endl;
#endif
                    string tcase = search_node(search_time_for_terms_in_seconds, search_time_for_predicates_in_seconds, node->left);
                    if (tcase != "") {
                        string fcase = search_node(search_time_for_terms_in_seconds, search_time_for_predicates_in_seconds, node->right);
                        if (fcase != "") {
                            searched_program = "(if " + cond + " then " + tcase + " else " + fcase + ")";
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
                searched_program = "";
            }
            if (searched_program != "") {
                break;
            }
            if (is_split_succeed) {
                backtracing(node);
            }
        }
    }
    
    node->searched_program = searched_program;
    
    return searched_program;
}

string unification::search(int search_time_for_terms_in_seconds, int search_time_for_predicates_in_seconds) {
#ifdef DEBUG
    cout << "--------------------------------------, search start" << endl;
#endif
    
    input_outputs_t left_input_outputs;
    input_outputs_t rightInputOutputs;
    
    return search_node(search_time_for_terms_in_seconds, search_time_for_predicates_in_seconds, input_output_tree);
#ifdef DEBUG
    cout << "--------------------------------------" << endl;
#endif
}

/*
    Dump language definition
 */
void unification::dump_language_defination() {
    cout << "Language used in Unification:" << endl;
    
    cout << "    Predicate language:" << endl;
    cout << "        program depth bound: " << depth_bound_for_predicate << endl;
    cout << "        intOps: ";
    for (const auto op : int_ops_in_predicate) cout << op << " ";
    cout << endl;
    cout << "        boolOps: ";
    for (const auto op : bool_ops_in_predicate) cout << op << " ";
    cout << endl;
    cout << "        constants: ";
    for (const auto c : constants_in_predicate) cout << c << " ";
    cout << endl;
    cout << "        vars: ";
    for (const auto v : vars_in_predicate) cout << v << " ";
    cout << endl;
    
    cout << "    Term language:" << endl;
    cout << "        program depth bound: " << depth_bound_for_term << endl;
    cout << "        intOps: ";
    for (const auto op : int_ops_in_term) cout << op << " ";
    cout << endl;
    cout << "        boolOps: ";
    for (const auto op : bool_ops_in_term) cout << op << " ";
    cout << endl;
    cout << "        constants: ";
    for (const auto c : constants_in_term) cout << c << " ";
    cout << endl;
    cout << "        vars: ";
    for (const auto v : vars_in_term) cout << v << " ";
    cout << endl;
}

/*
   Split inputoutput example to subsets, different split methods:
    (1) Split half and half
    (2) Split by freqency
*/
bool unification::split_input_output_tree_node(input_output_tree_node* node, int split_mode) {
    
    vector<int> outputs;
    for (auto ioe : node->input_outputs) {
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
    if (split_mode == 0) {
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
        input_outputs_t left_input_outputs;
        input_outputs_t rightInputOutputs;
        if (allSameValue == true) {
            for (int i = 0; i < half_size; i++) {
                left_input_outputs.push_back(node->input_outputs[i]);
            }
            for (int i = half_size; i < node->input_outputs.size(); i++) {
                rightInputOutputs.push_back(node->input_outputs[i]);
            }
        } else {
            for (auto &ioe : node->input_outputs) {
                if (ioe["_out"] <= outputs[half_size-1]) {
                    left_input_outputs.push_back(ioe);
                    ioe["_out"] = true;
                } else {
                    rightInputOutputs.push_back(ioe);
                    ioe["_out"] = false;
                }
            }
        }
#ifdef DEBUG
        cout << "Split to two: left size " << left_input_outputs.size() << " right size " << rightInputOutputs.size() << endl;
        cout << "LeftOut: [";
        for (auto ioe : left_input_outputs) {
            cout << ioe["_out"] << " ";
        }
        cout << "]" << endl;
        cout << "RightOut: [";
        for (auto ioe : rightInputOutputs) {
            cout << ioe["_out"] << " ";
        }
        cout << "]" << endl;
#endif
        node->left = new input_output_tree_node(left_input_outputs);
        node->right = new input_output_tree_node(rightInputOutputs);
        return true;
    }
    /* frequent based spliting */
    else if (split_mode == 1) {
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
        input_outputs_t left;
        input_outputs_t right;
        if (maxCnt == 1) {
            left.push_back(node->input_outputs.front());
            for (auto ioe : node->input_outputs) {
                if (ioe != node->input_outputs.front()) {
                    right.push_back(ioe);
                }
            }
#ifdef DEBUG
            cout << "Split to two: left size " << left.size() << " right size " << right.size() << endl;
#endif
        } else {
            for (auto ioe : node->input_outputs) {
                if (ioe["_out"] == mostFreqOut) {
                    left.push_back(ioe);
                } else {
                    right.push_back(ioe);
                }
            }
#ifdef DEBUG
            cout << "Split to two: left size " << left.size() << " right size " << right.size() << endl;
#endif
        }
        node->left = new input_output_tree_node(left);
        node->right = new input_output_tree_node(right);
        
        return true;
    } else {
        return false;
    }
}

/*
 backtracing, merget split node
 */
void unification::backtracing(input_output_tree_node* node) {
    node->input_outputs.clear();
    
    if (node != nullptr && node->left != nullptr) {
        for (auto ioe : node->left->input_outputs) {
            node->input_outputs.push_back(ioe);
        }
        node->left->input_outputs.clear();
        delete(node->left);
    }
    if (node != nullptr && node->right != nullptr) {
        for (auto ioe : node->right->input_outputs) {
            node->input_outputs.push_back(ioe);
        }
        node->right->input_outputs.clear();
        delete(node->right);
    }
    node->left = nullptr;
    node->right = nullptr;
}

/*
Dumping funcions
*/
void unification::dump_input_output_tree() {
    cout << "--------------------------------------, dump tree after search" << endl;
    dump_input_output_tree_node(input_output_tree, "");
    cout << "--------------------------------------" << endl;
}

void unification::dump_input_output_tree_node(input_output_tree_node* node, string space) {
    if (node != nullptr) {
        for (auto ioe : node->input_outputs) {
            cout << space;
            for (auto var_value : ioe) {
                if (var_value.first != "_out") {
                    cout << var_value.first << " " << var_value.second << " ";
                }
            }
            cout << "_out " << ioe["_out"] << endl;
        }
        
        dump_input_output_tree_node(node->left, space + "L---");
        dump_input_output_tree_node(node->right, space + "R---");
    }
}

void unification::dump_searched_program() {
#ifdef DEBUG
    cout << "--------------------------------------, dump search result start" << endl;
#endif
    if (input_output_tree != nullptr && input_output_tree->searched_program != "") {
        cout << "Searched Program (^0^) : " << input_output_tree->searched_program << endl;
    } else {
        cout << "Not yet found, (T^T)" << endl;
    }
#ifdef DEBUG
    cout << "--------------------------------------" << endl;
#endif
}

string unification::get_searched_program() {
    if (input_output_tree != nullptr && input_output_tree->searched_program != "") {
        return "Searched Program (^0^) : " + input_output_tree->searched_program;
    }
    return "Not yet founded, (T^T)";
}

