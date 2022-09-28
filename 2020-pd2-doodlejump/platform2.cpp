#include "platform2.h"

platform2::platform2()
{

}

void platform2::create(int x,int y)
{
    fl = new QGraphicsPixmapItem(QPixmap(":/res/floor2.jpeg").scaled(80,15));
    fl->setPos(x,y);
    ppp=2;
}
