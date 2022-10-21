#include "fix.h"

quint16 Fix::START_PORT_LISTENER = 2222;
QString Fix::loginUser = "";
bool Fix::isAuthorized = false;

QVector<SrcPrivateChat*> Fix::privateChatsSrc = QVector<SrcPrivateChat*>();
QVector<DstPrivateChat*> Fix::privateChatsDst = QVector<DstPrivateChat*>();

Fix::Fix(QObject *parent) : QObject(parent)
{

}
