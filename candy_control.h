#ifndef CANDY_CONTROL
#define CANDY_CONTROL

#include <QWidget>
#include "candy.h"
#include <stdlib.h>
#include <time.h>
#include <QMouseEvent>
#include <QKeyEvent>

/*分數控制*/
class Candy_Score{

public:
    Candy_Score(QWidget *parent=0);
    ~Candy_Score();
    void start();//開始連續得分
    void end();//停止連續得分
    void restart();
    int operator+(const int & a);
    int add(int style);
    void show_score(QPoint pos, int num);
    int score,scoring;
    int combo;
    QLabel *label;
    QWidget *par;
};


/*主要遊戲盤面控制*/
class candy_control : public QWidget{
    Q_OBJECT

public:
    candy_control(QWidget *parent = 0,QPoint pos = QPoint(0,0),int a = 1,int b = 1);
    ~candy_control();
    candy *plate[Candy_Num][Candy_Num];
    int create_plate();
    int choose(int i,int j);
    int check();
    candy* getCandy(QWidget * parent = 0,QPoint pos = QPoint(0,0));
    int m,n,activing;
    Candy_Score *candy_score;

protected:
    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
};






#endif // CANDY_CONTROL

