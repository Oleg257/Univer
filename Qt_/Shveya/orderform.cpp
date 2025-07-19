#include "orderform.h"
#include "ui_orderform.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "typeorderform.h" // Для взаимодействия с TypeOrderForm

OrderForm::OrderForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::OrderForm), orderID(-1) {  // -1 для нового заказа
    ui->setupUi(this);
    populateClients(); // Заполнение списка клиентов
    populateServices(); // Заполнение списка услуг
    connect(ui->buttonSave, &QPushButton::clicked, this, &OrderForm::onSave);
}

OrderForm::OrderForm(int orderID, QWidget *parent)
    : QDialog(parent), ui(new Ui::OrderForm), orderID(orderID) {
    ui->setupUi(this);
    populateClients(); // Заполнение списка клиентов
    populateServices(); // Заполнение списка услуг
    if (orderID != -1) {
        loadOrderDetails();  // Загружаем детали заказа
    }
    connect(ui->buttonSave, &QPushButton::clicked, this, &OrderForm::onSave);
}

OrderForm::~OrderForm() {
    delete ui;
}

void OrderForm::populateClients() {
    QSqlQuery query("SELECT ClientID, Name FROM Clients");
    while (query.next()) {
        ui->comboBoxClient->addItem(query.value("Name").toString(), query.value("ClientID"));
    }
}

void OrderForm::populateServices() {
    QSqlQuery query("SELECT TypeID, Type FROM TypeOrders");
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить услуги.");
        return;
    }
    while (query.next()) {
        ui->comboBoxService->addItem(query.value("Type").toString(), query.value("TypeID"));
    }
}

void OrderForm::loadOrderDetails() {
    QSqlQuery query;
    query.prepare("SELECT ClientID, TypeOrdersID, Quantity, Status, DateCreated FROM Orders WHERE OrderID = ?");
    query.addBindValue(orderID);
    if (query.exec() && query.next()) {
        int clientID = query.value("ClientID").toInt();
        int typeOrdersID = query.value("TypeOrdersID").toInt();
        // Устанавливаем выбранные значения в выпадающих списках
        ui->comboBoxClient->setCurrentIndex(ui->comboBoxClient->findData(clientID));
        ui->comboBoxService->setCurrentIndex(ui->comboBoxService->findData(typeOrdersID));
        ui->spinBoxQuantity->setValue(query.value("Quantity").toInt());
        ui->comboBoxStatus->setCurrentText(query.value("Status").toString());
        ui->dateEdit->setDate(query.value("DateCreated").toDate());
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить данные о заказе.");
    }
}

void OrderForm::onSave() {
    int clientID = ui->comboBoxClient->currentData().toInt();
    int typeOrdersID = ui->comboBoxService->currentData().toInt();
    int quantity = ui->spinBoxQuantity->value();
    QString status = ui->comboBoxStatus->currentText();
    QDate date = ui->dateEdit->date();

    if (clientID <= 0 || typeOrdersID <= 0 || quantity <= 0) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    QSqlQuery query;
    if (orderID == -1) {
        // Новый заказ
        query.prepare("INSERT INTO Orders (ClientID, TypeOrdersID, Quantity, Status, DateCreated) VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(clientID);
        query.addBindValue(typeOrdersID);
        query.addBindValue(quantity);
        query.addBindValue(status);
        query.addBindValue(date);
    } else {
        // Редактирование существующего заказа
        query.prepare("UPDATE Orders SET ClientID = ?, TypeOrdersID = ?, Quantity = ?, Status = ?, DateCreated = ? WHERE OrderID = ?");
        query.addBindValue(clientID);
        query.addBindValue(typeOrdersID);
        query.addBindValue(quantity);
        query.addBindValue(status);
        query.addBindValue(date);
        query.addBindValue(orderID);
    }

    if (!query.exec()) {
        qDebug() << "Ошибка SQL:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить заказ.");
    } else {
        // Если статус заказа "Выполнено", вызываем метод из TypeOrderForm
        if (status == "Выполнено") {
            Materials materialsManager; // Создаём объект для работы с материалами
            QSqlQuery query;
            query.prepare("SELECT MaterialID, Quanity FROM TypeOrders WHERE TypeID = ?");
            query.addBindValue(typeOrdersID);
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

            if (!materialsManager.updateStock(materialID, -requiredQuantity * quantity)) {
                QMessageBox::critical(this, "Ошибка", "Не удалось обновить количество материала.");
            }

            // Обновляем таблицу материалов в главном окне
            emit materialsUpdated(); // Сигнал для обновления таблицы материалов
        }
        accept();
    }
}
