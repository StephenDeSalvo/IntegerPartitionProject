#ifndef RECT_H
#define RECT_H

#include <QGraphicsItem>


class myrect:public QGraphicsRectItem{
public:
    myrect(int x, int y, int w=20, int h=20);

private:
    int loc_x;
    int loc_y;
    int width;
    int height;

};


#endif // RECT_H
