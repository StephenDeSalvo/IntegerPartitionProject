/*This is just a test of using qt to display young diagram, the assumption is that the partition is passed in a sorted
 * vector in ascending order
*/


#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
//#include <QDebug>
#include <vector>
#include "rect.h"

/** This function helps display the partition
 * @param partition is the vector that contains the integer partition
 * @param scene is the pointer to QGraphicsScene
 * @returns a vector of pointers to myrect
*/
std::vector<myrect*> display_parition(std::vector<int> partition,QGraphicsScene* scene){
    int box_length=20;

    //asuming the element in the vector are sorted so the last
    //element is the largest
    int par_size=partition.size();
    int max_col=partition[par_size-1];
    std::vector<myrect*> result(max_col*par_size);
    for(int i=par_size;i>0;--i){
        for(int j=0;j<partition[i-1];++j){
            int row=par_size-i;
            int col=j;
            result[row*max_col+col]=new myrect(col*box_length,row*box_length,box_length,box_length);
            scene->addItem(result[row*max_col+col]);
        }
    }


    return result;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsView view;

    QGraphicsScene* scene = new QGraphicsScene(&view);

    scene->setBackgroundBrush(Qt::black);
    view.setScene(scene);
    //view.resize(400,400);
    scene->setSceneRect(0,0,400,400);

    //can try to revise the values in here and it can display different partition
    std::vector<int> partition(4);
    partition[0]=1;
    partition[1]=3;
    partition[2]=6;
    partition[3]=10;

    display_parition(partition,scene);


    /*
    QGraphicsRectItem* rect = new QGraphicsRectItem(0,380,20,20);
    rect->setPen(QPen(QColor(Qt::white)));
    rect->setBrush(QBrush(Qt::yellow));
    scene->addItem(rect);

    //qDebug()<<rect->pos();
    QGraphicsRectItem* rect2 = new QGraphicsRectItem(20,380,20,20);
    rect2->setPen(QPen(QColor(Qt::white)));
    rect2->setBrush(QBrush(Qt::yellow));
    scene->addItem(rect2);
    */

    //qDebug()<<rect2->pos();
    //rect->moveBy(-100,-100);
    //qDebug()<<rect->scenePos();
    view.show();

    return a.exec();
}
