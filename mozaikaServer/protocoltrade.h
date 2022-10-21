#ifndef PROTOCOLTRADE_H
#define PROTOCOLTRADE_H

#include <QObject>
#include <QFile>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>

struct DataClientOnline
{
    QWebSocket* socket;
    QString login;
    bool isAuthorized;
};

class ProtocolTrade : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolTrade(QObject *parent = nullptr);

    const static QString ___COMMAND;

    //~~~~~commands start~~~~~
    const static QString ___CMD_AUTHORIZATION;
    const static QString ___CMD_GET_CHATS;
    const static QString ___CMD_GET_MESSAGES;
    const static QString ___CMD_CREATE_PRIVATE_CHAT;
    const static QString ___CMD_SEND_MESSAGE;
    const static QString ___CMD_CREATE_CHAT;
    const static QString ___CMD_GET_DATE_USER;
    const static QString ___CMD_UPDATE_STATUS_MESSAGE;
    const static QString ___CMD_GET_USERS_FROM_DIALOG;
    const static QString ___CMD_UPDATE_STATUS_USER;
    const static QString ___CMD_READ_ALL_MESSAGE_BY_CHAT;
    const static QString ___CMD_UDATE_CHAT;
    //~~~~~commands end~~~~~~~

    const static QString ___LOGIN;
    const static QString ___PASSWORD;
    const static QString ___STATUS;

    //~~~~~status start~~~~~
    const static QString ___STS_DONE;
    const static QString ___STS_NOPE;
    //~~~~~status end~~~~~~~

    const static QString ___USER_NAME;
    const static QString ___AVATAR;
    const static QString ___BINARY_FILE;
    const static QString ___NAME_FILE;
    const static QString ___TYPE_FILE;
    const static QString ___BIRTH_DATE;
    const static QString ___ARR_CHATS;
    const static QString ___ID_CHAT;
    const static QString ___CHAT_GROUP;
    const static QString ___ARR_USERS;
    const static QString ___ARR_MESSAGES;
    const static QString ___ID_MESSAGE;
    const static QString ___TEXT_MESSAGE;
    const static QString ___ARR_ATTACHMENT;
    const static QString ___STATUS_MESSAGE;
    const static QString ___COUNT_MESSAGE;

    //~~~~~status message start~~~~~
    const static QString ___STS_READ;
    const static QString ___STS_TAKEN;
    const static QString ___STS_NON_TAKEN;
    const static QString ___STS_ON_SERVER;
    //~~~~~status message end~~~~~~~

    const static QString ___IP_USER;
    const static QString ___PORT_USER;
    const static QString ___TMP_ID_MESSAGE;
    const static QString ___TMP_ID_CHAT;
    const static QString ___STATUS_USER;

    //~~~~~status user start~~~~~
    const static QString ___STS_ONLINE;
    const static QString ___STS_OFFLINE;
    //~~~~~status user end~~~~~~~

    static QString ByteArrayToString(QByteArray array);
    static QByteArray StringToByteArray(QString string);
    static bool CompareSocket(QWebSocket* a, QWebSocket* b);
    static void SaveBinaryFile(QString binary, QString name, QString type, QString idMsg, QString idChat, QString path = "C:\\Users\\test\\Desktop\\HackathonApril\\Client\\BufferAttachment");
    static void SendTextMessage(QString message, QWebSocket *client);
    static void SendBinaryMessage(QByteArray message, QWebSocket *client);
    static QString jsonObjectToString(QJsonObject *object);
    static QJsonObject StringToJsonObject(QString str);
    static QByteArray LoadBinaryFile(QString path);
    static QString GetTypeFromPathFile(QString path);
    static QString GetNameFromPathFile(QString path);

signals:

};

#endif // PROTOCOLTRADE_H
