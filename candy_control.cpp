#include "candy_control.h"
#include <QDebug>


candy_control::candy_control(QWidget *parent, QPoint pos, int a, int b) : QWidget(parent),m(a),n(b)
{
    move(pos);
    resize(m*Candy_size,n*Candy_size);
    activing=0;
    create_plate();
}

candy_control::~candy_control()
{

}

int candy_control::create_plate()
{
    srand(time(NULL));

    int r;

    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
        {
          //r=rand()%Candy_Color_Num;
          //char ch=Candy_Color.at(r).toLatin1();
          plate[i][j]=getCandy(this,QPoint(i*Candy_size,j*Candy_size));

        }

    //檢查
    int num[4]={0};
    int stop=1;
    while(stop)
    {
        stop=0;
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(plate[i][j]==0)
                    continue;

                for(int k=0;k<4;k++)
                    num[k]=0;

                int count;

                //上
                count=1;
                while(j-count>=0)
                {
                    if(plate[i][j-count]==0)
                        break;

                    if(plate[i][j]->value==plate[i][j-count]->value)
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
                    if(plate[i][j+count]==0)
                        break;

                    if(plate[i][j]->value==plate[i][j+count]->value)
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
                    if(plate[i-count][j]==0)
                        break;

                    if(plate[i][j]->value==plate[i-count][j]->value)
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
                    if(plate[i+count][j]==0)
                        break;

                    if(plate[i][j]->value==plate[i+count][j]->value)
                    {
                        num[3]++;
                        count++;
                    }
                    else
                        break;
                }
                //判斷完上下左右的數量
                //qDebug()<<i<<","<<j<<" "<<num[0]<<num[1]<<num[2]<<num[3];
                //判斷是否有連線
                if((num[0]+num[1])>=2)//上下有連線
                {
                    stop=1;//繼續迴圈
                    if((num[2]+num[3])>=2)
                    {
                        //上下左右都有連線
                        qDebug()<<"上下左右";
                        //清除
                        delete plate[i][j];
                        plate[i][j]=0;
                        for(int d=0;d<4;d++)
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
                                delete plate[i+x*s][j+y*s];
                                plate[i+x*s][j+y*s]=0;
                            }

                        }
                        //清除
                    }
                    else//左右無連線
                    {
                        qDebug()<<"上下";
                        //清除
                        delete plate[i][j];
                        plate[i][j]=0;
                        for(int d=0;d<2;d++)
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
                                delete plate[i+x*s][j+y*s];
                                plate[i+x*s][j+y*s]=0;
                            }

                        }
                        //清除
                        switch((num[0]+num[1]))
                        {
                        case 2:
                            //直向三個連線
                            break;
                        case 3:
                            //直向四個連線
                            break;
                        case 4:
                        default:
                            //直向五個連線
                            break;
                        }

                    }
                }
                else//上下無連線
                {
                    if((num[2]+num[3])>=2)//左右有連線
                    {
                        qDebug()<<"左右";
                        stop=1;
                        //清除
                        delete plate[i][j];
                        plate[i][j]=0;
                        for(int d=2;d<4;d++)
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
                                delete plate[i+x*s][j+y*s];
                                plate[i+x*s][j+y*s]=0;
                            }

                        }
                        //清除
                        switch((num[2]+num[3]))
                        {
                        case 2:
                            //橫向三個連線
                            break;
                        case 3:
                            //橫向四個連線
                            break;
                        case 4:
                        default:
                            //橫向五個連線
                            break;
                        }
                    }

                }
            }
        }//跑完全部盤面
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(plate[i][j]==0)
                {
                    /*補洞*/
                    for(int k=j;k>0;k--)
                    {
                        plate[i][k]=plate[i][k-1];
                        if(plate[i][k]!=0)
                        {
                        plate[i][k]->location=QPoint(i*Candy_size,k*Candy_size);
                        plate[i][k]->label->move(plate[i][k]->location);
                        }
                    }

                    /*放新的*/
                    //r=rand()%Candy_Color_Num;
                    //char ch=Candy_Color.at(r).toLatin1();
                    plate[i][0]=getCandy(this,QPoint(i*Candy_size,0));
                }
            }
        }
    }//while
    //檢查
    return 0;
}

int candy_control::choose(int i, int j)
{
    static int haschoose=0,choose_i,choose_j;

    int y=0;

    if(!haschoose)
    {
        choose_i=i;
        choose_j=j;
        plate[i][j]->bechoose();
    }
    else
    {
        plate[choose_i][choose_j]->bechoose();

        switch (choose_i-i) {
        case 1:
            if(choose_j==j)
                y=1;
            break;
        case -1:
            if(choose_j==j)
                y=1;
            break;
        case 0:
            if(choose_j-j==1 || choose_j-j==-1)
                y=1;
            break;
        default:
            break;
        }
    }
    if(y)//可以交換
    {
        int effect=0;
        activing=1;

        //交換
        *(plate[choose_i][choose_j])+plate[i][j];
        candy *p=plate[choose_i][choose_j];
        plate[choose_i][choose_j]=plate[i][j];
        plate[i][j]=p;
        //交換

        //前置作業
        if(plate[choose_i][choose_j]->value==1 || plate[i][j]->value==1)//star
        {
            effect=1;
            if(plate[choose_i][choose_j]->value==1)
            {
                plate[choose_i][choose_j]->setOther(plate[i][j]);
                plate[choose_i][choose_j]->clear(plate[0],m,n);
            }
            else
            {
                plate[i][j]->setOther(plate[choose_i][choose_j]);
                plate[i][j]->clear(plate[0],m,n);
            }
        }
        else
        {
            //判斷
            if(plate[choose_i][choose_j]->check(plate[0],m,n))
                effect=1;
            if(plate[i][j]->check(plate[0],m,n))
                effect=1;
            //判斷
        }
        if(effect)//如果有作用，就要補洞
        {
            QParallelAnimationGroup drop;

            QPropertyAnimation *anim;
            int stop=1;
            QTime t;

            while(stop)
            {
                while(stop)
                {
                stop=0;
                drop.clear();
                for(int i=0;i<m;i++)
                {
                    for(int j=n-1;j>=0;j--)
                    {
                        if(plate[i][j]==0)
                        {
                            stop=1;
                            for(int k=j;k>0;k--)
                            {
                                //動畫
                                if(plate[i][k-1]!=0)
                                {
                                    anim=plate[i][k-1]->move_anim(Candy_size,'s',Move_Second*0.6);
                                    drop.addAnimation(anim);
                                    plate[i][k-1]->change=1;
                                }
                                //同步數值
                                plate[i][k]=plate[i][k-1];
                            }
                            plate[i][0]=0;
                            break;
                        }
                    }
                }

                if(stop==0)
                    break;

                //執行動畫
                qDebug()<<"執行動畫";

                drop.start();
                t.restart();
                while(t.elapsed()<Move_Second*0.4)
                    QCoreApplication::processEvents();

                //補入新的candy
                for(int i=0;i<m;i++)
                {
                    if(plate[i][0]==0)
                    {
                        qDebug()<<"放入"<<i;
                        plate[i][0]=getCandy(this,QPoint(i*Candy_size,0));
                        plate[i][0]->change=1;
                    }
                }

                while(t.elapsed()<Move_Second*0.6)
                    QCoreApplication::processEvents();


                }//掉落迴圈

                t.restart();
                while(t.elapsed()<(Move_Second/3))
                    QCoreApplication::processEvents();

                //檢查，找有變化的candy
                qDebug()<<"檢查";
                for(int i=0;i<m;i++)
                {
                    for(int j=0;j<n;j++)
                    {
                        if(plate[i][j]!=0)
                        {
                            if(plate[i][j]->change==1)
                            {
                                if(plate[i][j]->check(plate[0],m,n))
                                    stop=1;
                                else
                                    plate[i][j]->change=0;

                                qDebug()<<"檢查完"<<i<<j;
                            }
                        }
                    }
                }

            }//while
        }


        //如果沒有效果換回來
        if(!effect)
        {
            *(plate[choose_i][choose_j])+plate[i][j];
            p=plate[choose_i][choose_j];
            plate[choose_i][choose_j]=plate[i][j];
            plate[i][j]=p;


        }
        activing=0;
    }
    haschoose++;
    haschoose=haschoose%2;

    return haschoose;
}

int candy_control::check()
{

    return 0;
}

candy *candy_control::getCandy(QWidget *parent, QPoint pos)
{
    //srand(time(NULL));

    int r=rand()%Candy_Color_Num;
    char ch=Candy_Color.at(r).toLatin1();
    //產生普通candy
    candy* p=new normal_candy(parent,pos,ch);

    return p;
}

void candy_control::mousePressEvent(QMouseEvent *e)
{
    if(!activing)
    {
        int x=e->x(),y=e->y();
        x=x/Candy_size;
        y=y/Candy_size;
        if(x>=0 && x<m && y>=0 && y<n)
            choose(x,y);
    }
    qDebug()<<"Mouse";
}
