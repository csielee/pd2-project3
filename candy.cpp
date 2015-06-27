#include "candy.h"

//candy

int candy::operator+(candy* other)
{
    QParallelAnimationGroup group;

    QPropertyAnimation *anim1=new QPropertyAnimation(label,"pos");
    QPropertyAnimation *anim2=new QPropertyAnimation(other->label,"pos");

    anim1->setDuration(Move_Second);
    anim1->setStartValue(location);
    anim1->setEndValue(other->location);

    anim2->setDuration(Move_Second);
    anim2->setStartValue(other->location);
    anim2->setEndValue(location);

    group.addAnimation(anim1);
    group.addAnimation(anim2);

    group.start();
    QTime t;
    t.start();
    while(t.elapsed()<Move_Second)
        QCoreApplication::processEvents();

    QPoint temp=location;
    location=other->location;
    other->location=temp;

    return 1;
}

candy::candy(QWidget *parent, QPoint pos, int s)
{
    location=pos;
    size=s;
    label=new QLabel(parent);
    label->move(location);
    label->resize(size,size);
    label->setVisible(false);
    img=QPixmap(":/img/candy/img/candy.jpg").scaled(size,size);

    label->setPixmap(img);
}



candy::~candy()
{

}

QPropertyAnimation* candy::move_anim(int n, char direction)//n代表移動像素 direction代表移動方向(wasd)
{
    QPropertyAnimation *anim=new QPropertyAnimation(label,"pos");
    anim->setDuration(Move_Second);
    anim->setStartValue(location);
    int i=0,j=0;
    switch (direction) {
    case 'w':
        j=-1;
        break;
    case 'a':
        i=-1;
        break;
    case 's':
        j=1;
        break;
    case 'd':
        i=1;
        break;
    default:
        break;
    }
    anim->setEndValue(QPoint(location.x()+i*n,location.y()+j*n));

    return anim;
}

int candy::clear()
{
    return 0;
}

/*
int candy::check()
{

}
*/

int candy::bechoose()
{
    return 0;
}

//candy

//normal_candy

normal_candy::normal_candy(QWidget *parent, QPoint pos, int s, char color) : candy(parent,pos,s)
{
    QString str("normal_candy_");
    name=str+color;
    img=QPixmap(":/img/candy/img/"+name+".jpg").scaled(size,size);
    label->setPixmap(img);

}

normal_candy::~normal_candy()
{

}

int normal_candy::clear()
{
    return 0;
}

int normal_candy::bechoose()
{
    return 0;
}

//normal_candy

//h_candy

h_candy::h_candy(QWidget *parent, QPoint pos, int s, char color) : candy(parent,pos,s)
{
    QString str("h_candy_");
    name=str+color;
    img=QPixmap(":/img/candy/img/"+name+".jpg").scaled(size,size);
    label->setPixmap(img);
}

h_candy::~h_candy()
{

}

int h_candy::clear()
{
    return 0;
}

int h_candy::bechoose()
{
    return 0;
}

//v_candy

v_candy::v_candy(QWidget *parent, QPoint pos, int s, char color) : candy(parent,pos,s)
{
    QString str("v_candy_");
    name=str+color;
    img=QPixmap(":/img/candy/img/"+name+".jpg").scaled(size,size);
    label->setPixmap(img);
}

v_candy::~v_candy()
{

}

int v_candy::clear()
{
    return 0;
}

int v_candy::bechoose()
{
    return 0;
}

//v_candy

//bomb_candy

bomb_candy::bomb_candy(QWidget *parent, QPoint pos, int s, char color) : candy(parent,pos,s)
{
    QString str("bomb_candy_");
    name=str+color;
    img=QPixmap(":/img/candy/img/"+name+".jpg").scaled(size,size);
    label->setPixmap(img);
}

bomb_candy::~bomb_candy()
{

}

int bomb_candy::clear()
{
    return 0;
}

int bomb_candy::bechoose()
{
    return 0;
}

//bomb_candy

//star_candy

star_candy::star_candy(QWidget *parent, QPoint pos, int s) : candy(parent,pos,s)
{
    QString str("star_candy");
    name=str;
    img=QPixmap(":/img/candy/img/"+name+".jpg").scaled(size,size);
    label->setPixmap(img);
}

star_candy::~star_candy()
{

}

int star_candy::clear()
{
    return 0;
}

int star_candy::bechoose()
{
    return 0;
}

//star_candy
