#ifndef CANDY_CONTROL
#define CANDY_CONTROL

#include <QWidget>
#include "candy.h"
#include <stdlib.h>
#include <time.h>
#include <QMouseEvent>
#define candy_num 10

/*主要遊戲盤面控制*/
class candy_control : public QWidget{
    Q_OBJECT

public:
    candy_control(QWidget *parent = 0,QPoint pos = QPoint(0,0),int a = 1,int b = 1);
    ~candy_control();
    candy *plate[candy_num][candy_num];
    int create_plate();
    int choose(int i,int j);
    int m,n,activing;

protected:
    void mousePressEvent(QMouseEvent *e);
};

#endif // CANDY_CONTROL

