#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>

/// \class Node
/// Simple node class to make a binary tree
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


/// \class Node
/// Binary tree to store special position
class RuleBst
{
    /** Class used to store special position rule
     * allows O(nb of neighbours) time checking complexity */
    private:
        Node * root; /// root of the tree
        Node * ite; /// Current position of the iterator
        RuleBst(const RuleBst&) = delete;
        const RuleBst& operator=(const RuleBst&) = delete;

    public:
        RuleBst();
        RuleBst(const std::string s);
        ~RuleBst() { deleteTree(); }

        char next(char c);

        /// insert path in BST
        void insert(const std::vector<bool>& s, char c);
        void printTree(int indent=0) {
            printTree(root, indent);
        }
        /// insert path in BST
        void printTree(Node* init, int indent=0);

        /// reset iterator
        inline void reset() { ite = root; }
        /// free the memory used by the tree
        void deleteTree() {
            deleteTree(root);
            root = nullptr;
            ite = nullptr;
        }
        /// delete tree from a special node
        void deleteTree(Node* node);

        /// trun the bst into a string
        std::string serialize();
        /// trun a string into a bst
        void deserialize(const std::string& s);
};


#endif // BST_H
