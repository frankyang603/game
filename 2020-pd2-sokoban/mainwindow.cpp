#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(700,700);
    this->setMaximumSize(700,700);
    menu = new QLabel(this);
    menu->setGeometry(0,0,500,500);
    QPixmap pix(":/new/prefix1/image/picture-of-sunset-blue-skies-and-clouds-115355698120xzxlsbdgn.jpg");
    menu->setPixmap(pix.scaled(menu->width(),menu->height()));
    start = new QPushButton(this);
    start->setGeometry(175,175,50,50);
    start->setText("start");
    quit = new QPushButton(this);
    quit->setGeometry(275,175,50,50);
    quit->setText("quit");
    level1 = new QPushButton(this);
    level1->setGeometry(125,300,50,50);
    level1->setText("level1");
    level2 = new QPushButton(this);
    level2->setGeometry(225,300,50,50);
    level2->setText("level2");
    level3 = new QPushButton(this);
    level3->setGeometry(325,300,50,50);
    level3->setText("level3");
    levelmap = new QLabel(this);  
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            qbomb[i][j] = new QLabel(this);
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            qaddHP[i][j] = new QLabel(this);
        }
    }
    int begining=0,end=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            map[i][j] = new QLabel(this);
        }
    }
    for(int i=0;i<3;i++){
        ultimate[end] = new QLabel(this);
        end++;
    }
    for(int i=0;i<3;i++){
        begin[begining] = new QLabel(this);
        begining++;
    }
    restart = new QPushButton(this);
    restart->setGeometry(575,275,50,50);
    restart->setText("restart");
    player = new QLabel(this);
    walknum = new QLabel(this);
    walktext = new QLabel(this);
    usebomb = new QPushButton(this);
    usebomb->setGeometry(575,200,70,50);
    usebomb->setText("usebomb");
    bombnum = new QLabel(this);
    bombtext = new QLabel(this);
    HPlabelnum = new QLabel(this);
    HPlabletext = new QLabel(this);
    coinlnum = new QLabel(this);
    coinltext = new QLabel(this);
    addbomb = new QPushButton(this);
    addHP = new QPushButton(this);
    addbomb->setGeometry(200,550,70,50);
    addbomb->setText("addbomb");
    addHP->setGeometry(300,550,70,50);
    addHP->setText("addHP");
    change = new QPushButton(this);
    change->setGeometry(525,350,150,50);
    change->setText("change character");
    pass = new QLabel(this);
    pass->setGeometry(100,625,250,50);
    pass->setVisible(false);
    usebomb->setVisible(false);
    bombnum->setVisible(false);
    bombtext->setVisible(false);
    walknum->setVisible(false);
    walktext->setVisible(false);
    HPlabelnum->setVisible(false);
    HPlabletext->setVisible(false);
    coinlnum->setVisible(false);
    coinltext->setVisible(false);
    addbomb->setVisible(false);
    addHP->setVisible(false);
    change->setVisible(false);
    restart->setVisible(false);
    connect(start,SIGNAL(clicked(bool)),this,SLOT(setmap()));
    connect(quit,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(addbomb,SIGNAL(clicked(bool)),this,SLOT(addbombbomb()));
    connect(change,SIGNAL(clicked(bool)),this,SLOT(changechar()));
    connect(addHP,SIGNAL(clicked(bool)),this,SLOT(addHPHP()));
    connect(level1,SIGNAL(clicked(bool)),this,SLOT(setmap()));
    connect(level2,SIGNAL(clicked(bool)),this,SLOT(setmap2()));
    connect(level3,SIGNAL(clicked(bool)),this,SLOT(setmap3()));
    connect(this,SIGNAL(restartlevel1()),this,SLOT(setmap()));
    connect(this,SIGNAL(restartlevel2()),this,SLOT(setmap2()));
    connect(this,SIGNAL(restartlevel3()),this,SLOT(setmap3()));
    connect(usebomb,SIGNAL(clicked(bool)),this,SLOT(bombbomb()));
    connect(this,SIGNAL(de()),this,SLOT(cout()));
    connect(this,SIGNAL(goup()),this,SLOT(up()));
    connect(this,SIGNAL(godown()),this,SLOT(down()));
    connect(this,SIGNAL(goleft()),this,SLOT(left()));
    connect(this,SIGNAL(goright()),this,SLOT(right()));
    connect(restart,SIGNAL(clicked(bool)),this,SLOT(restartlevel()));    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cout(){
    coin=cointemp;
    cointemp=0;
    if(firemap[8][8]==0){
        pass->setVisible(true);
        pass->setText("PASS!!!      Click here to continue:");
        if(deter[1][1]==0&&HP>0){
           level2->setVisible(true);
           level2->setGeometry(350,625,50,50);
        }
        if(deter[1][1]==4&&HP>0){
            level3->setVisible(true);
            level3->setGeometry(350,625,50,50);
        }
    }
    else{
        pass->setVisible(true);
        pass->setText("You finish all levels!!!");
    }
}

void MainWindow::addbombbomb(){
    if(cointemp>=5){
        bombnumber++;
        bombnum->setNum(bombnumber);
        cointemp-=5;
        coinlnum->setNum(cointemp);
    }
}

void MainWindow::addHPHP(){
    if(cointemp>=5){
        HP+=30;
        HPlabelnum->setNum(HP);
        cointemp-=5;
        coinlnum->setNum(cointemp);
    }
}

void MainWindow::changechar(){
    QPixmap pix9(":/new/prefix1/image/download (4).jpeg");
    QPixmap pix10(":/new/prefix1/image/images (2).jpeg");
    player->clear();
    if(changec==0){
        player->setPixmap(pix9.scaled(player->width(),player->height()));
        changec=1;
    }
    else{
        player->setPixmap(pix10.scaled(player->width(),player->height()));
        changec=0;
    }
}

void MainWindow::restartlevel(){
    if(firemap[2][4]==7){
        emit restartlevel1();
    }
    else if(firemap[2][1]==7){
        emit restartlevel2();
    }
    else if(firemap[8][8]==7){
        emit restartlevel3();
    }
}

void MainWindow::bombbomb(){
    if(bombnumber>0){
        for(int i=player->y()/50-1;i<=player->y()/50+1;i++){
           for(int j=player->x()/50-1;j<=player->x()/50+1;j++){
              if(location[i][j]==2){
                  map[i][j]->clear();
                  location[i][j]=0;
              }
           }
        }
        bombnumber--;
        bombnum->setNum(bombnumber);
    }
}

bool MainWindow::determine(){
    int count=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(location[i][j]%10==3){
                if(deter[i][j]==4){
                    count++;
                }
            }
        }
    }
    if(count==3){
        return true;
    }
    return false;
}

void MainWindow::setmap(){
    restart->setVisible(true);
    usebomb->setVisible(true);
    pass->setVisible(true);
    bombnum->setVisible(true);
    bombtext->setVisible(true);
    walknum->setVisible(true);
    walktext->setVisible(true);
    HPlabelnum->setVisible(true);
    HPlabletext->setVisible(true);
    coinlnum->setVisible(true);
    coinltext->setVisible(true);
    addbomb->setVisible(true);
    addHP->setVisible(true);
    change->setVisible(true);
    quit->setGeometry(575,425,50,50);
    quit->setText("quit");
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            map[i][j] ->clear();
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            qbomb[i][j] ->clear();
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            qaddHP[i][j] ->clear();
        }
    }
    int begining=0,end=0;
    for(int i=0;i<3;i++){
        ultimate[end]->clear();
        end++;
    }
    for(int i=0;i<3;i++){
        begin[begining]->clear();
        begining++;
    }
    player->clear();
    pass->clear();
    walknum->clear();
    walktext->clear();
    countwalk=0;
    bombnumber=0;
    HP=100;
    exit=0;
    cointemp=coin;
    level1->setVisible(false);
    level2->setVisible(false);
    level3->setVisible(false);
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            location[i][j]=map1[i][j];
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            deter[i][j]=mapend1[i][j];
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            bombmap[i][j]=bomb1[i][j];
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            firemap[i][j]=fire1[i][j];
        }
    }
    levelmap->setGeometry(0,0,500,500);
    QPixmap pix(":/new/prefix1/image/800px-Auto_Racing_Green.svg.png");
    levelmap->setPixmap(pix.scaled(levelmap->width(),levelmap->height()));
    QPixmap pix1(":/new/prefix1/image/download.jpeg");
    QPixmap pix2(":/new/prefix1/image/images.jpeg");
    QPixmap pix3(":/new/prefix1/image/download (5).jpeg");
    QPixmap pix4(":/new/prefix1/image/download (1).jpeg");
    QPixmap pix5(":/new/prefix1/image/images (2).jpeg");
    QPixmap pix6(":/new/prefix1/image/download (2).jpeg");
    QPixmap pix7(":/new/prefix1/image/malibucola.webp");
    int b=0,e=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            switch(location[i][j]){
               case 1:
                    map[i][j]->setGeometry(50*j,50*i,50,50);
                    map[i][j]->setPixmap(pix1.scaled(map[i][j]->width(),map[i][j]->height()));
                    break;
                case 2:
                    map[i][j]->setGeometry(50*j,50*i,50,50);
                    map[i][j]->setPixmap(pix2.scaled(map[i][j]->width(),map[i][j]->height()));
                    break;
                case 3:
                    begin[b]->setGeometry(50*j,50*i,50,50);
                    begin[b]->setPixmap(pix3.scaled(begin[b]->width(),begin[b]->height()));
                    location[i][j]=3+b*10;
                    b++;
                    break;
                case 4:
                    ultimate[e]->setGeometry(50*j,50*i,50,50);
                    ultimate[e]->setPixmap(pix4.scaled(ultimate[e]->width(),ultimate[e]->height()));
                    e++;
                    break;
                case 5:
                    player->setGeometry(50*j,50*i,50,50);
                    player->setPixmap(pix5.scaled(player->width(),player->height()));
                    break;
            }
         }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(bombmap[i][j]==6){
                qbomb[i][j]->setGeometry(50*j,50*i,50,50);
                qbomb[i][j]->setPixmap(pix6.scaled(qbomb[i][j]->width(),qbomb[i][j]->height()));              
             }
             if(bombmap[i][j]==8){
                 qaddHP[i][j]->setGeometry(50*j,50*i,50,50);
                 qaddHP[i][j]->setPixmap(pix7.scaled(qaddHP[i][j]->width(),qaddHP[i][j]->height()));
             }
        }
    }
    walktext->setGeometry(575,150,50,50);
    walknum->setGeometry(625,150,50,50);
    walktext->setText("walk:");
    walknum->setNum(countwalk);
    bombtext->setGeometry(525,100,80,50);
    bombnum->setGeometry(625,100,50,50);
    bombtext->setText("BOMBNUM:");
    bombnum->setNum(bombnumber);
    HPlabletext->setGeometry(575,50,50,50);
    HPlabelnum->setGeometry(625,50,50,50);
    HPlabletext->setText("HP:");
    HPlabelnum->setNum(HP);
    coinltext->setGeometry(100,550,50,50);
    coinlnum->setGeometry(150,550,50,50);
    coinltext->setText("coin:");
    coinlnum->setNum(coin);
}

void MainWindow::setmap2(){
    restart->setVisible(true);
    usebomb->setVisible(true);
    pass->setVisible(true);
    bombnum->setVisible(true);
    bombtext->setVisible(true);
    walknum->setVisible(true);
    walktext->setVisible(true);
    HPlabelnum->setVisible(true);
    HPlabletext->setVisible(true);
    coinlnum->setVisible(true);
    coinltext->setVisible(true);
    addbomb->setVisible(true);
    addHP->setVisible(true);
    change->setVisible(true);
    quit->setGeometry(575,425,50,50);
    quit->setText("quit");
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            map[i][j] ->clear();
        }
    }
    int begining=0,end=0;
    for(int i=0;i<3;i++){
        ultimate[end]->clear();
        end++;
    }
    for(int i=0;i<3;i++){
        begin[begining]->clear();
        begining++;
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            qbomb[i][j] ->clear();
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            qaddHP[i][j] ->clear();
        }
    }
    player->clear();
    pass->clear();
    walknum->clear();
    walktext->clear();
    countwalk=0;
    bombnumber=0;
    HP=100;
    exit=0;
    cointemp=coin;
    level1->setVisible(false);
    level2->setVisible(false);
    level3->setVisible(false);
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            location[i][j]=map2[i][j];
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            deter[i][j]=mapend2[i][j];
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            bombmap[i][j]=bomb2[i][j];
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            firemap[i][j]=fire2[i][j];
        }
    }
    levelmap->setGeometry(0,0,500,500);
    QPixmap pix(":/new/prefix1/image/800px-Auto_Racing_Green.svg.png");
    levelmap->setPixmap(pix.scaled(levelmap->width(),levelmap->height()));
    QPixmap pix1(":/new/prefix1/image/download.jpeg");
    QPixmap pix2(":/new/prefix1/image/images.jpeg");
    QPixmap pix3(":/new/prefix1/image/download (5).jpeg");
    QPixmap pix4(":/new/prefix1/image/download (1).jpeg");
    QPixmap pix5(":/new/prefix1/image/images (2).jpeg");
    QPixmap pix6(":/new/prefix1/image/download (2).jpeg");
    QPixmap pix7(":/new/prefix1/image/malibucola.webp");
    int b=0,e=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            switch(location[i][j]){
               case 1:
                    map[i][j]->setGeometry(50*j,50*i,50,50);
                    map[i][j]->setPixmap(pix1.scaled(map[i][j]->width(),map[i][j]->height()));
                    break;
                case 2:
                    map[i][j]->setGeometry(50*j,50*i,50,50);
                    map[i][j]->setPixmap(pix2.scaled(map[i][j]->width(),map[i][j]->height()));
                    break;
                case 3:
                    begin[b]->setGeometry(50*j,50*i,50,50);
                    begin[b]->setPixmap(pix3.scaled(begin[b]->width(),begin[b]->height()));
                    location[i][j]=3+b*10;
                    b++;
                    break;
                case 4:
                    ultimate[e]->setGeometry(50*j,50*i,50,50);
                    ultimate[e]->setPixmap(pix4.scaled(ultimate[e]->width(),ultimate[e]->height()));
                    e++;
                    break;
                case 5:
                    player->setGeometry(50*j,50*i,50,50);
                    player->setPixmap(pix5.scaled(player->width(),player->height()));
                    break;
            }
         }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(bombmap[i][j]==6){
                qbomb[i][j]->setGeometry(50*j,50*i,50,50);
                qbomb[i][j]->setPixmap(pix6.scaled(qbomb[i][j]->width(),qbomb[i][j]->height()));
             }
             if(bombmap[i][j]==8){
                    qaddHP[i][j]->setGeometry(50*j,50*i,50,50);
                    qaddHP[i][j]->setPixmap(pix7.scaled(qaddHP[i][j]->width(),qaddHP[i][j]->height()));
             }
        }
    }
    walktext->setGeometry(575,150,50,50);
    walknum->setGeometry(625,150,50,50);
    walktext->setText("walk:");
    walknum->setNum(countwalk);
    bombtext->setGeometry(525,100,80,50);
    bombnum->setGeometry(625,100,50,50);
    bombtext->setText("BOMBNUM:");
    bombnum->setNum(bombnumber);
    HPlabletext->setGeometry(575,50,50,50);
    HPlabelnum->setGeometry(625,50,50,50);
    HPlabletext->setText("HP:");
    HPlabelnum->setNum(HP);
    coinltext->setGeometry(100,550,50,50);
    coinlnum->setGeometry(150,550,50,50);
    coinltext->setText("coin:");
    coinlnum->setNum(coin);
}

void MainWindow::setmap3(){
    restart->setVisible(true);
    usebomb->setVisible(true);
    pass->setVisible(true);
    bombnum->setVisible(true);
    bombtext->setVisible(true);
    walknum->setVisible(true);
    walktext->setVisible(true);
    HPlabelnum->setVisible(true);
    HPlabletext->setVisible(true);
    coinlnum->setVisible(true);
    coinltext->setVisible(true);
    addbomb->setVisible(true);
    addHP->setVisible(true);
    change->setVisible(true);
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            qbomb[i][j] ->clear();
        }
    }
    quit->setGeometry(575,425,50,50);
    quit->setText("quit");
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            map[i][j] ->clear();
        }
    }
    int begining=0,end=0;
    for(int i=0;i<3;i++){
        ultimate[end]->clear();
        end++;
    }
    for(int i=0;i<3;i++){
        begin[begining]->clear();
        begining++;
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            qaddHP[i][j] ->clear();
        }
    }
    player->clear();
    pass->clear();
    walknum->clear();
    walktext->clear();
    countwalk=0;
    bombnumber=0;
    HP=100;
    exit=0;
    cointemp=coin;
    level1->setVisible(false);
    level2->setVisible(false);
    level3->setVisible(false);
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            location[i][j]=map3[i][j];
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            deter[i][j]=mapend3[i][j];
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            bombmap[i][j]=bomb3[i][j];
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            firemap[i][j]=fire3[i][j];
        }
    }
    levelmap->setGeometry(0,0,500,500);
    QPixmap pix(":/new/prefix1/image/800px-Auto_Racing_Green.svg.png");
    levelmap->setPixmap(pix.scaled(levelmap->width(),levelmap->height()));
    QPixmap pix1(":/new/prefix1/image/download.jpeg");
    QPixmap pix2(":/new/prefix1/image/images.jpeg");
    QPixmap pix3(":/new/prefix1/image/download (5).jpeg");
    QPixmap pix4(":/new/prefix1/image/download (1).jpeg");
    QPixmap pix5(":/new/prefix1/image/images (2).jpeg");
    QPixmap pix6(":/new/prefix1/image/download (2).jpeg");
    QPixmap pix7(":/new/prefix1/image/malibucola.webp");
    int b=0,e=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            switch(location[i][j]){
               case 1:
                    map[i][j]->setGeometry(50*j,50*i,50,50);
                    map[i][j]->setPixmap(pix1.scaled(map[i][j]->width(),map[i][j]->height()));
                    break;
                case 2:
                    map[i][j]->setGeometry(50*j,50*i,50,50);
                    map[i][j]->setPixmap(pix2.scaled(map[i][j]->width(),map[i][j]->height()));
                    break;
                case 3:
                    begin[b]->setGeometry(50*j,50*i,50,50);
                    begin[b]->setPixmap(pix3.scaled(begin[b]->width(),begin[b]->height()));
                    location[i][j]=3+b*10;
                    b++;
                    break;
                case 4:
                    ultimate[e]->setGeometry(50*j,50*i,50,50);
                    ultimate[e]->setPixmap(pix4.scaled(ultimate[e]->width(),ultimate[e]->height()));
                    e++;
                    break;
                case 5:
                    player->setGeometry(50*j,50*i,50,50);
                    player->setPixmap(pix5.scaled(player->width(),player->height()));
                    break;
            }
         }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(bombmap[i][j]==6){
                qbomb[i][j]->setGeometry(50*j,50*i,50,50);
                qbomb[i][j]->setPixmap(pix6.scaled(qbomb[i][j]->width(),qbomb[i][j]->height()));
             }
             if(bombmap[i][j]==8){
                    qaddHP[i][j]->setGeometry(50*j,50*i,50,50);
                    qaddHP[i][j]->setPixmap(pix7.scaled(qaddHP[i][j]->width(),qaddHP[i][j]->height()));
             }
        }
    }
    walktext->setGeometry(575,150,50,50);
    walknum->setGeometry(625,150,50,50);
    walktext->setText("walk:");
    walknum->setNum(countwalk);
    bombtext->setGeometry(525,100,80,50);
    bombnum->setGeometry(625,100,50,50);
    bombtext->setText("BOMBNUM:");
    bombnum->setNum(bombnumber);
    HPlabletext->setGeometry(575,50,50,50);
    HPlabelnum->setGeometry(625,50,50,50);
    HPlabletext->setText("HP:");
    HPlabelnum->setNum(HP);
    coinltext->setGeometry(100,550,50,50);
    coinlnum->setGeometry(150,550,50,50);
    coinltext->setText("coin:");
    coinlnum->setNum(coin);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()){
       case Qt::Key_W:
            emit goup();
            break;
       case Qt::Key_A:
            emit goleft();
            break;
       case Qt::Key_S:
            emit godown();
            break;
       case Qt::Key_D:
            emit goright();
            break;
    }
}

void MainWindow::up(){
    if(determine()==false&&HP>0&&exit==0){
        pass->setVisible(false);
    if(location[player->y()/50-1][player->x()/50]==0||location[player->y()/50-1][player->x()/50]==4){
        player->move(player->x(),player->y()-50);
        if(firemap[player->y()/50][player->x()/50]==7){
            HP-=10;
            HPlabelnum->setNum(HP);
        }
        walknum->setNum(++countwalk);
        location[player->y()/50][player->x()/50]=5;
        location[player->y()/50+1][player->x()/50]=0;
    }
    else if(location[player->y()/50-1][player->x()/50]==3){
         if(location[player->y()/50-2][player->x()/50]==0||location[player->y()/50-2][player->x()/50]==4){
             begin[0]->move(begin[0]->x(),begin[0]->y()-50);
             player->move(player->x(),player->y()-50);
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[0]->y()/50][begin[0]->x()/50]=3;
             location[player->y()/50+1][player->x()/50]=0;
         }
    }
    else if(location[player->y()/50-1][player->x()/50]==13){
         if(location[player->y()/50-2][player->x()/50]==0||location[player->y()/50-2][player->x()/50]==4){
             begin[1]->move(begin[1]->x(),begin[1]->y()-50);
             player->move(player->x(),player->y()-50);
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[1]->y()/50][begin[1]->x()/50]=13;
             location[player->y()/50+1][player->x()/50]=0;
         }
    }
    else if(location[player->y()/50-1][player->x()/50]==23){
         if(location[player->y()/50-2][player->x()/50]==0||location[player->y()/50-2][player->x()/50]==4){
             begin[2]->move(begin[2]->x(),begin[2]->y()-50);
             player->move(player->x(),player->y()-50);
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[2]->y()/50][begin[2]->x()/50]=23;
             location[player->y()/50+1][player->x()/50]=0;
         }
    }
    if(determine()){
        emit de();
    }
    if(bombmap[player->y()/50][player->x()/50]==6){
        bombnumber++;
        bombmap[player->y()/50][player->x()/50]=0;
        qbomb[player->y()/50][player->x()/50]->clear();
    } 
    bombnum->setNum(bombnumber);
    if(bombmap[player->y()/50][player->x()/50]==8){
        HP+=30;
        bombmap[player->y()/50][player->x()/50]=0;
        qaddHP[player->y()/50][player->x()/50]->clear();
        HPlabelnum->setNum(HP);
    }
    if(bombmap[player->y()/50][player->x()/50]==9){
        cointemp++;
        bombmap[player->y()/50][player->x()/50]=0;
        coinlnum->setNum(cointemp);
    }

    if(HP==0){
        pass->setVisible(true);
        pass->setText("GG");
    }
    if(bombmap[player->y()/50][player->x()/50]==3){
        exit++;
        emit de();
    }
    }
}

void MainWindow::down(){
    if(determine()==false&&HP>0&&exit==0){
        pass->setVisible(false);
    if(location[player->y()/50+1][player->x()/50]==0||location[player->y()/50+1][player->x()/50]==4){
        player->move(player->x(),player->y()+50);
        if(firemap[player->y()/50][player->x()/50]==7){
            HP-=10;
            HPlabelnum->setNum(HP);
        }
        walknum->setNum(++countwalk);
        location[player->y()/50][player->x()/50]=5;
        location[player->y()/50-1][player->x()/50]=0;
    }
    else if(location[player->y()/50+1][player->x()/50]==3){
         if(location[player->y()/50+2][player->x()/50]==0||location[player->y()/50+2][player->x()/50]==4){
             begin[0]->move(begin[0]->x(),begin[0]->y()+50);
             player->move(player->x(),player->y()+50);
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[0]->y()/50][begin[0]->x()/50]=3;
             location[player->y()/50-1][player->x()/50]=0;
         }
    }
    else if(location[player->y()/50+1][player->x()/50]==13){
         if(location[player->y()/50+2][player->x()/50]==0||location[player->y()/50+2][player->x()/50]==4){
             begin[1]->move(begin[1]->x(),begin[1]->y()+50);
             player->move(player->x(),player->y()+50);
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[1]->y()/50][begin[1]->x()/50]=13;
             location[player->y()/50-1][player->x()/50]=0;
         }
    }
    else if(location[player->y()/50+1][player->x()/50]==23){
         if(location[player->y()/50+2][player->x()/50]==0||location[player->y()/50+2][player->x()/50]==4){
             begin[2]->move(begin[2]->x(),begin[2]->y()+50);
             player->move(player->x(),player->y()+50);
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[2]->y()/50][begin[2]->x()/50]=23;
             location[player->y()/50-1][player->x()/50]=0;
         }
    }
    if(determine()){
        emit de();
    }
    if(bombmap[player->y()/50][player->x()/50]==6){
        bombnumber++;
        bombmap[player->y()/50][player->x()/50]=0;
        qbomb[player->y()/50][player->x()/50]->clear();
    }
    bombnum->setNum(bombnumber);
    if(bombmap[player->y()/50][player->x()/50]==8){
        HP+=30;
        bombmap[player->y()/50][player->x()/50]=0;
        qaddHP[player->y()/50][player->x()/50]->clear();
        HPlabelnum->setNum(HP);
    }
    if(bombmap[player->y()/50][player->x()/50]==9){
        cointemp++;
        bombmap[player->y()/50][player->x()/50]=0;
        coinlnum->setNum(cointemp);
    }
    if(HP==0){
        pass->setVisible(true);
        pass->setText("GG");
    }
    if(bombmap[player->y()/50][player->x()/50]==3){
        exit++;
        emit de();
    }
    }
}

void MainWindow::left(){
    if(determine()==false&&HP>0&&exit==0){
        pass->setVisible(false);
    if(location[player->y()/50][player->x()/50-1]==0||location[player->y()/50][player->x()/50-1]==4){
        player->move(player->x()-50,player->y());
        if(firemap[player->y()/50][player->x()/50]==7){
            HP-=10;
            HPlabelnum->setNum(HP);
        }
        walknum->setNum(++countwalk);
        location[player->y()/50][player->x()/50]=5;
        location[player->y()/50][player->x()/50+1]=0;
    }
    else if(location[player->y()/50][player->x()/50-1]==3){
         if(location[player->y()/50][player->x()/50-2]==0||location[player->y()/50][player->x()/50-2]==4){
             begin[0]->move(begin[0]->x()-50,begin[0]->y());
             player->move(player->x()-50,player->y());
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[0]->y()/50][begin[0]->x()/50]=3;
             location[player->y()/50][player->x()/50+1]=0;
         }
    }
    else if(location[player->y()/50][player->x()/50-1]==13){
         if(location[player->y()/50][player->x()/50-2]==0||location[player->y()/50][player->x()/50-2]==4){
             begin[1]->move(begin[1]->x()-50,begin[1]->y());
             player->move(player->x()-50,player->y());
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[1]->y()/50][begin[1]->x()/50]=13;
             location[player->y()/50][player->x()/50+1]=0;
         }
    }
    else if(location[player->y()/50][player->x()/50-1]==23){
         if(location[player->y()/50][player->x()/50-2]==0||location[player->y()/50][player->x()/50-2]==4){
             begin[2]->move(begin[2]->x()-50,begin[2]->y());
             player->move(player->x()-50,player->y());
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[2]->y()/50][begin[2]->x()/50]=23;
             location[player->y()/50][player->x()/50+1]=0;
         }
    }
    if(determine()){
        emit de();
    }
    if(bombmap[player->y()/50][player->x()/50]==6){
        bombnumber++;
        bombmap[player->y()/50][player->x()/50]=0;      
        qbomb[player->y()/50][player->x()/50]->clear();
    }
    bombnum->setNum(bombnumber);
    if(bombmap[player->y()/50][player->x()/50]==8){
        HP+=30;
        bombmap[player->y()/50][player->x()/50]=0;
        qaddHP[player->y()/50][player->x()/50]->clear();
        HPlabelnum->setNum(HP);
    }
    if(bombmap[player->y()/50][player->x()/50]==9){
        cointemp++;
        bombmap[player->y()/50][player->x()/50]=0;
        coinlnum->setNum(cointemp);
    }
    if(HP==0){
        pass->setVisible(true);
        pass->setText("GG");
    }
    if(bombmap[player->y()/50][player->x()/50]==3){
        exit++;
        emit de();
    }
    }
}

void MainWindow::right(){
    if(determine()==false&&HP>0&&exit==0){
        pass->setVisible(false);
    if(location[player->y()/50][player->x()/50+1]==0||location[player->y()/50][player->x()/50+1]==4){
        player->move(player->x()+50,player->y());
        if(firemap[player->y()/50][player->x()/50]==7){
            HP-=10;
            HPlabelnum->setNum(HP);
        }
        walknum->setNum(++countwalk);
        location[player->y()/50][player->x()/50]=5;
        location[player->y()/50][player->x()/50-1]=0;
    }
    else if(location[player->y()/50][player->x()/50+1]==3){
         if(location[player->y()/50][player->x()/50+2]==0||location[player->y()/50][player->x()/50+2]==4){
             begin[0]->move(begin[0]->x()+50,begin[0]->y());
             player->move(player->x()+50,player->y());
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[0]->y()/50][begin[0]->x()/50]=3;
             location[player->y()/50][player->x()/50-1]=0;
         }
    }
    else if(location[player->y()/50][player->x()/50+1]==13){
         if(location[player->y()/50][player->x()/50+2]==0||location[player->y()/50][player->x()/50+2]==4){
             begin[1]->move(begin[1]->x()+50,begin[1]->y());
             player->move(player->x()+50,player->y());
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[1]->y()/50][begin[1]->x()/50]=13;
             location[player->y()/50][player->x()/50-1]=0;
         }
    }
    else if(location[player->y()/50][player->x()/50+1]==23){
         if(location[player->y()/50][player->x()/50+2]==0||location[player->y()/50][player->x()/50+2]==4){
             begin[2]->move(begin[2]->x()+50,begin[2]->y());
             player->move(player->x()+50,player->y());
             if(firemap[player->y()/50][player->x()/50]==7){
                 HP-=10;
                 HPlabelnum->setNum(HP);
             }
             walknum->setNum(++countwalk);
             location[player->y()/50][player->x()/50]=5;
             location[begin[2]->y()/50][begin[2]->x()/50]=23;
             location[player->y()/50][player->x()/50-1]=0;
         }
    }
    if(determine()){
        emit de();
    }
    if(bombmap[player->y()/50][player->x()/50]==6){
        bombnumber++;
        bombmap[player->y()/50][player->x()/50]=0;
        qbomb[player->y()/50][player->x()/50]->clear();
    }
    bombnum->setNum(bombnumber);
    if(bombmap[player->y()/50][player->x()/50]==8){
        HP+=30;
        bombmap[player->y()/50][player->x()/50]=0;
        qaddHP[player->y()/50][player->x()/50]->clear();
        HPlabelnum->setNum(HP);
    }
    if(bombmap[player->y()/50][player->x()/50]==9){
        cointemp++;
        bombmap[player->y()/50][player->x()/50]=0;
        coinlnum->setNum(cointemp);
    }
    if(HP==0){
        pass->setVisible(true);
        pass->setText("GG");
    }
    if(bombmap[player->y()/50][player->x()/50]==3){
        exit++;
        emit de();
    }
    }
}
