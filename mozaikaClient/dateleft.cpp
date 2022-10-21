#include "dateleft.h"

DateLeft::DateLeft(QObject *parent) : QObject(parent)
{

}

int DateLeft::getLeftDayFirstCall()
{
    QDate date(2022, 7,6); //Первому призыву 2021 придет свобода

    QDate leftDay = QDate::currentDate();

    return leftDay.daysTo(date);
}

int DateLeft::getLeftDaySecondCall()
{
    QDate date(2022, 12, 9); //Второму призыву придет свобода

    QDate leftDay = QDate::currentDate();

    return leftDay.daysTo(date);
}
