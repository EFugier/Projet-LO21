#include <ostream>
#include "bst.h"

Bst::Bst() {
  root = new Node;
  root->value = 'r';
  ite = root;
}

char Bst::next(char c) const {
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
