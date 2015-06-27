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
    name=QString("candy");
    img=QPixmap(":/img/candy/img/"+name+".png").scaled(size,size);

    label->setPixmap(img);

    value=candy_color_value(name);
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

normal_candy::normal_candy(QWidget *parent, QPoint pos, char color, int s) : candy(parent,pos,s)
{
    QString str("normal_candy_");
    name=str+color;
    img=QPixmap(":/img/candy/img/"+name+".png").scaled(size,size);
    label->setPixmap(img);
    img_choose=QPixmap(":/img/candy/img/"+name+"_choose.png").scaled(size,size);

    value=candy_color_value(name);
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
    static int has=0;
    if(!has)
    {
        label->setPixmap(img_choose);
    }
    else
    {
        label->setPixmap(img);
    }
    has++;
    has=has%2;
    return 0;
}

//normal_candy

//h_candy

h_candy::h_candy(QWidget *parent, QPoint pos, char color, int s) : candy(parent,pos,s)
{
    QString str("h_candy_");
    name=str+color;
    img=QPixmap(":/img/candy/img/"+name+".png").scaled(size,size);
    label->setPixmap(img);
    img_choose=QPixmap(":/img/candy/img/"+name+"_choose.png").scaled(size,size);
    value=candy_color_value(name);
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

v_candy::v_candy(QWidget *parent, QPoint pos, char color, int s) : candy(parent,pos,s)
{
    QString str("v_candy_");
    name=str+color;
    img=QPixmap(":/img/candy/img/"+name+".png").scaled(size,size);
    label->setPixmap(img);
    img_choose=QPixmap(":/img/candy/img/"+name+"_choose.png").scaled(size,size);
    value=candy_color_value(name);
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

bomb_candy::bomb_candy(QWidget *parent, QPoint pos, char color, int s) : candy(parent,pos,s)
{
    QString str("bomb_candy_");
    name=str+color;
    img=QPixmap(":/img/candy/img/"+name+".png").scaled(size,size);
    label->setPixmap(img);
    img_choose=QPixmap(":/img/candy/img/"+name+"_choose.png").scaled(size,size);
    value=candy_color_value(name);
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
    img=QPixmap(":/img/candy/img/"+name+".png").scaled(size,size);
    label->setPixmap(img);
    img_choose=QPixmap(":/img/candy/img/"+name+"_choose.png").scaled(size,size);
    value=candy_color_value(name);
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


int candy_color_value(QString &str)
{
    int n=-1;
    char ch=str.at(0).toLatin1();

    switch(ch)
    {
    case 'c':
        n=0;
        break;
    case 's':
        n=1;
        break;
    case 'n':
    case 'h':
    case 'v':
    case 'b':
        ch=str.at(str.length()-1).toLatin1();
        switch(ch)
        {
        case 'r':
            n=2;
            break;
        case 'b':
            n=3;
            break;
        case 'g':
            n=4;
            break;
        case 'y':
            n=5;
            break;
        default:
            break;
        }
    default:
        break;
    }
    return n;
}
