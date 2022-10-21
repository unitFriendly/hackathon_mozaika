#ifndef HANDLECOMMAND_H
#define HANDLECOMMAND_H

#include <QObject>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "protocoltrade.h"
#include "fix.h"
#include "super_server/userdialog.h"
#include "super_server/user.h"

class HandlerCommand : public QObject
{
    Q_OBJECT
private:

public:
    ///Обработчик ответа от сервера на авторизацию
    static void HandlerCmdAuthorization(QJsonObject* object, QWebSocket* client);

    ///Обработчик получения нового сообщения
    static void HandlerCmdSendMessage(QJsonObject* object, QWebSocket* client);

    ///Обработчик ответа после отправки сообщения
    static void HandlerCmdSendMessageAnswerServer(QJsonObject* object, QWebSocket* client);

    explicit HandlerCommand(QObject *parent = nullptr);

    static void ProcessingEventFromServer(QJsonObject* object, QWebSocket* socket);

    /// Отправка запроса на создание приватного чата
    static void CreatePrivateChat(QString receiver_login, QWebSocket *socket);

    /// Обработка разрешения на создание приватного чата
    static void GetReqPrivateChat(QJsonObject* qObj, QWebSocket *socket);

    /// Получение ответа на создание приватного чата
    static void GetAnswerCreatePrivateChat(QJsonObject* qObj, QWebSocket *socket);

    static void SendMessage(QString idChat, QString tmpIdMsg, QString textMsg, QVector<QString> paths, QWebSocket* socket);
    static void Authorization(QString login, QString password, QWebSocket* socket);
    static void SendPrivateMessage(QString tmpIdMsg, QString textMsg, QVector<QString> paths, QWebSocket* socket);
    /// Запрос клиента на получение сообщений из конкретного диалога
    static void GetMessagesInDialog(QString idChat, QWebSocket *socket);

    /// Получение ответа от сервера на запрос сообщений из конкретного чата
    static void GetAnswerMessagesInDialog(QJsonObject* qObj, QWebSocket *socket);

    /// Запрос на получение контакта
    static void GetContact(QString login, QWebSocket *socket);

    /// Ответ на запрос на получение контакта
    static void GetAnswerContact(QJsonObject* qObj, QWebSocket *socket);

    /// Запрос на получение списка всех диалогов
    static void GetMyDialogs(QWebSocket *socket);

    /// Ответ на запрос получения списка всех диалогов
    static void AnswerMyDialogs(QJsonObject* qObj, QWebSocket *socket);

    /// Отправка запроса на создание чата
    static void CreateChat(QVector<QString> logins, QString name, QByteArray avatar, QWebSocket *socket);

signals:


};

#endif // HANDLECOMMAND_H
