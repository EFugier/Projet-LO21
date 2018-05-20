#include <ostream>
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

void Bst::insert(char * s) {
  Node * node = root;
  for (unsigned int i=0; i<depth; i++) {
    if (s[i] == '0') {  // go left
      if (!node->left) node->left = new Node('0');
      node = node->left;
    }
    else if (s[i] == '1') {  // go right
      if (!node->right) node->right = new Node('1');
      node = node->right;
    }
    else node->value = s[i];  // end of the branch
  }
}
