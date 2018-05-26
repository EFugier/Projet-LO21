#ifndef BST_H
#define BST_H

#include <iostream>

class Node {
 public:
  char value;
  Node * left;
  Node * right;

  Node(char c='r') {
    value = c;
    left = nullptr;
    right = nullptr;
  }
  ~Node();
};


class Bst
{
 private:
  unsigned int depth;  // number of neighbor + 1

 public:
  Node * root;
  Node * ite;
  Bst();
  Bst(std::string s);

  char next(char c);
  void insert(std::string& s);

  inline void reset() { ite = root; }

  std::string serialize();
  void deserialize(std::string& s);
};


#endif // BST_H
