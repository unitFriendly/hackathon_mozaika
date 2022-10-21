#include "dstprivatechat.h"

void DstPrivateChat::SendPrivateMessage(QString tmpIdMsg, QString textMsg, QVector<QString> paths, QWebSocket *socket)
{
    QJsonObject* jObj = new QJsonObject({
                                              {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_SEND_PRIVATE_MESSAGE)},
                                              {ProtocolTrade::___TMP_ID_MESSAGE, QJsonValue(tmpIdMsg)}
                                          });

    if(!textMsg.isEmpty())
    {
        jObj->insert(ProtocolTrade::___TEXT_MESSAGE, QJsonValue(textMsg));
    }

    if(!paths.isEmpty())
    {
        QJsonArray arrAttachment;
        QJsonObject tmpJsonObject;
        QByteArray array;

        for(int i = 0; i < paths.size(); i++)
        {
            array = ProtocolTrade::LoadBinaryFile(paths[i]);
            tmpJsonObject.insert(ProtocolTrade::___BINARY_FILE, QJsonValue(ProtocolTrade::ByteArrayToString(array)));
            tmpJsonObject.insert(ProtocolTrade::___NAME_FILE, QJsonValue(ProtocolTrade::GetNameFromPathFile(paths[i])));
            tmpJsonObject.insert(ProtocolTrade::___TYPE_FILE, QJsonValue(ProtocolTrade::GetTypeFromPathFile(paths[i])));

            arrAttachment.push_back(tmpJsonObject);
        }

        jObj->insert(ProtocolTrade::___ARR_ATTACHMENT, arrAttachment);
    }

    ProtocolTrade::SendTextMessage(ProtocolTrade::JsonObjectToString(jObj), socket);
}
void DstPrivateChat::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

        qDebug() << "Client connected:" << pSocket->peerPort();

        connect(pSocket,
                &QWebSocket::textMessageReceived,
                this,
                &DstPrivateChat::processTextMessage);

        connect(pSocket,
                &QWebSocket::binaryMessageReceived,
                this,
                &DstPrivateChat::processBinaryMessage);

        connect(pSocket,
                &QWebSocket::disconnected,
                this,
                &DstPrivateChat::socketDisconnected);

        client.isAuthorized = true;
        client.socket = pSocket;

        disconnect(m_pWebSocketServer,
                   &QWebSocketServer::newConnection,
                   this,
                   &DstPrivateChat::onNewConnection);
}

void DstPrivateChat::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    qDebug() << message;

    if(ProtocolTrade::CompareSocket(pClient, client.socket))
    {
        QJsonObject object = ProtocolTrade::StringToJsonObject(message);

        DstPrivateChat::ProcessingEventFromOtherClient(&object, &client, idPrivateChat);
    }
    else
    {
        qDebug() << "ERROR: Подключился другой пользователь";
    }




}

void DstPrivateChat::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    qDebug() << message;
}

void DstPrivateChat::socketDisconnected()
{
    qDebug() << "Client disconnected";

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    if (pClient)
    {
        client.isAuthorized = false;
        client.socket->deleteLater();
    }
}

void DstPrivateChat::onSslErrors(const QList<QSslError> &errors)
{
    qDebug() << "Ssl errors occurred";
}

DstPrivateChat::DstPrivateChat(QString loginDst, QString myLogin, quint16 port, QObject *parent) : QObject(parent)
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("SSL Server"),
                                                  QWebSocketServer::NonSecureMode,
                                                  this);
        QSslConfiguration sslConfiguration;
        QFile certFile(QStringLiteral(":/localhost.cert"));
        QFile keyFile(QStringLiteral(":/localhost.key"));
        certFile.open(QIODevice::ReadOnly);
        keyFile.open(QIODevice::ReadOnly);
        QSslCertificate certificate(&certFile, QSsl::Pem);
        QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);
        certFile.close();
        keyFile.close();
        sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
        sslConfiguration.setLocalCertificate(certificate);
        sslConfiguration.setPrivateKey(sslKey);
        m_pWebSocketServer->setSslConfiguration(sslConfiguration);

        if (m_pWebSocketServer->listen(QHostAddress::Any, port))
        {
            qDebug() << "SSL Echo Server listening on port" << port;

            connect(m_pWebSocketServer,
                    &QWebSocketServer::newConnection,
                    this,
                    &DstPrivateChat::onNewConnection);

            connect(m_pWebSocketServer,
                    &QWebSocketServer::sslErrors,
                    this,
                    &DstPrivateChat::onSslErrors);
        }

        client.login = loginDst;
        this->myLogin = myLogin;
        idPrivateChat = "1337";
}

void DstPrivateChat::HandlerCmdSendPrivateMessage(QJsonObject *object, DataClientOnline *client, QString idChat)
{
    // Обработка входных данных
    QString tmpIdMessage = ((*object)[ProtocolTrade::___TMP_ID_MESSAGE]).toString();
    QString messageText = "";
    QJsonArray arrAttachment;

    if (!object->find(ProtocolTrade::___TEXT_MESSAGE)->isUndefined())
    {
        messageText = ((*object)[ProtocolTrade::___TEXT_MESSAGE]).toString("");
    }

    if (!object->find(ProtocolTrade::___ARR_ATTACHMENT)->isUndefined())
    {
        arrAttachment = ((*object)[ProtocolTrade::___ARR_ATTACHMENT]).toArray();
    }

    if(arrAttachment.size() > 0)
    {
        QJsonObject jObj;

        for(int i = 0; i < arrAttachment.size(); i++)
        {
            jObj = arrAttachment[i].toObject();
            ProtocolTrade::SaveBinaryFile(
                    jObj[ProtocolTrade::___BINARY_FILE].toString(),
                    jObj[ProtocolTrade::___NAME_FILE].toString(),
                    jObj[ProtocolTrade::___TYPE_FILE].toString(),
                    "idMessage",
                    "idChat");
        }
    }

    // Формирование ответа серверу
    QJsonObject* answer = new QJsonObject({
                                              {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_SEND_PRIVATE_MESSAGE)},
                                              {ProtocolTrade::___TMP_ID_MESSAGE, QJsonValue(tmpIdMessage)},
                                              {ProtocolTrade::___STATUS_MESSAGE, QJsonValue(ProtocolTrade::___STS_TAKEN)}
                                          });

    ProtocolTrade::SendTextMessage(ProtocolTrade::JsonObjectToString(answer), client->socket);
}

void DstPrivateChat::HandlerCmdSendPrivateMessageAnswerServer(QJsonObject *object, DataClientOnline *client, QString idChat)
{
    QString tmpIdMessage = ((*object)[ProtocolTrade::___TMP_ID_MESSAGE]).toString();
    QString statusMessage = ((*object)[ProtocolTrade::___STATUS_MESSAGE]).toString();
}

void DstPrivateChat::ProcessingEventFromOtherClient(QJsonObject *object, DataClientOnline *client, QString idChat)
{
    QString commandFromClient = ((*object)[ProtocolTrade::___COMMAND]).toString();

    if(commandFromClient == ProtocolTrade::___CMD_SEND_PRIVATE_MESSAGE)
    {
        if(object->find(ProtocolTrade::___STATUS_MESSAGE)->isUndefined())
        {
            // обработка входящего сообщения
            HandlerCmdSendPrivateMessage(object, client, idChat);
        }
        else
        {
            // обработка ответа после отправленного сообщения
            HandlerCmdSendPrivateMessageAnswerServer(object, client, idChat);
        }
    }
}

