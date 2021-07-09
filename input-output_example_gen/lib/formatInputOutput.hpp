
struct ri_record {
    // reference ID of source/sink
    uint64_t ref_src;
    uint64_t ref_snk;
    // accessed address
    uint64_t addr;
    // iteration vector of source/sink
    vector<uint64_t> iv_src;
    vector<uint64_t> iv_snk;
    // data position in cache of source/sink
    uint64_t pos_src;
    uint64_t pos_snk;
    // reuse interval
    uint64_t ri;
    // cache line size and data size
    uint64_t cls;
    uint64_t ds;
    // loop bound symbol value
    vector<uint64_t> b;
};

class input_output_gen {
    private:
        vector<ri_record> trace;
        vector<uint64_t> train_sizes;
    public:
        read_trace();
        generate_input_output_examples(string conf);
}

