#ifndef CANDY_CONTROL
#define CANDY_CONTROL

#include <QWidget>
#include "candy.h"
#include <stdlib.h>
#include <time.h>
#include <QMouseEvent>


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

protected:
    void mousePressEvent(QMouseEvent *e);
};

#endif // CANDY_CONTROL

