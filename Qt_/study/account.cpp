#include "account.h"
#include "ui_account.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

// Конструктор
Account::Account(QSqlDatabase &database, bool isLoginMode, QWidget *parent)
    : QDialog(parent), ui(new Ui::Account), db(database), isLoginMode(isLoginMode)
{
    ui->setupUi(this);

    qDebug() << "Account constructor called. Mode:" << (isLoginMode ? "Login" : "Register");

    // Настройка интерфейса в зависимости от режима
    if (isLoginMode) {
        setWindowTitle("Вход в аккаунт");
        ui->roleComboBox->setVisible(false); // Скрываем выбор роли для входа
    } else {
        setWindowTitle("Создание аккаунта");
    }

    // Автоматическое подключение уже настроено через имя метода on_confirmButton_clicked
    // НЕ добавляйте ручное подключение сигнала здесь!
}

// Деструктор
Account::~Account()
{
    delete ui;
}

// Обработчик кнопки "Подтвердить"
static int confirmButtonClickCount = 0;

QString Account::getUsername() const
{
    return username;
}

void Account::on_confirmButton_clicked()
{
    confirmButtonClickCount++;
    qDebug() << "Confirm button clicked. Count:" << confirmButtonClickCount;

    username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        qDebug() << "Error: Username or password is empty.";
        QMessageBox::warning(this, "Ошибка", "Логин или пароль не может быть пустым!");
        return;
    }

    if (isLoginMode) {
        // Режим входа
        QSqlQuery query(db);
        query.prepare("SELECT role FROM users WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if (!query.exec()) {
            qDebug() << "Database error during login:" << query.lastError().text();
            return;
        }

        if (query.next()) {
            QString role = query.value(0).toString();
            qDebug() << "Login successful. Role:" << role;
            QMessageBox::information(this, "Успех", "Вы вошли как " + role);
            accept(); // Закрыть окно после успешного входа
        } else {
            qDebug() << "Login failed: Invalid username or password.";
            QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
        }
    } else {
        // Режим регистрации
        QString role = ui->roleComboBox->currentText().toLower();

        // Преобразование роли в допустимый формат
        if (role == "ученик") {
            role = "student";
        } else if (role == "преподаватель") {
            role = "teacher";
        } else {
            qDebug() << "Invalid role value:" << role;
            QMessageBox::warning(this, "Ошибка", "Неверная роль!");
            return;
        }

        qDebug() << "Checking username:" << username;

        // Проверка, существует ли уже пользователь с таким логином
        QSqlQuery checkQuery(db);
        checkQuery.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
        checkQuery.bindValue(":username", username);

        if (!checkQuery.exec()) {
            qDebug() << "Database error during registration (check):" << checkQuery.lastError().text();
            return;
        }

        if (checkQuery.next()) {
            int count = checkQuery.value(0).toInt();
            qDebug() << "User count for username:" << username << "is" << count;

            if (count > 0) {
                qDebug() << "Registration failed: User already exists.";
                QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином уже существует!");
                return;
            }
        }

        qDebug() << "Inserting new user. Username:" << username << ", Role:" << role;

        // Добавление нового пользователя в базу данных
        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO users (username, password, role) VALUES (:username, :password, :role)");
        insertQuery.bindValue(":username", username);
        insertQuery.bindValue(":password", password);
        insertQuery.bindValue(":role", role);

        if (!insertQuery.exec()) {
            qDebug() << "Database error during registration (insert):" << insertQuery.lastError().text();
            QMessageBox::critical(this, "Ошибка", "Не удалось создать аккаунт!");
            return;
        }

        qDebug() << "Registration successful. Username:" << username << ", Role:" << role;
        QMessageBox::information(this, "Успех", "Аккаунт успешно создан!");
        accept(); // Закрыть окно после успешной регистрации
    }
}

// Обработчик кнопки "Назад"
void Account::on_backButton_clicked()
{
    reject(); // Закрыть окно без сохранения изменений
}
