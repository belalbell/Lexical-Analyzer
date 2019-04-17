//
// Created by Sara on 22/03/2019.
//
#include "Node.h"

void Node::setStatus(bool statusValue) {
    status = statusValue;
}

bool Node::getStatus() {
    return status;
}

void Node::setIndex(int indexValue) {
    index = indexValue;
}

int Node::getIndex() {
    return index;
}

void Node::setChild(Node *child) {
    children.push_back(child);
}
//void Node::setChildNodes(Node child) {
//    childrenNodes.push_back(child);
//}
//
//vector<Node>* Node::getChildNodes(){
//    return &childrenNodes;
//}


vector<Node *> Node::getChildren() {
    return children;
}

void Node::setEdgeValue(string edge) {
    edgeValue.push_back(edge);
}

vector<string> Node::getEdgeValue() {
    return edgeValue;
}

void Node::setType(string typeValue) {
    type = typeValue;
}

string Node::getType() {
    return type;
}

void Node::setParent(Node *node) {
    parent.push_back(node);
}

vector<Node *> Node::getParent() {
    return parent;
}

void Node::alterChild(int index , Node* newChild){
    children[index]=newChild;
}