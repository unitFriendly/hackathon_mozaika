#include "protocoltrade.h"

const QString ProtocolTrade::___COMMAND = QString("command");
const QString ProtocolTrade::___CMD_AUTHORIZATION = QString("authorization");
const QString ProtocolTrade::___CMD_GET_CHATS = QString("getchats");
const QString ProtocolTrade::___CMD_GET_MESSAGES = QString("getmessages");
const QString ProtocolTrade::___CMD_CREATE_PRIVATE_CHAT = QString("createprivatechat");
const QString ProtocolTrade::___CMD_SEND_MESSAGE = QString("sendmessage");
const QString ProtocolTrade::___CMD_SEND_PRIVATE_MESSAGE = QString("sendprivatemessage");
const QString ProtocolTrade::___CMD_CREATE_CHAT = QString("createchat");
const QString ProtocolTrade::___CMD_GET_DATE_USER = QString("getdateuser");
const QString ProtocolTrade::___CMD_UPDATE_STATUS_USER = QString("getusersfromdialog");
const QString ProtocolTrade::___CMD_UPDATE_STATUS_MESSAGE = QString("updatestatusmessage");
const QString ProtocolTrade::___CMD_GET_USERS_FROM_DIALOG = QString("getusersfromdialog");
const QString ProtocolTrade::___CMD_READ_ALL_MESSAGE_BY_CHAT = QString("readallmessagebychat");
const QString ProtocolTrade::___CMD_UDATE_CHAT = QString("updatechat");
const QString ProtocolTrade::___LOGIN = QString("login");
const QString ProtocolTrade::___PASSWORD = QString("password");
const QString ProtocolTrade::___STATUS = QString("status");
const QString ProtocolTrade::___STS_DONE = QString("done");
const QString ProtocolTrade::___STS_NOPE = QString("nope");
const QString ProtocolTrade::___USER_NAME = QString("username");
const QString ProtocolTrade::___AVATAR = QString("avatar");
const QString ProtocolTrade::___BINARY_FILE = QString("binaryfile");
const QString ProtocolTrade::___NAME_FILE = QString("namefile");
const QString ProtocolTrade::___TYPE_FILE = QString("typefile");
const QString ProtocolTrade::___BIRTH_DATE = QString("birthdate");
const QString ProtocolTrade::___ARR_CHATS = QString("arrchats");
const QString ProtocolTrade::___ID_CHAT = QString("idchat");
const QString ProtocolTrade::___CHAT_GROUP = QString("chatgroup");
const QString ProtocolTrade::___ARR_USERS = QString("arrusers");
const QString ProtocolTrade::___ARR_MESSAGES = QString("arrmessages");
const QString ProtocolTrade::___ID_MESSAGE = QString("idmessage");
const QString ProtocolTrade::___TEXT_MESSAGE = QString("textmessage");
const QString ProtocolTrade::___ARR_ATTACHMENT = QString("arrattachment");
const QString ProtocolTrade::___STATUS_MESSAGE = QString("statusmessage");
const QString ProtocolTrade::___STS_READ = QString("read");
const QString ProtocolTrade::___STS_TAKEN = QString("taken");
const QString ProtocolTrade::___STS_NON_TAKEN = QString("nontaken");
const QString ProtocolTrade::___IP_USER = QString("ipuser");
const QString ProtocolTrade::___PORT_USER = QString("portuser");
const QString ProtocolTrade::___TMP_ID_MESSAGE = QString("tmpidmessage");
const QString ProtocolTrade::___TMP_ID_CHAT = QString("tmpidchat");
const QString ProtocolTrade::___STATUS_USER = QString("statususer");
const QString ProtocolTrade::___STS_ONLINE = QString("online");
const QString ProtocolTrade::___STS_OFFLINE = QString("offline");
//<<<<<<< HEAD
const QString ProtocolTrade::___STS_ON_SERVER = QString("onserver");
//=======
const QString ProtocolTrade::___COUNT_MESSAGE = QString("countmessage");
//>>>>>>> origin/back

ProtocolTrade::ProtocolTrade(QObject *parent) : QObject(parent)
{

}

QString ProtocolTrade::ByteArrayToString(QByteArray array)
{
    QString result(array.size(), QChar(255));

    for(int i = 0; i < array.size(); i++)
    {
        result[i] = array[i];
    }

    return result;
}

QByteArray ProtocolTrade::StringToByteArray(QString string)
{
    QByteArray byteArray(string.size(), (char)255);

    for(int i = 0; i < byteArray.size(); i++)
    {
        byteArray[i] = string[i].toLatin1();
    }

    return byteArray;
}

QString ProtocolTrade::SaveBinaryFile(QString binary, QString name, QString type, QString idMsg, QString idChat)
{
    if(binary.length()==0) return "";

    if(type=="")type="png";

    QDir dir = QDir::currentPath();
    QString path = "client_garbarge/";
    QFile file("client_garbarge/" + name + "." + type);

    file.open(QIODevice::WriteOnly);

    QByteArray byteArray(binary.size(), (char)255);

    for(int i = 0; i < byteArray.size(); i++)
    {
        byteArray[i] = binary[i].toLatin1();
    }

    file.write(byteArray);
    file.close();

    return file.fileName();
}

QByteArray ProtocolTrade::LoadBinaryFile(QString path)
{
    QByteArray byteArray;
    QFile file(path);
    file.open(QFile::ReadOnly);
    byteArray = file.readAll();
    file.close();
    return byteArray;
}

void ProtocolTrade::SendTextMessage(QString message, QWebSocket *client)
{
    client->sendTextMessage(message);
}

void ProtocolTrade::SendBinaryMessage(QByteArray message, QWebSocket *client)
{
    client->sendBinaryMessage(message);
}

QString ProtocolTrade::JsonObjectToString(QJsonObject *object)
{
    static QJsonDocument jDoc;
    jDoc.setObject(*object);
    return jDoc.toJson();
}

QJsonObject ProtocolTrade::StringToJsonObject(QString str)
{
    static QJsonDocument jDoc;
    jDoc = QJsonDocument::fromJson(str.toUtf8());
    return jDoc.object();
}

bool ProtocolTrade::CompareSocket(QWebSocket* a, QWebSocket* b)
{
    return ((a->peerAddress() == b->peerAddress()) && (a->peerPort() == b->peerPort()));
}

QString ProtocolTrade::GetTypeFromPathFile(QString path)
{
    int indexDot = path.lastIndexOf('.');
    indexDot++;
    int lenType = path.size() - indexDot;
    QString result(lenType, ' ');

    for(int i = 0; i < lenType; i++)
    {
        result[i] = path[indexDot + i];
    }

    return result;
}

QString ProtocolTrade::GetNameFromPathFile(QString path)
{
    int indexDot = path.lastIndexOf('.');
    path.replace("/","\\");
    int indexStartName = path.lastIndexOf('\\') + 1;

    int lenType = indexDot - indexStartName;
    QString result(lenType, ' ');

    for(int i = 0; i < lenType; i++)
    {
        result[i] = path[indexStartName + i];
    }

    return result;
}
