#ifndef TIMERWIDGETS_H
#define TIMERWIDGETS_H

#include <QObject>
#include <QTimer>
#include <QTime>

class QLCDNumber;
class QLabel;
class QSystemTrayIcon;

class TimerWidgets : public QObject
{
    Q_OBJECT
public:
    TimerWidgets(QLCDNumber *minNumber, QLCDNumber *secsNumber,
                 QLabel *label,
            QObject *parent = nullptr   );
    void stopEverything();
    void disable();
    void activate();
    bool automatic() const;
    void updateFromFile();

private:
    QTime m_from, m_to; bool m_automatic=0x0;
    QLCDNumber *min, *secs; bool activated=0x0;
    QLabel *m_label; QSystemTrayIcon *sysTrIcon {nullptr};
    QTimer mainTimer, soundTimer;
    int i=0x0;

    void update();

private slots:
    void tryCreateSysTrIcon();
signals:

};

#endif // TIMERWIDGETS_H
