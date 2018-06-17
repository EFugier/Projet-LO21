#ifndef RULESCONTROLLER_H
#define RULESCONTROLLER_H



#include "qttools.h"
#include "matrixcontroller.h"

/// @class RulesController

class RulesController : public QDialog
{
    Q_OBJECT

    friend class MainController;

public:
    /**
     * \fn RulesController(char def, int N, int column, int row, QWidget *parent)
     * \brief Constructeur du RulesController
     *
     * \param def état par défaut de la cellule
     * \param N nombre de voisins significatifs
     * \param column nombre de colonnes
     * \param row nombre de lignes
     *
    */
    RulesController(char def, int N, int column, int row=1, QWidget *parent = 0);

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    QRadioButton * dead;
    QRadioButton * alive;
    QRadioButton * same;

};

/// @class PositionRule
class PositionRule : public QWidget
{
    Q_OBJECT

    friend class MainController;

public:
    /**
     * \fn PositionRule(int column, int rows, QWidget* parent)
     * \brief Constructeur du PositionRule
     *
     * \param column nombre de colonnes
     * \param rows nombre de lignes
     *
    */
    explicit PositionRule(int column, int rows=1, QWidget* parent=nullptr);

private:
    MatrixController * positionMatrix;
};

/// @class NeighbourRule
class NeighbourRule : public QWidget
{
    Q_OBJECT

    friend class RulesController;
    friend class MainController;

private :
    QSpinBox *from;
    QSpinBox * to;
    QCheckBox *min;
    QPushButton *max;
public:
    /**
     * \fn NeighbourRule(int N, QWidget *parent = nullptr)
     * \brief Constructeur du NeighbourRule
     *
     * \param N nombre de voisins significatifs
     *
    */
    explicit NeighbourRule(int N, QWidget *parent = nullptr);
};




#endif // RULESCONTROLLER_H

