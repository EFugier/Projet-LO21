#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QString>
#include <stack>
#include <cmath>
#include "utilities/sqlite3.h"

int mod(int x, int m);

typedef std::vector<bool> Vec;
typedef unsigned int Uint;

static int callback_get_id(void *ptr, int count, char **data, char **columns);
static int callback_load_state(void *ptr, int count, char **data, char **columns);

class State : public QObject {
    Q_OBJECT
private:
    // The callback functions are used to deal with SQL "SELECT ..." requests
    friend int callback_load_state(void *ptr, int count, char **data, char **columns);

    // Attributes :
    Vec state;
    Uint nrow;
    Uint ncol;

    // Private methods :
    void loadStateFromString(char*str); // load a state from a string of 0 and 1

public:
    QString toString() const; // Convert the vector of booleans to a string // IS WORKING

    // Constructors :
    State(State const& old); // Copy constructor // IS WORKING
    State(QString const& fileName); // Constructor from file // IS WORKING
    State(const Uint id, sqlite3 * db); // Constructor from SQL database // IS WORKING
    State(const Uint dimension1d); // Constructor for random 1D state
    State(const Uint dimension1d, Vec v); // Constructor for specific 1D state
    State(const Uint rowDimension, const Uint colDimension); // Constructor for random 2D // IS WORKING
    State(const Uint rowDimension, const Uint colDimension, Vec v); // Constructor for specific 2D state

    // getters :
    Uint getNrow() const; // nrow getter // IS WORKING
    Uint getNcol() const; // ncol getter // IS WORKING
    const Vec& getState() const; // state getter // IS WORKING

    // setter :
    void setState(Vec& v); // state setter

    void emitSignal() {
        emit valueChanged(state);
    }

    void randomState(); // Create a random nrow*ncol vector of booleans // IS WORKING

    // Long term saves :
    Uint save(const QString& name, sqlite3 * db) const; // save to DB // IS WORKING
    void exportToFile(QString const& name) const; // export to file // IS WORKING

    std::vector<std::string> stackOfNb(Uint n) const; // IS WORKING
signals:
    void valueChanged(std::vector<bool>&);
};

#endif // STATE_H
