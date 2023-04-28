#ifndef FILES_H
#define FILES_H

class QTime;

class Files
{
public:
    Files();
    static void saveAutoTimes(const QTime &from, const QTime &to, bool automatic);
    static void readAutoTimes(QTime &from, QTime &to, bool &automatic);
    static void saveStartupSelection(bool b);
    static void readStartupSelection(bool &b);
};

#endif // FILES_H
