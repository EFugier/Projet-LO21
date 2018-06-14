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
    AutomataParameters(QWidget *parent = 0);

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
private:
    AutomataManager& instance;
    State * model;
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
    QDial * timer;
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
    void createMenus();
    void createToolBars();
    QString openFile();
    void insertNewAction(QMenu* menu, int id, const QString& name, void (AutomataManager::*)(unsigned int const) );
 //   void selectedAutomaton(int);
    void newAutomaton();
    void newRule();

};




#endif // MAINCONTROLLER_H

