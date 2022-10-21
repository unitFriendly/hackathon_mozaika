#ifndef SERVERGENERAL_H
#define SERVERGENERAL_H

#include <QObject>
#include <QWebSocketServer>
#include <QFile>
#include <QSslKey>
#include <QWebSocket>
#include "generalfunctionsocket.h"
#include "handlercommand.h"
#include "protocoltrade.h"


class ServerGeneral : public QObject
{
    Q_OBJECT
public:
    explicit ServerGeneral(QObject *parent = nullptr);

signals:

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void onSslErrors(const QList<QSslError> &errors);

private:
    const quint16 PORT_LISTENER = 1234;

    QWebSocketServer *m_pWebSocketServer;


};

#endif // SERVERGENERAL_H
