//
// Created by Sara on 22/03/2019.
//

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include<bits/stdc++.h>
#include "NonFiniteAutomata.h"

using namespace std;

static NonFiniteAutomata *insatnce = nullptr;

/*Singleton*/
NonFiniteAutomata *NonFiniteAutomata::getInstance() {
    if (insatnce == nullptr) {
        insatnce = new NonFiniteAutomata();
    }
    return insatnce;
}
//
//void giveChildren(Node *node) {
//    vector<Node> *children = node->getChildNodes();
//    for (int i = 0; i < children->size(); ++i) {
//        node->setChild(&children->at(i));
//    }
//}


int prec(char c) {
    if (c == '*' || c == '+')
        return 3;
    else if (c == '_')
        return 2;
    else if (c == '|')
        return 1;
    else
        return -1;
}

// The main function to convert infix expression
//to postfix expression
string NonFiniteAutomata::infixToPostfix(string s) {
    stack<char> st;
    st.push('N');
    int l = s.length();
    string ns;
    for (int i = 0; i < l; i++) {
        //"!","@","#","$","%","?","^"
        // If the scanned character is an operand, add it to output string.
        if (s[i] == '!' || s[i] == '@' || s[i] == '#' || s[i] == '$' || s[i] == '%' || s[i] == '?' || s[i] == '^'
            || s[i] == '\\' || s[i] == '<' || s[i] == '>' || s[i] == '/' || s[i] == '-' ||
            (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '&' || s[i] == '.' || s[i] == '=') {
            ns += s[i];
            if (s[i] == '\\') {
                i++;
                ns += s[i];
            }
        }

            // If the scanned character is an ‘(‘, push it to the stack.
        else if (s[i] == '(')

            st.push('(');

            // If the scanned character is an ‘)’, pop and to output string from the stack
            // until an ‘(‘ is encountered.
        else if (s[i] == ')') {
            while (st.top() != 'N' && st.top() != '(') {
                char c = st.top();
                st.pop();
                ns += c;
            }
            if (st.top() == '(') {
                char c = st.top();
                st.pop();
            }
        }

            //If an operator is scanned
        else {
            while (st.top() != 'N' && prec(s[i]) <= prec(st.top())) {
                char c = st.top();

                st.pop();
                ns += c;
            }
            st.push(s[i]);
        }

    }
    //Pop all the remaining elements from the stack
    while (st.top() != 'N') {
        char c = st.top();
        st.pop();
        ns += c;
    }
    /////////////////////////////////
    ///cout << ns;
    ////////////////////////////////

    return ns;

}


vector<Node *> concatenationRule(Node *start1, Node *end1, Node *start2, Node *end2) {
    end1->setEdgeValue("$");
    end1->setChild(start2);
    for (int i = 0; i < start1->getChildren().size(); ++i) {
        if (end1->getIndex() == start1->getChildren().at(i)->getIndex()) {
            start1->getChildren().at(i)->setChild(start2);
            start1->getChildren().at(i)->setEdgeValue("&");
        }
    }
    vector<Node *> node;
    node.push_back(start1);
    node.push_back(end2);
    return node;
}


Node *NonFiniteAutomata::getNFARoot() {
    int uniqueIndex = 0;
    vector<Node *> starts;
    vector<Node *> ends;
    stack<int> st;
    for (int i = 0; i < draw.size(); ++i) {
        string *tmp;
        vector<Node *> lastOp;
        tmp = draw.at(i);
        string post = infixToPostfix(tmp[1]);
        ////////////////////////////
        cout << post << endl;
        /////////////////////
        for (int j = 0; j < post.size(); ++j) {
            ///"@","#","$","%","?","^"
            if (post[j] == '@' || post[j] == '#' || post[j] == '$' || post[j] == '%' || post[j] == '?' ||
                post[j] == '^') {
                string str(1, post[j]);
                int index = symIndex[str];
//                for (int l = 0; l < symRanges.size(); ++l) {
//                    string *range = symRanges.at(l);
//                    cout<<"hhhhhhhhhhhhhhhh" << range[0]<<" "<< range[1]<<endl;
//
//                }
                string *range = symRanges.at(index);
                vector<Node *> startRange;
                vector<Node *> endRange;
                vector<Node *> start;
                vector<Node *> end;
                for (int k = 0; k < range[0].size(); k++) {

                    char c = range[0][k];
                    if (c == ' ')
                        continue;
                    while (c <= range[1][k]) {
                        string str1(1, c);
                        Node *first = new Node();
                        Node *last = new Node();
                        nfaRules->createEdge(str1, first, last);
                        //giveChildren(first);
                        //giveChildren(last);
                        start.push_back(first);
                        end.push_back(last);
                        c++;
                    }
                }
                vector<Node *> node = nfaRules->orRule(start, end);
                st.push(uniqueIndex);
                stIndex[uniqueIndex] = node;
                uniqueIndex++;
            } else if (post[j] == '+' && post[j - 1] != '\\') {
                int index = st.top();
                st.pop();
                vector<Node *> node = stIndex[index];
                vector<Node *> tmp = nfaRules->positiveClosureRule(node[0], node[1]);
                lastOp.clear();
                lastOp.push_back(tmp.at(0));
                lastOp.push_back(tmp.at(1));
                vector<Node *> *ret = new vector<Node *>();
                ret->push_back(tmp.at(0));
                ret->push_back(tmp.at(1));
                stIndex[uniqueIndex] = *ret;
                st.push(uniqueIndex);
                uniqueIndex++;
            } else if (post[j] == '*' && post[j - 1] != '\\') {
                int index = st.top();
                st.pop();
                vector<Node *> node = stIndex[index];
                vector<Node *> tmp = nfaRules->kleeneClosureRule(node[0], node[1]);
                lastOp.clear();
                lastOp.push_back(tmp.at(0));
                lastOp.push_back(tmp.at(1));
                vector<Node *> *ret = new vector<Node *>();
                ret->push_back(tmp.at(0));
                ret->push_back(tmp.at(1));
                stIndex[uniqueIndex] = *ret;
                st.push(uniqueIndex);
                uniqueIndex++;
            } else if (post[j] == '|') {
                int index1 = st.top();
                st.pop();
                int index2 = st.top();
                st.pop();
                vector<Node *> start;
                vector<Node *> end;
                vector<Node *> node1 = stIndex[index1];
                vector<Node *> node2 = stIndex[index2];
                start.push_back(node1[0]);
                start.push_back(node2[0]);
                end.push_back(node1[1]);
                end.push_back(node2[1]);
                vector<Node *> tmp = nfaRules->orRule(start, end);
                lastOp.clear();
                lastOp.push_back(tmp.at(0));
                lastOp.push_back(tmp.at(1));
                vector<Node *> *ret = new vector<Node *>();
                ret->push_back(tmp.at(0));
                ret->push_back(tmp.at(1));
                stIndex[uniqueIndex] = *ret;
                st.push(uniqueIndex);
                uniqueIndex++;
            } else if (post[j] == '_') {
                int index1 = st.top();
                st.pop();
                int index2 = st.top();
                st.pop();
                vector<Node *> node1;
                node1.push_back(stIndex[index1].at(0));
                node1.push_back(stIndex[index1].at(1));
                vector<Node *> node2;
                node2.push_back(stIndex[index2].at(0));
                node2.push_back(stIndex[index2].at(1));
                nfaRules->concatenationRule(node2.at(1), node1.at(0));
                lastOp.clear();
                lastOp.push_back(node2.at(0));
                lastOp.push_back(node1.at(1));
                vector<Node *> *ret = new vector<Node *>();
                ret->push_back(node2.at(0));
                ret->push_back(node1.at(1));
                stIndex[uniqueIndex] = *ret;
                st.push(uniqueIndex);
                uniqueIndex++;
            } else {
                if (post[j] == '\\')
                    continue;
                string str(1, post[j]);
                setDifferentEdgeValues(str);
                Node *first = new Node();
                Node *last = new Node();
                nfaRules->createEdge(str, first, last);
                //giveChildren(first);
                //giveChildren(last);
                lastOp.clear();
                lastOp.push_back(first);
                lastOp.push_back(last);
                vector<Node *> *ret = new vector<Node *>();
                ret->push_back(first);
                ret->push_back(last);
                //ret[1] = *last;
                stIndex[uniqueIndex] = *ret;
                st.push(uniqueIndex);
                uniqueIndex++;
            }
        }
        //cout<<&lastOp<<endl;
        //vector<Node*> booooooooo= stIndex[uniqueIndex-1];
        lastOp.at(1)->setType(tmp[0]);
        starts.push_back(lastOp.at(0));
        ends.push_back(lastOp.at(1));
        lastOp.clear();
        st.pop();
    }
    vector<Node *> final = nfaRules->orRule(starts, ends);
    final[1]->setStatus(true);
    nfaroot = final[0];
    return final[0];
}

void NonFiniteAutomata::setDifferentEdgeValues(string edgeValue) {
    bool check = true;
    for (int i = 0; i < differentEdgeValues.size(); ++i) {
        if (differentEdgeValues.at(i) == edgeValue)
            check = false;
    }
    if (check && edgeValue != "$")
        differentEdgeValues.push_back(edgeValue);
}

void NonFiniteAutomata::addingEdges() {
    for (int i = 0; i < symRanges.size(); ++i) {
        string *range = symRanges.at(i);
        int index = range[1].find('-');
        string first;
    }
}

vector<string> NonFiniteAutomata::getDifferentEdgeValues() {
    return differentEdgeValues;
}

void NonFiniteAutomata::readREFile(string address) {
    ifstream in(address);
    string tmp;
    while (getline(in, tmp)) {
        file.push_back(tmp);
    }
}

string NonFiniteAutomata::finder(string rhs) {
    for (int i = 0; i < LHSFinder.size(); ++i) {
        if (rhs.find(LHSFinder.at(i)) != string::npos)
            return LHSFinder.at(i);
    }
    return "";
}

vector<string> cutter(string rhs) {
    istringstream ss(rhs);
    string token;
    vector<string> line;
    while (std::getline(ss, token, '|')) {
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        line.push_back(token);
    }
    return line;
}

void NonFiniteAutomata::evaluateFile() {
    lhsSym["\\L"] = "$";
    int symStringIndex = 0;/*string sym*/
    for (int i = 0; i < file.size(); ++i) {
        string line = file.at(i);
        if (line.find('=') != string::npos && line.find(':') == string::npos) {
            string LHS = line.substr(0, line.find('='));
            LHS.erase(remove_if(LHS.begin(), LHS.end(), ::isspace), LHS.end());
            lhsSym[LHS] = "";
            string rhs = line.substr(line.find('=') + 1, line.size());
            vector<string> freeRhs = cutter(rhs);
            string *tmp = new string[2];
            tmp[0] = "";
            tmp[1] = "";
            for (int j = 0; j < freeRhs.size(); ++j) {
                string range = freeRhs.at(j);
                string test = finder(range);
                if (test != "") {
                    if (lhsSym[LHS] != "") {
                        lhsSym[LHS] += "|";
                    }
                    string replaceSym = lhsSym[test];
                    range = range.substr(0, range.find(test)) + replaceSym +
                            range.substr(range.find(test) + test.size(), range.size());
                    lhsSym[LHS] += range;

                } else {
                    symIndex[sym[symStringIndex]] = symStringIndex;
                    if (lhsSym[LHS] != "") {
                        lhsSym[LHS] += "|";
                    }
                    if (range.find('-') != string::npos) {
                        if (tmp[0] != "") {
                            tmp = new string[2];
                            tmp[0] = "";
                            tmp[1] = "";
                        }
                        tmp[0] += range[range.find('-') - 1];
                        tmp[1] += range[range.find('-') + 1];
                        char first = range[range.find('-') - 1], second = range[range.find('-') + 1];
                        while (first <= second) {
                            string str(1, first);
                            setDifferentEdgeValues(str);
                            first++;
                        }
                        range = range.substr(0, range.find('-') - 1) + sym[symStringIndex] +
                                range.substr(range.find('-') + 2, range.size());
                        lhsSym[LHS] += range;
                        ////////////////////////////////
                        cout << "ranges : " << tmp[0] << " " << tmp[1] << endl;
                        ////////////////////////////////
                        symRanges.push_back(tmp);
                    } else {
                        if (tmp[0] != "") {
                            tmp[0] += " ";
                            tmp[1] += " ";
                        }
                        int k = 0;
                        while (range[k] == '(') {
                            k++;
                        }
                        tmp[0] += range[k];
                        tmp[1] += range[k];
                        range[k] = sym[symStringIndex][0];
                        lhsSym[LHS] += range;
                        symRanges.push_back(tmp);
                    }
                }
                symStringIndex++;
                LHSFinder.push_back(LHS);
            }
        } else {
            if (line.find(':') != string::npos) {
                int index = line.find(':');
                string lhs = line.substr(0, index);
                lhs.erase(remove_if(lhs.begin(), lhs.end(), ::isspace), lhs.end());
                string rhs = line.substr(index + 1, line.size());
                string tmp = "";
                for (int j = 0; j < rhs.size(); ++j) {
                    int start = j;
                    if (((rhs[j] >= 'a' && rhs[j] <= 'z') || (rhs[j] >= 'A' && rhs[j] <= 'Z'))) {
                        if (rhs[j] == 'L' && rhs[j - 1] == '\\') {
                            tmp += "\\L";
                        } else {
                            tmp += rhs[j];
                        }
                    } else if (rhs[j] == '\\' && rhs[j + 1] != 'L' && rhs[j - 1] != ' ') {
                        rhs = rhs.substr(0, j) + '_' + rhs.substr(j + 1, rhs.size());

                    } else if (j != 0) {
                        if (rhs[j] == ' ' && rhs[j - 1] != '|' && rhs[j + 1] != '|' && rhs[j - 1] != '(') {
                            rhs[j] = '_';
                        }
                        int tmpIndex = rhs.find(tmp);
                        if (tmp != "") {
                            string addedsym;
                            if (lhsSym[tmp] == "") {
                                addedsym = tmp;
                            } else {
                                addedsym = "(" + lhsSym[tmp] + ")";
                            }
                            rhs = rhs.substr(0, tmpIndex) + addedsym +
                                  rhs.substr(tmpIndex + tmp.size(), rhs.size());
                            j = tmpIndex + lhsSym[tmp].size();
                            tmp = "";
                        }
                    }
                }
                string *toDraw = new string[2];
                toDraw[0] = lhs;
                rhs.erase(remove_if(rhs.begin(), rhs.end(), ::isspace), rhs.end());
                toDraw[1] = rhs;
                /////////////////////////////////////////////
                cout << toDraw[0] << " " << toDraw[1] << endl;
                /////////////////////////////////////////////
                priority[lhs] = normalPriority;
                normalPriority--;
                draw.push_back(toDraw);
            } else if (line[0] == '{') {
                string tmp1 = "";
                string tmp2 = "";
                int i = 1;
                while (line[i] != '}') {
                    if (line[i] != ' ') {
                        string str(1, line[i]);
                        setDifferentEdgeValues(str);
                        tmp1 += line[i];
                        tmp2 += line[i];
                        tmp2 += "_";
                    } else if (tmp1 != "") {
                        string *toDraw = new string[2];
                        keywords[tmp1]=keyWordsPriority;
                        toDraw[0] = "";
                        toDraw[1] = tmp2.substr(0, tmp2.size() - 1);
                        /////////////////////////////////////////////
                        cout << toDraw[0] << " " << toDraw[1] << endl;
                        /////////////////////////////////////////////
                        //priority["keyword"] = keyWordsPriority;
                        //keyWordsPriority--;
                        draw.push_back(toDraw);
                        tmp1 = "";
                        tmp2 = "";
                    }
                    i++;
                }
                if (tmp1 != "") {
                    string *toDraw = new string[2];
                    keywords[tmp1]=keyWordsPriority;
                    toDraw[0] = "";
                    toDraw[1] = tmp2.substr(0, tmp2.size() - 1);
                    /////////////////////////////////////////////
                    cout << toDraw[0] << " " << toDraw[1] << endl;
                    /////////////////////////////////////////////
                    //priority["keyword"] = keyWordsPriority;
                    //keyWordsPriority--;
                    draw.push_back(toDraw);
                    tmp1 = "";
                    tmp2 = "";
                }
            } else if (line[0] == '[') {
                string tmp1 = "";
                string tmp2 = "";
                int i = 1;
                while (line[i] != ']') {
                    if (line[i] != ' ') {
                        if (line[i] != '\\') {
                            string str(1, line[i]);
                            setDifferentEdgeValues(str);
                        }
                        tmp1 += line[i];
                        tmp2 += line[i];
                    } else if (tmp1 != "") {
                        string *toDraw = new string[2];
                        toDraw[0] = tmp1[tmp1.size() - 1];
                        toDraw[1] = tmp2;
                        /////////////////////////////////////////////
                        cout << toDraw[0] << " " << toDraw[1] << endl;
                        /////////////////////////////////////////////
                        priority[string(1, tmp1[tmp1.size() - 1])] = normalPriority;
                        normalPriority--;
                        draw.push_back(toDraw);
                        tmp1 = "";
                        tmp2 = "";
                    }
                    i++;
                }
                if (tmp1 != "") {
                    string *toDraw = new string[2];
                    toDraw[0] = tmp1[tmp1.size() - 1];
                    toDraw[1] = tmp2;
                    /////////////////////////////////////////////
                    cout << toDraw[0] << " " << toDraw[1] << endl;
                    /////////////////////////////////////////////
                    priority[string(1, tmp1[tmp1.size() - 1])] = normalPriority;
                    normalPriority--;
                    draw.push_back(toDraw);
                    tmp1 = "";
                    tmp2 = "";
                }
            }
        }
    }
}


void NonFiniteAutomata::buildNFA() {
    readREFile("/home/belal/Compiler/Compiler/re.txt");

}

string NonFiniteAutomata::compare(string str1, string str2) {
    int first = priority[str1];
    int second = priority[str2];
    cout << "compare str1: " << str1 << " str2: " << str2 << endl;
    if (str1 == "" && str2 == "") {
        return "";
    } else if (str1 == "") {
        return str2;
    } else if (str2 == "") {
        return str1;
    } else if (first > second) {
        return str1;
    } else {
        return str2;
    }
}

bool NonFiniteAutomata::isAKeyWord(string input) {
    if (input == "keyword")
        return true;
    return false;
}



//
//int main() {
//    NonFiniteAutomata nfa;
//    nfa.infixToPostfix("$+|$+_._$+_(&|E_$+)");
//    return 0;
//}

