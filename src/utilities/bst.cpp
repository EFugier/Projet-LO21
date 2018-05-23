#include <iostream>
#include <stack>
#include "bst.h"

Node::Node(char c) {
  value = c;
  left = nullptr;
  right = nullptr;
}

Bst::Bst() {
  root = new Node();
  ite = root;
}

char Bst::next(char c) {
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

void Bst::insert(std::string& s) {
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


std::string Bst::serialize() {

  if (!root) return "";

  std::string seq = "";

  std::stack<Node *> toProcess;
  toProcess.push(root);

  Node * node;
  while(!toProcess.empty()) {
    node = toProcess.top();
    toProcess.pop();
    // order is important to keep bst property (convention)
    if (node->right) {
      toProcess.push(node->right);
      seq.append(1, '1');
    }
    if (node->left) {
      toProcess.push(node->left);
      seq.append(1, '0');
    }

    if (node->right && node->left) seq.append(1, 'f');  // fork node
    else if (!node->right && !node->left) seq.append(1, node->value);  // leaf
  }

  return seq;
}


void Bst::deserialize(std::string& s) {
  std::stack<Node *> forkNodes;
  Node * last = nullptr;
  root = new Node('r');
  last = root;

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

      if (forkNodes.empty()) break;  // this is the last leaf

      // go to last fork node
      last = forkNodes.top();
      forkNodes.pop();
    }
  }
}
