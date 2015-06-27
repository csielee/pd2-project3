#include "candycrash.h"
#include "candy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CandyCrash *w=new CandyCrash;
    w->show();
    w->resize(1000,700);
    w->move(100,100);


    candy *c1=new candy(w),*c2=new normal_candy(w,QPoint(Candy_size,0));
    candy *c3=new h_candy(w,QPoint(Candy_size*2,0)),*c4=new v_candy(w,QPoint(Candy_size*3,0));
    c1->label->setVisible(true);
    c2->label->setVisible(true);
    c3->label->setVisible(true);
    c4->label->setVisible(true);

    QTime t;
    t.start();
    while(t.elapsed()<1000)
        QCoreApplication::processEvents();

    *c2+c1;

    *c1+c2;

    *c3+c4;

    *c4+c3;

    *c1+c4;

    *c4+c1;

    *c3+c2;

    *c2+c3;








    return a.exec();
}
