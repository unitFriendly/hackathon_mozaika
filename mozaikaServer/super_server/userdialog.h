#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QVector>
#include <QString>
#include "message.h"
#include "user.h"
//#include "servercontroller.h"

class UserDialog
{
private:
    int dialog_id;
    QString name;
    int avatar_id;
    bool isGroup;
    QVector<User> members;
    QVector<Message> messages;
public:
    UserDialog(int _dialog_id, bool _isGroup, QString _name="", int _avatar_id=-1): dialog_id(_dialog_id), isGroup(_isGroup), name(_name), avatar_id(_avatar_id) {}
    UserDialog(bool _isGroup, QString _name="", int _avatar_id=-1): UserDialog(-1, _isGroup, _name, _avatar_id) {}

    void addMessage(Message msg);
    UserDialog(){};
    QVector<Message> getMessages() {return messages;}
    Message getLastMessage();
    int addMember(User user);
    QString getName() {return name;}
    bool getIsGroup() {return isGroup;}
    int getAvatarID() {return avatar_id;}
    QVector<int> getMemberIDs();
    QVector<QString> getMemberLogins();
    QVector<User> getMembers() {return members;}
    void setID(int id) {dialog_id = id;}
    int getID() {return dialog_id;}
};

#endif // USERDIALOG_H
