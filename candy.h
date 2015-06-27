#ifndef CANDY
#define CANDY

#include <QPixmap>
#include <QLabel>
#include <QPropertyAnimation>
#include <QString>
#include <QParallelAnimationGroup>
#include <QTime>
#include <QApplication>

#define Move_Second 500
#define Candy_size 150

/*顏色種類*/
QString const Candy_Color("rbgy");
#define Candy_Color_Num 4
/*candy對應數值*/
int candy_color_value(QString &str);

/*多型的基底*/
class candy{

   // Q_OBJECT


public:
    candy(QWidget *parent = 0,QPoint pos = QPoint(0,0),int s = Candy_size);
    ~candy();
    QPropertyAnimation *move_anim(int n,char direction);
    int operator+(candy*);
    virtual int clear();
    //virtual int check();
    virtual int bechoose();
    QLabel *label;
    QPoint location;
    QPixmap img,img_choose;
    QString name;
    int size,value;
};

/*普通candy*/
class normal_candy : public candy{
public:
    normal_candy(QWidget *parent = 0,QPoint pos = QPoint(0,0), char color = 'w',int s = Candy_size);
    ~normal_candy();
    int clear();
    int bechoose();
};

/*垂直水平candy*/
class h_candy : public candy{
public:
    h_candy(QWidget *parent = 0,QPoint pos = QPoint(0,0), char color = 'w',int s = Candy_size);
    ~h_candy();
    int clear();
    int bechoose();
};

class v_candy : public candy{
public:
    v_candy(QWidget *parent=0,QPoint pos = QPoint(0,0), char color = 'w',int s = Candy_size);
    ~v_candy();
    int clear();
    int bechoose();
};

/*炸彈candy*/
class bomb_candy : public candy{
public:
    bomb_candy(QWidget *parent=0,QPoint pos = QPoint(0,0), char color = 'w',int s = Candy_size);
    ~bomb_candy();
    int clear();
    int bechoose();
};

/*星星candy*/
class star_candy : public candy{
public:
    star_candy(QWidget *parent=0,QPoint pos = QPoint(0,0),int s = Candy_size);
    ~star_candy();
    int clear();
    int bechoose();
};

#endif // CANDY

