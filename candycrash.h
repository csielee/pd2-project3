#ifndef CANDYCRASH_H
#define CANDYCRASH_H

#include <QWidget>
#include "candy_control.h"
#include <QPushButton>
#include <QPaintEvent>
#include <QTimer>
#include <QTime>

class CandyCrash : public QWidget
{
    Q_OBJECT

public:
    CandyCrash(QWidget *parent = 0);
    ~CandyCrash();

    candy_control *game;
    QLabel *score,*score_title;
    QLabel *time,*time_title;
    QLabel *target;
    QTime game_time;
    QTimer *game_timer;
    QPushButton *restart,*exit;

protected:
     void paintEvent(QPaintEvent* e);
     void keyPressEvent(QKeyEvent *e);

private slots:
     void on_Timer_Event();
     void game_restart();

};

#endif // CANDYCRASH_H
