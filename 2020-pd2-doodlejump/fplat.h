#ifndef FPLAT_H
#define FPLAT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class fplat : public QGraphicsPixmapItem
{
public:
    fplat();
    QGraphicsItem *fl;
    int ppp;
    void virtual create(int x,int y)=0;
};

#endif // FPLAT_H
