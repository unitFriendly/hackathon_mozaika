#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include "myfile.h"

class Message
{
    int id;
    int dialog_id;
    int sender_id;
    QString message_data;
    QDateTime time;
    int status;
    QVector<MyFile> files;
public:
    Message(int _id, int _dialog_id, int _sender_id, QString _message_data, QDateTime _time, int _status):
        id(_id), dialog_id(_dialog_id), sender_id(_sender_id), message_data(_message_data), time(_time), status(_status) {}
    void addFile(MyFile);
    int getId(){return id;};
    int getDialog_id(){return dialog_id;};
    int getSender_id(){return sender_id;};
    QString getMessage_data(){return message_data;};
    QDateTime getTime(){return time;};
    int getStatus(){return status;};
    QVector<MyFile> getFiles(){return files;};
};

#endif // MESSAGE_H
