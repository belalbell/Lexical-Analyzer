#include <iostream>
#include "NonFiniteAutomata.h"
#include "DFAAndTokens.h"
#include "MinDFA.h"
#include "Symbol_table_builder.h"

int main() {
    NonFiniteAutomata *nonFiniteAutomata = NonFiniteAutomata::getInstance();
    nonFiniteAutomata->readREFile("/home/mazen/CLionProjects/lexical analyzer/re.txt");
    nonFiniteAutomata->evaluateFile();
    Node *tem = nonFiniteAutomata->getNFARoot();

    NFAToDFA *nfaToDFA = NFAToDFA::getInstance();
    nfaToDFA->engine(tem);
    Node dfaRoot;
    dfaRoot = (nfaToDFA->dfa.getDFARoot());

    /*fix the first node (DFARoot) in the dfaGraph
     * it always has a wrong value*/
    Node *temp = &dfaRoot;
    nfaToDFA->dfaGraph[0] = temp;

    Node *minDfaRoot;

    MinDFA *minDFA = MinDFA::getInstance();
    minDFA->engine();
    minDfaRoot = minDFA->minDFARoot;

    DFAAndTokens *dfaAndTokens = DFAAndTokens::getInstance();
    dfaAndTokens->takeMinDfa(minDfaRoot);
    cout<<"3dena"<<endl;

    Symbol_table_builder stb;
    stb.read_input_code("/home/mazen/CLionProjects/lexical analyzer/code.txt");
    stb.build_symbol_table();
    stb.print_symbol_table();

    for(char x : stb.codeFile)
    {
        cout << x;
    }

    cout << "done :D" << endl;
    return 0;
}