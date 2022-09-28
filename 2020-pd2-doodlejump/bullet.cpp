#include "bullet.h"

bullet::bullet()
{

}

void bullet::fly()
{
    setPos(x(), y() - 5);
    if(y() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}
