#include "platfrom3.h"

platfrom3::platfrom3()
{

}

void platfrom3::create(int x,int y)
{
    fl = new QGraphicsPixmapItem(QPixmap(":/res/bouncebed.jpeg").scaled(80,15));
    fl->setPos(x,y);
    ppp=3;
}
