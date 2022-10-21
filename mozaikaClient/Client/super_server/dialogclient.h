#ifndef DIALOGCLIENT_H
#define DIALOGCLIENT_H

#include <QObject>

class dialogClient : public QObject
{
    Q_OBJECT
public:
    explicit dialogClient(QObject *parent = nullptr);
    QString name;
    QString pathAvatar;
    QString loginMembers;

    dialogClient(QString _name, QString _path, QString _loginMembers): name(_name), pathAvatar(_path), loginMembers(_loginMembers) {};
    dialogClient(dialogClient& d): name(d.name), pathAvatar(d.pathAvatar), loginMembers(d.loginMembers){};

    const dialogClient operator =(dialogClient user) const{
        dialogClient user2(user);
        return user2;
    }

     friend bool operator==(const dialogClient& userd1, const dialogClient& userd2) { return userd1.name == userd2.name; }

signals:

};

#endif // DIALOGCLIENT_H
