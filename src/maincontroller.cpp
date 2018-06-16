#include "maincontroller.h"


MainController::MainController() : instance(AutomataManager::getInstance()){
    // !!!!!!!! j'ai initialisé l'instance après les : prcq c'est obligatoire
    // pour un attribut référence !!!!!!!!!
    mainController = new QWidget(this);
    setCentralWidget(mainController);
    mainLayout = new QHBoxLayout;
    mainController->setLayout(mainLayout);
    this->setWindowTitle("Cellular Automaton");
    //Grille random au démarrage
    instance.selectedState(State(25,25));
    // !!!!!!! J'ai remplacé StateModel par State !!!!!!!!
    view = new MatrixController(25,25);
    QObject::connect(instance.getState(), SIGNAL(valueChanged(std::vector<bool>&)), view, SLOT(onChange(std::vector<bool>&)));
    instance.getState()->emitSignal();
    toolsLayout= new QVBoxLayout;
    createActions();
    createMenus();
    createToolBars();

    mainLayout->addLayout(toolsLayout);
    toolsLayout->setSpacing(0);
    toolsLayout->addWidget(fileToolBar);
    toolsLayout->addWidget(editToolBar);
    mainLayout->addWidget(view);


}


void MainController::createActions(){
    NewAutomaton=new QAction(QIcon(":/images/start.png"), tr("&New Automaton"), this);
    connect(NewAutomaton, &QAction::triggered, this, &MainController::newAutomaton);

    ImportAutomaton = new QAction(tr("&Import Automaton..."), this);
    connect(ImportAutomaton, &QAction::triggered, [this]()
    {
        QString str=openFile();
        instance.selectedAutomaton(str);
    });

    ImportGrid=new QAction(tr("&Import Grid..."), this);
    connect(ImportGrid, &QAction::triggered, [this]()
    {
        QString str=openFile();
        instance.selectedState(str);
        QObject::connect(instance.getState(), SIGNAL(valueChanged(std::vector<bool>&)), view, SLOT(onChange(std::vector<bool>&)));
        instance.getState()->emitSignal();
    });

    OpenRecentAutomata=new QAction(tr("&Open Recent Automaton"), this);
    subMenuAutomata=new QMenu();
    OpenRecentGrid=new QAction(tr("&Open Recent Grid"), this);
    subMenuGrid=new QMenu();

/*    // Test
    std::vector<int> vect;
    for(int i=0; i<6; i++) vect.push_back(i);
    for(std::vector<int>::iterator it=vect.begin(); it!=vect.end(); it++){
        insertNewAction(subMenuAutomata,*it,"Automate"+QString::number(*it), selectedAutomaton);
        insertNewAction(subMenuGrid,*it,"Grid"+QString::number(*it), selectedAutomaton);
    }

//      Pour charger les derniers automates BDD :*/

     std::vector<const AutomataManager::AutomatonDescription> * vect = instance.getArrayOfAutomata();
     for(std::vector<const AutomataManager::AutomatonDescription>::iterator it=vect->begin(); it!=vect->end(); it++){
         QString str=(*it).getName()+((*it).getDimension() == d2 ? "2D" : "1D");
         insertNewAction(subMenuAutomata,(*it).getId(),str, &AutomataManager::selectedAutomaton);
        // !!!!!!! j'ai remplacé *it par (*it).getId() puisque c'est l'ID que tu veux
         // j'ai mis &AutomataManager::selectedAutomaton comme pointeur de fonction !!!!!!!!
     }


//      Pour charger les derniers états BDD:

    std::map<const unsigned int, const QString> * mapStates = instance.getArrayOfStates();
    for(std::map<const unsigned int, const QString>::iterator it=mapStates->begin(); it!=mapStates->end(); it++){
        insertNewAction(subMenuGrid,it->first,it->second, &AutomataManager::selectedState);
    }
    // !!!! j'ai remplacé "vect" par "mapStates" prcq ça marchait pas le nom vect était utilisé juste au dessus !!!!!

    ExportAutomaton=new QAction(tr("&Export Automaton..."), this);
    connect(ExportAutomaton, &QAction::triggered, this, [this]()
    {
        QString chemin = QFileDialog::getSaveFileName(0, "Export Automaton", QString());
      //  std::cout<<chemin.toStdString();
        instance.exportAutomaton(chemin);
    });

    ExportCurrentGrid=new QAction(tr("&Export Current Grid..."), this);
    connect(ExportCurrentGrid, &QAction::triggered, this, [this]()
    {
        instance.exportCurrentState(QFileDialog::getSaveFileName(0, "Export Grid", QString()));
    });

    ExportInitialGrid=new QAction(tr("&Export Initial Grid..."), this);
    connect(ExportInitialGrid, &QAction::triggered, this, [this]()
    {
        instance.exportInitialState(QFileDialog::getSaveFileName(0, "Export Grid", QString()));
    });

    SaveAutomaton=new QAction(tr("&Save Automaton"), this);
    connect(SaveAutomaton, &QAction::triggered, this, [this]()
    {
        bool ok=true;
        // ok= instance.saveAutomaton(subMenuAutomata->actions()[0]->data().toInt());

        if(ok)
            QMessageBox::information(this, "Saved", subMenuAutomata->actions()[0]->text() + " Saved");

        else
            QMessageBox::critical(this, "Cancel", "Not Saved");
    });


    SaveAutomatonAs=new QAction(tr("&Save Automaton As..."), this);
    connect(SaveAutomatonAs, &QAction::triggered, this, [this]()
    {
        bool ok=false;
        QString name = QInputDialog::getText(this,"Save","Name:", QLineEdit::Normal, QString(), &ok);

        if (ok && !name.isEmpty())
        {
            insertNewAction(subMenuAutomata,instance.saveAutomaton(name),name, &AutomataManager::selectedAutomaton);
            QMessageBox::information(this, "Saved", name + " Saved");

            // !!!! j'ai remplacé saveAutomaton(str) par saveAutomaton(name) !!!!
       //     insertNewAction(subMenuAutomata,995,name, instance.selectedAutomaton); //Test
        }
        else
        {
            QMessageBox::critical(this, "Cancel", "Not Saved");
        }

    });

    SaveCurrentGrid=new QAction(tr("&Save Current Grid As..."), this);
    connect(SaveCurrentGrid, &QAction::triggered, this, [this]()
    {
        bool ok=false;
        QString name = QInputDialog::getText(this,"Save","Name:", QLineEdit::Normal, QString(), &ok);

        if (ok && !name.isEmpty())
        {
              insertNewAction(subMenuAutomata,instance.saveCurrentState(name),name, &AutomataManager::selectedState);
        // insertNewAction(subMenuGrid,995,name, selectedAutomaton); //Test

            QMessageBox::information(this, "Saved", name + " Saved");
        }
        else
        {
            QMessageBox::critical(this, "Cancel", "Not Saved");
        }
    });


    SaveInitialGrid=new QAction(tr("&Save Initial Grid As..."), this);
    connect(SaveInitialGrid, &QAction::triggered, this, [this]()
    {
        bool ok=false;
        QString name = QInputDialog::getText(this,"Save","Name:", QLineEdit::Normal, QString(), &ok);

        if (ok && !name.isEmpty())
        {
          insertNewAction(subMenuAutomata,instance.saveInitialState(name),name, &AutomataManager::selectedState);

        //    insertNewAction(subMenuGrid,995,name, selectedAutomaton);
            QMessageBox::information(this, "Saved", name + " Saved");
        }
        else
        {
            QMessageBox::critical(this, "Cancel", "Not Saved");
        }
    });


    Exit=new QAction(tr("&Exit"), this);
    connect(Exit, SIGNAL(triggered()), qApp, SLOT(quit()));

    NewRule=new QAction(QIcon(":/images/param.png"), tr("&New Rule"), this);
    connect(NewRule, &QAction::triggered, this, &MainController::newRule);
    NextStep=new QAction(tr("&Next Step"), this);
    SetTimer=new QAction(tr("&Set Timer"), this);

}


void MainController::insertNewAction(QMenu* menu, int id, const QString& name, void (AutomataManager::*selectedFunction)(unsigned int const) ){
    // !!!!!!! J'ai remplacé l'argument int de la fonction pointée par unsigned int const !!!!!!!
    QAction* newAction= new QAction(name);
    newAction->setData(QVariant(id));

    if(menu->actions().empty())  {
        QAction* Clear= new QAction(tr("&Clear"));
        connect(Clear, &QAction::triggered, this, [menu, this]()
        {
            menu->clear();
        });
        menu->addSeparator();
        menu->addAction(Clear);
    }

    menu->insertAction(menu->actions()[0],newAction);

    connect(newAction, &QAction::triggered, this, [newAction, menu, name, selectedFunction, this]()
    {
        // Ici, point critique car selectedFunction est un pointeur de fonction, pour tester j'ai mis une fonction membre de la classe
        // MainController, mais il faut utiliser une fonction contenu dans AutomataManager
        (instance.*selectedFunction)(newAction->data().toInt());
        // !!!!! j'ai remplacé this-> par instance. !!!!!
        insertNewAction(menu,newAction->data().toInt(),name,selectedFunction);
        menu->removeAction(newAction);
        QObject::connect(instance.getState(), SIGNAL(valueChanged(std::vector<bool>&)), view, SLOT(onChange(std::vector<bool>&)));
        instance.getState()->emitSignal();
    });
}



void MainController::createMenus(){
    fileMenu= menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(NewAutomaton);
    fileMenu->addAction(OpenRecentAutomata);
    OpenRecentAutomata->setMenu(subMenuAutomata);
    fileMenu->addAction(OpenRecentGrid);
    OpenRecentGrid->setMenu(subMenuGrid);
    fileMenu->addAction(SaveAutomaton);
    fileMenu->addAction(SaveAutomatonAs);
    fileMenu->addAction(SaveCurrentGrid);
    fileMenu->addAction(SaveInitialGrid);
    fileMenu->addAction(ImportAutomaton);
    fileMenu->addAction(ImportGrid);
    fileMenu->addAction(ExportAutomaton);
    fileMenu->addAction(ExportCurrentGrid);
    fileMenu->addAction(ExportInitialGrid);
    fileMenu->addAction(Exit);

    editMenu= menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(NewRule);
    editMenu->addAction(SetTimer);
    editMenu->addAction(NextStep);

}

void MainController::createToolBars()
{
fileToolBar = new QToolBar();
addToolBar(Qt::LeftToolBarArea, fileToolBar);
fileToolBar->setOrientation(Qt::Vertical);
fileToolBar->setFixedWidth(toolsLayout->maximumSize().width());
fileToolBar->setIconSize( QSize( 120, 120 ) );
fileToolBar->addAction(NewAutomaton);

 editToolBar = new QToolBar();
 addToolBar(Qt::LeftToolBarArea, editToolBar);
 editToolBar->setOrientation(Qt::Vertical);
 editToolBar->setFixedWidth(maximumWidth());
 editToolBar->setIconSize( QSize( 120, 120 ) );
 editToolBar->addAction(NewRule);


 timer= new QDial();
 timer->setMaximum(10000);
 timer->setMaximumSize(30,30);

play = new QPushButton();
play->setMaximumWidth(70);
play->setIcon(QIcon(":/images/play.png"));

QObject::connect(play, &QPushButton::clicked, [this] () {
    int v = timer->value();
    if (!v) instance.next();
    else instance.setTimer(v);
});

QObject::connect(timer, &QDial::valueChanged, [this] () {
   instance.setTimer(timer->value());
});

pause= new QPushButton();
pause->setMaximumWidth(70);
pause->setIcon(QIcon(":/images/pause.png"));

QObject::connect(pause, &QPushButton::clicked, [this] () {
    instance.setTimer(0);
});

QLCDNumber * lcd = new QLCDNumber(5);
//lcd->setMinimumSize(QSize(50,30));
lcd->setMinimumWidth(30);
lcd->setMaximumHeight(23);
lcd->setSegmentStyle( QLCDNumber::Filled );
QPalette palette = lcd->palette();
palette.setColor(QPalette::Normal, QPalette::Light, Qt::white);
palette.setColor(QPalette::Normal, QPalette::Dark, Qt::black);
lcd->setPalette(palette);


connect(timer, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));

QWidget * lecture = new QWidget;
lecture->setLayout(new QHBoxLayout);
lecture->layout()->addWidget(play);
lecture->layout()->addWidget(pause);
lecture->layout()->addWidget(timer);
lecture->layout()->addWidget(lcd);
editToolBar->addWidget(lecture);


randomButton = new QPushButton("Random state");

QWidget * buttonsState = new QWidget;
buttonsState->setLayout(new QHBoxLayout);
buttonsState->layout()->addWidget(randomButton);
editToolBar->addWidget(buttonsState);

QObject::connect(randomButton, &QPushButton::clicked, [this] () {
   instance.getState()->randomState();
});

}


void MainController::newRule(){
    if (!instance.getPtrAutomaton()) return;
    RulesController * rulesController = new RulesController(instance.getAutomaton().defaultNext,instance.getAutomaton().getN(), sqrt(instance.getAutomaton().getN()),sqrt(instance.getAutomaton().getN()));
    rulesController->setMinimumSize(QSize( 200, 200 ));
    rulesController->setWindowTitle("New Rule");
    connect(rulesController->buttonBox, &QDialogButtonBox::accepted, rulesController, [rulesController, this]() {
        char v = (rulesController->dead->isChecked() ? 'd' : (rulesController->alive->isChecked() ? 'a' : 's'));
        if (!rulesController->tabWidget->currentIndex()) { // Voisins
            NeighbourRule* nr = dynamic_cast<NeighbourRule*>(rulesController->tabWidget->currentWidget());
            instance.getAutomaton().insertRuleNbInto(nr->from->value(), nr->to->value(), v);
        }
        else {
            PositionRule * pr = dynamic_cast<PositionRule*>(rulesController->tabWidget->currentWidget());
            if (v=='s') {
                instance.getAutomaton().insertPositionRule(pr->positionMatrix->serializeGrid(true), 'a');
                instance.getAutomaton().insertPositionRule(pr->positionMatrix->serializeGrid(false), 'd');
            }
            else instance.getAutomaton().insertPositionRule(pr->positionMatrix->serializeGrid(), v);
        }
        rulesController->accept();
    });
    rulesController->show();
}

void MainController::newAutomaton(){
   if(instance.getPtrAutomaton()) {
        QWidget * yesNo = new QWidget;
        yesNo->setLayout(new QHBoxLayout);
        QLabel * label = new QLabel("An Automaton already exists, do you want to erase it?",yesNo);
        QPushButton * yes = new QPushButton("Yes", yesNo);
        QPushButton * no = new QPushButton("No", yesNo);
        yesNo->layout()->addWidget(label);
        yesNo->layout()->addWidget(yes);
        yesNo->layout()->addWidget(no);
        yesNo->show();
        QObject::connect(yes, &QPushButton::clicked,[this, yesNo] () {
            instance.deleteAutomaton();
            param= new AutomataParameters(this);
            yesNo->close();
            newAutomatonNext();
        });

        QObject::connect(no, &QPushButton::clicked,[this, yesNo] () {
            param = new AutomataParameters(this, instance.getAutomaton().defaultNext, (instance.getAutomaton().dim == 1 ? d1 : d2));
            yesNo->close();
            newAutomatonNext();

        });
    }
    else   {

       param= new AutomataParameters(this);
       newAutomatonNext();
   }

}
 void MainController::newAutomatonNext() {
    connect(param->buttonBox, &QDialogButtonBox::accepted, this, [this]()
{
     instance.createAutomaton(param->neighbourhood->value(), (param->row->text().isEmpty() ? d1 : d2), (param->dead->isChecked() ? 'd' : (param->alive->isChecked() ? 'a' : 's')));

    param->tabWidget->removeTab(1);

// Cas d'un état de départ random
    if(param->random->isChecked()){
        instance.selectedState(State((!param->row->text().toUInt() ? 1 : param->row->text().toUInt()), param->column->text().toUInt()));
        QObject::connect(instance.getState(), SIGNAL(valueChanged(std::vector<bool>&)), view, SLOT(onChange(std::vector<bool>&)));
        param->accept();



        view->setRowCount(instance.getState()->getNrow());
        view->setColumnCount(instance.getState()->getNrow());
        view->setFixedWidth(view->columnCount()*CELLSIZE);
        view->setFixedHeight(view->rowCount()*CELLSIZE);

        instance.getState()->emitSignal();

    }


    else{
           MatrixController * ptrMatrix=new MatrixController(param->column->text().toInt(),(!param->row->text().toInt() ? 1 : param->row->text().toInt() ));
           QObject::connect(ptrMatrix, SIGNAL(clicked(QModelIndex)), ptrMatrix, SLOT(cellActivation(QModelIndex)));
           QWidget * stateController = new QWidget;
           stateController->setLayout(new QVBoxLayout);
           stateController->layout()->addWidget(ptrMatrix);
           param->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
           stateController->layout()->addWidget(param->buttonBox);


           param->tabWidget->addTab(stateController, tr("Initial Grid"));
           param->resize(param->column->text().toInt()*(CELLSIZE+2),param->row->text().toInt()*(CELLSIZE+2));
           param->tabWidget->setCurrentIndex(1);
           param->row->setText("");

            connect(param->buttonBox, &QDialogButtonBox::accepted, [ptrMatrix,this](){
                std::vector<bool> vect = ptrMatrix->serializeGrid();

    //                if(param->row->text().isEmpty()) instance.selectedState(State(param->column->text().toUInt(),vect));
    //                  else  instance.selectedState(State(param->row->text().toUInt(),param->column->text().toUInt(),vect));

    // Solution précédente plus possible, nécessité de faire une méthode avec paramètre par défaut selectedState(int column,int row=1, QWidget *parent=nullptr)
                instance.selectedState(State(ptrMatrix->rowCount(),ptrMatrix->columnCount(),vect));
                QObject::connect(instance.getState(), SIGNAL(valueChanged(std::vector<bool>&)), view, SLOT(onChange(std::vector<bool>&)));
                //Recopie de l'état initial
                view->setRowCount((ptrMatrix->rowCount()==1? ptrMatrix->columnCount() : ptrMatrix->rowCount()));
                view->setColumnCount(ptrMatrix->columnCount());
                view->setFixedWidth(view->columnCount()*CELLSIZE);
                view->setFixedHeight(view->rowCount()*CELLSIZE);

                for(int i(0); i<view->rowCount(); i++)
                    for(int j(0); j<view->columnCount(); j++){
                           if (i<ptrMatrix->rowCount() && j<ptrMatrix->columnCount()) {
                               view->setItem(i,j, new QTableWidgetItem);
                               view->item(i,j)->setBackgroundColor(ptrMatrix->item(i,j)->backgroundColor());
                           }
                           else {
                               view->setItem(i,j, new QTableWidgetItem);
                               view->item(i,j)->setBackgroundColor("white");
                           }
                     }

                param->accept();
            });
            connect(param->buttonBox, &QDialogButtonBox::rejected, param, &QDialog::reject);
        }



});


    connect(param->buttonBox, &QDialogButtonBox::rejected, param, &QDialog::reject);
param->show();
}

/*
void MainController::selectedAutomaton(int n){
std::cout<<n;
} */

QString MainController::openFile(){
QString filename =  QFileDialog::getOpenFileName(
          this,
          "Open Document",
          QDir::currentPath(),
          "All files (*.*)");
    if( filename.isNull() )
    {
        throw "Error";
    }
    return filename;
}


AutomataParameters::AutomataParameters(QWidget *parent, char def, dim d) : QDialog(parent)
{
    tabWidget = new QTabWidget;
    QWidget * basicParameters=new QWidget(this);
    setFixedSize(QSize(maximumWidth(),maximumHeight()));
    tabWidget->addTab(basicParameters,  tr("Basic Parameters"));

    QGroupBox *defaultCellState = new QGroupBox(tr("Default cell-state"));
    QGroupBox *dimension = new QGroupBox(tr("Dimension"));

    dead = new QRadioButton(tr("Dead"));
    alive = new QRadioButton(tr("Alive"));
    same = new QRadioButton(tr("Same"));
    switch (def) {
        case 's':
            same->setChecked(true);
            break;
        case 'a' :
            alive->setChecked(true);
            break;
        case 'd' :
            dead->setChecked(true);
            break;
    }


    QVBoxLayout *defaultCellStateLayout = new QVBoxLayout;
    QVBoxLayout *basicParametersLayout = new QVBoxLayout;
    QVBoxLayout *dimensionLayout = new QVBoxLayout;
    defaultCellStateLayout->addWidget(dead);
    defaultCellStateLayout->addWidget(alive);
    defaultCellStateLayout->addWidget(same);
    defaultCellState->setLayout(defaultCellStateLayout);

    QRadioButton * bd1 = new QRadioButton("1D");
    QRadioButton * bd2 = new QRadioButton("2D");

    QHBoxLayout * sizeMatrix= new QHBoxLayout;
    column= new QLineEdit;
    row= new QLineEdit;
    column->setFixedSize(QSize(25,25));
    row->setFixedSize(QSize(25,25));
    column->setHidden(true);
    row->setHidden(true);
    column->setValidator( new QIntValidator(0, maximumWidth(), this));
    row->setValidator( new QIntValidator(0, maximumHeight(), this) );
    QLabel * times = new QLabel("x");
    times->setFixedWidth(10);
    times->setMargin(0);
    times->setHidden(true);
    row->setTextMargins(0,0,0,0);
    column->setTextMargins(0,0,0,0);

    dimensionLayout->addWidget(bd1);
    dimensionLayout->addWidget(bd2);
    dimensionLayout->addLayout(sizeMatrix);
    sizeMatrix->setAlignment(Qt::AlignLeft);
    sizeMatrix->addStretch(1);
    sizeMatrix->addWidget(column);
    sizeMatrix->addWidget(times);
    sizeMatrix->addWidget(row);
    sizeMatrix->addStretch(maximumWidth());

    connect(bd1, &QRadioButton::clicked, this, [this, times]()
    {
        column->setHidden(false);
        times->setHidden(true);
        row->setHidden(true);
        row->setText("");
    });

    connect(bd2, &QRadioButton::clicked, this, [this, times]()
    {
        column->setHidden(false);
        times->setHidden(false);
        row->setHidden(false);
    });

    QLabel * neighbourhoodLab= new QLabel(tr("Neighbourhood Level:"));
    neighbourhood = new QSpinBox();
    neighbourhood->setValue(1);

    dimensionLayout->addWidget(neighbourhoodLab);
    dimensionLayout->addWidget(neighbourhood);
    dimension->setLayout(dimensionLayout);

    random = new QCheckBox(tr("Random Initial Grid"));
    random->click();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

    basicParametersLayout->addWidget(dimension);
    basicParametersLayout->addWidget(defaultCellState);
    basicParameters->setLayout(basicParametersLayout);
    basicParametersLayout->addWidget(random);
    basicParametersLayout->addWidget(buttonBox);
    setWindowTitle(tr("New Automaton"));
    column->setText("25");
    row->setText("25");
    if (d==d2) bd2->click();
    else bd1->click();
}


