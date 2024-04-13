#include "mainwindow.h"
#include "registerwindow.h"
#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "data_users.cpp"

#define FILE_PERMISSIONS (QFile::ReadOwner | QFile::WriteOwner)



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString filePath = QCoreApplication::applicationDirPath() + "/user_data.txt";

    // Создаем ограниченный файл
        QFile file(filePath);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.close();

        // Записываем пользователя
        createUser(filePath, "user1","password1","Иванов Иван");

        // Проверяем существование пользователя
        if (userExists(filePath, "user1", "password1")) {
            qDebug() << "Пользователь найден.";
        } else {
            qDebug() << "Пользователь не найден.";
        }

    return a.exec();
}
