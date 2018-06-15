#include "rulescontroller.h"


RulesController::RulesController(char def, int column, int row, QWidget *parent) : QDialog(parent)
{
    tabWidget = new QTabWidget;
    tabWidget->addTab(new NeighbourRule(), tr("Neighbour Rule"));
    tabWidget->addTab(new PositionRule(column,row), tr("Position Rule"));

    QGroupBox *nextCellState = new QGroupBox(tr("Next cell-state"));
    dead = new QRadioButton(tr("Dead"));
    alive = new QRadioButton(tr("Alive"));
    same = new QRadioButton(tr("Same"));

    switch (def) {
        case 'a':
            alive->hide();
            break;
        case 'd':
            dead->hide();
            break;
        case 's':
            same->hide();
            break;
    }

    QVBoxLayout *nextCellStateLayout = new QVBoxLayout;
    nextCellStateLayout->addWidget(dead);
    nextCellStateLayout->addWidget(alive);
    nextCellStateLayout->addWidget(same);
    nextCellState->setLayout(nextCellStateLayout);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
 //   connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);

    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(nextCellState);
    mainLayout->addStretch(1);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("New Rule"));
}


PositionRule::PositionRule(int column, int rows, QWidget* parent): QWidget(parent)
{
//    positionMatrix= new QTableWidget(rows,column,parent);
    positionMatrix= new MatrixController(rows,column,parent);
    positionMatrix->setEditTriggers(QAbstractItemView::NoEditTriggers);
    positionMatrix->setFixedWidth(column*CELLSIZE);
    positionMatrix->setFixedHeight(rows*CELLSIZE);

    positionMatrix->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    positionMatrix->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    positionMatrix->horizontalHeader()->hide();
    positionMatrix->verticalHeader()->hide();

    positionMatrix->verticalHeader()->setDefaultSectionSize(CELLSIZE);
    positionMatrix->horizontalHeader()->setDefaultSectionSize(CELLSIZE);
/*
    for(int i(0); i<positionMatrix->rowCount(); i++)
        for(int j(0); j<positionMatrix->columnCount(); j++)
            positionMatrix->setItem(i,j, new QTableWidgetItem); */
   QObject::connect(positionMatrix, SIGNAL(doubleClicked(QModelIndex)), positionMatrix, SLOT(cellActivation(QModelIndex)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(positionMatrix);
    setLayout(mainLayout);
}

/*

std::vector<bool> PositionRule:: serializeGrid(){
std::vector<bool> vect;
for(int i(0); i<positionMatrix->rowCount(); i++)
       for(int j(0); j<positionMatrix->columnCount(); j++)
           vect.push_back(positionMatrix->item(i,j)->text()=='1' );
return vect;
}
 */


NeighbourRule::NeighbourRule(QWidget *parent): QWidget(parent)
{
    QGroupBox *nextCellState = new QGroupBox(tr("Number of neighbours"));
    from = new QSpinBox();
    to = new QSpinBox();
    min = new QCheckBox(tr("min"));
    max = new QCheckBox(tr("max ∞"));
    QLabel * fromLab = new QLabel("From");
    QLabel * toLab = new QLabel("To");


    QVBoxLayout *nextCellStateLayout = new QVBoxLayout;
    nextCellStateLayout->addWidget(fromLab);
    nextCellStateLayout->addWidget(from);
    nextCellStateLayout->addWidget(min);
    nextCellStateLayout->addWidget(toLab);
    nextCellStateLayout->addWidget(to);
    nextCellStateLayout->addWidget(max);
    nextCellState->setLayout(nextCellStateLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(nextCellState);
//    mainLayout->addStretch(1);
    setLayout(mainLayout);

}
