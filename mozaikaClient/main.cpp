#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "test.h"
#include "contactslist.h"
#include "settingsdata.h"
#include "Client/clientgeneral.h"
#include "Client/super_server/user.h"
#include "Client/super_server/dialogsvector.h"
#include "clientdata.h"
#include "qdir.h"
#include "dateleft.h"
//#include "userdialog.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QString* currentDir=new QString(QDir::currentPath().toStdString().c_str());
    QDir dir(*currentDir);
    dir.mkdir(*currentDir+"/client_garbarge");


    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Test testMap;
    ContactsList addContact;
    SettingsData settingsData;

    User *currentUser = new User();

    ClientGeneral client;
    ClientData clientData;
    clientData.user = currentUser;

    DateLeft dateLeft;

    addContact.getVectorSize(0);

    engine.rootContext()->setContextProperty("currentDir", *currentDir);
    engine.rootContext()->setContextProperty("testMap", &testMap);
    engine.rootContext()->setContextProperty("contactsss", &addContact);
    engine.rootContext()->setContextProperty("settingsData",&settingsData);
    engine.rootContext()->setContextProperty("client", &client);
    engine.rootContext()->setContextProperty("clientData", &clientData);
    engine.rootContext()->setContextProperty("currentUser", currentUser);

    engine.rootContext()->setContextProperty("dateLeft", &dateLeft);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    const QUrl url(QStringLiteral("qrc:/Dialogs.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
