#ifndef DATELEFT_H
#define DATELEFT_H

#include <QObject>
#include <QDateTime>

class DateLeft : public QObject
{
    Q_OBJECT
public:
    explicit DateLeft(QObject *parent = nullptr);


    QDate date;

public slots:
    int getLeftDaySecondCall();
    int getLeftDayFirstCall();


signals:

};

#endif // DATELEFT_H
