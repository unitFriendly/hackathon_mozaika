#include "servergeneral.h"

ServerGeneral::ServerGeneral(QObject *parent) : QObject(parent)
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

    if (m_pWebSocketServer->listen(QHostAddress::Any, PORT_LISTENER))
    {
        qDebug() << "SSL Echo Server listening on port" << PORT_LISTENER;

        connect(m_pWebSocketServer,
                &QWebSocketServer::newConnection,
                this,
                &ServerGeneral::onNewConnection);

        connect(m_pWebSocketServer,
                &QWebSocketServer::sslErrors,
                this,
                &ServerGeneral::onSslErrors);
    }
}

void ServerGeneral::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    qDebug() << "Client connected:" << pSocket->peerPort();

    connect(pSocket,
            &QWebSocket::textMessageReceived,
            this,
            &ServerGeneral::processTextMessage);

    connect(pSocket,
            &QWebSocket::binaryMessageReceived,
            this,
            &ServerGeneral::processBinaryMessage);

    connect(pSocket,
            &QWebSocket::disconnected,
            this,
            &ServerGeneral::socketDisconnected);

    static int i = 1;
    GeneralFunctionSocket::m_clients.push_back({pSocket, QString::number(i), true});
    i++;
}

void ServerGeneral::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    qDebug() << message;

    QJsonObject object = ProtocolTrade::StringToJsonObject(message);

    HandlerCommand::ProcessingEvent(&object, GeneralFunctionSocket::FindClient(pClient));
}

void ServerGeneral::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    qDebug() << message;

//    QJsonObject object = ProtocolTrade::StringToJsonObject(message);

//    DataClientOnline dataClientOnline;
//    dataClientOnline.socket = pClient;

//    HandlerCommand::ProcessingEvent(&object, &dataClientOnline);


//    if (pClient)
//    {
//        pClient->sendBinaryMessage(message);
//    }
}

void ServerGeneral::socketDisconnected()
{
    qDebug() << "Client disconnected";

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    HandlerCommand::HandlerUserDisconect(GeneralFunctionSocket::FindClient(pClient));

//    if (pClient)
//    {
//        GeneralFunctionSocket::RemoveClient(pClient);
//        pClient->deleteLater();
//    }
}

void ServerGeneral::onSslErrors(const QList<QSslError> &errors)
{
    qDebug() << "Ssl errors occurred";
}
