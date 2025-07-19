#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "materials.h"
#include "orderform.h"
#include "clients.h"
#include "typeorderform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Модель для заказов
    QSqlTableModel *orderModel;
    QSqlTableModel *typeordersModel;

    // Модель для материалов (нужна для работы с материалами)
    Materials *materials;

    // Модель для клиентов
    Clients *clients;

    // Функции для настройки таблиц
    void setupOrderTable();
    void setupMaterialsTable();
    void setupClientsTable();
    void setupTypeOrdersTable(); // Добавлено объявление функции для таблицы материалов

    // Обработчики кнопок
    void onAddOrder();
    void toggleEditOrders();
    void onDeleteOrder();
    void onAddMaterial();  // Обработчик для добавления материала
    void toggleEditMaterials();
    void onDeleteMaterial();
    void onAddClients();
    void onDeleteClients();
    void toggleEditClients();
    void onAddTypeOrders();  // Обработчик для добавления услуги
    void toggleEditTypeOrders();
    void onDeleteTypeOrders();

    QPushButton *editModeButton; // Кнопка для переключения режима
    bool materialsEditable = false; // Флаг редактируемости
    bool clientsEditable = false;

    // Новый метод для обновления таблицы материалов
    void refreshMaterialsTable();
};

#endif // MAINWINDOW_H
