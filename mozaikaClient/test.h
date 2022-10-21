#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QVector>
#include "massagetest.h"
#include "contactslist.h"

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);

    QVector<MassageTest*> array;

    QVector<QString> audio = {"audio 1, audio 2"};
    QVector<QString> picture = {"qrc:/resourses/avatar/baba.tif, qrc:/resourses/avatar/kloun.tif"};


public slots:

    int getSizeAudio() { return audio.size();}

    int getSizePicture() { return picture.size();}

    void emitMultiWidget();

    int getSizeMinuts(int size);

    int getSizeSeconds(int size);



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    QString getMassage(int index);
    bool getIsCheked(int index);
    int getSizeVector();

    int getSizeMessage(int index);

    void createNewMessage(QString message, bool status);

    void createNewDialog(QString login);

    void getMediaMessage();

signals:
    void onCreateNewMassage();

    void onCreateNewDialog();

    void onMediaMessage();

    void onEverythingMessage(/*QVector<QString>, QVector<QString>, int, int*/);


};

#endif // TEST_H
