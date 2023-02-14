#ifndef TIMERWIDGETS_H
#define TIMERWIDGETS_H

#include <QObject>
#include <QTimer>

class QLCDNumber;

class TimerWidgets : public QObject
{
    Q_OBJECT
public:
    TimerWidgets(
            QLCDNumber *minNumber,QLCDNumber *secsNumber,
            QObject *parent = nullptr   );
    void stopEverything();
    void disable();
    void activate();

private:
    QLCDNumber *min, *secs; bool activated=0x0;
    QTimer t, t_sound;
    int i=0x0;

    void update();

signals:

};

#endif // TIMERWIDGETS_H
