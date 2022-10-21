#include <QCoreApplication>
#include "servergeneral.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

      qDebug() << QDir::currentPath();
//    qDebug() << ProtocolTrade::___CMD_SEND_MESSAGE;

    ServerController* controller = ServerController::getInstance();

//    controller->addMessage(4,2,"Кто не спит?",QMap<QString,QByteArray>());
    ServerGeneral server;

    //HandlerCommand::ReadAllMessagesByChat(nullptr, nullptr);

    return a.exec();
}
