#ifndef CLIENTGENERAL_H
#define CLIENTGENERAL_H

#include <QObject>
#include <QtNetwork/QSslError>
#include <QtWebSockets/QWebSocket>
#include "handlercommand.h"
#include <QThread>
#include "clientdata.h"

//#include "super_server/user.h"

class ClientGeneral : public QObject
{
    Q_OBJECT

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onSslErrors(const QList<QSslError> &errors);

private:

    const QUrl URL_SERVER = QUrl(QStringLiteral("ws://localhost:1234"));
//        const QUrl URL_SERVER = QUrl(QStringLiteral("ws://10.0.2.2:1234"));

public:
    explicit ClientGeneral(QObject *parent = nullptr);

    ClientData* clientData;
    QWebSocket socketServer;
public slots:
//    void sendMessage(QString idChat, QString tmpIdMsg, QString textMsg, QVector<QString> paths);
//    void authorization(QString login, QString password);
//    void sendPrivateMessage(QString tmpIdMsg, QString textMsg, QVector<QString> paths);


    //HandlerController
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Обработчик обновления статуса контакта
    void handlerUpdateStatusUser(QJsonObject* object);

    ///Обработчик ответа от сервера на авторизацию
    void handlerCmdAuthorization(QJsonObject* object);

    ///Обработчик получения нового сообщения
    void handlerCmdSendMessage(QJsonObject* object);

    ///Обработчик ответа после отправки сообщения
    void handlerCmdSendMessageAnswerServer(QJsonObject* object);

    ///Обработчик получения запроса на обновление данных в чате
    void handlerCmdUpdateChat(QJsonObject* object);

    void processingEventFromServer(QJsonObject* object);

    /// Отправка запроса на создание приватного чата
    void createPrivateChat(QString receiver_login);

    /// Обработка разрешения на создание приватного чата
    void getReqPrivateChat(QString requester_login, bool isAccepted);

    /// Получение ответа на создание приватного чата
    void getAnswerCreatePrivateChat(QJsonObject* qObj);

    void sendMessage(QString idChat, QString tmpIdMsg, QString textMsg = "", QVector<QString> paths = {});
    void authorization(QString login, QString password, ClientData* clientData);
    void sendPrivateMessage(QString tmpIdMsg, QString textMsg = "", QVector<QString> paths = {});
    void sendReadAllMessageByChat(QString idChat);
    /// Запрос клиента на получение сообщений из конкретного диалога
    void getMessagesInDialog(QString idChat);

    /// Получение ответа от сервера на запрос сообщений из конкретного чата
    void getAnswerMessagesInDialog(QJsonObject* qObj);

    /// Запрос на получение контакта
    void getContact(QString login);

    /// Ответ на запрос на получение контакта
    void getAnswerContact(QJsonObject* qObj);

    /// Запрос на получение списка всех диалогов
    void getMyDialogs();

    /// Ответ на запрос получения списка всех диалогов
    void answerMyDialogs(QJsonObject* qObj);

    /// Отправка запроса на создание чата
    void createChat(QVector<QString> logins, QString name, QByteArray avatar, bool isGroup);

    /// Изменить статус сообщения
    void markMessage(int d_id, int m_id, int status);

    /// Получить данные об обновлнном статусе сообщения
    void getUpdatedStatusMessage(QJsonObject* qObj);

    QString generateTmpIdMsg();
    void addMessage(QString idDialog, QString tmpIdMessage, QString message = "", QVector<QString> paths = {});


signals:
    void onAutorization(QString, QString, QString, bool);

    void onUpdateAllChats();
    void onUpdateChat(int id_chat);
    void onUpdateMessage(int id_chat, int id_message);


    void onGetDialogs();


    void onGetInvitePrivat(QString login, QString name);
    void onOpenPrivateChat(QString login);
//    void onGetMessages();

//    void onUpdateStatusMessage(int, int, int);

//    void onMessageReceived(int, QString, QString, int);

};

#endif // CLIENTGENERAL_H
