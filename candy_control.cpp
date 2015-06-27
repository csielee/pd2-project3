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
          r=rand()%Candy_Color_Num;
          char ch=Candy_Color.at(r).toLatin1();
          plate[i][j]=new normal_candy(this,QPoint(i*Candy_size,j*Candy_size),ch);
          plate[i][j]->label->setVisible(true);
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
                for(int k=0;k<4;k++)
                    num[k]=0;

                int count;

                //上
                count=1;
                while(j-count>=0)
                {
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
                    if(plate[i][j]->value==plate[i+count][j]->value)
                    {
                        num[3]++;
                        count++;
                    }
                    else
                        break;
                }
                //判斷完上下左右的數量
                qDebug()<<i<<","<<j<<" "<<num[0]<<num[1]<<num[2]<<num[3];
                //判斷是否有連線
                if(num[0]+num[1]>=2)//上下有連線
                {
                    //stop=1;//繼續迴圈
                }
                else//上下無連線
                {
                    if(num[2]+num[3]>=2)//左右有連線
                    {
                       // stop=1;
                    }

                }
            }
        }//跑完全部盤面
    }
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
    if(y)
    {
        activing=1;
        *(plate[choose_i][choose_j])+plate[i][j];
        candy *p=plate[choose_i][choose_j];
        plate[choose_i][choose_j]=plate[i][j];
        plate[i][j]=p;
        activing=0;
    }
    haschoose++;
    haschoose=haschoose%2;

    return haschoose;
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
