#ifndef SETTINGSDATA_H
#define SETTINGSDATA_H

#include <QObject>
#include <QVector>
#include <QDebug>

class SettingsData : public QObject
{
    Q_OBJECT
public:
    explicit SettingsData(QObject *parent = nullptr);

    QVector<QString> arrayPointSettings = {"Аккаунт", "Уведомления", "Память", "Тема"};

    //Account
    QVector<QString> arrayPointSettingsAccount = {"Логин", "Пароль", "Телефон", "Дата рождения", "Язык"};
    QVector<QString> arrayAnswerPointSettingsAccount = {"5NR_Operator_27", "Сменить", "*********", "27.09.1997", "Русский"};

    //Notification
    QVector<QString> arrayPointSettingsNotification = {"Уведомления", "Отображать содержимое \nсообщение"};
    QVector<QString> arrayAnswerSettingsNotification = {"Включены", "Только при разблокировке"};

    //Memory
    QVector<QString> arrayPointSettingsMemory = {"Место сохранения файлов", "Автоматическая загрузка медиаконтента", "Автоматически очищать\nмедиаконтент"};
    QVector<QString> arrayAnswerSettingsMemory {"Внутренняя память", "Выключено", "Спустя 3 месяца"};

    //Themes
    QVector<QString> arrayPointSettingsThemes = {"Фон диалогов", "Палитра"};
    QVector<QString> arrayAnswerSettingsThemes = {"Выбрать", "ХЗ"};

    QVector<QVector<QString>> point;
    QVector<QVector<QString>> answer;
    int sizeJustSize;



public slots:
    QString getArrayPointSettings(int value);
    QString getArrayPointSettingsAccount(int value);
    QString getArrayAnswerPointSettingsAccount(int value);
    QString getArrayPointSettingsNotification(int value);
    QString getArrayAnswerSettingsNotification(int value);
    QString getArrayPointSettingsMemory(int value);
    QString getArrayAnswerSettingsMemory(int value);
    QString getArrayPointSettingsThemes(int value);
    QString getArrayAnswerSettingsThemes(int value);

    int getSizeArrayPointSettings();
    int getSizeArrayPointSettingsAccount();
    int getSizeArrayAnswerPointSettingsAccount();
    int getSizeArrayPointSettingsNotification();
    int getSizeArrayAnswerSettingsNotification();
    int getSizeArrayPointSettingsMemory();
    int getSizeArrayAnswerSettingsMemory();
    int getSizeArrayPointSettingsThemes();
    int getSizeArrayAnswerSettingsThemes();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~
    int getSizePointSettings(int value);
    int getSizeAnswerSettings(int value);

    QString getPointSettings(int countIndex, int index);
    QString getAnswerSettings(int countIndex, int index);


    int getSizeJustSize();
    void setSizeJustSize(int value);


    //~~~~~~~~~~~~~~~~~~~~~~~~~~

signals:

};

#endif // SETTINGSDATA_H
