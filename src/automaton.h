#ifndef AUTOMATON_H
#define AUTOMATON_H

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

class Automaton {
    private:
        struct Range {
            unsigned int a;
            unsigned int b;
        };

       std::string serialize();

    public:

        unsigned int n;
        unsigned int dim;
        std::unordered_map<std::string, char> specialRules;

    public:
        char defaultNext;

        RuleBst* ruleBst;
        std::vector<Range> ruleNbNeighbLife;
        std::vector<Range> ruleNbNeighbDeath;

        Automaton(unsigned int n, unsigned int dim, char dn) :
            n(n), dim(dim), defaultNext(dn), ruleBst() {}

        Automaton(const unsigned int id, sqlite3 * db); // Constructor from SQL database
        Automaton(QString const& fileName);
        Automaton() {}

        char next(std::string s);

        void insertSpecialRule(std::string s, char c);

        void insertRuleNbLife(unsigned int a, unsigned int b) { insertRangeInto(ruleNbNeighbLife, a, b); }
        void insertRuleNbDeath(unsigned int a, unsigned int b) { insertRangeInto(ruleNbNeighbDeath, a, b); }
        void insertRangeInto(std::vector<Range>& coll, unsigned int a, unsigned int b);
        std::string serializeNbRules();
        void deserializeNbRules(const std::string& s);

        void deserialize(const std::string& s);

        unsigned int save(const std::string& name, sqlite3 * db); // save to DB

        void exportToFile(QString& name);

        // getters & setters
        inline unsigned int getN() { return n;}
        inline unsigned int getDim() { return dim;}

};


#endif // AUTOMATON_H
