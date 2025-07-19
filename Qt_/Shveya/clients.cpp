#include "clients.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Clients::Clients(QObject *parent)
    : QObject(parent), model(new QSqlTableModel(this)) {
    // Настройка модели для работы с таблицей Clients
    model->setTable("Clients");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}

QSqlTableModel *Clients::getModel() {
    return model;
}

bool Clients::addClients(const QString &name, const QString &number) {
    // Проверка входных данных
    if (name.isEmpty() || number.isEmpty()) {
        qDebug() << "Ошибка: Имя клиента или номер телефона пусты.";
        return false;
    }

    // Подготовка запроса
    QSqlQuery query;
    query.prepare("INSERT INTO Clients (Name, Number) VALUES (?, ?)");
    query.addBindValue(name);
    query.addBindValue(number);

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Ошибка добавления клиента:" << query.lastError().text();
        return false;
    }

    // Обновление модели
    model->select();
    return true;
}

bool Clients::updateClients(int clientsID, const QString &name, const QString& number) {
    QSqlQuery query;
    query.prepare("UPDATE Clients SET Name = ?, Number = ? WHERE clientsID = ?");
    query.addBindValue(name);
    query.addBindValue(number);
    query.addBindValue(clientsID);

    if (!query.exec()) {
        qDebug() << "Ошибка обновления материала:" << query.lastError().text();
        return false;
    }
    model->select(); // Обновляем данные модели
    return true;
}

bool Clients::deleteClients(int clientsID) {
    QSqlQuery query;
    query.prepare("DELETE FROM Clients WHERE ClientID = ?");
    query.addBindValue(clientsID);

    if (!query.exec()) {
        qDebug() << "Ошибка удаления клиента:" << query.lastError().text();
        return false;
    }

    model->select(); // Обновляем данные модели
    return true;
}

void Clients::setEditable(bool editable) {
    if (editable) {
        model->setEditStrategy(QSqlTableModel::OnFieldChange); // Разрешить редактирование
    } else {
        model->setEditStrategy(QSqlTableModel::OnManualSubmit); // Отключить редактирование
    }
    model->select(); // Перечитать данные для синхронизации
}
