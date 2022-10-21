#ifndef USER_H
#define USER_H

#include <QString>
#include "myfile.h"
#include <QVector>
#include <QDate>

class User
{
private:
    int id;
    QString login;
    QString name;
    int avatar_id;
    QDate birthdate;
    User();
public:
    User(int _id, QString _login, QString _name, int _avatar_id, QDate _birthdate): id(_id), login(_login), name(_name), avatar_id(_avatar_id), birthdate(_birthdate){}
    int getID();
    QString getName(){return name;}
    int getAvatarId(){return avatar_id;}
    QDate getBirthDate(){return birthdate;}
    QString getLogin() {return login;}

    friend bool operator==(const User& user1, const User& user2) { return user1.login == user2.login; }
};


#endif // USER_H
