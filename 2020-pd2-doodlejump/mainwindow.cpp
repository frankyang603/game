#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 800, 800)),
    timer(new QTimer),
    timerhp(new QTimer),
    timerroc(new QTimer)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    showscore = new QLabel(this);
    showscore->setGeometry(930,350,50,50);
    showscore->setNum(score);

    showtext = new QLabel(this);
    showtext->setGeometry(850,350,70,50);
    showtext->setText("score:");

    end = new QLabel(this);
    QPixmap picwhite(":/res/Black_colour.jpg");
    end->setPixmap(picwhite.scaled(800,825));
    end->setGeometry(0,0,800,825);
    end->setVisible(false);

    gameover = new QLabel(this);
    QPixmap picgameover(":/res/GameOver.png");
    gameover->setPixmap(picgameover.scaled(800,825));
    gameover->setGeometry(0,0,800,825);
    gameover->setVisible(false);

    pause = new QPushButton(this);
    pause->setGeometry(850,500,100,50);
    pause->setText("pause");

    monsterr = new monster;
    monsterr->setPixmap(QPixmap(":/res/monster.jpg").scaled(100,100));
    monsterr->setX(-100);
    scene->addItem(monsterr);

    monsterr2= new soldier;
    monsterr2->setPixmap(QPixmap(":/res/soldier.jpg").scaled(100,100));
    monsterr2->setX(-200);
    scene->addItem(monsterr2);

    armorr = new armor;
    armorr->setPixmap(QPixmap(":/res/armor.jpeg").scaled(100,100));
    armorr->setX(-300);
    scene->addItem(armorr);

    rockett = new rocket;
    rockett->setPixmap(QPixmap(":/res/rocket.jpg").scaled(100,100));
    rockett->setX(-400);
    scene->addItem(rockett);

    platdown = new platform;
    platdown->fl = new QGraphicsPixmapItem(QPixmap(":/res/download (1).png").scaled(800,20));
    platdown->fl->setPos(0,780);
    scene->addItem(platdown->fl);

    p = new player;
    p->setPixmap(QPixmap(":/res/doodle.png").scaled(75,150));
    scene->addItem(p);
    p->setPos(350,650);

    srand(time(NULL));

    for(int i=0;i<10;i++){
        int rp;
        rp=rand()%20+1;
        if(rp==19){
            floor[i] = new platfrom3;
        }
        else if(rp==18||rp==17){
            floor[i] = new platform2;
        }
        else{
            floor[i] = new platform;
        }
        int r,rr,rrr;
        rrr=rand()%70+1;
        r=rand()%700+1;
        rr=rrr+70*i;
        floor[i]->create(r,rr);
        scene->addItem(floor[i]->fl);
    }
    for(int i=10;i<20;i++){
        int rp;
        rp=rand()%20+1;
        if(rp==19){
            floor[i] = new platfrom3;
        }
        else if(rp==18||rp==17||rp==16){
            floor[i] = new platform2;
        }
        else{
            floor[i] = new platform;
        }
        int r,rr,rrr;
        rrr=rand()%70+1;
        r=rand()%700+1;
        rr=rrr+70*i;
        floor[i]->create(r,rr-1500);
        scene->addItem(floor[i]->fl);
    }
    timer->start(15);
    connect(timer,SIGNAL(timeout()),this,SLOT(jump()));
    connect(timer,SIGNAL(timeout()),this,SLOT(showmonster()));
    connect(timer,SIGNAL(timeout()),this,SLOT(showprop()));
    connect(timerhp,SIGNAL(timeout()),this,SLOT(ar()));
    connect(timerroc,SIGNAL(timeout()),this,SLOT(rock()));
    connect(pause,SIGNAL(clicked(bool)),this,SLOT(pasue()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_A:
        if(endgame==1){
            end->setVisible(true);
            gameover->setVisible(true);
            return;
        }
        p->setPos(p->x() - 10, p->y());
        if(p->x()<0){
            p->setX(700);
        }
        break;
    case Qt::Key_D:
        if(endgame==1){
            return;
        }
        p->setPos(p->x() + 10, p->y());
        if(p->x()>700){
            p->setX(0);
        }
        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(deterpause==1){
        return;
    }
    if(endgame==1){
        end->setVisible(true);
        gameover->setVisible(true);
        return;
    }
    bullet *b = new bullet;
    b->setPixmap(QPixmap(":/res/bullet.png").scaled(80, 180));
    b->setPos(p->x() + p->pixmap().width() / 2 - b->pixmap().width() / 2, p->y()- b->pixmap().height());
    if(b->x()>=monsterr->x()-80 && b->x()<=monsterr->x()+100 &&b->y()>=monsterr->y()-100){
        monsterr->setX(-100);
        determon=1;
    }
    b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
}

void MainWindow::pasue(){
    if(endgame==1){
        return;
    }
    if(deterpause==0){
        timer->stop();
        pause->setText("continue");
        deterpause=1;
    }
    else {
        timer->start();
        pause->setText("pause");
        deterpause=0;
    }
}

void MainWindow::showmonster()
{
    if(determon==1){
        int r,rr,rrr;
        r=rand()%200+1;
        rr=rand()%700+1;
        rrr=rand()%700+1;
        if(r==50){
            monsterr->setPos(rr,rrr-800);
            determon=0;
        }
    }
    if(detersol==1){
        int r,rr,rrr;
        r=rand()%500+1;
        rr=rand()%700+1;
        rrr=rand()%700+1;
        if(r==50){
            monsterr2->setPos(rr,rrr-800);
            detersol=0;
        }
    }
}

void MainWindow::showprop()
{
    if(deterroc==1){
        int r,rr,rrr;
        r=rand()%350+1;
        rr=rand()%700+1;
        rrr=rand()%700+1;
        if(r==50){
            rockett->setPos(rr,rrr-800);
            deterroc=0;
        }
    }
    if(deterarm==1){
        int r,rr,rrr;
        r=rand()%250+1;
        rr=rand()%700+1;
        rrr=rand()%700+1;
        if(r==50){
            armorr->setPos(rr,rrr-800);
            deterarm=0;
        }
    }
}

void MainWindow::jump()
{
    if(endgame==1){
        end->setVisible(true);
        gameover->setVisible(true);
        return;
    }
    if(p->y()>800){
        endgame=1;
        end->setVisible(true);
        gameover->setVisible(true);
    }
    if(detroc==1){
        v=15;
    }
    if(v>0&&p->y()<300){
        monsterr->setY(monsterr->y()+v);
        monsterr2->setY(monsterr2->y()+v);
        armorr->setY(armorr->y()+v);
        rockett->setY(rockett->y()+v);
        platdown->fl->setY(platdown->fl->y()+v);
        score++;
        showscore->setNum(score);
        if(monsterr->y()>800){
            determon=1;
        }
        if(monsterr2->y()>800){
            detersol=1;
        }
        if(rockett->y()>800){
            deterroc=1;
        }
        if(armorr->y()>800){
            deterarm=1;
        }
        for(int i=0;i<20;i++){
            floor[i]->fl->setY(floor[i]->fl->y()+v);
            if(floor[i]->fl->y()>800){
                int gety;
                gety=floor[i]->y();
                int rp;
                rp=rand()%20+1;
                if(rp==19){
                    floor[i] = new platfrom3;
                }
                else if(rp==18||rp==17){
                    floor[i] = new platform2;
                }
                else{
                    floor[i] = new platform;
                }
                int r,rr;
                r=rand()%700+1;
                rr=rand()%700+1;
                floor[i]->create(r,gety-800);
                scene->addItem(floor[i]->fl);
            }
        }
        v-=g;
        if(dethp==0 && p->x()>=monsterr->x()-75 && p->x()<monsterr->x()+100 && p->y()>monsterr->y()-150 && p->y()<monsterr->y()+100){
            endgame=1;
        }
        if(dethp==0 && p->x()>=monsterr2->x()-75 && p->x()<monsterr2->x()+100 && p->y()>monsterr2->y()-150 && p->y()<monsterr2->y()+100){
            endgame=1;
        }
        if(p->x()>=rockett->x()-75 && p->x()<rockett->x()+100 && p->y()>rockett->y()-150 && p->y()<rockett->y()+100){
            if(dethp==1){
                dethp=0;
            }
            timerroc->start(5000);
            p->setPixmap(QPixmap(":/res/rocketdoodle.jpeg").scaled(75,150));
            detroc=1;
        }
        if(p->x()>=armorr->x()-75 && p->x()<armorr->x()+100 && p->y()>armorr->y()-150 && p->y()<armorr->y()+100){
            if(detroc==1){
                v=10;
                detroc=0;
            }
            timerhp->start(10000);
            p->setPixmap(QPixmap(":/res/doodleinprotect.jpeg").scaled(75,150));
            dethp=1;
        }
    }
    else{
        p->setY(p->y()-v);
        v-=g;
        for(int i=0;i<20;i++){
            if(v<0&&p->y()+150>=platdown->fl->y()){
                v=10;
            }
            if((v<0&&p->y()+150>=floor[i]->fl->y())&&(p->y()+150<=floor[i]->fl->y()+15)&&(p->x()+75>=floor[i]->fl->x())&&(p->x()<=floor[i]->fl->x()+80)){
                v=10;
                if(floor[i]->ppp==2){
                    delete floor[i]->fl;
                    int gety;
                    gety=floor[i]->y();
                    int rp;
                    rp=rand()%20+1;
                    if(rp==19){
                        floor[i] = new platfrom3;
                    }
                    else if(rp==18||rp==17){
                        floor[i] = new platform2;
                    }
                    else{
                        floor[i] = new platform;
                    }
                    int r,rr;
                    r=rand()%700+1;
                    rr=rand()%700+1;
                    floor[i]->create(r,gety-800);
                    scene->addItem(floor[i]->fl);
                }
                else if(floor[i]->ppp==3){
                    v+=3;
                }
            }
        }
        if(dethp==0 && p->x()>=monsterr->x()-75 && p->x()<monsterr->x()+100 && p->y()>monsterr->y()-150 && p->y()<monsterr->y()+100){
            endgame=1;
        }
        if(dethp==0 && p->x()>=monsterr2->x()-75 && p->x()<monsterr2->x()+100 && p->y()>monsterr2->y()-150 && p->y()<monsterr2->y()+100){
            endgame=1;
        }
        if(p->x()>=rockett->x()-75 && p->x()<rockett->x()+100 && p->y()>rockett->y()-150 && p->y()<rockett->y()+100){
            if(dethp==1){
                dethp=0;
            }
            timerroc->start(5000);
            p->setPixmap(QPixmap(":/res/rocketdoodle.jpeg").scaled(75,150));
            detroc=1;
        }
        if(p->x()>=armorr->x()-75 && p->x()<armorr->x()+100 && p->y()>armorr->y()-150 && p->y()<armorr->y()+100){
            if(detroc==1){
                v=10;
                detroc=0;
            }
            timerhp->start(10000);
            p->setPixmap(QPixmap(":/res/doodleinprotect.jpeg").scaled(75,150));
            dethp=1;
        }
    }
}

void MainWindow::ar()
{
    dethp=0;
    p->setPixmap(QPixmap(":/res/doodle.png").scaled(75,150));
}

void MainWindow::rock()
{
    detroc=0;
    v=10;
    p->setPixmap(QPixmap(":/res/doodle.png").scaled(75,150));
}


