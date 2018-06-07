#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "./utilities/rulebst.h"


// TODO
// Improve the insertRangeInto function

class Automaton {
    private:
        Automaton() = delete;
        struct Range {
            unsigned int a;
            unsigned int b;
        };
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
        char next(std::string s);

        void insertSpecialRule(std::string s, char c);

        void insertRuleNbLife(unsigned int a, unsigned int b) { insertRangeInto(ruleNbNeighbLife, a, b); }
        void insertRuleNbDeath(unsigned int a, unsigned int b) { insertRangeInto(ruleNbNeighbDeath, a, b); }
        void insertRangeInto(std::vector<Range>& coll, unsigned int a, unsigned int b);
        std::string serializeNbRules();
        void deserializeNbRules(const std::string& s);

        // getters & setters
        inline unsigned int getN() { return n;}
        inline unsigned int getDim() { return dim; }


};


#endif // AUTOMATON_H
