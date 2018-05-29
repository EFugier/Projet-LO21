#include <iostream>
#include <iomanip>
#include <stack>
#include "rulebst.h"


RuleBst::RuleBst() {
  root = new Node('r');
  ite = root;
}


RuleBst::RuleBst(std::string s) {
  deserialize(s);
}


void RuleBst::deleteTree(Node* init) {
  std::stack<Node *> toProcess;
  if (!init) return;
  toProcess.push(init);
  Node* node;
  while(!toProcess.empty()) {
    node = toProcess.top();
    toProcess.pop();
    if (node->left) toProcess.push(node->left);
    if (node->right) toProcess.push(node->right);

    delete node;
  }
}


void RuleBst::printTree(Node* node, int indent) {
  if(node) {
    if (indent) {
      std::cout<<std::setw(indent)<<' '<<std::flush;
    }
    std::cout<<"-"<<node->value<<"\n "<<std::flush;
    if (node->left || node->right) {
      printTree(node->right, indent+2);
      printTree(node->left, indent+2);
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


void RuleBst::insert(std::string& s) {
  Node * node = root;
  for(char& c : s) {
    if (c == '0') {  // go left
      if (!node->left) node->left = new Node('0');
      node = node->left;
    }
    else if (c == '1') {  // go right
      if (!node->right) node->right = new Node('1');
      node = node->right;
    }
    else node->value = c;  // end of the branch
  }
}


std::string RuleBst::serialize() {

  if (!root) return "";

  std::string seq = "";

  std::stack<Node *> toProcess;

  Node * node = root;
  while(1) {
    // fork node
    if (node->left && node->right) {
      seq.append(1, 'f');
      toProcess.push(node->right);
    }
    // start with the left child
    if (node->left) {
      node = node->left;
      seq.append(1, '0');
    }
    else if (node->right) {
      node = node->right;
      seq.append(1, '1');
    }
    // leaf
    else {
      seq.append(1, node->value);

      if (toProcess.empty()) break;  // last leaf

      node = toProcess.top();
      toProcess.pop();
      seq.append(1, '1');
    }
  }
  return seq;
}


void RuleBst::deserialize(std::string& s) {
  // deleteTree(root);
  root = new Node('r');

  Node * last = nullptr;
  last = root;
  std::stack<Node *> forkNodes;

  for(char& c : s) {
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
