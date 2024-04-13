#include "registerwindow.h"
#include "ui_register.h"
#include "data_users.h"
#include <QMessageBox>
#include <QString>
#include <QFile>

registerWindow::registerWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register)
{
     ui->setupUi(this);

     // Подключаем сигнал clicked() кнопки "Регистрация" к слоту on_registrationButton_clicked()
     connect(ui->registrButton, &QPushButton::clicked, this, &registerWindow::on_registrButton_clicked);
}

void registerWindow::on_registrButton_clicked()
{
    // Получаем текст из QLineEdit для имени, логина и пароля
    QString name = ui->name->text();
    QString login = ui->login->text();
    QString password = ui->password->text();

    QString filePath = QCoreApplication::applicationDirPath() + "/user_data.txt";

    if(name.isEmpty() || login.isEmpty() || password.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    } else {
        if(userExists(filePath,login, password))
        {
            QMessageBox::critical(this, "КПЦ", "такой пользователь уже есть");
        } else {
            createUser(filePath,login, password, name);
            QMessageBox::information(this, "Регистрация",name + " " + "Вы успешно зарегистрировались");
            this->close();
        }
    }
}

registerWindow::~registerWindow()
{
    delete ui;
}
