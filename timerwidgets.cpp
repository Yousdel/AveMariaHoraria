#include "timerwidgets.h"

#include <QLCDNumber>
#include <QDateTime>
#include <iostream>


TimerWidgets::TimerWidgets(QLCDNumber *minNumber, QLCDNumber *secsNumber, QObject *parent):
    QObject(parent),
    min(minNumber), secs(secsNumber)
{
    update();
    connect(&t, &QTimer::timeout, this, [=](){update();});
    connect(&t_sound, &QTimer::timeout, this,[&](){
        ++i;
        std::cout<<"\a";
        if (i==0xf){
            t_sound.stop();
            i=0x0;
        }
    });
    t.start(1000);
}

void TimerWidgets::stopEverything()
{
    t.stop(); disable();
}

void TimerWidgets::disable()
{
    t_sound.stop(); activated=0x0;
}

void TimerWidgets::activate()
{
    activated=0x1;
}

void TimerWidgets::update()
{
    QDateTime curr = QDateTime::currentDateTime();
    int minsToNextHour = 60 - curr.time().minute(),//60-curr.time().minute();
            secsToNextMinute= 60 - curr.time().second();/*60 - curr.time().second();*/
    if (minsToNextHour==0x0 && secsToNextMinute==0x0 && activated){
        t_sound.start(1500);
    }
    min->display(minsToNextHour);
    secs->display(secsToNextMinute);
}
