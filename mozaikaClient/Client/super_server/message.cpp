#include "message.h"

void Message::setId(int value)
{
    id = value;
}

void Message::setStatus(QString value)
{
    if(value == ProtocolTrade::___STS_READ)
    {
        status = 3;
    }
    else if(value == ProtocolTrade::___STS_TAKEN)
    {
        status = 2;
    }
    else if(value == ProtocolTrade::___STS_NON_TAKEN)
    {
        status = 0;
    }
    else if(value == ProtocolTrade::___STS_ON_SERVER)
    {
        status = 1;
    }
}

void Message::setStatus(int value)
{
    status = value;
}

void Message::addFile(MyFile file)
{
    files.append(file);
}

bool Message::operator<(const Message &d1) const
{

    return this->time<d1.time;
}

bool Message::operator>(const Message &d1) const
{
    return this->time>d1.time;
}
