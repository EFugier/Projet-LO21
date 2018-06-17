#include "matrixcontroller.h"


void MatrixController:: onChange(std::vector<bool>& v){

    if (anim) {
        movie->start();
        movie2->start();
    }

    switch (dimension) {
        case (d1) :
            onChangeD1(v);
            break;
        case (d2) :
            onChangeD2(v);
            break;
    }

}


void MatrixController::onChangeD2(std::vector<bool>& v) {
    std::vector<bool>::iterator it = v.begin();
    for(int i(0); i<rowCount(); i++)
        for(int j(0); j<columnCount(); j++) {
            if (anim && item(i,j)->backgroundColor() == QColor(0,0,0) && !*(it)) {
                item(i,j)->setFlags(item(i,j)->flags() | Qt::ItemIsEditable);
                QLabel *processLabel = new QLabel;
                processLabel->setMovie(movie);
                this->setCellWidget(i,j,processLabel);
            }
            else if (anim && item(i,j)->backgroundColor() != QColor(0,0,0) && *(it)) {
                item(i,j)->setFlags(item(i,j)->flags() | Qt::ItemIsEditable);
                QLabel *processLabel = new QLabel;
                processLabel->setMovie(movie2);
                this->setCellWidget(i,j,processLabel);
            }
            item(i,j)->setBackgroundColor((*(it++)? QColor(0,0,0) : QColor(255,255,255)));
        }
}


void MatrixController::onChangeD1(std::vector<bool>& v) {
    std::vector<bool>::iterator it = v.begin();
    if (!index) {
        for (int i(1); i<rowCount(); i++)
            for (int j(0); j<columnCount(); j++) {
                if (!item(i,j)) setItem(i,j,new QTableWidgetItem);
                item(i,j)->setBackgroundColor(QColor(255,255,255));
            }
      }

    else if (index == rowCount()) index = 0;
    int i(index);
    for(int j(0); j<columnCount(); j++) {
        if (anim && i && item(i-1,j)->backgroundColor() == QColor(0,0,0) && !*(it)) {
            item(i,j)->setFlags(item(i,j)->flags() | Qt::ItemIsEditable);
            QLabel * processLabel = new QLabel;
            processLabel->setMovie(movie);
            this->setCellWidget(i,j,processLabel);
        }
        else if (anim && i && item(i,j)->backgroundColor() != QColor(0,0,0) && *(it)) {
            item(i,j)->setFlags(item(i,j)->flags() | Qt::ItemIsEditable);
            QLabel * processLabel = new QLabel;
            processLabel->setMovie(movie2);
            this->setCellWidget(i,j,processLabel);
        }
        item(i,j)->setBackgroundColor((*(it++)? QColor(0,0,0) : QColor(255,255,255)));
    }
    index++;
}



MatrixController:: MatrixController(int c, int r, QWidget* p) : QTableWidget(r,c,p), anim(false){
        movie = new QMovie(":/images/boom.gif");
        movie2 = new QMovie(":/images/birth.gif");
        movie->setScaledSize(QSize(CELLSIZE, CELLSIZE));
        movie2->setScaledSize(QSize(CELLSIZE, CELLSIZE));
        QObject::connect(movie, &QMovie::finished, [this] () {
            movie->stop();
            for(int i(0); i<rowCount(); i++)
                for(int j(0); j<columnCount(); j++){
                    if (dynamic_cast<QLabel*>(cellWidget(i,j)))
                    dynamic_cast<QLabel*>(cellWidget(i,j))->clear();
            }
        });
        for(int i(0); i<rowCount(); i++)
            for(int j(0); j<columnCount(); j++){
                setItem(i,j, new QTableWidgetItem);
                item(i,j)->setBackgroundColor("white");
            }

        setEditTriggers(QAbstractItemView::NoEditTriggers);

        setFixedWidth(c*CELLSIZE);
        setFixedHeight(r*CELLSIZE);
        setMaximumHeight(maximumHeight());
        setMaximumWidth(maximumWidth());

        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        horizontalHeader()->hide();
        verticalHeader()->hide();
        verticalHeader()->setDefaultSectionSize(CELLSIZE);
        horizontalHeader()->setDefaultSectionSize(CELLSIZE);

}


void MatrixController::cellActivation(QModelIndex index)
{
    if(item(index.row(),index.column())->backgroundColor()=="white")
    {
        item(index.row(),index.column())->setText("1");
        item(index.row(),index.column())->setToolTip("X");
        item(index.row(),index.column())->setBackgroundColor("black");
        item(index.row(),index.column())->setTextColor("black");
    }
    else{
        item(index.row(),index.column())->setBackgroundColor("white");
        item(index.row(),index.column())->setTextColor("white");
        item(index.row(),index.column())->setText("0");
        item(index.row(),index.column())->setToolTip("");
        }

}



std::vector<bool> MatrixController:: serializeGrid(){
    std::vector<bool> vect;
    for(int i(0); i<rowCount(); i++)
        for(int j(0); j<columnCount(); j++)
            vect.push_back(item(i,j)->text()=='1' );
    return vect;
}


std::vector<bool> MatrixController:: serializeGrid(bool v) {
    std::vector<bool> vect;
    for(int i(0); i<rowCount(); i++)
        for(int j(0); j<columnCount(); j++)
            vect.push_back(item(i,j)->text()=='1' );
    vect[vect.size()/2] = v;
    return vect;
}
