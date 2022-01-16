#include "bottomUpSearch.hpp"
/******************************************
    Constructor
 */

// Support definition
#define GET_NUM_OF_OPS(prog, op)            ( prog->get_number_of_ops(op) )
#define GET_NUM_OF_SYMS(prog, sym)          ( prog->get_number_of_vars(sym) )
#define GET_LENGTH(prog)                    ( GET_NUM_OF_SYMS(prog, "ALL") + GET_NUM_OF_OPS(prog, "ALL") )
#define GET_EXP(prog, sym)                  ( prog->get_exponent_of_var(sym))

#define CHECK_NO_SYM(prog, sym)             ( GET_NUM_OF_SYMS(prog, sym) == 0 )
#define HAS_SYM(prog, sym)                  ( GET_NUM_OF_SYMS(prog, sym) > 0 )
#define CHECK_LESS_SYM(program_a, program_b, sym)         ( GET_NUM_OF_SYMS(program_a, sym) < GET_NUM_OF_SYMS(program_b, sym) )
#define CHECK_EQ_SYM(program_a, program_b, sym)           ( GET_NUM_OF_SYMS(program_a, sym) == GET_NUM_OF_SYMS(program_b, sym) )

#define DEPTH_SHOTER(program_a, program_b)                ( program_a->depth() < program_b->depth() )
#define LENGTH_SHOTER(program_a, program_b)               ( GET_LENGTH(program_a) < GET_LENGTH(program_b) )

// NO SYM
#define NO_SYM_1(prog)                      ( CHECK_NO_SYM(program_a, "ALL") )
#define NO_SYM_2(program_a, program_b)                    ( CHECK_NO_SYM(program_a, "ALL") && CHECK_NO_SYM(program_b, "ALL") )

#define GET_LENGTH_SHOTER(program_a, program_b)           ( LENGTH_SHOTER(program_a, program_b) ? program_a : program_b )

// B SYM ONLY
#define B_SYM_ONLY_1(prog)                  ( !NO_SYM_1(prog) && CHECK_NO_SYM(prog, "I") )
#define B_SYM_ONLY_2(program_a, program_b)                ( !NO_SYM_2(program_a, program_b) && CHECK_NO_SYM(program_a, "I") && CHECK_NO_SYM(program_b, "I") )

// I SYM ONLY
#define I_SYM_ONLY_1(prog)                  ( !NO_SYM_1(prog) && CHECK_NO_SYM(prog, "B") )
#define I_SYM_ONLY_2(program_a, program_b)                ( !NO_SYM_2(program_a, program_b) && CHECK_NO_SYM(program_a, "B") && CHECK_NO_SYM(program_b, "B") )

// BOTH SYM
#define BOTH_SYM_1(prog)                    ( !CHECK_NO_SYM(prog, "B") && !CHECK_NO_SYM(prog, "I") )
#define BOTH_SYM_2(program_a, program_b)                  ( BOTH_SYM_1(program_a) && BOTH_SYM_1(program_b) )

// LENGTH RULE
#define GET_LENGTH_SHOTER(program_a, program_b)           ( LENGTH_SHOTER(program_a, program_b) ? program_a : program_b )
#define GET_LESS_SYM(program_a, program_b, sym)           ( CHECK_EQ_SYM(program_a, program_b, sym) ? program_a : program_b )


/* Macros for code structure rules */
// No symbol
#define HAS_NO_SYM(operand, sym) if (operand && operand->get_number_of_vars(sym) != 0) return false;
#define HAS_NO_SYM_BOTH_OPERANDS(sym) HAS_NO_SYM(operand_a, sym) HAS_NO_SYM(operand_b, sym)
#define VAR_EXPONENT_BOUND(operand, sym, bound) if (operand->get_exponent_of_var(sym) > bound) return false;
#define VAR_EXPONENT_BOUND_BOTH_OPERANDS(sym, bound) VAR_EXPONENT_BOUND(operand_a, sym, bound) VAR_EXPONENT_BOUND(operand_a, sym, bound)

bottomUpSearch::bottomUpSearch(int depth_bound,
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
                               input_outputs_t input_outputs) {
    _depth_bound = depth_bound;
    _int_ops = int_ops;
    _bool_ops = bool_ops;
    _constants = constants;
    _input_outputs = input_outputs;
    _is_predicate = isPred;
    
    sort(vars.begin(), vars.end());
    if (isPred) {
        _vars = vars;
    } else {
        for (auto v : vars) {
            if (v.find("b") != string::npos) {
                _vars.push_back(v);
            }
        }
    }
    
    int var_order = 1;
    for(auto var_str : _vars) {
        Var* var = new Var(var_str);
        BaseType* var_base = dynamic_cast<BaseType*>(var);
        if(var_base == nullptr) throw runtime_error("Init Var list error");
        _program_list.push_back(var_base);
        _vars_orders[var_str] = var_order;
        var_order++;
    }
    _num_of_vars = _vars.size();
    
    for (auto num_str : constants) {
        if (stoi(num_str) > num_growing_upperbound) continue;
        Num* num = new Num(stoi(num_str));
        BaseType* num_base = dynamic_cast<BaseType*>(num);
        if (num_base == nullptr) throw runtime_error("Init Num list error");
        num_base->set_generation(1);
        _program_list.push_back(num_base);
    }
    
    for (auto program : _program_list) {
        if (program == nullptr) throw runtime_error("Nullptr in program list");
        program->set_generation(1);
    }
    
    for (auto ioe : input_outputs) {
        if (ioe.find("_out") == ioe.end()) throw runtime_error("No _out entry in IOE");
        _max_output = max(_max_output, ioe["_out"]);
    }
    
    _bench_name = bench_name;
    _ref_id = ref_id;
    
    _num_growing_speed = num_growing_speed;
    _num_growing_upperbound = num_growing_upperbound;
}

/******************************************
    Dump Program list
*/
inline string bottomUpSearch::dump_program(BaseType* program) {
    if (auto var = dynamic_cast<Var*>(program)) {
        return var->to_string();
    }
    else if (auto num = dynamic_cast<Num*>(program)) {
        return num->to_string();
    }
    else if (auto f = dynamic_cast<F*>(program)) {
        return f->to_string();
    }
    else if (auto plus = dynamic_cast<Plus*>(program)) {
        return plus->to_string();
    }
    else if (auto minus = dynamic_cast<Minus*>(program)) {
        return minus->to_string();
    }
    else if (auto times = dynamic_cast<Times*>(program)) {
        return times->to_string();
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(program)) {
        return leftshift->to_string();
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(program)) {
        return rightshift->to_string();
    }
    else if (auto lt = dynamic_cast<Lt*>(program)) {
        return lt->to_string();
    }
    else if (auto a = dynamic_cast<And*>(program)) {
        return a->to_string();
    }
    else if (auto n = dynamic_cast<Not*>(program)) {
        return n->to_string();
    }
    else if (auto ite = dynamic_cast<Ite*>(program)) {
        return ite->to_string();
    }
    else {
        throw runtime_error("bottomUpSearch::dump_program() operates on UNKNOWN type!");
    }
    return "NoExpr";
}

void bottomUpSearch::dump_program_list(vector<BaseType*> program_list) {
    cout << "[";
    for (auto program : program_list) {
        cout << dump_program(program);
        if (program != program_list.back()) cout << ", ";
    }
    cout << "]" << endl;
    return;
}

void bottomUpSearch::dump_program_list() {
    cout << "[";
    for (auto program : _program_list) {
        if (dynamic_cast<Num*>(program)) cout << dump_program(program) << ", ";
    }
    for (auto program : _program_list) {
        if (dynamic_cast<Times*>(program)) cout << dump_program(program) << ",";
    }
    for (auto program : _program_list) {
        if (dynamic_cast<Plus*>(program)) cout << dump_program(program) << ",";
    }
    for (auto program : _program_list) {
        if (dynamic_cast<Lt*>(program)) cout << dump_program(program) << ",";
    }
    cout << "]" << endl;
    return;
}

void bottomUpSearch::dump_language_defination() {
    cout << "Dump language used:" << endl;
    cout << "    int_ops: ";
    for (auto op : _int_ops) cout << op << " ";
    cout << endl;
    cout << "    bool_ops: ";
    for (auto op : _bool_ops) cout << op << " ";
    cout << endl;
    cout << "    constants: ";
    for (auto c : _constants) cout << c << " ";
    cout << endl;
    cout << "    vars: ";
    for (auto v : _vars) cout << v << " ";
    cout << endl;
}

/******************************************
    Specify and check  growing rules
*/

inline bool bottomUpSearch::depth_rule(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation) {
    if (operand_a && operand_a->depth() >= _depth_bound) return false;
    if (operand_b && operand_b->depth() >= _depth_bound) return false;
    if (operand_c && operand_c->depth() >= _depth_bound) return false;
    return true;
}

inline bool bottomUpSearch::generation_rule(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation) {
    int cur_generation = 0;
    if (operand_a != nullptr) cur_generation = max(cur_generation, operand_a->get_generation());
    if (operand_b != nullptr) cur_generation = max(cur_generation, operand_b->get_generation());
    if (operand_c != nullptr) cur_generation = max(cur_generation, operand_c->get_generation());
    
    if (cur_generation + 1 != program_generation) return false;
    return true;
}

inline bool bottomUpSearch::type_rule(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation) {
    if (op == "PLUS" || op == "MINUS" || op == "TIMES" || op == "LT" || op == "LEFTSHIFT" || op == "RIGHTSHIFT") {
        if (!(dynamic_cast<IntType*>(operand_a) && dynamic_cast<IntType*>(operand_b))) {
            return false;
        }
    }
    else if (op == "NOT") {
        if (!dynamic_cast<BoolType*>(operand_a)) {
            return false;
        }
    }
    else if (op == "AND") {
        if (!(dynamic_cast<BoolType*>(operand_a) && dynamic_cast<BoolType*>(operand_b))) {
            return false;
        }
    }
    else if (op == "ITE") {
        if (!(dynamic_cast<BoolType*>(operand_a) && dynamic_cast<IntType*>(operand_b) && dynamic_cast<IntType*>(operand_c))) {
            return false;
        }
    }
    else {
        throw runtime_error("bottomUpSearch::is_grow_rule_satisfied() operates on UNKNOWN type: " + op);
    }
    return true;
}

inline bool bottomUpSearch::elimination_free_rule(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation) {
    // grow NUM only by TIMES
    auto a_num = dynamic_cast<Num*>(operand_a);
    auto b_num = dynamic_cast<Num*>(operand_b);
    if (a_num != nullptr && b_num != nullptr) {
        if (op != "TIMES") return false;
        int a_value = a_num->interpret();
        int b_value = b_num->interpret();
        int c_value = a_value * b_value;
        if (c_value < 2 || a_value < 2 || b_value < 2) return false;
        
        int a_max_prime_factor = 2;
        for (auto prime : _prime_numbers) {
            if (prime <= a_value && prime > a_max_prime_factor && a_value % prime == 0) {
                a_max_prime_factor = prime;
            }
        }
        if (find(_prime_numbers.begin(), _prime_numbers.end(), b_value) == _prime_numbers.end() || a_max_prime_factor > b_value)
            return false;
        return true;
    }
    // no 0/1 TIMES op_b
    if (a_num != nullptr && b_num == nullptr) {
        int a_value = a_num->interpret();
        if (a_value < 2 && op == "TIMES") return false;
        if (a_value == 0 && op == "PLUS") return false;
    }
    // no NUM on the right handside of TIMES and PLUS
    if (b_num != nullptr && (op == "TIMES" || op == "PLUS")) {
        return false;
    }
    
    // form rule (No redunant expression rules)
    if (op == "PLUS" || op == "TIMES") {
        if (operand_a == nullptr || operand_b == nullptr) return false;
        
        bool is_a_num = ( dynamic_cast<Num*>(operand_a) != nullptr );
        bool is_a_var = ( dynamic_cast<Var*>(operand_a) != nullptr );
        bool is_a_plus = ( dynamic_cast<Plus*>(operand_a) != nullptr );
        bool is_a_times = ( dynamic_cast<Times*>(operand_a) != nullptr );
        
        bool is_b_num = ( dynamic_cast<Num*>(operand_b) != nullptr );
        bool is_b_var = ( dynamic_cast<Var*>(operand_b) != nullptr );
        bool is_b_times = ( dynamic_cast<Times*>(operand_b) != nullptr );
        bool is_b_plus = ( dynamic_cast<Plus*>(operand_b) != nullptr );
        
        int num_in_a = operand_a->get_number_of_vars("NUM");
        int num_in_b = operand_b->get_number_of_vars("NUM");
        int plus_in_a = operand_a->get_number_of_ops("PLUS");
        int plus_in_b = operand_b->get_number_of_ops("PLUS");
        
        if (op == "TIMES") {
            if ( !(is_a_var || is_a_num) ) return false;
            if ( !(is_b_var || is_b_times) ) return false;
            if ( is_a_var && _vars_orders.find(operand_a->to_string()) == _vars_orders.end() ) throw runtime_error("Var a not in _vars_orders list");
            if ( is_b_var && _vars_orders.find(operand_b->to_string()) == _vars_orders.end() ) throw runtime_error("Var b not in _vars_orders list");
            if ( is_a_var && is_b_var && _vars_orders[operand_a->to_string()] > _vars_orders[operand_b->to_string()] ) return false;
            if ( auto b_times = dynamic_cast<Times*>(operand_b) ) {
                if (dynamic_cast<Num*>(b_times->get_left())) return false;
                if (is_a_var) {
                    if (_vars_orders[operand_a->to_string()] > _vars_orders[b_times->get_left()->to_string()]) return false;
                }
            }
        }
        
        if (op == "PLUS") {
            if ( !(is_a_num || is_a_var || is_a_times) ) return false;
            if ( !(is_b_var || is_b_times || is_b_plus) ) return false;
            
            if ( (is_a_var || is_a_times) && (is_b_var || is_b_times)) {
                vector<int> a_lex = operand_a->get_lexical_order(_num_of_vars, _vars_orders);
                vector<int> b_lex = operand_b->get_lexical_order(_num_of_vars, _vars_orders);
                if (a_lex == b_lex ||
                    !lexicographical_compare(a_lex.begin(), a_lex.end(),
                                            b_lex.begin(), b_lex.end()))
                    return false;
            }
            
            if ( is_b_plus ) {
                auto b_plus = dynamic_cast<Plus*>(operand_b);
                vector<int> a_lex = operand_a->get_lexical_order(_num_of_vars, _vars_orders);
                vector<int> b_plus_left_lex = b_plus->get_left()->get_lexical_order(_num_of_vars, _vars_orders);
                if(a_lex == b_plus_left_lex ||
                   !lexicographical_compare(a_lex.begin(), a_lex.end(),
                                           b_plus_left_lex.begin(), b_plus_left_lex.end()))
                    return false;
                /*
                cout << operand_a->to_string() << " + " << operand_b->to_string() << " ";
                for (auto elm : a_lex) cout << elm << " ";
                cout << ",";
                for (auto elm : b_plus_left_lex) cout << elm << " ";
                cout << endl;
                 */
            }
        }
    }
    
    if (op == "LT") {
        bool is_a_num = dynamic_cast<Num*>(operand_a) != nullptr;
        bool is_a_var = dynamic_cast<Var*>(operand_a) != nullptr;
        bool is_a_plus = dynamic_cast<Plus*>(operand_a) != nullptr;
        bool is_a_times = dynamic_cast<Times*>(operand_a) != nullptr;
        
        bool is_b_num = dynamic_cast<Num*>(operand_b) != nullptr;
        bool is_b_var = dynamic_cast<Var*>(operand_b) != nullptr;
        bool is_b_times = dynamic_cast<Times*>(operand_b) != nullptr;
        bool is_b_plus = dynamic_cast<Plus*>(operand_b) != nullptr;
        
        // remove expr "Num < Num"
        if (is_a_num && is_b_num) return false;
        // remove expr "Num < Num + *" and "Num + * < Num"
        if (is_a_num && is_b_plus) {
            auto b_plus = dynamic_cast<Plus*>(operand_b);
            if (dynamic_cast<Num*>(b_plus->get_left())) return false;
        }
        if (is_b_num && is_a_plus) {
            auto a_plus = dynamic_cast<Plus*>(operand_a);
            if (dynamic_cast<Num*>(a_plus->get_left())) return false;
        }
        // remove expr "Num < Num x *" if gcd is not 1
        if (is_a_num && is_b_times) {
            auto b_times = dynamic_cast<Times*>(operand_b);
            if (auto b_coefficient = dynamic_cast<Num*>(b_times->get_left())) {
                if (gcd(stoi(operand_a->to_string()), stoi(b_coefficient->to_string())) != 1)
                    return false;
            }
        }
        if (is_b_num && is_a_times) {
            auto a_times = dynamic_cast<Times*>(operand_a);
            if (auto a_coefficient = dynamic_cast<Num*>(a_times->get_left())) {
                if (gcd(stoi(a_coefficient->to_string()), stoi(operand_b->to_string())) != 1) {
                    return false;
                }
            }
        }
        
        // remove "var < var" when var == var
        if (is_a_var && is_b_var && operand_a->to_string() == operand_b->to_string()) return false;
        // remove "var < x ", " x < var", when var is a factor
        if (is_a_var && is_b_times) {
            auto b_times = dynamic_cast<Times*>(operand_b);
            vector<string> b_times_factors = b_times->get_factors();
            if (find(b_times_factors.begin(), b_times_factors.end(), operand_a->to_string()) != b_times_factors.end())
                return false;
        }
        if (is_a_times && is_b_var) {
            auto a_times = dynamic_cast<Times*>(operand_a);
            vector<string> a_times_factors = a_times->get_factors();
            if (find(a_times_factors.begin(), a_times_factors.end(), operand_b->to_string()) != a_times_factors.end()) {
                return false;
            }
        }
        // remove "var < + ", "+ < var", when var is a term
        if (is_a_var && is_b_plus) {
            auto b_plus = dynamic_cast<Plus*>(operand_b);
            vector<string> b_plus_terms = b_plus->getTerms();
            if (find(b_plus_terms.begin(), b_plus_terms.end(), operand_a->to_string()) != b_plus_terms.end()) {
                return false;
            }
        }
        if (is_a_plus && is_b_var) {
            auto a_plus = dynamic_cast<Plus*>(operand_a);
            vector<string> a_plus_terms = a_plus->getTerms();
            if (find(a_plus_terms.begin(), a_plus_terms.end(), operand_b->to_string()) != a_plus_terms.end()) {
                return false;
            }
        }
        
        // remove "times < times ", where share same factor
        if (is_a_times && is_b_times) {
            auto a_times = dynamic_cast<Times*>(operand_a);
            auto b_times = dynamic_cast<Times*>(operand_b);
            vector<string> a_times_factors = a_times->get_factors();
            vector<string> b_times_factors = b_times->get_factors();
            for (auto factor : a_times_factors) {
                if (find(b_times_factors.begin(), b_times_factors.end(), factor) != b_times_factors.end()) {
                    return false;
                }
            }
        }
        // remove " time < + ", "+ < time", where time is a term of +
        if (is_a_times && is_b_plus) {
            auto a_times = dynamic_cast<Times*>(operand_a);
            auto b_plus = dynamic_cast<Plus*>(operand_b);
            vector<string> b_plus_terms = b_plus->getTerms();
            string a_times_str_no_num;
            if (dynamic_cast<Num*>(a_times->get_left())) {
                a_times_str_no_num = a_times->get_right()->to_string();
            } else {
                a_times_str_no_num = a_times->to_string();
            }
            if (find(b_plus_terms.begin(), b_plus_terms.end(), a_times_str_no_num) != b_plus_terms.end()) {
                return false;
            }
        }
        if (is_a_plus && is_b_times) {
            auto a_plus = dynamic_cast<Plus*>(operand_a);
            auto b_times = dynamic_cast<Times*>(operand_b);
            vector<string> a_plus_terms = a_plus->getTerms();
            string b_times_str_no_num;
            if (dynamic_cast<Num*>(b_times->get_left())) {
                b_times_str_no_num = b_times->get_right()->to_string();
            } else {
                b_times_str_no_num = b_times->to_string();
            }
            if (find(a_plus_terms.begin(), a_plus_terms.end(), b_times_str_no_num) != a_plus_terms.end()) {
                return false;
            }
        }
        
        // remove " + < + " with common terms
        if (is_a_plus && is_b_plus) {
            auto a_plus = dynamic_cast<Plus*>(operand_a);
            auto b_plus = dynamic_cast<Plus*>(operand_b);
            if (dynamic_cast<Num*>(a_plus->get_left()) && dynamic_cast<Num*>(b_plus->get_left()))
                return false;
            vector<string> a_plus_terms = a_plus->getTerms();
            vector<string> b_plus_terms = b_plus->getTerms();
            for (auto term : a_plus_terms) {
                if (find(b_plus_terms.begin(), b_plus_terms.end(), term) != b_plus_terms.end()) {
                    return false;
                }
            }
        }
    }
    
    if (op == "AND") {
        // no F in AND
        if (dynamic_cast<F*>(operand_a) || dynamic_cast<F*>(operand_b)) return false;
        // Operand_a has to be LT
        if (!dynamic_cast<Lt*>(operand_a)) return false;
        // Operand_b has to be And/Not/Lt
        if (!(dynamic_cast<And*>(operand_b) ||
              dynamic_cast<Not*>(operand_b) ||
              dynamic_cast<Lt*>(operand_b))) return false;
        // no redundant expr
        vector<int> left_lex = operand_a->get_lexical_order(_num_of_vars, _vars_orders);
        vector<int> right_lex;
        if (auto b_and = dynamic_cast<And*>(operand_b)) {
            right_lex = b_and->get_right()->get_lexical_order(_num_of_vars, _vars_orders);
            if(left_lex == right_lex ||
               !lexicographical_compare(left_lex.begin(), left_lex.end(),
                                        right_lex.begin(), right_lex.end()))
                return false;
            
        } else {
            right_lex = operand_b->get_lexical_order(_num_of_vars, _vars_orders);
            if(left_lex == right_lex ||
               !lexicographical_compare(left_lex.begin(), left_lex.end(),
                                        right_lex.begin(), right_lex.end()))
                return false;
        }
    }
    
    if (op == "NOT") {
        if (!dynamic_cast<And*>(operand_a)) return false;
    }
    
    return true;
}

inline bool bottomUpSearch::form_bias_rule(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation) {
    /* limiting the value range for numbers */
    auto a_num = dynamic_cast<Num*>(operand_a);
    auto b_num = dynamic_cast<Num*>(operand_b);
    if (a_num != nullptr && b_num != nullptr) {
        int c;
        if (op == "TIMES") c = a_num->interpret() * b_num->interpret();
        if (op == "PLUS") c = a_num->interpret() + b_num->interpret();
        if (c > _num_growing_upperbound) return false;
        return true;
    }
    
    /* bias rules for predicates */
    if (_is_predicate) {
        if (op == "LT") {
            // enforce "no b < *"
            if (operand_a && operand_b &&
                operand_a->get_number_of_vars("b") != 0 && operand_b->get_number_of_vars("b") != 0) return false;
            if (operand_a && operand_b &&
                operand_a->get_number_of_vars("b") == 0 && operand_b->get_number_of_vars("b") == 0) return false;
            // enforce "one isrc < *"
            if (operand_a && operand_b &&
                operand_a->get_number_of_vars("isrc") != 0 && operand_b->get_number_of_vars("isrc") != 0) return false;
            if (operand_a && operand_b &&
                operand_a->get_number_of_vars("isrc") == 0 && operand_b->get_number_of_vars("isrc") == 0) return false;
            // enforce "* < no isrc"
            //if (operand_b->get_number_of_vars("isrc") != 0) return false;
            
        }
        if (op == "TIMES") {
            if (!dynamic_cast<Num*>(operand_a) || !dynamic_cast<Var*>(operand_b)) return false;
        }
        if (op == "PLUS") {
            if (!dynamic_cast<Num*>(operand_a)) return false;
            if (dynamic_cast<Plus*>(operand_b)) return false;
            if (dynamic_cast<Times*>(operand_b)) return false;
        }
        
    }
    /* bias rules for terms */
    else {
        if (op == "TIMES") {
            if (operand_a && operand_b &&
                operand_a->get_number_of_vars("VAR") + operand_b->get_number_of_vars("VAR") > 4)
                return false;
        }
        /*
        if (op == "MINUS") {
            if (operand_a->get_number_of_ops("MINUS") != 0) return false;
            if (!dynamic_cast<Num*>(operand_b)) return false;
        }*/
    }
    
    return true;
}

inline bool bottomUpSearch::code_structure_rule_for_predicate(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation) {
    if (!_is_predicate) return true;
    
    if (_bench_name == "2mm") {
        if (_ref_id == 0) {
            HAS_NO_SYM_BOTH_OPERANDS("b2");
            HAS_NO_SYM_BOTH_OPERANDS("b3");
        }
        else if (_ref_id >= 1 && _ref_id <= 4) {
            HAS_NO_SYM_BOTH_OPERANDS("b3");
        }
        else if (_ref_id >= 5 && _ref_id <= 6) {
            HAS_NO_SYM_BOTH_OPERANDS("b1");
            HAS_NO_SYM_BOTH_OPERANDS("b2");
        }
        else if (_ref_id >= 7 && _ref_id <= 10) {
            HAS_NO_SYM_BOTH_OPERANDS("b2");
        }
    }
    else if (_bench_name == "3mm") {
        if (_ref_id == 0) {
            HAS_NO_SYM_BOTH_OPERANDS("b2");
            HAS_NO_SYM_BOTH_OPERANDS("b3");
            HAS_NO_SYM_BOTH_OPERANDS("b4");
        }
        else if (_ref_id >= 1 && _ref_id <= 4) {
            HAS_NO_SYM_BOTH_OPERANDS("b3");
            HAS_NO_SYM_BOTH_OPERANDS("b4");
        }
        else if (_ref_id == 5) {
            HAS_NO_SYM_BOTH_OPERANDS("b0");
            HAS_NO_SYM_BOTH_OPERANDS("b2");
            HAS_NO_SYM_BOTH_OPERANDS("b4");
        }
        else if (_ref_id >= 6 && _ref_id <= 9) {
            HAS_NO_SYM_BOTH_OPERANDS("b0");
            HAS_NO_SYM_BOTH_OPERANDS("b2");
        }
        else if (_ref_id == 10) {
            HAS_NO_SYM_BOTH_OPERANDS("b1");
            HAS_NO_SYM_BOTH_OPERANDS("b2");
            HAS_NO_SYM_BOTH_OPERANDS("b4");
        }
        else if (_ref_id >= 11 && _ref_id <= 14) {
            HAS_NO_SYM_BOTH_OPERANDS("b2");
            HAS_NO_SYM_BOTH_OPERANDS("b4");
        }
    }
    else if (_bench_name == "adi") {
        return true; // all references are relavent to all bound symbols
    }
    else if (_bench_name == "atax") {
        if (_ref_id == 0) {
            HAS_NO_SYM_BOTH_OPERANDS("b0");
        }
        else if (_ref_id == 1) {
            HAS_NO_SYM_BOTH_OPERANDS("b1");
        }
        return true;
    }
    else if (_bench_name == "bicg") {
        if (_ref_id == 0) {
            HAS_NO_SYM_BOTH_OPERANDS("b0");
        }
        else if (_ref_id == 1) {
            HAS_NO_SYM_BOTH_OPERANDS("b1");
        }
        return true;
    }
    else if (_bench_name == "cholesky") {
        return true;
    }
    else if (_bench_name == "convolution_2d") {
        return true;
    }
    else if (_bench_name == "convolution_3d") {
        return true;
    }
    else if (_bench_name == "correlation") {
        if (_ref_id == 0 || (_ref_id >= 4 && _ref_id <= 5) || _ref_id == 6 || (_ref_id >= 13 && _ref_id <= 18) || _ref_id == 25 || _ref_id == 26 || _ref_id == 31 || _ref_id == 32) {
            HAS_NO_SYM_BOTH_OPERANDS("b1");
        }
        return true;
    }
    else if (_bench_name == "covariance") {
        if (_ref_id == 0 || (_ref_id >= 4 && _ref_id <= 5) || _ref_id == 9 || (_ref_id >= 14 && _ref_id <= 15)) {
            HAS_NO_SYM_BOTH_OPERANDS("b1");
        }
        return true;
    }
    else if (_bench_name == "deriche") {
        return true;
    }
    else if (_bench_name == "doitgen") {
        return true;
    }
    else if (_bench_name == "durbin") {
        return true;
    }
    else if (_bench_name == "fdtd_2d") {
        if (_ref_id >= 0 && _ref_id <= 1) {
            HAS_NO_SYM_BOTH_OPERANDS("b1");
        }
        return true;
    }
    else if (_bench_name == "floyd_warshall") {
        return true;
    }
    else if (_bench_name == "gemm") {
        if (_ref_id >= 0 && _ref_id <= 1) {
            HAS_NO_SYM_BOTH_OPERANDS("b2");
        }
        return true;
    }
    else if (_bench_name == "gemver") {
        return true;
    }
    else if (_bench_name == "gesummv") {
        return true;
    }
    else if (_bench_name == "gramschmidt") {
        if (_ref_id == 2 || _ref_id == 6) {
            HAS_NO_SYM_BOTH_OPERANDS("b0");
        }
    }
    else if (_bench_name == "heat_3d") {
        return true;
    }
    else if (_bench_name == "jacobi_1d") {
        return true;
    }
    else if (_bench_name == "jacobi_2d") {
        return true;
    }
    else if (_bench_name == "lu") {
        return true;
    }
    else if (_bench_name == "ludcmp") {
        return true;
    }
    else if (_bench_name == "mvt") {
        return true;
    }
    else if (_bench_name == "nussinov") {
        return true;
    }
    else if (_bench_name == "seidel_2d") {
        return true;
    }
    else if (_bench_name == "symm") {
        return true;
    }
    else if (_bench_name == "syr2d") {
        if (_ref_id == 0 || _ref_id == 1) {
            HAS_NO_SYM_BOTH_OPERANDS("b1");
        }
        return true;
    }
    else if (_bench_name == "syrk") {
        if (_ref_id == 0 || _ref_id == 1) {
            HAS_NO_SYM_BOTH_OPERANDS("b1")
        }
        return true;
    }
    else if (_bench_name == "trisolv") {
        return true;
    }
    else if (_bench_name == "trmm") {
        return true;
    }
    else if (_bench_name == "stencil") {
        return true;
    }
    else if (_bench_name == "stencil_tiled") {
        return true;
    }
    return true;
}

inline bool bottomUpSearch::code_structure_rule_for_term(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation) {
    if (_is_predicate) return true;
    if (dynamic_cast<Num*>(operand_a) && dynamic_cast<Num*>(operand_b)) return true;
    /* code structure rules */
    if (_bench_name == "2mm") {
        if (_ref_id == 0) {
            HAS_NO_SYM_BOTH_OPERANDS("b0");
            VAR_EXPONENT_BOUND(operand_a, "b1", 1);VAR_EXPONENT_BOUND(operand_b, "b1", 1);
            VAR_EXPONENT_BOUND(operand_a, "b2", 1);VAR_EXPONENT_BOUND(operand_b, "b2", 1);
            VAR_EXPONENT_BOUND(operand_a, "b3", 1);VAR_EXPONENT_BOUND(operand_b, "b3", 1);
            if (op == "TIMES" && !(operand_b->to_string() == "b1" ||
                                   operand_b->to_string() == "(b1 * b2)" ||
                                   operand_b->to_string() == "b2" ||
                                   operand_b->to_string() == "(b1 * b3)" ||
                                   operand_b->to_string() == "b3")) return false;
        }
        else if (_ref_id >= 1 && _ref_id <= 4) {
            HAS_NO_SYM_BOTH_OPERANDS("b0");
            VAR_EXPONENT_BOUND(operand_a, "b1", 1);VAR_EXPONENT_BOUND(operand_b, "b1", 1);
            VAR_EXPONENT_BOUND(operand_a, "b2", 1);VAR_EXPONENT_BOUND(operand_b, "b2", 1);
            VAR_EXPONENT_BOUND(operand_a, "b3", 1);VAR_EXPONENT_BOUND(operand_b, "b3", 1);
            if (op == "TIMES" && !(operand_b->to_string() == "b1" ||
                                   operand_b->to_string() == "(b1 * b2)" ||
                                   operand_b->to_string() == "b2" ||
                                   operand_b->to_string() == "(b1 * b3)" ||
                                   operand_b->to_string() == "b3")) return false;
        }
        else if (_ref_id >= 5 && _ref_id <= 6) {
            HAS_NO_SYM_BOTH_OPERANDS("b0");
            HAS_NO_SYM_BOTH_OPERANDS("b2");
            VAR_EXPONENT_BOUND(operand_a, "b1", 1);VAR_EXPONENT_BOUND(operand_b, "b1", 1);
            VAR_EXPONENT_BOUND(operand_a, "b3", 1);VAR_EXPONENT_BOUND(operand_b, "b3", 1);
            if (op == "TIMES" && !(operand_b->to_string() == "b3" ||
                                   operand_b->to_string() == "(b1 * b3)" ||
                                   operand_b->to_string() == "b1")) return false;
        }
        else if (_ref_id >= 7 && _ref_id <= 10) {
            HAS_NO_SYM_BOTH_OPERANDS("b0");
            VAR_EXPONENT_BOUND(operand_a, "b1", 1);VAR_EXPONENT_BOUND(operand_b, "b1", 1);
            HAS_NO_SYM_BOTH_OPERANDS("b2");
            VAR_EXPONENT_BOUND(operand_a, "b3", 1);VAR_EXPONENT_BOUND(operand_b, "b3", 1);
            if (op == "TIMES" && !(operand_b->to_string() == "b3" ||
                                   operand_b->to_string() == "(b1 * b3)" ||
                                   operand_b->to_string() == "b1")) return false;
        }
    }
    else if (_bench_name == "3mm") {
        if (_is_predicate) {
            if (_ref_id == 0) {
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b2", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b3", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b4", 1)
                if (op == "TIMES" && !(operand_b->to_string() == "b1" ||
                                       operand_b->to_string() == "(b1 * b3)" ||
                                       operand_b->to_string() == "b3" ||
                                       operand_b->to_string() == "b2" ||
                                       operand_b->to_string() == "b4" ||
                                       operand_b->to_string() == "(b3 * b4)" ||
                                       operand_b->to_string() == "(b1 * b2)" ||
                                       operand_b->to_string() == "(b1 * (b3 * b4))")) return false;
            }
            else if (_ref_id >= 1 && _ref_id <= 4) {
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b2", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b3", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b4", 1)
                if (op == "TIMES" && !(operand_b->to_string() == "b1" ||
                                       operand_b->to_string() == "(b1 * b3)" ||
                                       operand_b->to_string() == "b3" ||
                                       operand_b->to_string() == "b2" ||
                                       operand_b->to_string() == "b4" ||
                                       operand_b->to_string() == "(b3 * b4)" ||
                                       operand_b->to_string() == "(b1 * (b3 * b4))")) return false;
            }
            else if (_ref_id == 5) {
                HAS_NO_SYM_BOTH_OPERANDS("b0");
                HAS_NO_SYM_BOTH_OPERANDS("b2");
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b3", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b4", 1)
                if (op == "TIMES" && !(operand_b->to_string() == "b1" ||
                                       operand_b->to_string() == "(b1 * b3)" ||
                                       operand_b->to_string() == "b3" ||
                                       operand_b->to_string() == "b4" ||
                                       operand_b->to_string() == "(b3 * b4)")) return false;
            }
            else if (_ref_id >= 6 && _ref_id <= 9) {
                HAS_NO_SYM_BOTH_OPERANDS("b0");
                HAS_NO_SYM_BOTH_OPERANDS("b2");
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b3", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b4", 1)
                if (op == "TIMES" && !(operand_b->to_string() == "b1" ||
                                       operand_b->to_string() == "(b1 * b3)" ||
                                       operand_b->to_string() == "b3" ||
                                       operand_b->to_string() == "b4" ||
                                       operand_b->to_string() == "(b3 * b4)")) return false;
            }
            else if (_ref_id == 10) {
                HAS_NO_SYM_BOTH_OPERANDS("b0");
                HAS_NO_SYM_BOTH_OPERANDS("b2");
                HAS_NO_SYM_BOTH_OPERANDS("b4");
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b3", 1)
                if (op == "TIMES" && !(operand_b->to_string() == "b1" ||
                                       operand_b->to_string() == "(b1 * b3)" ||
                                       operand_b->to_string() == "b3")) return false;
            }
            else if (_ref_id >= 11 && _ref_id <= 14) {
                HAS_NO_SYM_BOTH_OPERANDS("b0");
                HAS_NO_SYM_BOTH_OPERANDS("b2");
                HAS_NO_SYM_BOTH_OPERANDS("b4");
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
                VAR_EXPONENT_BOUND_BOTH_OPERANDS("b3", 1)
                if (op == "TIMES" && !(operand_b->to_string() == "b1" ||
                                       operand_b->to_string() == "(b1 * b3)" ||
                                       operand_b->to_string() == "b3")) return false;
            }
        }
    }
    else if (_bench_name == "adi") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "atax") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "bicg") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "cholesky") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 3)
    }
    else if (_bench_name == "convolution_2d") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "convolution_3d") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b2", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "b2" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "(b1 * b2)" ||
                               operand_b->to_string() == "(b0 * (b1 * b2))" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "correlation") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "(b0 * (b0 * b1))" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "covariance") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "(b0 * (b0 * b1))" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "deriche") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "doitgen") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b2", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "b2" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "(b1 * b2)" ||
                               operand_b->to_string() == "(b0 * (b1 * b2))" ||
                               operand_b->to_string() == "b1")) return false;
        
    }
    else if (_bench_name == "durbin") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)")) return false;
    }
    else if (_bench_name == "fdtd_2d") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b2", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "b2" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "(b1 * b2)" ||
                               operand_b->to_string() == "(b0 * (b1 * b2))" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "floyd_warshall") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 3)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * (b0 * b0))" ||
                               operand_b->to_string() == "(b0 * b0)")) return false;
        
    }
    else if (_bench_name == "gemm") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b2", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "b2" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "(b1 * b2)" ||
                               operand_b->to_string() == "(b0 * (b1 * b2))" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "gemver") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)")) return false;
    }
    else if (_bench_name == "gesummv") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)")) return false;
    }
    else if (_bench_name == "gramschmidt") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 2)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "(b1 * b1)" ||
                               operand_b->to_string() == "(b0 * (b1 * b1))" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "heat_3d") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 3)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "(b0 * (b0 * b1))" ||
                               operand_b->to_string() == "(b0 * (b0 * b0))" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "jacobi_1d") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "jacobi_2d") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "lu") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 3)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * (b0 * b0))" ||
                               operand_b->to_string() == "(b0 * b0)")) return false;
    }
    else if (_bench_name == "ludcmp") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 3)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * (b0 * b0))" ||
                               operand_b->to_string() == "(b0 * b0)")) return false;
    }
    else if (_bench_name == "mvt") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)")) return false;
    }
    else if (_bench_name == "nussinov") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 3)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * (b0 * b0))" ||
                               operand_b->to_string() == "(b0 * b0)")) return false;
    }
    else if (_bench_name == "seidel_2d") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "symm") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 1)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 2)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "(b1 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "syr2d") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "syrk") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "trisolv") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)")) return false;
    }
    else if (_bench_name == "trmm") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 1)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "b1")) return false;
    }
    else if (_bench_name == "stencil") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)")) return false;
    }
    else if (_bench_name == "stencil_tiled") {
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b0", 2)
        VAR_EXPONENT_BOUND_BOTH_OPERANDS("b1", 2)
        if (op == "TIMES" && !(operand_b->to_string() == "b0" ||
                               operand_b->to_string() == "(b0 * b0)" ||
                               operand_b->to_string() == "(b1 * b1)" ||
                               operand_b->to_string() == "(b0 * b1)" ||
                               operand_b->to_string() == "(b0 * (b1 * b1))" ||
                               operand_b->to_string() == "b1")) return false;
    }
    return true;
}

bool bottomUpSearch::is_grow_rule_satisfied(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation) {
    //if (dynamic_cast<Num*>(operand_b) && op == "MINUS")
    //    cout << depth_rule(operand_a, operand_b, operand_c, op, program_generation) << " " << type_rule(operand_a, operand_b, operand_c, op, program_generation) << " " << generation_rule(operand_a, operand_b, operand_c, op, program_generation) << " " << elimination_free_rule(operand_a, operand_b, operand_c, op, program_generation) << " "<< form_bias_rule(operand_a, operand_b, operand_c, op, program_generation) << endl;
    if (depth_rule(operand_a, operand_b, operand_c, op, program_generation) == false) return false;
    if (type_rule(operand_a, operand_b, operand_c, op, program_generation) == false) return false;
    if (generation_rule(operand_a, operand_b, operand_c, op, program_generation) == false) return false;
    if (elimination_free_rule(operand_a, operand_b, operand_c, op, program_generation) == false) return false;
    if (code_structure_rule_for_predicate(operand_a, operand_b, operand_c, op, program_generation) == false) return false;
    if (code_structure_rule_for_term(operand_a, operand_b, operand_c, op, program_generation) == false) return false;
    
    if (form_bias_rule(operand_a, operand_b, operand_c, op, program_generation) == false) return false;
    return true;
}

/******************************************
    Grow program list
*/
inline BaseType* bottomUpSearch::grow_one_expr(BaseType* operand_a, BaseType* operand_b, BaseType* operand_c, string op, int program_generation) {
    // check rules
    if (op == "F" || !is_grow_rule_satisfied(operand_a, operand_b, operand_c, op, program_generation)) {
        return nullptr;
    }
    
    // constant expression, only grow constant expression by times
    if (auto a = dynamic_cast<Num*>(operand_a)) {
        if (auto b = dynamic_cast<Num*>(operand_b)) {
            Num* new_num = new Num(a, b, "TIMES");
            new_num->set_generation(program_generation + _num_growing_speed - 1);
            return  dynamic_cast<BaseType*>(new_num);
        }
    }
    
    if (op == "PLUS") {
        Plus* plus = new Plus(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(plus);
    }
    else if (op == "MINUS") {
        Minus* minus = new Minus(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(minus);
    }
    else if (op == "LEFTSHIFT") {
        Leftshift* leftshift = new Leftshift(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(leftshift);
    }
    else if (op == "RIGHTSHIFT") {
        Rightshift* rightshift = new Rightshift(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(rightshift);
    }
    else if (op == "TIMES") {
        Times* times = new Times(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(times);
    }
    else if (op == "ITE") {
        Ite* ite = new Ite(dynamic_cast<BoolType*>(operand_a), dynamic_cast<IntType*>(operand_b), dynamic_cast<IntType*>(operand_c));
        return dynamic_cast<BaseType*>(ite);
    }
    else if (op == "F") {
        F* f = new F();
        return dynamic_cast<BaseType*>(f);
    }
    else if (op == "NOT") {
        Not* n = new Not(dynamic_cast<BoolType*>(operand_a));
        return dynamic_cast<BaseType*>(n);
    }
    else if (op == "AND") {
        And* a = new And(dynamic_cast<BoolType*>(operand_a), dynamic_cast<BoolType*>(operand_b));
        return dynamic_cast<BaseType*>(a);
    }
    else if (op == "LT") {
        Lt* lt = new Lt(dynamic_cast<IntType*>(operand_a), dynamic_cast<IntType*>(operand_b));
        return dynamic_cast<BaseType*>(lt);
    }
    else {
        throw runtime_error("bottomUpSearch::grow_one_expr() operates on UNKNOWN type!");
    }
    
    return nullptr;
}

void bottomUpSearch::grow(int program_generation) {
    
    int program_list_length = _program_list.size();
    
    for (auto op : _int_ops) {
        if (op == "PLUS" || op == "TIMES" || op == "MINUS" || op == "LEFTSHIFT" || op == "RIGHTSHIFT") {
            int cnt = 0;
            for (int i = 0; i < program_list_length; i++) {
                for (int j = 0; j < program_list_length; j++) {
                    BaseType* new_expr = grow_one_expr(_program_list[i], _program_list[j], nullptr, op, program_generation);
                    if (new_expr != nullptr) _program_list.push_back(new_expr);
                }
            }
        }
        else if (op == "ITE") {
            for (int i = 0; i < program_list_length; i++) {
                for (int j = 0; j < program_list_length; j++) {
                    for (int k = 0; k < program_list_length; k++) {
                        BaseType* new_expr = grow_one_expr(_program_list[i], _program_list[j], _program_list[k], op, program_generation);
                        if (new_expr != nullptr) _program_list.push_back(new_expr);
                    }
                }
            }
        }
        else {
            if (op != "VAR" && op != "NUM") throw runtime_error("bottomUpSearch::grow(): UNKNOWN int op: " + op);
        }
    }
    
    for (auto op : _bool_ops) {
        
        if (op == "F") {
            BaseType* new_expr = grow_one_expr(nullptr, nullptr, nullptr, op, program_generation);
            if (new_expr != nullptr)
                _program_list.push_back(new_expr);
        }
        else if (op == "NOT") {
            for (int i = 0; i < program_list_length; i++) {
                BaseType* new_expr = grow_one_expr(_program_list[i], nullptr, nullptr, op, program_generation);
                if (new_expr != nullptr)
                    _program_list.push_back(new_expr);
            }
        }
        else if (op == "AND" || op == "LT") {
            for (int i = 0; i < program_list_length; i++) {
                for (int j = 0; j < program_list_length; j++) {
                    BaseType* new_expr = grow_one_expr(_program_list[i], _program_list[j], nullptr, op, program_generation);
                    if (new_expr != nullptr)
                        _program_list.push_back(new_expr);
                }
            }
        }
        else {
            throw runtime_error("bottomUpSearch::grow(): UNKNOWN bool op");
        }
            
    }
    
    for (int i = program_list_length; i < _program_list.size(); i++) {
        if (_program_list[i] && !dynamic_cast<Num*>(_program_list[i]))
            _program_list[i]->set_generation(program_generation);
    }
    
    return;
}

/******************************************
    Eliminate equvalent programs
*/
inline int bottomUpSearch::evaluate_int_program(BaseType* p, int input_output_id) {
    
    if (_int_program_to_value_record.find(make_pair(p, input_output_id)) != _int_program_to_value_record.end()) {
        return _int_program_to_value_record[make_pair(p, input_output_id)];
    }
    
    int pValue;
    if (auto num = dynamic_cast<Num*>(p)) {
        pValue = num->interpret();
    }
    else if (auto var = dynamic_cast<Var*>(p)) {
        pValue = var->interpret(_input_outputs[input_output_id]);
    }
    else if (auto plus = dynamic_cast<Plus*>(p)) {
        pValue = plus->interpret(_input_outputs[input_output_id]);
    }
    else if (auto times = dynamic_cast<Times*>(p)) {
        pValue = times->interpret(_input_outputs[input_output_id]);
    }
    else if (auto minus = dynamic_cast<Minus*>(p)) {
        pValue = minus->interpret(_input_outputs[input_output_id]);
    }
    else if (auto leftshift = dynamic_cast<Leftshift*>(p)) {
        pValue = leftshift->interpret(_input_outputs[input_output_id]);
    }
    else if (auto rightshift = dynamic_cast<Rightshift*>(p)) {
        pValue = rightshift->interpret(_input_outputs[input_output_id]);
    }
    else if (auto ite = dynamic_cast<Ite*>(p)) {
        pValue = ite->interpret(_input_outputs[input_output_id]);
    }
    else {
        throw runtime_error("bottomUpSearch::evaluate_int_program() operates on UNKNOWN type!");
    }
    
    _int_program_to_value_record[make_pair(p, input_output_id)] = pValue;
    return pValue;
}

inline bool bottomUpSearch::evaluate_bool_program(BaseType* p, int input_output_id) {
    if (_bool_program_to_value_record.find(make_pair(p, input_output_id)) != _bool_program_to_value_record.end()) {
        return _bool_program_to_value_record[make_pair(p, input_output_id)];
    }
    
    bool pValue;
    if (auto f = dynamic_cast<F*>(p)) {
        pValue = f->interpret();
    }
    else if (auto n = dynamic_cast<Not*>(p)) {
        pValue = n->interpret(_input_outputs[input_output_id]);
    }
    else if (auto a = dynamic_cast<And*>(p)) {
        pValue = a->interpret(_input_outputs[input_output_id]);
    }
    else if (auto lt = dynamic_cast<Lt*>(p)) {
        pValue = lt->interpret(_input_outputs[input_output_id]);
    }
    else {
        throw runtime_error("bottomUpSearch::evaluate_bool_program() operates on UNKNOWN type!");
    }
    
    _bool_program_to_value_record[make_pair(p, input_output_id)] = pValue;
    return pValue;
}

inline bool bottomUpSearch::check_two_programs_equivilent(BaseType* program_a, BaseType* program_b) {
    if (dynamic_cast<IntType*>(program_a) && dynamic_cast<IntType*>(program_b)) {
        for (int i = 0; i < _input_outputs.size(); i++) {
            if (evaluate_int_program(program_a, i) != evaluate_int_program(program_b, i)) {
                return false;
            }
        }
        return true;
    }
    else if (dynamic_cast<BoolType*>(program_a) && dynamic_cast<BoolType*>(program_b)) {
        for (int i = 0; i < _input_outputs.size(); i++) {
            if (evaluate_bool_program(program_a, i) != evaluate_bool_program(program_b, i)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

inline BaseType* bottomUpSearch::eliminate_one_program_by_rules(BaseType* program_a, BaseType* program_b) {
    
    if (program_a == nullptr) {
        return program_b;
    }
    if (program_b == nullptr) {
        return program_a;
    }
    
    BaseType* progToKeep = program_a;
        
    // Apply common rules
    if (NO_SYM_2(program_a, program_b) ) {
        progToKeep = GET_LENGTH_SHOTER(program_a, program_b);
    }
    
    // Apply different rules for predicts and terms
    if (_is_predicate) {
        if (HAS_SYM(program_a, "B") > 0 && HAS_SYM(program_b, "B") > 0) {
            if (HAS_SYM(program_a, "Isrc") > 0 && HAS_SYM(program_b, "Isrc") > 0) {
                if (HAS_SYM(program_a, "Isnk") > 0 && HAS_SYM(program_b, "Isnk") > 0) {
                    progToKeep = GET_LESS_SYM(program_a, program_b, "ALL");
                } else {
                    if (HAS_SYM(program_a, "Isnk") > 0) {
                        progToKeep = program_b;
                    } else if (HAS_SYM(program_b, "Isnk") > 0) {
                        progToKeep = program_a;
                    } else {
                        if (GET_EXP(program_a, "Isrc") < GET_EXP(program_b, "Isrc")) {
                            progToKeep = program_a;
                        } else if (GET_EXP(program_a, "Isrc") > GET_EXP(program_b, "Isrc")) {
                            progToKeep = program_b;
                        } else {
                            if (GET_EXP(program_a, "B") < GET_EXP(program_b, "B")) {
                                progToKeep = program_a;
                            } else if (GET_EXP(program_a, "B") > GET_EXP(program_b, "B")) {
                                progToKeep = program_b;
                            } else {
                                progToKeep = GET_LESS_SYM(program_a, program_b, "ALL");
                            }
                        }
                    }
                }
            } else {
                if (HAS_SYM(program_a, "Isrc") > 0) {
                    progToKeep = program_a;
                } else if (HAS_SYM(program_b, "Isrc") > 0) {
                    progToKeep = program_b;
                } else {
                    if (GET_NUM_OF_SYMS(program_a, "B") < GET_NUM_OF_SYMS(program_b, "B")) {
                        progToKeep = program_a;
                    } else if (GET_NUM_OF_SYMS(program_a, "B") > GET_NUM_OF_SYMS(program_b, "B")) {
                        progToKeep = program_b;
                    } else {
                        progToKeep = GET_LENGTH_SHOTER(program_a, program_b);
                    }
                }
            }
        } else {
            if (HAS_SYM(program_a, "B") > 0) {
                progToKeep = program_a;
            } else if (HAS_SYM(program_b, "B") > 0) {
                progToKeep = program_b;
            } else {
                progToKeep = GET_LENGTH_SHOTER(program_a, program_b);
            }
        }
    } else {
        
        if (HAS_SYM(program_a, "B") > 0 && HAS_SYM(program_b, "B") > 0) {
            if (HAS_SYM(program_a, "Isrc") > 0 && HAS_SYM(program_b, "Isrc") > 0) {
                if (HAS_SYM(program_a, "Isnk") > 0 && HAS_SYM(program_b, "Isnk") > 0) {
                    progToKeep = GET_LESS_SYM(program_a, program_b, "ALL");;
                } else {
                    if (HAS_SYM(program_a, "Isnk") > 0) {
                        progToKeep = program_a;
                    } else if (HAS_SYM(program_b, "Isnk") > 0) {
                        progToKeep = program_b;
                    } else {
                        progToKeep = GET_LESS_SYM(program_a, program_b, "ALL");
                    }
                }
            } else {
                if (HAS_SYM(program_a, "Isrc") > 0) {
                    progToKeep = program_b;
                } else if (HAS_SYM(program_b, "Isrc") > 0) {
                    progToKeep = program_a;
                } else {
                    progToKeep = GET_LESS_SYM(program_a, program_b, "ALL");
                }
            }
        } else {
            if (HAS_SYM(program_a, "B") > 0) {
                progToKeep = program_a;
            } else if (HAS_SYM(program_b, "B") > 0) {
                progToKeep = program_b;
            } else {
                progToKeep = GET_LENGTH_SHOTER(program_a, program_b);
            }
        }
        
    }
    
    if (progToKeep == program_a) {
        for (int input_output_id = 0; input_output_id < _input_outputs.size(); input_output_id++) {
            _bool_program_to_value_record.erase(make_pair(program_b, input_output_id));
            _int_program_to_value_record.erase(make_pair(program_b, input_output_id));
        }
    } else {
        for (int input_output_id = 0; input_output_id < _input_outputs.size(); input_output_id++) {
            _bool_program_to_value_record.erase(make_pair(program_a, input_output_id));
            _int_program_to_value_record.erase(make_pair(program_a, input_output_id));
        }
    }
    
    return progToKeep;
}

void bottomUpSearch::eliminate_equivalents() {
    vector<BaseType*> programs_to_keep_list;
    vector<bool> eqFlag(_program_list.size() ,false);
    
    for (int i = 0; i < _program_list.size(); i++) {
        if (eqFlag[i] == true) {
            continue;
        }
        BaseType* program_a = _program_list[i];
        
        /* reserve all variables */
        if (dynamic_cast<Var*>(program_a)) {
            programs_to_keep_list.push_back(program_a);
            continue;
        }
        
        /* Find all programs that equal */
        vector<BaseType*> eqPList;
        eqPList.push_back(program_a);
        for (int j = i+1; j < _program_list.size(); j++) {
            BaseType* program_b = _program_list[j];
            
            if (check_two_programs_equivilent(program_a, program_b)) {
                eqFlag[j] = true;
                eqPList.push_back(program_b);
            }
        }
        
        /* Find the program to keep */
        BaseType* progToKeep = nullptr;
        for (auto prog : eqPList) {
            //if (eqPList.size() > 1) cout << prog->to_string() << " ";
            progToKeep = eliminate_one_program_by_rules(progToKeep, prog);
        }
        //if (eqPList.size() > 1) cout << endl;
        
        for (int input_output_id = 0; input_output_id < _input_outputs.size(); input_output_id++) {
            _bool_program_to_value_record.erase(make_pair(program_a, input_output_id));
            _int_program_to_value_record.erase(make_pair(program_a, input_output_id));
        }
        
        /* random choose program to keep */
        //srand((unsigned)time(nullptr));
        //programToKeep.push_back(eqPList[rand() % eqPList.size()]);
        /* always keep the first program, which is short in depth */
        programs_to_keep_list.push_back(progToKeep);
    }
    
    _bool_program_to_value_record.clear();
    _int_program_to_value_record.clear();
    _program_list = programs_to_keep_list;
    return;
}

void bottomUpSearch::eliminate_program_by_value() {
    int number_of_programs = _program_list.size();
    vector<bool> keep_flag(number_of_programs, true);
    
    for (int i = 0; i < number_of_programs; i++) {
        BaseType* program = _program_list[i];
        if (auto int_program = dynamic_cast<IntType*>(program)) {
            for (auto ioe : _input_outputs) {
                int program_value = int_program->interpret(ioe);
                if (program_value > ioe["_out"] && ioe["_out"] != 0) {
                    keep_flag[i] = false;
                    break;
                }
            }
        }
    }
    
    vector<BaseType*> programs_to_keep;
    for (int i = 0; i < number_of_programs; i++) {
        if (keep_flag[i]) {
            programs_to_keep.push_back(_program_list[i]);
        }
    }
    _program_list = programs_to_keep;
    return;
}

/******************************************
    Check correct
 */
bool bottomUpSearch::is_correct(BaseType* program) {
    if (_is_predicate) {
        if (auto bool_program = dynamic_cast<BoolType*>(program)) {
                /* all true or all false are both correct program */
                bool all_false = true;
                bool all_true = true;
                
                for (int i = 0; i < _input_outputs.size(); i++) {
                    
                    if (!(_input_outputs[i]["_out"] == 0 || _input_outputs[i]["_out"] == 1)) {
                        return false;
                    }
                    
                    if (evaluate_bool_program(program, i) != _input_outputs[i]["_out"]) {
                        all_true = false;
                    } else {
                        all_false = false;
                    }

                    if (!all_true && !all_false) {
                        return false;
                    }
                }
                if (all_false == true) {
                    program = new Not(bool_program);
                }
            }
        else {
            return false;
        }
    }
    else {
        if (dynamic_cast<IntType*>(program)) {
            for (int i = 0; i < _input_outputs.size(); i++) {
                if (evaluate_int_program(program, i) != _input_outputs[i]["_out"]) {
                    return false;
                }
            }
        }
        else {
            return false;
        }
    }
    
    return true;
}

inline string bottomUpSearch::get_correct(int program_generation) {
    for (auto program : _program_list) {
        if (program->get_generation() == program_generation && is_correct(program)) {
#ifdef DEBUG
            cout << "SynProg: " << dump_program(program) << endl;
#endif
            return dump_program(program);
        }
    }
    return "";
}

bool bottomUpSearch::has_new_program(int program_generation) {
    for (auto program : _program_list) {
        if (program->get_generation() == program_generation)
            return true;
    }
    return false;
}

string bottomUpSearch::search() {

#ifdef DEBUG
    cout << "Init program_list size " << _program_list.size() << ", check correct" << endl;
#endif
    
    //eliminate_equivalents();
    //dump_program_list();
    
    int program_generation = 1;
    while (get_correct(program_generation) == "") {
#ifdef DEBUG
        cout << "Current generation " << program_generation << endl;
        cout << "Current program_list size " << _program_list.size() << ", grow" << endl;
#endif
        //dump_program_list();
        program_generation++;
        grow(program_generation);
        //dump_program_list();
#ifdef DEBUG
        cout << "Current program_list size " << _program_list.size() << ", eliminate equvalents" << endl;
#endif
        
        if (!_is_predicate) eliminate_program_by_value();
        if (_is_predicate) eliminate_equivalents();
        
        if (!has_new_program(program_generation)) {
            break;
        }
        
        //if (!_is_predicate) dump_program_list();
#ifdef DEBUG
        cout << "Current program_list size " << _program_list.size() << ", check correct" << endl;
#endif
    }
    
    return get_correct(program_generation);
}
