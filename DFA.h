
//
// Created by Sara on 22/03/2019.
//

#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H


#include "Node.h"
using namespace std;

class DFA {
private:
    Node DFARoot;

public:
    Node getDFARoot();
    void setDFARoot(Node*);

};


#endif //COMPILER_DFA_H