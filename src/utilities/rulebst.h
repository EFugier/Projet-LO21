#ifndef BST_H
#define BST_H

#include <iostream>

class Node {
    /** Simple node class to be used in a binary tree */
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


class RuleBst
{
    /** Class used to store special position rule
     * allows O(nb of neighbours) time checking complexity */
    private:
        Node * root; ///< root of the tree
        Node * ite; ///< Current position of the iterator
        RuleBst(const RuleBst&) = delete;
        const RuleBst& operator=(const RuleBst&) = delete;

    public:
        RuleBst();
        RuleBst(const std::string s);
        ~RuleBst() { deleteTree(); }

        char next(char c);

        void insert(const std::string& s); ///< insert path in BST
        void printTree(int indent=0) {
            printTree(root, indent);
        }
        void printTree(Node* init, int indent=0); ///< insert path in BST

        inline void reset() { ite = root; } ///< reset iterator 
        void deleteTree() { ///< free the memory used by the tree
            deleteTree(root);
            root = nullptr;
            ite = nullptr;
        }
        void deleteTree(Node* node);

        std::string serialize(); ///< trun the bst into a string
        void deserialize(const std::string& s); ///< trun a string into a bst
};


#endif // BST_H
