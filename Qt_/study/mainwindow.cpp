#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "account.h" // Подключаем заголовочный файл нового окна
#include "menu.h"    // Подключаем заголовочный файл окна Menu
#include <QMessageBox>
#include <QSqlQuery> // Добавлено для QSqlQuery
#include <QSqlError>

bool isAccountWindowOpen = false;

MainWindow::MainWindow(QSqlDatabase &database, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), db(database)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    if (isAccountWindowOpen) {
        qDebug() << "Account window is already open.";
        return;
    }

    isAccountWindowOpen = true;
    qDebug() << "Login button clicked.";

    Account accountWindow(db, true, this); // true - режим входа
    if (accountWindow.exec() == QDialog::Accepted) {
        // Получаем имя пользователя из окна входа
        QString username = accountWindow.getUsername();

        // Получаем роль и ID пользователя из базы данных
        QSqlQuery query(db);
        query.prepare("SELECT id, role FROM users WHERE username = :username");
        query.bindValue(":username", username);

        if (!query.exec()) {
            qDebug() << "Database error during role retrieval:" << query.lastError().text();
            QMessageBox::critical(this, "Ошибка", "Не удалось получить данные пользователя!");
            isAccountWindowOpen = false;
            return;
        }

        if (query.next()) {
            int userId = query.value(0).toInt(); // ID пользователя
            QString role = query.value(1).toString(); // Роль пользователя
            qDebug() << "User ID retrieved:" << userId << ", Role:" << role;

            // Открываем главное меню
            Menu *menuWindow = new Menu(db, role, userId, this); // Передаем role и userId
            menuWindow->setWindowIcon(QIcon(":/icons/img_384101.png")); // Устанавливаем иконку
            this->hide(); // Скрываем главное окно

            // Показываем окно меню
            menuWindow->show();

            // Обработка закрытия окна меню
            connect(menuWindow, &Menu::menuClosed, this, [this]() {
                qDebug() << "Menu closed, showing MainWindow.";
                this->show(); // Показываем главное окно после закрытия меню
            });
        }
    }

    isAccountWindowOpen = false;
}

void MainWindow::on_createAccountButton_clicked()
{
    if (isAccountWindowOpen) {
        qDebug() << "Account window is already open.";
        return;
    }

    isAccountWindowOpen = true;
    qDebug() << "Create account button clicked.";

    Account accountWindow(db, false, this); // false - режим регистрации
    accountWindow.exec();

    isAccountWindowOpen = false;
}

void MainWindow::on_exitButton_clicked()
{
    close();
}
