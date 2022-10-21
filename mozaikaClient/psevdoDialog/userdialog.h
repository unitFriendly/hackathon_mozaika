#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QVector>
#include <QString>
#include "message.h"

class UserDialog
{
private:
    int buddy_id;
    QVector<Message> messages;
public:
    UserDialog(int _buddy_id): buddy_id(_buddy_id) {}
    void addMessage(Message msg);
    UserDialog(){};
};

#endif // USERDIALOG_H
