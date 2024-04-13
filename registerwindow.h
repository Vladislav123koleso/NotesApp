#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
#include <QDialog>
#include<QtGlobal>

QT_BEGIN_NAMESPACE
namespace Ui { class Register; }
QT_END_NAMESPACE

class registerWindow : public QDialog
{
    Q_OBJECT

public:
    registerWindow(QWidget *parent = nullptr);
    ~registerWindow();

    void on_registrButton_clicked();
private:
    Ui::Register *ui;

};

#endif // REGISTERWINDOW_H
