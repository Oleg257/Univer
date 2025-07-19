#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QDir>


// Функция подключения к базе данных
bool connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/user/Documents/Shveya/atelier.db");

    if (!db.open()) {
        qDebug() << "Error:" << db.lastError().text();
        return false;
    }
    qDebug() << "Right!";
    return true;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Подключение файла стилей
    QFile styleFile(":/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = styleFile.readAll();
        a.setStyleSheet(styleSheet);
        styleFile.close();
    } else {
        qDebug() << "Не удалось открыть файл стилей.";
    }

    if (!connectToDatabase()) {
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
