#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H



#include"qttools.h"
#include "matrixcontroller.h"
#include "rulescontroller.h"
#include "automatamanager.h"

class AutomataParameters : public QDialog
{
    Q_OBJECT

    friend class MainController;

public:
    AutomataParameters(QWidget *parent = 0, char def ='s', dim d = d2);

private:
    QTabWidget *tabWidget;
    QLineEdit * column;
    QLineEdit * row;
    QRadioButton *dead;
    QRadioButton *alive;
    QRadioButton *same;
    QSpinBox *neighbourhood;
    QCheckBox * random;
    QDialogButtonBox *buttonBox;
};



class MainController : public QMainWindow{
     Q_OBJECT

public:
    MainController();
    /**
     * \fn MainController()
     * \brief Constructeur de la classe MainController
    */

private:
    AutomataManager& instance;
    MatrixController * view;
    AutomataParameters * param;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *subMenuAutomata;
    QMenu *subMenuGrid;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QPushButton * play;
    QPushButton * pause;
    QPushButton * randomButton;
    QCheckBox * animation;
    QDial * timer;
    QLCDNumber * lcd;
    QAction *NewAutomaton;
    QAction *ImportAutomaton;
    QAction *ImportGrid;
    QAction *OpenRecentAutomata;
    QAction *OpenRecentGrid;
    QAction *SaveAutomaton;
    QAction *SaveAutomatonAs;
    QAction *SaveInitialGrid;
    QAction *SaveCurrentGrid;
    QAction *ExportAutomaton;
    QAction *ExportCurrentGrid;
    QAction *ExportInitialGrid;
    QAction *Exit;
    QAction *NewRule;
    QAction *SetTimer;
    QAction *NextStep;
    QWidget *mainController;
    QHBoxLayout *mainLayout;
    QVBoxLayout * toolsLayout;

    void createActions();
    /**
     * \fn void createActions()
     * \brief Initialisation des différentes QActions permettant de déclencher les différentes fonctionnalités de l'application depuis les menu
    */

    void createMenus();
    /**
     * \fn void createMenus()
     * \brief Initialisation des menus File et Edit
    */

    void createToolBars();
    /**
     * \fn void createToolBars
     * \brief Initialisation des toolbars fileToolBar et editToolBar
    */

    QString openFile();
    void insertNewAction(QMenu* menu, int id, const QString& name, void (AutomataManager::*)(unsigned int const) );
    /**
     * \fn void insertNewAction(QMenu* menu, int id, const QString& name, void (AutomataManager::*selectedFunction)(unsigned int const) )
     * \brief Fonction générique permettant d'ajouter des QActions à un sous-menu, en mettant en tête de liste le dernier item selectionné
     *
     * \param menu QMenu * permettant d'avoir accès au sous menu dans lequel l'élément doit être ajouté (subMenuAutomata ou subMenuGrid)
     * \param name const QString& permet de transmettre l'id de l'item dans le sous menu
     * \param  selectedFunction pointeur de fonction void (AutomataManager::*selectedFunction)(unsigned int const) permettant lors de selection
     * d'un automate ou d'une grille d'appeler la fonction correspondante (selectedAutomaton ou selectedState)
     *
    */

    void newAutomaton();
    /**
     * \fn void newAutomaton()
     * \brief Instanction de la classe AutomataParameters depuis le MainController. On vérifie s'il existe déjà un automate créé.
     *  Si oui, on demande validation à l'utilisateur avant d'écraser l'automate courant. Sinon, on crée un nouvel automate.
    */

    void newAutomatonNext();
    /**
     * \fn void newAutomatonNext()
     * \brief Permet de transmettre les différents paramètres entrés par l'utilisateur dans AutomataParameters,
     *  et de définir l'état initial du modèle relié à la vue.
     *  La fenêtre principale de l'application est actualisée en conséquence selon si 1D, 2D et/ou random
    */

    void newRule();
    /**
     * \fn void newRule()
     * \brief Instanciation de la classe RulesController par le MainController. On vérifie qu'il existe bien un automate avant d'ajouter une règle,
     * et on transmet la dimension de l'automate au constructeur de règles
    */

};




#endif // MAINCONTROLLER_H

