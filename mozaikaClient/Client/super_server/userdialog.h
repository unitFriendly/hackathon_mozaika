#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QVector>
#include <QString>
#include "message.h"
#include "user.h"
#include "myvector.h"
//#include "servercontroller.h"

class UserDialog
{

private:
    int dialog_id;
    QString name;
    bool isGroup;
    QByteArray avatar;
    QString avatarPath;

public:
    QVector<QString> members;
    QVector<Message> messages;
//<<<<<<< HEAD
//    UserDialog(int _dialog_id, QString _name="", QByteArray _avatar = nullptr, QString _avatarPath=""): dialog_id(_dialog_id), name(_name), avatar(_avatar), avatarPath(_avatarPath) {}
//    UserDialog(QString _name="", QByteArray _avatar = nullptr): UserDialog(-1, _name, _avatar) {}
//=======
    int countUnChecked;
    bool isOnline;
public:// очень важный комментарий

    UserDialog(int _dialog_id, bool _isGroup, QString _name="", QByteArray _avatar = nullptr, QString _avatarPath=""): dialog_id(_dialog_id),isGroup(_isGroup), name(_name), avatar(_avatar), avatarPath(_avatarPath) {}
    UserDialog( bool _isGroup, QString _name="", QByteArray _avatar = nullptr): UserDialog(-1,_isGroup, _name, _avatar) {}
//>>>>>>> origin/back



    void addMessage(Message msg);
//    UserDialog(){};
    QVector<Message> getMessages() {return messages;}
    void setMessages( QVector<Message> ms) {messages=ms;}
    Message getLastMessage();
    int addMember(User* user);
    QString getName() {return name;}
    bool getIsGroup() {return isGroup;}
    bool setIsGroup(bool _isGroup) {isGroup = _isGroup;}
    QByteArray getAvatar() {return avatar;}
    QString getAvatarPath() {return avatarPath;}
//    QVector<int> getMemberIDs();
    QVector<QString> getMemberLogins();
    void setID(int id) {dialog_id = id;}
    int getID() {return dialog_id;}

    bool operator<(const UserDialog& d1) const;
    bool operator>(const UserDialog& d1) const;
    int getCountUnChecked();
    void setCountUnChecked(int value);
    bool getIsOnline();
    void setIsOnline(bool value);

    void SortBy();
};

#endif // USERDIALOG_H
