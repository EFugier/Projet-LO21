#include "matrixcontroller.h"

void MatrixController:: onChange(std::vector<bool>& v){
        if (anim) movie->start();

        std::vector<bool>::iterator it = v.begin();
        for(int i(0); i<rowCount(); i++)
            for(int j(0); j<columnCount(); j++) {
                if (anim && item(i,j)->backgroundColor() == QColor(0,0,0) && !*(it)) {
                    item(i,j)->setFlags(item(i,j)->flags() | Qt::ItemIsEditable);
                    QLabel *processLabel = new QLabel;
                    processLabel->setMovie(movie);
                    this->setCellWidget(i,j,processLabel);
                }
                item(i,j)->setBackgroundColor((*(it++)? QColor(0,0,0) : QColor(255,255,255)));
            }
}


MatrixController:: MatrixController(int c, int r, QWidget* p) : QTableWidget(r,c,p), anim(false){
        movie = new QMovie(":/images/boom.gif");
        movie->setScaledSize(QSize(CELLSIZE, CELLSIZE));
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
