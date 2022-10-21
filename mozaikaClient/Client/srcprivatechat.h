#ifndef SRCPRIVATECHAT_H
#define SRCPRIVATECHAT_H

#include <QObject>
#include <QWebSocket>

#include "protocoltrade.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class SrcPrivateChat : public QObject
{
    Q_OBJECT
public:
    SrcPrivateChat(QString loginDst, QString myLogin, quint16 port, QString ip, QObject *parent = nullptr);
    DataClientOnline server;
    QString idPrivateChat;
    QString myLogin;

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onSslErrors(const QList<QSslError> &errors);

private:
    static void SendPrivateMessage(QString tmpIdMsg, QString textMsg, QVector<QString> paths, QWebSocket* socket);

    static void ProcessingEventFromOtherClient(QJsonObject* object, DataClientOnline* client, QString idChat);

    ///Обработчик получения нового приватного сообщения
    static void HandlerCmdSendPrivateMessage(QJsonObject* object, DataClientOnline* client, QString idChat);

    ///Обработчик ответа после отправки приватного сообщения
    static void HandlerCmdSendPrivateMessageAnswerServer(QJsonObject* object, DataClientOnline* client, QString idChat);

signals:

};

#endif // SRCPRIVATECHAT_H
