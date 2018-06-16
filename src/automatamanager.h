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
#include <QTimer>
#include <QObject>
#include <QTimer>

enum dim {d1, d2};
typedef std::map<const unsigned int, const QString> Map;
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
    QTimer * timer;

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
        QString name;
        dim dimension;
    public:
        AutomatonDescription(unsigned int i, QString n, dim d);
        unsigned int getId() const;
        const QString& getName() const;
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
     void selectedAutomaton(unsigned int const i);
     void selectedAutomaton(QString& nameFile);
     void selectedAutomaton() { runningAutomaton = nullptr; }
    /* Create an empty automaton
     * */
     void createAutomaton(unsigned int deg, dim d, char def);
     void deleteAutomaton();

      void selectedState(unsigned int const i); // IS WORKING
      // Set the initial state from the DB via the ID of the state

      void selectedState(State const& initial); // IS WORKING
      void selectedState(QString& nameFile); // IS WORKING

      unsigned int saveInitialState(QString const& name) const; // IS WORKING
      unsigned int saveCurrentState(QString const& name) const; // IS WORKING

      unsigned int saveAutomaton(QString const& name) const; // IS WORKING

      void exportInitialState(QString const& name) const; // IS WORKING
      void exportCurrentState(QString const& name) const; // IS WORKING
      void exportAutomaton(QString const& name) const;

      void deleteAutomata() const;
      void deleteStates() const;

      void next();
      Automaton& getAutomaton() const { return *runningAutomaton; }
      Automaton * getPtrAutomaton() const { return runningAutomaton; }
      ~AutomataManager();
      State* getState() { return currentState; }
      void setTimer(unsigned int ms);
};

#endif // AUTOMATAMANAGER_H
