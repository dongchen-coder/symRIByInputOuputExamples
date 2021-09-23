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
    bool _isPred;
    int _num_of_vars;
    
    map<string, int> _vars_orders;
    
    vector<string> _rules_to_apply;
};
#endif
