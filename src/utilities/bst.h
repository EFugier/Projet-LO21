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
};


class Bst
{
 private:
  Node * root;
  Node * ite;

 public:
  Bst();
  Bst(std::string s);
  ~Bst() { deleteTree(); }

  char next(char c);
  void insert(std::string& s);
  void printTree(Node* init, int indent=0);
  void printTree(int indent=0) {
    printTree(root, indent);
  }

  inline void reset() { ite = root; }
  void deleteTree() {
    deleteTree(root);
    root = nullptr;
    ite = nullptr;
  }
  void deleteTree(Node* node);

  std::string serialize();
  void deserialize(std::string& s);
};


#endif // BST_H
