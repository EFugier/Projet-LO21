#ifndef RULESCONTROLLER_H
#define RULESCONTROLLER_H



#include "qttools.h"
#include "matrixcontroller.h"

class RulesController : public QDialog
{
    Q_OBJECT

    friend class MainController;

public:
    RulesController(int column, int row=1, QWidget *parent = 0);

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    QRadioButton * dead;
    QRadioButton * alive;
    QRadioButton * same;

};


class PositionRule : public QWidget
{
    Q_OBJECT

public:
    explicit PositionRule(int column, int rows=1, QWidget* parent=nullptr);
//    std::vector<bool> serializeGrid();

private:
    MatrixController * positionMatrix;
};


class NeighbourRule : public QWidget
{
    Q_OBJECT

    friend class RulesController;

private :
    QSpinBox *from;
    QSpinBox * to;
    QCheckBox *min;
    QCheckBox *max;
public:
    explicit NeighbourRule(QWidget *parent = nullptr);
};




#endif // RULESCONTROLLER_H

