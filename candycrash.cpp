#include "candycrash.h"

CandyCrash::CandyCrash(QWidget *parent)
    : QWidget(parent)
{
    resize(1000,800);
    move(200,100);

    game=new candy_control(this,QPoint(300,100),8,8);


    //連接時間事件
    game_timer=new QTimer(this);
    connect(game_timer,SIGNAL(timeout()),this,SLOT(on_Timer_Event()));


    //LABEL
    score_title=new QLabel(this);
    score_title->resize(150,60);
    score_title->move(75,250);
    score_title->setText("得分\nScore");

    score=new QLabel(this);
    score->resize(150,40);
    score->move(75,330);
    score->setNum(game->candy_score->score);

    time_title=new QLabel(this);
    time_title->move(75,100);
    time_title->resize(150,60);
    time_title->setText("遊戲時間\ntime");

    game_time.start();

    time=new QLabel(this);
    time->move(75,180);
    time->resize(150,40);
    QString str=QString("%1:%2").arg(game_time.elapsed()/60000).arg((game_time.elapsed()%60000)/1000);
    time->setText(str);

    target=new QLabel(this);
    target->setVisible(false);

    //按鈕
    restart=new QPushButton("重新開始",this);
    restart->move(75,640);
    restart->resize(150,50);
    connect(restart,SIGNAL(clicked()),this,SLOT(game_restart()));

    exit=new QPushButton("退出遊戲",this);
    exit->move(75,690);
    exit->resize(150,50);
    connect(exit,SIGNAL(clicked()),this,SLOT(close()));

    //開始計時
    game_timer->start(1000);
}

CandyCrash::~CandyCrash()
{

}

void CandyCrash::paintEvent(QPaintEvent *e)
{
    score->setNum(game->candy_score->score);

    QString str=QString("%1:%2").arg(game_time.elapsed()/60000).arg((game_time.elapsed()%60000)/1000);
    time->setText(str);
}

void CandyCrash::keyPressEvent(QKeyEvent *e)
{

}

void CandyCrash::on_Timer_Event()
{
    update();
}

void CandyCrash::game_restart()
{
    game->candy_score->restart();
    game_time.restart();
    game->create_plate();
}
