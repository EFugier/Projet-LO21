#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>

/// \class Node
/// Simple classe noeud pour former un arbre binaire
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


/// \class RuleBst
/// Arbre binaire utilise pour stocker les règles de position
class RuleBst
{
    /** Classe qui stocke les règles de position.
     * permet d'avoir une complexité temporel de verification d'appartenance en O(nb of neighbours) */
    private:
        Node * root; /// Racine de l'arbre
        Node * ite; /// Position actuelle du pseudo-iterateur
        RuleBst(const RuleBst&) = delete;
        const RuleBst& operator=(const RuleBst&) = delete;

    public:
        RuleBst();
        RuleBst(const std::string s);
        ~RuleBst() { deleteTree(); }

        /// Fait avancer l'iterateur à droite si c='0', à gauche si c='1'
        char next(char c);

        /// Insère un voisinage et l'état suivant associé dans l'arbre
        void insert(const std::vector<bool>& s, char c);
        /// Affiche l'arbre
        void printTree(int indent=0) {
            printTree(root, indent);
        }
        /// Afficher l'arbre à partir d'un certain noeud
        void printTree(Node* init, int indent=0);

        /// Reset le pseudo-iterateur
        inline void reset() { ite = root; }
        /// Libère la mémoire utilisée par l'arbre
        void deleteTree() {
            deleteTree(root);
            root = nullptr;
            ite = nullptr;
        }
        /// Efface une partie de l'arbre
        void deleteTree(Node* node);

        /// Transforme l'arbre en string
        std::string serialize();
        /// Transforme une string en arbre
        void deserialize(const std::string& s);
};


#endif // BST_H
