#include "automatamanager.h"

AutomataManager* AutomataManager::instance = nullptr;

// Constructor and getters for the inner class AutomatonDescription :

AutomataManager::AutomatonDescription::AutomatonDescription(unsigned int i, QString n, dim d) : id(i), name(n), dimension(d) {}

unsigned int AutomataManager::AutomatonDescription::getId() const {
    return id;
}

const QString& AutomataManager::AutomatonDescription::getName() const {
    return name;
}

dim AutomataManager::AutomatonDescription::getDimension() const {
    return dimension;
}

// Constructor, destructor and getIstance (because of the singleton pattern) :

AutomataManager::AutomataManager() : runningAutomaton(0), initialState(0), currentState(0), db(0)
{
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [=]() { next(); });
    connectToDb();
}

AutomataManager::~AutomataManager() {
    delete initialState;
    delete currentState;
    delete runningAutomaton;
    delete timer;
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

std::vector<const AutomataManager::AutomatonDescription> * AutomataManager::getArrayOfAutomata() const {
    std::vector<const AutomataManager::AutomatonDescription> * v = new std::vector<const AutomataManager::AutomatonDescription>();
    sqlite3_exec(db, "SELECT id, name, is2d FROM automata ORDER BY lastUse DESC",select_callback_automata,v,nullptr);
    return v;
}

static int select_callback_automata(void *ptr, int count, char **data, char **columns) {
    std::vector<const AutomataManager::AutomatonDescription> * vecPtr = static_cast<std::vector<const AutomataManager::AutomatonDescription>*>(ptr);
    AutomataManager::AutomatonDescription a(atoi(data[0]),QString(data[1]),((data[2]) ? d2 : d1));
    vecPtr->push_back(a);
    return 0;
}

Map * AutomataManager::getArrayOfStates() const {
    Map * v = new Map();
    sqlite3_exec(db, "SELECT id, name FROM states ORDER BY lastUse DESC",select_callback_states,v,nullptr);
    return v;
}

static int select_callback_states(void *ptr, int count, char **data, char **columns) {
    Map * mapPtr = static_cast<Map*>(ptr);
    mapPtr->insert(std::pair<const unsigned int, const QString>(atoi(data[0]), QString(data[1])));
    return 0;
}

// Save to the database :

unsigned int AutomataManager::saveInitialState(QString const& name) const {
    return initialState->save(name, db);
}

unsigned int AutomataManager::saveCurrentState(QString const& name) const {
    return currentState->save(name, db);
}

unsigned int AutomataManager::saveAutomaton(QString const& name) const {
    return runningAutomaton->save(name, db);
}

static int callback_get_id_automaton(void *ptr, int count, char **data, char **columns) {
    Uint * intPtr = static_cast<Uint *>(ptr);
    *intPtr = atoi(data[0]);
    return 0;
}

// Delete from database TODO

void AutomataManager::deleteAutomata() const {
    sqlite3_exec(db, "DELETE FROM automota", nullptr,nullptr,nullptr);
}

void AutomataManager::deleteStates() const {
    sqlite3_exec(db, "DELETE FROM states", nullptr,nullptr,nullptr);
}

// Load a state

void AutomataManager::selectedState(unsigned int const i) {
    initialState = new State(i, db);
    currentState = new State(*initialState);
}

void AutomataManager::selectedState(State const& initial) {
    initialState = new State(initial);
    currentState = new State(initial);
}

void AutomataManager::selectedState(QString& nameFile) {
    initialState = new State(nameFile);
    currentState = new State(*initialState);
}

// Load an automaton

void AutomataManager::selectedAutomaton(unsigned int const i) {
    runningAutomaton = new Automaton(i, db);
}
void AutomataManager::selectedAutomaton(QString& nameFile) {
    runningAutomaton = new Automaton(nameFile);
}
static int callback_load_automata(void *ptr, int count, char **data, char **columns) {
    AutomataManager * amPtr = static_cast<AutomataManager*>(ptr);
    amPtr->runningAutomaton = new Automaton();
    amPtr->runningAutomaton->deserialize(std::string(data[0]));
    return 0;
}

void AutomataManager::createAutomaton(unsigned int deg, dim d, char def = 's') {
    unsigned int n = 2*deg+1;
    runningAutomaton = new Automaton((d == d1 ? n : n*n), (d == d1 ? 1 : 2), def);
}

// Save state to file

void AutomataManager::exportInitialState(QString& name) const {
    initialState->exportToFile(name);
}

void AutomataManager::exportCurrentState(QString& name) const {
    currentState->exportToFile(name);
}

void AutomataManager::exportAutomaton(QString& name) const {
    runningAutomaton->exportToFile(name);
}

// Run the automaton

void AutomataManager::next() {
    std::vector<std::string> s = currentState->stackOfNb(runningAutomaton->getN());
    std::vector<bool> v;
    for(std::vector<std::string>::iterator it = s.begin(); it != s.end(); it++) {
       char tmp = runningAutomaton->next(*it);
       std::cout << "tmp = " << tmp << std::endl;
        v.push_back(tmp == 's' ? (*it)[(*it).size()/2] : (tmp == 'a' ? true : false));
    }

   currentState->setState(v);

}

void AutomataManager::setTimer(unsigned int ms) {
    if (timer->isActive()) timer->stop();
    if (ms) timer->start(ms);
}

