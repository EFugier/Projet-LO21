#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>
#include <iostream>
#include <unordered_map>
#include "./utilities/rulebst.h"

class Automaton {
    public:
        int n;
        char defaultNext;
        std::unordered_map<std::string, char> specialRules;
        RuleBst* ruleBst;
        unsigned int ruleNbNeighbLife[][2];
        unsigned int ruleNbNeighbDeath[][2];

        char next(std::string s);
        void insertSpecialRule(std::string s, char c);
        void insertRuleNbLife(unsigned int a, unsigned int b);
        void insertRuleNbDeath(unsigned int a, unsigned int b);
};


#endif // AUTOMATON_H
