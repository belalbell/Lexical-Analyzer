//
// Created by belal on 3/22/19.
//

#ifndef COMPILER_NFARULES_H
#define COMPILER_NFARULES_H

#include "Node.h"

using namespace std;

class NFARules {

private:
    long nfaIndex=0;
public:
    static NFARules* getInstance();

    vector<Node *>orRule(vector<Node *> start, vector<Node *> end);

    vector<Node *>kleeneClosureRule(Node *start, Node *end);

    vector<Node *>positiveClosureRule(Node *start, Node *end);

    void concatenationRule( Node* end1,Node *start2);

    Node* createStart(Node *start, int index);

    Node* createEnd(Node *end, int index);

    void createEdge(string edgeValue,Node*,Node*);

};


#endif //COMPILER_NFARULES_H