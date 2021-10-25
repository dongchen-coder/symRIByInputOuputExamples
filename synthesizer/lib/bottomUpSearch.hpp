#ifndef BOTTOMUPSEARCH_H
#define BOTTOMUPSEARCH_H

#include "langDef.hpp"
#include "typeDef.hpp"
#include <algorithm>
#include <numeric>
#include <future>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

//#define DEBUG

class bottomUpSearch {
public:
    bottomUpSearch(int depth_bound,
                   vector<string> int_ops,
                   vector<string> bool_ops,
                   vector<string> vars,
                   vector<string> constants,
                   bool isPred,
                   vector<string> rules_to_apply,
                   string bench_name,
                   int ref_id,
                   int num_growing_speed,
                   int num_growing_upperbound,
                   input_outputs_t input_outputs);
    
    /* search function */
    string search();
    
    /* dump language used */
    void dump_language_defination();
    
private:
    /* dump one program */
    inline string dump_program(BaseType* program);
    
    /* Grow program list */
    void grow(int prog_generation);
    //void grow_with_specific_operations(vector<string> opertions);
    
    /* Eliminate equalivlent programs */
    inline BaseType* eliminate_one_program_by_rules(BaseType* program_a, BaseType* program_b);
    void eliminate_equivalents();
    void eliminate_program_by_value();
    
    /* Check whether there is a correct program in program list */
    inline string get_correct(int program_generation);
    
    /* Dumping function */
    void dump_program_list();
    void dump_program_list(vector<BaseType*> program_list);
    
    /* grow expression rules */
    inline bool depth_rule(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation);
    inline bool generation_rule(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation);
    inline bool type_rule(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation);
    inline bool elimination_free_rule(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation);
    inline bool form_bias_rule(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation);
    inline bool code_structure_rule_for_predicate(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation);
    inline bool code_structure_rule_for_term(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation);
    bool is_grow_rule_satisfied(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation);
    
    /* Construct one expression: op i j */
    BaseType* grow_one_expr(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation);
    
    /* Temporal program evaluation result record */
    map<pair<BaseType*, int>, int> _int_program_to_value_record;
    map<pair<BaseType*, int>, int> _bool_program_to_value_record;
    
    /* Evaluate program */
    inline int evaluate_int_program(BaseType* p, int input_output_id);
    inline bool evaluate_bool_program(BaseType* p, int input_output_id);
    
    /* Check whether program pi and pj are equal (based on input output examples) */
    inline bool check_two_programs_equivilent(BaseType* program_a, BaseType* program_b);
    
    /* Check program p is correct or not */
    bool is_correct(BaseType* program);
    
    /* Check whether there is new program generated */
    bool has_new_program(int program_generation);
    
    /* Program list */
    vector<BaseType*> _program_list;
    
    /* Input-output examples */
    input_outputs_t _input_outputs;
    int _max_output = 0;

    /* Language defination */
    int _depth_bound;
    vector<string> _int_ops;
    vector<string> _bool_ops;
    vector<string> _vars;
    vector<string> _constants;
    bool _is_predicate;
    int _num_of_vars;
    
    map<string, int> _vars_orders;
    
    vector<string> _rules_to_apply;
    
    string _bench_name;
    int _ref_id;
    
    int _num_growing_speed;
    int _num_growing_upperbound;
    
    vector<int> _prime_numbers = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
};
#endif
