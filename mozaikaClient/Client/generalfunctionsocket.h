#ifndef GENERALFUNCTIONSOCKET_H
#define GENERALFUNCTIONSOCKET_H

#include <QObject>
#include <QWebSocket>
#include "protocoltrade.h"

class GeneralFunctionSocket : public QObject
{
    Q_OBJECT
public:
    explicit GeneralFunctionSocket(QObject *parent = nullptr);

    static void RemoveClient(QWebSocket *client);

    static DataClientOnline* FindClient(QWebSocket *client);
    static DataClientOnline* FindClient(QString login);

    static QVector<DataClientOnline> m_clients;



signals:

};

#endif // GENERALFUNCTIONSOCKET_H
