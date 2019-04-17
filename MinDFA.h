//
// Created by Sara on 22/03/2019.
//

#ifndef COMPILER_MINDFA_H
#define COMPILER_MINDFA_H

#include "Node.h"
#include "NFAToDFA.h"

using namespace std;

class MinDFA {
private:
    NFAToDFA *nfaToDFA = NFAToDFA::getInstance();
    NonFiniteAutomata* nonFiniteAutomata= NonFiniteAutomata::getInstance();


public:

    Node *minDFARoot;
    static MinDFA* getInstance();

    void alterChild(int oldIndex, Node* parent, int newIndex);

    void removeFromChildren(int removedIndex, int newIndex);

    void removeFromDFA(int nodeIndex);

    bool isEdgeValuesEqual(vector<string> firstValues, vector<string> secondValues);

    bool isChildrenEqual(vector<Node *> firstChildren, vector<Node *> secondChildren);

    void engine();
};


#endif //COMPILER_MINDFA_H