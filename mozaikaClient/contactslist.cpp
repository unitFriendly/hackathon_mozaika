#include "contactslist.h"

ContactsList::ContactsList(QObject *parent) : QObject(parent)
{

    QVector<QString> arrayA = {"Азман Андрей", "Афанасьев Никита", "Абрамов Михаил", "Толоконников Святослав", "Брагин Александр", "Костриков Владимир", "Бабушкин Игорь", "Горбунов Максим", "Горбунов Сергей", "Кирянов Николай", "Балбес Балбесович", "Костарев Станислав", "Иванов Андрей", "Назаров Алексей"};

    foreach(QString contact, arrayA)
    {
        map[contact.at(0).toUpper()].append(contact);
    }

    list = map.keys();
}

int ContactsList::getCountIndexMessage()
{
    return countIndexMessage++;
}

void ContactsList::setCountIndexMessage(int value)
{
    countIndexMessage = value;
}

void ContactsList::setMulti(QString symbol, QVector<QString> tmp)
{

}

QString ContactsList::getSymbol(int index)
{
    return list[index];
}

QString ContactsList::getName(QString str, int index)
{
//    qDebug() << "getName"<< map[list.at(index)][index];
    return map[str][index];
}

int ContactsList::getMapSize()
{
    return map.size();
}

int ContactsList::getVectorSize(int index)
{
    qDebug() <<map[list[index]].size();
    return map[list[index]].size();
}

int ContactsList::getAllVectorSize()
{
    int tmp = 0;
    for (int i = 0; i < map.size(); i++)
    {
        tmp += getVectorSize(i);
    }
    qDebug() << tmp;
    return tmp;
}
