#ifndef DIALOGSVECTOR_H
#define DIALOGSVECTOR_H

#include <QObject>
#include <QVector>
#include "dialogclient.h"


class DialogsVector : public QObject
{
    Q_OBJECT

public:
    dialogClient dialogs;
    explicit DialogsVector(QObject *parent = nullptr){};

    void setDialogs(dialogClient _dialogs) {dialogs=_dialogs;}
//    DialogsVector(DialogsVector& _DialogsVector): dialogs(_DialogsVector.dialogs) {};

//    const DialogsVector operator =(DialogsVector _DialogsVector) const{
//        DialogsVector __DialogsVector(_DialogsVector);
//        return __DialogsVector;
//    }

//    friend bool operator==(const DialogsVector& user1, const DialogsVector& user2) { return user1.dialogs == user2.dialogs; }

//    Q_INVOKABLE MyVector<UserDialog> getMyDialogs();
//public slots:
//    void getDialogs(MyVector<UserDialog>);

//signals:
//    void onGetDialogsCompletted();
};

#endif // DIALOGSVECTOR_H
