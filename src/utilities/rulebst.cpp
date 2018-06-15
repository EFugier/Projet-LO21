#include <iostream>
#include <iomanip>
#include <stack>
#include "rulebst.h"


RuleBst::RuleBst() {
    root = new Node('r');
    ite = root;
}


RuleBst::RuleBst(const std::string s) {
    root = nullptr;
    ite = nullptr;

    deserialize(s);
}


void RuleBst::deleteTree(Node* node) {
    if (node) {
        if (node->left) deleteTree(node->left);
        if (node->right) deleteTree(node->right);

        delete node;
    }
}

void RuleBst::printTree(Node* node, int indent) {
    if(node) {
        if (node->left || node->right) {
            printTree(node->right, indent+4);
            if (indent) {
                std::cout<<std::setw(indent)<<' '<<std::flush;
            }
            std::cout<<"-"<<node->value<<"\n "<<std::flush;
            printTree(node->left, indent+4);
        }
    }
    else {std::cout<<std::setw(indent)<<' '<<"-"<<"\n "<<std::flush;};
}


char RuleBst::next(char c) {
    if (!ite) return 'n';
    if (c == '0' and ite->left ) {
        ite = ite->left;
        return ite->value;
    }
    else if (c == '1' and ite->right) {
        ite = ite->right;
        return ite->value;
    }
    return 'n'; // path do not exist in the tree
}


void RuleBst::insert(const std::vector<bool>& s, char cc) {
    Node * node = root;
    for(const bool& b : s) {
        if (b) { // go right 
            if (!node->right) node->right = new Node('1');
            node = node->right;
        }
        else {  // go left
            if (!node->left) node->left = new Node('0');
            node = node->left;
        }
    }
    node->value = cc;  // end of the branch
}


std::string RuleBst::serialize() {

    if (!root) return "";

    std::string seq = "";

    std::stack<Node *> toProcess;

    Node * node = root;
    while(1) {
        // fork node
        if (node->left && node->right) {
            seq.push_back('f');
            toProcess.push(node->right);
        }
        // start with the left child
        if (node->left) {
            node = node->left;
            seq.push_back('0');
        }
        else if (node->right) {
            node = node->right;
            seq.push_back('1');
        }
        // leaf
        else {
            seq.push_back(node->value);

            if (toProcess.empty()) break;  // last leaf

            node = toProcess.top();
            toProcess.pop();
            seq.push_back('1');
        }
    }
    return seq;
}


void RuleBst::deserialize(const std::string& s) {
    deleteTree();
    root = new Node('r');

    Node * last = nullptr;
    last = root;
    std::stack<Node *> forkNodes;

    for(const char& c : s) {
        if (c == '0') {
            last->left = new Node('0');
            last = last-> left;
        }
        else if (c == '1') {
            last->right = new Node('1');
            last = last->right;
        }
        else if (c == 'f') {
            forkNodes.push(last);
        }
        else {  // leaf
            last->value = c;  // overwrite the leaf value

            if (forkNodes.empty()) break;  // last leaf

            // go to last fork node
            last = forkNodes.top();
            forkNodes.pop();
        }
    }
    ite = root;
}
