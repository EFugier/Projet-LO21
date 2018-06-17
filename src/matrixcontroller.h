#ifndef MATRIXCONTROLLER_H
#define MATRIXCONTROLLER_H

#include "qttools.h"
#include <QMovie>

class MatrixController : public QTableWidget{
  Q_OBJECT

    friend class MainController;

    QMovie *movie;
    QMovie *movie2;
    bool anim;
    dim dimension;
    int index;
public:

    MatrixController(int column, int rows=1, QWidget* parent=nullptr);
//    MatrixController(int r, int c, QWidget* p=nullptr);
    std::vector<bool> serializeGrid();
    std::vector<bool> serializeGrid(bool v);
    void switchBool() { anim = !anim; }
    bool getAnim() const { return anim; }
    void onChangeD1(std::vector<bool>& v);
    void onChangeD2(std::vector<bool>& v);
    void setDimension(dim d) { dimension = d; index = 0; }
    dim getDimension() const { return dimension; }
private slots:
    void onChange(std::vector<bool>& v);
    void cellActivation(QModelIndex);
};



#endif // MATRIXCONTROLLER_H


