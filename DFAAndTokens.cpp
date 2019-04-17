//
// Created by Sara on 22/03/2019.
//

#include "DFAAndTokens.h"
#include "MinDFA.h"


static DFAAndTokens *insatnce = nullptr;

/*Singleton*/
DFAAndTokens *DFAAndTokens::getInstance() {
    if (insatnce == nullptr) {
        insatnce = new DFAAndTokens();
    }
    return insatnce;
}

void DFAAndTokens::takeMinDfa(Node *node) {
    minDfaRoot = node;
    pointer = node;
}

Node *DFAAndTokens::getNextNode(char input) {
    string temp = "";
    temp += input;
    inputStr += input;
    Node *currentNode = NULL;
    bool currentStatus;

    vector<Node *> children = pointer->getChildren();
    vector<string> edgeValues = pointer->getEdgeValue();
    for (int i = 0; i < edgeValues.size(); ++i) {
        if (edgeValues[i] == temp) {
            pointer = children[i];
            currentNode = children[i];
        }
    }
    if (currentNode == NULL) {
        setInputStr();
        return NULL;
    } else {
        currentStatus = currentNode->getStatus();
        if (nonFiniteAutomata->keywords[inputStr]) {
            Node *newNode = new Node();
            newNode->setType(inputStr);
            newNode->setStatus(currentNode->getStatus());
            setInputStr();
            return newNode;
        } else {
            return currentNode;
        }
    }

}

void DFAAndTokens::resetDFA() {
    pointer = minDfaRoot;
    setInputStr();
}

//Node *lkl(char input) {
//    inputStr += input;
//    Node *currentNode;
//    bool currentStatus;
//
//    currentNode = getNextNode(input);
//    if (currentNode == NULL) {
//        setInputStr();
//        return NULL;
//    } else {
//        currentStatus = currentNode->getStatus();
//        if (nonFiniteAutomata->keywords[inputStr]) {
//            Node *newNode = new Node();
//            newNode->setType(inputStr);
//            newNode->setStatus(currentNode->getStatus());
//            setInputStr();
//            return newNode;
//        } else {
//            return currentNode;
//        }
//    }
//}

void DFAAndTokens::setInputStr() { inputStr = ""; }