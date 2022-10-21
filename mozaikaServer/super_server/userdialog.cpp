#include "userdialog.h"

void UserDialog::addMessage(Message msg)
{
    messages.append(msg);
}

Message UserDialog::getLastMessage()
{
    if(messages.count()!=0)
        return messages.first();
}

int UserDialog::addMember(User user)
{
    if (!members.contains(user)) {
        members.append(user);
        return 0;
    }
    return 1;
}

QVector<int> UserDialog::getMemberIDs()
{
    QVector<int> ids;
    foreach(User user, members){
        ids.append(user.getID());
    }

    return ids;
}

QVector<QString> UserDialog::getMemberLogins()
{
    QVector<QString> logins;
    foreach(User user, members){
        logins.append(user.getLogin());
    }

    return logins;
}
