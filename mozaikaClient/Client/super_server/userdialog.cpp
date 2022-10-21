#include "userdialog.h"

int UserDialog::getCountUnChecked()
{
    int count=0;
    foreach(auto m,messages)
        if(m.getStatus()!=3)
        {
            count++;
        }


    return count;
}

void UserDialog::setCountUnChecked(int value)
{
    countUnChecked = value;
}

bool UserDialog::getIsOnline()
{
    return isOnline;
}

void UserDialog::setIsOnline(bool value)
{
    isOnline = value;
}

void UserDialog::SortBy()
{
    for(int startIndex = 0; startIndex < messages.length()-1; ++startIndex){
        int smallestIndex = startIndex;
        for(int currIndex = startIndex+1; currIndex < messages.length(); ++currIndex){
            if(messages[currIndex]<messages[smallestIndex])
                smallestIndex = currIndex;
        }
        std::swap(messages[startIndex], messages[smallestIndex]);
    }

}

void UserDialog::addMessage(Message msg)
{
    messages.append(msg);
    //    messages.append(msg);
}

Message UserDialog::getLastMessage()
{
    if(messages.count()!=0)
        return messages.last();
}

int UserDialog::addMember(User *user)
{

    if (!members.contains(user->getLogin())) {
        members.append(user->getLogin());
        return 0;
    }
    return 1;
}

//QVector<int> UserDialog::getMemberIDs()
//{
//    return members;
//}

QVector<QString> UserDialog::getMemberLogins()
{
    return members;
}

Message getLastMessage(QVector<Message> arr){
    Message res = arr[0];
    for(int i = 1; i<arr.length(); i++){
        if(arr[i]>res)
            res = arr[i];
    }

    return res;
}

bool UserDialog::operator<(const UserDialog &d1) const
{

    Message m1=messages.last();
    Message m2=d1.messages.last();

    return m1.getTime()<m2.getTime();
}

bool UserDialog::operator>(const UserDialog &d1) const
{

    Message m1=messages.last();
    Message m2=d1.messages.last();

    return m1.getTime()>m2.getTime();
}
