#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QDialog>

namespace Ui {
class OrderForm;
}

class OrderForm : public QDialog {
    Q_OBJECT

public:
    explicit OrderForm(QWidget *parent = nullptr);
    explicit OrderForm(int orderID, QWidget *parent = nullptr);  // Конструктор для редактирования
    ~OrderForm();

private slots:
    void onSave(); // Слот для сохранения данных формы

private:
    Ui::OrderForm *ui; // Указатель на объект пользовательского интерфейса
    int orderID;       // ID заказа для редактирования

    void populateClients();  // Загрузка клиентов из базы данных
    void populateServices(); // Загрузка услуг из базы данных
    void loadOrderDetails(); // Загрузка данных о заказе для редактирования

signals:
    void materialsUpdated(); // Сигнал для обновления таблицы материалов
};

#endif // ORDERFORM_H
