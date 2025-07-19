#include "menu.h"
#include "createtestdialog.h"
#include "testselectionwindow.h"
#include "testeditorwindow.h"
#include "testpasswindow.h"
#include "ui_menu.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QCloseEvent> // Для QCloseEvent

Menu::Menu(QSqlDatabase &database, const QString &role, int userId, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Menu), db(database), userRole(role), currentUserId(userId)
{
    ui->setupUi(this);

    qDebug() << "Menu constructor called. Role:" << userRole << ", User ID:" << currentUserId;

    // Включаем поддержку внешних ключей
    QSqlQuery enableForeignKeys(db);
    if (!enableForeignKeys.exec("PRAGMA foreign_keys = ON;")) {
        qDebug() << "Failed to enable foreign keys:" << enableForeignKeys.lastError().text();
    }

    // Проверка подключения к базе данных
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных!");
        return;
    }

    // Настройка интерфейса в зависимости от роли
    if (userRole == "student") {
        ui->tabWidget->setTabVisible(1, false); // Скрываем вкладку "Создание тестов"
    }

    // Загрузка тестов
    loadTests();
}

Menu::~Menu()
{
    qDebug() << "Menu destructor called.";
    delete ui;
}

void Menu::loadTests()
{
    ui->testsList->clear();

    // Загружаем все тесты
    QSqlQuery query(db);
    query.prepare("SELECT id, title FROM tests");

    if (!query.exec()) {
        qDebug() << "Database error during loading tests:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить тесты!");
        return;
    }

    while (query.next()) {
        int testId = query.value(0).toInt();
        QString testTitle = query.value(1).toString();

        // Находим лучший результат пользователя для данного теста
        double bestPercentage = 0;
        bool hasAttempt = false;

        QSqlQuery resultsQuery(db);
        resultsQuery.prepare("SELECT MAX(score) FROM results "
                             "WHERE test_id = :test_id AND user_id = :user_id");
        resultsQuery.bindValue(":test_id", testId);
        resultsQuery.bindValue(":user_id", currentUserId);

        if (resultsQuery.exec() && resultsQuery.next()) {
            bestPercentage = resultsQuery.value(0).toDouble();
            if (!resultsQuery.isNull(0)) {
                hasAttempt = true; // Пользователь хотя бы раз проходил тест
            }
        }

        // Отображаем результат в списке
        QString displayText;
        if (hasAttempt) {
            displayText = QString("%1 (%2%)").arg(testTitle).arg(bestPercentage, 0, 'f', 1);
        } else {
            displayText = QString("%1 (Не пройден)").arg(testTitle); // Если тест еще не пройден
        }

        QListWidgetItem *item = new QListWidgetItem(displayText);
        item->setData(Qt::UserRole, testId);
        ui->testsList->addItem(item);
    }
}

void Menu::on_selectTestButton_clicked()
{
    // Получаем выбранный элемент из списка
    QListWidgetItem *selectedItem = ui->testsList->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Ошибка", "Выберите тест из списка!");
        return;
    }

    // Получаем ID выбранного теста
    int selectedTestId = selectedItem->data(Qt::UserRole).toInt();

    // Открываем окно прохождения теста
    TestPassWindow passWindow(db, selectedTestId, currentUserId, this);

    // Подключаем сигнал завершения теста к обновлению списка тестов
    connect(&passWindow, &TestPassWindow::testFinished, this, &Menu::updateTestList);

    passWindow.exec();
}

void Menu::updateTestList(double percentage)
{
    qDebug() << "Updating test list with percentage:" << percentage;

    // Обновляем список тестов
    loadTests();

}

void Menu::on_createTestButton_clicked()
{
    CreateTestDialog createDialog(this);
    if (createDialog.exec() == QDialog::Accepted) {
        QString testTitle = createDialog.getTestTitle();

        // Добавляем новый тест в базу данных с author_id
        QSqlQuery query(db);
        query.prepare("INSERT INTO tests (title, author_id) VALUES (:title, :author_id)");
        query.bindValue(":title", testTitle);
        query.bindValue(":author_id", currentUserId);

        if (!query.exec()) {
            qDebug() << "Database error during test creation:" << query.lastError().text();
            QMessageBox::critical(this, "Ошибка", "Не удалось создать тест!\n"
                                                  "Причина: " + query.lastError().text());
            return;
        }

        int testId = query.lastInsertId().toInt(); // Получаем ID созданного теста
        qDebug() << "Test created with ID:" << testId;

        // Убедитесь, что транзакция завершена
        db.commit();

        // Проверяем, существует ли тест в базе данных
        QSqlQuery checkQuery(db);
        checkQuery.prepare("SELECT id FROM tests WHERE id = :id");
        checkQuery.bindValue(":id", testId);

        if (!checkQuery.exec() || !checkQuery.next()) {
            qDebug() << "Test not found in database for ID:" << testId;
            QMessageBox::critical(this, "Ошибка", "Созданный тест не найден в базе данных!");
            return;
        }

        // Открываем окно редактирования теста
        TestEditorWindow editorWindow(db, testId, this);
        if (editorWindow.exec() == QDialog::Accepted) {
            qDebug() << "Test editing completed successfully.";
        } else {
            qDebug() << "Test editing canceled.";
        }

        loadTests(); // Обновляем список тестов
    }
}

void Menu::on_editTestButton_clicked()
{
    TestSelectionWindow selectionWindow(db, "edit", this);
    if (selectionWindow.exec() == QDialog::Accepted) {
        int testId = selectionWindow.getSelectedTestId();
        qDebug() << "Edit test with ID:" << testId;

        // Проверяем, существует ли тест
        QSqlQuery query(db);
        query.prepare("SELECT id FROM tests WHERE id = :id");
        query.bindValue(":id", testId);

        if (!query.exec() || !query.next()) {
            qDebug() << "Test not found in database for ID:" << testId;
            QMessageBox::critical(this, "Ошибка", "Выбранный тест не найден в базе данных!");
            return;
        }

        // Открываем окно редактирования теста
        TestEditorWindow editorWindow(db, testId, this);
        if (editorWindow.exec() == QDialog::Accepted) {
            qDebug() << "Test editing completed successfully.";
        } else {
            qDebug() << "Test editing canceled.";
        }
    }
}

void Menu::on_deleteTestButton_clicked()
{
    TestSelectionWindow selectionWindow(db, "delete", this);
    if (selectionWindow.exec() == QDialog::Accepted) {
        int testId = selectionWindow.getSelectedTestId();
        qDebug() << "Delete test with ID:" << testId;

        // Удаляем тест из базы данных
        QSqlQuery query(db);
        query.prepare("DELETE FROM tests WHERE id = :id");
        query.bindValue(":id", testId);

        if (!query.exec()) {
            qDebug() << "Database error during test deletion:" << query.lastError().text();
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить тест!");
            return;
        }

        loadTests(); // Обновляем список тестов
    }
}

void Menu::on_exitButton_clicked()
{
    close(); // Закрываем окно Menu
}

void Menu::closeEvent(QCloseEvent *event)
{
    qDebug() << "Menu close event triggered.";
    emit menuClosed(); // Генерируем собственный сигнал
    event->accept();
}
