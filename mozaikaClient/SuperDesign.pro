QT += quick sql network websockets multimedia


CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Client/clientgeneral.cpp \
        Client/dstprivatechat.cpp \
        Client/fix.cpp \
        Client/generalfunctionsocket.cpp \
        Client/handlercommand.cpp \
        Client/protocoltrade.cpp \
        Client/srcprivatechat.cpp \
        Client/super_server/dialogclient.cpp \
        Client/super_server/dialogsvector.cpp \
        Client/super_server/message.cpp \
        Client/super_server/myfile.cpp \
        Client/super_server/myvector.cpp \
        Client/super_server/user.cpp \
        Client/super_server/userdialog.cpp \
        clientdata.cpp \
        contactslist.cpp \
        dateleft.cpp \
        main.cpp \
        massagetest.cpp \
        settingsdata.cpp \
        test.cpp \
        userdata.cpp \
        userdata.cpp

RESOURCES += qml.qrc \
    Client/resourcesServer.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Client/clientgeneral.h \
    Client/dstprivatechat.h \
    Client/fix.h \
    Client/generalfunctionsocket.h \
    Client/handlercommand.h \
    Client/protocoltrade.h \
    Client/srcprivatechat.h \
    Client/super_server/dialogclient.h \
    Client/super_server/dialogsvector.h \
    Client/super_server/message.h \
    Client/super_server/myfile.h \
    Client/super_server/myvector.h \
    Client/super_server/user.h \
    Client/super_server/userdialog.h \
    clientdata.h \
    contactslist.h \
    dateleft.h \
    massagetest.h \
    settingsdata.h \
    test.h \
    userdata.h \
    userdata.h

SUBDIRS += \
    ../Client/super_server/super_server.pro

DISTFILES += \
    Client/localhost.cert \
    Client/localhost.key
    test.h \
