#ifndef BST_H
#define BST_H

#include <ostream>

class Bst
{
 private:
  struct Node {
    char value;
    Node left;
    Node right;
  };

 public:
  Node * root;
  Node * ite;
  Bst();
  ~Bst();

  char next(char c) const;

  inline reset() { ite = root }
};

#endif // BST_H
