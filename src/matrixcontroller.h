#ifndef MATRIXCONTROLLER_H
#define MATRIXCONTROLLER_H


#include "qttools.h"
#include <QMovie>
/*
class StateModel : public QObject{
    Q_OBJECT

private:

    int row;
    int col;
    std::vector<bool> state;

public:
    StateModel(int r, int c, QObject* p=nullptr): row(r), col(c), QObject(p){
        srand(time(0));
        state = std::vector<bool>();
    }
    void randomState(){
        state.clear();
        for(int i(0); i<row*col; i++) state.push_back((rand()%2));
        emit valueChanged(state);
    }

signals:
    void valueChanged(std::vector<bool>&);
public slots:
    void randomSlot(){
        randomState();
    }
}; */



class MatrixController : public QTableWidget{
  Q_OBJECT

    QMovie *movie;
    QMovie *movie2;
    bool anim;
public:
    MatrixController(int column, int rows=1, QWidget* parent=nullptr);
//    MatrixController(int r, int c, QWidget* p=nullptr);
    std::vector<bool> serializeGrid();
    std::vector<bool> serializeGrid(bool v);
    void switchBool() { anim = !anim; }
    bool getAnim() const { return anim; }
private slots:
    void onChange(std::vector<bool>& v);
    void cellActivation(QModelIndex);
};



#endif // MATRIXCONTROLLER_H


