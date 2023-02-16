#include "timerwidgets.h"

#include <QLCDNumber>
#include <QLabel>
#include <QDateTime>
#include <QSound>
#include <QSystemTrayIcon>
#include "files.h"

TimerWidgets::TimerWidgets(QLCDNumber *minNumber,
                           QLCDNumber *secsNumber, QLabel *label,
                           QObject *parent):
    QObject(parent),
    min(minNumber), secs(secsNumber), m_label(label)
{
    updateFromFile();
    update();
    connect(&t, &QTimer::timeout, this, [=](){update();});
    connect(&t_sound, &QTimer::timeout, this,[&](){
        ++i;
        m_label->setText("---Decir un Ave María---");
        QSystemTrayIcon ti(this);
        ti.showMessage("Mensaje", "Decir un Ave María",QIcon(":/icono.ico"));
        QSound::play(":/Alarm05.wav");
        if (i==0xf){
            t_sound.stop();
            i=0x0;
        }
    });
    t.start(0x3e8);/*t.start(1000);*/
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

bool TimerWidgets::automatic() const
{
    return m_automatic;
}

void TimerWidgets::updateFromFile()
{
    Files::readAutoTimes(m_from,m_to,m_automatic);
    if (m_automatic)
        activate();
}

void TimerWidgets::update()
{
    QDateTime curr = QDateTime::currentDateTime();
    QDate currDate = curr.date();
    if (curr < QDateTime(currDate, m_from) || curr > QDateTime(currDate, m_to))
    {
        m_label->setText("Desactivado por estar\nfuera del horario.\n(para cambiar vaya a Ajustes)");
        return;
    }
    m_label->setText("Faltan:");
    int minsToNextHour = 0x3b - curr.time().minute(),//59-curr.time().minute();
            secsToNextMinute= 0x3b - curr.time().second();/*59 - curr.time().second();*/
    if (minsToNextHour==0x0 && secsToNextMinute==0x0 && activated){
        t_sound.start(0x5dc);/*t_sound.start(1500);*/
    }
    min->display(minsToNextHour);
    secs->display(secsToNextMinute);
}
