//
// Created by Sara on 22/03/2019.
//

#ifndef COMPILER_NONFINITEAUTOMATA_H
#define COMPILER_NONFINITEAUTOMATA_H

#include "Node.h"
#include "NFARules.h"
#include <map>

using namespace std;

class NonFiniteAutomata {
private:
    map<string,int> priority;
    int keyWordsPriority=1000;
    int normalPriority=100;
    vector<string> differentEdgeValues;/*contains the different values an edge can take*/
    vector<string> file;
    vector<string> evaluatedFile;/*after file fix*/
    string sym[7] = {"@","#","%","?","^"};
    vector<string*> symRanges;
    map<string,int> symIndex;
    map<string,string> lhsSym;
    vector<string> LHSFinder;
    vector<string*> draw;
    NFARules *nfaRules = NFARules::getInstance();
    //NFARules nfaRules;
    map<int,vector<Node*>>stIndex;

    Node* nfaroot;
    int nfaIndex =0;
public:

    map<string,int> keywords;
    bool isAKeyWord(string input);
    string compare(string str1,string str2);

    static NonFiniteAutomata* getInstance();

    Node *getNFARoot();

    void setDifferentEdgeValues(string edgeValue);

    vector<string> getDifferentEdgeValues();

    void readREFile(string address);

    string finder(string rhs);

    void evaluateFile();

    string infixToPostfix(string s);

    void buildNFA();

    void addingEdges();

    vector<Node > createEdge(string edgeValue);
};


#endif //COMPILER_NONFINITEAUTOMATA_H