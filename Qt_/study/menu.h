#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QString>
#include "testpasswindow.h" // Подключаем TestPassWindow для сигнала testFinished

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QSqlDatabase &database, const QString &role, int userId, QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_createTestButton_clicked();
    void on_editTestButton_clicked();
    void on_deleteTestButton_clicked();
    void on_exitButton_clicked();
    void on_selectTestButton_clicked();
    void updateTestList(double percentage); // Добавляем объявление метода

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void menuClosed(); // Сигнал о закрытии окна

private:
    Ui::Menu *ui;
    QSqlDatabase db;
    QString userRole;
    int currentUserId; // ID текущего пользователя

    void loadTests(); // Загрузка тестов из базы данных
};

#endif // MENU_H
