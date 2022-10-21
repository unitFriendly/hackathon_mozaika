#include "myfile.h"



QByteArray MyFile::readFile()
{
    QFile file("C:/Users/Tihon/Desktop/hack_new/secondday/build-super_server-3-Debug/debug/super_garbage/" + path);
    file.open(QIODevice::ReadOnly);
    QByteArray bytes=file.readAll();
    return  bytes;
}
