#include "rect.h"
#include <QPen>
#include <QBrush>

myrect::myrect(int x, int y, int w, int h):QGraphicsRectItem(x,y,w,h),
    loc_x(x),loc_y(y),width(w),height(h)
{
    setPen(QPen(QColor(Qt::white)));
    setBrush(QBrush(Qt::yellow));
}

