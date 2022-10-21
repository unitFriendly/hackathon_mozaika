#ifndef MYFILE_H
#define MYFILE_H

#include <QString>
#include <QFile>

class MyFile
{
private:
    int id;
    QString path;
    QString name;
    QString type;
public:
    MyFile(int _id, QString _path, QString _name, QString _type): id(_id), path(_path), name(_name), type(_type) {}
    QByteArray readFile();
    int getId(){return id;};
    QString getPath(){return path;};
    QString getName(){return name;};
    QString getType(){return type;};
};

#endif // MYFILE_H
