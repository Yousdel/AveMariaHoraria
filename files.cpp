#include "files.h"

#include <QTime>
#include <QFile>
#include <QDir>

Files::Files()
{

}

void Files::saveAutoTimes(const QTime &from, const QTime &to, bool automatic)
{
    QFile f(QDir::currentPath()+"/times.txt");
    if (!f.open(QIODevice::Text | QIODevice::WriteOnly))
        return;
    QByteArray content;
    content.append(QString::number(from.hour()));
    content.append("\n");
    content.append(QString::number(from.minute()));
    content.append("\n");
    content.append(QString::number(from.second()));
    content.append("\n");
    content.append(QString::number(to.hour()));
    content.append("\n");
    content.append(QString::number(to.minute()));
    content.append("\n");
    content.append(QString::number(to.second()));
    content.append("\n");
    content.append(QString::number(automatic));
    f.write(content);
    f.flush();
    f.close();
}

void Files::readAutoTimes(QTime &from, QTime &to, bool &automatic)
{
    QFile f(QDir::currentPath()+"/times.txt");
    if (!f.open(QIODevice::Text | QIODevice::ReadOnly))
        return;
    const QByteArray content {
        f.readAll()
    };
    QList<QByteArray> l{
        content.split('\n')
    };
    from.setHMS(l.at(0x0).toInt(), l.at(0x1).toInt(), l.at(0x2).toInt());
    to.setHMS(l.at(0x3).toInt(), l.at(0x4).toInt(), l.at(0x5).toInt());
    automatic = l.at(0x6).toInt();
    f.flush();
    f.close();
}
