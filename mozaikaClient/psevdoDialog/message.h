#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include "myfile.h"

class Message
{
private:
    int id;
    bool is_user_sender;
    QString message_data;
    QDateTime time;
    bool is_checked;
    QVector<MyFile> files;
public:
    Message(int _id, bool _is_user_sender, QString _message_data, QDateTime _time, bool _is_checked): id(_id), is_user_sender(_is_user_sender), message_data(_message_data), time(_time), is_checked(_is_checked) {}
    void addFile(MyFile);
};

#endif // MESSAGE_H
