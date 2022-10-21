#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H
#define svalue(a) query.value(a).toString()
#define ivalue(a) query.value(a).toInt()
#define tostr(a) QString::number(a)

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QCryptographicHash>
#include "user.h"
#include "userdialog.h"

class ServerController
{
private:
    QSqlDatabase db;
    QVector<User> users;

    static ServerController* instance;
    ServerController();
    bool startServer();
    void shutdownServer();
    int loadUsers();
    int getLastIdMessageDialog(int dialog_id);
public:
    static ServerController * getInstance();
    static QString  pathGarbage;
    int loadData();
    MyFile getFile(int id);
    QByteArray getFileBytes(int id);
    QVector<UserDialog> getUserDialogs(int user_id);
    UserDialog getDialog(int dialog_id, int user_id);

    int addMessage(int dialog_id, int sender_id, QString msg, QMap<QString, QByteArray> files);
    int markMessage(int m_id, int d_id, int status);
    int markMessages(int user_id, int d_id);
    int addFile(QByteArray bytes, QString name, QString type);

    int confirmAuthorization(QString login, QString passhash);
    User* getUser(int id);
    User* getUser(QString login);

    bool addMemeber(int dialog_id, int member_id);
    bool addDialog(UserDialog* dialog);
    bool renameDialog(int id, QString name);
    bool changeAvatarDialog(int id, QByteArray file);
    bool updateUserInfo(User user, QByteArray avatar);

    int getCountDayFromDembel();

    /// список связанных юзеров
    QVector<QString> getNetUsers(QString login);

    /// прочитать сообщения чата
    void readAllMessagesByChat(QString login, int chat_id);
};



#endif // SERVERCONTROLLER_H
