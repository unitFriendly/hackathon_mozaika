#include "servercontroller.h"

//QString ServerController::pathGarbage="C:\\Users\\test\\Desktop\\HackathonApril\\super_garbage\\";

QString ServerController::pathGarbage="C:\\Users\\Tihon\\Desktop\\hack_new\\secondday\\build-super_server-3-Debug\\debug\\super_garbage\\";

//QString ServerController::pathGarbage="C:\\Users\\rota\\Documents\\build-Server-MinGW64-Debug\\super_garbage\\";


ServerController* ServerController::instance = nullptr;

ServerController::ServerController()
{
    startServer();
}

ServerController *ServerController::getInstance()
{
    if(!instance)
        instance = new ServerController();
    return instance;
}

bool ServerController::startServer()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("super_database2");
    db.setUserName("postgres");
    db.setPassword("1234");
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void ServerController::shutdownServer()
{
    db.close();
}

int ServerController::loadData()
{
    loadUsers();
    return 0;
}

MyFile ServerController::getFile(int id)
{
    QSqlQuery query("SELECT path, name, type FROM files WHERE id = " + tostr(id) + ";");
    //query.exec();
    query.first();

    return MyFile(id, svalue(0), svalue(1), svalue(2));
}

QByteArray ServerController::getFileBytes(int id)
{
    auto file = getFile(id);
    return file.readFile();
}

QVector<UserDialog> ServerController::getUserDialogs(int user_id)
{
    QSqlQuery query(QString("SELECT dialog_id FROM member WHERE user_id = %1;")
                    .arg(tostr(user_id)));

    QVector<UserDialog> dialogs;

    while(query.next())
    {
        int dialog_id = ivalue(0);
        UserDialog dialog=getDialog(dialog_id, user_id);
        dialogs.append(dialog);
    }

    return dialogs;
}

UserDialog ServerController::getDialog(int dialog_id, int user_id)
{
    QSqlQuery query(QString("SELECT id, name, avatar_id, is_group FROM public.dialog WHERE id = %1;")
                    .arg(tostr(dialog_id)));

    query.first();
    UserDialog dialog(dialog_id, query.value(3).toBool(), svalue(1), ivalue(2));

    query= QSqlQuery(QString("SELECT user_id FROM public.member WHERE dialog_id = %1 ORDER BY user_id;")
                     .arg(tostr(dialog_id)));

    while(query.next())
    {
        int member_id = ivalue(0);
        dialog.addMember(*getUser(member_id));
    }

    query= QSqlQuery(QString("SELECT id, dialog_id, sender_id, message, date FROM public.message WHERE dialog_id = %1 ORDER BY date DESC;")
                     .arg(tostr(dialog_id)));

    while(query.next())
    {
        int m_id = ivalue(0);
        int d_id = ivalue(1);
        int s_id = ivalue(2);
        QString msg_text = svalue(3);
        QDateTime dateTime = query.value(4).toDateTime();// КРИВО ПАРСЕРИТ ДАТУ, НАДО РЕШИТЬ ЧТО ТО

        QSqlQuery queryStatus= QSqlQuery(QString("SELECT status FROM public.status WHERE dialog_id = %1 AND message_id = %2 AND user_id = %3;")
                                         .arg(tostr(dialog_id))
                                         .arg(tostr(m_id))
                                         .arg(tostr(user_id)));
        queryStatus.first();
        int status = queryStatus.value(0).toInt();

        Message msg(m_id, d_id, s_id, msg_text, dateTime, status);

        QSqlQuery query_getfile(QString("SELECT file_id FROM content where message_id = %1 and dialog_id = %2;").arg(m_id).arg(d_id));
        while(query_getfile.next()){
            MyFile file = getFile(query_getfile.value(0).toInt()); // small lose
            msg.addFile(file);
        }

        dialog.addMessage(msg);
    }

    return dialog;
}

int ServerController::addMessage(int dialog_id, int sender_id, QString msg, QMap<QString, QByteArray> files)
{
    int message_id=getLastIdMessageDialog(dialog_id)+1;
    QString text=QString("INSERT INTO public.message(id, dialog_id, sender_id, message) VALUES (%1, %2, %3, '%4') RETURNING id;")
            .arg(message_id)
            .arg(dialog_id)
            .arg(sender_id)
            .arg(msg);
    QSqlQuery query(text);
    query.first();
    int returned_id = ivalue(0);

    UserDialog dialog=getDialog(dialog_id, sender_id);
    foreach(auto m, dialog.getMemberIDs()){
        QString textStatus=QString("INSERT INTO public.status(dialog_id, message_id, user_id, status) VALUES (%1, %2, %3, %4);")
                .arg(dialog_id)
                .arg(message_id)
                .arg(m)
                .arg((m==sender_id ? 3:2 ));
        QSqlQuery queryStatus(textStatus);
        queryStatus.exec();
    }



    for (int i=0; i<files.count() ; i++ )
    {
        QString key=files.keys()[i];
        QString type=key.remove(0,key.indexOf(".")+1);
        int f_id = addFile(files[files.keys()[i]],files.keys()[i], type);

        QSqlQuery query_f(QString("INSERT INTO public.content(message_id, dialog_id, file_id) VALUES (%1, %2, %3)")
                          .arg(message_id)
                          .arg(dialog_id)
                          .arg(f_id));
        query_f.exec();
    }

    return returned_id;
}

int ServerController::markMessage(int m_id, int d_id, int status)
{
    QSqlQuery query(QString("UPDATE message SET status = %1 WHERE id = %2 AND dialog_id = %3")
                    .arg(tostr(status))
                    .arg(m_id)
                    .arg(d_id));
    query.exec();

    return 0;
}

int ServerController::markMessages(int d_id ,int user_id)
{
    UserDialog d= getDialog(d_id,user_id);

    foreach(auto m, d.getMessages()){
        QSqlQuery query(QString("UPDATE public.status SET status = %1 WHERE dialog_id = %2 AND message_id = %3 user_id = %4;")
                        .arg("3")
                        .arg(d_id)
                        .arg(m.getId())
                        .arg(user_id));
        query.exec();

        QSqlQuery query2(QString("UPDATE public.status SET status = %1 WHERE dialog_id = %2 AND message_id = %3 user_id = %4;")
                        .arg("3")
                        .arg(d_id)
                        .arg(m.getId())
                        .arg(m.getSender_id()));
        query2.exec();
    }

    QSqlQuery query(QString("UPDATE public.status SET status = %1 WHERE dialog_id = %2 AND user_id = %3;")
                    .arg("3")
                    .arg(d_id)
                    .arg(user_id));
    query.exec();
}

int ServerController::addFile(QByteArray bytes, QString name, QString type)
{
    if(bytes.length()==0) return -1;

    QByteArray date = QByteArray(QDateTime::currentDateTime().toString().toStdString().c_str());
    QString fileName=QString(QCryptographicHash::hash(date,QCryptographicHash::Md5).toHex());//(QDateTime::currentDateTime().toString().replace(":","")+" "+name);
    QString filePath=pathGarbage+fileName+".spg";
    QFile out(filePath);
    out.open(QIODevice::WriteOnly);
    out.write(bytes);
    out.close();

    QSqlQuery query(QString("INSERT INTO public.files(path, name, type) VALUES ('%1', '%2', '%3') RETURNING id;")
                    .arg(fileName+".spg")
                    .arg(name)
                    .arg(type));
    query.first();
    return ivalue(0);
}

int ServerController::confirmAuthorization(QString login, QString hash_pass)
{
    auto str = QString("SELECT id, hash_pass FROM public.\"user\" where login = '%0';").arg(login.toLower());
    QSqlQuery query(str);

    if(!query.first()){
        qDebug() << QString("login '%0': not exist").arg(login.toLower());
        return 0;
    }
    else{
        int user_id = ivalue(0);
        QString true_hash_pass = svalue(1);
        if(true_hash_pass == hash_pass){
            // add user to adffklhaddgvklds
            qDebug() << QString("login '%0': successful authorization").arg(login.toLower());
            return 1;
        }
        else{
            // poshol
            qDebug() << QString("login '%0': wrong password").arg(login.toLower());
            return 0;
        }
    }
}

User* ServerController::getUser(int id)
{
    auto str = QString("SELECT id, login, name, avatar_id, birthday FROM \"user\" WHERE id = %0;").arg(id);
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;

    User* user= new User(ivalue(0), svalue(1), svalue(2), ivalue(3), query.value(4).toDate());
    return user;
}

User *ServerController::getUser(QString login)
{
    auto str = QString("SELECT id FROM public.\"user\" where login = '%0';").arg(login.toLower());
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;
    return getUser(ivalue(0));
}

bool ServerController::addMemeber(int dialog_id, int member_id)
{
    QSqlQuery query(QString("INSERT INTO public.member(dialog_id, user_id) VALUES (%1, %2);").arg(dialog_id).arg(member_id));
    return query.exec();
}

bool ServerController::addDialog(UserDialog* dialog)
{
    QString str=QString("INSERT INTO public.dialog(name, avatar_id, is_group) VALUES ('%1', %2, %3) RETURNING id;")
            .arg(dialog->getName())
            .arg(dialog->getAvatarID())
            .arg(dialog->getIsGroup()?"true":"false");
    QSqlQuery query(str);
    query.first();
    dialog->setID(ivalue(0));
    int member_id;
    foreach(member_id, dialog->getMemberIDs())
        addMemeber(dialog->getID(), member_id);
}

bool ServerController::renameDialog(int id, QString name)
{
    QSqlQuery query(QString("UPDATE public.dialog SET name='%1' WHERE id = %2;").arg(name).arg(id));
    query.exec();
}

bool ServerController::changeAvatarDialog(int id, QByteArray file)
{
    int file_id = addFile(file, "", "");
    QSqlQuery query(QString("UPDATE public.dialog SET avatar_id=%1 WHERE id = %2;").arg(file_id).arg(id));
    return query.exec();
}

bool ServerController::updateUserInfo(User user, QByteArray avatar)
{
    int id_avatar=-1;
    if(avatar.count()!=0){
        id_avatar=addFile(avatar, "","");
    }

    QString str=QString("UPDATE public.\"user\" SET avatar_id=%1, name='%2', birthday='%3' WHERE id=%4;")
            .arg(id_avatar)
            .arg(user.getName())
            .arg(user.getBirthDate().toString("dd MM yyyy"))
            .arg(user.getID());
    QSqlQuery query(str);

    return query.exec();
}

int ServerController::getCountDayFromDembel()
{
    QDate date(2022,7,6);
    return (QDate::currentDate().daysTo(date));
}

QVector<QString> ServerController::getNetUsers(QString login)
{
    auto str = QString("select login from \"user\" where id = ANY(SELECT distinct(user_id) FROM public.member where dialog_id = any(select dialog_id from member inner join \"user\" on \"user\".id = user_id where login = '%1') except select user_id from member inner join \"user\" on \"user\".id = user_id where login = '%1');").arg(login.toLower());
    QSqlQuery query(str);

    QVector<QString> logins;

    while(query.next()){
        logins.append(svalue(0));
    }

    return logins;
}

void ServerController::readAllMessagesByChat(QString login, int chat_id)
{
    User* user = getUser(login);
    int user_id = user->getID();
    delete user;
    auto str = QString("UPDATE public.status SET status=3 WHERE dialog_id = %1 and user_id = %2;").arg(chat_id).arg(user_id);
    QSqlQuery query(str);

    query.exec();
}

int ServerController::loadUsers()
{
    QSqlQuery query("SELECT id, login, name, avatar_id, birthday FROM \"user\";");

    //    query.exec();
    while (query.next()) {
        User user(ivalue(0), svalue(1), svalue(2), ivalue(3), QDate::fromString(svalue(4)));
        users.push_back(user);
    }

    return 0;
}

int ServerController::getLastIdMessageDialog(int dialog_id)
{
    QSqlQuery query(QString("SELECT id FROM public.message WHERE dialog_id = %1 ORDER BY id DESC LIMIT 1;")
                    .arg(tostr(dialog_id)));
    query.first();
    return ivalue(0);
}
