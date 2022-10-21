#include "settingsdata.h"

SettingsData::SettingsData(QObject *parent) : QObject(parent)
{
    point.append(arrayPointSettingsAccount);
    point.append(arrayPointSettingsNotification);
    point.append(arrayPointSettingsMemory);
    point.append(arrayPointSettingsThemes);

    answer.append(arrayAnswerPointSettingsAccount);
    answer.append(arrayAnswerSettingsNotification);
    answer.append(arrayAnswerSettingsMemory);
    answer.append(arrayAnswerSettingsThemes);
}

int SettingsData::getSizeJustSize()
{
    return sizeJustSize;
}

void SettingsData::setSizeJustSize(int value)
{
    sizeJustSize = value;
}

QString SettingsData::getArrayAnswerSettingsThemes(int value)
{
    return arrayAnswerSettingsThemes.at(value);
}

int SettingsData::getSizeArrayPointSettings()
{
    return arrayPointSettings.size();
}

int SettingsData::getSizeArrayPointSettingsAccount()
{
    return arrayPointSettingsAccount.size();
}

int SettingsData::getSizeArrayAnswerPointSettingsAccount()
{
    return arrayAnswerPointSettingsAccount.size();
}

int SettingsData::getSizeArrayPointSettingsNotification()
{
    return arrayPointSettingsNotification.size();
}

int SettingsData::getSizeArrayAnswerSettingsNotification()
{
    return arrayAnswerSettingsNotification.size();
}

int SettingsData::getSizeArrayPointSettingsMemory()
{
    return arrayPointSettingsMemory.size();
}

int SettingsData::getSizeArrayAnswerSettingsMemory()
{
    return arrayAnswerSettingsMemory.size();
}

int SettingsData::getSizeArrayPointSettingsThemes()
{
    return arrayPointSettingsThemes.size();
}

int SettingsData::getSizeArrayAnswerSettingsThemes()
{
    return arrayAnswerSettingsThemes.size();
}

int SettingsData::getSizePointSettings(int value)
{
    qDebug() << "getSizePointSettings" << point[value].size();
    return point[value].size();
}

int SettingsData::getSizeAnswerSettings(int value)
{
    qDebug() << "getSizeAnswerSettings" << answer[value].size();
    return answer[value].size();
}

QString SettingsData::getPointSettings(int countIndex, int index)
{
    return point[countIndex][index];
}

QString SettingsData::getAnswerSettings(int countIndex, int index)
{
    return answer[countIndex][index];
}

QString SettingsData::getArrayPointSettingsThemes(int value)
{
    return arrayPointSettingsThemes.at(value);
}

QString SettingsData::getArrayAnswerSettingsMemory(int value)
{
    return arrayAnswerSettingsMemory.at(value);
}

QString SettingsData::getArrayPointSettingsMemory(int value)
{
    return arrayPointSettingsMemory.at(value);
}

QString SettingsData::getArrayAnswerSettingsNotification(int value)
{
    return arrayAnswerSettingsNotification.at(value);
}

QString SettingsData::getArrayPointSettingsNotification(int value)
{
    return arrayPointSettingsNotification.at(value);
}

QString SettingsData::getArrayAnswerPointSettingsAccount(int value)
{
    return arrayAnswerPointSettingsAccount.at(value);
}

QString SettingsData::getArrayPointSettingsAccount(int value)
{
    return arrayPointSettingsAccount.at(value);
}

QString SettingsData::getArrayPointSettings(int value)
{
    return arrayPointSettings.at(value);
}
