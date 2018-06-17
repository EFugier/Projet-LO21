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

/// \class State
class State : public QObject {
    Q_OBJECT
private:
    friend int callback_load_state(void *ptr, int count, char **data, char **columns);

    Vec state; /// state est le vecteur de booléens stockant les valeurs de l'état
    Uint nrow; /// nrow est le nombre de lignes de la grille
    Uint ncol; /// ncol est le nombre de colonnes de la grille

    /**
     * @fn void loadStateFromString(char *str)
     * @brief Méthode de désérialisation d'un état
     * @param str est une chaine issue de la sérialisation d'un état
     */
    void loadStateFromString(char*str);

public:
    /**
     * @fn QString toString() const
     * @brief méthode de sérialisation du vecteur state
     * @return Retourne un QString représentant avec des 0 et des 1 le vecteur state
     */
    QString toString() const;

    /**
     * @fn State(State const& old)
     * @brief Constructeur de recopie
     * @param old est l'état que l'on souhaite recopier
     */
    State(State const& old);

    /**
     * @fn State(QString const& fileName)
     * @brief Constructeur à partir d'un fichier
     * @param fileName est le pathname du fichier à importer
     */
    State(QString const& fileName);

    /**
     * @fn State(const Uint id, sqlite3 * db)
     * @brief Constructeur à partir d''un automate de la BDD
     * @param id est l'id de l'état dans la BDD
     * @param db est le pointeur de sqlite représentant la BDD
     */
    State(const Uint id, sqlite3 * db);

    /**
     * @fn State(const Uint dimension1d)
     * @brief Constructeur d'état 1D aléatoire
     * @param dimension1d est la taille (le nombre de colonnes) de l'état
     */
    State(const Uint dimension1d);

    /**
     * @fn State(const Uint dimension1d, Vec v)
     * @brief Constructeur d'état 1D non-aléatoire
     * @param dimension1d est la taille (le nombre de colonnes) de l'état
     * @param v est le vecteur de booléens à mettre dans state
     */
    State(const Uint dimension1d, Vec v);

    /**
     * @fn State(const Uint rowDimension, const Uint colDimension)
     * @brief Constructeur d'état 2D aléatoire
     * @param rowDimension est la taille verticale (le nombre de lignes) de l'état
     * @param colDimension est la taille horizontale (le nombre de colonnes) de l'état
     */
    State(const Uint rowDimension, const Uint colDimension);

    /**
     * @fn State(const Uint rowDimension, const Uint colDimension, Vec v)
     * @brief Constructeur d'état 2D non-aléatoire
     * @param rowDimension est la taille verticale (le nombre de lignes) de l'état
     * @param colDimension est la taille horizontale (le nombre de colonnes) de l'état
     * @param v est le vecteur de booléens à mettre dans state
     */
    State(const Uint rowDimension, const Uint colDimension, Vec v);

    Uint getNrow() const;
    Uint getNcol() const;
    const Vec& getState() const;

    void setState(Vec& v);

    /**
     * void emitSignal()
     * @brief Permet d'émettre le signal valueChangd, envoyant une référence de state
     */
    void emitSignal() {
        emit valueChanged(state);
    }

    /**
     * @fn void randomState()
     * @brief Rempli state de manière aléatoire
     */
    void randomState();

    /**
     * @fn Uint save(const QString& name, sqlite3 * db) const
     * @brief Sauvegarde l'état dans la BDD
     * @param name est le nom à mettre dans la BDD
     * @param db est le pointeur représentant la BDD
     * @return Retourne l'ID dans la BDD de l'état nouvellement crée
     */
    Uint save(const QString& name, sqlite3 * db) const;

    /**
     * @fn void exportToFile(QString const& name) const
     * @brief Exporte l'état dans un fichier
     * @param name est le pathname du fichier à créer
     */
    void exportToFile(QString const& name) const;

    /**
     * @fn std::vector<std::string> stackOfNb(Uint n) const
     * @brief Permet d'envoyer les voisins significatifs de chaque case
     * @param n est le nombre de voisins à prendre en considération
     * @return Retourne un vecteur de strings où chaque string représente les voisins significatifs d'une cellule de l'état
     */
    std::vector<std::string> stackOfNb(Uint n) const;

signals:

    /**
     * @fn void valueChanged(std::vector<bool>&)
     * @brief Signal qui sera envoyé à la vue lorsque state est modifié
     * @param On envoi la référence de state
     */
    void valueChanged(std::vector<bool>&);
};

#endif // STATE_H
