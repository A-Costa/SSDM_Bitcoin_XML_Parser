typedef struct output_s{
    char address[64];
    //size_t address_length;
}output;

typedef struct tx_outputs_s{
    char hash[64];
    unsigned long long outs_length;
    output *outs;
    struct tx_outputs_s *next;
}tx_outputs;
