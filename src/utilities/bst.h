#ifndef BST_H
#define BST_H

#include <iostream>

class Node {
 public:
  char value;
  Node * left;
  Node * right;

  Node(char c='r');
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
  ~Bst();

  char next(char c);
  void insert(std::string& s);

  inline reset() { ite = root }

  std::string serialize();
  void deserialize(std::string& s);
};


#endif // BST_H
