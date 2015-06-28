#include "candycrash.h"
//#include "candy_control.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CandyCrash *w=new CandyCrash;

    w->show();

    return a.exec();
}
