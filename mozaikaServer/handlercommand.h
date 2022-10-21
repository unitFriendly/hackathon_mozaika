#ifndef HANDLERCOMMAND_H
#define HANDLERCOMMAND_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QWebSocket>
#include <protocoltrade.h>
#include <QMap>
#include "generalfunctionsocket.h"
#include "super_server/servercontroller.h"

class HandlerCommand : public QObject
{
    Q_OBJECT
private:
//    static void AuthorizationCommandHandler(QJsonObject* object, DataClientOnline* client);
//    static void GiveIpCommandHandler(QJsonObject* object, DataClientOnline* client);
//    static void GiveIpFromSrcCommandHandler(QJsonObject* object, DataClientOnline* client);
//    static void GiveIpFromDstCommandHandler(QJsonObject* object, DataClientOnline* client);
    static void HandlerCmdSendMessage(QJsonObject* object, DataClientOnline* client);
    static void HandlerCmdSendMessageAnswerFromClient(QJsonObject* object, DataClientOnline* client);

    static void HandlerCmdAuthorization(QJsonObject* object, DataClientOnline* client);

    /// Обработка ответа от клиента на создание приватного чата
    static void CreatePrivateChat(QJsonObject* object, DataClientOnline* client);

    /// Обработка запроса от клиента на создание приватного чата
    static void HandlerReqPrivatChat(QJsonObject* object, DataClientOnline* client);

    /// Обработка запроса от клиента на получение сообщений из конкретного диалога
    static void HandlerReqGetMessageInDialog(QJsonObject* object, DataClientOnline* client);

//    static void SendBinaryMessage(QJsonObject* object, DataClientOnline* client);
    /// Обработка запроса на получение данных о пользователе
    static void ReqGetContact(QJsonObject* object, DataClientOnline* client);

    /// Отправить диалоги пользователю
    static void SendDialogsToUser(DataClientOnline* client);

    /// Обработка запроса на создание чата
    static void CreateChat(QJsonObject *object, DataClientOnline* client);

    /// Обработка изменения статуса сообщения
    static void MarkMessage(QJsonObject* object, DataClientOnline* client);

    /// Оповещение пользователей о прочитанном сообщении
    static void NotifyStatusChanged(QJsonObject* object, DataClientOnline *client);

    /// Получить список связанных логинов
    static void GetNetUsers(DataClientOnline *client);



public:
    /// Прочитать все сообщения чата
    static void ReadAllMessagesByChat(QJsonObject *object, DataClientOnline* client);

    explicit HandlerCommand(QObject *parent = nullptr);

    static void ProcessingEvent(QJsonObject* object, DataClientOnline* client);

    /// Рассылка нового статуса пользователя его друзьям
    static void HandlerUserStautusChange(DataClientOnline *client, QString newStatus);

    /// Обработчик отключения клиента от сети (рассылка обновленного статуса его друзьям)
    static void HandlerUserDisconect(DataClientOnline *client);

    /// Обработчик подключения клиента (рассылка обновленного статуса его друзьям)
    static void HandlerUserConnect(DataClientOnline *client);

signals:

};

#endif // HANDLERCOMMAND_H
