#include "candy.h"
#include "candy_control.h"

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

candy::candy(Candy_Score *game_score, QWidget *parent, QPoint pos, int s)
{
    location=pos;
    size=s;
    score=game_score;
    label=new QLabel(parent);
    label->move(location);
    label->resize(size,size);
    label->setVisible(true);
    name=QString("candy");
    img=QPixmap(":/img/candy/img/"+name+".png").scaled(size,size);

    label->setPixmap(img);

    value=candy_color_value(name);
    change=0;
    other_name=QString("");
}



candy::~candy()
{
    delete label;
}

QPropertyAnimation* candy::move_anim(int n, char direction,int second)//n代表移動像素 direction代表移動方向(wasd)
{
    QPropertyAnimation *anim=new QPropertyAnimation(label,"pos");
    anim->setDuration(second);
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

    //改變位置
    location=QPoint(location.x()+i*n,location.y()+j*n);

    anim->setEndValue(location);

    return anim;
}

int candy::clear(candy** p, int m, int n)
{
    int i=location.x()/Candy_size,j=location.y()/Candy_size;
    (*(p+i*Candy_Num+j))=0;
    delete this;
    return 0;
}



int candy::bechoose()
{
    return 0;
}

int candy::check(candy** p, int m, int n,Candy_Score *s)
{
    int num[4]={0};
    int count;
    int i=location.x()/Candy_size,j=location.y()/Candy_size;
    int effect=0;

    //上
    count=1;
    while(j-count>=0)
    {
        if((*(p+i*Candy_Num+j-count))==0)
            break;


        if((*(p+i*Candy_Num+j-count))->value==value)
        {
            num[0]++;
            count++;
        }
        else
            break;
    }
    //下
    count=1;
    while(j+count<n)
    {
        if((*(p+i*Candy_Num+j+count))==0)
            break;


        if((*(p+i*Candy_Num+j+count))->value==value)
        {
            num[1]++;
            count++;
        }
        else
            break;
    }
    //左
    count=1;
    while(i-count>=0)
    {
        if((*(p+(i-count)*Candy_Num+j))==0)
            break;


        if((*(p+(i-count)*Candy_Num+j))->value==value)
        {
            num[2]++;
            count++;
        }
        else
            break;
    }
    //右
    count=1;
    while(i+count<m)
    {
        if((*(p+(i+count)*Candy_Num+j))==0)
            break;


        if((*(p+(i+count)*Candy_Num+j))->value==value)
        {
            num[3]++;
            count++;
        }
        else
            break;
    }
    //判斷完上下左右
    qDebug()<<num[0]<<num[1]<<num[2]<<num[3]<<location;

    //判斷連線
    if((num[0]+num[1])>=2)//上下有連線
    {
        effect=1;

        if((num[2]+num[3])>=2)
        {
            //上下左右都有連線
            qDebug()<<"上下左右"<<location;
            candy* nc=new bomb_candy(score,label->parentWidget(),location,name.at(name.length()-1).toLatin1());
            //得分
            score->add(num[0]+num[1]+num[2]+num[3]+1);

            //清除
            clear_candy(p,num,i,j,0,4,m,n);
            //clear(p,m,n);
            //清除
            qDebug()<<"上下左右清除後";

            //得炸彈
            (*(p+i*Candy_Num+j))=nc;


            while(t.elapsed()<Move_Second/3)
                QCoreApplication::processEvents();
        }
        else//左右無連線
        {
            qDebug()<<"上下"<<location;

            candy *nc;

            switch((num[0]+num[1]))
            {
            case 2:
                //直向三個連線
                //得分
                nc=0;
                break;
            case 3:
                //直向四個連線
                //得分
                //得垂直
                nc=new v_candy(score,label->parentWidget(),location,name.at(name.length()-1).toLatin1());
                break;
            case 4:
            default:
                //直向五個連線
                //得分
                //得星星
                nc=new star_candy(score,label->parentWidget(),location);
                break;
            }
            //得分
            score->add(num[0]+num[1]+1);

            //清除
            clear_candy(p,num,i,j,0,2,m,n);
            //清除

            qDebug()<<"上下清除後";
            (*(p+i*Candy_Num+j))=nc;

            while(t.elapsed()<Move_Second/3)
                QCoreApplication::processEvents();
        }
    }
    else//上下無連線
    {
        if((num[2]+num[3])>=2)//左右有連線
        {
            effect=1;
            qDebug()<<"左右"<<location;



            candy* nc;
            switch((num[2]+num[3]))
            {
            case 2:
                //橫向三個連線
                //得分
                nc=0;
                break;
            case 3:
                //橫向四個連線
                //得分
                //得水平
                nc=new h_candy(score,label->parentWidget(),location,name.at(name.length()-1).toLatin1());
                break;
            case 4:
            default:
                //橫向五個連線
                //得分
                //得星星
                nc=new star_candy(score,label->parentWidget(),location);
                break;
            }
            //得分
            score->add(num[2]+num[3]+1);

            //清除
            clear_candy(p,num,i,j,2,4,m,n);
            //清除

            qDebug()<<"左右清除後";
            (*(p+i*Candy_Num+j))=nc;
            while(t.elapsed()<Move_Second/3)
                QCoreApplication::processEvents();
        }

    }

    return effect;
}

int candy::setOther(candy *other)
{
    other_name=other->name;
    return 0;
}

//candy

//normal_candy

normal_candy::normal_candy(Candy_Score *game_score,QWidget *parent, QPoint pos, char color, int s) : candy(game_score,parent,pos,s)
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

int normal_candy::clear(candy** p,int m,int n)
{
    candy::clear(p,m,n);
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

h_candy::h_candy(Candy_Score *game_score, QWidget *parent, QPoint pos, char color, int s) : candy(game_score,parent,pos,s)
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

int h_candy::clear(candy** p, int m, int n)
{
    int i=location.x()/Candy_size,j=location.y()/Candy_size;
    //水平消除
    for(int k=0;k<m;k++)
    {
        if(k!=i)
        {
            if((*(p+k*Candy_Num+j))!=0)
            {
                (*(p+k*Candy_Num+j))->clear(p,m,n);
                (*score)+100;
            }
        }
    }

    candy::clear(p,m,n);
    return 0;
}

int h_candy::bechoose()
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

//v_candy

v_candy::v_candy(Candy_Score *game_score,QWidget *parent, QPoint pos, char color, int s) : candy(game_score,parent,pos,s)
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

int v_candy::clear(candy** p,int m,int n)
{
    int i=location.x()/Candy_size,j=location.y()/Candy_size;
    //垂直消除
    for(int k=0;k<m;k++)
    {
        if(k!=j)
        {
            if((*(p+i*Candy_Num+k))!=0)
            {
                (*(p+i*Candy_Num+k))->clear(p,m,n);
                (*score)+100;
            }
        }
    }

    candy::clear(p,m,n);
    return 0;
}

int v_candy::bechoose()
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

//v_candy

//bomb_candy

bomb_candy::bomb_candy(Candy_Score *game_score, QWidget *parent, QPoint pos, char color, int s) : candy(game_score,parent,pos,s)
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

int bomb_candy::clear(candy** p,int m,int n)
{
    int i=location.x()/Candy_size,j=location.y()/Candy_size;
    int num=0;
    //周圍消除
    //上
    if(j-1>=0)
        if((*(p+i*Candy_Num+j-1))!=0)
        {
            (*(p+i*Candy_Num+j-1))->clear(p,m,n);
            num++;
        }
    //下
    if(j+1<n)
        if((*(p+i*Candy_Num+j+1))!=0)
        {
            num++;
            (*(p+i*Candy_Num+j+1))->clear(p,m,n);
        }
    //左
    if(i-1>=0)
        if((*(p+(i-1)*Candy_Num+j))!=0)
        {
            num++;
            (*(p+(i-1)*Candy_Num+j))->clear(p,m,n);
        }
    //右
    if(i+1<m)
        if((*(p+(i+1)*Candy_Num+j))!=0)
        {
            num++;
            (*(p+(i+1)*Candy_Num+j))->clear(p,m,n);
        }

    //左上
    if(j-1>=0 && i-1>=0)
        if((*(p+(i-1)*Candy_Num+(j-1)))!=0)
        {
            num++;
            (*(p+(i-1)*Candy_Num+(j-1)))->clear(p,m,n);
        }
    //右上
    if(j-1>=0 && i+1<m)
        if((*(p+(i+1)*Candy_Num+j-1))!=0)
        {
            num++;
            (*(p+(i+1)*Candy_Num+j-1))->clear(p,m,n);
        }
    //右下
    if(j+1<n && i+1<m)
        if((*(p+(i+1)*Candy_Num+j+1))!=0)
        {
            num++;
            (*(p+(i+1)*Candy_Num+j+1))->clear(p,m,n);
        }
    //左下
    if(j+1<n && i-1>=0)
        if((*(p+(i-1)*Candy_Num+j+1))!=0)
        {
            num++;
            (*(p+(i-1)*Candy_Num+j+1))->clear(p,m,n);
        }


    score->add(num);
    candy::clear(p,m,n);
    return 0;
}

int bomb_candy::bechoose()
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

//bomb_candy

//star_candy

star_candy::star_candy(Candy_Score *game_score,QWidget *parent, QPoint pos, int s) : candy(game_score,parent,pos,s)
{
    QString str("star_candy");
    name=str;
    size=s;
    img=QPixmap(":/img/candy/img/"+name+".png").scaled(size,size);
    label->setPixmap(img);
    img_choose=QPixmap(":/img/candy/img/"+name+"_choose.png").scaled(size,size);
    value=candy_color_value(name);
}

star_candy::~star_candy()
{

}

int star_candy::clear(candy** p,int m,int n)
{
    if(other_name.length()==0)
        return 0;
    else
    {
        int v=candy_color_value(other_name);
        if(v==1)
        {
            int num=(m*n)/2;

        }
        else
        {

            for(int i=0;i<m;i++)
                for(int j=0;j<n;j++)
                {
                    if((*(p+i*Candy_Num+j))!=0)
                    {
                        if((*(p+i*Candy_Num+j))->value==v)
                        {
                            (*(p+i*Candy_Num+j))->clear(p,m,n);
                            score->add(1);
                        }
                    }
                }

        }
    }
    candy::clear(p,m,n);
    return 0;
}

int star_candy::bechoose()
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

    return 1;
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


void candy::clear_candy(candy **p, int num[], int i, int j,int start,int end,int m,int n)
{


    t.restart();
    while(t.elapsed()<Move_Second/4)
        QCoreApplication::processEvents();

    if((*(p+i*Candy_Num+j))!=0)
        (*(p+i*Candy_Num+j))->clear(p,m,n);
   // (*(p+i*Candy_Num+j))->label->setVisible(false);
  //  (*(p+i*Candy_Num+j))=0;

    qDebug()<<"剛消除自己";
    for(int d=start;d<end;d++)
    {
        int x,y;
        switch (d) {
        case 0:
            x=0;
            y=-1;
            break;
        case 1:
            x=0;
            y=1;
            break;
        case 2:
            x=-1;
            y=0;
            break;
        case 3:
            x=1;
            y=0;
            break;
        default:
            break;
        }

        for(int s=1;s<=num[d];s++)
        {
            if((*(p+(i+x*s)*Candy_Num+j+(y*s)))!=0)
                (*(p+(i+x*s)*Candy_Num+j+(y*s)))->clear(p,m,n);
        }

    }

}





