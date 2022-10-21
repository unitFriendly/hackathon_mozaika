#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include "myfile.h"
#include "Client/protocoltrade.h"

class Message
{
    int id;
    int dialog_id;
    QString sender_login;
    QString message_data;
    QDateTime time;
    int status;
    /*
     * 0 - не доставлено серверу
     * 1 - на сервере
     * 2 - на клиенте
     * 3 - прочитано
    */
    QVector<MyFile> files;
public:
    Message(int _id, int _dialog_id, QString _sender_login, QString _message_data, QDateTime _time, int _status):
        id(_id), dialog_id(_dialog_id), sender_login(_sender_login), message_data(_message_data), time(_time), status(_status) {}
    void addFile(MyFile);
    int getId(){return id;};
    int getDialog_id(){return dialog_id;};
    QString getSender_login(){return sender_login;};
    QString getMessage_data(){return message_data;};
    QDateTime getTime(){return time;};
    int getStatus(){return status;};
    QVector<MyFile> getFiles(){return files;};
//<<<<<<< HEAD
    void setId(int value);
    void setStatus(QString value);
    void setStatus(int value);
//=======

    bool operator<(const Message& d1) const;
    bool operator>(const Message& d1) const;
//>>>>>>> origin/back
};

#endif // MESSAGE_H
