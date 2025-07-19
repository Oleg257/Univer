#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "orderform.h"
#include "materials.h"
#include "clients.h"
#include "typeorderform.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Настройка таблиц заказов, клиентов, услуг и материалов
    setupOrderTable();
    setupClientsTable();
    setupTypeOrdersTable();
    setupMaterialsTable();

    // Подключение кнопок для заказов
    connect(ui->addOrderButton, &QPushButton::clicked, this, &MainWindow::onAddOrder);
    connect(ui->deleteOrderButton, &QPushButton::clicked, this, &MainWindow::onDeleteOrder);
    connect(ui->toggleEditOrdersButton, &QPushButton::clicked, this, &MainWindow::toggleEditOrders);

    // Подключение кнопок для клиентов
    connect(ui->addClientsButton, &QPushButton::clicked, this, &MainWindow::onAddClients);
    connect(ui->deleteClientsButton, &QPushButton::clicked, this, &MainWindow::onDeleteClients);
    connect(ui->editClientsButton, &QPushButton::clicked, this, &MainWindow::toggleEditClients);

    // Подключение кнопок для услуг
    connect(ui->addTypeOrdersButton, &QPushButton::clicked, this, &MainWindow::onAddTypeOrders);
    connect(ui->deleteTypeOrdersButton, &QPushButton::clicked, this, &MainWindow::onDeleteTypeOrders);
    connect(ui->toggleEditTypeOrdersButton, &QPushButton::clicked, this, &MainWindow::toggleEditTypeOrders);

    // Подключение кнопок для материалов
    connect(ui->addMaterialButton, &QPushButton::clicked, this, &MainWindow::onAddMaterial);
    connect(ui->deleteMaterialButton, &QPushButton::clicked, this, &MainWindow::onDeleteMaterial);
    connect(ui->editMaterialButton, &QPushButton::clicked, this, &MainWindow::toggleEditMaterials);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupOrderTable() {
    orderModel = new QSqlTableModel(this);
    orderModel->setTable("Orders");
    orderModel->select();

    orderModel->setHeaderData(0, Qt::Horizontal, "ID Заказа");
    orderModel->setHeaderData(1, Qt::Horizontal, "Клиент");
    orderModel->setHeaderData(2, Qt::Horizontal, "Тип Заказа");
    orderModel->setHeaderData(3, Qt::Horizontal, "Количество");
    orderModel->setHeaderData(4, Qt::Horizontal, "Статус");
    orderModel->setHeaderData(5, Qt::Horizontal, "Дата");

    ui->ordersTable->setModel(orderModel);
    ui->ordersTable->resizeColumnsToContents();
    ui->ordersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ordersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ordersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setupClientsTable() {
    clients = new Clients(this);
    QSqlTableModel *model = clients->getModel();

    model->setHeaderData(0, Qt::Horizontal, "ID Клиента");
    model->setHeaderData(1, Qt::Horizontal, "Имя клиента");
    model->setHeaderData(2, Qt::Horizontal, "Номер телефона");

    ui->ClientsTable->setModel(model);
    ui->ClientsTable->resizeColumnsToContents();
    ui->ClientsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ClientsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ClientsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    model->select();
}

void MainWindow::setupTypeOrdersTable() {
    typeordersModel = new QSqlTableModel(this);
    typeordersModel->setTable("TypeOrders");
    typeordersModel->select();

    typeordersModel->setHeaderData(0, Qt::Horizontal, "ID Услуги");
    typeordersModel->setHeaderData(1, Qt::Horizontal, "Название");
    typeordersModel->setHeaderData(2, Qt::Horizontal, "Материал");
    typeordersModel->setHeaderData(3, Qt::Horizontal, "Количество");

    ui->TypeOrdersTable->setModel(typeordersModel);
    ui->TypeOrdersTable->resizeColumnsToContents();
    ui->TypeOrdersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TypeOrdersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TypeOrdersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setupMaterialsTable() {
    materials = new Materials(this);
    QSqlTableModel *model = materials->getModel();

    model->setHeaderData(0, Qt::Horizontal, "ID Материала");
    model->setHeaderData(1, Qt::Horizontal, "Материал");
    model->setHeaderData(2, Qt::Horizontal, "Запас");

    ui->materialsTable->setModel(model);
    ui->materialsTable->resizeColumnsToContents();
    ui->materialsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->materialsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->materialsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::onAddOrder() {
    OrderForm form(this);
    if (form.exec() == QDialog::Accepted) {
        orderModel->select();
        refreshMaterialsTable();
    }
}

void MainWindow::toggleEditOrders() {
    QModelIndex selectedIndex = ui->ordersTable->currentIndex();
    if (!selectedIndex.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите заказ для редактирования.");
        return;
    }

    int orderID = ui->ordersTable->model()->data(ui->ordersTable->model()->index(selectedIndex.row(), 0)).toInt();
    OrderForm form(orderID, this);
    if (form.exec() == QDialog::Accepted) {
        orderModel->select();
        refreshMaterialsTable();
    }
}

void MainWindow::refreshMaterialsTable() {
    materials->getModel()->select(); // Перечитываем данные из базы
    ui->materialsTable->resizeColumnsToContents(); // Обновляем размеры столбцов
}

void MainWindow::onDeleteOrder() {
    QModelIndex currentIndex = ui->ordersTable->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите заказ для удаления.");
        return;
    }

    orderModel->removeRow(currentIndex.row());
    if (!orderModel->submitAll()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить заказ.");
    } else {
        orderModel->select();
    }
}

void MainWindow::onAddClients() {
    QString clientsName = QInputDialog::getText(this, "Добавить клиента", "Имя клиента:");
    if (clientsName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Имя клиента не может быть пустым.");
        return;
    }

    QString number = QInputDialog::getText(this, "Добавить номер", "Номер телефона:");
    if (number.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Номер телефона не может быть пустым.");
        return;
    }

    if (!clients->addClients(clientsName, number)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить клиента.");
    }
}

void MainWindow::toggleEditClients() {
    static bool isEditing = false;
    isEditing = !isEditing;

    if (isEditing) {
        ui->ClientsTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
        ui->editClientsButton->setText("Завершить редактирование клиентов");
    } else {
        ui->ClientsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->editClientsButton->setText("Редактировать клиентов");

        if (!clients->getModel()->submitAll()) {
            QMessageBox::critical(this, "Ошибка", "Не удалось сохранить изменения клиентов.");
        } else {
            clients->getModel()->select();
        }
    }
}

void MainWindow::onDeleteClients() {
    QModelIndex currentIndex = ui->ClientsTable->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите клиента для удаления.");
        return;
    }

    // Получаем ID клиента из текущей строки таблицы
    int clientsID = clients->getModel()->data(clients->getModel()->index(currentIndex.row(), 0)).toInt();
    qDebug() << "Извлеченный ClientID:" << clientsID;

    if (clientsID <= 0) {
        QMessageBox::critical(this, "Ошибка", "Некорректный ID клиента.");
        return;
    }

    // Проверяем, существует ли клиент с таким ID
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM Clients WHERE ClientID = ?");
    checkQuery.addBindValue(clientsID);
    if (!checkQuery.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << checkQuery.lastError().text();
        return;
    }
    if (!checkQuery.next() || checkQuery.value(0).toInt() == 0) {
        QMessageBox::critical(this, "Ошибка", "Клиент с указанным ID не существует.");
        return;
    }

    // Удаляем клиента
    if (!clients->deleteClients(clientsID)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить клиента.");
    } else {
        QMessageBox::information(this, "Успех", "Клиент успешно удален.");
    }
}

void MainWindow::onAddTypeOrders() {
    TypeOrderForm form(this);
    if (form.exec() == QDialog::Accepted) {
        typeordersModel->select();
    }
}

void MainWindow::toggleEditTypeOrders() {
    QModelIndex selectedIndex = ui->TypeOrdersTable->currentIndex();
    if (!selectedIndex.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите услугу для редактирования.");
        return;
    }

    int typeID = ui->TypeOrdersTable->model()->data(ui->TypeOrdersTable->model()->index(selectedIndex.row(), 0)).toInt();
    TypeOrderForm form(typeID, this);
    if (form.exec() == QDialog::Accepted) {
        typeordersModel->select();
    }
}

void MainWindow::onDeleteTypeOrders() {
    QModelIndex currentIndex = ui->TypeOrdersTable->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите услугу для удаления.");
        return;
    }

    typeordersModel->removeRow(currentIndex.row());
    if (!typeordersModel->submitAll()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить услугу.");
    } else {
        typeordersModel->select();
    }
}

void MainWindow::onAddMaterial() {
    QString materialName = QInputDialog::getText(this, "Добавить материал", "Название материала:");
    if (materialName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название материала не может быть пустым.");
        return;
    }

    int stock = QInputDialog::getInt(this, "Добавить материал", "Количество на складе:", 1, 1);
    if (!materials->addMaterial(materialName, stock)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить материал.");
    }
}

void MainWindow::toggleEditMaterials() {
    static bool isEditing = false;
    isEditing = !isEditing;

    if (isEditing) {
        ui->materialsTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
        ui->editMaterialButton->setText("Завершить редактирование материалов");
    } else {
        ui->materialsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->editMaterialButton->setText("Редактировать материалы");

        if (!materials->getModel()->submitAll()) {
            QMessageBox::critical(this, "Ошибка", "Не удалось сохранить изменения материалов.");
        } else {
            materials->getModel()->select();
        }
    }
}

void MainWindow::onDeleteMaterial() {
    QModelIndex currentIndex = ui->materialsTable->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите материал для удаления.");
        return;
    }

    int materialID = materials->getModel()->data(materials->getModel()->index(currentIndex.row(), 0)).toInt();
    if (!materials->deleteMaterial(materialID)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить материал.");
    }
}
