#include "materials.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Materials::Materials(QObject *parent)
    : QObject(parent), model(new QSqlTableModel(this)) {
    // Настройка модели для работы с таблицей Materials
    model->setTable("Materials");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}

QSqlTableModel *Materials::getModel() {
    return model;
}

bool Materials::addMaterial(const QString &name, int stock) {
    QSqlQuery query;
    query.prepare("INSERT INTO Materials (Name, Stock) VALUES (?, ?)");
    query.addBindValue(name);
    query.addBindValue(stock);
    if (!query.exec()) {
        qDebug() << "Ошибка добавления материала:" << query.lastError().text();
        return false;
    }
    model->select(); // Обновляем данные модели
    return true;
}

bool Materials::updateMaterial(int materialID, const QString &name, int stock) {
    QSqlQuery query;
    query.prepare("UPDATE Materials SET Name = ?, Stock = ? WHERE MaterialID = ?");
    query.addBindValue(name);
    query.addBindValue(stock);
    query.addBindValue(materialID);
    if (!query.exec()) {
        qDebug() << "Ошибка обновления материала:" << query.lastError().text();
        return false;
    }
    model->select(); // Обновляем данные модели
    return true;
}

bool Materials::deleteMaterial(int materialID) {
    QSqlQuery query;
    query.prepare("DELETE FROM Materials WHERE MaterialID = ?");
    query.addBindValue(materialID);
    if (!query.exec()) {
        qDebug() << "Ошибка удаления материала:" << query.lastError().text();
        return false;
    }
    model->select(); // Обновляем данные модели
    return true;
}

void Materials::setEditable(bool editable) {
    if (editable) {
        model->setEditStrategy(QSqlTableModel::OnFieldChange); // Разрешить редактирование
    } else {
        model->setEditStrategy(QSqlTableModel::OnManualSubmit); // Отключить редактирование
    }
    model->select(); // Перечитать данные для синхронизации
}

// Новый метод для обновления запаса материала
bool Materials::updateStock(int materialID, int delta) {
    QSqlQuery query;
    query.prepare("UPDATE Materials SET Stock = Stock + ? WHERE MaterialID = ?");
    query.addBindValue(delta);
    query.addBindValue(materialID);

    if (!query.exec()) {
        qDebug() << "Ошибка обновления запаса:" << query.lastError().text();
        return false;
    }

    model->submitAll(); // Фиксируем изменения
    model->select(); // Обновляем данные модели
    return true;
}
