#include "state.h"

// Static callback (for the database) :

static int callback_get_id(void *ptr, int count, char **data, char **columns) {
    Uint * intPtr = static_cast<Uint *>(ptr);
    *intPtr = atoi(data[0]);
    return 0;
}

static int callback_load_state(void *ptr, int count, char **data, char **columns) {
    State * stPtr = static_cast<State *>(ptr);
    stPtr->nrow = atoi(data[0]);
    stPtr->ncol = atoi(data[1]);
    stPtr->loadStateFromString(data[2]);
    return 0;
}

// Constructors :

State::State(State const& old) : QObject(0), nrow(old.getNrow()), ncol(old.getNcol()) {
    state = Vec(old.getState());
}

State::State(QString const& fileName) : QObject(0) {
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) return;
    QTextStream in(&file);
    QString value = in.readLine();
    QString::iterator it = value.begin();
    if (*it != 'r') return;
    it++;
    std::ostringstream nrowStm, ncolStm;
    for (;*it != 'c'; it++) nrowStm << (*it).toLatin1();
    nrow = std::stoi(nrowStm.str());
    it++;
    for (;*it != 'v'; it++) ncolStm << (*it).toLatin1();
    ncol = std::stoi(ncolStm.str());
    it++;
    state = Vec();
    for(;it != value.end(); it++) state.push_back(*it == '1');
}

State::State(const Uint id, sqlite3 * db) : QObject(0) {
    state = Vec();
    std::ostringstream req1, req2;
    req1 << "SELECT nrow, ncol, value FROM states WHERE id = " << id;
    sqlite3_exec(db, req1.str().c_str(), callback_load_state, this, nullptr);
    req2 << "UPDATE states SET lastUse = date('now') WHERE id = " << id;
    sqlite3_exec(db, req2.str().c_str(), nullptr, nullptr, nullptr);
}

State::State(const Uint dimension1d) : QObject(0), nrow(1), ncol(dimension1d)
{
    state = Vec(dimension1d);
    randomState();
}

State::State(const Uint rowDimension, const Uint colDimension) : QObject(0), nrow(rowDimension), ncol(colDimension)
{
    state = Vec(rowDimension*colDimension);
    randomState();
}

State::State(const Uint dimension1d, Vec initState) : QObject(0), state(initState), nrow(1), ncol(dimension1d) {}

State::State(const Uint rowDimension, const Uint colDimension, Vec initState) : QObject(0), state(initState), nrow(rowDimension), ncol(colDimension) {}

// Getters :

Uint State::getNrow() const {
    return nrow;
}

Uint State::getNcol() const {
    return ncol;
}

const Vec& State::getState() const {
    return state;
}

// Setter :

void State::setState(Vec& v) {
    state.swap(v);
    emit valueChanged(state);
}

// Long term saves :

Uint State::save(const QString& name, sqlite3 * db) const {
    std::ostringstream flux;
    flux << "INSERT INTO states(name, nrow, ncol, value, lastUse) VALUES('";
    flux << name.toStdString() << "', " << nrow << ", " << ncol << ", '" << toString().toStdString() << "', date('now'))";
    sqlite3_exec(db, flux.str().c_str(), nullptr,nullptr,nullptr);
    Uint * ptr = new Uint;
    sqlite3_exec(db, "SELECT id FROM states WHERE id=@@Identity", callback_get_id, ptr, nullptr);
    return *ptr;
}

void State::exportToFile(QString& name) const {
    QFile file(name);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << 'r' << nrow << "c" << ncol << "v" << QString(toString());
}

// Private methods :

void State::randomState() {
    srand(time(0));
    Vec::iterator it;
    for (it = state.begin(); it != state.end(); ++it) *it = rand()%2;
}

void State::loadStateFromString(char *str) {
    while (*str != '\0')
        state.push_back(*(str++) == '1');
}

std::vector<std::string> State::stackOfNb(Uint n) const { 
    int s_nrow = static_cast<int>(nrow);
    int s_ncol = static_cast<int>(ncol);
    // If n is the number of neighbours, deg is the degree (9 neighbours <=> 1 deg for instance)
    std::vector<std::string> s;

    if (nrow == 1) {
        int deg = static_cast<int>((n-1)/2);
        for (int ind(0); ind<s_ncol; ind++) {
            std::ostringstream flux;
            for (int i(static_cast<int>(ind-deg)) ; i <= static_cast<int>(ind+deg) ; i++)
                flux << (state[mod(i,ncol)] ? 1 : 0);
            s.push_back(flux.str());
        }
        return s;
    }

    int deg = static_cast<int>((std::sqrt(n)-1)/2);
    for (int ind(0); ind<s_nrow*s_ncol; ind++) {
        std::ostringstream flux;
        for (int i(static_cast<int>(ind / s_ncol) - deg) ; i <= static_cast<int>(ind / s_ncol) + deg ; i++)
            for (int j(mod(ind, s_ncol) - deg) ; j <= mod(ind, s_ncol) + deg ; j++)
                flux << (state[mod(i,s_nrow)*s_ncol+mod(j,s_ncol)] ? 1 : 0);
        s.push_back(flux.str());
    }
    return s;
    /* State is a 1D vector.
     * [i%iMax][j%jMax] (for a 2D tab) is similar to [(i%nrow)*ncol+j%ncol] for a 1D vector
     * deg is the considered degree of
     * */
}

QString State::toString() const {
    std::ostringstream flux;
    Vec::const_iterator it = state.begin();
    for(; it != state.end(); it++)
        flux << ((*it) ? 1 : 0);
    return QString().fromStdString(flux.str());
}

int mod(int x, int m) {
    return (x%m + m)%m;
}
