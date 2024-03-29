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



    time=new QLabel(this);
    time->move(75,180);
    time->resize(150,40);
    QString str=QString("%1:%2").arg(game_time.elapsed()/60000).arg((game_time.elapsed()%60000)/1000);
    time->setText(str);

    target=new QLabel(this);
    target->move(75,400);
    target->resize(150,100);
    target->setText("過關條件：\n限時1分鐘內，達到一定分數\n一星:5W\n二星:10W\n三星:20W");

    //按鈕
    restart=new QPushButton("重新開始",this);
    restart->move(75,640);
    restart->resize(150,50);
    connect(restart,SIGNAL(clicked()),this,SLOT(game_restart()));

    exit=new QPushButton("退出遊戲",this);
    exit->move(75,690);
    exit->resize(150,50);
    connect(exit,SIGNAL(clicked()),this,SLOT(game_over()));

    //開始計時
    game_timer->start(1000);
    game_time.start();

    star=0;
}

CandyCrash::~CandyCrash()
{
    emit quit(star,game->candy_score->score);
}

void CandyCrash::game_over()
{
    int score=game->candy_score->score;
    if(score>=50000)
    {
        star=1;
        if(score>=100000)
        {
            star=2;
            if(score>200000)
            {
                star=3;
            }
        }
    }

    emit quit(star,score);
    close();
}

void CandyCrash::paintEvent(QPaintEvent *e)
{
    score->setNum(game->candy_score->score);

    QString str=QString("you has %1 second").arg((60000-(game_time.elapsed()%60000))/1000);
    time->setText(str);
}

void CandyCrash::keyPressEvent(QKeyEvent *e)
{

}

void CandyCrash::on_Timer_Event()
{
    update();
    if(game_time.elapsed()>60000)
    {
        game_over();
    }
}

void CandyCrash::game_restart()
{
    game->candy_score->restart();
    game_time.restart();
    game->create_plate();
}
