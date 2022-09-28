#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <time.h>

#include "bullet.h"
#include "player.h"
#include "platform.h"
#include "platform2.h"
#include "platfrom3.h"
#include "monster.h"
#include "rocket.h"
#include "soldier.h"
#include "armor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    void jump();
    void pasue();
    void showmonster();
    void showprop();
    void ar();
    void rock();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer,*timerhp,*timerroc;
    player *p;
    fplat *platdown;
    fplat* floor[20];
    monster *monsterr;
    rocket *rockett;
    armor *armorr;
    soldier *monsterr2;
    QPushButton *pause;
    QLabel *showscore,*showtext,*end,*gameover;
    int score=0,deterpause=0,determon=1,detersol=1,deterroc=1,deterarm=1,endgame=0,dethp=0,detroc=0;
    double v=10,g=0.15;
};

#endif // MAINWINDOW_H

