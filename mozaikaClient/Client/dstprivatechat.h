#ifndef DSTPRIVATECHAT_H
#define DSTPRIVATECHAT_H

#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QFile>
#include <QSslKey>
#include "protocoltrade.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class DstPrivateChat : public QObject
{
    Q_OBJECT
public:
    DstPrivateChat(QString loginDst, QString myLogin, quint16 port, QObject *parent = nullptr);
    QString myLogin;
    DataClientOnline client;
    QString idPrivateChat;

    static void SendPrivateMessage(QString tmpIdMsg, QString textMsg, QVector<QString> paths, QWebSocket* socket);

    static void ProcessingEventFromOtherClient(QJsonObject* object, DataClientOnline* client, QString idChat);

    ///Обработчик получения нового приватного сообщения
    static void HandlerCmdSendPrivateMessage(QJsonObject* object, DataClientOnline* client, QString idChat);

    ///Обработчик ответа после отправки приватного сообщения
    static void HandlerCmdSendPrivateMessageAnswerServer(QJsonObject* object, DataClientOnline* client, QString idChat);
signals:


private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void onSslErrors(const QList<QSslError> &errors);

private:
    QWebSocketServer *m_pWebSocketServer;

};



#endif // DSTPRIVATECHAT_H
