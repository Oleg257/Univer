#include "testselectionwindow.h"
#include "ui_testselectionwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

TestSelectionWindow::TestSelectionWindow(QSqlDatabase &database, const QString &action, QWidget *parent)
    : QDialog(parent), ui(new Ui::TestSelectionWindow), db(database), action(action), selectedTestId(-1)
{
    ui->setupUi(this);

    // Загружаем тесты в список
    loadTests();
}

TestSelectionWindow::~TestSelectionWindow()
{
    delete ui;
}

int TestSelectionWindow::getSelectedTestId() const
{
    return selectedTestId;
}

void TestSelectionWindow::loadTests()
{
    QSqlQuery query(db);
    query.prepare("SELECT id, title FROM tests");

    if (!query.exec()) {
        qDebug() << "Database error during loading tests:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить тесты!");
        return;
    }

    ui->testsList->clear(); // Очищаем список

    while (query.next()) {
        int testId = query.value(0).toInt();
        QString testTitle = query.value(1).toString();

        QListWidgetItem *item = new QListWidgetItem(testTitle);
        item->setData(Qt::UserRole, testId); // Сохраняем ID теста в данных элемента
        ui->testsList->addItem(item);
    }
}

void TestSelectionWindow::on_selectButton_clicked()
{
    if (ui->testsList->currentItem() == nullptr) {
        QMessageBox::warning(this, "Ошибка", "Выберите тест из списка!");
        return;
    }

    // Получаем ID выбранного теста
    selectedTestId = ui->testsList->currentItem()->data(Qt::UserRole).toInt();

    if (action == "delete") {
        // Удаляем тест
        QSqlQuery query(db);
        query.prepare("DELETE FROM tests WHERE id = :id");
        query.bindValue(":id", selectedTestId);

        if (!query.exec()) {
            qDebug() << "Database error during test deletion:" << query.lastError().text();
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить тест!");
            return;
        }

        QMessageBox::information(this, "Успех", "Тест успешно удален!");
        accept(); // Закрываем окно
    } else if (action == "edit") {
        // Переходим к редактированию теста
        accept(); // Закрываем окно
    }
}

void TestSelectionWindow::on_cancelButton_clicked()
{
    reject(); // Закрываем окно без выбора
}
