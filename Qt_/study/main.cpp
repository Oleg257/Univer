#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QIcon> // Подключите этот заголовочный файл для работы с иконками

// Функция подключения к базе данных
bool connectToDatabase(QSqlDatabase &db) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/user/Documents/study/test.db");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
        return false;
    }
    qDebug() << "Подключение к базе данных успешно!";
    return true;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Устанавливаем глобальную иконку для приложения
    a.setWindowIcon(QIcon(":/icons/img_243887.png")); // Укажите путь к иконке в ресурсах

    // Создаем объект базы данных
    QSqlDatabase db;

    // Проверка подключения к базе данных
    if (!connectToDatabase(db)) {
        return -1; // Завершаем программу, если не удалось подключиться к БД
    }

    // Создание и отображение главного окна с передачей базы данных
    MainWindow w(db); // Передаем объект базы данных в конструктор MainWindow
    w.show();

    return a.exec();
}
