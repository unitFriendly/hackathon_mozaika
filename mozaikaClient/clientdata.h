#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <QObject>
#include <Client/super_server/userdialog.h>
#include <algorithm>
#include "Client/protocoltrade.h"
#include "userdata.h"


class ClientData : public QObject
{
    Q_OBJECT
public:
    explicit ClientData(QObject *parent = nullptr);

    QVector<UserDialog> dialogs;

//<<<<<<< HEAD
    User *user;

//=======
//    QString myLogin;
//    QString getMyLogin() const;
//    void setMyLogin(const QString &value);
//>>>>>>> origin/back

    QMap<QString, QVector<UserData>> contacts;


public slots:

    QString getCurrentLogin(){return user->getLogin();}

    void saveFile(QString nameFile, QString path);

    void addContact(User* user);
    QString getNameContact(QString login);
    QString getAvatarPathContact(QString login);
    QString getAvatarPathContact(int d_index, int m_index);
    QString getBirthDateContact(QString login);
    int getCountMapContacts();
    int getCountContacts();
    int getCountContactsInMap(QString c);
    QString getCharMapContacts(int index);
    QString getNameContact(QString c, int index);
     QString getLoginContact(QString c, int index);
    QString getPathAvatarContact(QString c, int index);
    QString getBirthDateContact(QString c, int index);

    QVector<UserDialog> getDialogs();
    void setDialogs( QVector<UserDialog> value);
    void sortDialogs();
    void sortDialog(int index);

    UserDialog* getDialogFromId(int id);
    int getCountDialogs() {return dialogs.count();}
    int getCountMembers(int index);
    QString getNameDialog(int index){return dialogs[index].getName();}
    int getIdDialog(int index){return dialogs[index].getID();}
    int getIndexDialog(int id);
    QString getPathAvatar(int index){return dialogs[index].getAvatarPath();}

    QString getTextLastMessage(int index);

    QString getDateLastMessage(int index);
    bool getIsCheckedLastMessage(int index);
    bool getDialogIsGroup(int index);
    int getDialogCountUnChecked(int index);
    bool getDialogIsOnline(int index);
    //    QVector<UserDialog> SortBy(QVector<UserDialog> arr);
    //    bool greater(UserDialog a, UserDialog b);

    QString getLastActiveDateTime(QDateTime date);

//<<<<<<< HEAD
    QString getIdDialogString(int index);

    void AddMessage(QString idDialog, QString idMessage, QString loginSender, QDateTime date, QString status, QString message, QVector<QString> paths);
    void UpdateMessageId(QString idDialog, QString tmpIdMessage, QString idMessage, QString statusMessage);
//    QString getNameDialog(int index){return dialogs[index].();}
//=======
    int getCountMessages(int index);
    QString getTextMessage(int d_index, int m_index);
    bool checkAttachInMsg(int d_index, int m_index);
    QVector<QString> getImageInMsg(int d_index, int m_index);
    QVector<QString> getVideoInMsg(int d_index, int m_index);
    QVector<QString> getMusicInMsg(int d_index, int m_index);
    QVector<QString> getAnyFilesInMsg(int d_index, int m_index);
    QString getFileNameWithoutPath(QString path);

    int getSizeTextMessage(int d_index, int m_index){return getTextMessage(d_index,m_index).length();}
    QString getDateMessage(int d_index, int m_index);
    int getStatusMessage(int d_index, int m_index);
    bool getIsSenderMessage(int d_index, int m_index);

    int getLength(QString text){return text.size();}

    int setAllReadMessageInDialog(int indexDialog);


    bool isExistDialogWithUser(QString login);


    //    QString getNameDialog(int index){return dialogs[index].();}
//>>>>>>> origin/back
signals:

};

#endif // CLIENTDATA_H
