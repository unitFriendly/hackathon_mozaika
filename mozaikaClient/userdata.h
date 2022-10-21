#ifndef USERDATA_H
#define USERDATA_H

#include "QString"
class UserData{
public:
    QString login;
    QString name;
    QString birthdate;
    QString avatarFile;

    UserData(QString _login, QString _name, QString _birthdate, QString _avatarFile):login(_login), name(_name), birthdate(_birthdate), avatarFile(_avatarFile){};
};

#endif // USERDATA_H
