#include "massagetest.h"

MassageTest::MassageTest(QObject *parent) : QObject(parent)
{

}

void MassageTest::setMulti(QString str, bool flag)
{
    message = str;
    status = flag;
}

int MassageTest::getSizeMessagePx()
{
    return message.size();
}

QString MassageTest::getMessage()
{
    return message;
}

bool MassageTest::getStatus()
{
    return status;
}


