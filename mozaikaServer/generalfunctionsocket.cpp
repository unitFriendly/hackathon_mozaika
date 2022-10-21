#include "generalfunctionsocket.h"

QVector<DataClientOnline> GeneralFunctionSocket::m_clients = QVector<DataClientOnline>();

GeneralFunctionSocket::GeneralFunctionSocket(QObject *parent) : QObject(parent)
{

}

void GeneralFunctionSocket::RemoveClient(QWebSocket *client)
{
    for(int i = 0; i < m_clients.count(); i++)
    {
        if((m_clients[i].socket->peerAddress() == client->peerAddress()) && (m_clients[i].socket->peerPort() == client->peerPort()))
        {
            m_clients.remove(i);
        }
    }
}

DataClientOnline* GeneralFunctionSocket::FindClient(QWebSocket *client)
{
    for(int i = 0; i < m_clients.count(); i++)
    {
        if((m_clients[i].socket->peerAddress() == client->peerAddress()) && (m_clients[i].socket->peerPort() == client->peerPort()))
        {
            return &(m_clients[i]);
        }
    }

    return nullptr;
}

DataClientOnline* GeneralFunctionSocket::FindClient(QString login)
{
    for(int i = 0; i < m_clients.count(); i++)
    {
        if(m_clients[i].login == login)
        {
            return &(m_clients[i]);
        }
    }

    return nullptr;
}
