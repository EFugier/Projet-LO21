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

enum dim {d1, d2}; /// Enum ayant 2 valeurs possibles : d1 (représentant les automates 1D), d2 (représentant les automates 2D)
typedef std::map<const unsigned int, const QString> Map;

/** Les fonctions de callback sont des prototypes à implémenter donnés par la librairie sqlite.
 * Elles permettent notamment de gérer les résultats des requêtes SQL SELECT. */
static int select_callback_automata(void *ptr, int count, char **data, char **columns);
static int select_callback_states(void *ptr, int count, char **data, char **columns);
static int callback_load_automata(void *ptr, int count, char **data, char **columns);
static int callback_get_id_automaton(void *ptr, int count, char **data, char **columns);

/// \class AutomataManager
class AutomataManager {
    friend int callback_load_automata(void *ptr, int count, char **data, char **columns);

    /// Instance unique de l'automate (design pattern Singleton)
    static AutomataManager * instance;

    Automaton * runningAutomaton; /// Pointeur vers l'automate choisi
    State * initialState; /// Poointeur vers l'état initial
    State * currentState;   /// Pointeur vers l'état courant
    sqlite3 * db;   /// Pointeur de sqlite3 pour la base de données
    QTimer * timer; /// Pointeur de timer utilisé pour appeler la fonction next() de manière continue (mode continu)

    /** \fn void connectToDb()
     * \brief Méthode pour se connecter à la BDD SQLite, appelée à la construcion
     */
    void connectToDb();

    /** \fn void connectToDb() const
     * \brief Méthode pour créer la base de données si cette dernière n'existe pas (première utilisation)
     */
    void createDb() const;

    /** \fn AutomataManager()
     * \brief Constructeur privé (design pattern Singleton)
     */
    AutomataManager();

public:
    /** \fn static AutomataManager& getInstance()
     * \brief Méthode statique renvoyant l'instance statique de AutomataManager (il y a création si l'instance est null)
     * \return Référence de l'instance statique d'AutomataManager
    */
    static AutomataManager& getInstance();

    /** \class AutomatonDescription
     * \brief Classe interne permettant de stocker les informations des automates venus de la BDD
     */
    class AutomatonDescription {
        unsigned int id; /// L'id de l'automate dans la BDD
        QString name;   /// Le nom de l'automate
        dim dimension;  /// La dimension de l'automate
    public:
        AutomatonDescription(unsigned int i, QString n, dim d);
        unsigned int getId() const;
        const QString& getName() const;
        dim getDimension() const;
    };

    /**
      * \fn std::vector<const AutomataManager::AutomatonDescription> * getArrayOfAutomata() const
      * \brief Permet d'obtenir les automates stockés dans la BDD
      * \return Retourne un pointeur de vecteur d'AutomatonDescription
      */
     std::vector<const AutomataManager::AutomatonDescription> * getArrayOfAutomata() const;

     /**
       * \fn Map * getArrayOfStates() const
       * \brief Permet d'obtenir les états stockés dans la BDD
       * \return Retourne un pointeur de map (id dans la BDD - nom de l'état)
       */
     Map * getArrayOfStates() const;

     /**
      * \fn void selectedAutomaton(unsigned int const i);
      * \brief Permet de choisir l'état à utiliser à partir de la BDD
      * @param i est l'id de l'état dans la BDD
      */
     void selectedAutomaton(unsigned int const i);

     /**
      * \fn void selectedAutomaton(QString& nameFile);
      * \brief Permet de choisir l'état à utiliser à partir d'un fichier
      * @param nameFile est le pathname du fichier à importer
      */
     void selectedAutomaton(QString& nameFile);

     void selectedAutomaton() { runningAutomaton = nullptr; }

     /**
      * @fn void createAutomaton(unsigned int deg, dim d, char def)
      * @brief Permet de créer un automate vide (sans règle)
      * @param deg est le degré de voisinage à considérer
      * @param d est la dimension de l'automate
      * @param def est la valeur par défaut de l'automate
      */
     void createAutomaton(unsigned int deg, dim d, char def);

     /**
      * @fn void deleteAutomaton()
      * @brief Supprime l'automate courant
      */
     void deleteAutomaton();

     /**
       * @fn void selectedState(unsigned int const i)
       * @brief Permet de choisir un état initial à partir de la BDD
       * @param i est l'id de l'état dans la BDD
       */
      void selectedState(unsigned int const i);

      /**
       * @fn void selectedState(State const& initial)
       * @brief Permet de choisir un état initial à partir d'un constructeur de State
       * @param initial représente les valeurs de l'état initial
       */
      void selectedState(State const& initial);

      /**
       * @fn void selectedState(QString& nameFile)
       * @brief Permet de choisir un état initial à partir d'un fichier
       * @param nameFile est le pathname du fichier à importer
       */
      void selectedState(QString& nameFile);

      /**
       * @fn unsigned int saveInitialState(QString const& name) const
       * @brief Sauvegarde l'état intial dans la BDD
       * @param name est le nom à donner à l'état
       * @return Retourne l'ID dans la BDD de l'état nouvellement stocké
       */
      unsigned int saveInitialState(QString const& name) const;

      /**
       * @fn unsigned int saveCurrentState(QString const& name) const
       * @brief Sauvegarde l'état courant dans la BDD
       * @param name est le nom à donner à l'état
       * @return Retourne l'ID dans la BDD de l'état nouvellement stocké
       */
      unsigned int saveCurrentState(QString const& name) const;

      /**
       * @fn unsigned int saveAutomaton(QString const& name) const
       * @brief Sauvegarde l'automate courant dans la BDD
       * @param name est le nom à donner à l'automate
       * @return Retourne l'ID dans la BDD de l'automate nouvellement stocké
       */
      unsigned int saveAutomaton(QString const& name) const;

      /**
       * @fn void exportInitialState(QString const& name) const
       * @brief Exporte l'état initial dans un fichier
       * @param name est le pathname du fichier à créer
       */
      void exportInitialState(QString const& name) const;

      /**
       * @fn void exportCurrentState(QString const& name) const
       * @brief Exporte l'état courant dans un fichier
       * @param name est le pathname du fichier à créer
       */
      void exportCurrentState(QString const& name) const;

      /**
       * @fn void exportAutomaton(QString const& name) const
       * @brief Exporte l'automate courant dans un fichier
       * @param name est le pathname du fichier à créer
       */
      void exportAutomaton(QString const& name) const;

      /**
       * @fn void deleteAutomata() const
       * @brief Vide la table des automates de la BDD
       */
      void deleteAutomata() const;

      /**
       * @fn void deleteStates() const
       * @brief Vide la table des états de la BDD
       */
      void deleteStates() const;

      /**
       * @fn void next()
       * @brief Passe l'état courant à l'état suivant en fonction de l'automate courant
       */
      void next();

      /**
       * @fn void setTimer(unsigned int ms)
       * @brief Lance ou arrête le timer qui va mettre à jour l'état en continu
       * @param ms est le nombre de millisecondes séparant chaque mise-à-jour (ou 0 si on souhaite arrêter le timer)
       */
      void setTimer(unsigned int ms);

      Automaton& getAutomaton() const { return *runningAutomaton; }
      Automaton * getPtrAutomaton() const { return runningAutomaton; }
      State* getState() { return currentState; }

      virtual ~AutomataManager();

};

#endif // AUTOMATAMANAGER_H
