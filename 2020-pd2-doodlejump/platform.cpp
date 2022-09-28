#include "platform.h"

platform::platform()
{

}

void platform::create(int x,int y)
{
    fl = new QGraphicsPixmapItem(QPixmap(":/res/download (1).png").scaled(80,15));
    fl->setPos(x,y);
    ppp=1;
}
