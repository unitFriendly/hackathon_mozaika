QT -= gui
QT += network sql websockets

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        generalfunctionsocket.cpp \
        handlercommand.cpp \
        main.cpp \
        protocoltrade.cpp \
        servergeneral.cpp \
        super_server/message.cpp \
        super_server/myfile.cpp \
        super_server/servercontroller.cpp \
        super_server/user.cpp \
        super_server/userdialog.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    generalfunctionsocket.h \
    handlercommand.h \
    protocoltrade.h \
    servergeneral.h \
    super_server/message.h \
    super_server/myfile.h \
    super_server/servercontroller.h \
    super_server/user.h \
    super_server/userdialog.h

RESOURCES += resourcesServer.qrc

SUBDIRS += \
    super_server/super_server.pro
