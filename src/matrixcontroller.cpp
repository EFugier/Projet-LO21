#include "matrixcontroller.h"

void MatrixController:: onChange(std::vector<bool>& v){
        std::vector<bool>::iterator it = v.begin();
        for(int i(0); i<rowCount(); i++)
            for(int j(0); j<columnCount(); j++)
                item(i,j)->setBackgroundColor((*(it++)? QColor(255,255,255) : QColor(0,0,0)));
    }


MatrixController:: MatrixController(int c, int r, QWidget* p) : QTableWidget(r,c,p){
        for(int i(0); i<rowCount(); i++)
            for(int j(0); j<columnCount(); j++){
                setItem(i,j, new QTableWidgetItem);
                item(i,j)->setBackgroundColor("white");
            }

        setEditTriggers(QAbstractItemView::NoEditTriggers);
        setFixedWidth(c*CELLSIZE);
        setFixedHeight(r*CELLSIZE);

        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        horizontalHeader()->hide();
        verticalHeader()->hide();
        verticalHeader()->setDefaultSectionSize(CELLSIZE);
        horizontalHeader()->setDefaultSectionSize(CELLSIZE);

}


void MatrixController::cellActivation(QModelIndex index)
{
    if(item(index.row(),index.column())->text()=="")
    {
        item(index.row(),index.column())->setText("1");
        item(index.row(),index.column())->setToolTip("X");
        item(index.row(),index.column())->setBackgroundColor("black");
        item(index.row(),index.column())->setTextColor("black");

    }
    else{ if(item(index.row(),index.column())->backgroundColor()=="black")
        {
            item(index.row(),index.column())->setText("?");
            item(index.row(),index.column())->setBackgroundColor("white");
            item(index.row(),index.column())->setTextColor("black");
        }
        else if(item(index.row(),index.column())->text()=="?"    ) {
        item(index.row(),index.column())->setBackgroundColor("white");
        item(index.row(),index.column())->setTextColor("white");
        item(index.row(),index.column())->setText("0");
        item(index.row(),index.column())->setToolTip("");
        }
    }
}

std::vector<bool> MatrixController:: serializeGrid(){
std::vector<bool> vect;
for(int i(0); i<rowCount(); i++)
       for(int j(0); j<columnCount(); j++)
           vect.push_back(item(i,j)->text()=='1' );
return vect;
}
