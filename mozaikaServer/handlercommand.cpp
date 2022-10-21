#include "handlercommand.h"

void HandlerCommand::HandlerCmdSendMessage(QJsonObject *object, DataClientOnline *client)
{
    if((*client).isAuthorized)
    {
        QString idChat = ((*object)[ProtocolTrade::___ID_CHAT]).toString();
        QString tmpIdMessage = ((*object)[ProtocolTrade::___TMP_ID_MESSAGE]).toString();
        QString messageText = "";
        QJsonArray arrAttachment;
        QMap<QString, QByteArray> mapAttachment;

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

                mapAttachment.insert(
                            jObj[ProtocolTrade::___NAME_FILE].toString() + "." + jObj[ProtocolTrade::___TYPE_FILE].toString(),
                        ProtocolTrade::StringToByteArray(jObj[ProtocolTrade::___BINARY_FILE].toString())
                        );
            }
        }

        // Добавление в БД

        // idChat
        // getUser(client->login)
        // messageText
        // mapAttachment

        ServerController* controller = ServerController::getInstance();

        // Получили новый id и записываем в бд
        QString newId = QString::number(controller->addMessage(idChat.toInt(), controller->getUser(client->login)->getID(), messageText, mapAttachment));


        // Устанавливаем статус сообщения "на сервере"

        // Формирование ответа пользователю, который отправляет письмо
        QJsonObject* answer = new QJsonObject({
                                                  {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_SEND_MESSAGE)},
                                                  {ProtocolTrade::___ID_MESSAGE, QJsonValue(newId)},
                                                  {ProtocolTrade::___ID_CHAT, QJsonValue(idChat)},
                                                  {ProtocolTrade::___TMP_ID_MESSAGE, QJsonValue(tmpIdMessage)},
                                                  {ProtocolTrade::___STATUS_MESSAGE, QJsonValue(ProtocolTrade::___STS_READ)}
                                              });

        ProtocolTrade::SendTextMessage(ProtocolTrade::jsonObjectToString(answer), client->socket);

        // Формирование ответа пользователю, который получает письмо
        answer = new QJsonObject({
                                     {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_SEND_MESSAGE)},
                                     {ProtocolTrade::___ID_MESSAGE, QJsonValue(newId)},
                                     {ProtocolTrade::___ID_CHAT, QJsonValue(idChat)},
                                     {ProtocolTrade::___TEXT_MESSAGE, QJsonValue(messageText)},
                                     {ProtocolTrade::___BIRTH_DATE, QJsonValue(QDateTime::currentDateTime().toString())},
                                     {ProtocolTrade::___LOGIN, QJsonValue(client->login)},
                                     {ProtocolTrade::___STATUS_MESSAGE, QJsonValue(ProtocolTrade::___STS_TAKEN)},
                                     {ProtocolTrade::___ARR_ATTACHMENT, QJsonValue(arrAttachment)}
                                 });


        // тут получение логина или логинов адресатов по идентификатору диалога
//        QVector<QString> dstVectorUsers =
        int myIdUser = controller->getUser(client->login)->getID();
        UserDialog usrDialog = controller->getDialog(idChat.toInt(), myIdUser);
        QVector<QString> members = usrDialog.getMemberLogins();


        for(int i = 0; i < members.size(); i++)
        {
            if(members[i] == client->login)
            {
                continue;
            }

            DataClientOnline* dstUser = GeneralFunctionSocket::FindClient(members[i]);

            if(dstUser)
            {
                ProtocolTrade::SendTextMessage(ProtocolTrade::jsonObjectToString(answer), dstUser->socket);
            }
        }
    }
}

//ЖОПИСАТЬ ПОдтверждение доставленного сообщения
void HandlerCommand::HandlerCmdSendMessageAnswerFromClient(QJsonObject *object, DataClientOnline *client)
{
    QString idChat = ((*object)[ProtocolTrade::___ID_CHAT]).toString();
    QString idMessage = ((*object)[ProtocolTrade::___ID_MESSAGE]).toString();
    QString statusMessage = ((*object)[ProtocolTrade::___STATUS_MESSAGE]).toString();

    MarkMessage(object, client);
}

void HandlerCommand::HandlerCmdAuthorization(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolTrade::___LOGIN]).toString();
    QString password = ((*object)[ProtocolTrade::___PASSWORD]).toString();

    QJsonObject* answer = new QJsonObject({
                                              {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_AUTHORIZATION)}
                                          });

    ServerController* controller = ServerController::getInstance();
    int autoriz = controller->confirmAuthorization(login,password);

    if(autoriz == 1){



        User* user=controller->getUser(login);
        client->isAuthorized = true;
        client->login = user->getLogin();
        answer->insert(ProtocolTrade::___STATUS, QJsonValue(ProtocolTrade::___STS_DONE));
        answer->insert(ProtocolTrade::___USER_NAME, QJsonValue(user->getName()));

        MyFile file= controller->getFile(user->getAvatarId());

        QJsonObject* avatar = new QJsonObject({
                                                  {ProtocolTrade::___BINARY_FILE, QJsonValue(ProtocolTrade::ByteArrayToString(controller->getFileBytes(user->getAvatarId())))},
                                                  {ProtocolTrade::___NAME_FILE, QJsonValue(file.getName())},
                                                  {ProtocolTrade::___TYPE_FILE, QJsonValue(file.getType())}
                                              });

        answer->insert(ProtocolTrade::___AVATAR, *avatar);
        answer->insert(ProtocolTrade::___BIRTH_DATE, QJsonValue(user->getBirthDate().toString()));

        HandlerUserConnect(client);
    }
    else{
        answer->insert(ProtocolTrade::___STATUS, QJsonValue(ProtocolTrade::___STS_NOPE));
    }

    ProtocolTrade::SendTextMessage(ProtocolTrade::jsonObjectToString(answer), client->socket);
}

void HandlerCommand::ProcessingEvent(QJsonObject* object, DataClientOnline* client)
{
    QString commandFromClient = ((*object)[ProtocolTrade::___COMMAND]).toString();

    if(commandFromClient == ProtocolTrade::___CMD_SEND_MESSAGE)
    {
        QString statusMessage = ((*object)[ProtocolTrade::___STATUS_MESSAGE]).toString();

        if(statusMessage == ProtocolTrade::___STS_TAKEN)
        {
            HandlerCmdSendMessageAnswerFromClient(object, client);
        }
        else
        {
            HandlerCmdSendMessage(object, client);
        }
    }else if (commandFromClient == ProtocolTrade::___CMD_AUTHORIZATION)
    {
        HandlerCmdAuthorization(object, client);
    }
    else if(commandFromClient == ProtocolTrade::___CMD_CREATE_PRIVATE_CHAT)
    {
        if(!object->find(ProtocolTrade::___STATUS)->isUndefined())
        {
            // Обработка ответа от клиента на создание приватного чата
            CreatePrivateChat(object, client);
        }
        else
        {
            // Обработка запроса от клиента на создание приватного чата
            HandlerReqPrivatChat(object, client);
        }
    }
    else if(commandFromClient == ProtocolTrade::___CMD_GET_MESSAGES){
        // Обработка запроса от клиента на получение сообщений из конкретного чата
        HandlerReqGetMessageInDialog(object, client);
    }
    else if(commandFromClient == ProtocolTrade::___CMD_GET_DATE_USER){
        ReqGetContact(object, client);
    }

    else if(commandFromClient == ProtocolTrade::___CMD_GET_CHATS){
        SendDialogsToUser(client);
    }

    else if(commandFromClient == ProtocolTrade::___CMD_CREATE_CHAT){
        CreateChat(object, client);
    }
    else if(commandFromClient == ProtocolTrade::___CMD_UPDATE_STATUS_MESSAGE){
        MarkMessage(object, client);
    }
    else if(commandFromClient == ProtocolTrade::___CMD_READ_ALL_MESSAGE_BY_CHAT)
    {
        ReadAllMessagesByChat(object, client);
    }
}

void HandlerCommand::CreatePrivateChat(QJsonObject *object, DataClientOnline *client)
{
    QString receiver_login = ((*object)[ProtocolTrade::___LOGIN]).toString();

    DataClientOnline* dstUser = GeneralFunctionSocket::FindClient(receiver_login);

    if(dstUser){
        bool status = (*object)[ProtocolTrade::___STATUS] == ProtocolTrade::___STS_DONE;
        QJsonObject* answer;

        QString ip = "localhost";
//        QString ip = client->socket->peerAddress().toString();
//        if(ip == "::1")
//        {
//            ip = "localhost";
//        }


        if(status)
            answer = new QJsonObject({
                                         {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_CREATE_PRIVATE_CHAT)},
                                         {ProtocolTrade::___STATUS, QJsonValue(ProtocolTrade::___STS_DONE)},
                                         {ProtocolTrade::___IP_USER, QJsonValue(ip)},
                                         {ProtocolTrade::___PORT_USER, (*object)[ProtocolTrade::___PORT_USER]},
                                         {ProtocolTrade::___LOGIN, QJsonValue(client->login)}
                                     });
        else
            answer = new QJsonObject({
                                         {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_CREATE_PRIVATE_CHAT)},
                                         {ProtocolTrade::___STATUS, QJsonValue(ProtocolTrade::___STS_NOPE)},
                                         {ProtocolTrade::___LOGIN, QJsonValue(client->login)}
                                     });

        ProtocolTrade::SendTextMessage(ProtocolTrade::jsonObjectToString(answer), dstUser->socket);
    }
}

void HandlerCommand::HandlerReqPrivatChat(QJsonObject *object, DataClientOnline *client)
{
    QString requester_login = ((*object)[ProtocolTrade::___LOGIN]).toString();
    DataClientOnline* dst_client = GeneralFunctionSocket::FindClient(requester_login);
    (*object)[ProtocolTrade::___LOGIN] = client->login;

    if(dst_client)
    {
        ProtocolTrade::SendTextMessage(ProtocolTrade::jsonObjectToString(object), dst_client->socket);
    }
}

void HandlerCommand::HandlerReqGetMessageInDialog(QJsonObject *object, DataClientOnline *client)
{
    QString dialog_id = ((*object)[ProtocolTrade::___ID_CHAT]).toString();

    ServerController* controller = ServerController::getInstance();
    controller->markMessages(dialog_id.toInt(), controller->getUser(client->login)->getID());
    UserDialog dialog = controller->getDialog(dialog_id.toInt(), controller->getUser(client->login)->getID());

    QJsonObject* answer = new QJsonObject({
                                              {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_GET_MESSAGES)},
                                              {ProtocolTrade::___ID_CHAT, QJsonValue(dialog_id)},
                                              {ProtocolTrade::___CHAT_GROUP, QJsonValue(dialog.getIsGroup())}
                                          });

    QJsonArray* jsonMsgs=new QJsonArray();
    foreach(Message msg, dialog.getMessages()){
        QString loginSender=controller->getUser(msg.getSender_id())->getLogin();

        QJsonObject* jsonMsg = new QJsonObject({
                                                   {ProtocolTrade::___ID_MESSAGE, QJsonValue(msg.getId())},
                                                   {ProtocolTrade::___TEXT_MESSAGE, QJsonValue(msg.getMessage_data())},
                                                   {ProtocolTrade::___STATUS_MESSAGE, QJsonValue(msg.getStatus())},
                                                   {ProtocolTrade::___LOGIN, QJsonValue(loginSender)},
                                                   {ProtocolTrade::___BIRTH_DATE, QJsonValue(msg.getTime().toString())}
                                               });
        QJsonArray* jsonFiles=new QJsonArray();
        foreach(MyFile file, msg.getFiles()){
            QJsonObject* jsonFile = new QJsonObject({
                                                        {ProtocolTrade::___NAME_FILE, QJsonValue(file.getName())},
                                                        {ProtocolTrade::___TYPE_FILE, QJsonValue(file.getType())},
                                                        {ProtocolTrade::___BINARY_FILE, QJsonValue(ProtocolTrade::ByteArrayToString(file.readFile()))},
                                                    });
            jsonFiles->push_back(*jsonFile);
        }
        jsonMsg->insert(ProtocolTrade::___ARR_ATTACHMENT, *jsonFiles);

        jsonMsgs->push_back(*jsonMsg);
    }

    answer->insert(ProtocolTrade::___ARR_MESSAGES, *jsonMsgs);

    ProtocolTrade::SendTextMessage(ProtocolTrade::jsonObjectToString(answer), client->socket);
}

void HandlerCommand::ReqGetContact(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolTrade::___LOGIN]).toString();
    ServerController* controller = ServerController::getInstance();
    User* user = controller->getUser(login);
    QJsonObject* answer;
    if(user != nullptr){
        DataClientOnline* dstUser = GeneralFunctionSocket::FindClient(login);
        QString sts = dstUser ? ProtocolTrade::___STS_ONLINE : ProtocolTrade::___STS_OFFLINE;
        answer = new QJsonObject({
                                     {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_GET_DATE_USER)},
                                     {ProtocolTrade::___STATUS, QJsonValue(ProtocolTrade::___STS_DONE)},
                                     {ProtocolTrade::___USER_NAME, QJsonValue(user->getName())},
                                     {ProtocolTrade::___BINARY_FILE, QJsonValue(ProtocolTrade::ByteArrayToString(controller->getFileBytes(user->getAvatarId())))},
                                     {ProtocolTrade::___BIRTH_DATE, QJsonValue(user->getBirthDate().toString())},
                                     {ProtocolTrade::___STATUS_USER, QJsonValue(sts)}
                                 });

    }
    else
        answer = new QJsonObject({
                                     {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_GET_DATE_USER)},
                                     {ProtocolTrade::___STATUS, QJsonValue(ProtocolTrade::___STS_NOPE)}
                                 });

    ProtocolTrade::SendTextMessage(ProtocolTrade::jsonObjectToString(answer), client->socket);
}

void HandlerCommand::SendDialogsToUser(DataClientOnline *client)
{
    ServerController* controller = ServerController::getInstance();
    QVector<UserDialog> dialogs = controller->getUserDialogs(controller->getUser(client->login)->getID());
    QJsonArray jdialogs;
    foreach(UserDialog d, dialogs){
        QJsonArray jmembers;

        auto members = d.getMembers();
        foreach(User u, members){
            QByteArray avatar = controller->getFileBytes(u.getAvatarId());
            QJsonValue juser({
                                 {ProtocolTrade::___LOGIN, QJsonValue(u.getLogin())},
                                 {ProtocolTrade::___AVATAR, QJsonValue(ProtocolTrade::ByteArrayToString(avatar))},
                                 {ProtocolTrade::___USER_NAME, QJsonValue(u.getName())},
                                 {ProtocolTrade::___BIRTH_DATE, QJsonValue(u.getBirthDate().toString())}
                             });
            jmembers.append(juser);
        }



        QByteArray avatar = controller->getFileBytes(d.getAvatarID());



        Message lastMsg = d.getLastMessage();
        QJsonValue jLastMsg({
                               {ProtocolTrade::___TEXT_MESSAGE, QJsonValue(lastMsg.getMessage_data())},
                               {ProtocolTrade::___BIRTH_DATE, QJsonValue(lastMsg.getTime().toString())},
                                {ProtocolTrade::___ID_MESSAGE, QJsonValue(lastMsg.getId())},
                                {ProtocolTrade::___STATUS_MESSAGE, QJsonValue(lastMsg.getStatus())},
                                {ProtocolTrade::___USER_NAME, QJsonValue(controller->getUser(lastMsg.getSender_id())->getLogin())}
                           });

        QString nameChat=d.getName();
        QByteArray avatarBytes=avatar;
        QJsonValue statusUser= QJsonValue(ProtocolTrade::___STS_OFFLINE);
        if(!d.getIsGroup()){
            DataClientOnline* dst_client = new DataClientOnline();// GeneralFunctionSocket::FindClient(requester_login);

            if(members.count()==1){
                nameChat=members[0].getName();
                avatarBytes= controller->getFileBytes(members[0].getAvatarId());
                dst_client=GeneralFunctionSocket::FindClient(members[0].getLogin());
            }
            else{
                if(members[0].getLogin()==client->login){
                    nameChat=members[1].getName();
                    avatarBytes= controller->getFileBytes(members[1].getAvatarId());
                    dst_client=GeneralFunctionSocket::FindClient(members[1].getLogin());
                }
                else
                {
                    nameChat=members[0].getName();
                    avatarBytes= controller->getFileBytes(members[0].getAvatarId());
                    dst_client=GeneralFunctionSocket::FindClient(members[0].getLogin());
                }
            }

            statusUser= QJsonValue(dst_client? ProtocolTrade::___STS_ONLINE:ProtocolTrade::___STS_OFFLINE);
        }

        int countUnCheck=0;
        foreach(auto m, d.getMessages())
            if(m.getStatus()!=3)
                    countUnCheck++;

        QJsonValue jdialog({
                               {ProtocolTrade::___USER_NAME, QJsonValue(nameChat)},
                               {ProtocolTrade::___AVATAR, QJsonValue(ProtocolTrade::ByteArrayToString(avatarBytes))},
                               {ProtocolTrade::___ID_CHAT, QJsonValue(d.getID())},
                               {ProtocolTrade::___ARR_USERS, jmembers},
                               {ProtocolTrade::___ARR_MESSAGES, jLastMsg},
                               {ProtocolTrade::___COUNT_MESSAGE, QJsonValue(countUnCheck)},
                               {ProtocolTrade::___CHAT_GROUP, QJsonValue(d.getIsGroup())},
                               {ProtocolTrade::___STATUS_USER, statusUser}
                           });

        jdialogs.append(jdialog);
    }

    QJsonObject* object = new QJsonObject({
                                              {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_GET_CHATS)},
                                              {ProtocolTrade::___ARR_CHATS, jdialogs}
                                          });
    ProtocolTrade::SendTextMessage(ProtocolTrade::jsonObjectToString(object), client->socket);
}

void HandlerCommand::CreateChat(QJsonObject *object, DataClientOnline* client)
{
    ServerController* controller=ServerController::getInstance();

    QJsonArray logins = (*object)[ProtocolTrade::___ARR_USERS].toArray();

    QString name= (*object)[ProtocolTrade::___USER_NAME].toString();
    QByteArray avatar = ProtocolTrade::StringToByteArray((*object)[ProtocolTrade::___AVATAR].toString());
    int avatar_id = controller->addFile(avatar,"", "");
    bool isGroup = (*object)[ProtocolTrade::___CHAT_GROUP].toBool();
    UserDialog* dialog=new UserDialog(-1,isGroup, name,avatar_id);

    foreach(QJsonValue jmem, logins){
        QString memLogin = jmem[ProtocolTrade::___LOGIN].toString();
        dialog->addMember(*controller->getUser(memLogin));
    }
    dialog->addMember(*controller->getUser(client->login));

    controller->addDialog(dialog);

    controller->addMessage(dialog->getID(),controller->getUser(client->login)->getID(),"Здравия желаю", QMap<QString,QByteArray>());
}

void HandlerCommand::MarkMessage(QJsonObject *object, DataClientOnline *client)
{
    ServerController* controller=ServerController::getInstance();

    QString dialog_id = (*object)[ProtocolTrade::___ID_CHAT].toString();
    QString message_id = (*object)[ProtocolTrade::___ID_MESSAGE].toString();
    QString status = (*object)[ProtocolTrade::___STATUS_MESSAGE].toString();
    int istatus = -1;
    if(ProtocolTrade::___STS_TAKEN == status)
        istatus = 2;
    else if(ProtocolTrade::___STS_READ == status)
        istatus = 3;
    else
        istatus = 1;

    controller->markMessage(message_id.toInt(), dialog_id.toInt(), istatus);
    NotifyStatusChanged(object, client);
}

void HandlerCommand::NotifyStatusChanged(QJsonObject *object, DataClientOnline *client)
{
    int dialog_id = (*object)[ProtocolTrade::___ID_CHAT].toInt();
    ServerController* controller=ServerController::getInstance();

    UserDialog dialog = controller->getDialog(dialog_id, controller->getUser(client->login)->getID());

    foreach(User u, dialog.getMembers()){
        DataClientOnline* dstClient = GeneralFunctionSocket::FindClient(u.getLogin());
        if(dstClient == nullptr)
            continue;
        ProtocolTrade::SendTextMessage(ProtocolTrade::jsonObjectToString(object), dstClient->socket);
    }
}


void HandlerCommand::GetNetUsers(DataClientOnline *client)
{
    ServerController* controller=ServerController::getInstance();
    QVector<QString> logins = controller->getNetUsers(client->login);
}

void HandlerCommand::HandlerUserStautusChange(DataClientOnline *client, QString newStatus)
{
    QJsonObject* answer = new QJsonObject({
                                              {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_UPDATE_STATUS_USER)},
                                              {ProtocolTrade::___STATUS_USER, QJsonValue(newStatus)},
                                              {ProtocolTrade::___LOGIN, QJsonValue(client->login)}
                                          });

    QString answerString = ProtocolTrade::jsonObjectToString(answer);

    ServerController* controller = ServerController::getInstance();

    QVector<QString> netUsers = controller->getNetUsers(client->login);

    DataClientOnline* friendClient;

    for(int i = 0; i < netUsers.size(); i++)
    {
        friendClient = GeneralFunctionSocket::FindClient(netUsers[i]);

        if(friendClient)
        {
            ProtocolTrade::SendTextMessage(answerString, friendClient->socket);
        }
    }
}

void HandlerCommand::HandlerUserDisconect(DataClientOnline *client)
{
    HandlerUserStautusChange(client, ProtocolTrade::___STS_OFFLINE);

    GeneralFunctionSocket::RemoveClient(client->socket);
}

void HandlerCommand::HandlerUserConnect(DataClientOnline *client)
{
    HandlerUserStautusChange(client, ProtocolTrade::___STS_ONLINE);
}

void HandlerCommand::ReadAllMessagesByChat(QJsonObject *object, DataClientOnline *client)
{
    ServerController* controller=ServerController::getInstance();

    int chat_id = (*object)[ProtocolTrade::___ID_CHAT].toString().toInt();
    int id_client = controller->getUser(client->login)->getID();

    controller->markMessages(id_client, chat_id);

    UserDialog userDialog = controller->getDialog(chat_id, id_client);
    QVector<User> usersFromDialog = userDialog.getMembers();

    DataClientOnline* memberOnline;

    QJsonObject* answer = new QJsonObject({
                                              {ProtocolTrade::___COMMAND, QJsonValue(ProtocolTrade::___CMD_UDATE_CHAT)},
                                              {ProtocolTrade::___ID_CHAT, QJsonValue(QString::number(chat_id))}
                                          });

    QString answerString = ProtocolTrade::jsonObjectToString(answer);

    for(int i = 0; i < usersFromDialog.size(); i++)
    {
        memberOnline = GeneralFunctionSocket::FindClient(usersFromDialog[i].getLogin());

        if(memberOnline)
        {
            ProtocolTrade::SendTextMessage(answerString, memberOnline->socket);
        }
    }

//    controller->readAllMessagesByChat(client->login, chat_id);
}

HandlerCommand::HandlerCommand(QObject *parent) : QObject(parent)
{

}
