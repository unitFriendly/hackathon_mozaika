#include <QCoreApplication>
#include <QSsl>
#include <QDebug>
#include "servercontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerController* controller = ServerController::getInstance();
        auto a0=controller->getUserDialogs(1);
        auto a1=controller->getUserDialogs(2);
        auto a2=controller->getUserDialogs(3);


        auto f1=controller->getFile(1);
        auto f2=controller->getFile(2);
        auto f3=controller->getFile(3);
//    controller->loadData();
//    //    controller->markReadedMessage(4);
//    controller->confirmAuthorization("maksim", "123");
//    controller->confirmAuthorization("maksim123", "123");

    //QString fileName=QDateTime::currentDateTime().toString()+name;

    //    controller->getFileBytes(1);




//    QMap<QString, QByteArray> map;
//    map["Безымянный.png"]=bytes;
//    controller->addMessage(3,
//                           2,"KAK DELA PARNI", map);

    //    QMap<QString, QByteArray> map;
    //    map["sex"] = bytes;

    //    QFile out("C:/Users/Tihon/Desktop/tmp.png");
    //    out.open(QIODevice::WriteOnly);

    //    out.write(map["Безымянный.png"]);

    //    out.close();


//    UserDialog slavik("SLAVIK");
//    slavik.addMember(1);
//    slavik.addMember(2);
//    slavik.addMember(3);
//    slavik.addMember(4);
//    controller->addDialog(slavik);

//    QFile file("C:/Users/Tihon/Desktop/l5evR.jpg");
//    file.open(QIODevice::ReadOnly);
//    QByteArray bytes=file.readAll();
//    User user(4,"","Владимир Владимирович", 2, QDate(2000, 2, 19));
//    controller->updateUserInfo(user,bytes);


//    int test = controller->addMessage(4,
//                               1,"KAK DELA PARNI", QMap<QString, QByteArray>());

//    qDebug() << test;

    qDebug() << "DONE";

    return a.exec();



    //    QMap<QString, QByteArray> map;
    //    map["Безымянный.png"]=bytes;
    //    controller->addMessage(1,3,"Socu is best", map);
}
