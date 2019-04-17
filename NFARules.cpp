//
// Created by belal on 3/22/19.
//

#include <algorithm>
#include <iostream>
#include "NFARules.h"


static NFARules *insatnce = nullptr;

/*Singleton*/
NFARules *NFARules::getInstance() {
    if (insatnce == nullptr) {
        insatnce = new NFARules();
    }
    return insatnce;
}

void NFARules::createEdge(string edgeValue, Node *start, Node *end) {
//    Node*  start = new Node();
//    Node * end= new Node();
    //end->setType(edgeValue);
    end->setStatus(false);
    start->setEdgeValue(edgeValue);
    start->setStatus(false);
    start->setType("");
    start->setIndex(nfaIndex);
    nfaIndex++;
    end->setIndex(nfaIndex);
    nfaIndex++;
    //start.setChild(&end);
    //start->setChildNodes(*end);
    start->setChild(end);
    vector<Node> *node = new vector<Node>();
    node->push_back(*start);
    node->push_back(*end);
    //return *node;
}

Node* NFARules::createStart(Node *start, int index) {
    Node* first = new Node();
    first->setEdgeValue("$");
    first->setChild(start);
    first->setIndex(index);
    first->setStatus(false);
    first->setIndex(nfaIndex);
    //nfaIndex++;
    return first;
}

Node* NFARules::createEnd(Node *end, int index) {
    Node* last=new Node();
    last->setParent(end);
    last->setStatus(false);
    last->setIndex(index);
    end->setChild(last);
    end->setEdgeValue("$");
    last->setIndex(nfaIndex);
    //nfaIndex++;
    return last;
}

void NFARules::concatenationRule( Node *end1, Node *start2) {
    end1->setEdgeValue("$");
    end1->setChild(start2);
//    for (int i = 0; i < start1->getChildren().size(); ++i) {
//        if (end1->getIndex()==start1->getChildren().at(i)->getIndex()){
//            start1->getChildren().at(i)->setChild(start2);
//            start1->getChildren().at(i)->setEdgeValue("&");
//        }
//    }
//    vector<Node*> node ;
//    node.push_back(start1);
//    node.push_back(end2);
//    return node;
}

vector<Node*> NFARules::kleeneClosureRule(Node *start, Node *end) {
    Node *first = createStart(start, nfaIndex);
    nfaIndex++;
    Node *last = createEnd(end, nfaIndex);
    nfaIndex++;
    first->setChild(last);
    first->setEdgeValue("$");
    end->setChild(start);
    end->setEdgeValue("$");
//    first.setChild(start);
//    first.setEdgeValue("&");
//    end->setChild(&last);
//    end->setEdgeValue("&");
    vector<Node*> node;
    node.push_back(first);
    node.push_back(last);
    return node;
}


vector<Node*> NFARules::positiveClosureRule(Node *start, Node *end) {
    Node* first = createStart(start, nfaIndex);
    nfaIndex++;
    Node* last = createEnd(end, nfaIndex);
    nfaIndex++;
    end->setChild(start);
    end->setEdgeValue("$");
//    first.setChild(start);
//    first.setEdgeValue("&");
//    end->setChild(&last);
//    end->setEdgeValue("&");
    vector<Node*> node;
    node.push_back(first);
    node.push_back(last);
    return node;
}

vector<Node*> NFARules::orRule(vector<Node *> start, vector<Node *> end) {
    Node* first = createStart(start.at(0), nfaIndex);
    nfaIndex++;
    for (int i = 1; i < start.size(); ++i) {
        Node *temp = start[i];
        first->setChild(temp);
        //start.at(i)->setParent(first);
        first->setEdgeValue("$");
    }
    Node* last = createEnd(end.at(0), nfaIndex);
    nfaIndex++;
    for (int j = 1; j < end.size(); ++j) {
        end.at(j)->setChild(last);
        end.at(j)->setEdgeValue("$");
        last->setParent(end.at(j));
    }
    vector<Node*> node;
    node.push_back(first);
    node.push_back(last);
    return node;
}