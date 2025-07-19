#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Account;
}

class Account : public QDialog
{
    Q_OBJECT

public:
    explicit Account(QSqlDatabase &database, bool isLoginMode, QWidget *parent = nullptr);
    ~Account();

    QString getUsername() const;

private slots:
    void on_confirmButton_clicked(); // Обработчик кнопки "Подтвердить"
    void on_backButton_clicked();    // Обработчик кнопки "Назад"

private:
    Ui::Account *ui;
    QSqlDatabase db;                 // Подключение к базе данных
    bool isLoginMode;                // Флаг режима: true - вход, false - регистрация

    QString username; // Поле для хранения имени пользователя
};

#endif // ACCOUNT_H
