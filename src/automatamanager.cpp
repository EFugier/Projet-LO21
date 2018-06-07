#include "automatamanager.h".h"

AutomataManager* AutomataManager::instance = nullptr;

// Constructor and getters for the inner class AutomataDescription :

AutomataManager::AutomataDescription::AutomataDescription(unsigned int i, std::string n, dim d) : id(i), name(n), dimension(d) {}

unsigned int AutomataManager::AutomataDescription::getId() const {
    return id;
}

const std::string& AutomataManager::AutomataDescription::getName() const {
    return name;
}

dim AutomataManager::AutomataDescription::getDimension() const {
    return dimension;
}

// Constructor, destructor and getIstance (because of the singleton pattern) :

AutomataManager::AutomataManager() : runningAutomata(0), currentState(0), initialState(0), db(0)
{
    connectToDb();
}

AutomataManager::~AutomataManager() {
    delete initialState;
    delete currentState;
    delete runningAutomata;
    sqlite3_close(db);
}

AutomataManager& AutomataManager::getInstance() {
    if (!instance) instance = new AutomataManager();
    return *instance;
}

// Connexion to the SQL database :

void AutomataManager::connectToDb() {
    try {
       if(sqlite3_open_v2("db", &db, SQLITE_OPEN_READWRITE, nullptr)) throw nullptr;
    }
    catch(void*) {
        std::cout<<"The database did not exist. It has been created."<<std::endl;
        sqlite3_close(db);
        sqlite3_open_v2("db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
        createDb();
    }
}

void AutomataManager::createDb() const {
    sqlite3_exec(db, "CREATE TABLE 'states' ('id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'name' TEXT NOT NULL, 'nrow' INTEGER, 'ncol' INTEGER NOT NULL, 'value' TEXT, 'lastUse'  DATETIME NOT NULL  ); CREATE TABLE 'automata' ('id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'name' TEXT NOT NULL, 'is2d' BOOLEAN NOT NULL, 'value' TEXT NOT NULL, 'lastUse' DATETIME NOT NULL)", nullptr, nullptr, nullptr);
}

// SELECT from the database :

std::vector<const AutomataManager::AutomataDescription> AutomataManager::getArrayOfAutomata() const {
    std::vector<const AutomataManager::AutomataDescription> v;
    sqlite3_exec(db, "SELECT id, name, is2d FROM automata ORDER BY lastUse DESC",select_callback_automata,&v,nullptr);
    return v;
}

static int select_callback_automata(void *ptr, int count, char **data, char **columns) {
    std::vector<const AutomataManager::AutomataDescription> * vecPtr = static_cast<std::vector<const AutomataManager::AutomataDescription>*>(ptr);
    AutomataManager::AutomataDescription a(atoi(data[0]),std::string(data[1]),((data[2]) ? d2 : d1));
    vecPtr->push_back(a);
    return 0;
}

Map AutomataManager::getArrayOfStates() const {
    Map v;
    sqlite3_exec(db, "SELECT id, name FROM states ORDER BY lastUse DESC",select_callback_states,&v,nullptr);
    return v;
}

static int select_callback_states(void *ptr, int count, char **data, char **columns) {
    Map * mapPtr = static_cast<Map*>(ptr);
    mapPtr->insert(std::pair<const unsigned int, const std::string>(atoi(data[0]), std::string(data[1])));
    return 0;
}

// Save to the database :

unsigned int AutomataManager::saveInitialState(std::string const& name) const {
    return initialState->save(name, db);
}

unsigned int AutomataManager::saveCurrentState(std::string const& name) const {
    return currentState->save(name, db);
}

// Delete from database

void AutomataManager::deleteAutomaton(unsigned int i) const {
    std::ostringstream req;
    req << "DELETE FROM automata WHERE id = " << i;
    sqlite3_exec(db, req.str().c_str(), nullptr,nullptr,nullptr);
}

void AutomataManager::deleteState(unsigned int i) const {
    std::ostringstream req;
    req << "DELETE FROM states WHERE id = " << i;
    sqlite3_exec(db, req.str().c_str(), nullptr,nullptr,nullptr);
}

// Load a state

void AutomataManager::selectedState(unsigned int const i) {
    initialState = new State(i, db);
    currentState = new State(*initialState);
}

void AutomataManager::selectedState(State& initial) {
    initialState = new State(initial);
    currentState = new State(initial);
}

void AutomataManager::selectedState(QString& nameFile) {
    initialState = new State(nameFile);
    currentState = new State(*initialState);
}

// Load an automata

Automaton * AutomataManager::selectedAutomata(unsigned int const i) {
    std::ostringstream req1, req2;
    req1 << "SELECT value FROM automata WHERE id = " << i;
    sqlite3_exec(db, req1.str().c_str(), callback_load_automata, this, nullptr);
    req2 << "UPDATE automata SET lastUse = now() WHERE id = " << i;
    sqlite3_exec(db, req2.str().c_str(), nullptr, nullptr, nullptr);
    return runningAutomata;
}

static int callback_load_automata(void *ptr, int count, char **data, char **columns) {
    AutomataManager * amPtr = static_cast<AutomataManager*>(ptr);
    amPtr->runningAutomata = new Automaton(std::string(data[0]));
    return 0;
}

Automaton * AutomataManager::createAutomaton() {
    runningAutomata = new Automaton();
    return runningAutomata;
}

// Save state to file

void AutomataManager::exportInitialState(QFile *file) const {
    initialState->exportToFile(file);
}

void AutomataManager::exportCurrentState(QFile *file) const {
    currentState->exportToFile(file);
}

// Run the automaton

void AutomataManager::next() {
//    std::vector<std::string> s = currentState->stackOfNb(runningAutomata->getN());
    std::vector<std::string> s = currentState->stackOfNb(25);

    std::vector<bool> v;
    int i = -1;
    for(std::vector<std::string>::iterator it = s.begin(); it != s.end(); it++) { i++;
        std::cout << "INDEX " << i << " : " << *it << std::endl; }
 //       v.push_back((runningAutomata->next(*it) == '1') ? true : false);
 //   currentState->setState(v);
}

