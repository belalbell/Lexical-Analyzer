
//
// Created by Sara on 22/03/2019.
//

#include "DFA.h"

void DFA::setDFARoot(Node* root) {
    DFARoot = *root;
}

Node DFA::getDFARoot() { return DFARoot; }