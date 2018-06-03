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
    public:
        struct Range {
            unsigned int a;
            unsigned int b;
        };

        int n;
        char defaultNext;
        std::unordered_map<std::string, char> specialRules;
        RuleBst* ruleBst;
        std::vector<Range> ruleNbNeighbLife;
        std::vector<Range> ruleNbNeighbDeath;

        Automaton(int n) : n(n), ruleBst() {}
        char next(std::string s);

        void insertSpecialRule(std::string s, char c);

        void insertRuleNbLife(unsigned int a, unsigned int b) { insertRangeInto(ruleNbNeighbLife, a, b); }
        void insertRuleNbDeath(unsigned int a, unsigned int b) { insertRangeInto(ruleNbNeighbDeath, a, b); }
        void insertRangeInto(std::vector<Range>& coll, unsigned int a, unsigned int b);
        std::string serializeNbRules();
        void deserializeNbRules(const std::string& s);

};


#endif // AUTOMATON_H
