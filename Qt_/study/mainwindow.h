#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QSqlDatabase &database, QWidget *parent = nullptr); // Объявление конструктора
    ~MainWindow();

private slots:
    void on_loginButton_clicked();       // Обработчик нажатия на "Войти в аккаунт"
    void on_createAccountButton_clicked(); // Обработчик нажатия на "Создать аккаунт"
    void on_exitButton_clicked();        // Обработчик нажатия на "Выйти"

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;                     // Подключение к базе данных
};

#endif // MAINWINDOW_H
