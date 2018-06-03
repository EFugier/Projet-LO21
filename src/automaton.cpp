#include "Automaton.h"
#include <stdexcept>

char Automaton::next(std::string s) {
    if (s.length() != n) throw std::invalid_argument("wrong string size");
    ruleBst->reset();
    bool inTree = true;
    unsigned int nb_neigh = 0;

    char state;
    for(const char& c : s) { // neighbour counting + tree search
        if (c == '1') nb_neigh++;

        state = ruleBst->next(c); 
        if (inTree && state == 'n') { // not in the tree anymore
            ruleBst->reset();
            inTree = false;
        }
        else if (state != c) { // leaf
            return state;
        }
    }

    for(const Range& r : ruleNbNeighbLife) { // Life number rules
        if (r.a <= nb_neigh && nb_neigh <= r.b) return '1'; 
    }
    for(const Range& r : ruleNbNeighbDeath) { // Death number rules
        if (r.a <= nb_neigh && nb_neigh <= r.b) return '0'; 
    }
}


void Automaton::insertRangeInto(std::vector<Range>& coll, unsigned int a, unsigned int b) {
    bool done = false;
    // Easy fusion
    for(Range& r : coll) { // Death number rules
        if (r.a <= a && b <= r.b) break;
        if (a <= r.a && r.b <= b) {
            r.a = a; r.b = b;
            done = true;
            break;
        }
        if (a <= r.a && b <= r.b) {
            r.a = a;
            done = true;
            break;
        }
        if (r.a <= a && r.b <= b) {
            r.b = b;
            done = true;
            break;
        }
    }
    if (!done) {
        Range r = {a, b};        
        coll.push_back(r);
    }
}


std::string Automaton::serializeNbRules() {
    std::string seq = "";
    for(Range& r : ruleNbNeighbLife) seq += std::to_string(r.a)+","+std::to_string(r.b)+",";
    seq.push_back(';');
    for(Range& r : ruleNbNeighbDeath) seq += std::to_string(r.a)+","+std::to_string(r.b)+",";

    return seq;
}


void Automaton::deserializeNbRules(const std::string& s) {
    ruleNbNeighbLife.clear();

    std::string a = "";
    std::string b = "";
    bool life = true;  // save in nbLife

    bool isa = true, isb = false;
    for(const char& c : s) {
        if (c == ',' && isa) {
            isa = false;
            isb = true;
            continue;
        }
        if (c == ',' && isb) { // end of a range
            isa = true;
            isb = false;
            
            // append the new range
            if (life) ruleNbNeighbLife.push_back(Range {std::stoi(a), std::stoi(b)});
            else ruleNbNeighbDeath.push_back(Range {std::stoi(a), std::stoi(b)});

            // reset a and b
            a.clear(); b.clear();
            continue;
        }
        if (c == ';') { // start of ruleNbNeighbDeath
            isa = true;
            isb = false;
            life = false;
            continue;
        }

        // append the current char to the right string
        if (isa) a.push_back(c);
        if (isb) b.push_back(c);
    }
}




