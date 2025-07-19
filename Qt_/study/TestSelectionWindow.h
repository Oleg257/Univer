#ifndef TESTSELECTIONWINDOW_H
#define TESTSELECTIONWINDOW_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class TestSelectionWindow;
}

class TestSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestSelectionWindow(QSqlDatabase &database, const QString &action, QWidget *parent = nullptr);
    ~TestSelectionWindow();

    int getSelectedTestId() const; // Получить ID выбранного теста

private slots:
    void on_selectButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::TestSelectionWindow *ui;
    QSqlDatabase db;
    QString action; // Действие: "create", "edit", "delete"
    int selectedTestId; // ID выбранного теста

    void loadTests(); // Загрузка тестов из базы данных
};

#endif // TESTSELECTIONWINDOW_H
