#include "typeorderform.h"
#include "ui_typeorderform.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "materials.h" // Для работы с материалами

TypeOrderForm::TypeOrderForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::TypeOrderForm), orderID(-1) {  // -1 для нового заказа
    ui->setupUi(this);
    populateMaterials();
    connect(ui->buttonSave, &QPushButton::clicked, this, &TypeOrderForm::onSave);
}

TypeOrderForm::TypeOrderForm(int orderID, QWidget *parent)
    : QDialog(parent), ui(new Ui::TypeOrderForm), orderID(orderID) {
    ui->setupUi(this);
    populateMaterials();
    if (orderID != -1) {
        loadOrderDetails();  // Загружаем детали заказа
    }
    connect(ui->buttonSave, &QPushButton::clicked, this, &TypeOrderForm::onSave);
}

TypeOrderForm::~TypeOrderForm() {
    delete ui;
}

void TypeOrderForm::populateMaterials() {
    QSqlQuery query("SELECT MaterialID, Name FROM Materials");
    while (query.next()) {
        ui->comboBoxMaterial->addItem(query.value("Name").toString(), query.value("MaterialID"));
    }
}

void TypeOrderForm::loadOrderDetails() {
    QSqlQuery query;
    query.prepare("SELECT Type, MaterialID, Quanity FROM TypeOrders WHERE TypeID = ?");
    query.addBindValue(orderID);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить данные о заказе.");
        return;
    }

    if (!query.next()) {
        qDebug() << "Результат запроса пуст.";
        QMessageBox::critical(this, "Ошибка", "Не удалось найти данные о заказе.");
        return;
    }

    ui->lineEditServiceName->setText(query.value("Type").toString());
    ui->comboBoxMaterial->setCurrentIndex(ui->comboBoxMaterial->findData(query.value("MaterialID")));
    ui->spinBoxQuantity->setValue(query.value("Quanity").toInt());
}

void TypeOrderForm::onSave() {
    QString serviceName = ui->lineEditServiceName->text();
    int materialID = ui->comboBoxMaterial->currentData().toInt();
    int quantity = ui->spinBoxQuantity->value();

    if (serviceName.isEmpty() || quantity <= 0) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    if (materialID <= 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите материал.");
        return;
    }

    QSqlQuery query;
    if (orderID == -1) {
        query.prepare("INSERT INTO TypeOrders (Type, MaterialID, Quanity) VALUES (?, ?, ?)");
        query.addBindValue(serviceName);
        query.addBindValue(materialID);
        query.addBindValue(quantity);
    } else {
        query.prepare("UPDATE TypeOrders SET Type = ?, MaterialID = ?, Quanity = ? WHERE TypeID = ?");
        query.addBindValue(serviceName);
        query.addBindValue(materialID);
        query.addBindValue(quantity);
        query.addBindValue(orderID);
    }

    if (!query.exec()) {
        qDebug() << "Ошибка SQL:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить заказ.");
    } else {
        accept();
    }
}

void TypeOrderForm::updateStockForOrder(int serviceID, int quantity) {
    QSqlQuery query;
    query.prepare("SELECT MaterialID, Quanity FROM TypeOrders WHERE TypeID = ?");
    query.addBindValue(serviceID);
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось найти материалы для услуги.");
        return;
    }
    if (!query.next()) {
        qDebug() << "Результат запроса пуст.";
        QMessageBox::critical(this, "Ошибка", "Не удалось найти материалы для услуги.");
        return;
    }

    int materialID = query.value("MaterialID").toInt();
    int requiredQuantity = query.value("Quanity").toInt();

    // Проверяем текущий запас материала
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT Stock FROM Materials WHERE MaterialID = ?");
    checkQuery.addBindValue(materialID);

    if (!checkQuery.exec() || !checkQuery.next()) {
        qDebug() << "Ошибка проверки запасов:" << checkQuery.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось проверить запасы материала.");
        return;
    }

    int currentStock = checkQuery.value("Stock").toInt();
    int totalRequired = requiredQuantity * quantity;

    if (currentStock < totalRequired) {
        QMessageBox::warning(this, "Ошибка", "Недостаточно материала для выполнения заказа. Требуется: " + QString::number(totalRequired) +
                                                 ", доступно: " + QString::number(currentStock));
        return;
    }

    // Обновляем запасы материала
    Materials materialsManager;
    if (!materialsManager.updateStock(materialID, -totalRequired)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось обновить количество материала.");
    }
}
