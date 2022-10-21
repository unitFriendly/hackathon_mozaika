#ifndef FIX_H
#define FIX_H

#include <QObject>
#include "dstprivatechat.h"
#include "srcprivatechat.h"

class Fix : public QObject
{
    Q_OBJECT
public:
    explicit Fix(QObject *parent = nullptr);

    static QVector<SrcPrivateChat*> privateChatsSrc;
    static QVector<DstPrivateChat*> privateChatsDst;

    static QString loginUser;
    static bool isAuthorized;

    static quint16 START_PORT_LISTENER;

signals:

};

#endif // FIX_H
