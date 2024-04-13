#include "data_users.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Установка прав доступа к файлу для записи
void enableWriteAccess(const QString &filePath) {
    QFile file(filePath);
    file.setPermissions(QFile::WriteOwner | QFile::ReadOwner);
}
// Снятие прав доступа к файлу для записи
void disableWriteAccess(const QString &filePath) {
    QFile file(filePath);
    file.setPermissions(QFile::ReadOwner);
}
// Установка прав доступа к файлу для чтения
void enableReadAccess(const QString &filePath) {
    QFile file(filePath);
    file.setPermissions(QFile::ReadOwner | QFile::WriteOwner);
}
// Снятие прав доступа к файлу для чтения
void disableReadAccess(const QString &filePath) {
    QFile file(filePath);
    file.setPermissions(QFile::WriteOwner);
}

bool createUser(const QString &filePath, const QString &login, const QString &password, const QString &name) {
    // Включаем доступ на запись
    enableWriteAccess(filePath);

    // Открываем файл для записи
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для записи:" << file.errorString();
        return false;
    }

    // Записываем данные пользователя (логин, пароль, имя)
    QTextStream out(&file);
    out << login << "," << password << "," << name << endl;

    // Закрываем файл и отключаем доступ на запись
    file.close();
    disableWriteAccess(filePath);

    // Включаем доступ на чтение
    disableReadAccess(filePath);

    return true;
}
// проверка существования пользователя по логину и паролю
bool userExists(const QString &filePath, const QString &login, const QString &password) {
    // Включаем доступ на чтение
    enableReadAccess(filePath);

    // Открываем файл для чтения
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для чтения:" << file.errorString();
        return false;
    }

    // Ищем пользователя
    QTextStream in(&file);
    while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userData = line.split(",");
            if (userData.size() >= 2 && userData[0] == login && userData[1] == password) {
                // Нашли пользователя, отключаем доступ на чтение и закрываем файл
                disableReadAccess(filePath);
                file.close();
                return true;
            }
        }

    // Пользователь не найден, отключаем доступ на чтение и закрываем файл
    disableReadAccess(filePath);
    file.close();
    return false;
}

bool userExists(const QString &filePath, const QString &login) {
    // Включаем доступ на чтение
    enableReadAccess(filePath);

    // Открываем файл для чтения
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для чтения:" << file.errorString();
        return false;
    }

    // Ищем пользователя
    QTextStream in(&file);
    while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userData = line.split(",");
            if (userData.size() >= 1 && userData[0] == login) {
                // Нашли пользователя, отключаем доступ на чтение и закрываем файл
                disableReadAccess(filePath);
                file.close();
                return true;
            }
        }

    // Пользователь не найден, отключаем доступ на чтение и закрываем файл
    disableReadAccess(filePath);
    file.close();
    return false;
}
