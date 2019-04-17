//
// Created by Sara on 22/03/2019.
//

#ifndef COMPILER_NODE_H
#define COMPILER_NODE_H

#include <vector>
#include <string>

using namespace std;

class Node {

private:
    bool status;/*0 means internal node 1 means acceptance node*/
    int index;/*index of the node*/
    string type="";/*defines the acceptance node type as id,num,if, then ,....*/
    vector<Node *> children;
    vector<Node > childrenNodes;
    vector<Node *> parent;
    vector<string> edgeValue;

public:
    void setParent(Node *node);

    vector<Node *> getParent();

    void setStatus(bool statusValue);

    bool getStatus();

    void setIndex(int indexValue);

    int getIndex();

    void setChild(Node *child);

    //void setChildNodes(Node child);

    //vector<Node>* getChildNodes();

    void alterChild(int index , Node* newChild);

    vector<Node *> getChildren();

    void setEdgeValue(string edge);

    vector<string> getEdgeValue();

    void setType(string typeValue);

    string getType();

};


#endif //COMPILER_NODE_H