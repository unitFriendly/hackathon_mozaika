#include "handlercommand.h"

void HandlerCommand::HandlerCmdAuthorization(QJsonObject *object, QWebSocket *client)
{
    QString status = ((*object)[ProtocolTrade::___STATUS]).toString();

    if(status == ProtocolTrade::___STS_DONE)
    {
        // Пользователь авторизовался
        QString userName = ((*object)[ProtocolTrade::___USER_NAME]).toString();
        QString birthDate = ((*object)[ProtocolTrade::___BIRTH_DATE]).toString();

        QJsonObject jObj = ((*object)[ProtocolTrade::___AVATAR]).toObject();

        ProtocolTrade::SaveBinaryFile(
                    jObj[ProtocolTrade::___BINARY_FILE].toString(),
                jObj[ProtocolTrade::___NAME_FILE].toString(),
                jObj[ProtocolTrade::___TYPE_FILE].toString(),
                "idMessage",
                "idChat");

        Fix::isAuthorized = true;
    }
    else
    {
        // Пользователь не авторизовался
    }
}

void HandlerCommand::HandlerCmdSendMessage(QJsonObject *object, QWebSocket *socket)
{
    // Обработка входных данных
    QString idChat = ((*object)[ProtocolTrade::___ID_CHAT]).toString();
    QString idMessage = ((*object)[ProtocolTrade::___ID_MESSAGE]).toString();
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
                    idMessage,
                    idChat);
        }
    }

    // Формирование ответа серверу
    QJsonObject* answer = new QJsonObject({
                                              {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_SEND_MESSAGE)},
                                              {ProtocolTrade::___ID_CHAT, QJsonValue(idChat)},
                                              {ProtocolTrade::___ID_MESSAGE, QJsonValue(idMessage)},
                                              {ProtocolTrade::___STATUS_MESSAGE, QJsonValue(ProtocolTrade::___STS_TAKEN)}
                                          });

    ProtocolTrade::SendTextMessage(ProtocolTrade::JsonObjectToString(answer), socket);
}

//ЖОПиСАТЬ
void HandlerCommand::HandlerCmdSendMessageAnswerServer(QJsonObject *object, QWebSocket *client)
{
    QString idChat = ((*object)[ProtocolTrade::___ID_CHAT]).toString();
    QString idMessage = ((*object)[ProtocolTrade::___ID_MESSAGE]).toString();
    QString tmpIdMessage = ((*object)[ProtocolTrade::___TMP_ID_MESSAGE]).toString();
    QString statusMessage = ((*object)[ProtocolTrade::___TMP_ID_MESSAGE]).toString();
}

HandlerCommand::HandlerCommand(QObject *parent) : QObject(parent)
{

}

void HandlerCommand::ProcessingEventFromServer(QJsonObject *object, QWebSocket *socket)
{
    QString commandFromClient = ((*object)[ProtocolTrade::___COMMAND]).toString();

    if(commandFromClient == ProtocolTrade::___CMD_SEND_MESSAGE)
    {
        if(!object->find(ProtocolTrade::___TMP_ID_MESSAGE)->isUndefined())
        {
            // обработка ответа с сервера после отправки сообщения
            HandlerCmdSendMessageAnswerServer(object, socket);
        }
        else
        {
            // обработка входящего сообщения
            HandlerCmdSendMessage(object, socket);
        }
    }
    else if(commandFromClient == ProtocolTrade::___CMD_CREATE_PRIVATE_CHAT)
    {
        if(!object->find(ProtocolTrade::___STATUS)->isUndefined())
        {
            // Обработка полученного запроса на создание приватного чата от сервера
            GetAnswerCreatePrivateChat(object, socket);
        }
        else
        {
            // Обработка ответа на создание приватног чата
            GetReqPrivateChat(object, socket);
        }
    }
    else if(commandFromClient == ProtocolTrade::___CMD_AUTHORIZATION)
    {
        // Обработка ответа от сервера на авторизацию
        HandlerCmdAuthorization(object, socket);
    }
    else if(commandFromClient == ProtocolTrade::___CMD_GET_MESSAGES){
        // Обработка ответа от сервера на запрос сообщений из конкретного чата
        GetAnswerMessagesInDialog(object, socket);
    }
    else if(commandFromClient == ProtocolTrade::___CMD_GET_DATE_USER){
        // Обработка ответа от сервера на запрос информации об котнтакте
        GetAnswerContact(object, socket);
    }
    else if(commandFromClient == ProtocolTrade::___CMD_GET_CHATS){
        // Обработка ответа от сервера на запрос всех диалогов
        AnswerMyDialogs(object, socket);
    }

}

void HandlerCommand::SendMessage(QString idChat, QString tmpIdMsg, QString textMsg, QVector<QString> paths, QWebSocket* socket)
{
    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_SEND_MESSAGE)},
                                            {ProtocolTrade::___ID_CHAT, QJsonValue(idChat)},
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

void HandlerCommand::Authorization(QString login, QString password, QWebSocket *socket)
{
    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_AUTHORIZATION)},
                                            {ProtocolTrade::___LOGIN, QJsonValue(login)},
                                            {ProtocolTrade::___PASSWORD, QJsonValue(password)}
                                        });

    ProtocolTrade::SendTextMessage(ProtocolTrade::JsonObjectToString(jObj), socket);
}

void HandlerCommand::SendPrivateMessage(QString tmpIdMsg, QString textMsg, QVector<QString> paths, QWebSocket *socket)
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

void HandlerCommand::GetMessagesInDialog(QString idChat, QWebSocket *socket)
{
    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_GET_MESSAGES)},
                                            {ProtocolTrade::___ID_CHAT, QJsonValue(idChat)}
                                        });

    ProtocolTrade::SendTextMessage(ProtocolTrade::JsonObjectToString(jObj), socket);
}

void HandlerCommand::GetAnswerMessagesInDialog(QJsonObject *object, QWebSocket *socket)
{
    QString idChat = ((*object)[ProtocolTrade::___ID_CHAT]).toString();
    bool isGroup = ((*object)[ProtocolTrade::___CHAT_GROUP]).toBool();

    UserDialog dialog(idChat.toInt(), isGroup);

    QJsonArray messages = ((*object)[ProtocolTrade::___ARR_MESSAGES]).toArray();
    foreach(QJsonValue objMsg, messages)
    {
        int idMessage = ((objMsg)[ProtocolTrade::___ID_MESSAGE]).toInt();
        QString textMessage = ((objMsg)[ProtocolTrade::___TEXT_MESSAGE]).toString();
        int statusMessage = ((objMsg)[ProtocolTrade::___STATUS_MESSAGE]).toInt();
        QString loginSender = ((objMsg)[ProtocolTrade::___LOGIN]).toString();
        QDateTime date= QDateTime::fromString(((objMsg)[ProtocolTrade::___BIRTH_DATE]).toString());

        Message msg(idMessage,idChat.toInt(),loginSender,textMessage,date,statusMessage);

        QJsonArray files = ((objMsg)[ProtocolTrade::___ARR_ATTACHMENT]).toArray();
        foreach(QJsonValue objFiles, files)
        {
            QString nameFile = ((objFiles)[ProtocolTrade::___NAME_FILE]).toString();
            QString typeFile = ((objFiles)[ProtocolTrade::___TYPE_FILE]).toString();
            QByteArray bytes = ProtocolTrade::StringToByteArray(((objFiles)[ProtocolTrade::___BINARY_FILE]).toString());

            MyFile file(-1,"",nameFile, typeFile);
            file.SetByteArray(bytes);

            msg.addFile(file);
        }

        dialog.addMessage(msg);
    }

    qDebug() <<dialog.getID();
    // ОТДАТЬ ИГОРЮ ПОЛУЧЕННЫЙ ДИАЛОГ
}

void HandlerCommand::GetContact(QString login, QWebSocket *socket)
{
    QJsonObject * object = new QJsonObject({
                                               {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_GET_DATE_USER)},
                                               {ProtocolTrade::___LOGIN, QJsonValue(login)}
                                           });
    ProtocolTrade::SendTextMessage(ProtocolTrade::JsonObjectToString(object), socket);
}

void HandlerCommand::GetAnswerContact(QJsonObject *qObj, QWebSocket *socket)
{
    bool status = ((*qObj)[ProtocolTrade::___STATUS]) == ProtocolTrade::___STS_DONE;
    if(status){
        QString name = ((*qObj)[ProtocolTrade::___USER_NAME]).toString();
        QByteArray avatar = ProtocolTrade::StringToByteArray(((*qObj)[ProtocolTrade::___BINARY_FILE]).toString());
        QDate date= QDate::fromString(((*qObj)[ProtocolTrade::___BIRTH_DATE]).toString());
        bool isOnline = ((*qObj)[ProtocolTrade::___STATUS_USER]) == ProtocolTrade::___STS_ONLINE;


        // takogo polsovatelya est'
    }
    else{
        // takogo polsovatelya net
    }
}

void HandlerCommand::GetMyDialogs(QWebSocket *socket)
{
    QJsonObject* object = new QJsonObject({{ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_GET_CHATS)}});
    ProtocolTrade::SendTextMessage(ProtocolTrade::JsonObjectToString(object), socket);
}

void HandlerCommand::AnswerMyDialogs(QJsonObject *qObj, QWebSocket *socket)
{
    QJsonArray chats = (*qObj)[ProtocolTrade::___ARR_CHATS].toArray();
    QVector<UserDialog> dialogs;
    foreach(QJsonValue c, chats){
        QString dialog_name = c[ProtocolTrade::___USER_NAME].toString();
        QByteArray dialog_avatar = ProtocolTrade::StringToByteArray(c[ProtocolTrade::___AVATAR].toString());
        int id = c[ProtocolTrade::___ID_CHAT].toInt();
        QJsonArray members = c[ProtocolTrade::___ARR_USERS].toArray();
        UserDialog dialog(id, dialog_name, dialog_avatar);
        foreach(QJsonValue m, members){
            QString login = m[ProtocolTrade::___LOGIN].toString();
            QByteArray user_avatar = ProtocolTrade::StringToByteArray(m[ProtocolTrade::___AVATAR].toString());
            QString user_name = m[ProtocolTrade::___USER_NAME].toString();
            QString birthdate = m[ProtocolTrade::___BIRTH_DATE].toString();
            User user(-1, login, user_name, user_avatar, birthdate);
            dialog.addMember(&user);
        }
        dialogs.append(dialog);
    }

    // СДЕЛАЙ ЧТО ТО С ДИАЛОГС
}

void HandlerCommand::CreateChat(QVector<QString> logins, QString name, QByteArray avatar, QWebSocket *socket)
{
    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_CREATE_CHAT)},
                                            {ProtocolTrade::___USER_NAME, QJsonValue(name)},
                                            {ProtocolTrade::___AVATAR, QJsonValue(ProtocolTrade::ByteArrayToString(avatar))}
                                        });

    QJsonArray* jlogins=new QJsonArray();
    foreach(QString login, logins){
        QJsonObject* jlogin = new QJsonObject({
                                                  {ProtocolTrade::___LOGIN, QJsonValue(login)}
                                              });
        jlogins->append(*jlogin);
    }
    jObj->insert(ProtocolTrade::___ARR_USERS, *jlogins);

    ProtocolTrade::SendTextMessage(ProtocolTrade::JsonObjectToString(jObj), socket);
}

void HandlerCommand::CreatePrivateChat(QString receiver_login, QWebSocket *socket)
{
    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_CREATE_PRIVATE_CHAT)},
                                            {ProtocolTrade::___LOGIN, QJsonValue(receiver_login)}
                                        });

    ProtocolTrade::SendTextMessage(ProtocolTrade::JsonObjectToString(jObj), socket);
}

void HandlerCommand::GetReqPrivateChat(QJsonObject *qObj, QWebSocket *socket)
{
    QString requester_login = ((*qObj)[ProtocolTrade::___LOGIN]).toString();
    bool isAccepted;// НУЖНО СПРОСИТЬ У ПОЛЬЗОВАТЕЛЯ ХОЧЕТ ЛИ ОН СОЗДАТЬ ДИАЛОГ
    isAccepted = requester_login == "1";


    QString status = isAccepted ? ProtocolTrade::___STS_DONE : ProtocolTrade::___STS_NOPE;
    QJsonObject* answer;

    if(isAccepted)
    {
        quint16 port = Fix::START_PORT_LISTENER + Fix::privateChatsDst.size() + Fix::privateChatsSrc.size();
        DstPrivateChat* tmpDst = new DstPrivateChat(requester_login, Fix::loginUser, port);
        Fix::privateChatsDst.push_back(tmpDst);
        answer = new QJsonObject({
                                     {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_CREATE_PRIVATE_CHAT)},
                                     {ProtocolTrade::___STATUS, QJsonValue(ProtocolTrade::___STS_DONE)},
                                     {ProtocolTrade::___PORT_USER, QJsonValue(QString::number(port))},
                                     {ProtocolTrade::___LOGIN, QJsonValue(requester_login)}
                                 });
    }

    else
    {
        answer = new QJsonObject({
                                     {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_CREATE_PRIVATE_CHAT)},
                                     {ProtocolTrade::___STATUS, QJsonValue(ProtocolTrade::___STS_NOPE)},
                                     {ProtocolTrade::___LOGIN, QJsonValue(requester_login)}
                                 });
    }

    ProtocolTrade::SendTextMessage(ProtocolTrade::JsonObjectToString(answer), socket);
}

void HandlerCommand::GetAnswerCreatePrivateChat(QJsonObject *qObj, QWebSocket *socket)
{
    QString status = ((*qObj)[ProtocolTrade::___STATUS]).toString();
    if(status == ProtocolTrade::___STS_DONE){
        QString ip = ((*qObj)[ProtocolTrade::___IP_USER]).toString();
        QString port = ((*qObj)[ProtocolTrade::___PORT_USER]).toString();
        QString login = ((*qObj)[ProtocolTrade::___LOGIN]).toString();

        //чувак согласился на првиатный чат надо с этим что-то делать

        SrcPrivateChat* tmpSrc = new SrcPrivateChat(login, Fix::loginUser, port.toUInt(), ip);
                Fix::privateChatsSrc.push_back(tmpSrc);
    }
    else {
        // чувак не согласился на првиатный чат ну и ладно
    }
}
