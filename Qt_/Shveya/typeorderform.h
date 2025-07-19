#ifndef TYPEORDERFORM_H
#define TYPEORDERFORM_H

#include <QDialog>
#include "materials.h" // Для работы с материалами

namespace Ui {
class TypeOrderForm;
}

class TypeOrderForm : public QDialog {
    Q_OBJECT

public:
    explicit TypeOrderForm(QWidget *parent = nullptr);
    explicit TypeOrderForm(int orderID, QWidget *parent = nullptr); // Конструктор для редактирования
    ~TypeOrderForm();

    void updateStockForOrder(int serviceID, int quantity); // Сделано public для доступа из других классов

private slots:
    void onSave(); // Слот для сохранения данных формы

private:
    Ui::TypeOrderForm *ui; // Указатель на объект пользовательского интерфейса
    int orderID;           // ID заказа для редактирования

    void populateMaterials(); // Загрузка материалов из базы данных
    void loadOrderDetails();  // Загрузка данных о заказе для редактирования
};


#endif // TYPEORDERFORM_H
