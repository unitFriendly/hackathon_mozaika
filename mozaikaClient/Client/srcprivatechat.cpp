#include "srcprivatechat.h"

void SrcPrivateChat::SendPrivateMessage(QString tmpIdMsg, QString textMsg, QVector<QString> paths, QWebSocket *socket)
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

SrcPrivateChat::SrcPrivateChat(QString loginDst, QString myLogin, quint16 port, QString ip, QObject *parent) : QObject(parent)
{
    server.socket = new QWebSocket();
    connect(server.socket,
            &QWebSocket::connected,
            this,
            &SrcPrivateChat::onConnected);

    connect(server.socket,
            QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),
            this,
            &SrcPrivateChat::onSslErrors);

    QString strUrl = "ws://" + ip + ":" + QString::number(port);
    server.socket->open(QUrl(strUrl));
    server.login = loginDst;
    this->myLogin = myLogin;
}

void SrcPrivateChat::onConnected()
{
    qDebug() << "WebSocketServer connected";
    connect(server.socket,
            &QWebSocket::textMessageReceived,
            this,
            &SrcPrivateChat::onTextMessageReceived);

    //    socketServer.sendTextMessage(QStringLiteral("Hello, world!"));

//    QVector<QString> paths = {"C:\\Users\\test\\Desktop\\HackathonApril\\ex\\1.txt", "C:\\Users\\test\\Desktop\\HackathonApril\\ex\\5.txt"};

//    HandlerCommand::SendMessage("1", "2", "3", paths, &socketServer);

    //    HandlerCommand::Authorization("1", "1", &socketServer);
}

void SrcPrivateChat::onTextMessageReceived(QString message)
{
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());

    qDebug() << message;

    QJsonObject object = ProtocolTrade::StringToJsonObject(message);

    SrcPrivateChat::ProcessingEventFromOtherClient(&object, &server, idPrivateChat);
}

void SrcPrivateChat::onSslErrors(const QList<QSslError> &errors)
{

}

void SrcPrivateChat::HandlerCmdSendPrivateMessage(QJsonObject *object, DataClientOnline *client, QString idChat)
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

void SrcPrivateChat::HandlerCmdSendPrivateMessageAnswerServer(QJsonObject *object, DataClientOnline *client, QString idChat)
{
    QString tmpIdMessage = ((*object)[ProtocolTrade::___TMP_ID_MESSAGE]).toString();
    QString statusMessage = ((*object)[ProtocolTrade::___STATUS_MESSAGE]).toString();
}

void SrcPrivateChat::ProcessingEventFromOtherClient(QJsonObject *object, DataClientOnline *client, QString idChat)
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

