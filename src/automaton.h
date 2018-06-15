#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "./utilities/sqlite3.h"
#include <unordered_map>
#include "./utilities/rulebst.h"
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QString>

// TODO
// Improve the insertRangeInto function

static int callback_load_automata(void *ptr, int count, char **data, char **columns);
static int callback_get_id_automata(void *ptr, int count, char **data, char **columns);
const std::vector<std::string> explode(const std::string& s, const char& c);
/// \class Automaton
/// Classe qui peut se résumer à un ensemble de règles
/// Possède également une méthode calculer l'état suivant

class Automaton {
    private:
        struct Range {
            unsigned int a;
            unsigned int b;
        };

       std::string serialize();

       Automaton() = delete;

    public:

        /// Nombre de voisins qui comptent pour l'état suivant
        unsigned int n;
        /// Dimension: 1D ou 2D
        unsigned int dim;

        /// Etat suivant par défaut
        char defaultNext;

        /// Arbre des positions d'états
        RuleBst* ruleBst;
        /// Vecteur d'intervalles donnant la vie
        std::vector<Range> ruleNbNeighbLife;
        /// Vecteur d'intervalles donnant la mort
        std::vector<Range> ruleNbNeighbDeath;vie
        /// Vecteur d'intervalles donnant un état identique
        std::vector<Range> ruleNbNeighbSame;

        /// Constructeur pour créer un nouvel automate
        Automaton(unsigned int nb, unsigned int dim, char dn) :
            n(nb), dim(dim), defaultNext(dn), ruleNbNeighbDeath() {
            ruleBst = new RuleBst();
        }

        /// Constructeur à partir d'une base de donnees SQL
        Automaton(const unsigned int id, sqlite3 * db); // Constructor from SQL database
        /// Constructeur à partir d'une Qstring
        Automaton(QString const& fileName);

        /// Calcul l'etat suivant a partir de la string des voisins
        char next(std::string s);

        /// Insere une regle de position dans l'arbre binaire
        void insertPositionRule(std::vector<bool> v, char c) {
            if (v.size() != n) throw std::invalid_argument("wrong size");
            ruleBst->insert(v, c);
            std::cout << serialize() << std::endl;
        }

        /// Insere une regle sur le nombre de voisins de type donne
        void insertRuleNbInto(unsigned int a, unsigned int b, char c) {
            if (c == 'a') insertRangeInto(ruleNbNeighbLife, a, b);
            else if (c == 'd') insertRangeInto(ruleNbNeighbDeath, a, b); 
            else if (c == 's') insertRangeInto(ruleNbNeighbSame, a, b); 
        }
        /// Insere un intervalle dans la collection specifiee
        void insertRangeInto(std::vector<Range>& coll, unsigned int a, unsigned int b);


        /// Serialise les regles de voisins en une std::string
        std::string serializeNbRules();
        /// Deserialise les regles de voisins a partir d'une std::string
        void deserializeNbRules(const std::string& s);


        /// Deserialise a partir d'une std::string
        void deserialize(const std::string& s);

        unsigned int save(const QString& name, sqlite3 * db); // save to DB

        void exportToFile(QString& name);

        /// Getters & Setters
        inline unsigned int getN() { return n;}
        inline unsigned int getDim() { return dim; }

};


#endif // AUTOMATON_H
