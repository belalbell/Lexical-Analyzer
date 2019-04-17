cmake_minimum_required(VERSION 3.13)
project(lexical_analyzer)

set(CMAKE_CXX_STANDARD 11)

add_executable(lexical_analyzer main.cpp DFA.cpp DFA.h DFAAndTokens.cpp DFAAndTokens.h MinDFA.cpp MinDFA.h NFARules.cpp NFARules.h NFAToDFA.cpp NFAToDFA.h Node.cpp Node.h NonFiniteAutomata.cpp NonFiniteAutomata.h Symbol_table_builder.cpp Symbol_table_builder.h)