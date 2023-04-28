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
    tryCreateSysTrIcon();
    connect(&mainTimer, &QTimer::timeout, this, [=](){update();});
    connect(&soundTimer, &QTimer::timeout, this,[&](){
        ++i;
        m_label->setText("---Decir un Ave María---");
        if (i==0x1)
            sysTrIcon->showMessage(
                        "Mensaje",
                        "Decir un Ave María",
                        QIcon(":/icono.png"));
        QSound::play(":/Alarm05.wav");
        if (i==0xf){
            soundTimer.stop();
            i=0x0;
        }
    });
}

void TimerWidgets::stopEverything()
{
    mainTimer.stop(); disable();
}

void TimerWidgets::disable()
{
    soundTimer.stop(); activated=0x0;
}

void TimerWidgets::activate()
{
    activated=0x1;
    mainTimer.start(0x3e8);/*.start(1000);*/
}

bool TimerWidgets::automatic() const
{
    return m_automatic;
}

void TimerWidgets::updateFromFile()
{
    Files::readAutoTimes(m_from,m_to,m_automatic);    
}

void TimerWidgets::update()
{
    if (!activated) return;
    QDateTime curr = QDateTime::currentDateTime();
    QDate currDate = curr.date();
    if (curr < QDateTime(currDate, m_from) || curr > QDateTime(currDate, m_to))
    {
        m_label->setText("Desactivado por estar\nfuera"
                         " del horario.\n(para cambiar vaya a Ajustes)");
        return;
    }
    m_label->setText("Faltan:");
    int minsToNextHour = 0x3b - curr.time().minute(),//59-curr.time().minute();
            secsToNextMinute= 0x3b - curr.time().second();/*59 - curr.time().second();*/
    if (minsToNextHour==0x0 && secsToNextMinute==0x0){
        soundTimer.start(0x5dc);/*t_sound.start(1500);*/
    }
    min->display(minsToNextHour);
    secs->display(secsToNextMinute);
}

void TimerWidgets::tryCreateSysTrIcon()
{
    sysTrIcon= new QSystemTrayIcon(this);
    sysTrIcon->setIcon(QIcon(":/icono.ico"));
    sysTrIcon->show();
}
