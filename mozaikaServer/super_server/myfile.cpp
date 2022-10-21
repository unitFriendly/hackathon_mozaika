#include "myfile.h"
#include "servercontroller.h"

QByteArray MyFile::readFile()
{
    QFile file(ServerController::pathGarbage + path);
    file.open(QIODevice::ReadOnly);
    QByteArray bytes=file.readAll();
    return  bytes;
}
