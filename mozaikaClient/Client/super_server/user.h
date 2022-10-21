#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include "myfile.h"
#include <QVector>
#include <QDate>
#include "message.h"
#include "myvector.h"
//#include "userdialog.h"

//class User;



class User : public QObject
{
        Q_OBJECT
private:
    int id;
    QString login;
    QString name;
    QString birthdate;
    QByteArray avatar;
    QString avatarFile;

public:
        explicit User(QObject *parent = nullptr) : QObject(parent)
        {

        };
    User(User& user): id(user.id), login(user.login), name(user.name), avatar(user.avatar), birthdate(user.birthdate) {};
    User(int _id, QString _login, QString _name, QByteArray _avatar, QString _birthdate): id(_id), login(_login), name(_name), avatar(_avatar), birthdate(_birthdate){}
//    User();
    const User operator =(User user) const{
        User user2(user);
        return user2;
    }

public slots:
    int getID();
    QString getName(){return name;}
    QByteArray getAvatar(){return avatar;}
    QString getBirthDate(){return birthdate;}
    QString getLogin() {return login;}

    QString getAvatarFile();

    void setID(int value) {id = value; }
    void setName(QString str){name = str; }
    void setAvatar(QByteArray tmp){avatar = tmp; }
    void setAvatarFile(QString tmp){avatarFile = tmp; }
    void setBirthDate(QString date){birthdate = date; }
    void setLogin(QString tmp) {login = tmp; }

    //UserDialog dialogs;

    friend bool operator==(const User& user1, const User& user2) { return user1.login == user2.login; }
};

#endif // USER_H
