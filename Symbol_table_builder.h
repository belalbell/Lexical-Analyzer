//
// Created by mazen on 14/04/19.
//

#ifndef TEST_SYMBOL_TABLE_BUILDER_H
#define TEST_SYMBOL_TABLE_BUILDER_H
#include <bits/stdc++.h>
#include "Node.h"
#include "DFAAndTokens.h"

class Symbol_table_builder {
public:
    DFAAndTokens* dfa;
    std::vector<char> codeFile;

    std::stack<Node*> final_states_nodes;
    std::stack<std::string> final_states_lexeme_value;
    std::stack<int> final_states_lexeme_end_index;

    std::vector<std::string> symbol_table_token_name;
    std::vector<std::string> symbol_table_lexeme_name;

    std::string get_token_value(std::vector<char>* temp_token_value);
    void fill_symbol_table(std::string tokenName, std::string tokenValue);
    void pop_the_final_states_stacks();
    void put_error_message(int token_start_index, int current_index);


    void read_input_code (char* path);
    void build_symbol_table();
    void print_symbol_table();


};


#endif //TEST_SYMBOL_TABLE_BUILDER_H