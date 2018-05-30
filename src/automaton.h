#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include "./utilities/rulebst.h"

class Automaton {
 public:
     int n;
     char defaultNext;
     RuleBst* ruleBst;
     unsigned int ruleNbNeighbLife[][2];
     unsigned int ruleNbNeighbDeath[][2];
     
     char next(std::string s);
     void insertBstRule(std::string s);
     void insertRuleNbLife(unsigned int a, unsigned int b);
     void insertRuleNbDeath(unsigned int a, unsigned int b);
};


#endif // AUTOMATON_H
