#include "test.h"

Test::Test(QObject *parent) : QObject(parent)
{
    MassageTest* mas = new MassageTest();
    MassageTest* mas1 = new MassageTest();
    MassageTest* mas2 = new MassageTest();
    MassageTest* mas3 = new MassageTest();
    MassageTest* spamTrue = new MassageTest();
    MassageTest* spamFalse = new MassageTest();

    MassageTest* temp1 = new MassageTest();

    temp1->setMulti("adsasdasdsa asd asd as da das das sssssssssssss sd as sadasdsadas asdasda asdsadasd asd asd asd asd sad asdasdasdasd as adaasdsd a a a dsddsdsds sdsdsdsd sdsdsdsdsd sd  sdsdsdsd sdsdsdsd sdsdsdsds dsdsdsds dsdsdsd sdsdsdsd sd sd sdsdsdsds sdsdsdsd sdsdsdsds sdsdsds sdsdsd sdsdsd", false);


    array.push_back(temp1);
    spamFalse->setMulti("spamFalse", false);
    spamTrue->setMulti("spamTrue", true);
    mas->setMulti("Hi", true);
    mas1->setMulti("Hi", false);
    mas2->setMulti("How are you?",true);
    mas3->setMulti("i`m fine and you?", false);

//    test___.push_back(1);

    array.push_back(mas);
    array.push_back(mas1);
    array.push_back(mas2);
    array.push_back(mas3);

    for (int i = 0; i < 10; i++)
    {
        array.push_back(spamTrue);
        array.push_back(spamFalse);
    }
}

void Test::emitMultiWidget()
{
    emit onEverythingMessage();
}

int Test::getSizeMinuts(int size)
{
    return size/1000/60;
}

int Test::getSizeSeconds(int size)
{
    return size/1000%60;
}

QString Test::getMassage(int index)
{
    //        qDebug() <<"getMassage"<< index;
    return array[index]->getMessage();
}

bool Test::getIsCheked(int index)
{
//    qDebug() <<"array[index]->getStatus()"<< array[index]->getStatus();
    return array[index]->getStatus();
}

int Test::getSizeVector()
{
    return array.size();
}

int Test::getSizeMessage(int index)
{
    return array[index]->getSizeMessagePx();
}

void Test::createNewMessage(QString message, bool status)
{
    if (message != "")
    {
        MassageTest *newMessage = new MassageTest();
        newMessage->setMulti(message, status);
        array.append(newMessage);

        emit onCreateNewMassage();
    }
}

void Test::createNewDialog(QString login)
{
    if(login != "")
    {
        emit onCreateNewDialog();
    }
}

void Test::getMediaMessage()
{
    emit onMediaMessage();
}

