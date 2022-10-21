#ifndef MASSAGETEST_H
#define MASSAGETEST_H

#include <QObject>
#include <QDebug>

class MassageTest : public QObject
{
    Q_OBJECT
public:
    MassageTest(QObject *parent = nullptr);

    QString message;
    bool status;

public slots:

    void setMulti(QString str, bool flag);

    int getSizeMessagePx();

    QString getMessage();
    bool getStatus();


signals:

};

#endif // MASSAGETEST_H
