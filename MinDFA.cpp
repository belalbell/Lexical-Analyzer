//
// Created by Sara on 22/03/2019.
//

#include "MinDFA.h"

static MinDFA *insatnce = nullptr;

/*Singleton*/
MinDFA *MinDFA::getInstance() {
    if (insatnce == nullptr) {
        insatnce = new MinDFA();
    }
    return insatnce;
}


void MinDFA::alterChild(int oldIndex, Node *parent, int newIndex) {
    parent->alterChild(oldIndex, nfaToDFA->dfaGraph[newIndex]);
}

void MinDFA::removeFromChildren(int removedIndex, int newIndex) {
    Node *removedNode = nfaToDFA->dfaGraph[removedIndex];
    removeFromDFA(removedIndex);
    for (int i = 0; i < nfaToDFA->dfaGraph.size(); ++i) {
        vector<Node *> children = nfaToDFA->dfaGraph[i]->getChildren();
        for (int j = 0; j < children.size(); ++j) {
            if (children[j] == removedNode) {
                alterChild(j, nfaToDFA->dfaGraph[i], newIndex);
            }
        }
    }
}

void MinDFA::removeFromDFA(int nodeIndex) {
    vector<Node *> temp;
    int size = nfaToDFA->dfaGraph.size() - 1;
    for (int i = size; i > nodeIndex; i--) {
        temp.push_back(nfaToDFA->dfaGraph[i]);
        nfaToDFA->dfaGraph.pop_back();
    }
    nfaToDFA->dfaGraph.pop_back();

    while (!temp.empty()) {
        nfaToDFA->dfaGraph.push_back(temp[temp.size() - 1]);
        temp.pop_back();
    }

}

bool MinDFA::isEdgeValuesEqual(vector<string> firstValues, vector<string> secondValues) {
    if (firstValues.size() == secondValues.size()) {
        for (int i = 0; i < firstValues.size(); i++) {
            if (firstValues[i] != secondValues[i]) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;

}

bool MinDFA::isChildrenEqual(vector<Node *> firstChildren, vector<Node *> secondChildren) {
    for (int i = 0; i < firstChildren.size(); i++) {
        if (firstChildren[i]->getIndex() != secondChildren[i]->getIndex()) {
            return false;
        }
    }
    return true;
}

void MinDFA::engine() {
    int removedIndex = -1, newIndex = -1, size = nfaToDFA->dfaGraph.size();
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if ((nfaToDFA->dfaGraph[i]->getStatus() == nfaToDFA->dfaGraph[j]->getStatus()) &&
                (!nfaToDFA->dfaGraph[i]->getEdgeValue().empty()) && (!nfaToDFA->dfaGraph[j]->getEdgeValue().empty()) &&
                (isEdgeValuesEqual(nfaToDFA->dfaGraph[i]->getEdgeValue(), nfaToDFA->dfaGraph[j]->getEdgeValue())) &&
                (isChildrenEqual(nfaToDFA->dfaGraph[i]->getChildren(), nfaToDFA->dfaGraph[j]->getChildren()))) {
                removedIndex = j;
                newIndex = i;

                /*set the dfa node type*/
                nfaToDFA->dfaGraph[i]->setType(
                        nonFiniteAutomata->compare(nfaToDFA->dfaGraph[j]->getType(), nfaToDFA->dfaGraph[i]->getType()));

                removeFromChildren(removedIndex, newIndex);
                size--;
                j--;
            }
        }
    }
    minDFARoot = nfaToDFA->dfaGraph[0];/*this is the min dfa root*/
}