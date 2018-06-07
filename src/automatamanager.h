#ifndef AUTOMATAMANAGER_H
#define AUTOMATAMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include "utilities/sqlite3.h"
#include "state.h"
#include "automaton.h"
#include <QString>

enum dim {d1, d2};
typedef std::map<const unsigned int, const std::string> Map;
static int select_callback_automata(void *ptr, int count, char **data, char **columns);
static int select_callback_states(void *ptr, int count, char **data, char **columns);
static int callback_load_automata(void *ptr, int count, char **data, char **columns);
static int callback_get_id_automaton(void *ptr, int count, char **data, char **columns);


class AutomataManager {
// Friend :
    friend int callback_load_automata(void *ptr, int count, char **data, char **columns);

// Static :
    static AutomataManager * instance;

// Attributes :
    Automaton * runningAutomaton;
    State * initialState;
    State * currentState;
    sqlite3 * db;

// Methods :
    void connectToDb();
    void createDb() const;

// Constructor :
    AutomataManager();

public:
    // Design pattern singleton :
    static AutomataManager& getInstance(); // IS WORKING

    // An internal class to store the description of an automaton from the database
    class AutomatonDescription {
        unsigned int id;
        std::string name;
        dim dimension;
    public:
        AutomatonDescription(unsigned int i, std::string n, dim d);
        unsigned int getId() const;
        const std::string& getName() const;
        dim getDimension() const;
    };



// Automata management :
    /* Return a vector of AutomatonDescription, each one containing
     * the id, the name and the dimension of the automaton */
     std::vector<const AutomataManager::AutomatonDescription> * getArrayOfAutomata() const;

    /* Return a map of the saved states with their id as the key
     * and their name as the value */
     Map * getArrayOfStates() const; // IS WORKING

    /* Create an automaton from a specific set of rules
     * indicated by the id i of the automaton */
     Automaton * selectedAutomaton(unsigned int const i);

    /* Create an empty automaton
     * */
     Automaton * AutomataManager::createAutomaton(unsigned int deg, dim d, char def = 's');



      void selectedState(unsigned int const i); // IS WORKING
      // Set the initial state from the DB via the ID of the state

      void selectedState(State& initial); // IS WORKING
      void selectedState(QString& nameFile); // IS WORKING

      unsigned int saveInitialState(std::string const& name) const; // IS WORKING
      unsigned int saveCurrentState(std::string const& name) const; // IS WORKING

      unsigned int saveAutomaton(std::string const& name) const; // IS WORKING

      void exportInitialState(QFile * file) const; // IS WORKING
      void exportCurrentState(QFile * file) const; // IS WORKING
      void exportAutomaton(QFile *file) const;

      void deleteAutomaton(unsigned int i) const;
      void deleteState(unsigned int i) const; // IS WORKING

      void next();
      State* getState() { return initialState; }
      ~AutomataManager();
};

#endif // AUTOMATAMANAGER_H
