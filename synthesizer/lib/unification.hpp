#ifndef UNIFICATION_H
#define UNIFICATION_H

#include "bottomUpSearch.hpp"
#include "typeDef.hpp"
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>

//#define DEBUG

struct input_output_tree_node {
    input_outputs_t input_outputs;
    string searched_program;
    input_output_tree_node *left;
    input_output_tree_node *right;
    input_output_tree_node() {
        input_outputs = input_outputs_t ();
        left = nullptr;
        right = nullptr;
        searched_program = "";
    }
    input_output_tree_node(input_outputs_t ios) : input_outputs(ios), left(nullptr), right(nullptr), searched_program("") {}
    input_output_tree_node(input_outputs_t ios, input_output_tree_node *left, input_output_tree_node *right) : input_outputs(ios), left(left), right(right), searched_program("") {}
};

class unification {
public:
    unification(int depth_bound_for_predicate,
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
                
                input_outputs_t input_outputs);
    
    string search(int search_time_for_terms_in_seconds, int search_time_for_predicates_in_seconds);
    
    /* Dumping fucntions */
    void dump_language_defination();
    void dump_input_output_tree();
    void dump_searched_program();
    string get_searched_program();
    
private:
    /* Dumping fucntions */
    void dump_input_output_tree_node(input_output_tree_node* node, string space="");
    
    /* Search node */
    string search_node_one_pass(int time_bound_in_seconds, input_output_tree_node* node);
    string search_node(int search_time_for_terms_in_seconds, int search_time_for_predicates_in_seconds, input_output_tree_node* node);
    
    /* Split current tree node of inputoutput examples */
    bool split_input_output_tree_node(input_output_tree_node* node, int split_mode);
    
    /* backtracing, merge the split node */
    void backtracing(input_output_tree_node* node);
    
    /* Cluster the input-output examples to subsets for divde-and-conqure */
    input_output_tree_node* input_output_tree;
    bool _has_zero_in_ioes = false;
    
    /* Language definition for predicates */
    int depth_bound_for_predicate;
    vector<string> int_ops_in_predicate;
    vector<string> bool_ops_in_predicate;
    vector<string> vars_in_predicate;
    vector<string> constants_in_predicate;
    
    /* Language definition for terms */
    int depth_bound_for_term;
    vector<string> int_ops_in_term;
    vector<string> bool_ops_in_term;
    vector<string> vars_in_term;
    vector<string> constants_in_term;
    
    /* Rules to apple */
    vector<string> rules_to_apply;
};


#endif
